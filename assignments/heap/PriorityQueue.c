#include "PriorityQueue.h"
#include "UsefulHeap.h"
/*
제목: 우선순위큐 관련 함수
기능: 우선순위큐 라이브러리
작성자: 김홍중 (윤성우저자 열혈 자료구조 책 라이브러리)
*/
void PQueueInit(PQueue *ppq, PriorityComp pc)
{
    HeapInit(ppq, pc); //초기화
}

int PQIsEmpty(PQueue *ppq)
{
    return HIsEmpty(ppq); //비어있는지 판단
}

void PEnqueue(PQueue *ppq, PQData data)
{
    HInsert(ppq, data); //삽입
}

PQData PDequeue(PQueue *ppq)
{
    return HDelete(ppq); //삭제
}
