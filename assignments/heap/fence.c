#include <stdio.h>
#include <stdlib.h>
#include "PriorityQueue.h"

/*
제목: 울타리
기능: 스카이라인에 따라 필요한 만큼의 울타리만 구합니다.
작성자: 김홍중
문제 출처 : https://www.acmicpc.net/problem/3119
*/

int DataPriorityComp(Location loc1, Location loc2);
/*
기본적으로 왼쪽x가 작을수록 우선순위가 높도록 설정
왼쪽x가 같다면 오른쪽x가 큰것이 우선순위 높도록 설정
둘다x가 동일하다면 높이가 큰 것이 우선순위 높도록 설정
*/

int main()
{
    PQueue input;  //인풋 힙
    PQueue answer; //정답을 저장한 힙
    int loop = 0;  // 입력 개수
    int i = 0, j = 0;
    int count = 0;
    int X = 0, W = 0, H = 0; //왼쪽x, 너비, 높이
    int removed = 0;
    PQData cur = {0, 0, 0, 0};           //현재 힙에서 꺼낸 노드
    PQData max_R_node = {0, 0, 0, 0};    //가장 큰 오른쪽x인 노드 킵
    PQData second_R_node = {0, 0, 0, 0}; // 두번째로 큰 오른쪽x인 노드 킵
    PQData temp = {0, 0, 0, 0};
    PQData *arr = NULL; // 이전 노드들 범위를 벗어나지 못한 경우 저장
    /*
	1. 입력을 받을때 왼쪽x, 오른쪽x(왼쪽x에서 너비를 더한 수), 높이, 입력순서를 저장한 노드들을 저장하는데,
	왼쪽 x 기준으로 최소힙을 구성
	2. 최소힙에서 노드들을 꺼내면서 다른 울타리로 인해 안보이는 울타리를 제외하고 새로운 힙에 저장
	3. 새로운 힙들을 출력
	*/

    PQueueInit(&input, DataPriorityComp);  //사용자 입력으로 저장된 힙
    PQueueInit(&answer, DataPriorityComp); //최소한의 울타리의 힙

    // 사용자로부터 입력 받으면 왼쪽x 기준으로 최소힙 구성
    scanf("%d", &loop);
    arr = (PQData *)malloc(sizeof(PQData) * (loop));
    for (i = 0; i < loop; i++)
    {
        scanf("%d", &X);       //왼쪽x
        scanf("%d", &W);       //너비
        scanf("%d", &H);       //높이
        cur.L_X = X;           //왼쪽x 설정
        cur.R_X = X + W;       //왼쪽x에 너비를 더해 오른쪽x설정
        cur.H = H;             //높이 설정
        cur.order = i + 1;     //입력 순서 설정
        PEnqueue(&input, cur); //노드 삽입
    }

    //최소힙에서 노드들을 꺼내면서 최소한의 울타리만 따로 저장하는 과정
    cur = PDequeue(&input);
    max_R_node = cur;
    PEnqueue(&answer, cur); // 처음은 무조건 삽입
    while (!PQIsEmpty(&input))
    {
        if (removed == 0)
        {
            cur = PDequeue(&input); // 하나씩 노드들 꺼내기
        }
        if (max_R_node.R_X < cur.R_X)
        { // 최대 오른쪽x보다 큰 경우
            removed = 0;
            if (max_R_node.H >= cur.H)
            {                        // 최대 오른쪽 노드의 높이가 현재 보다 크다면 범위내에 저장 가능한 울타리 있는지 판정
                second_R_node = cur; // 두번재로 큰 노드 저장
                while (1)
                {
                    if (!PQIsEmpty(&input))
                    {
                        cur = PDequeue(&input); // 현재 노드
                        removed = 1;            //next를 꺼낼 경우 표시
                    }
                    else
                    {
                        PEnqueue(&answer, second_R_node); // 범위를 벗어 나게되면 저장 가능한 울타리를 저장하고 탈출
                        break;
                    }
                    if (max_R_node.R_X < cur.R_X && second_R_node.R_X <= cur.R_X)
                    { //이전의 큰 노드들의 범위를 벗어난 경우
                        if (second_R_node.H < cur.H)
                        { // 두번째 큰 노드보다 높이가 크다면
                            if (max_R_node.R_X < cur.L_X)
                            {                                     //가장 큰 노드의 범위와 아예 겹치지 않는 경우
                                max_R_node = second_R_node;       // 가장 큰노드 업데이트
                                PEnqueue(&answer, second_R_node); // 노드 삽입
                            }
                            max_R_node = second_R_node; // 가장 큰노드 업데이트
                            break;
                        }
                        else
                        {
                            max_R_node = second_R_node;       // 가장 큰노드 업데이트
                            PEnqueue(&answer, second_R_node); //노드 삽입
                            break;
                        }
                    }
                    else if (second_R_node.R_X > cur.R_X)
                    { // 두번째 큰 노드의 범위를 벗어나지 못한 경우
                        if (max_R_node.H < cur.H)
                        { // 현재 노드의 높이가 클 때만 저장
                            PEnqueue(&answer, cur);
                        }
                    }
                }
            }
            else
            { // 최대보다 높이가 크다면
                max_R_node = cur;
                PEnqueue(&answer, cur);
            }
        }
        else if (max_R_node.R_X >= cur.R_X && max_R_node.H < cur.H)
        { //최대 노드의 범위 내이면서 높이는 더 큰 경우
            i = 0;
            while (!PQIsEmpty(&input) && i < loop)
            {
                count = 0;
                //temp = max_R_node;
                for (j = 0; j < i; j++)
                { // 이전 노드들의 범위를 벗어나지 못하는지 판단
                    temp = arr[j];
                    if (cur.L_X <= temp.R_X)
                    {
                        count++;
                    }
                }
                if (cur.R_X <= max_R_node.R_X)
                {
                    count++;
                }
                if (count == 0)
                { // 범위 벗어나면 탈출
                    break;
                }
                arr[i++] = max_R_node; // 벗어나지 못한 범위들을 저장
                max_R_node = cur;      //최대 노드 업데이트
                count = 0;
                for (j = 0; j < i; j++)
                { //저장된 노드들을 조회하면서 저장할 노드 찾기
                    if (arr[j].H < cur.H && arr[j].L_X <= cur.L_X && cur.R_X <= arr[j].R_X)
                    { //범위내에서 높이가 더 높다면
                        count++;
                    }
                }
                if (count == i)
                {
                    PEnqueue(&answer, cur); //노드 저장
                }
                cur = PDequeue(&input);
                for (j = 0; j < i; j++)
                {
                    if (arr[j].H < cur.H)
                    {
                        count++;
                    }
                }
            }
            PEnqueue(&answer, cur); // 노드 삽입
        }
    }

    printf("%d\n", answer.numOfData); //개수 출력
    loop = answer.numOfData;
    for (i = 0; i < loop; i++)
    { // 해당 노드들 출력
        if (!HIsEmpty(&answer))
        {
            cur = PDequeue(&answer); // 노드 꺼내기
        }
        printf("%d", cur.order);
        if (i == loop - 1)
        {
            break;
        }
        printf(" ");
    }
    free(arr); //동적할당 해제
    arr = NULL;
}

int DataPriorityComp(Location loc1, Location loc2)
{
    if (loc1.L_X < loc2.L_X)
    { //왼쪽x가 작을 수록 우선순위 높도록
        return 1;
    }
    else if (loc1.L_X > loc2.L_X)
    {
        return -1;
    }
    else if (loc1.R_X < loc2.R_X)
    {
        return -1;
    }
    else if (loc1.R_X > loc2.R_X)
    { //왼쪽x가 같다면 오른쪽x의 큰것이 우선순위 높게
        return 1;
    }
    else if (loc1.R_X == loc2.R_X)
    {
        if (loc1.L_X == loc2.L_X)
        {
            if (loc1.H < loc2.H)
            { //왼쪽x와 오른쪽x가 동일하다면 높이가 큰것이 우선순위 높도록
                return -1;
            }
            else
            {
                return 1;
            }
        }
    }
}
