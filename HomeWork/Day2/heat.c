#include <stdio.h>

int main() {
    float   inputF=12.1;
    char   arrF[8];
    float   outputC;

    printf("Enter temperature in Fahrenheit: ");
    // scanf("%f", &inputF);
    fgets(arrF,4, stdin);
    printf("%s\n", arrF);

    printf("Enter temperature in Fahrenheit: ");
    fgets(arrF,4, stdin);
    printf("%s\n", arrF);

    outputC = 5*(inputF - 32)/9; //华氏度转温度

    printf("Temperature in Celsius: ");
    printf("%.2f\n", outputC);
    return 0;
}