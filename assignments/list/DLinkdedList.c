/*
제목: 단방향 연결리스트 함수
기능: 단방향 연결리스트 라이브러리
작성자: 김홍중 (윤성우저자 열혈 자료구조 책 라이브러리)
*/
#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"

//리스트를 초기화
void ListInit(List *plist)
{
    plist->head = (Node *)malloc(sizeof(Node)); //노드 할당
    plist->head->next = NULL;                   // 헤드 초기화
    plist->comp = NULL;                         //함수포인터 조기화
    plist->numOfData = 0;                       // 개수 초기화
}

//리스트에 데이터 추가 (정렬 고려하지 않습니다.)
void FInsert(List *plist, LData data)
{
    Node *newNode = (Node *)malloc(sizeof(Node)); // 새로운 노드 할당
    newNode->data = data;                         // 새 데이터 저장

    //데이터 삽입
    newNode->next = plist->head->next; //새 노드가 다른 노드 가리키도록
    plist->head->next = newNode;       // 더미 노드가 새 노드를 가리키도록

    (plist->numOfData)++; // 데이터 개수 증가
}

//리스트에 데이터 추가 (정렬 고려합니다.)
void SInsert(List *plist, LData data)
{
    Node *newNode = (Node *)malloc(sizeof(Node)); // 새로운 노드 할당
    Node *pred = plist->head;                     //더미노드
    newNode->data = data;                         // 새 데이터 저장

    // 새 노드 들어갈 위치 찾기
    while (pred->next != NULL &&
           plist->comp(data, pred->next->data) != 0)
    {
        pred = pred->next;
    }

    newNode->next = pred->next; // 새 노드의 오른쪽 연결
    pred->next = newNode;       // 새 노드의 왼쪽 연결

    (plist->numOfData)++; // 데이터 개수 증가
}

//정렬 여부에 따라 데이터 추가 함수를 호출합니다.
void LInsert(List *plist, LData data)
{
    if (plist->comp == NULL) // 정렬방식 등록 되어있지 않으면
        FInsert(plist, data);
    else // 정렬방식 등록 되어있으면
        SInsert(plist, data);
}

// 처음 데이터 조회 함수
int LFirst(List *plist, LData *pdata)
{
    if (plist->head->next == NULL) //조회할 데이터가 없는 경우 FALSE리턴
        return FALSE;

    //처음 데이터 조회
    plist->before = plist->head;    //before가 더미 노드 가리키도록
    plist->cur = plist->head->next; // cur이 첫번째 노드 가리키도록

    *pdata = plist->cur->data; // 첫 번째 노드의 데이터 저장
    return TRUE;               //데이터 있는 경우 TRUE리턴
}

// 두번째 이후 데이터 조회 함수
int LNext(List *plist, LData *pdata)
{
    if (plist->cur->next == NULL) //더이상 조회할 데이터가 없는 경우 FALSE리턴
        return FALSE;

    //데이터 조회
    plist->before = plist->cur;    //cur이 카리키던 것을 before이 가리키도록
    plist->cur = plist->cur->next; // cur이 그 다음 노드 카리키도록

    *pdata = plist->cur->data; //cur이 가리키는 노드의 데이터 전달
    return TRUE;               //데이터 있는 경우 TRUE리턴
}

//데이터 삭제 함수
LData LRemove(List *plist)
{
    Node *rpos = plist->cur;  //해제를 위해 저장합니다.
    LData rdata = rpos->data; //리턴을 위해 저장해 둡니다.

    //삭제로 인한 연결 재조정
    plist->before->next = plist->cur->next; // 제거 대상 리스트에서 제거
    plist->cur = plist->before;             // cur이 가리키는 위치 재조정

    free(rpos);           //해제
    (plist->numOfData)--; //데이터 개수 감소
    return rdata;         //삭제한 데이터 리턴
}

//데이터의 개수 구하는 함수
int LCount(List *plist)
{
    return plist->numOfData; //데이터 개수 리턴
}

//정렬 방식 대입 함수
void SetSortRule(List *plist, int (*comp)(LData d1, LData d2))
{
    plist->comp = comp; //함수포인터를 이용하여 정렬방식을 등록합니다.
}
