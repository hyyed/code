#include <stdio.h>
#include "list.h"
#include <stdlib.h>
#include <string.h>

//使用内核链表来存储学生信息
struct Student 
{
    char name[32];
    int age;
    struct list_head list; //内核链表
};

// 创建节点
void creat_node(struct Student* stu, const char *name, int age){
    stu->age = age;
    strcpy(stu->name ,name);
    INIT_LIST_HEAD(&stu->list);
}


int main(void)
{
    //创建头
    struct Student *shead = (struct Student*)malloc(sizeof(struct Student));
    creat_node(shead, "",0);

    //录入数据---从文件录入数据
    FILE *file = fopen("./stuinfo.txt", "r");
    if(file ==  NULL) {
        free(shead);
        return -1;
    }

    //一行一行读取文件中数据
    char name[32];
    int age;
    while(1){
        int ret = fscanf(file, "%[^,],%d\n",name, &age);
        if(ret < 0) break;
        //创建一个学生结构体
        struct Student *snode = (struct Student*)malloc(sizeof(struct Student));
        //向结构体写入数据
        creat_node(snode, name,age);
        //把新学生结构体节点插入到头后面
        list_add(&snode->list, &shead->list);
    }
    fclose(file);

    //遍历链表输入学生信息
    //list_for_each_entry(数据结构体指针， 链表结构体指针， 链表结构在数据结构体里面的变量名称)
    struct Student *pos = NULL;
    struct Student *n =NULL;
    list_for_each_entry(pos, &shead->list,list) {
        printf("%s:%d\n", pos->name, pos->age);
    }

    list_for_each_entry_safe(pos,n, &shead->list,list) {
        if(strcmp(pos->name, "王五") == 0) {
            //把pos从链表上脱离
            list_del(&pos->list);
            free(pos);
            break;
        }
        //printf("%s:%d\n", pos->name, pos->age);
    }
    printf("------------------------\n");
    list_for_each_entry_safe(pos,n, &shead->list,list) {
        printf("%s:%d\n", pos->name, pos->age);
    }
}