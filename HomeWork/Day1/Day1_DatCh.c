#include <stdio.h>


int main() {
    int a = 0;
    int week = 0;
    int day = 0;

    printf("Enter a number: ");
    scanf("%d", &a);
    printf("the Enter number is %d\n", a);
    week = a / 7;
    day = a % 7;

    printf("Week: %d\n", week);
    printf("Day: %d\n", day);

    return 0;
}
