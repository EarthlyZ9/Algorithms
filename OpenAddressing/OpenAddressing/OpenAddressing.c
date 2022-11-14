//
// Created by Jisoo Lee on 2022/11/14.
//

#include "OpenAddressing.h"

// 해시 테이블 생성
HashTable* OAHT_CreateHashTable(int TableSize)
{
    HashTable* HT = (HashTable*)malloc(sizeof(HashTable));
    HT->Table = (ElementType*)malloc(sizeof(ElementType) * TableSize);

    // 모든 바이트를 특정 값으로 설정함 (배열)
    memset(HT->Table, 0, sizeof(ElementType) * TableSize);

    HT->TableSize = TableSize;
    HT->OccupiedCount = 0;

    return HT;
}

// 해시 테이블 제거
void OAHT_DestroyHashTable(HashTable* HT)
{
    // 각 링크드 리스트를 자유 저장소에서 제거하기
    int i = 0;
    for (i=0; i<HT->TableSize; i++)
    {
        OAHT_ClearElement(&(HT->Table[i]));
    }

    // 해시 테이블을 자유 저장소에서 제거하기
    free(HT->Table);
    free(HT);
}

// 주소의 데이터 제거
void OAHT_ClearElement(ElementType* Element)
{
    if (Element->Status == EMPTY)
        return;

    free(Element->Key);
    free(Element->Value);
}

// 데이터 삽입
void OAHT_Set(HashTable** HT, KeyType Key, ValueType Value)
{
    int KeyLen, Address, StepSize;
    double Usage;

    Usage = (double)(*HT)->OccupiedCount / (*HT)->TableSize;

    // 이 예제에서는 공간 사용률 임계치를 50% 로 설정함
    if (Usage > 0.5)
        OAHT_Rehash(HT);

    KeyLen = strlen(Key);
    Address = OAHT_Hash(Key, KeyLen, (*HT)->TableSize);
    StepSize = OAHT_Hash2(Key, KeyLen, (*HT)->TableSize);

    // 1차 해시 함수로 탐색했을 때 이미 차있는 상태이나 찾는 데이터가 아닐 때 -> 2차 해시 함수로 다른 주소에 저장되어 있음
    // 비어있는 자리 찾을 때까지 루프
    while ((*HT)->Table[Address].Status != EMPTY && strcmp((*HT)->Table[Address].Key, Key) != 0)
    {
        printf("Coliision occured: Key(%s), Address(%d), StepSize(%d)\n", Key, Address, StepSize);
        Address = (Address + StepSize) % (*HT)->TableSize;
    }

    // 자리 찾은 후 삽입 과
    (*HT)->Table[Address].Key = (char*)malloc(sizeof(char) * (KeyLen + 1));
    strcpy( (*HT)->Table[Address].Key, Key );

    (*HT)->Table[Address].Value = (char*)malloc(sizeof(char) * (strlen(Value) + 1));
    strcpy((*HT)->Table[Address].Value, Value);

    (*HT)->Table[Address].Status = OCCUPIED;

    (*HT)->OccupiedCount++;

    printf("Key(%s) entered at address(%d)\n", Key, Address );
}

// 데이터 탐색
ValueType OAHT_Get(HashTable* HT, KeyType Key)
{
    int KeyLen = strlen(Key);
    int Address = OAHT_Hash(Key, KeyLen, HT->TableSize);
    int StepSize = OAHT_Hash2(Key, KeyLen, HT->TableSize);

    // 1차 해시 함수로 탐색했을 때 이미 차있는 상태이나 찾는 데이터가 아닐 때 -> 2차 해시 함수로 다른 주소에 저장되어 있음
    // 데이터 찾을 때까지 루프
    while (HT->Table[Address].Status != EMPTY && strcmp(HT->Table[Address].Key, Key) != 0)
    {
        Address = (Address + StepSize) & HT->TableSize;
    }
    return HT->Table[Address].Value;
}

// 자릿수 접기로 만든 해시 함수
int OAHT_Hash(KeyType Key, int KeyLength, int TableSize)
{
    int i=0;
    int HashValue = 0;

    for (i=0; i<KeyLength; i++)
    {
        HashValue = (HashValue << 3) + Key[i];
    }

    HashValue = HashValue % TableSize;

    return HashValue;

}

// 자릿수 접기로 만든 2자 해시 함수
int OAHT_Hash2(KeyType Key, int KeyLength, int TableSize)
{
    int i=0;
    int HashValue = 0;

    for (i=0; i<KeyLength; i++)
    {
        HashValue = (HashValue << 2) + Key[i];
    }

    HashValue = HashValue % (TableSize - 3);

    return HashValue + 1;

}

// 재해싱
void OAHT_Rehash(HashTable** HT)
{
    int i = 0;
    ElementType* OldTable = (*HT)->Table;

    //  새 해시 테이블을 만들고,
    HashTable* NewHT = OAHT_CreateHashTable((*HT)->TableSize * 2);

    printf("\nRehashed. New table size is : %d\n\n", NewHT->TableSize);

    //  이전의 해시테이블에 있던 데이터를 새 해시테이블로 옮긴다.
    for (i=0; i<(*HT)->TableSize; i++)
    {
        if (OldTable[i].Status == OCCUPIED)
        {
            OAHT_Set(&NewHT, OldTable[i].Key, OldTable[i].Value);
        }
    }

    //  이전의 해시테이블은 소멸시킨다.
    OAHT_DestroyHashTable((*HT));

    //  HT 포인터에는 새로 해시테이블의 주소를 대입한다.
    (*HT) = NewHT;
}
