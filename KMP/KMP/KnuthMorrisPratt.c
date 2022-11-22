//
// Created by Jisoo Lee on 2022/11/22.
//

#include "KnuthMorrisPratt.h"

// 문자열을 순회하며 비교를 수행하다가 불일치 부분이 발견되면 패턴의 탐색 위치를 이동함
int KnuthMorrisPratt(char* Text, int TextSize, int Start, char* Pattern, int PatternSize)
{
    int i = Start;
    int j = 0;
    int Position = -1;

    // int 를 PatternSize + 1 개 만큼 저장할 수 있는 메모리 할당
    int* Border = (int*)calloc(PatternSize + 1, sizeof (int));

    // Border 에 경계 사전 정보 저장
    Preprocess(Pattern, PatternSize, Border);

    while (i < TextSize)
    {
        while (j >= 0 && Text[i] != Pattern[j])
            j = Border[j];

        i++;
        j++;

        if (j == PatternSize)
        {
            Position = i - j;
            break;
        }
    }
    free(Border);

    return Position;
}

/**
 * 경계 사전 정보 추출
 * @param Pattern 패턴
 * @param PatternSize 패턴 크기
 * @param Border 최대 경계 너비의 테이블을 가리키는 포인터
 */
void Preprocess(char* Pattern, int PatternSize, int* Border)
{
    int i = 0;
    int j = -1;

    // 경계 사전 정보 테이블의 첫번째 값은 항상 -1 임 (이전 문자열이 존재하지 않으므로)
    Border[0] = -1;

    // 최대 경계 넓이 탐색
    while (i < PatternSize)
    {
        while (j > -1 && Pattern[i] != Pattern[j])
            j = Border[j];

        i++;
        j++;

        Border[i] = j;
    }
}
