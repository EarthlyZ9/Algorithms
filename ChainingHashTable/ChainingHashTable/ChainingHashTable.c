//
// Created by Jisoo Lee on 2022/11/09.
//

#include "ChainingHashTable.h"

// 탐색
ValueType CHT_Get(HashTable* HT, KeyType Key)
{
    // 주소 해싱
    int Address = CHT_Hash(Key, strlen(Key), HT->TableSize);

    // 해싱한 주소의 링크드 리스트
    List ls = HT->Table[Address];
    List Target = NULL;

    if (ls == NULL)
        return NULL;

    // 순차 탐색
    while (1)
    {
        if (strcmp(ls->Key, Key) == 0)
        {
            Target = ls;
            break;
        }
        if (ls->Next == NULL)
            break;
        else
            ls = ls->Next;
    }
    return Target->Value;
}

// 삽입
void CHT_Set(HashTable* HT, KeyType Key, ValueType Value)
{
    int Address = CHT_Hash(Key, strlen(Key), HT->TableSize);
    Node* NewNode = CHT_CreateNode(Key, Value);

    // 해당 주소가 비어 있는 경우
    if (HT->Table[Address] == NULL)
        HT->Table[Address] = NewNode;
        // 비어 있지 않은 경우
    else
    {
        List ls = HT->Table[Address];
        NewNode->Next = ls;

        printf("Collision occurred: Key(%s), Address(%d)\n", Key, Address);
    }
}

// 해시 테이블 생성
HashTable* CHT_CreateHashTable(int TableSize)
{
    HashTable* HT = (HashTable*) malloc(sizeof(HashTable));
    HT->Table = (List*)malloc(sizeof(Node)*TableSize);

    // 모든 바이트를 특정 값으로 설정함 (배열)
    memset(HT->Table, 0, sizeof(List) * TableSize);

    HT->TableSize = TableSize;
    return HT;
}

// 해시 테이블 제거
void CHT_DestroyHashTable(HashTable* HT)
{
    // 각 링크드 리스트를 자유 저장소에서 제거
    int i = 0;
    for (i=0; i<HT->TableSize;i++)
    {
        List ls = HT->Table[i];
        CHT_DestroyNode(ls);
    }

    // 해시 테이블을 자유저장소에서 제거
    free(HT->Table);
    free(HT);
}

// 노드 생성
Node* CHT_CreateNode(KeyType Key, ValueType Value)
{
    Node* NewNode = (Node*) malloc(sizeof (Node));

    // 문자의 끝을 열리는 빈 바이트가 마지막에 붙음 (length  + 1)
    NewNode->Key = (char*) malloc(sizeof (char) * strlen(Key) + 1);
    strcpy(NewNode->Key, Key);

    NewNode->Value = (char*)malloc(sizeof(char) * strlen(Value) + 1);
    strcpy(NewNode->Value, Value);

    NewNode->Next = NULL;
    return NewNode;
}

// 노드 제거
void CHT_DestroyNode(Node* TargetNode)
{
    free(TargetNode->Key);
    free(TargetNode->Value);
    free(TargetNode);
}

// 링크드 리스트 제거
void CHT_DestroyList(List ls)
{
    if (ls == NULL)
        return;
    if (ls->Next != NULL)
        CHT_DestroyList(ls->Next);

    CHT_DestroyNode(ls);
}

// 해시 함수
int CHT_Hash(KeyType Key, int KeyLength, int TableSize)
{
    int i = 0;
    int HashValue = 0;

    for (i=0; i<KeyLength; i++)
    {
        HashValue = (HashValue << 3) + Key[i];
    }

    return HashValue % TableSize;
}

