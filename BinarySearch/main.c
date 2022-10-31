#include <stdio.h>
#include <stdlib.h>
#include "BinarySearch/Point.h"

int main(void) {
    int Length = sizeof DataSet / sizeof DataSet[0];
    printf("%.2f", DataSet[0].point);

    // 구매 포인트에 대해 오름차순 정렬
    qsort((void*)DataSet, Length, sizeof (Point), ComparePoint);

    Point* found = BinarySearch(DataSet, Length, 877.88);

    printf("found...Point: %f \n", found->point);

    return 0;
}
