//
// Created by Jisoo Lee on 2022/11/25.
//

#include "BoyerMoore.h"
#include <stdlib.h>

/**
 * 보이어-무어 알고리즘 구현
 * @param Text 본문
 * @param TextSize 본문 크기
 * @param Start 시작 지점
 * @param Pattern 패턴 (찾고자 하는 문자열)
 * @param PatternSize 패턴의 크기
 * @return 패턴의 위치
 */
int BoyerMoore(char* Text, int TextSize, int Start, char* Pattern, int PatternSize)
{
    int BadCharTable[128]; // 나쁜 문자열 테이블, 모든 문자를 담을 수 있는 테이블 문자 128개
    int* GoodSuffixTable = (int*) calloc(PatternSize + 1, sizeof(int));  // 착한 접미부 테이블
    int* BorderPos = (int*) calloc(PatternSize + 1, sizeof(int));  // 접미부의 가장 넓은 경계의 시작 위치
    int i = Start;
    int j = 0;

    int Position = -1;

    BuildBCT(Pattern, PatternSize, BadCharTable);
    BuildGST(Pattern, PatternSize, BorderPos, GoodSuffixTable);

    while (i <= TextSize - PatternSize)
    {
        // 보이어-무어 알고리즘에서는 패턴을 오른쪽에서 왼쪽으로 탐색함
        j = PatternSize - 1;
        while (j >= 0 && Pattern[j] == Text[i+j])
            j--;

        if (j < 0)
        {
            Position = 1;
            break;
        }
        else
        {
            // 착한 접미부 이동과 나쁜 문자열 이동 중 더 큰 이동 거리만큼 이동
            i+= Max(GoodSuffixTable[j+1], j-BadCharTable[Text[i+j]]);
        }
    }
    free(BorderPos);
    free(GoodSuffixTable);

    return Position;
}

/**
 * 착한 접미부 테이블 생성
 * @param Pattern 패턴
 * @param PatternSize 패턴의 크기
 * @param BorderPos 접미부의 가장 넓은 경계의 시작 위치
 * @param GST 착한 접미부 테이블
 */
void BuildGST(char* Pattern, int PatternSize, int* BorderPos, int* GST)
{
    // 첫번째 경우: 본문의 착한 접미부와 동일한 문자열이 패턴의 나머지 부분에 존재할 때
    int i = PatternSize;
    int j = PatternSize + 1;

    // 빈 접미부일 때
    BorderPos[i] = j;

    // 패턴의 길이만큼 반복
    while (i>0)
    {
        // 패턴에서 경계 찾기
        while (j <= PatternSize && Pattern[i-1] != Pattern[j-1])
        {
            if (GST[j] == 0)
                GST[j] = j - 1;

            j = BorderPos[j];
        }
        i--;
        j--;

        // 찾아낸 경계의 시작점 저장
        BorderPos[i] = j;
    }

    // 두번째 경우
    j = BorderPos[0];
    for (i = 0; i <=PatternSize; i++)
    {
        if (GST[i] == 0)
            GST[i] = j;  // 이동거리가 0인 항목에 대해서면 첫 '접미부의 가장 넓은 경계의 시작 위치' 입력

        if (i == j)
            j = BorderPos[j];
    }
}

/**
 * 나쁜 문자열 테이블 생성
 * @param Pattern 패턴
 * @param PatternSize 패턴 크기
 * @param BST 나쁜 문자열 테이블
 */
void BuildBCT(char* Pattern, int PatternSize, int* BCT)
{
    int i;
    int j;

    for (i = 0; i < 128; i++)
        BCT[i] = -1;

    for (j = 0; j < PatternSize; j++)
        BCT[Pattern[j]] = j;
}


int Max(int A, int B)
{
    if (A > B)
        return A;
    else
        return B;
}
