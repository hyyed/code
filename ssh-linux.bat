@echo off
ssh -V
echo.
ssh -V >nul 2>&1
chcp 936 >nul

REM ����˽����Կ��ַ
REM set private_key=C:\Users\Libubai\.ssh\id_rsa
set private_key=~\.ssh\id_rsa
echo ˽����Կ��ַ%private_key%

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
echo.*       0��%USERNAME_Lunux%@%HOST133%                     *
echo.*       1��%USERNAME_Lunux%@%HOST132%                     *
echo.*       2��%USERNAME_Board%@%HOSTBrd%                    *
echo.*                                                  *
echo.*       Ĭ�� 0                                     *
echo.****************************************************

echo ������Կ 0 �����ã� ��Կ������ʱֻ֧�� %USERNAME_Lunux%@%HOST131% 
set sel=0
REM set /p sel=�������������(Ĭ�� 0):

if %sel% == 0 (
	REM ssh %USERNAME_Lunux%@%HOST131%
	ssh -i %private_key% %USERNAME_Lunux%@%HOST131%
)
REM REM ����������
if %sel% == 1 (
	ssh %USERNAME_Lunux%@%HOST132%
)
if %sel% == 2 (
	ssh %USERNAME_Board%@%HOSTBrd%
)

chcp 936 > nul
echo ����ʧ�ܣ�
set /p sel=����q �˳�:
if %sel% == q (
	exit 0 REM �˳������÷�����Ϊ0��0����ʾ��ȷ�˳���
)
goto begin

pause
@echo on
