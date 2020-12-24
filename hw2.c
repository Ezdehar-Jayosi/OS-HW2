#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/list.h>
//////////////////////helper functions////////////////////////
long getChildrenWeight(struct task_struct* task){
    int sum=0;
    struct list_head* list_head;
     if(&(current->children) == current->children.next){
 		return 0;
 	}
    list_for_each(list_head,&(task->children)){
        struct task_struct* child_tasks = list_entry(list_head,struct task_struct, sibling);
        sum += child_tasks->task_weight;
        //printk("child_tasks->task_weight is %d  child_pid is %d\n",child_tasks->task_weight, child_tasks->pid);
        sum += getChildrenWeight(child_tasks);
    
    }
    return sum;
}
long getHaeviestPid(struct task_struct* task){
    struct list_head* list_head;
    long prev_sum=0;
    long heavy_pid = 0;
   
    list_for_each(list_head,&(task->children)){
        struct task_struct* child_tasks = list_entry(list_head,struct task_struct, sibling);
        int sum = getChildrenWeight(child_tasks);
        sum += child_tasks->task_weight;
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
asmlinkage long sys_set_weight(int weight){
    //printk("weight is %d\n",weight);
    if(weight < 0) return -EINVAL;
    current->task_weight = weight;
    return 0;

}


//335
asmlinkage long sys_get_total_weight(void){
    //printk("parent weight is %d\n",current->task_weight);
  int weight_sum=getChildrenWeight(current);
  int current_weight = current->task_weight;
  //printk("total weight is %d\n",weight_sum+current_weight);
  return weight_sum+current_weight;

}
 
 
//336
asmlinkage long sys_get_heaviest_child(void){
  if(&(current->children) == current->children.next){
		return -ECHILD;
    }
  long heaviest_pid =getHaeviestPid(current);
  if(heaviest_pid == 0) return -ECHILD;
  return heaviest_pid;

}