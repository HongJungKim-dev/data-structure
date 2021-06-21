/*
제목: 상범이의 우울(ZIMA)
기능: 문제의 조건에 맞게 우울기간을 구합니다.
작성자: 김홍중
문제 출처 : https://www.acmicpc.net/problem/2811
*/
#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"

int is_term(int cur, int pre);
/*
우울기간 판단 함수
우울기간인지 판별할때 현재 데이터가 양수이고 직전의 데이터가 음수이면 TRUE를, 아니면 FALSE를 리턴합니다. 
*/

int short_sad(List depress, List *flower_addr, int *sum_addr);
/*
2T 구하는 함수
depress리스트를 조회하면서 우울한 기간이 나오면 2T만큼 flower리스트에 꽃(데이터 -1)을 주고, 그 외의 경우에는 다른 값(데이터 0)을 저장합니다.
flower리스트에 2T만큼 꽃을 부여하게 되는 과정에서 최장우울기간(3T)를 구해서 long_sad에서 참고합니다.
*/

void long_sad(List verse_depress, List *flower_addr, int max, int *sum_addr);
/*
3T 구하는 함수
verse_depress리스트에서 전체 기분의 기간을 조회하는동안 우울기간이 나오면 우울기간 이전까지 flower리스트에서 추가 가능한 꽃이 아닌 데이터를 조회합니다.
이때, short_sad함수에서 구해놓은 최장우울기간(3T)에 해당하면서 가장 많이 꽃을 줄 수 있는 개수를 찾아서 그 수가를 추가합니다.
*/
int main()
{
    /*
	사용자로 부터 예측한 날의 수, 기분을 입력 받아 리스트(depress)를 생성합니다.
	리스트(depress)를 생성할때 단방향연결리스트를 사용했기 때문에 입력의 반대순서대로 정보가 저장됩니다.
	3T를 구할때 입력된 순서에 따라 접근하고자 입력순서로 구성된 리스트(verse_depress)를 생성합니다.
	depress리스트를 조회하면서 flower리스트에 2T를 구하고 저장합니다.
	verse_depress리스트와 flower리스트를 조회하면서 3T를 구합니다. (flower리스트에 3T로 변경사항을 수정하지 않고 다른 변수로 카운트한 후에 결과를 냅니다.)
	결과를 출력합니다.
	*/
    List depress = {NULL, NULL, NULL, 0, 0};       //입력된 리스트
    List verse_depress = {NULL, NULL, NULL, 0, 0}; //입력된 순서의 반대인 리스트
    List flower = {NULL, NULL, NULL, 0, 0};        //이후에 꽃은 -1로 저장, 그외의 경우 0으로 저장

    int sum = 0; //전체 꽃 개수
    int data = 0;
    int loop = 0, i = 0;
    int max = 0; //최장우울기간(3T)

    //리스트들 초기화
    ListInit(&depress);
    ListInit(&flower);
    ListInit(&verse_depress);

    //리스트의 loop입력
    scanf("%d", &loop);

    //리스트 생성
    for (i = 0; i < loop; i++)
    { //사용자 입력으로 리스트(depress)를 생성합니다.
        scanf("%d", &data);
        LInsert(&depress, data); // 입력된 반대로 저장합니다.
    }

    //depress의 순서가 반대인 verse 생성
    if (LFirst(&depress, &data))
    { // list 첫 번째 데이터 조회

        LInsert(&verse_depress, data);     //verse_depress에 depress의 순서 반대로 저장
        while (LNext(&depress, &data))     // list 두 번째 이후의 데이터 조회
            LInsert(&verse_depress, data); //verse_depress에 depress의 순서 반대로 저장
    }

    //2T를 구합니다.
    max = short_sad(depress, &flower, &sum);

    //3T를 구합니다.
    long_sad(verse_depress, &flower, max, &sum);

    //정답을 출력합니다.
    printf("%d\n", sum);
}

//우울기간 판단 함수
int is_term(int cur, int pre)
{ //우울기간 판단 함수
    if (cur >= 0 && pre < 0)
    {                // 현재 데이터가 양수이고 직전의 데이터가 음수 인지 판별
        return TRUE; //맞다면 TRUE리턴
    }
    else
    {
        return FALSE; //아니라면 FALSE리턴
    }
}

//2T 구하는 함수
int short_sad(List depress, List *flower_addr, int *sum_addr)
{
    int data = 0, pre_data = 0;       //depress리스트에서 data는 현재 조회하는 데이터이고 pre_data는 직전에 조회한 데이터
                                      // pre_data는 is_term함수를 판단하기 위해 필요
    int flower = 0, sad = 0, max = 0; //flower은 꽃리스트에 꽃을 실제 넣을때 필요한 변수, sad는 우울한 날을 카운트,  max는 최장우울기간
    int d_idx = 0;                    //depress리스트의 인덱스, 가장 처음 데이터가 음수인 경우 최장우울기간으로 선정할 수 없도록 처리할때 필요
    int double_sad = 0;               //우울한 기간T의 2배만큼 flower을 주기 위해 사용

    if (LFirst(&depress, &data))
    { // depress리스트 첫번째 데이터 조회
        if (data < 0)
        { //depress리스트에서 우울기간 카운트////////////// 데이터가 음수이면 꽃의 개수 2T씩 기본으로 부여
            sad++;
            pre_data = data; //직전 데이터 저장
        }
        LInsert(flower_addr, 0); //꽃 리스트에 데이터 삽입 (-1만 꽃을 의미, 그 외는 0)
        d_idx++;                 //depress리스트 인덱스 증가

        while (LNext(&depress, &data))
        { // depress리스트 두 번째 이후의 데이터 조회

            if (data < 0)
            { //depress리스트에서 우울기간 카운트
                sad++;
            }

            //우울기간이 끝날때 삽입할 꽃 개수 업데이트
            if (is_term(data, pre_data))
            { //우울기간이면
                if (data < 0 && d_idx == (LCount(&depress) - 1))
                { //가장 처음 데이터가 음수인 경우 최장우울기간(3T)으로 선정할 수 없도록 처리
                    sad = 0;
                }
                double_sad = sad * 2;
                if (flower <= 0 || (double_sad) > flower)
                {                        // 꽃 리스트에 더 이상 삽입할 꽃이 없거나 꽃 리스트에 삽입할 꽃이 남아 있는 경우
                    flower = double_sad; //기본적으로 2T를 부여합니다.
                    sad = 0;
                    if (max < flower)
                    { //최장우울기간(3T) 업데이트
                        max = flower;
                    }
                }
                else
                {
                    sad = 0;
                }
            }

            //꽃리스트에 데이터 삽입 (-1만 꽃을 의미)
            if (flower <= 0)
            { //삽입할 꽃이 없다면 0 삽입
                LInsert(flower_addr, 0);
            }
            else if (flower > 0)
            { //삽입할 꽃이 있다면 -1삽입
                LInsert(flower_addr, -1);
                flower--;
                (*sum_addr)++;
            }
            pre_data = data; //직전 데이터 저장
            d_idx++;         //depress리스트 인덱스 증가
        }
    }
    return max / 2; //3T구할때 T를 이용하기 위해 2를 나누기
}

//3T 구하는 함수
void long_sad(List verse_depress, List *flower_addr, int max, int *sum_addr)
{
    int data = 0, pre_data = 0; //verse_depress(입력된 순서의 리스트)리스트의 현재 데이터, 직전의 데이터 저장 변수
    int sad = 0;                // 우울힌 날
    int keep_sad = 0;
    int idx = 0;                          //verse_depress의 인덱스. 우울한 첫날, 마지막날 구할 때 사용. 마지막 인덱스인지 비교할때 사용
    int end = LCount(&verse_depress) - 1; //verse_depress리스트의 마지막 인덱스
    int first_idx = 0, last_idx = 0;      //verse_depress리스트에서 우울한 첫날, 마지막날 (매 우울기간 마다 달라집니다.)
    int start = 0;                        //3T의 시작 인덱스. 구체적으로 현재 꽃이 아니지만 3T가 될 수 있는지 판별하기 위한 범위의 시작

    int flower_idx = 0;  //flower리스트 인덱스, 각 우울기간보다 나중의 flower를 카운트하지 못하게 하기 위해 필요
    int flower_data = 0; //현재 flower리스트 내의 정보, 꽃이면 -1이고 그외의 경우는 0
    int not_flower = 0;  //flower리스트에서 현재 꽃이 아닌 데이터
    int plus = 0;        //3T로 추가할 꽃의 개수

    if (LFirst(&verse_depress, &data))
    { // verse_depress리스트 첫번째 데이터 조회
        if (data < 0)
        { //우울한 날이면 증가
            sad++;
        }
        if (sad == 1)
        { //verse_depress리스트 우울한 날 첫날 저장
            first_idx = idx;
        }
        pre_data = data; //직전의 데이터 저장
        idx++;           //verse_depress리스트 인덱스 증가
        while (LNext(&verse_depress, &data))
        { // verse_depress리스트 두 번째 이후의 데이터 조회

            if (data < 0)
            { //우울한 날이면 증가
                sad++;
                keep_sad = sad;
            }
            else
            {
                sad = 0;
            }
            if (sad == 1)
            { //verse_depress리스트 우울한 날 첫날 업데이트
                first_idx = idx;
            }
            if (is_term(data, pre_data) || ((keep_sad > 0) && idx == end))
            { //우울기간인경우(1.계속 음수이다가 양수되거나, 2.계속 음수이다가 마지막인덱스까지 간 경우)
                if (end == idx && data < 0)
                { // 우울기간2인경우 우울한 날 마지막날 업데이트
                    last_idx = idx;
                }
                else
                {
                    last_idx = idx - 1; // 우울기간1인 경우 우울한 날 마지막날 업데이트
                }
                start = first_idx + (-3) * (last_idx - first_idx + 1); //3T의 시작 인덱스 구하기

                not_flower = 0; //꽃이 아닌 데이터 초기화
                flower_idx = 0; //flower리스트 인덱스 초기화
                if ((flower_idx < first_idx) && LFirst(flower_addr, &flower_data))
                { // flower리스트 첫번째 데이터 조회
                    if ((start <= flower_idx) && flower_data == 0)
                    { //3T가능 구간이고 꽃이 아직 없는 경우
                        not_flower++;
                    }
                    flower_idx++; //flower리스트 인덱스 증가
                    while ((flower_idx < first_idx) && LNext(flower_addr, &flower_data))
                    { // flower리스트 두번째 이후 데이터 조회

                        if ((start <= flower_idx) && flower_data == 0)
                        { //3T가능 구간이고 꽃이 아직 없는 경우
                            not_flower++;
                        }
                        if ((keep_sad == max) && plus < not_flower)
                        { //3T구하기. (short_sad에서 구해놓은 최장우울기간이고 추가할 후보의 꽃이 가장 많은 경우)
                            plus = not_flower;
                        }
                        flower_idx++; //flower리스트 인덱스 증가
                    }
                }
                start = 0;
                sad = 0;
                keep_sad = 0;
            }
            pre_data = data; //verse_depress 직전의 데이터 저장
            idx++;
        }
    }
    (*sum_addr) += plus; // 꽃 추가
}
