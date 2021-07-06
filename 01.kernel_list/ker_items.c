#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

struct timer_list my_timer;
struct list_head stu_head;
struct list_head data_head;
void * p_stu;
void * p_data;

struct student
{
  struct list_head list;
  char name[20];
  int age;
};

struct data
{
  char prefix[20];
  char content[20];
  struct list_head list;
  char seqno;
};

static void timeout_callback(struct timer_list *t)
{
	static int n=0;
	printk("timeout n=%d\n",n++);
	gpio_set_value(132,(n%2));
	mod_timer(t, jiffies + HZ);
}

static int ker_items_init(void)
{
    int i=0;
	struct list_head *pos;
	struct student *p;
	struct data *d;
	printk("Hello, world\n");
    gpio_direction_output(132,0);
	timer_setup(&my_timer,timeout_callback,0);
	mod_timer(&my_timer, jiffies + HZ);
    
    INIT_LIST_HEAD(&stu_head);
	INIT_LIST_HEAD(&data_head);
    for(i=0;i<10;i++){
    	struct student *s = kmalloc(sizeof(struct student), GFP_KERNEL);
		sprintf(s->name,"wang %d",i);
        s->age = 2*i+1;
		list_add(&s->list, &stu_head);
	}
	for(i=0;i<10;i++){
		struct data *d = kmalloc(sizeof(struct data), GFP_KERNEL);
		sprintf(d->prefix,"AT");
		sprintf(d->content,"name %d",i);
		d->seqno = i;
		list_add(&d->list, &data_head);
	}
	list_for_each_entry(p,&stu_head,list){
		printk("--------------\n");
		printk("student : %s    age:%d\n",p->name, p->age);
	}
    list_for_each(pos, &data_head){
		printk("--------------\n");
		d = container_of(pos, struct data, list);
		printk("prefix : %s\tcontent:%s\tseqno=%d\n",d->prefix, d->content,d->seqno);
	}
	list_for_each_entry(d,&data_head,list){
		printk("--------------\n");
		printk("prefix : %s\tcontent:%s\tseqno=%d\n",d->prefix, d->content,d->seqno);
	}
	return 0;
}

static void ker_items_exit(void)
{
	struct student *ps,*ns;
    struct data *pd,*nd;
	list_for_each_entry_safe(ps, ns, &stu_head, list){
		printk("------free--------\n");
		printk("student : %s    age:%d\n",ps->name, ps->age);
		kfree(ps);
	}
	list_for_each_entry_safe(pd, nd, &data_head, list){
		printk("------free--------\n");
		printk("prefix : %s\tcontent:%s\tseqno=%d\n",pd->prefix, pd->content, pd->seqno);
		kfree(pd);
	}
	del_timer(&my_timer);
	gpio_direction_input(132);
	printk("Goodbye, cruel world\n");
}

module_init(ker_items_init);
module_exit(ker_items_exit);
MODULE_LICENSE("GPL");
