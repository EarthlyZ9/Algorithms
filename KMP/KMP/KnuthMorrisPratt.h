//
// Created by Jisoo Lee on 2022/11/22.
//

#ifndef KMP_KNUTHMORRISPRATT_H
#define KMP_KNUTHMORRISPRATT_H

#include <stdio.h>
#include <stdlib.h>

// 함수 원형 선언
int KnuthMorrisPratt(char* Text, int TextSize, int Start, char* Pattern, int PatternSize);
void Preprocess(char* Pattern, int PatternSize, int* Border);

#endif //KMP_KNUTHMORRISPRATT_H
