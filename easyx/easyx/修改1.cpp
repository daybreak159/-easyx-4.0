#include <graphics.h>
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

int main() {
    initgraph(640, 480);

    // ����һ��͸��ͼ�㣨����Ļ��С��ͬ��
    IMAGE transparentLayer;
    getimage(&transparentLayer, 0, 0, 640, 480);

    // ��͸��ͼ���ϻ���һ����ɫ����
    setbkcolor(TRANSPARENT);  // ���ñ���ɫΪ͸��
    setlinecolor(RED);        // ����������ɫΪ��ɫ
    rectangle(100, 100, 300, 200);  // ����һ����ɫ����

    // ��͸��ͼ����ʾ����Ļ��
    putimage(0, 0, &transparentLayer);

    // ˢ����Ļ
    getch();
    closegraph();

    return 0;
}
