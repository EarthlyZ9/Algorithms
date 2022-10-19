//
// Created by Jisoo Lee on 2022/10/19.
//

#ifndef SEQUENTIALSEARCH_LINKEDLIST_H
#define SEQUENTIALSEARCH_LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct tagNode
{
    ElementType Data;
    struct tagNode* NextNode;
} Node;

// 함수 원형 선언
Node* SLL_CreateNode(ElementType NewData);
void  SLL_DestroyNode(Node* Node);
void  SLL_DestroyAllNodes(Node** List);
void  SLL_AppendNode(Node** Head, Node* NewNode);
void  SLL_InsertBefore(Node** Head, Node* Current, Node* NewNode);
void  SLL_InsertAfter(Node* Current, Node* NewNode);
void  SLL_InsertNewHead(Node** Head, Node* NewHead);
void  SLL_RemoveNode(Node** Head, Node* Remove);
Node* SLL_GetNodeAt(Node* Head, int Location);
int   SLL_GetNodeCount(Node* Head);


#endif //SEQUENTIALSEARCH_LINKEDLIST_H
