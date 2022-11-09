//
// Created by Jisoo Lee on 2022/11/09.
//

#ifndef CHAININGHASHTABLE_CHAININGHASHTABLE_H
#define CHAININGHASHTABLE_CHAININGHASHTABLE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef char* KeyType;
typedef char* ValueType;

// 링크드 리스트의 노드
typedef struct tagNode
{
    KeyType Key;
    ValueType Value;
    struct tagNode* Next;
} Node;

// 링크드 리스트
typedef Node* List;

// 해시 테이블
typedef struct tagHashTable
{
    int TableSize;
    List* Table;
} HashTable;

// 함수 원형 선언
ValueType CHT_Get(HashTable* HT, KeyType Key);
void CHT_Set(HashTable* HT, KeyType Key, ValueType Value);
HashTable* CHT_CreateHashTable(int TableSize);
void CHT_DestroyHashTable(HashTable* HT);
Node* CHT_CreateNode(KeyType Key, ValueType Value);
void CHT_DestroyNode(Node* TargetNode);
void CHT_DestroyList(List ls);
int CHT_Hash(KeyType Key, int KeyLength, int TableSize);

#endif //CHAININGHASHTABLE_CHAININGHASHTABLE_H
