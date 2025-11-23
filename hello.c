// SPDX-License-Identifier: GPL-2.0
/*
 * hello.c - Kernel module with parameter and linked list
 * Author: Sas Yevhenii, IO-31
 * Date: November 23, 2025
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>

MODULE_AUTHOR("Sas Yevhenii <qwerty2015f5@gmail.com>");
MODULE_DESCRIPTION("Hello world module with parameter and timing");
MODULE_LICENSE("GPL");

/* Module parameter */
static uint count = 1;
module_param(count, uint, 0444);
MODULE_PARM_DESC(count, "Number of times to print 'Hello, world!' (default=1)");

/* Structure for linked list */
struct timing_entry {
	struct list_head list;
	ktime_t timestamp;
};

/* Static head of the list */
static LIST_HEAD(timing_list);

static int __init hello_init(void)
{
	uint i;
	struct timing_entry *entry;

	pr_info("Hello module: count parameter = %u\n", count);

	/* Check parameter value */
	if (count == 0 || (count >= 5 && count <= 10))
		pr_warn("Hello module: Warning! Parameter is %u\n", count);

	if (count > 10) {
		pr_err("Hello module: Error! Parameter %u > 10\n", count);
		return -EINVAL;
	}

	/* Print hello messages and record timestamps */
	for (i = 0; i < count; i++) {
		/* Allocate memory for timing entry */
		entry = kmalloc(sizeof(*entry), GFP_KERNEL);
		if (!entry)
			return -ENOMEM;

		/* Record current kernel time */
		entry->timestamp = ktime_get();

		/* Add to list */
		list_add_tail(&entry->list, &timing_list);

		/* Print hello message */
		pr_info("Hello, world!\n");
	}

	return 0;
}

static void __exit hello_exit(void)
{
	struct timing_entry *entry, *tmp;
	ktime_t elapsed;

	pr_info("Hello module: cleaning up\n");

	/* Walk through the list, print timestamps, and free memory */
	list_for_each_entry_safe(entry, tmp, &timing_list, list) {
		elapsed = entry->timestamp;
		pr_info("Hello module: Event at %lld ns\n",
			ktime_to_ns(elapsed));

		/* Remove from list and free memory */
		list_del(&entry->list);
		kfree(entry);
	}

	pr_info("Goodbye, world!\n");
}

module_init(hello_init);
module_exit(hello_exit);

