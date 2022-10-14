#include <stdio.h>

void BubbleSort(int DataSet[], int Length)
{
    int i = 0;
    int j = 0;
    int temp = 0;

    // 배열의 길이가 n 이라면 n-1 번의 순회를 함
    for (i = 0; i < Length - 1; i++)
    {
        // 내부 for 문은 반복횟수가 줄어듦 
        // 외부 for 문이 실행될 때마다 정렬 대상으로 삼는 자료구조의 범위가 줄어들기 때문
        for (j = 0; j < Length - (i + 1); j++)
        {
            if (DataSet[j] > DataSet[j+1])
            {
                // 삽입하고 뒤에 요소들 한 칸씩 밀기
                temp = DataSet[j + 1];
                DataSet[j + 1] = DataSet[j];
                DataSet[j] = temp;
            }
        }
    }
}

int main(void)
{
    int DataSet[] = {6, 4, 2, 3, 1, 5};
    int Length = sizeof DataSet / sizeof DataSet[0];
    int i = 0;

    BubbleSort(DataSet, Length);

    for (i = 0; i < Length; i++)
    {
        printf("%d ", DataSet[i]);
    }
    printf("\n");

    return 0;
}