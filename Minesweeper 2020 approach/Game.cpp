#include "Game.h"

Cube arr[32][32];

Game::Game() : amount(12), alive(true), AtoS(12), colour(192), flash (8), win(false), canClick(true), dev(false)
{
	//clock.restart().asSeconds;
	srand(time(NULL));
	font = loader.GetFont();
	
	GO.setFont(font);
	GO.setCharacterSize(38);
	GO.setString("Game Over");
	GO.setOutlineColor(sf::Color::Black);
	GO.setOutlineThickness(2);

	GO2.setFont(font);
	GO2.setCharacterSize(20);
	GO2.setString("Press >Space< to continue");
	GO2.setOutlineColor(sf::Color::Black);
	GO2.setOutlineThickness(2);

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

void Game::Set_Up(int a)
{
	mode = a;
	if (mode <= 0)
	{
		n = 8;
		m = 8;
		amount = 12;
	}
	else if (mode == 1)
	{
		n = 12;
		m = 16;
		amount = 30;
	}
	else if (mode >= 2)
	{
		n = 16;
		m = 24;
		amount = 62;
	}
	sf::Vector2i c;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			c.x = i; //y
			c.y = j; //x
			arr[i][j].Set(sf::Vector2f((CUBE * (j)) + (CUBE / 2.0f + 2.0f) + (float)(2 * (j)),
										CUBE + (CUBE * (i)) + (CUBE / 2.0f + 2.0f) + (float)(2 * ( i + 1))));
			positions[i][j].x = (CUBE * (j)) + (2.0f) + (float)(2 * (j));
			positions[i][j].y = CUBE + (CUBE * (i)) + (2.0f) + (float)(2 * (i));
			arr[i][j].SetFont(loader.GetFont());

			arr[i][j].SetFlagSprite(loader.GetTexture(1));
		}
	}
	
	SetBombs();
	
}

void Game::Draw(sf::RenderWindow & window)
{
	if (mode <= 0)
	{
		GO.setPosition(window.getSize().x / 2.0f - (window.getSize().x / 4.0f) - 15.0f, window.getSize().y / 2.0f - 40.0f);
		GO2.setPosition(window.getSize().x / 2.0f - (window.getSize().x / 4.0f) - 40.0f, window.getSize().y / 2.0f + CUBE - 40.0f);
	}
	else if (mode == 1)
	{
		GO.setPosition(window.getSize().x / 2.0f - (window.getSize().x / 6.0f) + 10.0f, window.getSize().y / 2.0f - 30.0f);
		GO2.setPosition(window.getSize().x / 2.0f - (window.getSize().x / 6.0f) - 15.0f, window.getSize().y / 2.0f + CUBE - 30.0f);
	}
	else if (mode >= 2)
	{
		GO.setPosition(window.getSize().x / 2.0f - (window.getSize().x / 8.0f) + 10.0f, window.getSize().y / 2.0f - 50.0f);
		GO2.setPosition(window.getSize().x / 2.0f - (window.getSize().x / 8.0f) - 15.0f, window.getSize().y / 2.0f + CUBE - 50.0f);
	}
	
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++)
			arr[i][j].Draw(window);
	window.draw(BombCounter);
	if (win)
	{
		window.draw(GO);
		window.draw(GO2);

	}
}

void Game::Clean()
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			arr[i][j].Clean();
			arr[i][j].SetSprite(loader.GetTexture(0));
		}
	}
	win = false;
	canClick = true;
}

void Game::RightClick(sf::Vector2i mouse)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (mouse.x >= positions[i][j].x && positions[i][j].y <= mouse.y
				&& positions[i][j].x + CUBE >= mouse.x && positions[i][j].y + CUBE >= mouse.y && canClick)
			{
				arr[i][j].RightClick();
				if (arr[i][j].CheckFlag() && arr[i][j].CheckCover())
					AtoS--;
				else if (!arr[i][j].CheckFlag() && arr[i][j].CheckCover())
					AtoS++;
				string = std::to_string(AtoS);
				if (AtoS < 0)
					string = "0";
				BombCounter.setString("Bombs: " + string);
			}
		}
	}
}

void Game::LeftClick(sf::Vector2i mouse)
{

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (positions[i][j].x <= mouse.x && positions[i][j].y <= mouse.y
				&& positions[i][j].x + CUBE >= mouse.x && positions[i][j].y + CUBE >= mouse.y && canClick)
			{
				if (!arr[i][j].CheckFlag())
					Uncover(i, j);
				return;
			}
		}
	}
}

void Game::SetBombs()
{
	for (int i = 0; i < amount; i++)
	{
		int y = rand() % n;
		int x = rand() % m;

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
		arr[y][x].SetSprite(loader.GetTexture(2));
	}

	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 8; j < 8; j++)
		{
			if (arr[i][j].Status())
				arr[i][j].SetSprite(loader.GetTexture(2));
		}
	}*/

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
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
				if (j > 0 && j < m - 1)
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
				if (j == m - 1)
				{
					if (arr[i + 1][j].Status())
						arr[i][j].bombs++;
					if (arr[i + 1][j - 1].Status())
						arr[i][j].bombs++;
					if (arr[i][j - 1].Status())
						arr[i][j].bombs++;
				}
			}
			if (i > 0 && i < n - 1) // MIDDLE
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
				if (j > 0 && j < m - 1)
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
				if (j == m - 1)
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
			if (i == n - 1) //BOTTOM
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
				if (j > 0 && j < m - 1)
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
				if (j == m - 1)
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
		GO.setString("Game Over");
		canClick = false;
	}
	if (y >= 0 && y <= n - 1 && x >= 0 && x <= m - 1)
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
				if (x > 0 && x < m - 1)
				{
					arr[y][x - 1].LeftClick();
					arr[y][x + 1].LeftClick();
					//////////////////////
					arr[y + 1][x - 1].LeftClick();
					arr[y + 1][x].LeftClick();
					arr[y + 1][x + 1].LeftClick();
				}
				if (x == m - 1)
				{
					arr[y][x - 1].LeftClick();
					//////////////////////
					arr[y + 1][x - 1].LeftClick();
					arr[y + 1][x].LeftClick();
				}
			}
			if (y > 0 && y < n - 1)
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
				if (x > 0 && x < m - 1)
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
				if (x == m - 1)
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
			if (y == n - 1)
			{
				if (x == 0)
				{
					arr[y - 1][x].LeftClick();
					arr[y - 1][x + 1].LeftClick();
					///////////////////
					arr[y][x + 1].LeftClick();
				}
				if (x > 0 && x < m - 1)
				{
					arr[y - 1][x - 1].LeftClick();
					arr[y - 1][x].LeftClick();
					arr[y - 1][x + 1].LeftClick();
					///////////////////
					arr[y][x - 1].LeftClick();
					arr[y][x + 1].LeftClick();
				}
				if (x == m - 1)
				{
					arr[y - 1][x - 1].LeftClick();
					arr[y - 1][x].LeftClick();
					///////////////////
					arr[y][x - 1].LeftClick();
				}
			}
			//UP,DOWN,LEFT,RIGHT
			if (y - 1 >= 0 && y + 1 <= n - 1 && x - 1 >= 0 && x + 1 <= m - 1)
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
				if (x > 0 && x < m - 1)
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
				if (x == m - 1)
				{
					if (!arr[y][x - 1].visited)
						Uncover(y, x - 1);
					if (!arr[y + 1][x].visited)
						Uncover(y + 1, x);
					if (!arr[y + 1][x - 1].visited)
						Uncover(y + 1, x + 1);
				}
			}
			if (y == n - 1)
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
				if (x > 0 && x < m - 1)
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
				if (x == m - 1)
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
				if (y > 0 && y < n - 1)
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
			if (x == m - 1)
			{
				if (y > 0 && y < n - 1)
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
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			arr[i][j].Reveal();
	AtoS = amount;
}

void Game::DrawGameOver(sf::RenderWindow & window)
{
	if (mode <= 0)
	{
		GO.setPosition(window.getSize().x / 2.0f - (window.getSize().x / 4.0f) - 15.0f, window.getSize().y / 2.0f - 40.0f);
		GO2.setPosition(window.getSize().x / 2.0f - (window.getSize().x / 4.0f) - 40.0f, window.getSize().y / 2.0f + CUBE - 40.0f);
	}
	else if (mode == 1)
	{
		GO.setPosition(window.getSize().x / 2.0f - (window.getSize().x / 6.0f) + 10.0f, window.getSize().y / 2.0f - 30.0f);
		GO2.setPosition(window.getSize().x / 2.0f - (window.getSize().x / 6.0f) - 15.0f, window.getSize().y / 2.0f + CUBE - 30.0f);
	}
	else if (mode >= 2)
	{
		GO.setPosition(window.getSize().x / 2.0f - (window.getSize().x / 8.0f) + 10.0f, window.getSize().y / 2.0f - 50.0f);
		GO2.setPosition(window.getSize().x / 2.0f - (window.getSize().x / 8.0f) - 15.0f, window.getSize().y / 2.0f + CUBE - 50.0f);
	}
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

void Game::Win()
{
	int all = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (!arr[i][j].CheckCover() && !arr[i][j].Status())
				all++;
		}
	}

	if (all == n * m - amount && alive)
	{
		GO.setString("YOU WIN!");
		win = true;
		canClick = false;
	}
}
void Game::DevDraw(sf::RenderWindow & window)
{
	if (dev) for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++) 
			arr[i][j].DevDraw(window);
}
