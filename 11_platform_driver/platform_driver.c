#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>

struct resource* Myresource;

int MyDriver_probe(struct platform_device *dev){
    printk("MyDriver_probe \n");
    printk("IRQ is %lld", dev->resource[1].start);

    Myresource = platform_get_resource(dev, IORESOURCE_IRQ, 0);
    printk("IRQ is %lld", Myresource->start);

    return 0;
}

int MyDriver_remove(struct platform_device *dev){
    printk("MyDriver_remove \n");
    return 0;
}

const struct platform_device_id MyDriver_Idtable[] = {
    {.name = "my_device"},
    {}
};

struct platform_driver platform_driver_test = {
    .probe = MyDriver_probe,
    .remove = MyDriver_remove,
    .driver = {
        .name = "my_device",
        .owner = THIS_MODULE
    },
    .id_table = MyDriver_Idtable,
};


static int platform_driver_init(void)
{
    platform_driver_register(&platform_driver_test);
    printk("platform_driver_init!\n");
    return 0;
}

static void platform_driver_exit(void)
{
    platform_driver_unregister(&platform_driver_test);
    printk("platform_driver_exit\n");
}

module_init(platform_driver_init);
module_exit(platform_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("fashi");
MODULE_VERSION("V1.0");