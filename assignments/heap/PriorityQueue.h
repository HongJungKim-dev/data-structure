#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include "UsefulHeap.h"
/*
제목: 우선순위큐 헤더
기능: 우선순위큐 라이브러리
작성자: 김홍중 (윤성우저자 열혈 자료구조 책 라이브러리)
*/

typedef Heap PQueue;
typedef HData PQData;

void PQueueInit(PQueue *ppq, PriorityComp pc); //초기화
int PQIsEmpty(PQueue *ppq);                    //비어있는지 판단

void PEnqueue(PQueue *ppq, PQData data); //삽입
PQData PDequeue(PQueue *ppq);            //삭제

#endif
