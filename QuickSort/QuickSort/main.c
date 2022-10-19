#include <stdio.h>

void Swap(int* A, int* B)
{
    int Temp = *A;
    *A = *B;
    *B = Temp;
}

int Partition(int DataSet[], int Left, int Right)
{
    // Left 와 Right 는 왼쪽과 오른쪽 요소의 인덱스 값임
    int First = Left;

    // 기준 요소를 정렬 대상의 첫 요소로 잡음
    int Pivot = DataSet[First];

    // 기준 요소의 다음 요소부터 비교 시작
    ++Left;

    while(Left <= Right)
    {
        // 기준 요소보다 큰 요소를 만날 때까지 오른쪽으로 한칸씩 이동
        // 오른쪽에서 오는 요소와 만나기 직전까지
        while (DataSet[Left] <= Pivot && Left < Right)
            ++Left;

        // 기준 요소보다 작은 요소를 만날 때까지 왼쪽으로 한칸씩 이동
        // Left 와 Right 가 나란히 있을 때 둘이 자리를 바꾼 뒤,
        // Right를 한번 더 왼쪽으로 이동하여 Left 와 포갬
        // 그 다음에 기준 요소와 Right 자리의 요소를 Swap
        while (DataSet[Right] >= Pivot && Left <= Right)
            --Right;

        if (Left < Right)
            Swap(&DataSet[Left], &DataSet[Right]);
        else
            break;
    }
    Swap(&DataSet[First], &DataSet[Right]);

    return Right;
}

void QuickSort(int DataSet[], int Left, int Right)
{
    if ( Left < Right )
    {
        int Index = Partition(DataSet, Left, Right);

        QuickSort( DataSet, Left, Index - 1 );
        QuickSort( DataSet, Index + 1, Right );
    }
}

int main( void )
{
    int DataSet[] = {6, 4, 2, 3, 1, 5};
    int Length = sizeof DataSet / sizeof DataSet[0];
    int i = 0;

    QuickSort( DataSet, 0, Length-1 );

    for ( i=0; i<Length; i++ )
    {
        printf("%d ", DataSet[i]);
    }

    printf("\n");

    return 0;
}
