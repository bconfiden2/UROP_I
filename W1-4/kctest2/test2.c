#include <linux/kernel.h>
#include <linux/module.h>
#include "../moduleparams.h"
#include <linux/unistd.h>

void **sys_call_table;

asmlinkage int (*original_call) (const char*, int, int);

asmlinkage int our_sys_open(const char* file, int flags, int mode)
{
   printk("A file was opened\n");
   return original_call(file, flags, mode);
}
int init_module()
{
    // sys_call_table address in System.map
    sys_call_table = (void*)0xffffffff820002a0;
    original_call = sys_call_table[__NR_open];
    // Hook: Crashes here
    sys_call_table[__NR_open] = our_sys_open;
}
void cleanup_module()
{
   // Restore the original call
   sys_call_table[__NR_open] = original_call;
}
