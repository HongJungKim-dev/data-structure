#include <stdio.h>
#include "Deque.h"
/*
제목: AC
기능: AC언어에 따라 두 함수 R(뒤집기)과 D(버리기)를 수행합니다.
작성자: 김홍중
문제 출처 : https://www.acmicpc.net/problem/5430
*/

char dtoi(Deque *pdeq);
/*
덱타입을 int타입으로 변환
덱에는 tail에서 head까지 1의 자리수, 10의 자리수, 100의 자리수... 순서로 저장되어 있습니다.
각 자리수를 1, 10, 100... 등으로 곱한 후에 각 자리수를 모두 더해 int타입으로 변환합니다.
*/

int RD(Deque *pdeq, Deque *func, int *pis_last);
/*
R(뒤집기), D(버리기) 수행하는 함수
함수덱에 있는 함수를 이용하여 R이면 XOR연산으로 앞, 뒤 순서를 뒤집어서 이 정보를 is_last에 저장
D인 경우에는 덱이 비어있는데도 버리기를 시도할 경우 FALSE로 리턴하는데 리턴하기 전에 함수덱이 비어있지 않으면 비우기
덱이 비어있지 않으면 is_last의 정보에 따라 앞이면 앞쪽에서 버리고 뒤쪽이면 뒤쪽에서 버리기
*/

void show_deq(Deque *pdeq, int res, int *pis_last);
/*
RD함수 이후에 덱에 남아 있는 데이터 출력하는 함수
에러이면 에러 메세지 출력
아니라면 뒤집힌상태(is_last)여부에 따라 앞 혹은 뒤쪽에서부터 출력
*/

int main()
{
    int i = 0;
    int j = 0;
    int loop = 0;    // 테스트케이스
    int len = 0;     // 입력된 숫자 개수
    char tok = 0;    // 입력된 각 함수이름 , 입력된 숫자Xn을 구성하는 각 자리수의 숫자
    int res = 0;     // error인지 아닌지 저장
    int is_last = 0; // 뒤집힌 상태인지 저장
    char prev = 0;   // 아무 숫자 입력되지 않는 경우 위해 이전 값 저장
    /*
	0. 반복할 테스트 케이스를 입력
	1. 함수를 입력
	2. 입력하는 숫자의 개수 입력
	3. [10,20,30]형태로 숫자를 입력
	   각 자리수의 수를 임시덱에 차례로 저장
	   ','또는 ']'가 나오면 임시덱을 int타입의 숫자로 변환 후 덱에 입력
	4. RD함수로 R(뒤집기), D(버리기)를 수행
	5. RD함수로 바뀐 덱을 차례로 출력
	6. 1~5을 테스트 케이스만큼 반복
	*/

    Deque deq;  /* 덱 선언 */
    Deque temp; /* 임시덱 선언 */
    Deque func; /* 함수덱 선언 */

    DequeInit(&deq);  /* 덱 초기화 */
    DequeInit(&temp); /* 임시덱 초기화 */
    DequeInit(&func); /* 함수덱 초기화 */

    scanf("%d", &loop); /* 반복할 테스트케이스 개수 입력 */

    for (i = 0; i < loop; i++)
    {
        for (j = 0;; j++)
        {
            scanf("%c", &tok); /* 함수 입력 */
            if (j == 0 && tok == '\n')
            { /* 입력버퍼 비우기 */
                continue;
            }
            else if (tok == '\n')
            { /* 입력이 끝나면 종료 */
                break;
            }
            if (tok == 'R' || tok == 'D')
            { /* R이나 D함수일경우 함수 덱에 삽입 */
                DQAddLast(&func, tok);
            }
        }

        scanf("%d", &len); /* 입력하는 숫자의 개수 입력 */
        tok = 0;
        for (j = 0;; j++)
        {
            scanf("%c", &tok);
            if (j == 0 && tok == '\n')
            { /* 입력버퍼 비우기 */
                continue;
            }
            else if (tok == '\n')
            { /* 사용자가 엔터할때까지 입력허용 */
                break;
            }

            if (prev == '[' && tok == ']')
            { /* 아무 숫자도 입력되지 않은 경우 예외 처리 */
                break;
            }
            else if ((tok == ',' || tok == ']'))
            {                                 /* 숫자 Xn을 덱에 삽입 */
                DQAddLast(&deq, dtoi(&temp)); /* 숫자Xn의 각 자리수의 수가 저장된 임시덱을 int 타입의 숫자로 변환후 덱에 숫자를 삽입 */
            }
            else if ('0' <= tok && tok <= '9')
            { /* 숫자 Xn 의 각 자리수의 수를 임시덱에 int타입으로 저장 */
                DQAddLast(&temp, tok - '0');
            }
            prev = tok; /* 아무 숫자가 입력되지 않는 예외를 처리하기 위해 저장 */
        }

        res = RD(&deq, &func, &is_last); /* R(뒤집기)와 D(버리기)를 수행 */
        show_deq(&deq, res, &is_last);   /* RD함수의 결과를 출력 */
    }
}

/* 덱타입을 int타입으로 변환 */
char dtoi(Deque *pdeq)
{
    int temp = 0;
    int data = 0;  /* 각 자리수의 숫자 */
    int digit = 1; /* 자리수 */

    while (!DQIsEmpty(pdeq))
    { /* 덱이 비워질때까지 */
        temp = DQRemoveLast(pdeq);
        data = data + temp * digit; /* 덱에 있는 숫자를 하나씩 꺼내어 각 자리수만큼 곱하여 저장 */
        digit *= 10;                /* 큰 자리수 이동 */
    }
    return data; /* 변환된 정수 리턴 */
}

/* R(뒤집기), D(버리기) 수행 */
int RD(Deque *pdeq, Deque *pfunc, int *pis_last)
{
    char data = 0; /* 입력된 함수 */

    *pis_last = 0;
    while (!DQIsEmpty(pfunc))
    {                                /* 함수덱이 빌때까지 확인 */
        data = DQRemoveFirst(pfunc); /* 입력된 함수를 차례로 확인 */
        if (data == 'R')
        { /* XOR연산으로 R(뒤집기) 함수가 나올때마다 앞, 뒤 순서를 전환 */
            *pis_last = *pis_last ^ 1;
        }
        else if (DQIsEmpty(pdeq) && data == 'D')
        { /* 덱이 비어있는데도 D(버리기)를 시도할 경우 에러가 발생하기에 예외처리로 FALSE 리턴 */
            while (!DQIsEmpty(pfunc))
            { /* 사용이 완료된 함수덱 비우기 */
                DQRemoveFirst(pfunc);
            }
            return FALSE;
        }
        else if (data == 'D' && *pis_last == 1)
        {                       /* 덱이 비어있지 않고 D(버리기)함수 일경우 */
            DQRemoveLast(pdeq); /* R함수로 인해 뒤쪽이면 뒤쪽 버리기 */
        }
        else if (*pis_last == 0)
        { /* R함수로 인해 앞쪽이면 앞쪽 버리기 */
            DQRemoveFirst(pdeq);
        }
    }
    return TRUE; /* 에러가 발생하지 않으면 TRUE 리턴 */
}

/* RD함수 이후에 덱에 남아 있는 데이터 출력 */
void show_deq(Deque *pdeq, int res, int *pis_last)
{
    int data = 0; // 덱에 저장된 데이터

    if (res == TRUE)
    { /* 에러가 아닌 경우 */
        printf("[");
        while (1)
        {
            if (*pis_last == 1 && !DQIsEmpty(pdeq))
            {                                     /* 뒤쪽으로 뒤집힌 경우이면서 덱이 비어있지 않은 경우 */
                printf("%d", DQRemoveLast(pdeq)); /* 뒤쪽에서부터 출력 */
            }
            else if (*pis_last == 0 && !DQIsEmpty(pdeq))
            {                                      /* 앞쪽이면서 덱이 비어있지 않은 경우 */
                printf("%d", DQRemoveFirst(pdeq)); /* 앞쪽에서부터 출력 */
            }
            if (DQIsEmpty(pdeq))
            { /* 마지막 숫자는 ','를 출력하지 않기 위해 반복문 탈출 */
                break;
            }
            printf(",");
        }
        printf("]\n");
    }
    else if (res == FALSE)
    { /* 에러인 경우 에러 메세지 출력 */
        printf("error\n");
    }
}
