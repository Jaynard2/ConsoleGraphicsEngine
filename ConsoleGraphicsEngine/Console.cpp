#include "Console.h"
#include <vector>

namespace ConsoleEng
{

	Console::Console(int width, int height, SHORT charWidth, SHORT charHeight, std::wstring title)
		: _hConsole(CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL)),
		_width(width), _height(height), _charWidth(charWidth), _charHeight(charHeight), _title(title)
	{
		CONSOLE_CURSOR_INFO cursor = { 1, false };
		SetConsoleCursorInfo(_hConsole, &cursor);

		CONSOLE_FONT_INFOEX font;
		font.cbSize = sizeof(font);
		font.nFont = 0;
		font.dwFontSize = { _charWidth, _charHeight };
		font.FontFamily = FF_DONTCARE;
		font.FontWeight = FW_NORMAL;
		wcscpy_s(font.FaceName, L"Consolas");
		SetCurrentConsoleFontEx(_hConsole, false, &font);

		SetConsoleTitle(title.c_str());

		SetConsoleActiveScreenBuffer(_hConsole);
	}


	Console::~Console()
	{
	}

	int Console::Draw(std::wstring buffer, SHORT x, SHORT y, COLOR color)
	{
		if (y * _width + x + buffer.length() > _width * _height)
			return 1;


		DWORD bytesWritten = 0;
		WriteConsoleOutputCharacter(_hConsole, buffer.c_str(), buffer.length(), { x, y }, &bytesWritten);

		std::vector<WORD> attrib;
		attrib.reserve(buffer.length());
		for (int i = 0; i < buffer.length(); i++)
			attrib.push_back(color);

		WriteConsoleOutputAttribute(_hConsole, &attrib[0], buffer.length(), { x, y }, &bytesWritten);

		return 0;
	}
}
