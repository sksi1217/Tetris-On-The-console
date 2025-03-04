#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "Blocks.h"
#include <random>


void HideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void sizeWindow()
{
	SetConsoleOutputCP(CP_UTF8);

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	GetCurrentConsoleFontEx(hOut, FALSE, &cfi);


	cfi.dwFontSize.Y = 50;

	SetCurrentConsoleFontEx(hOut, FALSE, &cfi);

}

std::deque<COORD> RandomBlock(Blocks& blocks)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, blocks.blocks.size());

	int randomNumber = distrib(gen);

	std::cout << randomNumber << std::endl;

	std::deque<COORD>& block = blocks.blocks[randomNumber];

	return block;
}

void InputManager(Blocks& blocks)
{
	if (_kbhit()) {
		char input = _getch();

		if (input == 100) // d
		{
			for (int i = 0; i < blocks.blockPosition.size(); i++)
			{
				blocks.blockPosition[i].X += 2;
			}
		}
		else if (input == 97) // a
		{
			for (int i = 0; i < blocks.blockPosition.size(); i++)
			{
				blocks.blockPosition[i].X -= 2;
			}
		}
	}
}

void CleanBlock(Blocks& blocks)
{
	// Очистить блоки, заменив символ на пробел
	for (int i = 0; i < blocks.blockPosition.size(); i++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), blocks.blockPosition[i]);
		std::cout << " ";  // Очистка позиции
	}
}

void MoveBlock(Blocks& blocks)
{
	// Отобразить блоки в новых позициях
	for (int i = 0; i < blocks.blockPosition.size(); i++)
	{
		blocks.blockPosition[i].Y += 1;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), blocks.blockPosition[i]);
		std::cout << blocks._blockSprite;
	}
}


void CreateBlock(Blocks& blocks)
{
	/*
	for (const auto& coord : randomBlock) {
		std::cout << "(" << coord.X << ", " << coord.Y << ") ";
	}*/
	std::deque<COORD> randBlock = RandomBlock(blocks);

	blocks.blockPosition = randBlock;
}

void StartGame(Blocks& blocks)
{
	system("mode con: cols=21 lines=15");
	HideCursor();
	sizeWindow();

	CreateBlock(blocks);
}

void Updata(Blocks& blocks)
{
	while (true)
	{
		CleanBlock(blocks);

		for (int i = 0; i < blocks.blockPosition.size(); i++)
		{
			if (blocks.blockPosition[i].Y >= 14)
			{
				

				blocks.blockPosition = { {0, 0}};
				CreateBlock(blocks);
			}
		}

		InputManager(blocks);

		MoveBlock(blocks);

		Sleep(500);
	}
}



int main() {

	Blocks blocks;

	

	StartGame(blocks);
	Updata(blocks);

	system("pause");

	return 0;
}




