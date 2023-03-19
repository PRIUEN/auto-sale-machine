#include "project.h"




//双向链表的初始化
struct doublelist *list_init()
{
	struct doublelist *head=malloc(sizeof(struct doublelist));
	head->next=NULL;
	head->prev=NULL;
	return head;
}

//尾插
int list_insert_tail(struct doublelist *head,char *name,float price,int amount)
{
	struct doublelist *p=head;
	while(p->next!=NULL)
		p=p->next;
	
	//准备一个新的节点
	struct doublelist *newnode=malloc(sizeof(struct doublelist));
	strcpy(newnode->com_name,name);
    newnode->com_price = price;
    newnode->com_amount = amount;
	newnode->next=NULL;
	newnode->prev=NULL;
	
	//尾插新的节点
	p->next=newnode;
	newnode->prev=p;
	return 0;
}

//中间插入
/* int list_insert_mid(struct doublelist *head,int somedata,int newdata)
{
	//第一步：定义指针p找到somedata所代表的那个节点
	struct doublelist *p=head;
	while(p->next!=NULL)
	{
		p=p->next;
		if(p->data==somedata) //找到了
			break;
	}
	
	//准备新的节点
	struct doublelist *newnode=malloc(sizeof(struct doublelist));
	newnode->data=newdata;
	newnode->next=NULL;
	newnode->prev=NULL;
	
	//第二步：依据我们画的图来写指针的指向关系
	newnode->next=p->next;
	p->next=newnode;
	newnode->next->prev=newnode;
	newnode->prev=p;
	return 0;
} */

//删除节点
int list_delete(struct doublelist *head,char *name)
{
	//第一步：找到要删除的节点
	struct doublelist *p=head;
	while(p->next!=NULL)
	{
		p=p->next;
		//经过分析：最后一个节点删除的写法跟前面节点删除的写法有所不同
		//最后一个节点单独判断一下即可
		if(p->next==NULL) //此时p就是最后一个节点
		{
			if(strcmp(p->com_name,name) == 0)
			{
				p->prev->next=NULL;
				p->prev=NULL;
				free(p);
				break;
			}			
		}
		else //此时p就是前面的节点
		{
			if(strcmp(p->com_name,name) == 0)
			{
				p->prev->next=p->next;
				p->next->prev=p->prev;
				struct doublelist *temp=p->next;
				p->next=NULL;
				p->prev=NULL;
				free(p);  //此时p是个野指针
				//p继续往后遍历，看看后面还有没有要删除的节点
				p=temp->prev; //p重生了
            }
		}
		
	}
	return 0;
}

int list_show(struct doublelist *head)
{
	struct doublelist *p=head;
	while(p->next!=NULL)
	{
		p=p->next;
		printf("名称：%s  价格：￥%.1f  数量：%d \n",p->com_name,p->com_price,p->com_amount);
	}
	return 0;
}

//销毁链表
int free_list(struct doublelist *p)
{	
	
    struct doublelist *s;
    while(p != NULL)
    {
        s = p;
        p = p->next;
        s->next = NULL;
        s->prev = NULL;
        free(s);
    }
    if(p == NULL)
        printf("链表已销毁！\n");
    return 0;
}

//清空链表，保留头节点
int clear_list(struct doublelist *list)
{
	struct doublelist *pos = list->next;
	struct doublelist *s;
    while(pos != NULL)
    {
        s = pos;
        pos = pos->next;
        s->next = NULL;
        s->prev = NULL;
        free(s);
    }
	list->next = NULL;
	if(pos == NULL)
        printf("链表已清空！\n");
    return 0;
}