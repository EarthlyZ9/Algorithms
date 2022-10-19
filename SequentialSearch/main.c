//
// Created by Jisoo Lee on 2022/10/19.
//

#include "LinkedList.h"

// 순차 탐색
Node* SLL_SequentialSearch(Node* Head, int Target)
{
    Node* Current = Head;
    Node *Match = NULL;

    while (Current != NULL)
    {
        if (Current->Data == Target)
        {
            Match = Current;
            break;
        }
        else
            Current = Current->NextNode;
    }
    return Match;
}

// 전진 이동법
Node* SLL_MoveToFront(Node** Head, int Target)
{
    Node* Current = (*Head);
    Node* Previous = NULL;
    Node* Match = NULL;

    while (Current != NULL)
    {
        // Target Data 를 찾았을 때
        if (Current->Data == Target)
        {
            Match = Current;
            if (Previous != NULL)
            {
                // 자신의 이전 노드의 다음 노드와 자신의 다음 노드를 연결함 (자신의 앞과 뒤 노드 연결)
                Previous->NextNode = Current->NextNode;
                // 맨 앞에 있던 노드를 자신의 다음 노드로 설정
                Current->NextNode = (*Head);
                // 맨 앞 노드를 자신으로 설정
                (*Head) = Current;
            }
            break;
        }
        else
        {
            Previous = Current;
            Current = Current->NextNode;
        }
    }
    return Match;
}

// 전위법
Node* SLL_Transpose(Node** Head, int Target)
{
    Node* Current = (*Head);
    Node* PPrevious = NULL;
    Node* Previous = NULL;
    Node* Match = NULL;

    while (Current != NULL)
    {
        if (Current->Data == Target)
        {
            Match == Current;
            if (Previous != NULL)
            {
                if (PPrevious != NULL)
                    // 이전 노드와 전전 노드가 둘 다 NULL 이 아닐 때
                    PPrevious->NextNode = Current;
                else
                    // 이전 노드는 NULL 이 아니지만 전전 노드가 NULL 일 때 (현재 노드가 두번째 노드임)
                    (*Head) = Current;

                Previous->NextNode = Current->NextNode;
                Current->NextNode = Previous;
            }
            break;
        }
        else
        {
            if (Previous != NULL)
                // 다음 노드로 넘어가면서 PPrevious 와 Previous 포인터 조정
                PPrevious = Previous;

            Previous = Current;
            Current = Current->NextNode;
        }
    }
    return Match;
}

int main( void )
{
    int   i       = 0;
    int   Count   = 10;
    Node* List    = NULL;
    Node* Current = NULL;
    Node* NewNode = NULL;
    Node* Match   = NULL;

    int   InitValue[10] = {1, 2, 6, 10, 4, 9, 5, 3, 8, 7};

    //  리스트 초기화
    for ( i = 0; i<Count; i++ )
    {
        NewNode = SLL_CreateNode(InitValue[i]);
        SLL_AppendNode(&List, NewNode);
    }

    // 순차 탐색
    printf("Simple Sequential Search...\n");

    Match =  SLL_SequentialSearch(List, 9);
    if (Match != NULL)
        printf("Found : %d\n", Match->Data);
    else
        printf("Not Found : %d\n", Match->Data);

    // 전진 이동법
    printf("Move To Front...\n");

    Match =  SLL_MoveToFront(&List, 4);
    if (Match != NULL)
        printf("Found : %d\n", Match->Data);
    else
        printf("Not Found : %d\n", Match->Data);

    // 전위법
    printf("Transpose...\n");

    Match =  SLL_Transpose(&List, 7);
    if (Match != NULL)
        printf("Found : %d\n", Match->Data);
    else
        printf("Not Found : %d\n", Match->Data);


    //  모든 노드를 메모리에서 제거
    printf("Destroying List...\n");

    for ( i = 0; i<Count; i++ )
    {
        Current = SLL_GetNodeAt(List, 0);

        if ( Current != NULL )
        {
            SLL_RemoveNode(&List, Current);
            SLL_DestroyNode(Current);
        }
    }

    return 0;
}
