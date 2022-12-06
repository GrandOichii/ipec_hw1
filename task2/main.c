#include <stdio.h>

int main() {
    int a = 1;

    unsigned int size = sizeof(a);
    unsigned int maxPow = 1<<(size*8-1);

    for(int i = 0; i < size * 8; ++i){
        printf("%u ",a&maxPow ? 1 : 0);
        a = a<<1;
    }
    printf("\n");
}