#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>

static dev_t dev_num;

// 定义静态全局变量，默认值为0（表示动态分配）
static int major = 0;
static int minor = 0;

// 将变量暴露为可加载模块参数
module_param(major, int, S_IRUGO);
module_param(minor, int, S_IRUGO);

static int moduleparam_init(void)
{
    int ret;

    if (major) {
        // 1. 静态指定主设备号
        printk(KERN_EMERG "major is %d\n", major);
        printk(KERN_EMERG "minor is %d\n", minor);
        // 拼接主次设备号
        dev_num = MKDEV(major, minor);
        // 注册设备号区域（1个设备）
        ret = register_chrdev_region(dev_num, 1, "chrdev_name");
        if (ret < 0) {
            printk(KERN_EMERG "register_chrdev_region is error\n");
        }
        printk(KERN_EMERG "register_chrdev_region is ok\n");
    } else {
        // 2. 动态申请设备号
        ret = alloc_chrdev_region(&dev_num, 0, 1, "alloc_name");
        if (ret < 0) {
            printk(KERN_EMERG "alloc_chrdev_region is error\n");
        }
        printk(KERN_EMERG "alloc_chrdev_region is ok\n");
        // 从dev_t中提取主设备号
        major = MAJOR(dev_num);
        // 从dev_t中提取次设备号
        minor = MINOR(dev_num);
        printk(KERN_EMERG "major is %d\n", major);
        printk(KERN_EMERG "minor is %d\n", minor);
    }
    return 0;
}

static void moduleparam_exit(void)
{
    // 释放设备号区域
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_EMERG "bye bye\n");
}

module_init(moduleparam_init);
module_exit(moduleparam_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("lmc");
MODULE_VERSION("V1.0");


//编译命令 先告诉编译器的位置
//export PATH=$PATH:/home/alientek/rk3588_linux_sdk/prebuilts/gcc/linux-x86/aarch64/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin
//make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu-
//make ARCH=arm64 CROSS_COMPILE=/home/alientek/rk3588_linux_sdk/prebuilts/gcc/linux-x86/aarch64/gcc-arm-10.3-2021.07-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-