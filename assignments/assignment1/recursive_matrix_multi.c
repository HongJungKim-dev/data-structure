/*
제목: 재귀함수로 행렬곱 구하기
기능: 타일링 방식으로 공간복잡도를 줄입니다.
작성자: 김홍중
*/
#include <stdio.h>
#include <stdlib.h>

void make_row(int ***row_addr, int a);                                                                  //행 만들기
void make_col(int **row, int a, int b);                                                                 //열 만들기
void make_matrix(int ***row_addr, int a, int b);                                                        //make_row, make_col호출후 사용자입력 받기
void print_matrix(int **matrix, int a, int b);                                                          // 행렬 출력하기
int recur_multi(int **A, int **B, int ***C_addr, int row_A, int col_A, int row_B, int col_B, int size); //재귀 행렬곱셈하기
void free_matrix(int ***matrix_addr, int a, int b);                                                     // 행렬 동적할당하기

int main()
{
    /*
	사용자의 입력에 따라 두 행렬을 생성하고 이를 곱합니다.
	이후 동적할당한 행렬들은 해제합니다.
	*/
    int i = 0, j = 0, c = 0;
    int size = 0, row_A = 0, col_A = 0, row_B = 0, col_B = 0;
    int **A = NULL;
    int **B = NULL;
    int **C = NULL;
    printf("nxn행행렬을 생성하기 위한 n을 입력하시오 :");
    scanf("%d", &size);

    row_A = size;
    col_A = size;
    row_B = size;
    col_B = size;

    //A행렬 생성
    printf("A행렬을 입력하시오:\n");
    make_matrix(&A, row_A, col_A);

    //B행렬 생성
    printf("B행렬을 입력하시오:\n");
    make_matrix(&B, row_B, col_B);

    //C행렬 생성
    make_row(&C, row_A);
    make_col(C, row_A, col_A);

    //재귀행렬곱
    recur_multi(A, B, &C, 0, 0, 0, 0, size);

    //결과 출력
    printf("출력\n");
    print_matrix(C, row_A, col_B);

    //각 행렬 동적할당 해제
    free_matrix(&C, row_A, col_B);
    free_matrix(&B, row_B, col_B);
    free_matrix(&A, row_A, col_A);
}

void make_row(int ***row_addr, int a)
{
    (*row_addr) = (int **)calloc(a, sizeof(int *)); //행 생성후 0으로 초기화
    if (*row_addr == NULL)
    { //예외처리
        printf("calloc fail\n");
        exit(-1);
    }
}

void make_col(int **row, int a, int b)
{
    int i = 0;
    for (i = 0; i < a; i++)
    {
        row[i] = (int *)calloc(b, sizeof(int)); //열 생성후 0으로 초기화
        if (row[i] == NULL)
        { //예외처리
            printf("calloc fail\n");
            exit(-1);
        }
    }
}

void make_matrix(int ***row_addr, int a, int b)
{
    int i = 0, j = 0;
    make_row(row_addr, a);     // 행 생성
    make_col(*row_addr, a, b); // 열 생성

    for (i = 0; i < a; i++)
    {
        for (j = 0; j < b; j++)
        {
            scanf("%d", &((*row_addr)[i][j])); // 각 행렬의 원소 사용자 입력
        }
    }
}

void print_matrix(int **matrix, int a, int b)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < a; i++)
    {
        for (j = 0; j < b; j++)
        {
            printf("%d ", matrix[i][j]); //각 원소 출력
        }
        printf("\n");
    }
}

int recur_multi(int **A, int **B, int ***C_addr, int row_A, int col_A, int row_B, int col_B, int size)
{
    int new_size = 0;
    if (size == 1)
    {
        return A[row_A][col_A] * B[row_B][col_B]; //곱셈 후 리턴
    }
    else
    {
        new_size = size / 2; //부분행렬로 나눌 인덱스를 구하기 위해서
        //C11 = A11 * B11 + A12 * B21
        (*C_addr)[row_A][col_B] += (recur_multi(A, B, C_addr, row_A, col_A, row_B, col_B, new_size) + recur_multi(A, B, C_addr, row_A, col_A + new_size, row_B + new_size, col_B, new_size));
        //C12 = A11 * B12 + A12 * B22
        (*C_addr)[row_A][col_B + new_size] += (recur_multi(A, B, C_addr, row_A, col_A, row_B, col_B + new_size, new_size) + recur_multi(A, B, C_addr, row_A, col_A + new_size, row_B + new_size, col_B + new_size, new_size));
        //C21 = A21 * B11 + A22 * B21
        (*C_addr)[row_A + new_size][col_B] += (recur_multi(A, B, C_addr, row_A + new_size, col_A, row_B, col_B, new_size) + recur_multi(A, B, C_addr, row_A + new_size, col_A + new_size, row_B + new_size, col_B, new_size));
        //C22 = A21 * B12 + A22 * B22
        (*C_addr)[row_A + new_size][col_B + new_size] += (recur_multi(A, B, C_addr, row_A + new_size, col_A, row_B, col_B + new_size, new_size) + recur_multi(A, B, C_addr, row_A + new_size, col_A + new_size, row_B + new_size, col_B + new_size, new_size));
    }
    return 0;
}

void free_matrix(int ***matrix_addr, int a, int b)
{
    int i = 0, j = 0;
    for (i = 0; i < a; i++)
    {
        free((*matrix_addr)[i]); //각 행렬 동적할당해제
        (*matrix_addr)[i] = NULL;
    }
}
