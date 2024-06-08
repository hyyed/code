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
        return -1;
    }

    // 读取文件内容
    char buffer[256] = {0};
    int length = read(fd, buffer, sizeof(buffer) - 1);
    if (length < 0) {
        perror("read error");
        close(fd);
        return -1;
    }

    // 查找密码位置
    char* colon_pos = strchr(buffer, ':');
    if (!colon_pos) {
        printf("文件格式错误!\n");
        close(fd);
        return -1;
    }

    // 计算用户名长度
    int user_length = colon_pos - buffer;

    // 输入新密码
    char newPassword[64] = {0};
    printf("请输入修改后的密码：");
    scanf("%s", newPassword);

    // 构造新文件内容
    int new_length = user_length + 1 + strlen(newPassword);
    char new_buffer[256] = {0};
    strncpy(new_buffer, buffer, user_length + 1);
    strncpy(new_buffer + user_length + 1, newPassword, sizeof(new_buffer) - user_length - 1);

    // 清空旧文件内容
    ftruncate(fd, 0);

    // 将新内容写回文件
    lseek(fd, 0, SEEK_SET);
    write(fd, new_buffer, new_length);

    close(fd);
    return 0;
}
