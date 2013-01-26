/*
Description：在没有显式的指针数据类型时实现双向链表数据结构
Date：2012/10/7
Author：Roger Liu 
*/ 

#include <stdio.h> 

#define space 10
#define nill -1//用-1代表空指针 
 
typedef int elementType;
typedef int listType; 

listType allocate_object();
void free_object(listType);//为链表结点分配空间以及释放结点 

listType list_search(elementType);
void list_insert(listType);
void list_delete(listType); //链表基本操作：搜索元素，插入元素以及删除元素 

listType next[space];
elementType key[space];
listType prev[space];//三个数组分别存储 
listType L = nill;//L存储链表的头结点指针 ，初始-1表示链表为空 
listType free = 0;//free存储空余未分配空间（即自由表）的头指针，初始值为数组空间首地址，0 

int main()
{
    int i;
    int a[5] = {1,2,3,4,5}; 
    listType x, iterate;
    //建立自由表，初始链表为空 
    
    for (i = 0; i < space-1; i++)
    {
        next[i] = i + 1;
    }    
    next[space-1] = nill;//自由表表尾 
    
    //根据数组a的元素值建立链表 
    L = allocate_object();//分配一个结点，并让L指向它
    key[L] = a[0];
    prev[L] = next[L] = nill;
    iterate = L;
     
    for (i = 1; i < 5; i++)
    {
        x = allocate_object();//分配一个结点
        if(x != nill){
            key[x] = a[i]; 
            next[iterate] = x;
            prev[x] = iterate;
            next[x] = nill; 
            
            iterate = next[iterate];
        }
    }
    
    printf("\nprint the elements of the list:\n");
    iterate = L; 
    printf("%d", key[iterate]);
    iterate = next[iterate];
    while(iterate != nill){
        printf("-->%d",key[iterate]);
        iterate = next[iterate];
    }
    
    x = allocate_object();
    key[x] = 0;
    list_insert(x);//表头插入元素0
    x = list_search(4);
    list_delete(x); 
    
    printf("\n\nafter basic list operation, print the elements of the list(supposed to be 0,1,2,3,5)\n");
    iterate = L; 
    printf("%d", key[iterate]);
    iterate = next[iterate];
    while(iterate != nill){
        printf("-->%d",key[iterate]);
        iterate = next[iterate];
    }
    
    system("pause");
    return 0; 
}


listType allocate_object()
{
    listType x;
    
    if (free == nill){
        printf("\n***out of space***\n");//溢出 
        x = -1;
    }else{
        x = free;
        free = next[free];//这里自由表采用栈操作来分配和释放结点     
    }
    
    return x;
} 

void free_object(listType x)
{
    next[x] = free;
    free = x;
}

listType list_search(elementType x)
{
    listType iterate;
    
    iterate = L;
    while (iterate != nill && key[iterate] != x)
    {
        iterate = next[iterate];
    }
    
    return iterate;
}

void list_insert(listType x)
{
    next[x] = L;
    prev[x] = nill;
    L = x;
}

void list_delete(listType x)
{
    if (prev[x] != nill)
        next[prev[x]] = next[x];
    else
        L = next[x];//删表头元素不要忘了头指针移动 
    if (next[x] != nill)
        prev[next[x]] = prev[x];
        
    free_object(x);//把x加入自由表表头等待下次分配 
}
















