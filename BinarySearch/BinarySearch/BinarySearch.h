//
// Created by Jisoo Lee on 2022/10/31.
//


#ifndef BINARYSEARCH_POINT_H
#define BINARYSEARCH_POINT_H

typedef struct tagPoint {
    int id;
    double point;
} Point;

// 함수 원형 선언
Point* BinarySearch(Point PointList[], int Size, double Target);
int ComparePoint(const void *_elem1, const void *_elem2);

#endif //BINARYSEARCH_POINT_H