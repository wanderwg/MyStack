typedef int QDataType;
typedef struct QNode
{
	struct QNode* _pNext;
	QDataType _data;
}QNode;

typedef struct Queue
{
	QNode* _front;
	QNode* _back;
}Queue;

void QueueInit(Queue* q) {
	assert(q);
	q->_back = q->_front = NULL;
}

QNode* BuyQueueNode(QDataType data) {
	QNode* pNewNode = (QNode*)malloc(sizeof(QNode));
	if (pNewNode == NULL) {
		assert(0);
		return NULL;
	}
	pNewNode->_data = data;
	pNewNode->_pNext = NULL;
	return pNewNode;
}

void QueuePush(Queue* q, QDataType data) {
	assert(q);
	QNode* pNewNode = BuyQueueNode(data);
	if (QueueEmpty(q))
		q->_back = q->_front = pNewNode;
	else {
		q->_back->_pNext = pNewNode;
		q->_back = pNewNode;
	}
}

void QueuePop(Queue* q) {
	assert(q);
	if (QueueEmpty(q))
		return;
	QNode* pDelNode = q->_front;
	if (pDelNode->_pNext == NULL)
		q->_back = q->_front = NULL;
	else {
		q->_front = pDelNode->_pNext;
	}
	free(pDelNode);
}

QDataType QueueFront(Queue* q) {
	assert(q);
	return q->_front->_data;
}
QDataType QueueBack(Queue* q) {
	assert(q);
	return q->_back->_data;
}
int QueueSize(Queue* q) {
	assert(q);
	int count = 0;
	QNode* pCur = q->_front;
	while (pCur) {
		count++;
		pCur = pCur->_pNext;
	}
	return count;
}
int QueueEmpty(Queue* q) {
	assert(q);
	return q->_front == NULL;
}
void QueueDestory(Queue* q) {
	assert(q);
	QNode* pCur = q->_front;
	while (pCur) {
		q->_front = pCur->_pNext;
		free(pCur);
		pCur = q->_front;
	}
	q->_front = q->_back = NULL;
}

typedef struct {
	Queue _q1;
	Queue _q2;
} MyStack;

/** Initialize your data structure here. */

MyStack* myStackCreate() {
	MyStack* pms = (MyStack*)malloc(sizeof(MyStack));
	if (pms == NULL) {
		assert(0);
		return;
	}
	QueueInit(&pms->_q1);
	QueueInit(&pms->_q2);
	return pms;
}

/** Push element x onto stack. */
void myStackPush(MyStack* obj, int x) {
	assert(obj);
	if (QueueEmpty(&obj->_q1))
		QueuePush(&obj->_q2, x);
	else
		QueuePush(&obj->_q1, x);
}

/** Removes the element on top of the stack and returns that element. */
int myStackPop(MyStack* obj) {
	assert(obj);
	if (!QueueEmpty(&obj->_q1)) {
		//��q1��Ϊ��ʱ����q1�е�ǰn-1��Ԫ�ذ��Ƶ�q2��
		int size = QueueSize(&obj->_q1);
		while (size > 1) {
			QueuePush(&obj->_q2, QueueFront(&obj->_q1));
			QueuePop(&obj->_q1);
			size--;
		}
		int ret = QueueFront(&obj->_q1);
		QueuePop(&obj->_q1);
		return ret;
	}
	else {
		//��q2�е�ǰn-1��Ԫ�ذ��Ƶ�q1��
		int size = QueueSize(&obj->_q2);
		while (size > 1) {
			QueuePush(&obj->_q1, QueueFront(&obj->_q2));
			QueuePop(&obj->_q2);
			size--;
		}
		int ret = QueueFront(&obj->_q2);
		QueuePop(&obj->_q2);
		return ret;
	}
}

/** Get the top element. */
int myStackTop(MyStack* obj) {
	assert(obj);
	if (QueueEmpty(&obj->_q1))
		return QueueBack(&obj->_q2);
	else
		return QueueBack(&obj->_q1);
}

/** Returns whether the stack is empty. */
bool myStackEmpty(MyStack* obj) {
	assert(obj);
	if (QueueEmpty(&obj->_q1) && QueueEmpty(&obj->_q2))
		return true;
	else
		return false;
}

void myStackFree(MyStack* obj) {
	assert(obj);
	QueueDestory(&obj->_q1);
	QueueDestory(&obj->_q2);
	free(obj);
}