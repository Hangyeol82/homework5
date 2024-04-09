#include <stdio.h>
#include <stdlib.h>

int r, c;                                           // r(행), c(열)은 모든 함수에서 같은 값으로 사용하기 때문에 전역변수로 선언

void print_matrix(int **x, int R, int C){           // 행렬을 출력하는 함수
    for(int i = 0 ; i < R; i ++){
        for(int j = 0 ; j < C ; j++){
            printf("%d ", x[i][j]);                 // 행렬의 각 원소를 출력 
        }   
        printf("\n");                               
    }
}
void free_matrix(int **x){
    int R = sizeof(x)/sizeof(x[0]);                 // 행렬의 행의 크기를 구함
    for(int i = 0 ; i < R ; i++){
        free(x[i]);                                 // 동적 할당받은 행의 열부분의 메모리 해제
    }
    free(x);                                        // 동적 할당받은 행의 행부분의 메모리 해제
}
void addition_matrix(int **x, int **y){
    int **M = (int**)malloc(sizeof(int*)*r);        // 더한 값을 저장할 행렬 M을 동적할당으로 생성
    for(int i = 0 ; i < r ; i++){
        M[i] = (int*)malloc(sizeof(int)*c);
    }
    for(int i = 0 ; i < r; i ++){
        for(int j = 0 ; j < c ; j++){
            M[i][j] = x[i][j] + y[i][j];            // 두 행렬의 각 원소를 더하여 M행렬에 대입
        }
    }
    print_matrix(M,r ,c);                           // M행렬을 출력
    free_matrix(M);                                 // M행렬의 메모리 해제
}
void subtract_matrix(int **x, int **y){
    int **M = (int**)malloc(sizeof(int*)*r);        // 뺀 값을 저장할 행렬 M을 동적할당으로 생성
    for(int i = 0 ; i < r ; i++){
        M[i] = (int*)malloc(sizeof(int)*c);         // M행렬의 열을 동적할당으로 생성
    }
    for(int i = 0 ; i < r; i ++){
        for(int j = 0 ; j < c ; j++){
            M[i][j] = x[i][j] - y[i][j];            // 두 행렬의 각 원소를 빼서 M행렬에 대입
        }
    }
    print_matrix(M, r, c);                          // M행렬을 출력     
    free_matrix(M);                                 // M행렬의 메모리 해제       
}   
void transpose_matrix(int **x){
    int **M = (int**)malloc(sizeof(int*)*r);        // 전치행렬을 저장할 행렬 M을 동적할당으로 생성
    for(int i = 0 ; i < c ; i++){
        M[i] = (int*)malloc(sizeof(int)*r);         // M행렬의 열을 동적할당으로 생성
    }
    for(int i = 0 ; i < c; i ++){
        for(int j = 0 ; j < r ; j++){
            M[i][j] = x[j][i];                      // 행렬의 행과 열을 바꾸어 M행렬에 대입
        }
    }
    print_matrix(M, c, r);                          // M행렬을 출력
    free_matrix(M);                                 // M행렬의 메모리 해제
}
void multiply_matrix(int **x, int **y){
    if(r != c){
        printf("행과 열의 크기가 같지 않습니다.\n");  
        return;                                     // 행과 열의 크기가 같지 않으면 행렬의 곱을 구할 수 없으므로 함수 종료
    }
    int **M = (int**)malloc(sizeof(int*)*r);        // 곱한 값을 저장할 행렬 M을 동적할당으로 생성
    for(int i = 0 ; i < r ; i++){
        M[i] = (int*)malloc(sizeof(int)*c);
    }
    for(int i = 0 ; i < r; i ++){
        for(int j = 0 ; j < c ; j++){
            int num = 0;                            // 계산한 값을 출력할 변수 생성 
            for(int k = 0 ; k < r ; k++){
                num+=x[i][k]*y[k][j];               // 계산한 값을 num변수에 더하여 행렬의 곱의 원소값을 구함
            }
            M[i][j] = num;                          // M행렬에 대입
        }
    }
    print_matrix(M, r, c);                          // M행렬을 출력
    free_matrix(M);                                 // M행렬의 메모리 해제
}

int main(){
    printf("----- [이한결]  [2021041055] -----\n");
    scanf("%d %d", &r, &c);
    int **A = (int**)malloc(sizeof(int*)*r);        // A 행렬의 행을 동적할당으로 생성
    for(int i = 0 ; i < r ; i++){
        A[i] = (int*)malloc(sizeof(int)*c);         // A 행렬의 열을 동적할당으로 생성
    }
    int **B = (int**)malloc(sizeof(int*)*r);        // B 행렬의 행을 동적할당으로 생성
    for(int i = 0 ; i < r ; i++){
        B[i] = (int*)malloc(sizeof(int)*c);         // B 행렬의 열을 동적할당으로 생성
    }
    for(int i = 0 ; i < r; i ++){
        for(int j = 0 ; j < c ; j++){
            A[i][j] = rand()%9+1;                   // A 행렬의 각 원소에 1~9 사이의 랜덤값을 대입
            B[i][j] = rand()%9+1;                   // B 행렬의 각 원소에 1~9 사이의 랜덤값을 대입
        }
    }
    print_matrix(A,r ,c);                           // A행렬을 출력
    print_matrix(B,r ,c);                           // B행렬을 출력        
    addition_matrix(A,B);                           // A행렬과 B행렬을 더함
    subtract_matrix(A,B);                           // A행렬과 B행렬을 뺌
    transpose_matrix(A);                            // A행렬의 전치행렬을 구함
    transpose_matrix(B);                            // B행렬의 전치행렬을 구함
    multiply_matrix(A,B);                           // A행렬과 B행렬을 곱함
    free_matrix(A);                                 // A행렬의 메모리 해제
    free_matrix(B);                                 // B행렬의 메모리 해제       
    return 0;
}