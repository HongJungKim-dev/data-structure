#include <stdio.h>
#include <stdlib.h>

typedef int Data;
typedef struct _node
{
    Data data;
    struct _node *next;
} Node;
int main()
{
    Node *head = NULL;
    Node *current = NULL;
    Node *new = NULL;
    Node *tail = NULL;
    Data data = 0;
    Data del = 0;
    Node *del_node = NULL;
    Node *keep_node = NULL;
    int length = 0;
    Node *delNode = NULL;
    Node *delNextNode = NULL;

    printf("head의 data : %d입니다.\n", head->data);
    printf("head의 data : %d입니다.\n", head);
    printf("head의 next : %p입니다.\n", head->next);
    printf("head의 next : %p입니다.\n", head);

    head = current;

    while (1)
    {

        printf("자연수 입력: ");
        scanf("%d", &data);
        if (data < 1)
        {
            break;
        }
        //방법1. 추가 순서 유지, 처음과 그 이외의 경우 구분하기 위해 length 변수 이용
        new = (Node *)malloc(sizeof(Node));
        new->data = data;
        new->next = NULL;
        if (length == 0)
        {
            head = new;
            current = head;
            length++;
            continue;
        }
        current->next = new;
        length++;
        current = current->next;
        //방법2. 추가 순서 유지, 처음과 그 이외의 경우 구분하기 위해 널 여부로 판단
        new = (Node *)malloc(sizeof(Node));
        new->data = data;
        new->next = NULL;
        if (head == NULL)
        {
            head = new;
            tail = head;
        }
        else
        {
            tail->next = new;
            //tail = tail->next; tail = new와 동일
            tail = new;
        }
        //방법3. 추가 순서 역순

        //새 노드 생성
        new = (Node *)malloc(sizeof(Node));
        new->data = data;
        new->next = NULL;

        //연결
        new->next = head;
        head = new;
    }

    printf("입력 받은 데이터의 전체 출력!\n");
    while (current != NULL)
    {
    }
    if (head == NULL)
    {
        printf("저장된 자연수가 존재하지 않습니다. \n");
    }
    else
    {
        //방법1
        current = head;
        while (current != NULL)
        {
            printf("%d ", current->data);
            current = current->next;
        }
        //방법2
        current = head;
        printf("%d ", current->data);
        while (current->next != NULL)
        {
            current = current->next;
            printf("%d ", current->data);
        }
    }
    printf("\n");
    //방법1.
    current = head;
    while (current != NULL)
    {
        keep_node = current->next;
        del_node = current;
        del = del_node->data;
        printf("%d을(를) 삭제합니다.\n", del);

        free(del_node);
        del_node = NULL;

        head = keep_node;
        current = head;
    }
    if (head == NULL)
    {
        return 0;
    }
    else
    {
        delNode = head;
        delNextNode = delNode->next;
        printf("%d을(를) 삭제합니다. \n", delNode->data);
        free(delNode);
        delNode = NULL;

        while (delNextNode != NULL)
        {
            delNode = delNextNode;
            delNextNode = delNode->next;

            printf("%d을(를) 삭제합니다. \n", delNode->data);
            free(delNode);
            delNode = NULL;
        }
    }
    //거꾸로 삭제도 해보기
}