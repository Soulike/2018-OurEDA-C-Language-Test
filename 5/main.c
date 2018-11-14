#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<Windows.h>
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
struct node* getNode(struct node * head, struct node * tail, int index);
int insertCard(struct node* head, struct node* tail, int index, struct goodPeopleCard* newCard);
int deleteCardByNode(struct node* node);
int deleteCardByName(struct node* head, char* name);
int deleteCardByDate(struct node* head, char* date);
struct node* searchCardByName(struct node* head, char* name);
struct node* searchCardByDate(struct node* head, char* date);
void clear(struct node* head);
void destoryCardList(struct node* head);
struct goodPeopleCard* pop_back(struct node * tail);
void push_back(struct node * tail, struct goodPeopleCard* newCard);
struct goodPeopleCard* pop_front(struct node * head);
void push_front(struct node * head, struct goodPeopleCard* newCard);
void printCard(struct goodPeopleCard* card);
// 函数声明部分结束

typedef struct node node;
typedef node* nodePtr;

typedef struct goodPeopleCard goodPeopleCard;
typedef goodPeopleCard* goodPeopleCardPtr;

/*
main 函数运行过程如下
1. 输入时结点交替在头尾位置放入链表（即在头插入->在尾插入->在头插入->在尾插入->…）；
2. 输入一个名字，用名字为目标删除其中一个结点；
3. 输入一个日期，用日期为目标删除其中一个结点；
4. 输出时交替在头尾位置输出（即输出第一个->输出最后一个->输出第一个->输出最后一个->…），要求输出完成后链表只剩下不承载数据的头尾结点；
5. 在程序退出之前，不承载数据的头尾结点也被删除。
*/

int main()
{
	int inputNum = 0;
	scanf("%d", &inputNum);

	nodePtr head = initCardList();
	nodePtr tail = head->next; // 获得 tail 的唯一办法。在链表构造完成后head的后面就是tail

	goodPeopleCardPtr card = NULL;

	for (int i = 0; i < inputNum; i++)
	{
		card = (goodPeopleCardPtr)malloc(sizeof(goodPeopleCard));
		scanf("%s %s", &card->name, &card->date);
		if (i % 2 == 0) // 偶数放在头
		{
			push_front(head, card);
		}
		else // 奇数放在尾
		{
			push_back(tail, card);
		}
	}

	char name[20]; 
	char date[9];

	scanf("%s", name);

	deleteCardByName(head, name);

	scanf("%s", date);

	deleteCardByDate(head, date);

	for (int i = 0;; i++)
	{
		if (i % 2 == 0)// 偶数，输出第一个
		{
			card = pop_front(head);
		}
		else// 奇数，输出最后一个
		{
			card = pop_back(tail);
		}

		if (card == NULL)
		{
			break;
		}
		else
		{
			printCard(card);
			free(card); // 大坑，这里的 card 不能随着链表一起释放，因此必须手动释放
		}
	}

	destoryCardList(head);

	system("pause");
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
	nodePtr head = (nodePtr)malloc(sizeof(node));
	nodePtr tail = (nodePtr)malloc(sizeof(node));
	head->card = NULL;
	tail->card = NULL;
	head->prev = NULL;
	head->next = tail;
	tail->prev = head;
	tail->next = NULL;
	return head;
}

/*
参数：链表头结点 head，链表尾结点 tail，被获取结点位置 index

返回值：被查找的结点指针，如果找不到返回 NULL

函数执行操作：查找并返回 index 位置指定的结点指针

其他说明：
index 可正可负。为正时从头开始计算，为负时从尾开始计算。例如对于以下链表
head <--> node1 <--> node2 <--> node3 <--> node4 <--> tail
index = 0 代表 node1 的位置， index = 1 代表 node2 的位置， index = -1 代表 node4 的位置，index = -2 代表 node3 的位置
*/
struct node* getNode(struct node * head, struct node * tail, int index)
{
	nodePtr currentNode = NULL;
	if (head != NULL && index >= 0) // index 是正数，就从头开始找
	{
		currentNode = head;
		for (int i = 0; i <= index; i++)
		{
			currentNode = currentNode->next;
			if (currentNode->next == NULL) // 如果找到了 tail，就返回 NULL
			{
				return NULL;
			}
		}
	}
	else if (tail != NULL && index < 0) // index 是负数，就从尾开始找
	{
		index = -index;
		currentNode = tail;
		for (int i = 0; i < index; i++)
		{
			currentNode = currentNode->prev;
			if (currentNode->prev == NULL) // 如果找到了 head，就返回 NULL
			{
				return NULL;
			}
		}
	}
	else // 混着搭配没法找，就返回失败
	{
		return NULL;
	}

	return currentNode;
}

/*
参数：链表头指针 head，链表尾指针 tail，插入位置 index，新好人卡指针 newCard

返回值：0或者1。1代表插入成功，0代表插入失败（index过大或过小或无法实现定位)

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
	// 这个地方不能复用 getNode。因为存在插入到0或者-1位置的情况
	nodePtr currentNode = NULL;

	if (head != NULL && index >= 0)
	{
		currentNode = head;
		for (int i = 0; i <= index; i++)
		{
			currentNode = currentNode->next;
			if (currentNode == NULL) // 一直找到尾结点之后了，就放弃插入
				break;
		}
	}
	else if(tail != NULL && index < 0)
	{
		currentNode = tail;
		index = -index;
		for (int i = 0; i < index - 1; i++)
		{
			currentNode = currentNode->prev;
			if (currentNode == NULL) // 一直找到头结点之前了，就放弃插入
				break;
		}
	}

	if (currentNode != NULL)
	{
		// 实际的插入操作
		nodePtr newNode = (nodePtr)malloc(sizeof(node));
		newNode->card = newCard;

		nodePtr prevNode = currentNode->prev;
		nodePtr nextNode = currentNode;

		prevNode->next = newNode;
		nextNode->prev = newNode;

		newNode->prev = prevNode;
		newNode->next = nextNode;

		return 1;
	}
	else
	{
		return 0;
	}
}

/*
参数：被删除结点指针

返回值：0或者1。1代表删除成功，0代表删除失败

函数执行操作：把node结点从所在链表中删除，并释放该结点占用的所有内存

特殊说明：不允许删除预留的头尾结点。如果传入的是头尾结点，则返回0。
*/
int deleteCardByNode(struct node* node)
{
	if (node->prev == NULL || node->next == NULL) // 只有头尾节点才会出现 prev 或 next 为 NULL
	{
		return 0;
	}
	else
	{
		// 并不需要进行搜索，原地删除即可
		nodePtr prevNode = node->prev;
		nodePtr nextNode = node->next;

		prevNode->next = nextNode;
		nextNode->prev = prevNode;

		// 注意每个结点里面的好人卡指针也是需要释放的
		free(node->card);
		free(node);
		return 1;
	}
}

/*
参数：链表头指针 head，发卡人的名字name

返回值：该好人卡所在结点的指针

函数执行操作：在链表中查找首个发卡人姓名为name的好人卡结点并返回其指针。如果没有返回 NULL
*/
struct node* searchCardByName(struct node* head, char* name)
{
	nodePtr currentNode = head; 
	while (currentNode->card == NULL || strcmp(name, currentNode->card->name) != 0) // 给 strcmp 传一个 NULL 是不确定行为，不作死
	{
		currentNode = currentNode->next;
		if (currentNode == NULL)
			break;
	}

	if (currentNode == head || currentNode == NULL)
	{
		return NULL;
	}
	else
	{
		return currentNode;
	}
}

/*
参数：链表头指针 head，发卡的日期 date

返回值：该好人卡所在结点的指针

函数执行操作：在链表中查找首个发卡时间为date的结点并返回其指针。如果没有返回 NULL
*/
struct node* searchCardByDate(struct node* head, char* date)
{
	nodePtr currentNode = head;
	while (currentNode->card == NULL || strcmp(date, currentNode->card->date) != 0) // 给 strcmp 传一个 NULL 是不确定行为，不作死
	{
		currentNode = currentNode->next;
		if (currentNode == NULL)
			break;
	}

	if (currentNode == head || currentNode == NULL)
	{
		return NULL;
	}
	else
	{
		return currentNode;
	}
}

/*
参数：链表头指针 head，要删除的名字 name

返回值：0或者1。1代表删除成功，0代表没找到

函数执行操作：把首个具有发卡人姓名为name的node结点从所在链表中删除，并释放该结点占用的所有内存
*/
int deleteCardByName(struct node* head, char* name)
{
	nodePtr node = searchCardByName(head, name);
	if (node == NULL)
	{
		return 0;
	}
	else
	{
		return deleteCardByNode(node);
	}
}

/*
参数：链表头指针 head，要删除的名字 name

返回值：0或者1。1代表删除成功，0代表没找到

函数执行操作：把首个具有发卡日期为date的node结点从所在链表中删除，并释放该结点占用的所有内存
*/
int deleteCardByDate(struct node* head, char* date)
{
	nodePtr node = searchCardByDate(head, date);
	if (node == NULL)
	{
		return 0;
	}
	else
	{
		return deleteCardByNode(node);
	}
}

/*
参数：链表头指针 head

返回值：无

函数执行操作：清空链表，只留下不承载数据的头和尾
*/
void clear(struct node* head)
{
	nodePtr currentNode = head->next;
	nodePtr nextNode = currentNode->next;
	while (nextNode != NULL)
	{
		free(currentNode->card);
		free(currentNode);
		currentNode = nextNode;
		nextNode = nextNode->next;
	}
	// 循环出来之后，currentNode 指向的就是 tail，因此重新连起来
	head->next = currentNode;
	currentNode->prev = head;
}

/*
参数：链表头指针 head

返回值：无

函数执行操作：删除整个链表，包括预留的头和尾
*/
void destoryCardList(struct node* head)
{
	clear(head);
	free(head->next);
	free(head);
}

/*
参数：无

返回值：指向一个 goodPeopleCard 的指针

函数执行操作：读取链表最后一个结点中的好人卡指针，并从链表中删除这个结点

其他说明：如果链表为空，返回 NULL
*/
struct goodPeopleCard* pop_back(struct node * tail)
{
	nodePtr node = getNode(NULL, tail, -1);
	if (node == NULL)
	{
		return NULL;
	}
	goodPeopleCardPtr card = node->card;

	// 大坑，这里如果调用上面的删除函数就会出错，必须手动移除，因为我们还需要内存中的 card 对象。如果你在上面忘了释放 card 当我没说
	nodePtr prevNode = node->prev;
	nodePtr nextNode = node->next;

	prevNode->next = nextNode;
	nextNode->prev = prevNode;

	free(node);

	return card;
}

/*
参数：指向一个 goodPeopleCard 的指针 newCard

返回值：无

函数执行操作：把一个新的好人卡指针包装成结点插入链表的最后一个位置
*/
void push_back(struct node * tail, struct goodPeopleCard* newCard)
{
	insertCard(NULL, tail, -1, newCard);
}

/*
参数：无

返回值：指向一个 goodPeopleCard 的指针

函数执行操作：读取链表最前一个结点中的好人卡指针，并从链表中删除这个结点

其他说明：如果链表为空，返回 NULL
*/
struct goodPeopleCard* pop_front(struct node * head)
{
	nodePtr node = getNode(head, NULL, 0);

	if (node == NULL)
	{
		return NULL;
	}

	goodPeopleCardPtr card = node->card;

	// 大坑，这里如果调用上面的删除函数就会出错，必须手动移除，因为我们还需要内存中的 card 对象。如果你在上面忘了释放 card 当我没说
	nodePtr prevNode = node->prev;
	nodePtr nextNode = node->next;

	prevNode->next = nextNode;
	nextNode->prev = prevNode;

	free(node);

	return card;
}

/*
参数：指向一个 goodPeopleCard 的指针 newCard

返回值：无

函数执行操作：把一个新的好人卡指针包装成结点插入链表的第一个位置
*/
void push_front(struct node * head, struct goodPeopleCard * newCard)
{
	insertCard(head, NULL, 0, newCard);
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