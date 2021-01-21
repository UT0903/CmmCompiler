#include <stdio.h>
#include <stdint.h>
#include <limits.h>
int FloatToInt (float f){
    union {
        float f;
        uint32_t u;
    } fu = { .f = f };
    int i = sizeof f * CHAR_BIT;
    unsigned int ret = 0;
    while (i--){
        ret = ret << 1;
        ret += ((fu.u >> i) & 0x1);
    }
    return (int)ret;
}
int main(){
    float a;
    scanf("%f", &a);
    printf("%d\n", FloatToInt(a));
}