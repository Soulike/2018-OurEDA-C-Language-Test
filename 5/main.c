#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<Windows.h>
// �˴�����������Լ���Ҫ��ͷ�ļ�

struct goodPeopleCard
{
	char name[20];    // �����˵����֣�Ӧ�ò������˵����ֳ���������Ȱɣ�
	char date[9];     // ���������ڣ����� 20180102��Ӧ�ò��ᵽ��Ԫ10000�껹�����˷����ɣ�
};

struct node
{
	struct goodPeopleCard* card;	// ָ��һ�����˿��ṹ��
	struct node * prev;				// ָ����һ�����
	struct node * next;				// ָ����һ�����
};

// �����������ֿ�ʼ
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
// �����������ֽ���

typedef struct node node;
typedef node* nodePtr;

typedef struct goodPeopleCard goodPeopleCard;
typedef goodPeopleCard* goodPeopleCardPtr;

/*
main �������й�������
1. ����ʱ��㽻����ͷβλ�÷�����������ͷ����->��β����->��ͷ����->��β����->������
2. ����һ�����֣�������ΪĿ��ɾ������һ����㣻
3. ����һ�����ڣ�������ΪĿ��ɾ������һ����㣻
4. ���ʱ������ͷβλ��������������һ��->������һ��->�����һ��->������һ��->������Ҫ�������ɺ�����ֻʣ�²��������ݵ�ͷβ��㣻
5. �ڳ����˳�֮ǰ�����������ݵ�ͷβ���Ҳ��ɾ����
*/

int main()
{
	int inputNum = 0;
	scanf("%d", &inputNum);

	nodePtr head = initCardList();
	nodePtr tail = head->next; // ��� tail ��Ψһ�취������������ɺ�head�ĺ������tail

	goodPeopleCardPtr card = NULL;

	for (int i = 0; i < inputNum; i++)
	{
		card = (goodPeopleCardPtr)malloc(sizeof(goodPeopleCard));
		scanf("%s %s", &card->name, &card->date);
		if (i % 2 == 0) // ż������ͷ
		{
			push_front(head, card);
		}
		else // ��������β
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
		if (i % 2 == 0)// ż���������һ��
		{
			card = pop_front(head);
		}
		else// ������������һ��
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
			free(card); // ��ӣ������ card ������������һ���ͷţ���˱����ֶ��ͷ�
		}
	}

	destoryCardList(head);

	system("pause");
}


// �밴Ҫ��ʵ�����º���


/*
��������

����ֵ��˫�������ͷ���ָ��

����ִ�в���������ͷ����β���

����˵����
ͷ���� prev ָ�� NULL��next ָ��β���
β���� prev ָ��ͷ��㣬next ָ�� NULL
ͷβ���� card ��ָ�� NULL
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
����������ͷ��� head������β��� tail������ȡ���λ�� index

����ֵ�������ҵĽ��ָ�룬����Ҳ������� NULL

����ִ�в��������Ҳ����� index λ��ָ���Ľ��ָ��

����˵����
index �����ɸ���Ϊ��ʱ��ͷ��ʼ���㣬Ϊ��ʱ��β��ʼ���㡣���������������
head <--> node1 <--> node2 <--> node3 <--> node4 <--> tail
index = 0 ���� node1 ��λ�ã� index = 1 ���� node2 ��λ�ã� index = -1 ���� node4 ��λ�ã�index = -2 ���� node3 ��λ��
*/
struct node* getNode(struct node * head, struct node * tail, int index)
{
	nodePtr currentNode = NULL;
	if (head != NULL && index >= 0) // index ���������ʹ�ͷ��ʼ��
	{
		currentNode = head;
		for (int i = 0; i <= index; i++)
		{
			currentNode = currentNode->next;
			if (currentNode->next == NULL) // ����ҵ��� tail���ͷ��� NULL
			{
				return NULL;
			}
		}
	}
	else if (tail != NULL && index < 0) // index �Ǹ������ʹ�β��ʼ��
	{
		index = -index;
		currentNode = tail;
		for (int i = 0; i < index; i++)
		{
			currentNode = currentNode->prev;
			if (currentNode->prev == NULL) // ����ҵ��� head���ͷ��� NULL
			{
				return NULL;
			}
		}
	}
	else // ���Ŵ���û���ң��ͷ���ʧ��
	{
		return NULL;
	}

	return currentNode;
}

/*
����������ͷָ�� head������βָ�� tail������λ�� index���º��˿�ָ�� newCard

����ֵ��0����1��1�������ɹ���0�������ʧ�ܣ�index������С���޷�ʵ�ֶ�λ)

����ִ�в������� newCard ָ���װ�ɽ�㣬���뵽 index ָ����λ��

����˵����
index �����ɸ���Ϊ��ʱ��ͷ��ʼ���㣬Ϊ��ʱ��β��ʼ���㡣���������������
head <--> node1 <--> node2 <--> node3 <--> node4 <--> tail
index = 0 ���� node1 ��λ�ã� index = 1 ���� node2 ��λ�ã� index = -1 ���� node4 ��λ�ã�index = -2 ���� node3 ��λ��
�����Ҵ��� index = 1����������ͻ��Ϊ
head <--> node1 <--> newCardNode <--> node2 <--> node3 <--> node4 <--> tail
*/
int insertCard(struct node* head, struct node* tail, int index, struct goodPeopleCard* newCard)
{
	// ����ط����ܸ��� getNode����Ϊ���ڲ��뵽0����-1λ�õ����
	nodePtr currentNode = NULL;

	if (head != NULL && index >= 0)
	{
		currentNode = head;
		for (int i = 0; i <= index; i++)
		{
			currentNode = currentNode->next;
			if (currentNode == NULL) // һֱ�ҵ�β���֮���ˣ��ͷ�������
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
			if (currentNode == NULL) // һֱ�ҵ�ͷ���֮ǰ�ˣ��ͷ�������
				break;
		}
	}

	if (currentNode != NULL)
	{
		// ʵ�ʵĲ������
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
��������ɾ�����ָ��

����ֵ��0����1��1����ɾ���ɹ���0����ɾ��ʧ��

����ִ�в�������node��������������ɾ�������ͷŸý��ռ�õ������ڴ�

����˵����������ɾ��Ԥ����ͷβ��㡣����������ͷβ��㣬�򷵻�0��
*/
int deleteCardByNode(struct node* node)
{
	if (node->prev == NULL || node->next == NULL) // ֻ��ͷβ�ڵ�Ż���� prev �� next Ϊ NULL
	{
		return 0;
	}
	else
	{
		// ������Ҫ����������ԭ��ɾ������
		nodePtr prevNode = node->prev;
		nodePtr nextNode = node->next;

		prevNode->next = nextNode;
		nextNode->prev = prevNode;

		// ע��ÿ���������ĺ��˿�ָ��Ҳ����Ҫ�ͷŵ�
		free(node->card);
		free(node);
		return 1;
	}
}

/*
����������ͷָ�� head�������˵�����name

����ֵ���ú��˿����ڽ���ָ��

����ִ�в������������в����׸�����������Ϊname�ĺ��˿���㲢������ָ�롣���û�з��� NULL
*/
struct node* searchCardByName(struct node* head, char* name)
{
	nodePtr currentNode = head; 
	while (currentNode->card == NULL || strcmp(name, currentNode->card->name) != 0) // �� strcmp ��һ�� NULL �ǲ�ȷ����Ϊ��������
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
����������ͷָ�� head������������ date

����ֵ���ú��˿����ڽ���ָ��

����ִ�в������������в����׸�����ʱ��Ϊdate�Ľ�㲢������ָ�롣���û�з��� NULL
*/
struct node* searchCardByDate(struct node* head, char* date)
{
	nodePtr currentNode = head;
	while (currentNode->card == NULL || strcmp(date, currentNode->card->date) != 0) // �� strcmp ��һ�� NULL �ǲ�ȷ����Ϊ��������
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
����������ͷָ�� head��Ҫɾ�������� name

����ֵ��0����1��1����ɾ���ɹ���0����û�ҵ�

����ִ�в��������׸����з���������Ϊname��node��������������ɾ�������ͷŸý��ռ�õ������ڴ�
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
����������ͷָ�� head��Ҫɾ�������� name

����ֵ��0����1��1����ɾ���ɹ���0����û�ҵ�

����ִ�в��������׸����з�������Ϊdate��node��������������ɾ�������ͷŸý��ռ�õ������ڴ�
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
����������ͷָ�� head

����ֵ����

����ִ�в������������ֻ���²��������ݵ�ͷ��β
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
	// ѭ������֮��currentNode ָ��ľ��� tail���������������
	head->next = currentNode;
	currentNode->prev = head;
}

/*
����������ͷָ�� head

����ֵ����

����ִ�в�����ɾ��������������Ԥ����ͷ��β
*/
void destoryCardList(struct node* head)
{
	clear(head);
	free(head->next);
	free(head);
}

/*
��������

����ֵ��ָ��һ�� goodPeopleCard ��ָ��

����ִ�в�������ȡ�������һ������еĺ��˿�ָ�룬����������ɾ��������

����˵�����������Ϊ�գ����� NULL
*/
struct goodPeopleCard* pop_back(struct node * tail)
{
	nodePtr node = getNode(NULL, tail, -1);
	if (node == NULL)
	{
		return NULL;
	}
	goodPeopleCardPtr card = node->card;

	// ��ӣ�����������������ɾ�������ͻ���������ֶ��Ƴ�����Ϊ���ǻ���Ҫ�ڴ��е� card ��������������������ͷ� card ����û˵
	nodePtr prevNode = node->prev;
	nodePtr nextNode = node->next;

	prevNode->next = nextNode;
	nextNode->prev = prevNode;

	free(node);

	return card;
}

/*
������ָ��һ�� goodPeopleCard ��ָ�� newCard

����ֵ����

����ִ�в�������һ���µĺ��˿�ָ���װ�ɽ�������������һ��λ��
*/
void push_back(struct node * tail, struct goodPeopleCard* newCard)
{
	insertCard(NULL, tail, -1, newCard);
}

/*
��������

����ֵ��ָ��һ�� goodPeopleCard ��ָ��

����ִ�в�������ȡ������ǰһ������еĺ��˿�ָ�룬����������ɾ��������

����˵�����������Ϊ�գ����� NULL
*/
struct goodPeopleCard* pop_front(struct node * head)
{
	nodePtr node = getNode(head, NULL, 0);

	if (node == NULL)
	{
		return NULL;
	}

	goodPeopleCardPtr card = node->card;

	// ��ӣ�����������������ɾ�������ͻ���������ֶ��Ƴ�����Ϊ���ǻ���Ҫ�ڴ��е� card ��������������������ͷ� card ����û˵
	nodePtr prevNode = node->prev;
	nodePtr nextNode = node->next;

	prevNode->next = nextNode;
	nextNode->prev = prevNode;

	free(node);

	return card;
}

/*
������ָ��һ�� goodPeopleCard ��ָ�� newCard

����ֵ����

����ִ�в�������һ���µĺ��˿�ָ���װ�ɽ���������ĵ�һ��λ��
*/
void push_front(struct node * head, struct goodPeopleCard * newCard)
{
	insertCard(head, NULL, 0, newCard);
}

/*
������ָ��һ�� goodPeopleCard ��ָ�� card

����ֵ����

����ִ�в���������ú��˿��е���Ϣ
*/
void printCard(struct goodPeopleCard* card)
{
	printf("�����ˣ�%s\t�������ڣ�%s\n", card->name, card->date);
}