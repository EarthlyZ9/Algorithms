//
// Created by Jisoo Lee on 2022/11/02.
//

#include "RedBlackTree.h"

extern RBTNode* Nil;

void      RBT_DestroyTree( RBTNode* Tree );

RBTNode*  RBT_CreateNode( ElementType NewData );
void      RBT_DestroyNode( RBTNode* Node );

RBTNode*  RBT_SearchNode( RBTNode* Tree, ElementType Target );
RBTNode*  RBT_SearchMinNode( RBTNode* Tree );

// 노드 삽입
void RBT_InsertNode( RBTNode** Tree, RBTNode *NewNode )
{
    RBT_InsertNodeHelper(Tree, NewNode);

    NewNode->Color = RED;
    NewNode->Left = Nil;
    NewNode->Right = Nil;

    RBT_RebuildAfterInsert(Tree, NewNode);
}

void      RBT_InsertNodeHelper( RBTNode** Tree, RBTNode *NewNode );
RBTNode*  RBT_RemoveNode( RBTNode** Root, ElementType Target );

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


void      RBT_RebuildAfterRemove( RBTNode** Root, RBTNode* X );

void      RBT_PrintTree( RBTNode* Node, int Depth, int BlackCount );
void      RBT_RotateLeft( RBTNode** Root, RBTNode* Parent );

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