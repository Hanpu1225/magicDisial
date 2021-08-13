#include<graphics.h>
#include<stdio.h>
#include<mmsystem.h>
#include"date_tool.h"


#pragma comment(lib,"winmm.lib")//��

IMAGE imgs[71];
IMAGE sz[11];
IMAGE sz2[10];//��ʾ��

//void drawTime()
//{
//	//������
//
//	//��ȡʱ��
//	int hour, minute, second;
//	getTime(&hour, &minute, &second);
//	int h1 = hour / 10;
//	int h2 = hour % 10;
//	putimage(-130, -90, &sz[h1]);
//	putimage(-80, -90, &sz[h2]);
//
//	//:
//	putimage(-30, -70, &sz[10]);
//	putimage(-30, -45, &sz[10]);
//
//	int m1 = minute / 10;
//	int m2 = minute % 10;
//	putimage(-10, -90, &sz[m1]);
//	putimage(40, -90, &sz[m2]);
//
//	int s1 = second / 10;
//	int s2 = second % 10;
//	putimage(90, -55, &sz2[s1]);
//	putimage(120, -55, &sz2[s2]);
//
//}

void drawDate() {
	char str[16] = "";
	int year, month, day;
	getDate(&year, &month, &day, str);

	setbkcolor(RGB(223, 230, 240));
	settextcolor(RGB(15, 15, 15));      //����������ɫ
	settextstyle(25, 0, "��������"); //����������ʽ΢���ź�
	outtextxy(70, 0, str); //��ָ��λ������ı�

	getWeek(year, month, day, str);
	outtextxy(65, 30, str);

	sprintf(str, "%d-%d", month, day);
	outtextxy(110, 30, str);
}


void drawTime() {
	static int last_hour = -1, last_minute = -1, last_second = -1;
	int hour, minute, second;
	getTime(&hour, &minute, &second);

	int posX = -130;
	int posY = -90;

	int h1 = hour / 10;
	int h2 = hour % 10;
	if (last_hour != hour)  putimage(posX, posY, &sz[h1]);
	posX += 50;
	if (last_hour != hour) putimage(posX, posY, &sz[h2]);

	posX += 50;
	posY += 15;
	static bool first = true;
	if (first) putimage(posX, posY, &sz[10]);
	posY += 30;
	if (first) putimage(posX, posY, &sz[10]);

	posX += 20;
	posY = -90;
	int m1 = minute / 10;
	int m2 = minute % 10;
	if (last_minute != minute) putimage(posX, posY, &sz[m1]);
	posX += 50;
	if (last_minute != minute) putimage(posX, posY, &sz[m2]);

	posX += 50;
	posY += 35;
	if (last_second / 10 != second / 10) putimage(posX, posY, &sz2[second / 10]);
	posX += 30;

	if (last_second % 10 != second % 10) putimage(posX, posY, &sz2[second % 10]);

	if (first || (hour == 0 && minute == 0 && second<3)) {
		drawDate();
	}

	first = false;
	last_hour = hour;
	last_minute = minute;
	last_second = second;
}

int main(void)
{
	//�������̴���
	//1.1����һ��������һ����С�Ĵ���
	//1.2��������������Ϊ���㡢͸��
	initgraph(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));////�����,׿���
	//׼��ȥ��������

	HWND hwnd = GetHWnd();//��ȡ��ǰ���ڵĳ��ھ��,���Ǵ���id

	//���ô��ھ��
	SetWindowLong(hwnd,//�����Ǹ����ڵ�����
		GWL_STYLE,//���ô��ڵķ��
		GetWindowLong(hwnd,GWL_STYLE-WS_CAPTION));
	
	//���ô���Ϊ���㴰��
	SetWindowPos(hwnd,//�����Ǹ����ڵ�����
		HWND_TOPMOST,//���㴰��
		0, 0,//���ڵ�λ��
		GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),SWP_SHOWWINDOW);
	
	//���ô���Ϊ͸��Ч��
	/*
	1��Ҫ���ȰѴ�������Ϊ�ֲ㴰��
	2���ڰ�����ֲ㴰������Ϊ͸��
	3��
	*/
	SetWindowLong(hwnd,
		GWL_EXSTYLE,//���ڵ���չ��ʽ
		GetWindowLong(hwnd, GWL_STYLE) | WS_EX_LAYERED);
	//���÷ֲ㴰�ڵ�͸���� ���߲���ϵͳ
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0),//ָ����Ҫ���͸���ı���ɫ
		0,//͸����0 255����ȫ��͸��
		LWA_COLORKEY);//͸����ʽ���ò���2��������ɫ���͸��ɫ

	//׼������-������
	setbkcolor(RGB(0, 0, 0));//���ñ��������ɫ
	cleardevice();//ʹ�ñ�����ɫ������

	//��������ԭ��
	setorigin(GetSystemMetrics(SM_CXSCREEN) - 200, 200);


	//���Ʊ���
	IMAGE bg;
	//loadimage(&bg, L"bg3.jpg", 400, 400,//��Ҫ��ʾ�Ŀ����߶�
 //   true);//�ȱ�������
	loadimage(&bg, "bg3.jpg", 400, 400,true);//�ȱ�������
	putimage(-200, -200, &bg);
	//��һ����ɫԲȦ,ȥ��ë��
	setlinecolor(BLACK);//����������ɫ
	setlinestyle(PS_SOLID, 8);//���ʿ����8
	circle(0, 0, 202);//��Բ

	//��̫����
	//Ԥ����̫����
	char imgName[64];
	for (int i = 0; i < 71; i++)
	{
		sprintf_s(imgName, sizeof(imgName), "img/human_%04d_ͼ�� %d.jpg", i, 71 - i);
		loadimage(&imgs[i], imgName, 105, 105, true);
	}

	for (int i = 0; i < 10; i++)
	{
		sprintf_s(imgName, sizeof(imgName), "img/%d.jpg",i);
		loadimage(&sz[i], imgName, 40, 70, true);
		loadimage(&sz2[i], imgName, 20, 35, true);//��
	}
	loadimage(&sz[10], "img/rect.jpg", 10, 10, true);


	mciSendString("play img/bg.mp3 repeat", 0, 0, 0);
	//mciSendString()
	//��Ϸѭ��
	int k = 0;
	while (1)
	{
		putimage(-50, -15, &imgs[k]);
		k = (k + 1) % 71;//��0 ��70 �ڴ�70��0
		
		drawTime();

		Sleep(30);
	}

	closegraph();

	system("pause");
	return 0;
}

//��CPU�¶�ʪ�ȣ��ڴ��С