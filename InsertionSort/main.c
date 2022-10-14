#include <stdio.h>
#include <string.h>


void InsertionSort(int DataSet[], int Length) 
{ 
    int i = 0; 
    int j = 0; 
    int value = 0; 
 
    for ( i=1; i<Length; i++ ) 
    { 
        // 현재 요소의 값이 오른쪽 요소의 값보다 작거나 클 때에는 비교할 필요가 없음
        if ( DataSet[i-1] <= DataSet[i] ) 
            continue; 

        // 현재 요소의 값이 오른쪽 요소의 값보다 클 때에는 비교하여 정렬해야함
        value = DataSet[i]; 
 
        // 정렬 범위: 현재 요소와 0 ~ i -1 까지 
        for ( j=0; j<i; j++ )  
        {             
            if (DataSet[j] > value)  
            { 
                // 메모리의 내용을 이동시킴
                // 첫번째 매개변수: 원본 데이터가 옮겨갈 새로운 메모리의 주소
                // 두번째 매개변수: 원본 데이터가 있는 주소
                // 세번째 매개변수: 이동할 데이터 양
                memmove(&DataSet[j+1], &DataSet[j], sizeof(DataSet[0]) * (i-j)); 
                DataSet[j] = value; 
                break;     
            } 
        } 
    } 
} 
 
int main( void ) 
{ 
    int DataSet[] = {6, 4, 2, 3, 1, 5}; 
    int Length = sizeof DataSet / sizeof DataSet[0];     
    int i = 0; 
 
    InsertionSort(DataSet, Length); 
 
    for ( i=0; i<Length; i++ ) 
    { 
        printf("%d ", DataSet[i]); 
    } 
 
    printf("\n"); 
 
    return 0; 
}