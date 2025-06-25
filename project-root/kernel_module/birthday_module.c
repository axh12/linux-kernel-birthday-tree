#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Kernel module with birthday list implementation");
MODULE_VERSION("1.0");

// Define the birthday structure
struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};

// Head of the birthday list
static LIST_HEAD(birthday_list);

// Function to add a birthday to the list
static void add_birthday(int day, int month, int year) {
    struct birthday *person;

    // Allocate memory for the new birthday struct
    person = kmalloc(sizeof(*person), GFP_KERNEL);
    if (!person) {
        printk(KERN_ERR "birthday_module: Memory allocation failed\n");
        return;
    }

    // Initialize the birthday struct
    person->day = day;
    person->month = month;
    person->year = year;
    INIT_LIST_HEAD(&person->list);

    // Add the birthday to the list
    list_add_tail(&person->list, &birthday_list);

    printk(KERN_INFO "birthday_module: Added birthday %d/%d/%d\n", day, month, year);
}

// Function to display the list contents in the kernel log
static void display_birthdays(void) {
    struct birthday *ptr;
    printk(KERN_INFO "birthday_module: Birthday List:\n");
    list_for_each_entry(ptr, &birthday_list, list) {
        printk(KERN_INFO "birthday_module: %d/%d/%d\n", ptr->day, ptr->month, ptr->year);
    }
}

// Function to remove all birthdays from the list
static void remove_all_birthdays(void) {
    struct birthday *ptr, *next;
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {
        list_del(&ptr->list);
        kfree(ptr);
    }
}

// /proc file operations
static int birthday_proc_show(struct seq_file *m, void *v) {
    struct birthday *ptr;
    seq_printf(m, "Birthday List:\n");
    list_for_each_entry(ptr, &birthday_list, list) {
        seq_printf(m, "%d/%d/%d\n", ptr->day, ptr->month, ptr->year);
    }
    return 0;
}

static int birthday_proc_open(struct inode *inode, struct file *file) {
    return single_open(file, birthday_proc_show, NULL);
}

static const struct proc_ops birthday_proc_fops = {
    .proc_open = birthday_proc_open,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

// Init function (called when module is loaded)
static int __init birthday_module_init(void) {
    printk(KERN_INFO "birthday_module: Initializing module\n");

    // Add sample birthdays
    add_birthday(2, 8, 1995);
    add_birthday(15, 5, 1990);
    add_birthday(7, 11, 1985);
    add_birthday(22, 3, 2000);
    add_birthday(30, 9, 1992);

    // Display in kernel log
    display_birthdays();

    // Create /proc entry
    proc_create("birthday_list", 0, NULL, &birthday_proc_fops);

    printk(KERN_INFO "birthday_module: Module loaded successfully\n");
    return 0;
}

// Exit function (called when module is unloaded)
static void __exit birthday_module_exit(void) {
    printk(KERN_INFO "birthday_module: Removing module\n");

    // Remove /proc entry
    remove_proc_entry("birthday_list", NULL);

    // Free allocated memory
    remove_all_birthdays();

    printk(KERN_INFO "birthday_module: Module removed successfully\n");
}

module_init(birthday_module_init);
module_exit(birthday_module_exit);

