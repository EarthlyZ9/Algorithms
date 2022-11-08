//
// Created by Jisoo Lee on 2022/11/08.
//

#include "SimpleHashTable.h"

// 해시테이블 생성
HashTable* SHT_CreateHashTable(int TableSize)
{
    HashTable* HT = (HashTable*)malloc(sizeof(HashTable));
    HT->Table = (Node*)malloc(sizeof(Node)*TableSize);
    HT->TableSize = TableSize;

    return HT;
}

// 해시테이블에 데이터 삽입
void SHT_Set(HashTable* HT, KeyType Key, ValueType Value)
{
    int Address = SHT_Hash(Key, HT->TableSize);

    HT->Table[Address].Key = Key;
    HT->Table[Address].Value = Value;
}

// 해시테이블에서 데이터 접근하기
ValueType SHT_Get(HashTable* HT, KeyType Key)
{
    int Address = SHT_Hash(Key, HT->TableSize);
    return HT->Table[Address].Value;
}

// 해시 테이블 제거
void SHT_DestroyHashTable(HashTable* HT)
{
    free(HT->Table);
    free(HT);
}

// 해시 함수
int SHT_Hash(KeyType Key, int TableSize)
{
    return Key % TableSize;
}