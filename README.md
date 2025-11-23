# Лабораторна робота 4: Модулі ядра Linux

**Студент:** Сас Євгеній, група IO-31, номер 20  
**Дата:** 23 листопада 2025

## Опис

Kernel module з параметром та linked list для зберігання часу подій.

## Особливості

- Параметр `count` - кількість виводів "Hello, world!" (default=1)
- Перевірка параметрів:
  - count=0 або 5-10: WARNING
  - count>10: ERROR, модуль не завантажується
- Linked list для зберігання timestamps (ktime_t)
- Вивід часу кожної події при rmmod в наносекундах

## Компіляція
```bash
export KDIR=$HOME/repos/linux-stable
export PATH=/opt/gcc-arm-8.3-2019.03-x86_64-arm-eabi/bin:$PATH
export CROSS_COMPILE='ccache arm-eabi-'
export ARCH=arm

make
```

## Тестування
```bash
# Без параметра
insmod hello.ko
rmmod hello

# З параметром
insmod hello.ko count=3
rmmod hello

# Перевірка параметра
cat /sys/module/hello/parameters/count
```

## Результати

Всі тести пройшли успішно:
- ✅ count=1 (default)
- ✅ count=0 (WARNING)
- ✅ count=3 (нормальна робота)
- ✅ count=7 (WARNING, між 5-10)
- ✅ count=15 (ERROR, відмова завантаження)
