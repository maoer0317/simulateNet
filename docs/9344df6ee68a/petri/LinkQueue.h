#ifndef _LinkQueue_H
#define _LinkQueue_H

struct tag_select_finish
{
	int time;
	int num;
};
struct tag_place
{
	int select;
	int queue;
	int bargin_zone;
	int leave;
	int rest;
};
struct tag_event
{
	int arrive_time;
	int select_time;
	int finish_time;
};
struct tag_client
{
	unsigned int sn;
	int arrive_time;
	int select_time;
	int select_finish;
	int bargin_begin;
	int service_time;
};
struct LNode{
	tag_client data;
    LNode *next;
};

class CLinkQueue
{//method
public:
	void InitQueue();
	void ClearQueue();
	BOOL QueueEmpty();
	tag_client QFront();
	void QInsert(const tag_client& item);
	int QDelete();

public:
	LNode* front;
	LNode* rear;
};



#endif