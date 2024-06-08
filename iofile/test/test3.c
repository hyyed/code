#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>

/*
    - 编写一个注册的程序
    - 用户输入：用户名
    - 用户输入：密码
    - 把用户和密码存储在文件中, 比如  hqd:123
    - 程序可以修改密码比如：hqd:123456
*/



bool SetData(const char* filename);
bool ResetPassword(const char* filename);

int main() {

    const char* dir_name = "./filetest";
    const char* filename = "./filetest/userinfo.txt";

    // 检测目录
    DIR* dir = opendir(dir_name);
    if (dir) {
        closedir(dir);
    } else {
        printf("没有%s目录, 即将创建!\n", dir_name);
        if (0 == mkdir(dir_name, 0755)) {
            printf("目录创建成功!\n");
        } else {
            printf("目录创建失败!");
            goto err;
        }
    }

    // 输入用户和密码
    if (0 == SetData(filename)) {
        printf("数据保存成功!\n");
    } else {
        printf("数据保存失败!");
        goto err;
    }

    // 重置密码
    if (0 == ResetPassword(filename)) {
        printf("密码重置成功!\n");
    } else {
        printf("密码重置失败!\n");
        goto err;
    }
    
    return 0;

err:
    return -1;
}

// 输入用户和密码
bool SetData(const char* filename) {
    // 打开文件
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (-1 == fd) {
        perror("open error");
        return -1;
    }

    // 输入用户名和密码
    char user[64] = {0};
    char password[64] = {0};
    char ch = ':';
    printf("请输入用户名：");
    scanf("%s", user);
    while (getchar() != '\n');
    printf("请输入密码：");
    scanf("%s", password);

    // 输入写入文件
    write(fd, user, strlen(user));
    write(fd, &ch, 1);
    write(fd, password, strlen(password));

    close(fd);
    return 0;
}

// 重置密码
bool ResetPassword(const char* filename) {

    // 打开文件，读写
    int fd = open(filename, O_RDWR);
    if (-1 == fd) {
        perror("open error");
        return 0;
    }

    // 读取到密码位置
    char ch = '#';
    int cntSeek = 0;
    while (1 && ch != '\0') {
        cntSeek++;
        read(fd, &ch, 1);
        if (ch == ':')
            break;
    }

    // 计算旧密码长度
    int cntPassLength = 0;
    while (1) {
        int red = read(fd, &ch, 1);
        if (1 != red) {
            break;
        }
        cntPassLength++;
    }

    // 输入新秘密
    char newPassword[64] = {0};
    printf("请输入修改后的密码：");
    scanf("%s", newPassword);

    // 清空旧密码，
    char empty[64]={0};
    // for(int i=0; i<sizeof(empty); i++) {
    //     empty[i] = '\0';
    // }
    lseek(fd, cntSeek, SEEK_SET);
    write(fd, empty, cntPassLength);

    // 写入新密码
    lseek(fd, cntSeek, SEEK_SET);
    while (getchar() != '\n');
    write(fd, newPassword, strlen(newPassword));

    close(fd);
    return 0;
}


