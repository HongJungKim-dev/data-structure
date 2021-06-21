#include "UsefulHeap.h"
/*
제목: 힙 관련 함수
기능: 힙 라이브러리
작성자: 김홍중 (윤성우저자 열혈 자료구조 책 라이브러리)
*/
void HeapInit(Heap *ph, PriorityComp pc)
{
    ph->numOfData = 0; //0으로 초기화
    ph->comp = pc;     // 함수 등록
}

int HIsEmpty(Heap *ph)
{
    if (ph->numOfData == 0) // 데이터 없다면 TRUE리턴
        return TRUE;
    else
        return FALSE;
}

int GetParentIDX(int idx) // 부모 인덱스 구하기
{
    return idx / 2;
}

int GetLChildIDX(int idx) // 자식 인덱스 구하기
{
    return idx * 2;
}

int GetRChildIDX(int idx) //자식 인덱스 구하기
{
    return GetLChildIDX(idx) + 1;
}

int GetHiPriChildIDX(Heap *ph, int idx)
{
    if (GetLChildIDX(idx) > ph->numOfData) // 자식 노드가 존재하지 않으면
        return 0;

    else if (GetLChildIDX(idx) == ph->numOfData) // 자식 노드가 왼쪽 자식 노드 하나만 존재하면
        return GetLChildIDX(idx);

    else // 자식 노드가 둘다 존재하면
    {
        // 오른쪽 자식 노드 우선순위가 높다면
        if (ph->comp(ph->heapArr[GetLChildIDX(idx)],
                     ph->heapArr[GetRChildIDX(idx)]) < 0)
            return GetRChildIDX(idx);
        else // 왼쪽 자식 노드의 우선순위 높다면
            return GetLChildIDX(idx);
    }
}

void HInsert(Heap *ph, HData data)
{
    int idx = ph->numOfData + 1; // 새노드 저장할 인덱스 값을 저장

    while (idx != 1) // 새 노드가 저장될 위치를 찾기 위해서 while문 반복
    {
        if (ph->comp(data, ph->heapArr[GetParentIDX(idx)]) > 0) // 새 노드의 우선순위가 높다면
        {
            ph->heapArr[idx] = ph->heapArr[GetParentIDX(idx)]; // 부모 노드를 한 레벨 내리는데 실제로도 내림
            idx = GetParentIDX(idx);                           // 새 노드를 한 레벨 올리는데 실제로 올리지 않고 인덱스 값만 업데이트
        }
        else
        {
            break; //새 노드의 우선순위가 높지 않다면
        }
    }

    ph->heapArr[idx] = data; // 새 노드를 배열에 저장
    ph->numOfData += 1;      // 개수 증가
}

HData HDelete(Heap *ph)
{
    HData retData = ph->heapArr[1];              // 삭제할 데이터 저장
    HData lastElem = ph->heapArr[ph->numOfData]; // 힙의 마지막 노드 저장

    int parentIdx = 1; // 루트 노드가 위치해야할 인덱스 값
    int childIdx;

    while (childIdx = GetHiPriChildIDX(ph, parentIdx)) // 루트 노드의 우선순위 높은 자식 노드를 시작으로 반복문 시작
    {
        if (ph->comp(lastElem, ph->heapArr[childIdx]) >= 0) // 마지막 노드오 우선순위 비교
            break;                                          // 마지막 노드 우선수위 높으면 탈출
        // 마지막 노드보다 우선순위 가 높아서 비교대상 노드의 위치를 한 레벨 올림
        ph->heapArr[parentIdx] = ph->heapArr[childIdx];
        parentIdx = childIdx; // 마지막 노드가 저장될 위치정보를 한 레벨 내림
    }

    ph->heapArr[parentIdx] = lastElem; // 마지막 노드 저장
    ph->numOfData -= 1;                // 개수 줄이기
    return retData;                    //리턴
}
