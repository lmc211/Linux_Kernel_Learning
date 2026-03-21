#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>

int irq;

void mysoftirq_function(struct softirq_action *softirq_action){
    printk("This is mysoftirq_function \n");
}

irqreturn_t test_interrupt(int irq, void* arg){
    printk("This is test_interrupt");
    raise_softirq(TEST_SOFTIRQ);
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
    open_softirq(TEST_SOFTIRQ, mysoftirq_function);
    return 0;
}

static void interrupt_irq_exit(void){
    free_irq(irq, NULL);
    printk("bye bye");

}


module_init(interrupt_irq_init);
module_exit(interrupt_irq_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("LMC");
MODULE_VERSION("V 1.0");
