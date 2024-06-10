@echo off
ssh -V
echo.
ssh -V >nul 2>&1
chcp 936 >nul

REM 设置私有密钥地址
REM set private_key=C:\Users\Libubai\.ssh\id_rsa
set private_key=~\.ssh\id_rsa
echo 私有密钥地址%private_key%

set HOST131=192.168.32.133
set HOST132=192.168.32.132
set HOSTBrd=192.168.172.166
set USERNAME_Lunux=even
set USERNAME_Board=root
set PASSWORD=123

:begin
chcp 936
echo.****************************************************
echo.*                                                  *
echo.*       0、%USERNAME_Lunux%@%HOST133%                     *
echo.*       1、%USERNAME_Lunux%@%HOST132%                     *
echo.*       2、%USERNAME_Board%@%HOSTBrd%                    *
echo.*                                                  *
echo.*       默认 0                                     *
echo.****************************************************

echo 公有密钥 0 已配置！ 密钥连接暂时只支持 %USERNAME_Lunux%@%HOST131% 
set sel=0
REM set /p sel=请输入主机序号(默认 0):

if %sel% == 0 (
	REM ssh %USERNAME_Lunux%@%HOST131%
	ssh -i %private_key% %USERNAME_Lunux%@%HOST131%
)
REM REM 下密码连接
if %sel% == 1 (
	ssh %USERNAME_Lunux%@%HOST132%
)
if %sel% == 2 (
	ssh %USERNAME_Board%@%HOSTBrd%
)

chcp 936 > nul
echo 连接失败！
set /p sel=输入q 退出:
if %sel% == q (
	exit 0 REM 退出并设置返回码为0（0，表示正确退出）
)
goto begin

pause
@echo on
