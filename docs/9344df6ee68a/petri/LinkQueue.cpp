#include "stdAfx.h"
#include "LinkQueue.h"

void CLinkQueue::InitQueue()
{
	front=NULL;
	rear=NULL;
}
void CLinkQueue::ClearQueue()
{
	LNode* p=front;
	while(p!=NULL)
	{
		front=front->next;
		delete p;
		p=front;
	}
	rear=NULL;
}
BOOL CLinkQueue::QueueEmpty()
{
	return front==NULL;
}
tag_client CLinkQueue::QFront()
{
	if(front==NULL)
		exit(1);
	return front->data;
}
void CLinkQueue::QInsert(const tag_client& item)
{
	LNode* newptr=new LNode;
	if(newptr==NULL)
		exit(1);
	newptr->data=item;
	newptr->next=NULL;
	if(rear==NULL)
	{
		front=rear=newptr;
	}
	else
	{
		rear->next=newptr;
		rear=newptr;
	}
}
int CLinkQueue::QDelete()
{
	if(front==NULL)
	{
		MessageBox(NULL,"queue is empty","error",1);
		exit(1);
	}
	tag_client temp=front->data;
	LNode* p=front;
	front=p->next;
	if(front==NULL)
		rear=NULL;
	delete p;
	return temp.sn;
}