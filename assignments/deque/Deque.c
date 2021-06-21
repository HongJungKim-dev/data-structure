#include <stdio.h>
#include <stdlib.h>
#include "Deque.h"
/*
제목: 덱 관련 함수
기능: 덱 라이브러리
작성자: 김홍중 (윤성우저자 열혈 자료구조 책 라이브러리)
*/

/* 덱 초기화 */
void DequeInit(Deque *pdeq)
{
    pdeq->head = NULL; /* 덱의 헤드를 널로 초기화*/
    pdeq->tail = NULL; /* 덱의 테일을 널로 초기화 */
}

/* 덱이 비어있는지 확인 */
int DQIsEmpty(Deque *pdeq)
{
    if (pdeq->head == NULL) /* 덱이 비어있다면 TRUE 반환 */
        return TRUE;
    else
        return FALSE; /* 그렇지 않으면 TRUE 반환 */
}

/* 덱의 헤드에 삽입 */
void DQAddFirst(Deque *pdeq, Data data)
{
    Node *newNode = (Node *)malloc(sizeof(Node)); /* 새로운 노드 할당 */
    newNode->data = data;                         /* 새로운 노드가 가리키는 데이터에 파라미터로 넘어온 데이터 저장 */

    newNode->next = pdeq->head; /* 새로운노드가 맨 처음으로 오도록 새로운노드 next가 기존의 처음노드를 가리키도록 */

    if (DQIsEmpty(pdeq)) /* 덱이 비어있다면 테일(마지막)이 새로운 노드 가리키도록 */
        pdeq->tail = newNode;
    else
        pdeq->head->prev = newNode; /* 덱이 비어있지 않다면 헤드가 가리키고 있던것은 두번째가 되므로 두번째 노드의 이전이 새로운 노드 가리키도록 */

    newNode->prev = NULL; /* 새로운 노드는 첫번째가 되어서 이전은 없으므로 널 */
    pdeq->head = newNode; /* 새로운 노드가 첫번째가 되어서 헤드가 이를 가리키도록 */
}

/* 덱의 테일에 삽입 */
void DQAddLast(Deque *pdeq, Data data)
{
    Node *newNode = (Node *)malloc(sizeof(Node)); /* 새로운 노드 할당 */
    newNode->data = data;                         /* 새로운 노드가 가리키는 데이터에 파라미터로 넘어온 데이터 저장 */

    newNode->prev = pdeq->tail; /* 새로운노드가 맨 마지막으로 오도록 새로운 노드 prev이 기존의 마지막 노드에 연결 */

    if (DQIsEmpty(pdeq))      /* 덱이 비어있다면 */
        pdeq->head = newNode; /* 새로운노드를 헤드가 가리킴 */
    else
        pdeq->tail->next = newNode; /* 덱이 비어있지 않다면 새로운노드가 맨 마지막으로 오도록 기존의 마지막 노드 next가 새로운 노드 가리키도록 */

    newNode->next = NULL; /* 마지막에 위치해서 그 다음은 널 */
    pdeq->tail = newNode; /* 테일이 새로운 노드 가리키도록 */
}

/* 덱의 헤드에서 반환 및 제거 */
Data DQRemoveFirst(Deque *pdeq)
{
    Node *rnode = pdeq->head;      /* 삭제할 노드가 처음을 가리키도록 */
    Data rdata = pdeq->head->data; /* 처음 노드의 데이터를 반환하기 위해 저장 */

    if (DQIsEmpty(pdeq)) /* 덱이 비어있다면 오류메시지 출력후 종료 */
    {
        printf("Deque Memory Error!");
        exit(-1);
    }

    pdeq->head = pdeq->head->next; /* 처음 데이터가 삭제되서 없어지므로 그 다음데이터가 첫번째가 되도록 헤드가 다음 데이터 가리킴 */
    free(rnode);                   /* 삭제할 노드 해제 */

    if (pdeq->head == NULL) /* 헤드가 널이면 테일 널 처리 */
        pdeq->tail = NULL;
    else
        pdeq->head->prev = NULL; /* 헤드가 널이 아니면 기존의 두번째 위치했던 노드의 이전은 널처리 */

    return rdata; // 삭제한 데이터 반환
}

/* 덱의 테일에서 반환 및 제거 */
Data DQRemoveLast(Deque *pdeq)
{
    Node *rnode = pdeq->tail;      /* 삭제할 노드 마지막을 가리키도록 */
    Data rdata = pdeq->tail->data; /* 마지막 노드의 데이터를 반환하기 위해 저장 */

    if (DQIsEmpty(pdeq)) /* 덱이 비어있다면 오류메세지 출력후 종료 */
    {
        printf("Deque Memory Error!");
        exit(-1);
    }

    pdeq->tail = pdeq->tail->prev; /* 테일을 먼저 마지막의 이전노드로 이동 (노드 동적할당 해제후에는 이동 못시켜서) */
    free(rnode);                   /* 삭제할 노드 해제 */

    if (pdeq->tail == NULL) /* 테일이 널이면 헤드 널처리 */
        pdeq->head = NULL;
    else
        pdeq->tail->next = NULL; /* 테일이 널이 아니면 기존 남아있던 노드가 마지막이 되므로 그것의 next가 널이 되도록 */

    return rdata; /* 삭제한 데이터 반환 */
}

/* 덱 헤드의 데이터 소멸하지않고 PEEK */
Data DQGetFirst(Deque *pdeq)
{
    if (DQIsEmpty(pdeq)) /* 덱이 비어있을 경우 오류메세지 출력후 종료 */
    {
        printf("Deque Memory Error!");
        exit(-1);
    }

    return pdeq->head->data; /* 헤드가 가리키는 데이터 리턴 */
}

/* 덱 테일의 데이터 소멸하지않고 PEEK */
Data DQGetLast(Deque *pdeq)
{
    if (DQIsEmpty(pdeq)) /* 덱이 비어있을 경우 오류메세지 출력후 종료 */
    {
        printf("Deque Memory Error!");
        exit(-1);
    }

    return pdeq->tail->data; /* 테일이 가리키는 데이터 리턴 */
}
