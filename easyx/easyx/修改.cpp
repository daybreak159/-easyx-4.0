#define _stprintf
#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include <graphics.h>
#include <stdio.h>
#include <Windows.h>
#include <stdio.h>
#include <Windows.h>
#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include<mmsystem.h>
#include<vector>
#include<ctime>
#include<conio.h>
#include<string>
#include<time.h>
#include <thread>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
int co = 0;
class Node {
public:
	int m_x;
	int m_y;
	COLORREF m_color;
	IMAGE m_layer; // 添加一个成员变量来存储图层的图像

	Node() : Node(0, 0, BLUE) {};
	Node(int x, int y, COLORREF color) : m_x(x), m_y(y), m_color(color) {
		getimage(&m_layer, x, y, 20, 10); // 在构造函数中获取图层的图像
	}

	void draw() {
		setlinecolor(RED);
		setfillcolor(m_color);
		fillrectangle(m_x, m_y, m_x + 20, m_y + 10);
		fillrectangle(m_x, m_y, m_x + 10, m_y + 10);
		fillrectangle(m_x, m_y, m_x - 10, m_y + 10);
	}

	void clear() {
		putimage(m_x, m_y, &m_layer); // 在清除之前将图层图像放回到指定位置
	}

	void move(int dx, int dy) {
		m_x += dx;
		m_y += dy;
		if (m_x == -10) m_x = 490;
		if (m_x == 500) m_x = 0;
		if (m_y == -10) m_y = 490;
		if (m_y == 500) return;
	}
};

ExMessage msg = { 0 };
using namespace std;
bool inarea(int x, int y, int w, int h, int mx, int my)
{
	if (mx > x && mx<x + w && my>y && my < y + h)
	{
		return true;
	}
	return false;
}
bool button(int x, int y, int w, int h, const char* text)
{
	if (inarea(x, y, w, h, msg.x, msg.y))
	{
		setfillcolor(WHITE);
	}
	fillroundrect(x, y, x + w, y + h, 5, 5);
	int rw = (w - textwidth(text)) / 2;
	int rh = (h - textheight(text)) / 2;
	outtextxy(x + rw, y + rh, text);
	if (inarea(x, y, w, h, msg.x, msg.y) && msg.message == WM_LBUTTONDOWN)
	{
		return true;
	}
	return false;
}
int gamestart()
{
	mciSendString(TEXT("open NULL type waveaudio alias audio"), NULL, 0, NULL);
	initgraph(640, 480);
	setbkcolor(RGB(45, 204, 51));
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	IMAGE img;	//准备图片
	loadimage(&img, "哆啦A梦.jpg");	//加载图片  L"背景.jpg"是图片的相对路径,也可以使用绝对路径
	putimage(0, 0, &img);
	while (true)
	{
		peekmessage(&msg, EM_MOUSE);
		BeginBatchDraw();
		if (button(350, 120, 150, 35, "game start"))
		{
			cout << "gamestart";
			cleardevice();
			EndBatchDraw();
			msg = { 0 };
			return 1;
		}
		if (button(350, 60, 150, 35, "introduction"))
		{
			cleardevice();
			EndBatchDraw();
			msg = { 0 };
			return 2;
		}
		EndBatchDraw();
		msg = { 0 };
	}
	getchar();
}
int choose()
{
	initgraph(640, 480);
	setbkcolor(RGB(45, 204, 51));
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	IMAGE img;	//准备图片
	loadimage(&img, "pic.jpg");	//加载图片  L"背景.jpg"是图片的相对路径,也可以使用绝对路径
	putimage(0, 0, &img);
	while (true)
	{
		peekmessage(&msg, EM_MOUSE);
		BeginBatchDraw();
		if (button(150, 180, 150, 35, "two"))
		{
			cout << "gamestart";
			cleardevice();
			EndBatchDraw();
			msg = { 0 };
			return 2;
		}
		if (button(150, 60, 150, 35, "one"))
		{
			cleardevice();
			EndBatchDraw();
			msg = { 0 };
			return 1;
		}
		if (button(150, 300, 150, 35, "three"))
		{
			cleardevice();
			EndBatchDraw();
			msg = { 0 };
			return 3;
		}
		EndBatchDraw();
		msg = { 0 };
	}
	getchar();
}

int tab(int t, int n)
{
	int p = 0;
	char x = 0;
	switch (n)
	{
	case 1:
		x = 'A';
		p = 10;
		break;
	case 2:
		x = 'D';
		p = 213;
		break;
	case 3:
		x = 'J';
		p = 426;
		break;
	case 4:
		x = 'L';
		p = 620;
		break;
	}
	Node n1(p, 0, RED);
	Node n2(p, -10, WHITE);
	int i = 49;
	Sleep(t);
	while (i--)
	{
		n1.draw();
		n1.move(0, 10);
		n2.clear();
		n2.move(0, 10);
		if (i < 5 && (GetAsyncKeyState(x) & 0x8000))
		{
			co++;
			n2.clear();
			return 0;
		}
		Sleep(20);
	}
	return 0;
}

int game1()
{
	setbkcolor(WHITE);
	initgraph(640, 480);
	IMAGE img;	//准备图片
	loadimage(&img, "pic.jpg");	//加载图片  L"背景.jpg"是图片的相对路径,也可以使用绝对路径
	putimage(0, 0, &img);
	//在指定位置贴图  前面的(0,0)是坐标
	int s = 1240;
	// 创建两个线程来运行tab函数
	mciSendString(_T("open music.mp3 alias bkmusic"), NULL, 100, NULL);
	setbkcolor(WHITE);
	mciSendString(_T("play bkmusic "), NULL, 0, NULL);//循环播放
	std::thread t1(tab, 0, 1);
	std::thread t2(tab, s, 2);
	std::thread t3(tab, s * 2, 3);
	std::thread t4(tab, s * 3, 4);
	std::thread t5(tab, s * 4, 1);
	std::thread t6(tab, s * 5, 2);
	std::thread t7(tab, s * 6, 3);
	std::thread t8(tab, s * 7, 4);
	std::thread a1(tab, s * 8, 2);
	std::thread a2(tab, s * 9, 2);
	std::thread a3(tab, s * 10, 3);
	std::thread a4(tab, s * 11, 3);
	std::thread a5(tab, s * 12, 4);
	std::thread a6(tab, s * 13, 3);
	std::thread a7(tab, s * 14, 2);
	std::thread a8(tab, s * 15, 1);
	std::thread b1(tab, s * 16, 1);
	std::thread b2(tab, s * 17, 2);
	std::thread b3(tab, s * 18, 3);
	std::thread b4(tab, s * 19, 4);
	std::thread c1(tab, s * 20, 1);
	std::thread c2(tab, s * 21, 1);
	std::thread c3(tab, s * 22, 4);
	std::thread c4(tab, s * 23, 4);
	std::thread d1(tab, s * 24, 1);
	std::thread d2(tab, s * 25, 1);
	std::thread d3(tab, s * 26, 1);
	std::thread d4(tab, s * 27, 1);
	std::thread f1(tab, s * 28, 4);
	std::thread f2(tab, s * 29, 4);
	std::thread f3(tab, s * 30, 4);
	std::thread f4(tab, s * 31, 4);
	std::thread g1(tab, s * 32, 1);
	std::thread g2(tab, s * 32.5, 4);
	std::thread g3(tab, s * 33, 2);
	std::thread g4(tab, s * 33.5, 3);
	std::thread h1(tab, s * 34, 2);
	std::thread h2(tab, s * 34.5, 4);
	std::thread h3(tab, s * 35, 1);
	std::thread h4(tab, s * 35.5, 3);
	std::thread i1(tab, s * 36, 2);
	std::thread i2(tab, s * 36.5, 3);
	std::thread i3(tab, s * 37, 2);
	std::thread i4(tab, s * 37.5, 3);
	std::thread j1(tab, s * 38, 1);
	std::thread j2(tab, s * 38.5, 2);
	std::thread j3(tab, s * 39, 3);
	std::thread j4(tab, s * 39.5, 4);
	std::thread k2(tab, s * 40, 4);
	std::thread k3(tab, s * 40.5, 2);
	std::thread k4(tab, s * 41.5, 3);
	std::thread o1(tab, s * 42, 2);
	std::thread o2(tab, s * 3, 4);
	std::thread o3(tab, s * 35, 1);
	std::thread o4(tab, s * 35.5, 3);
	std::thread p1(tab, s * 36, 2);
	std::thread p2(tab, s * 36.5, 3);
	std::thread p3(tab, s * 37, 2);
	std::thread p4(tab, s * 37.5, 3);
	std::thread q1(tab, s * 38, 1);
	std::thread q2(tab, s * 38.5, 2);
	std::thread q3(tab, s * 39, 3);
	std::thread q4(tab, s * 39.5, 4);
	std::thread r1(tab, s * 40, 4);
	std::thread r2(tab, s * 40.5, 2);
	std::thread r3(tab, s * 41, 3);
	std::thread r4(tab, s * 41.5, 2);
	std::thread s1(tab, s * 42, 4);
	std::thread s2(tab, s * 42.5, 1);
	std::thread s3(tab, s * 43, 3);
	std::thread s4(tab, s * 43.5, 2);
	std::thread v1(tab, s * 44, 3);
	std::thread v2(tab, s * 44.5, 2);
	std::thread v3(tab, s * 45, 3);
	std::thread v4(tab, s * 45.5, 1);
	std::thread u1(tab, s * 46, 2);
	std::thread u2(tab, s * 46.5, 3);
	std::thread u3(tab, s * 47, 4);

	// 等待两个线程结束
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();
	t6.join();
	t7.join();
	t8.join();
	a1.join();
	a2.join();
	a3.join();
	a4.join();
	a5.join();
	a6.join();
	a7.join();
	a8.join();
	b1.join();
	b2.join();
	b3.join();
	b4.join();
	c1.join();
	c2.join();
	c3.join();
	c4.join();
	d1.join();
	d2.join();
	d3.join();
	d4.join();
	f1.join();
	f2.join();
	f3.join();
	f4.join();
	g1.join();
	g2.join();
	g3.join();
	g4.join();
	h1.join();
	h2.join();
	h3.join();
	h4.join();
	i1.join();
	i2.join();
	i3.join();
	i4.join();
	j1.join();
	j2.join();
	j3.join();
	j4.join();
	k2.join();
	k3.join();
	k4.join();
	o1.join();
	o2.join();
	o3.join();
	o4.join();
	p1.join();
	p2.join();
	p3.join();
	p4.join();
	q1.join();
	q2.join();
	q3.join();
	q4.join();
	r1.join();
	r2.join();
	r3.join();
	r4.join();
	s1.join();
	s2.join();
	s3.join();
	s4.join();
	v1.join();
	v2.join();
	v3.join();
	v4.join();
	u1.join();
	u2.join();
	u3.join();
	mciSendString(_T("close bkmusic "), NULL, 0, NULL);
	return 0;
}
int game2()
{
	return 0;
}
int game3()
{
	return 0;
}
void end()
{
	initgraph(500, 500);
	IMAGE img;	//准备图片
	loadimage(&img, "pic.jpg");
	putimage(0, 0, &img);
	TCHAR s[40];
	_stprintf(s, _T("你的分数:%d"), co);
	outtextxy(50, 50, s);
	getchar();
	// 关闭窗口
	closegraph();
}
void instruction() {
	cleardevice(); // 清除图形

	// 初始化说明页面的图形环境
	initgraph(500, 500);
	IMAGE img;
	loadimage(&img, "pic.jpg");
	putimage(0, 0, &img);
	TCHAR s[40];
	settextstyle(24, 0, _T("宋体"));
	_stprintf(s, _T("游戏说明：从左到右四个键位为A D J L"));
	outtextxy(50, 50, s);
	_stprintf(s, _T("在滑块落在红线和底部之间点击即可得分"));
	outtextxy(50, 90, s);
	_stprintf(s, _T("一共只做了三首歌"));
	outtextxy(50, 130, s);
	_stprintf(s, _T("因为作者太菜了（）"));
	outtextxy(50, 170, s);
	_stprintf(s, _T("还是希望这个游戏给你带来一点点的快乐"));
	outtextxy(50, 210, s);
	_stprintf(s, _T("剩下的介绍放在readme里面了"));
	outtextxy(50, 250, s);
	_stprintf(s, _T("按任意键返回开始界面"));
	outtextxy(50, 290, s);

	// 等待用户按下任意键
	while (!_kbhit()) {
		Sleep(100);
	}
	_getch(); // 清除输入缓冲区中的按键

	// 清除图形
	cleardevice();
}


int main() {
	initgraph(640, 480);
	int a;
	bool initialized = false; // 用于标记图形环境是否已经初始化
	while (true) {
		if (!initialized) {
			initgraph(640, 480); // 在第一次循环前初始化图形环境
			initialized = true;
		}
		a = gamestart();
		switch (a) {
		case 1:
			int b;
			b = choose();
			switch (b) {
			case 1:
				game1();
				break;
			case 2:
				game2();
				break;
			case 3:
				game3();
				break;
			}
			break;
		case 2:
			instruction();
			break;
		}
		// 不再重新初始化图形环境
	}
}




