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

int MyDriver_probe(struct platform_device *dev){
    printk("MyDriver_probe \n");

    my_device_node_led = of_find_node_by_name(NULL, "rk3588_led");
    printk("my_device_node_led is %s", my_device_node_led->name);

    my_device_node = of_find_node_by_path("/reserved-memory/cma");
    printk("my_device_node is %s", my_device_node->name);

    my_device_node = of_get_parent(my_device_node);
    printk("my_device_node parent is %s", my_device_node->name);

    my_device_node = of_get_next_child(my_device_node, NULL);
    printk("my_device_node parent's child is %s", my_device_node->name);

    my_device_node_led = of_find_compatible_node(NULL, NULL, "atkrk3588-led");
    printk("my_device_node_led is %s", my_device_node_led->name);

    my_device_node_led = of_find_matching_node_and_match(NULL, of_match_table_id, &mynode_match);
    printk("my_device_node_led is %s", my_device_node_led->name);

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