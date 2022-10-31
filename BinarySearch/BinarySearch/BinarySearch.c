//
// Created by Jisoo Lee on 2022/10/31.
//

#include "BinarySearch.h"

Point* BinarySearch(Point PointList[], int Size, double Target) {
    int Left, Right, Mid;
    Left = 0;
    Right = Size - 1;
    while (Left <= Right)
    {
        Mid = (Left + Right / 2);

        if (Target == PointList[Mid].point)
            return &(PointList[Mid]);
        else if (Target > PointList[Mid].point)
            // target 이 더 크다면 오른편에서 다시 이진 탐색 수행
            Left = Mid + 1;
        else
            // target 이 더 크다면 왼편에서 다시 이진 탐색 수행
            Right = Mid - 1;
    }
//    return NULL;
}

int ComparePoint(const void *_elem1, const void *_elem2)
{
    Point* elem1 = (Point*)_elem1;
    Point* elem2 = (Point*)_elem2;

    if (elem1->point > elem2->point)
        return 1;
    else if (elem1->point < elem2->point)
        return -1;
    else
        return 0;
}