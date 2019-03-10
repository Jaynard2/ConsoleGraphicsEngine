#include <ConsoleEngine.h>
#include <string>
#include <vector>
#include <random>

int main()
{
	ConsoleEng::Console game = ConsoleEng::Console(150, 100, 4, 4);

	while (true)
	{
		static int timer = 0;
		for (int y = 0; y < game.GetHeight(); y++)
		{
			for (int x = 0; x < game.GetWidth(); x++)
			{
				game.Draw(CHARACTER_SOLID, x, y, (ConsoleEng::COLOR)(int)(sin((x + y) * timer / 100) * 8 + 8));
			}
		}
		game.Update();

		timer++;
	}

	return 0;
 }
