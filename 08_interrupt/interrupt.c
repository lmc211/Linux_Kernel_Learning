#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>

int irq;
struct tasklet_struct mytasklet;

void mytasklet_function(unsigned long data){
    printk("This is mytasklet_function data = %ld\n", data);
}

//DEFINE_TASKLET(mytasklet, mytasklet_function, 1);

irqreturn_t test_interrupt(int irq, void* arg){
    printk("This is test_interrupt");
    tasklet_schedule(&mytasklet);
    return IRQ_RETVAL(IRQ_HANDLED);
}

static int interrupt_irq_init(void){
    int ret;
    irq = gpio_to_irq(35);
    ret = request_irq(irq, test_interrupt, IRQF_TRIGGER_RISING, "test", NULL);
    if(ret < 0){
        printk("interrupt_irq_init error \n");
        return -1;
    }
    tasklet_init(&mytasklet, mytasklet_function, 1);
    return 0;
}

static void interrupt_irq_exit(void){
    tasklet_kill(&mytasklet);
    tasklet_disable(&mytasklet);
    free_irq(irq, NULL);
    printk("bye bye");

}


module_init(interrupt_irq_init);
module_exit(interrupt_irq_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LMC");
MODULE_VERSION("V 1.0");
