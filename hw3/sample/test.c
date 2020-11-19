#include <stdio.h>
int main(){
    int a = 0, b = 0;
    if((((a = 1), b = 0))){
        a = 3;
    };
    printf("%d %d\n", a, b);
}