#ifndef __USEFUL_HEAP_H__
#define __USEFUL_HEAP_H__

#define TRUE 1
#define FALSE 0
/*
제목: 힙 헤더
기능: 힙 라이브러리
작성자: 김홍중 (윤성우저자 열혈 자료구조 책 라이브러리)
*/

/*** Heap의 정의 ****/
#define HEAP_LEN 100

/* 문제를 풀기 위해 Location을 정의*/
typedef struct location
{
    int L_X;   //사각형의 왼쪽 x
    int R_X;   //오른쪽 x
    int H;     //높이
    int order; //입력 순서
} Location;

/* Location을 HData로 선언 */
typedef Location HData;

typedef int PriorityComp(HData d1, HData d2);

typedef struct _heap
{
    PriorityComp *comp;      // 우선순위를 위해 함수포인터 사용
    int numOfData;           // 데이터의 개수
    HData heapArr[HEAP_LEN]; // 힙 배열
} Heap;

/*** Heap 관련 연산들 ****/
void HeapInit(Heap *ph, PriorityComp pc); // 힙 초기화
int HIsEmpty(Heap *ph);                   // 힙 비어있는지 확인

void HInsert(Heap *ph, HData data); // 힙 삽입
HData HDelete(Heap *ph);            // 힙 삭제

#endif
