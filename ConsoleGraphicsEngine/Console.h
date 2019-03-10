#pragma once
#include <Windows.h>
#include <string>
#include <chrono>

#include "Color.h"

namespace ConsoleEng
{

	class Console
	{
	public:
		Console(int width, int height, SHORT charWidth, SHORT charHeight, std::wstring title = L"Console Gaphics Engine");
		~Console();

		int Draw(wchar_t buffer, SHORT x, SHORT y, COLOR color = COLOR::WHITE);
		int DrawString(std::wstring buffer, SHORT x, SHORT y, COLOR color = COLOR::WHITE);
		void Update();

		//Getters
		int GetWidth() { return _width; }
		int GetHeight() { return _height; }

	private:
		HANDLE _hConsole = nullptr;
		int _width;
		int _height;
		SHORT _charWidth;
		SHORT _charHeight;
		std::chrono::system_clock::time_point _t1;

		std::wstring _title;
		CHAR_INFO* _buffer;

	};
}
