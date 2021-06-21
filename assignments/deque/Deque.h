#ifndef __DEQUE_H__
#define __DEQUE_H__

#define TRUE 1  /* TRUE를 1로 정의 */
#define FALSE 0 /* FALSE를 0 으로 정의 */

/*
제목: 덱 헤더
기능: 덱 라이브러리
작성자: 김홍중 (윤성우저자 열혈 자료구조 책 라이브러리)
*/

typedef int Data; /* int타입을 일반적인 형태로 Data로 정의. 나중에 다른 타입으로 바꾸기 용이 */

typedef struct _node /* 노드 구조체 정의 */
{
    Data data;          /* 데이터타입의 데이터 */
    struct _node *next; /* 노드의 다음을 가리킴 */
    struct _node *prev; /* 노드의 이전을 가리킴 */
} Node;

typedef struct _dlDeque /* 덱 정의 */
{
    Node *head; /* 처음 노드 가리키는 헤드 */
    Node *tail; /* 마지막 노드 가리키는 테일 */
} DLDeque;

typedef DLDeque Deque; /* 일반적인 형태의 덱으로 정의 */

void DequeInit(Deque *pdeq); /* 덱 초기화 */
int DQIsEmpty(Deque *pdeq);  /* 덱이 비어있는지 확인 */

void DQAddFirst(Deque *pdeq, Data data); /* 덱의 헤드에 삽입 */
void DQAddLast(Deque *pdeq, Data data);  /* 덱의 테일에 삽입 */

Data DQRemoveFirst(Deque *pdeq); /* 덱의 헤드에서 반환 및 제거 */
Data DQRemoveLast(Deque *pdeq);  /* 덱의 테일에서 반환 및 제거 */

Data DQGetFirst(Deque *pdeq); /* 덱 헤드의 데이터 얻기 */
Data DQGetLast(Deque *pdeq);  /* 덱 테일의 데이터 얻기 */

#endif
