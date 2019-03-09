#include "Windows.h"
#include <iostream>
#include <random>

const int TEPANIE = 1;

void ruszrelatywniemyszk¹(int x, int czas)
{
	PPOINT pozycja = new POINT;
	GetCursorPos(pozycja);
	int deltaczas = 0;
	while (deltaczas < czas)
	{
		SetCursorPos(pozycja->x + x * deltaczas / czas, pozycja->y);
		Sleep(TEPANIE);
		deltaczas += TEPANIE;
	}
}


void ruszmyszk¹(int x, int czas)
{
	PPOINT pozycja = new POINT;
	GetCursorPos(pozycja);
	x -= pozycja->x;
	int deltaczas = 0;
	while (deltaczas < czas)
	{
		SetCursorPos(pozycja->x + x * deltaczas/czas, pozycja->y);
		Sleep(TEPANIE);
		deltaczas += TEPANIE;
	}
}

bool nolog = false;
int main(int argc, char *args[])
{
	for (int x = 0; x != argc; ++x)
	{
		if (args[x] == "-nolog") nolog = true;
	}
	wchar_t c;
	std::locale::global(std::locale(""));
	std::wcout.imbue(std::locale());
	if (!nolog) std::wcout << L"Napisz \"c\" lub \"b\"\n\nC - poruszenie bezwzglêdne myszk¹\nB - poruszenie wzglêdne myszk¹\n";
	while (std::wcin >> c)
	{
		if (c == 'c')
			//SetCursorPos(rand()%1919, rand()%767);
		{
			int arg[2];
			if (!nolog) std::wcout << L"Podaj bezwzglêdn¹ pozycjê(x):\n";
			std::wcin >> arg[0];
			if (!nolog) std::wcout << L"Podaj czas:\n";
			std::wcin >> arg[1];
			ruszmyszk¹(arg[0], arg[1]);
		}
		else if (c == 'b')
		{
			int arg[2];
			if (!nolog) std::wcout << L"Podaj wzglêdn¹ pozycjê(x):\n";
			std::wcin >> arg[0];
			if (!nolog) std::wcout << L"Podaj czas:\n";
			std::wcin >> arg[1];
			ruszrelatywniemyszk¹(arg[0], arg[1]);
		}
		//mouse_event(MOUSEEVENTF_MOVE, 200, 0, NULL, NULL);
		//Sleep(100);
		//mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, NULL, NULL);
		//mouse_event(MOUSEEVENTF_LEFTUP, 100, 100, NULL, NULL);
		//PPOINT pozycja = new POINT;
		
		//mouse_event(MOUSEEVENTF_ABSOLUTE, pozycja->x, pozycja->y, NULL, NULL);
	}
	// get the device context of the screen
	HDC hScreenDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	// and a device context to put it in
	HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

	int width = GetDeviceCaps(hScreenDC, HORZRES);
	int height = GetDeviceCaps(hScreenDC, VERTRES);

	// maybe worth checking these are positive values
	HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);

	// get a new bitmap
	HBITMAP hOldBitmap = static_cast<HBITMAP>(SelectObject(hMemoryDC, hBitmap));

	BitBlt(hMemoryDC, 0, 0, width, height, hScreenDC, 0, 0, SRCCOPY);
	hBitmap = static_cast<HBITMAP>(SelectObject(hMemoryDC, hOldBitmap));

	// clean up
	DeleteDC(hMemoryDC);
	DeleteDC(hScreenDC);
	return 0;
}