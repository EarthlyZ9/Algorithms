//
// Created by Jisoo Lee on 2022/11/17.
//

#ifndef KARPRABIN_KARPRABIN_H
#define KARPRABIN_KARPRABIN_H

#include <math.h>
#include <stdio.h>

int KarpRabin(char* Text, int TextSize, int Start, char* Pattern, int PatternSize);
int Hash(char* String, int Size);
int ReHash(char* String, int Start, int Size, int HashPrev, int Coefficient);
/*
 * Coefficient: 거듭 제곱 값
 * 2 ^ (m-1) 의 값을 일일이 ReHash 함수 안에서 계산하기엔 비용이 큼
 */

#endif //KARPRABIN_KARPRABIN_H
