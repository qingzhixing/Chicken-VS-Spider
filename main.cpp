#include <graphics.h>
#include "ImageResource.hpp"

ImageResource imgResource;

static void MessageHandler(const ExMessage& exMessage) {
}

static void DataHandler() {
}

static void DrawFrame() {
	putimage(0, 0, &imgResource.background);
}

int main(void) {
	initgraph(1280, 720);

	// init image resource
	loadimage(&imgResource.background, _T("./static/img/Background.png"));

	bool needExit = false;
	ExMessage exMessage;

	BeginBatchDraw();

	while (!needExit) {
		DWORD startTime = GetTickCount();

		// 消息处理
		while (peekmessage(&exMessage))MessageHandler(exMessage);

		// 绘制
		cleardevice();
		DrawFrame();
		FlushBatchDraw();

		// 处理数据
		DataHandler();

		DWORD endTime = GetTickCount();
		DWORD deltaTime = endTime - startTime;
		// 锁定刷新率60fps
		if (deltaTime < 1000 / 60) {
			Sleep(1000 / 60 - deltaTime);
		}
	}

	EndBatchDraw();
	return 0;
}