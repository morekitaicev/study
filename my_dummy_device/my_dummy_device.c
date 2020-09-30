/* Подключаем модули и макросы */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h> 

// Информация о модуле для команды modinfo
MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Ilya Asadullin <asadullin.ilya@yandex.ru>" );
MODULE_DESCRIPTION( "my_dummy_device" );
MODULE_SUPPORTED_DEVICE( "my_dummy_device" );

#define SUCCESS 0
#define DEVICE_NAME "my_dummy_device" /* Имя устройства*/

/* Объявление функций устройства */
static int device_open( struct inode *, struct file *);
static int device_release( struct inode *, struct file *);
static ssize_t device_read( struct file *, char *, size_t, loff_t *);
static ssize_t device_write( struct file *, const char *, size_t, loff_t *);

static int major_number; /* Старший номер устройства драйвера */
static int is_device_open = 0; /* Состояние */
static char text[14] = "Hello, world!\n"; /* Текст, выдающийся при обращении к устройству */
static char* text_ptr = text; /* Указатель на текущую позицию в тексте */

/* Структура операций над устройством*/
static struct file_operations fops =
{
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};

// Функция загрузки модуля
static int __init test_init( void )
{
	/* Функция printk выводит текст в журнал ядра */
	printk(KERN_ALERT "my_dummy_device is loaded!\n");

	// Регистрируем устройсво и получаем старший номер устройства
	major_number = register_chrdev(0, DEVICE_NAME, &fops);
	
	/* Если регистрация не удалась*/
	if (major_number < 0)
	{
		printk("Registering the character device failed with %d\n", major_number);
		return major_number;
	}

	/* Сообщаем присвоенный нам старший номер устройства */
	printk("my_dummy_device is loaded!\n");

	/* Выводим в журнал ядря сообщение для создания символьного устройства и номер этого устройства*/
	printk("Please, create a dev file with 'mknod /dev/my_dummy_device c %d 0'.\n", major_number);

	return SUCCESS;
}

// Функция выгрузки модуля
static void __exit test_exit( void )
{
	// Освобождаем устройство
	unregister_chrdev(major_number, DEVICE_NAME);

	printk(KERN_ALERT "my_dummy_device is unloaded!\n");
}

// Указываем наши функции загрузки и выгрузки
module_init(test_init);
module_exit(test_exit);

/* Открытие девайса */
static int device_open(struct inode *inode, struct file *file)
{
	text_ptr = text;

	if (is_device_open)
		return -EBUSY;

	is_device_open++;

	return SUCCESS;
}

/* Закрытие девайса */
static int device_release(struct inode *inode, struct file *file)
{
	is_device_open--;
	return SUCCESS;
}

/* Запись в журнал ядра */
static ssize_t device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	printk("Unknown operation.\n");
	return -EINVAL;
}

/* Чтение из журнала ядра */
static ssize_t device_read(struct file *filp,
       char *buffer,
       size_t length,
       loff_t * offset)
{
	int byte_read = 0;

	if (*text_ptr == 0)
		return 0;

	while (length && *text_ptr)
	{
		put_user(*(text_ptr++), buffer++);
		length--;
		byte_read++;
	}

	return byte_read;
}

