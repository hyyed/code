#!/bin/bash

# username="${root166}"
username="192.168.32.166"
userpath=root/test
echo "Current user is $username"

# 检查参数数量
if [ "$#" -eq 1 ]; then
    # 获取文件名
    file=$1
    # 检查文件是否存在
    if [ ! -e "$file" ]; then
        echo "File $file does not exist"
        exit 1
    fi

elif [ "$#" -gt 1 ]; then
    file=$1
    # 检查文件是否存在
    if [! -e "$file" ]; then
        echo "File $file does not exist"
        exit 1
    fi
    userpath=$2

fi 

# 执行 scp 命令
scp -r "$file" $username:$userpath

# 检查 scp 命令是否成功
if [ "$?" -eq 0 ]; then
    echo "File $file successfully copied to ${username}:${userpath}"
else
    echo "Failed to copy $file to $username:$userpath"
fi

echo "Faild!!!"