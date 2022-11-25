//
// Created by Jisoo Lee on 2022/11/25.
//

#ifndef BOYERMOORE_BOYERMOORE_H
#define BOYERMOORE_BOYERMOORE_H

#include <stdio.h>

// 함수 원형 선언
int BoyerMoore(char* Text, int TextSize, int Start, char* Pattern, int PatternSize);
void BuildGST(char* Pattern, int PatternSize, int* Suffix, int* GST);
void BuildBCT(char* Pattern, int PatternSize, int* BCT);
int Max(int A, int B);

#endif //BOYERMOORE_BOYERMOORE_H
