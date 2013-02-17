typedef int QElemtype;
typedef struct QNode
{
	QElemtype data;
	struct QNode *next;
}QNode;

typedef struct LinkQueue
{
	QNode *front;
	QNode *rear;
	size_t LQNum;
	bool IsEmpty();
}LinkQueue;

bool InitQueue(LinkQueue &Q)
{
	Q.front = Q.rear = (QNode *)malloc(sizeof(QNode));
	if (Q.front == NULL) return 1;
	Q.rear->next = NULL;
	return 0;
}

bool ClearQueue(LinkQueue &Q)
{
	while(Q.front != Q.rear)
	{
		QNode *temp = Q.front;
		Q.front = Q.front->next;
		free(temp);
	}
	return 0;
}

bool LinkQueue::IsEmpty()
{
	if (front == NULL) return TRUE;
	else return FALSE;
}

bool EnQueue(LinkQueue &Q,const QElemtype &val)
{
	if (Q.front == NULL)	//队列为空
	{
		Q.front = Q.rear = (QNode *)malloc(sizeof(QNode));
		if (Q.front == NULL) return 1;
		Q.rear->next = NULL;
	}
	else
	{
		Q.rear->next = (QNode *)malloc(sizeof(QNode));
		if (Q.rear->next == NULL) return 1;
		Q.rear = Q.rear->next;
	}
	++Q.LQNum;
	Q.rear->data = val;
	Q.rear->next = NULL;
	return 0;
}

bool DeQueue(LinkQueue &Q,QElemtype &val)
{
	if (Q.front == NULL) return 1;
	if (Q.front != Q.rear)
	{
		QNode *temp = Q.front;
		val = Q.front->data;
		Q.front = Q.front->next;
		free(temp);
	}
	else if (Q.front)	//队列中只有一个元素
	{
		val = Q.front->data;
		free(Q.rear);
		Q.front = Q.rear = NULL;
	}
	--Q.LQNum;
	return 0;
}