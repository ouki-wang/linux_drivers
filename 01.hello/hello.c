#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/moduleparam.h>



static int hello_init(void)
{
	printk("hello world\n");
	return 0;
}

static void hello_exit(void)
{
	printk("Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_AUTHOR("Ouki.Wang <dzdzz@qq.com>");
MODULE_DESCRIPTION("Hello World Linux Driver");
MODULE_LICENSE("GPL");

