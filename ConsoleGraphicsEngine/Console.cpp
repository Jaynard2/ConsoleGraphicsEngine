#include "Console.h"
#include <vector>

namespace ConsoleEng
{

	Console::Console(int width, int height, SHORT charWidth, SHORT charHeight, std::wstring title)
		: _hConsole(CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL)),
		_width(width), _height(height), _charWidth(charWidth), _charHeight(charHeight),
		_t1(std::chrono::system_clock::now()), _title(title)
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

		COORD largestSize = GetLargestConsoleWindowSize(_hConsole);
		if (largestSize.X < _width)
			_width = largestSize.X;
		if (largestSize.Y < _height)
			_height = largestSize.Y;

		SMALL_RECT size = { 0, 0, _width, _height};
		SetConsoleWindowInfo(_hConsole, TRUE, &size);

		_buffer = new CHAR_INFO[_width * _height];
		memset(_buffer, 0, _width * _height);

		SetConsoleTitle(title.c_str());

		SetConsoleActiveScreenBuffer(_hConsole);
	}


	Console::~Console()
	{
		delete[] _buffer;
	}

	int Console::Draw(wchar_t buffer, SHORT x, SHORT y, COLOR color)
	{
		if (x >= 0 && x <= _width && y >= 0 && y <= _height)
		{
			_buffer[y * (_width) + x].Char.UnicodeChar = buffer;
			_buffer[y * (_width) + x].Attributes = color;
			return 0;
		}

		return 1;
	}

	int Console::DrawString(std::wstring buffer, SHORT x, SHORT y, COLOR color)
	{
		for (int i = 0; i < buffer.length(); i++)
		{
			if (Draw(buffer[i], x + i % _width, y + i / _width, color))
				return 1;
		}

		return 0;
	}

	void Console::Update()
	{
		SMALL_RECT rect = { 0, 0, _width, _height };

		WriteConsoleOutput(_hConsole, _buffer, { (SHORT)_width, (SHORT)_height }, { 0, 0 }, &rect);

		auto t2 = std::chrono::system_clock::now();
		float timeElapsed = std::chrono::duration<float>(t2 - _t1).count();
		float fps = 1.0f / timeElapsed;
		SetConsoleTitle((_title + L" - " + std::to_wstring(fps) + L" FPS").c_str());
		
		_t1 = t2;

	}
}
