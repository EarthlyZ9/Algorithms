//
// Created by Jisoo Lee on 2022/11/08.
//

#ifndef SIMPLEHASHTABLE_SIMPLEHASHTABLE_H
#define SIMPLEHASHTABLE_SIMPLEHASHTABLE_H

#include <stdio.h>
#include <stdlib.h>

typedef int KeyType;
typedef int ValueType;

typedef struct tagNode
{
    KeyType Key;
    ValueType Value;
} Node;

typedef struct tagHashTable
{
    int TableSize;
    Node* Table;
} HashTable;

// 함수 원형 선언
HashTable* SHT_CreateHashTable(int TableSize);
void SHT_Set(HashTable* HT, KeyType Key, ValueType Value);
ValueType SHT_Get(HashTable* HT, KeyType Key);
void SHT_DestroyHashTable(HashTable* HT);
int SHT_Hash(KeyType Key, int TableSize);

#endif //SIMPLEHASHTABLE_SIMPLEHASHTABLE_H
