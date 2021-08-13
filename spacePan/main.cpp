#include<graphics.h>
#include<stdio.h>
#include<mmsystem.h>
#include"date_tool.h"


#pragma comment(lib,"winmm.lib")//库

IMAGE imgs[71];
IMAGE sz[11];
IMAGE sz2[10];//显示秒

//void drawTime()
//{
//	//基础版
//
//	//获取时间
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
	settextcolor(RGB(15, 15, 15));      //设置字体颜色
	settextstyle(25, 0, "华文隶书"); //设置字体样式微软雅黑
	outtextxy(70, 0, str); //在指定位置输出文本

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
	//创建表盘窗口
	//1.1创建一个和桌面一样大小的窗口
	//1.2把整个窗口设置为顶层、透明
	initgraph(GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));////桌面宽,卓面高
	//准备去掉标题栏

	HWND hwnd = GetHWnd();//获取当前窗口的敞口句柄,就是窗口id

	//设置窗口句柄
	SetWindowLong(hwnd,//设置那个窗口的属性
		GWL_STYLE,//设置窗口的风格
		GetWindowLong(hwnd,GWL_STYLE-WS_CAPTION));
	
	//设置窗口为顶层窗口
	SetWindowPos(hwnd,//设置那个窗口的属性
		HWND_TOPMOST,//顶层窗口
		0, 0,//窗口的位置
		GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),SWP_SHOWWINDOW);
	
	//设置窗口为透明效果
	/*
	1、要求先把窗口设置为分层窗口
	2、在把这个分层窗口设置为透明
	3、
	*/
	SetWindowLong(hwnd,
		GWL_EXSTYLE,//窗口的拓展样式
		GetWindowLong(hwnd, GWL_STYLE) | WS_EX_LAYERED);
	//设置分层窗口的透明度 告诉操作系统
	SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0),//指定需要变成透明的背景色
		0,//透明度0 255是完全不透明
		LWA_COLORKEY);//透明方式，让参数2的所有颜色变成透明色

	//准备工作-清理窗口
	setbkcolor(RGB(0, 0, 0));//设置背景填充颜色
	cleardevice();//使用背景颜色清理窗口

	//设置坐标原点
	setorigin(GetSystemMetrics(SM_CXSCREEN) - 200, 200);


	//绘制表盘
	IMAGE bg;
	//loadimage(&bg, L"bg3.jpg", 400, 400,//想要显示的宽度与高度
 //   true);//等比例缩放
	loadimage(&bg, "bg3.jpg", 400, 400,true);//等比例缩放
	putimage(-200, -200, &bg);
	//画一个黑色圆圈,去除毛刺
	setlinecolor(BLACK);//设置线条颜色
	setlinestyle(PS_SOLID, 8);//画笔宽度是8
	circle(0, 0, 202);//画圆

	//画太空人
	//预加载太空人
	char imgName[64];
	for (int i = 0; i < 71; i++)
	{
		sprintf_s(imgName, sizeof(imgName), "img/human_%04d_图层 %d.jpg", i, 71 - i);
		loadimage(&imgs[i], imgName, 105, 105, true);
	}

	for (int i = 0; i < 10; i++)
	{
		sprintf_s(imgName, sizeof(imgName), "img/%d.jpg",i);
		loadimage(&sz[i], imgName, 40, 70, true);
		loadimage(&sz2[i], imgName, 20, 35, true);//秒
	}
	loadimage(&sz[10], "img/rect.jpg", 10, 10, true);


	mciSendString("play img/bg.mp3 repeat", 0, 0, 0);
	//mciSendString()
	//游戏循环
	int k = 0;
	while (1)
	{
		putimage(-50, -15, &imgs[k]);
		k = (k + 1) % 71;//从0 到70 在从70到0
		
		drawTime();

		Sleep(30);
	}

	closegraph();

	system("pause");
	return 0;
}

//加CPU温度湿度，内存大小