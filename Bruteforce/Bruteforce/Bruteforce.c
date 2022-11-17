//
// Created by Jisoo Lee on 2022/11/17.
//

#include "Bruteforce.h"

int BruteForce(char* Text, int TextSize, int Start, char* Pattern, int PatternSize)
{
    int i = 0;
    int j = 0;

    // 시작 위치에서부터 TextSize - PatternSize 위치까지 순회
    for (i = Start; i <= TextSize - PatternSize; i++)
    {
        for (j = 0; j < PatternSize; j++)
        {
            // PatternSize 만큼 Text 를 순회하여 Text 와 Pattern 비교
            if (Text[i+j] != Pattern[j])
                break;
        }
        // break 되지 않고 j 가 PatternSize 보다 크거나 같은 상황까지 도달한다면 Pattern 을 찾은 것임
        if (j >= PatternSize)
            return i;
    }
    return -1;
}
