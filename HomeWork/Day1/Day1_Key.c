#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char key[] = "\0";
static int  temp = 0;

int main() {

    while(1) {
        char key[] = "hello\0world";
        temp = 0;
        
        int is_alpha = 1;
        int is_digit = 1;

        /* 1.input_key(); */
        printf("请输入大小写字母或其对应的ASCII码(65-90为大写字母，97-122为小写字母)!\n");
        scanf("%s", key);

        printf("input = %s\n", key);
        printf("sizeof: %ld\n", sizeof(key)); //sizeof函数返回变量的（字节数？）
        printf("strlen: %ld\n", strlen(key)); //str开头的函数返回字符串的长度，不包括结尾的\0，碰到\0就返回字符串的长度

        /* 2.判断是否为字母或数字 */
        for (int i = 0; i < strlen(key); i++) 
        {
            if (!isalpha(key[i])) // 判断是否为字母
            { 
                is_alpha = 0;
            }
            if(!isdigit(key[i])) // 判断是否为数字
            { 
                is_digit = 0;
            }
        }

        temp = atoi(key); // 字符串转换为数字
        printf("atoi: %d\n", temp);
        
        /* 3.转换输出 */
        if (is_alpha) 
        {  
            temp = key[0];
            printf("%c的ASSIC码为%d\n", key[0], temp);
            break;
        } 
        else if (is_digit) 
        { 
            temp = atoi(key); // 字符串转换为数字
            if ((temp >= 65 && temp <= 90) || (temp >= 97 && temp <= 122)) 
            {
                printf("%d的对应的字母为%c\n", temp, temp);
                break;
            } 
            else 
            {
                printf("\"%d\"不再指定ASCII码范围!\n", temp);
                printf("请重新输入!\n\n");
            }
        } 
        else 
        {
            printf("\"%s\"不是字母或数字\n", key); 
            printf("请重新输入!\n\n");
        }
    }
    return 0;
}