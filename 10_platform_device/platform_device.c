#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>

void	my_device_release(struct device *dev){
    printk("This is my_device_release");
}

static struct resource my_device_resources[] = {
    [0] = {
        .start = 0xFDD60000,
        .end   = 0xFDD60004,
        .flags = IORESOURCE_MEM,
    },
    [1] = {
        .start = 13,
        .end   = 13,
        .flags = IORESOURCE_IRQ,
    },
};

struct platform_device platform_device_test = {
    .name = "my_device",
    .id = 0,
    .resource = my_device_resources,
    .num_resources = ARRAY_SIZE(my_device_resources),
    .dev = {
        .release = my_device_release,
    },
};

static int platform_device_init(void)
{
    platform_device_register(&platform_device_test);
    printk("platform_device_init!\n");
    return 0;
}

static void platform_device_exit(void)
{
     platform_device_unregister(&platform_device_test);
    printk("platform_device_exit\n");
}

module_init(platform_device_init);
module_exit(platform_device_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fashi");
MODULE_VERSION("V1.0");