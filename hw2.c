#include <linux/kernel.h>
#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/kernel.h>
//////////////////////helper functions////////////////////////
int getChildrenWeight(struct task_struct* task){
    int sum=0;
    struct list_head* list_head;
    list_for_each(list_head,task){
        struct task_struct* child_tasks = list_entry(list_head,struct task_struct, sibling);
        sum += child_task->task_weight;
        sum += getchildrenWeight(child_tasks);
    
    }
    return sum;
}
pid_t getHaeviestPid(struct task_struct* task){
    struct list_head* list_head;
    int prev_sum=0;
    int heavy_pid;
    list_for_each(list_head,task){
        struct task_struct* child_tasks = list_entry(list_head,struct task_struct, sibling);
        int sum = getChildrenWeight(child_tasks);
        if(prev_sum <= sum){
            prev_sum=sum;
            heavy_pid=child_tasks->pid;
        
        }
        
    
    }
    return heavy_pid;
}

////////////////////////////////
//333
asmlinkage long sys_hello(void){
    printk("Hello, World!\n");
    return 0;

}

//334
asmlinkage int sys_set_weight(int weight){
    if(weight < 0) return EINVAL;
    current->task_weigth = weight;
    return 0;

}


//335
asmlinkage int sys_get_total_weight(void){
  int weight_sum=0;
  struct list_head* list_head;
   list_for_each(list_head, &current->children) {
        struct task_struct* child = list_entry(list_head, struct task_struct, sibling);
        weight_sum+= child->task_weight;
   }
 // weight_sum = getChildrenWeight(current);
  int current_weight = current->task_weight;
  return weight_sum+current_sum;

}
 
 
 //336
asmlinkage pid_t sys_get_heaviest_child(void){
  
  int heaviest_pid =getHaeviestPid(current)
  if(heaviest_pid == 0) return ECHILD;
  return heaviest_pid;

}