#pragma once
#include <Windows.h>
#include <string>
namespace ConsoleEng
{

	//Colors
	enum COLOR
	{ 
		BLACK = 0, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, WHITE, GRAY, LIGHT_BLUE, LIGHT_GREEN, LIGHT_AQUA,
		LIGHT_RED, LIGHT_PURPLE, LIGHT_YELLOW, BRIGHT_WHITE
	};

	class Console
	{
	public:
		Console(int width, int height, SHORT charWidth, SHORT charHeight, std::wstring title = L"Console Gaphics Engine");
		~Console();

		int Draw(std::wstring buffer, SHORT x, SHORT y, COLOR color = COLOR::WHITE);

	private:
		HANDLE _hConsole = nullptr;
		int _width;
		int _height;
		SHORT _charWidth;
		SHORT _charHeight;

		std::wstring _title;

	};


}