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

    // 创建一个透明图层（与屏幕大小相同）
    IMAGE transparentLayer;
    getimage(&transparentLayer, 0, 0, 640, 480);

    // 在透明图层上绘制一个红色矩形
    setbkcolor(TRANSPARENT);  // 设置背景色为透明
    setlinecolor(RED);        // 设置线条颜色为红色
    rectangle(100, 100, 300, 200);  // 绘制一个红色矩形

    // 将透明图层显示在屏幕上
    putimage(0, 0, &transparentLayer);

    // 刷新屏幕
    getch();
    closegraph();

    return 0;
}
