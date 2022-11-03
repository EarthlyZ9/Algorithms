//
// Created by Jisoo Lee on 2022/11/02.
//

#include "RedBlackTree.h"
#include <string.h>

extern RBTNode* Nil;

// 트리 제거
void RBT_DestroyTree(RBTNode* Tree)
{
    if ( Tree->Right != Nil )
        RBT_DestroyTree( Tree->Right );

    if ( Tree->Left != Nil )
        RBT_DestroyTree( Tree->Left );

    Tree->Left = Nil;
    Tree->Right = Nil;

    RBT_DestroyNode( Tree );

}

// 노드 생성
RBTNode*  RBT_CreateNode(ElementType NewData)
{
    RBTNode* NewNode = (RBTNode*)malloc(sizeof(RBTNode));
    NewNode->Parent  = NULL;
    NewNode->Left    = NULL;
    NewNode->Right   = NULL;
    NewNode->Data    = NewData;
    NewNode->Color   = BLACK;

    return NewNode;
}

// 노드 제거
void RBT_DestroyNode(RBTNode* Node)
{
    free(Node);
}

// 노드 탐색
RBTNode* RBT_SearchNode(RBTNode* Tree, ElementType Target)
{
    if (Tree == Nil)
        return NULL;


    if (Tree->Data > Target)
        // 타겟보다 클 때 왼쪽편 탐색
        return RBT_SearchNode (Tree->Left, Target);
    else if (Tree->Data < Target)
        // 타겟보다 작을 때 오른편 탐색
        return RBT_SearchNode (Tree->Right,  Target);
    else
        return Tree;
}

// 최솟값 노드 참색
RBTNode* RBT_SearchMinNode(RBTNode* Tree)
{
    if (Tree == Nil)
        return Nil;

    if (Tree->Left == Nil)
        return Tree;
    else
        return RBT_SearchMinNode( Tree->Left);

}

// 노드 삽입
void RBT_InsertNode(RBTNode** Tree, RBTNode *NewNode )
{
    RBT_InsertNodeHelper(Tree, NewNode);

    NewNode->Color = RED;
    NewNode->Left = Nil;
    NewNode->Right = Nil;

    RBT_RebuildAfterInsert(Tree, NewNode);
}

void RBT_InsertNodeHelper(RBTNode** Tree, RBTNode *NewNode)
{
    if ((*Tree) == NULL)
        (*Tree) = NewNode;

    // 새 노드가 현재 노드보다 큰 경우
    if ((*Tree)->Data < NewNode->Data)
    {
        // 오른편이 비어있을 때
        if ((*Tree)->Right == Nil)
        {
            (*Tree)->Right = NewNode;
            NewNode->Parent = (*Tree);
        }
        else
            // 오른편에 공간이 없을 때
            RBT_InsertNodeHelper((*Tree)->Right, NewNode);
    }
    else if ((*Tree)->Data > NewNode->Data)
    {
        // 왼편이 비어있을 때
        if ((*Tree)->Left == Nil)
        {
            (*Tree)->Left = NewNode;
            NewNode->Parent = (*Tree);
        }
        else
            // 왼편에 공간이 없을 때
            RBT_InsertNodeHelper((*Tree)->Left, NewNode);
    }
}

// 노드 삽입 후 후처리
void RBT_RebuildAfterInsert(RBTNode** Root, RBTNode* X)
{
    // 부모가 빨간색인 경우 계속 반복
    while (X != (*Root)  && X->Parent->Color == RED)
    {
        // 부모 노드가 할아버지 노드의 왼쪽 자식인 경우
        if (X->Parent == X->Parent->Parent->Left)
        {
            RBTNode* Uncle = X->Parent->Parent->Right;

            // Case 1: 삼촌 노드도 빨간색일 때
            if (Uncle->Color == RED)
            {
                // 부모와 삼촌 노드를 검은색, 할아버지 노드는 빨간색
                X->Parent->Color = BLACK;
                Uncle->Color = BLACK;
                X->Parent->Parent = RED;
            }
            else
            {   // Case 2: 삼촌 노드가 검은색이고 새로 삽입한 노드가 부모 노드의 오른쪽 노드일 때
                if (X == X->Parent->Right)
                {
                    // 부모를 기준으로 좌회전
                    X = X->Parent;
                    RBT_RotateLeft(Root, X);
                }

                // Case 3: 삼촌 노드가 검은색이고 새로 삽입한 노드가 부모 노드의 왼쪽 노드일 때

                // 부모 노드를 검은색, 할아버지 노드를 빨간색으로 칠함
                X->Parent->Color = BLACK;
                X->Parent->Parent->Color = RED;

                // 할아버지 노드를 기준으로 우회전
                RBT_RotateRight(Root, X->Parent->Parent);
            }
        }
        else // 부모 노드가 할아버지 노드의 왼쪽 자식인 경우
        {
            RBTNode* Uncle = X->Parent->Parent->Left;

            // Case 1: 삼촌 노드도 빨간색일 때
            if (Uncle->Color == RED)
            {
                // 부모와 삼촌 노드를 검은색, 할아버지 노드는 빨간색
                X->Parent->Color = BLACK;
                Uncle->Color = BLACK;
                X->Parent->Parent = RED;
            }
            else
            {   // Case 2: 삼촌 노드가 검은색이고 새로 삽입한 노드가 부모 노드의 왼쪽 노드일 때
                if (X == X->Parent->Left)
                {
                    // 부모를 기준으로 우회전
                    X = X->Parent;
                    RBT_RotateRight(Root, X);
                }

                // Case 3: 삼촌 노드가 검은색이고 새로 삽입한 노드가 부모 노드의 오른쪽 노드일 때

                // 부모 노드를 검은색, 할아버지 노드를 빨간색으로 칠함
                X->Parent->Color = BLACK;
                X->Parent->Parent->Color = RED;

                // 할아버지 노드를 기준으로 좌회전
                RBT_RotateLeft(Root, X->Parent->Parent);
            }
        }
    }
    (*Root)->Color = BLACK;
}

// 노드 삭제
RBTNode* RBT_RemoveNode(RBTNode** Root, ElementType Data)
{
    RBTNode* Removed = NULL;
    RBTNode* Successor = NULL;
    RBTNode* Target = RBT_SearchNode((*Root), Data);

    if (Target == NULL)
        return NULL;

    if (Target->Left == Nil || Target->Right == Nil)
        Removed = Target;
    else
    {
        Removed = RBT_SearchMinNode(Target->Right);
        Target->Data = Removed->Data;
    }

    if (Removed->Left != Nil)
        Successor = Removed->Left;
    else
        Successor = Removed->Right;

    Successor->Parent = Removed->Parent;

    if (Removed->Parent == NULL)
        (*Root) = Successor;
    else
    {
        if (Removed == Removed->Parent->Left)
            Removed->Parent->Left = Successor;
        else
            Removed->Parent->Right = Successor;
    }

    if (Removed->Color == BLACK)
        RBT_RebuildAfterRemove(Root, Successor);

    return Removed;
}

void RBT_RebuildAfterRemove(RBTNode** Root, RBTNode* Successor)
{
    RBTNode* Sibling = NULL;

    // Successor = 대체 노드 -> 이중 흑색 노드
    // 뿌리 노드가 아니고 이중 흑색 노드가 검은색에 머물러 있을 경우 루프
    while (Successor->Parent != NULL && Successor->Color == BLACK)
    {
        // 이중 흑색 노드가 부모 노드의 왼쪽 자식일 경우
        if (Successor == Successor->Parent->Left)
        {
            Sibling = Successor->Parent->Right;

            // 형제가 빨간색인 경우
            if (Sibling->Color == RED)
            {
                // 부모 노드를 빨간색으로, 형제 노드는 검은색으로
                // 부모 노드 기준 좌회전
                Sibling->Color = BLACK;
                Sibling->Parent->Color = RED;
                RBT_RotateLeft(Root, Successor->Parent);
            }
            // 형제가 검은색인 경우
            else
            {
                // 형제 노드의 양쪽 자식이 검은색인 경우
                if (Sibling->Left->Color == BLACK && Sibling->Right->Color == BLACK)
                {
                    // 검은색을 부모로 옮기고, 형제 노드는 빨간색으로 칠함
                    Sibling->Color = RED;
                    Successor = Successor->Parent;
                }
                else {
                    // 형제 노드의 왼쪽 자식이 빨간색인 경우
                    if (Sibling->Left->Color == RED)
                    {
                        // 형제 노드는 빨간색으로, 그 왼쪽 자식은 검은색으로
                        // 형제 노드 기준으로 우회전
                        Sibling->Color = RED;
                        Sibling->Left->Color = BLACK;
                        RBT_RotateRight(Root, Sibling);
                        Sibling = Successor->Parent->Right;
                    }

                    // 형제 노드의 오른쪽 자식이 빨간색인 경우
                    Sibling->Color = Successor->Parent->Color;
                    Successor->Parent->Color = BLACK;
                    Sibling->Right->Color = BLACK;
                    RBT_RotateLeft(Root, Successor->Parent);
                    Successor = (*Root);
                }
            }
        }
        else // 이중 흑색 노드가 부모 노드의 오른쪽 자식인 경우
        {
            Sibling = Successor->Parent->Left;

            // 형제가 빨간색인 경우
            if (Sibling->Color == RED)
            {
                // 부모 노드를 빨간색으로, 형제 노드는 검은색으로
                // 부모 노드 기준 우회전
                Sibling->Color = BLACK;
                Sibling->Parent->Color = RED;
                RBT_RotateRight(Root, Successor->Parent);
            }
                // 형제가 검은색인 경우
            else
            {
                // 형제 노드의 양쪽 자식이 검은색인 경우
                if (Sibling->Right->Color == BLACK && Sibling->Left->Color == BLACK)
                {
                    // 검은색을 부모로 옮기고, 형제 노드는 빨간색으로 칠함
                    Sibling->Color = RED;
                    Successor = Successor->Parent;
                }
                else {
                    // 형제 노드의 오른쪽 자식이 빨간색인 경우
                    if (Sibling->Right->Color == RED)
                    {
                        // 형제 노드는 빨간색으로, 그 왼쪽 자식은 검은색으로
                        // 형제 노드 기준으로 좌회전
                        Sibling->Color = RED;
                        Sibling->Right->Color = BLACK;
                        RBT_RotateLeft(Root, Sibling);
                        Sibling = Successor->Parent->Left;
                    }

                    // 형제 노드의 오른쪽 자식이 빨간색인 경우
                    Sibling->Color = Successor->Parent->Color;
                    Successor->Parent->Color = BLACK;
                    Sibling->Right->Color = BLACK;
                    RBT_RotateLeft(Root, Successor->Parent);
                    Successor = (*Root);
                }
            }
        }
    }
}

void RBT_PrintTree(RBTNode* Node, int Depth, int BlackCount)
{
    int   i = 0;
    char c = 'X';
    int  v = -1;
    char cnt[100];

    if (Node == NULL || Node == Nil)
        return;

    if (Node->Color == BLACK)
        BlackCount++;

    if (Node->Parent != NULL)
    {
        v = Node->Parent->Data;

        if (Node->Parent->Left == Node)
            c = 'L';
        else
            c = 'R';
    }

    if (Node->Left == Nil && Node->Right == Nil)
        sprintf(cnt, "--------- %d", BlackCount );
    else
        strncpy(cnt, "", sizeof(cnt));

    for (i = 0; i < Depth; i++)
        printf("  ");

    printf("%d %s [%c,%d] %s\n", Node->Data,
            (Node->Color == RED)?"RED":"BLACK", c, v, cnt);

    RBT_PrintTree(Node->Left, Depth+1, BlackCount);
    RBT_PrintTree(Node->Right, Depth+1, BlackCount);
}

// 좌회전
void RBT_RotateLeft( RBTNode** Root, RBTNode* Parent )
{
    // 오른쪽 자식 노드
    RBTNode* RightChild = Parent->Right;

    // 오른쪽 자식 노드의 왼쪽 노드를 부모 노드의 오른쪽 자식으로 등록함
    Parent->Right = RightChild->Left;

    // 오른쪽 자식 노드의 왼쪽 노드가 nil 이 아니면
    if (RightChild->Left != Nil)
        RightChild->Left->Parent = Parent;

    RightChild->Parent = Parent->Parent;

    // 부모가 NULL 이라면 이 RightChild 는 루트가 됨
    if (Parent->Parent == NULL)
        (*Root) = RightChild;
    else
    {
        if (Parent == Parent->Parent->Left)
            Parent->Parent->Left = RightChild;
        else
            Parent->Parent->Right = RightChild;
    }
    RightChild->Left = Parent;
    Parent->Parent = RightChild;
}

// 우회전
void RBT_RotateRight(RBTNode** Root, RBTNode* Parent)
{
    // 왼쪽 자식 노드
    RBTNode* LeftChild = Parent->Left;

    // 왼쪽 자식 노드의 오른쪽 노드를 부모 노드의 왼쪽 자식으로 등록함
    Parent->Left = LeftChild->Right;

    // 왼쪽 자식 노드의 오른쪽 노드가 nil 이 아니면
    if (LeftChild->Right != Nil)
        LeftChild->Right->Parent = Parent;

    LeftChild->Parent = Parent->Parent;

    // 부모가 NULL 이라면 이 LeftChild 는 루트가 됨
    if (Parent->Parent == NULL)
        (*Root) = LeftChild;
    else
    {
        if (Parent == Parent->Parent->Left)
            Parent->Parent->Left = LeftChild;
        else
            Parent->Parent->Right = LeftChild;
    }
    LeftChild->Right = Parent;
    Parent->Parent = LeftChild;
}