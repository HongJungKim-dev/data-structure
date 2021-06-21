/*
제목: 단방향 연결리스트 헤더
기능: 단방향 연결리스트 라이브러리
작성자: 김홍중 (윤성우저자 열혈 자료구조 책 라이브러리)
*/
#ifndef __D_LINKED_LIST_H__
#define __D_LINKED_LIST_H__

#define TRUE 1
#define FALSE 0

typedef int LData; //데이터의 타입을 사용자가 바꿀 수 있기 때문에 general하게 LData로 정의

typedef struct _node //노드에 데이터와 노드 가리키는 포인터
{
    LData data;
    struct _node *next;
} Node;

typedef struct _linkedList //리스트 구성
{
    Node *head;                      //더미노드 가리킴
    Node *cur;                       //참조 및 삭제 도움
    Node *before;                    // 삭제를 도움
    int numOfData;                   // 데이터 개수
    int (*comp)(LData d1, LData d2); //정렬기준
} LinkedList;

typedef LinkedList List; // 다양한 리스트를 사용할 수 있기에 geneeral하게 List로 사용

void ListInit(List *plist);            // 리스트 초기화
void LInsert(List *plist, LData data); ////정렬 여부에 따라 데이터 추가 함수를 호출

int LFirst(List *plist, LData *pdata); // 처음 데이터 조회
int LNext(List *plist, LData *pdata);  // 두번째 이후 데이터 조회

LData LRemove(List *plist); // 데이터 삭제
int LCount(List *plist);    // 데이터 개수 구하기

void SetSortRule(List *plist, int (*comp)(LData d1, LData d2)); // 정렬기준 저장

#endif
