#include <stdio.h>

int main() {
    float a = 333.14;
    printf("%f\n", a);
    printf("%2.1f\n", a);
    printf("%4.3lf\n", a);
    printf("%-f\n", a);
    printf("%-2.1f\n", a);
    printf("%-4.3lf\n", a);
    printf("%u\n", a);
    return 0;
};