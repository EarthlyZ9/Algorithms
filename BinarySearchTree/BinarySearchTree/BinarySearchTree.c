//
// Created by Jisoo Lee on 2022/11/01.
//

#include "BinarySearchTree.h"

// 노드 생성
BSTNode* BST_CreateNode(ElementType NewData)
{
    BSTNode* NewNode = (BSTNode*) malloc(sizeof (BSTNode));
    NewNode->Left = NULL;
    NewNode->Right = NULL;

    NewNode->Data = NewData;
    return NewNode;
}

// 노드 제거
void BST_DestroyNode(BSTNode* Node)
{
    free(Node);
}

// 트리 제거
void BST_DestroyTree(BSTNode* Tree)
{
    if (Tree->Right != NULL)
        BST_DestroyTree(Tree->Right);
    if (Tree->Left != NULL)
        BST_DestroyTree(Tree->Left);

    Tree->Left = NULL;
    Tree->Right =NULL;
    BST_DestroyNode(Tree);
}

// 탐색 연산
BSTNode* BST_SearchNode(BSTNode* Tree, ElementType Target)
{
    if (Tree == NULL)
        return NULL;

    if (Tree->Data == Target)
        return Tree;
    else if (Tree->Data > Target)
        // 타겟보다 Data 가 크므로 왼편 탐색
        return BST_SearchNode(Tree->Left, Target);
    else
        // 타겟보다 Data 가 크므로 오른편 탐색
        return BST_SearchNode(Tree->Right, Target);
}


// 노드 삽입 연산
void BST_InsertNode(BSTNode* Tree, BSTNode* Child)
{
    // 새 노드가 현재 노드보다 큰 경우
    if (Tree->Data < Child->Data)
    {
        // 오른편에 자리가 있다면 삽입함
        if (Tree->Right == NULL)
            Tree->Right = Child;
        else
            // 오른편이 이미 차 있다면 오른편 자식을 기준으로 다시 검사함
            BST_InsertNode(Tree->Right, Child);
    }
    else if (Tree->Data > Child->Data)
    {
        // 왼편에 자리가 있다면 삽입함
        if (Tree->Left == NULL)
            Tree->Left = Child;
        else
            // 왼편이 이미 차 있다면 왼편 자식을 기준으로 다시 검사함
            BST_InsertNode(Tree->Left, Child);
    }
}

// 최솟값 노드 탐색
BSTNode* BST_SearchMinNode(BSTNode* Tree)
{
    if (Tree == NULL)
        return NULL;

    // 항상 왼쪽 자식이 더 작기 때문에 왼편에 대해서 재귀 호출함
    if (Tree->Left == NULL)
        return Tree;
    else
        return BST_SearchMinNode(Tree->Left);
}

// 노드 삭제 연산
BSTNode* BST_RemoveNode(BSTNode* Tree, BSTNode* Parent, ElementType Target)
{
    BSTNode* Removed = NULL;

    if (Tree == NULL)
        return NULL;

    if (Tree->Data > Target)
        Removed = BST_RemoveNode(Tree->Left, Tree, Target);
    else if (Tree->Data < Target)
        Removed = BST_RemoveNode(Tree->Right, Tree, Target);
    else
    {
        // 목표값을 찾은 경우
        Removed = Tree;

        // 잎 노드인 경우 바로 삭제
        if (Tree->Left == NULL && Tree->Right == NULL)
        {
            if (Parent->Left == Tree)
                Parent->Left = NULL;
            else
                Parent->Right = NULL;
        }
        else
        {
            // 자식이 양쪽 다 있는 경우
            if (Tree->Left != NULL && Tree->Right != NULL)
            {
                // 최솟값 노드를 찾아 제거한 뒤 현재의 노드에 위치시킴
                BSTNode* MinNode = BST_SearchMinNode(Tree->Right);
                MinNode = BST_RemoveNode(Tree, NULL, MinNode->Data);
                Tree->Data = MinNode->Data;
            }
            else
            {
                // 자식이 하나만 있는 경우
                BSTNode* Temp = NULL;
                if (Tree->Left != NULL)
                    Temp = Tree->Left;
                else
                    Temp = Tree->Right;

                if (Parent->Left == Tree)
                    Parent->Left = Temp;
                else
                    Parent->Right = Temp;
            }
        }
    }
    return Removed;
}

// 트리 출력
void BST_InorderPrintTree(BSTNode* Node)
{
    if (Node == NULL)
        return;

    // 왼쪽 하위 트리 출력
    BST_InorderPrintTree(Node->Left);

    // 뿌리 노드 출력
    printf("%d ", Node->Data);

    // 오른편 하위 트리 출력
    BST_InorderPrintTree(Node->Right);
}
