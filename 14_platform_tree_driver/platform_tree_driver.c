#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/mod_devicetable.h>
#include <linux/of.h>

struct resource* Myresource;
struct device_node* my_device_node_led;
struct device_node* my_device_node;

const struct of_device_id* mynode_match;
const struct of_device_id of_match_table_id[] = {
    {.compatible = "atkrk3588-led"},
    {}
};

int size;
int num;
u32 value_u32;
u64 value_u64;
u32 value_u32_array[16];
const char* value_compatible;

struct property *led_property;
int MyDriver_probe(struct platform_device *dev){
    printk("MyDriver_probe \n");

    my_device_node_led = of_find_node_by_name(NULL, "rk3588_led");
    printk("my_device_node_led is %s\n", my_device_node_led->name);

    led_property = of_find_property(my_device_node_led, "compatible", &size);
    printk("my_device_node_led name is %s\n", led_property->name);

    num = of_property_count_elems_of_size(my_device_node_led, "reg", 4);
    printk("num is %d\n", num);

    of_property_read_u32_index(my_device_node_led, "reg", 1, &value_u32);
    of_property_read_u64_index(my_device_node_led, "reg", 1, &value_u64);
    printk("value_u32 is %x\n", value_u32);
    printk("value_u64 is %llx\n", value_u64);

    of_property_read_variable_u32_array(my_device_node_led, "reg", value_u32_array, 1, 16);
    printk("value_u32_array[0] is %x\n", value_u32_array[0]);
    printk("value_u32_array[1] is %x\n", value_u32_array[1]);

    of_property_read_string(my_device_node_led, "compatible", &value_compatible);
    printk("value_compatible is %s\n", value_compatible);

    Myresource = platform_get_resource(dev, IORESOURCE_MEM, 0);
    if(Myresource == NULL){
        printk("Myresource is error\n");
        return -1;
    }
    return 0;
}

int MyDriver_remove(struct platform_device *dev){
    printk("MyDriver_remove \n");
    return 0;
}
/*
const struct platform_device_id MyDriver_Idtable[] = {
    {.name = "atkrk3588-led"},
    {}
};
*/

struct platform_driver platform_driver_test = {
    .probe = MyDriver_probe,
    .remove = MyDriver_remove,
    .driver = {
        .name = "atkrk3588-led",
        .owner = THIS_MODULE,
        .of_match_table = of_match_table_id,
    },
    //.id_table = &MyDriver_Idtable,
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