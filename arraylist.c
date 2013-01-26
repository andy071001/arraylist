/*
Description����û����ʽ��ָ����������ʱʵ��˫���������ݽṹ
Date��2012/10/7
Author��Roger Liu 
*/ 

#include <stdio.h> 

#define space 10
#define nill -1//��-1�����ָ�� 
 
typedef int elementType;
typedef int listType; 

listType allocate_object();
void free_object(listType);//Ϊ���������ռ��Լ��ͷŽ�� 

listType list_search(elementType);
void list_insert(listType);
void list_delete(listType); //�����������������Ԫ�أ�����Ԫ���Լ�ɾ��Ԫ�� 

listType next[space];
elementType key[space];
listType prev[space];//��������ֱ�洢 
listType L = nill;//L�洢�����ͷ���ָ�� ����ʼ-1��ʾ����Ϊ�� 
listType free = 0;//free�洢����δ����ռ䣨�����ɱ���ͷָ�룬��ʼֵΪ����ռ��׵�ַ��0 

int main()
{
    int i;
    int a[5] = {1,2,3,4,5}; 
    listType x, iterate;
    //�������ɱ���ʼ����Ϊ�� 
    
    for (i = 0; i < space-1; i++)
    {
        next[i] = i + 1;
    }    
    next[space-1] = nill;//���ɱ��β 
    
    //��������a��Ԫ��ֵ�������� 
    L = allocate_object();//����һ����㣬����Lָ����
    key[L] = a[0];
    prev[L] = next[L] = nill;
    iterate = L;
     
    for (i = 1; i < 5; i++)
    {
        x = allocate_object();//����һ�����
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
    list_insert(x);//��ͷ����Ԫ��0
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
        printf("\n***out of space***\n");//��� 
        x = -1;
    }else{
        x = free;
        free = next[free];//�������ɱ����ջ������������ͷŽ��     
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
        L = next[x];//ɾ��ͷԪ�ز�Ҫ����ͷָ���ƶ� 
    if (next[x] != nill)
        prev[next[x]] = prev[x];
        
    free_object(x);//��x�������ɱ��ͷ�ȴ��´η��� 
}
















