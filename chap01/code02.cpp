#include <stdio.h>

int main() {

    // slide page 7
    int x=1, y=2;
    int *ip;
    ip = &x;

    y = *ip;
    *ip = 0;


    // slide page 8
    int *pt1, *pt2;
    x = 3, y = 2;

    // 초기화되지 않은 포인터
    x = *pt1;   // wrong
    *pt1 = 12;  // wrong

    // 포인터의 초기화
    pt1 = 5;        // wrong
    pt1 = NULL;     // C style
    pt1 = nullptr;  // C++
    x = *pt1;       // wrong
    pt1 = &x;       // ok

    // 포인터 간의 치환
    pt2 = pt1;      // ok
    y = *pt2;

    return 0;
}

