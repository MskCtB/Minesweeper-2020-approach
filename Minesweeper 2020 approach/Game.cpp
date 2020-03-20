#include "Game.h"



Game::Game() : amount(12), alive(true), AtoS(12), colour(192), flash (8)
{
	//clock.restart().asSeconds;
	srand(time(NULL));
	font = loader.GetFont();

	GO.setFont(font);
	GO.setCharacterSize(38);
	GO.setString("Game Over");

	GO2.setFont(font);
	GO2.setCharacterSize(20);
	GO2.setString("Press >Space< to continue");

	string = std::to_string(amount);
	BombCounter.setCharacterSize(16);
	BombCounter.setFont(font);
	BombCounter.setString("Bombs: " + string);
	//BombCounter.setFillColor(sf::Color(24, 0, 192));
	float k = BombCounter.getCharacterSize() / 2.0f;
	BombCounter.setPosition(sf::Vector2f(0.0f, CUBE / 2.0f - k));

	GO.setFillColor(sf::Color(220, 255, 0, 255));
	GO.setPosition(70.0f, 120.0f);
	GO2.setFillColor(sf::Color(220, 255, 0, 255));
	GO2.setPosition(38.0f, 180.0f);
}


Game::~Game()
{
}

void Game::Set_Up()
{
	sf::Vector2i c;
	int y = 0;
	for (int i = 0; i < 64; i++)
	{
		if (i > 0 && !(i % 8))
			y++;
		c.x = i / 8; //y
		c.y = i % 8; //x
		arr[i / 8][i % 8].Set(sf::Vector2f((CUBE * (i % 8)) + (CUBE / 2.0f + 2.0f) + (float)(2 * (i % 8)),
			CUBE + (CUBE * y) + (CUBE / 2.0f + 2.0f) + (float)(2 * y)), c);
		positions[i / 8][i % 8].x = (CUBE * (i % 8)) + (2.0f) + (float)(2 * (i % 8));
		positions[i / 8][i % 8].y = CUBE + (CUBE * y) + (2.0f) + (float)(2 * y);
		arr[i / 8][i % 8].SetFont(loader.GetFont());

		arr[i / 8][i % 8].SetFlagSprite(loader.GetTexture(1));
	}
	
	SetBombs();
	
}

void Game::Clean()
{
	for (int i = 0; i < 64; i++)
	{
		arr[i / 8][i % 8].Clean();
		arr[i / 8][i % 8].SetSprite(loader.GetTexture(0));
	}
}

void Game::RightClick(sf::Vector2i mouse)
{
	for (int i = 0; i < 64; i++)
	{
		if (mouse.x >= positions[i/8][i%8].x && positions[i / 8][i % 8].y <= mouse.y
			&& positions[i / 8][i % 8].x + CUBE >= mouse.x && positions[i / 8][i % 8].y + CUBE >= mouse.y && alive)
		{
			arr[i / 8][i % 8].RightClick();	
			if (arr[i / 8][i % 8].CheckFlag() && arr[i/8][i%8].CheckCover())
				AtoS--;
			else if(!arr[i / 8][i % 8].CheckFlag() && arr[i / 8][i % 8].CheckCover())
				AtoS++;
			string = std::to_string(AtoS);
			if (AtoS < 0)
				string = "0";
			BombCounter.setString("Bombs: " + string);
		}
	}
}

void Game::LeftClick(sf::Vector2i mouse)
{
	sf::Vector2i temp;
	for (int i = 0; i < 64; i++)
	{
		if (positions[i / 8][i % 8].x <= mouse.x && positions[i / 8][i % 8].y <= mouse.y
			&& positions[i / 8][i % 8].x + CUBE >= mouse.x && positions[i / 8][i % 8].y + CUBE >= mouse.y && alive)
		{
			temp.x = i % 8;
			temp.y = i / 8;
		}
	}
	Uncover(temp.y, temp.x);
}

void Game::SetBombs()
{
	for (int i = 0; i < amount; i++)
	{
		int y = rand() % 8;
		int x = rand() % 8;

		if (!arr[y][x].Status())
			arr[y][x].SetBomb();
		else
		{
			while (arr[y][x].Status())
			{
				y = rand() % 8;
				x = rand() % 8;
			}
			arr[y][x].SetBomb();
		}
	}

	for (int i = 0; i < 64; i++)
		if (arr[i / 8][i % 8].Status())
			arr[i / 8][i % 8].SetSprite(loader.GetTexture(2));

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (i == 0) // TOP ROW
			{
				if (j == 0)
				{
					if (arr[i + 1][j].Status())
						arr[i][j].bombs++;
					if (arr[i + 1][j + 1].Status())
						arr[i][j].bombs++;
					if (arr[i][j + 1].Status())
						arr[i][j].bombs++;
				}
				if (j > 0 && j < 7)
				{
					if (arr[i][j - 1].Status())
						arr[i][j].bombs++;
					if (arr[i][j + 1].Status())
						arr[i][j].bombs++;
					//////////////////////////////////////
					if (arr[i + 1][j - 1].Status())
						arr[i][j].bombs++;
					if (arr[i + 1][j].Status())
						arr[i][j].bombs++;
					if (arr[i + 1][j + 1].Status())
						arr[i][j].bombs++;
				}
				if (j == 7)
				{
					if (arr[i + 1][j].Status())
						arr[i][j].bombs++;
					if (arr[i + 1][j - 1].Status())
						arr[i][j].bombs++;
					if (arr[i][j - 1].Status())
						arr[i][j].bombs++;
				}
			}
			if (i > 0 && i < 7) // MIDDLE
			{
				if (j == 0)
				{
					if (arr[i - 1][j].Status())
						arr[i][j].bombs++;
					if (arr[i - 1][j + 1].Status())
						arr[i][j].bombs++;
					//////////////////////////
					if (arr[i][j + 1].Status())
						arr[i][j].bombs++;
					//////////////////////////
					if (arr[i + 1][j].Status())
						arr[i][j].bombs++;
					if (arr[i + 1][j + 1].Status())
						arr[i][j].bombs++;
				}
				if (j > 0 && j < 7)
				{
					if (arr[i - 1][j - 1].Status())
						arr[i][j].bombs++;
					if (arr[i - 1][j].Status())
						arr[i][j].bombs++;
					if (arr[i - 1][j + 1].Status())
						arr[i][j].bombs++;
					//////////////////////////
					if (arr[i][j - 1].Status())
						arr[i][j].bombs++;
					if (arr[i][j + 1].Status())
						arr[i][j].bombs++;
					//////////////////////////
					if (arr[i + 1][j - 1].Status())
						arr[i][j].bombs++;
					if (arr[i + 1][j].Status())
						arr[i][j].bombs++;
					if (arr[i + 1][j + 1].Status())
						arr[i][j].bombs++;
				}
				if (j == 7)
				{
					if (arr[i - 1][j - 1].Status())
						arr[i][j].bombs++;
					if (arr[i - 1][j].Status())
						arr[i][j].bombs++;
					/////////////////////////
					if (arr[i][j - 1].Status())
						arr[i][j].bombs++;
					/////////////////////////
					if (arr[i + 1][j - 1].Status())
						arr[i][j].bombs++;
					if (arr[i + 1][j].Status())
						arr[i][j].bombs++;
				}
			}
			if (i == 7) //BOTTOM
			{
				if (j == 0)
				{
					if (arr[i - 1][j].Status())
						arr[i][j].bombs++;
					if (arr[i - 1][j + 1].Status())
						arr[i][j].bombs++;
					///////////////////////////
					if (arr[i][j + 1].Status())
						arr[i][j].bombs++;
				}
				if (j > 0 && j < 7)
				{
					if (arr[i - 1][j - 1].Status())
						arr[i][j].bombs++;
					if (arr[i - 1][j].Status())
						arr[i][j].bombs++;
					if (arr[i - 1][j + 1].Status())
						arr[i][j].bombs++;
					////////////////////////////
					if (arr[i][j - 1].Status())
						arr[i][j].bombs++;
					if (arr[i][j + 1].Status())
						arr[i][j].bombs++;
				}
				if (j == 7)
				{
					if (arr[i - 1][j - 1].Status())
						arr[i][j].bombs++;
					if (arr[i - 1][j].Status())
						arr[i][j].bombs++;
					/////////////////////////////
					if (arr[i][j - 1].Status())
						arr[i][j].bombs++;
				}
			}
			arr[i][j].Update();
		}
}

void Game::Uncover(int y, int x)
{
	if (arr[y][x].Status())
	{
		alive = false;
		arr[y][x].SetSprite(loader.GetTexture(3));
	}
	if (y >= 0 && y <= 7 && x >= 0 && x <= 7)
	{
		arr[y][x].LeftClick();
		arr[y][x].visited = true;
		if (arr[y][x].bombs == 0)
		{
			if (y == 0)
			{
				if (x == 0)
				{
					arr[y][x + 1].LeftClick();
					//////////////////////
					arr[y + 1][x].LeftClick();
					arr[y + 1][x + 1].LeftClick();
				}
				if (x > 0 && x < 7)
				{
					arr[y][x - 1].LeftClick();
					arr[y][x + 1].LeftClick();
					//////////////////////
					arr[y + 1][x - 1].LeftClick();
					arr[y + 1][x].LeftClick();
					arr[y + 1][x + 1].LeftClick();
				}
				if (x == 7)
				{
					arr[y][x - 1].LeftClick();
					//////////////////////
					arr[y + 1][x - 1].LeftClick();
					arr[y + 1][x].LeftClick();
				}
			}
			if (y > 0 && y < 7)
			{
				if (x == 0)
				{
					arr[y - 1][x].LeftClick();
					arr[y - 1][x + 1].LeftClick();
					//////////////////////
					arr[y][x + 1].LeftClick();
					//////////////////////
					arr[y + 1][x].LeftClick();
					arr[y + 1][x + 1].LeftClick();
				}
				if (x > 0 && x < 7)
				{
					arr[y - 1][x - 1].LeftClick();
					arr[y - 1][x].LeftClick();
					arr[y - 1][x + 1].LeftClick();
					//////////////////////
					arr[y][x - 1].LeftClick();
					arr[y][x + 1].LeftClick();
					/////////////////////
					arr[y + 1][x - 1].LeftClick();
					arr[y + 1][x].LeftClick();
					arr[y + 1][x + 1].LeftClick();
				}
				if (x == 7)
				{
					arr[y - 1][x - 1].LeftClick();
					arr[y - 1][x].LeftClick();
					//////////////////////
					arr[y][x - 1].LeftClick();
					//////////////////////
					arr[y + 1][x - 1].LeftClick();
					arr[y + 1][x].LeftClick();
				}
			}
			if (y == 7)
			{
				if (x == 0)
				{
					arr[y - 1][x].LeftClick();
					arr[y - 1][x + 1].LeftClick();
					///////////////////
					arr[y][x + 1].LeftClick();
				}
				if (x > 0 && x < 7)
				{
					arr[y - 1][x - 1].LeftClick();
					arr[y - 1][x].LeftClick();
					arr[y - 1][x + 1].LeftClick();
					///////////////////
					arr[y][x - 1].LeftClick();
					arr[y][x + 1].LeftClick();
				}
				if (x == 7)
				{
					arr[y - 1][x - 1].LeftClick();
					arr[y - 1][x].LeftClick();
					///////////////////
					arr[y][x - 1].LeftClick();
				}
			}
			//UP,DOWN,LEFT,RIGHT
			if (y - 1 >= 0 && y + 1 <= 7 && x - 1 >= 0 && x + 1 <= 7)
			{
				if (!arr[y - 1][x].visited)
					Uncover(y - 1, x);
				if (!arr[y][x - 1].visited)
					Uncover(y, x - 1);
				if (!arr[y][x + 1].visited)
					Uncover(y, x + 1);
				if (!arr[y + 1][x].visited)
					Uncover(y + 1, x);
				//CORNERS
				if (!arr[y - 1][x - 1].visited)
					Uncover(y - 1, x - 1);
				if (!arr[y - 1][x + 1].visited)
					Uncover(y - 1, x + 1);
				if (!arr[y + 1][x - 1].visited)
					Uncover(y + 1, x - 1);
				if (!arr[y + 1][x + 1].visited)
					Uncover(y + 1, x + 1);
			}
			if (y == 0)
			{
				if (x == 0)
				{
					if (!arr[y][x + 1].visited)
						Uncover(y, x + 1);
					if (!arr[y + 1][x].visited)
						Uncover(y + 1, x);
					if (!arr[y + 1][x + 1].visited)
						Uncover(y + 1, x + 1);
				}
				if (x > 0 && x < 7)
				{
					if (!arr[y][x - 1].visited)
						Uncover(y, x - 1);
					if (!arr[y][x + 1].visited)
						Uncover(y, x + 1);
					if (!arr[y + 1][x].visited)
						Uncover(y + 1, x);
					if (!arr[y + 1][x - 1].visited)
						Uncover(y + 1, x + 1);
					if (!arr[y + 1][x + 1].visited)
						Uncover(y + 1, x + 1);
				}
				if (x == 7)
				{
					if (!arr[y][x - 1].visited)
						Uncover(y, x - 1);
					if (!arr[y + 1][x].visited)
						Uncover(y + 1, x);
					if (!arr[y + 1][x - 1].visited)
						Uncover(y + 1, x + 1);
				}
			}
			if (y == 7)
			{
				if (x == 0)
				{
					if (!arr[y - 1][x].visited)
						Uncover(y - 1, x);
					if (!arr[y][x + 1].visited)
						Uncover(y, x + 1);
					if (!arr[y - 1][x + 1].visited)
						Uncover(y - 1, x + 1);
				}
				if (x > 0 && x < 7)
				{
					if (!arr[y - 1][x].visited)
						Uncover(y - 1, x);
					if (!arr[y][x - 1].visited)
						Uncover(y, x - 1);
					if (!arr[y][x + 1].visited)
						Uncover(y, x + 1);
					if (!arr[y - 1][x - 1].visited)
						Uncover(y - 1, x - 1);
					if (!arr[y - 1][x + 1].visited)
						Uncover(y - 1, x + 1);
				}
				if (x == 7)
				{
					if (!arr[y - 1][x].visited)
						Uncover(y - 1, x);
					if (!arr[y][x - 1].visited)
						Uncover(y, x - 1);
					if (!arr[y - 1][x - 1].visited)
						Uncover(y - 1, x - 1);
				}
			}
			if (x == 0)
			{
				if (y > 0 && y < 7)
				{
					if (!arr[y - 1][x].visited)
						Uncover(y - 1, x);
					if (!arr[y][x + 1].visited)
						Uncover(y, x + 1);
					if (!arr[y + 1][x].visited)
						Uncover(y + 1, x);
					if (!arr[y - 1][x + 1].visited)
						Uncover(y - 1, x + 1);
					if (!arr[y + 1][x + 1].visited)
						Uncover(y + 1, x + 1);
				}
			}
			if (x == 7)
			{
				if (y > 0 && y < 7)
				{
					if (!arr[y - 1][x].visited)
						Uncover(y - 1, x);
					if (!arr[y][x - 1].visited)
						Uncover(y, x - 1);
					if (!arr[y + 1][x].visited)
						Uncover(y + 1, x);
					if (!arr[y - 1][x - 1].visited)
						Uncover(y - 1, x - 1);
					if (!arr[y + 1][x - 1].visited)
						Uncover(y + 1, x - 1);
				}
			}
		}
	}
}

void Game::GameOver()
{
	for (int i = 0; i < 64; i++)
		arr[i / 8][i % 8].Reveal();
	AtoS = amount;
}

void Game::DrawGameOver(sf::RenderWindow & window)
{
	window.draw(GO);
	window.draw(GO2);
}

void Game::Colour()
{
	if (colour >= 192)
		flash = !flash;
	if (colour <= 0)
		flash = !flash;
	GO.setFillColor(sf::Color(colour, colour, 0, 255));
	GO2.setFillColor(sf::Color(colour, colour, 0, 255));
}