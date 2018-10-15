#include<stdio.h>
#include<stdlib.h>
// 此处可以添加你自己需要的头文件

struct goodPeopleCard
{
	char name[20];    // 发卡人的名字，应该不会有人的名字超过这个长度吧？
	char date[9];     // 发卡的日期，例如 20180102，应该不会到公元10000年还会有人发卡吧？
};

struct node
{
	struct goodPeopleCard* card;	// 指向一个好人卡结构体
	struct node * prev;				// 指向上一个结点
	struct node * next;				// 指向下一个结点
};

// 函数声明部分开始
struct node* initCardList();
int insertCard(struct node* head, struct node* tail, int index, struct goodPeopleCard* newCard);
int deleteCardByNode(struct node* node);
int deleteCardByName(struct node* head, char* name);
int deleteCardByDate(struct node* head, char* date);
struct node* searchCardByName(struct node* head, char* name);
struct node* searchCardByDate(struct node* head, char* date);
void clear(struct node* head);
struct goodPeopleCard* pop_back();
void push_back(struct goodPeopleCard* newCard);
struct goodPeopleCard* pop_front();
void push_front(struct goodPeopleCard* newCard);
void printCard(struct goodPeopleCard* card);
// 函数声明部分结束

// 请在完成函数实现后完成 main 函数
int main()
{

}


// 请按要求实现以下函数


/*
参数：无

返回值：双向链表的头结点指针

函数执行操作：创建头结点和尾结点

其他说明：
头结点的 prev 指向 NULL，next 指向尾结点
尾结点的 prev 指向头结点，next 指向 NULL
头尾结点的 card 均指向 NULL
*/
struct node* initCardList()
{
	
}

/*
参数：链表头指针 head，链表尾指针 tail，插入位置 index，新好人卡指针 newCard

返回值：0或者1。1代表插入成功，0代表插入失败（index过大或过小）

函数执行操作：把 newCard 指针包装成结点，插入到 index 指定的位置

其他说明：
index 可正可负。为正时从头开始计算，为负时从尾开始计算。例如对于以下链表
head <--> node1 <--> node2 <--> node3 <--> node4 <--> tail
index = 0 代表 node1 的位置， index = 1 代表 node2 的位置， index = -1 代表 node4 的位置，index = -2 代表 node3 的位置
比如我传入 index = 1，上述链表就会变为
head <--> node1 <--> newCardNode <--> node2 <--> node3 <--> node4 <--> tail
*/
int insertCard(struct node* head, struct node* tail, int index, struct goodPeopleCard* newCard)
{
	return 0;
}

/*
参数：被删除结点指针

返回值：0或者1。1代表删除成功，0代表删除失败

函数执行操作：把node结点从所在链表中删除，并释放该结点占用的所有内存

特殊说明：不允许删除预留的头尾结点。如果传入的是头尾结点，则返回0。
*/
int deleteCardByNode(struct node* node)
{
	return 0;
}

/*
参数：链表头指针 head，要删除的名字 name

返回值：0或者1。1代表删除成功，0代表没找到

函数执行操作：把首个具有发卡人姓名为name的node结点从所在链表中删除，并释放该结点占用的所有内存
*/
int deleteCardByName(struct node* head, char* name)
{
	return 0;
}

/*
参数：链表头指针 head，要删除的名字 name

返回值：0或者1。1代表删除成功，0代表没找到

函数执行操作：把首个具有发卡日期为date的node结点从所在链表中删除，并释放该结点占用的所有内存
*/
int deleteCardByDate(struct node* head, char* date)
{
	return 0;
}

/*
参数：链表头指针 head，发卡人的名字name

返回值：该好人卡所在结点的指针

函数执行操作：在链表中查找首个发卡人姓名为name的好人卡结点并返回其指针。如果没有返回 NULL
*/
struct node* searchCardByName(struct node* head, char* name)
{
	return NULL;
}

/*
参数：链表头指针 head，发卡的日期 date

返回值：该好人卡所在结点的指针

函数执行操作：在链表中查找首个发卡时间为date的结点并返回其指针。如果没有返回 NULL
*/
struct node* searchCardByDate(struct node* head, char* date)
{
	return NULL;
}

/*
参数：链表头指针 head

返回值：无

函数执行操作：清空链表，只留下头和尾
*/
void clear(struct node* head)
{

}

/*
参数：链表头指针 head

返回值：无

函数执行操作：删除整个链表，包括预留的头和尾
*/
void destoryCardList(struct node* head)
{

}

/*
参数：无

返回值：指向一个 goodPeopleCard 的指针

函数执行操作：读取链表最后一个结点中的好人卡指针，并从链表中删除这个结点

其他说明：如果链表为空，返回 NULL
*/
struct goodPeopleCard* pop_back()
{
	return NULL;
}

/*
参数：指向一个 goodPeopleCard 的指针 newCard

返回值：无

函数执行操作：把一个新的好人卡指针包装成结点插入链表的最后一个位置
*/
void push_back(struct goodPeopleCard* newCard)
{

}

/*
参数：无

返回值：指向一个 goodPeopleCard 的指针

函数执行操作：读取链表最前一个结点中的好人卡指针，并从链表中删除这个结点

其他说明：如果链表为空，返回 NULL
*/
struct goodPeopleCard* pop_front()
{
	return NULL;
}

/*
参数：指向一个 goodPeopleCard 的指针 newCard

返回值：无

函数执行操作：把一个新的好人卡指针包装成结点插入链表的第一个位置
*/
void push_front(struct goodPeopleCard * newCard)
{

}

/*
参数：指向一个 goodPeopleCard 的指针 card

返回值：无

函数执行操作：输出该好人卡中的信息
*/
void printCard(struct goodPeopleCard* card)
{
	printf("发卡人：%s\t发卡日期：%s\n", card->name, card->date);
}