#include <stdio.h>

int main() {
    int a = 10;
    int b = 20;
    printf("a=%d, b=%d\n", a, b);

    printf("请输入a=:");
    scanf("%d%d", &a,&b);
    printf("a=%d, b=%d\n", a, b);

    char d[] = "hello world";
    char c[100] = "hello world";
    printf("\nc-size = %ld\n", sizeof(c));
    printf("c=%s\n", c);
    printf("请输入c=:");
    scanf("%s", c);
    printf("c=%s\n", c);

    while (getchar()!= '\n');

    printf("\nd = %s\n", d);
    printf("请输入d=:");
    scanf("%s", d);
    printf("d = %s\n", d);

    if(a > b) {
        printf("a > b\n");
    } else {
        return 2;
    }

    return 0;
}