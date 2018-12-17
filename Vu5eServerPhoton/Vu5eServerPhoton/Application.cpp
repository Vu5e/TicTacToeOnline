#include "Application.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "MyPhoton.h"

using namespace std;


Application::Application()
{
}

Application::~Application()
{
}

void Application::start()
{
	package->m_data = 0;

	srand(time(0));
	MyPhoton::getInstance().connect();

	player1Turn = true;

	cout << MyPhoton::getInstance().playerID << endl;

	spriteTypes[0] = new Sprite("../media/O.png");
	spriteTypes[1] = new Sprite("../media/X.png");
	spriteTypes[2] = new Sprite("../media/Empty.png");
	spriteTypes[3] = new Sprite("../media/TicTacToe BG.png");
	spriteTypes[4] = new Sprite("../media/Player 1 Wins.png");
	spriteTypes[5] = new Sprite("../media/Player 2 Wins.png");
	spriteTypes[6] = new Sprite("../media/Restart.png");
	spriteTypes[7] = new Sprite("../media/Player 1 Turn.png");
	spriteTypes[8] = new Sprite("../media/Player 2 Turn.png");
	spriteTypes[9] = new Sprite("../media/Draw.png");

	startBackground = GameObject(spriteTypes[3], 640, 480, 12.8, 9.6);
	playerTurn = GameObject(spriteTypes[7], 640, 800, 6.4, 0.64);

	//Board
	TicTacToeBoard[0][0] = GameObject(spriteTypes[2], 527, 593); //0
	TicTacToeBoard[0][1] = GameObject(spriteTypes[2], 640, 593); //1
	TicTacToeBoard[0][2] = GameObject(spriteTypes[2], 753, 593); //2
	TicTacToeBoard[1][0] = GameObject(spriteTypes[2], 527, 480); //3
	TicTacToeBoard[1][1] = GameObject(spriteTypes[2], 640, 480); //4
	TicTacToeBoard[1][2] = GameObject(spriteTypes[2], 753, 480); //5
	TicTacToeBoard[2][0] = GameObject(spriteTypes[2], 527, 366); //6
	TicTacToeBoard[2][1] = GameObject(spriteTypes[2], 640, 366); //7
	TicTacToeBoard[2][2] = GameObject(spriteTypes[2], 753, 366); //8

	P1Wins = GameObject(spriteTypes[3], 640, 800);
	P2Wins = GameObject(spriteTypes[3], 640, 800);

	DrawGames = GameObject(spriteTypes[3], 640, 800);

	restartButton = GameObject(spriteTypes[3], 640, 100);
}

void Application::sendData(unsigned int i, unsigned int j)
{
	unsigned char dataSent = 0;

	package->m_data = 0;
	package->Pack((unsigned char)i, 3);

	package->Pack((unsigned char)j, 3);

	/*//View Binary
	for (int i = sizeof(unsigned int) * 8 - 1; i >= 0; i--)
	{
		int temp = package->data;
		cout << (1 & (temp >> i));

		if (i % 4 == 0)
			cout << " ";
	}

	cout << endl << endl;
	*/

	dataSent = package->m_data;

	cout << (int)dataSent << endl;
	cout << "Sent: " << i << ", " << j << endl;

	MyPhoton::getInstance().sendData(dataSent);

	CheckWinCondition();

	cout << package->totalBitCount << endl;
	package->ResetTotalBitCount();
	cout << package->totalBitCount << endl;
}

void Application::networkUpdate()
{
	//static double prevTime = glfwGetTime();

}


void Application::update(double elapsedTime)
{

	MyPhoton::getInstance().run();
}

void Application::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	startBackground.draw();

	playerTurn.draw();

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; i++)
		{
			TicTacToeBoard[i][j].draw();
		}
	}
}


void Application::OnReceivedOpponentData(unsigned char data)
{
	//receivedPackData = data;
}


void Application::onKeyPressed(int key)
{

}

void Application::onKeyReleased(int key)
{

}

void Application::onKeyHold(int key)
{

}

void Application::onMousePressed(int button)
{
	if (!isGameEnd)
	{
		if (MyPhoton::getInstance().playerID == player1Turn)
		{
			if (mouseX >= 477 && mouseX <= 803 && mouseY >= 316 && mouseY <= 643)
			{
				if (mouseX <= 577)
				{
					if (mouseY >= 543)
					{
						if (TicTacToeBoard[0][0].getOwner() == TileOwner::NOTOWNED)
						{
							TicTacToeBoard[0][0].setSprite(spriteTypes[player1Turn]);
							TicTacToeBoard[0][0].setOwner(player1Turn);

							sendData(0, 0);
						}
					}
					else if (mouseY >= 430 && mouseY <= 530)
					{
						if (TicTacToeBoard[1][0].getOwner() == TileOwner::NOTOWNED)
						{
							TicTacToeBoard[1][0].setSprite(spriteTypes[player1Turn]);
							TicTacToeBoard[1][0].setOwner(player1Turn);

							sendData(1, 0);
						}
					}
					else if (mouseY <= 416)
					{
						if (TicTacToeBoard[2][0].getOwner() == TileOwner::NOTOWNED)
						{
							TicTacToeBoard[2][0].setSprite(spriteTypes[player1Turn]);
							TicTacToeBoard[2][0].setOwner(player1Turn);

							sendData(2, 0);
						}
					}
				}
				else if (mouseX >= 590 && mouseX <= 690)
				{
					if (mouseY >= 543)
					{
						if (TicTacToeBoard[0][1].getOwner() == TileOwner::NOTOWNED)
						{
							TicTacToeBoard[0][1].setSprite(spriteTypes[player1Turn]);
							TicTacToeBoard[0][1].setOwner(player1Turn);

							sendData(0, 1);
						}
					}
					else if (mouseY >= 430 && mouseY <= 530)
					{
						if (TicTacToeBoard[1][1].getOwner() == TileOwner::NOTOWNED)
						{
							TicTacToeBoard[1][1].setSprite(spriteTypes[player1Turn]);
							TicTacToeBoard[1][1].setOwner(player1Turn);

							sendData(1, 1);
						}
					}
					else if (mouseY <= 416)
					{
						if (TicTacToeBoard[2][1].getOwner() == TileOwner::NOTOWNED)
						{
							TicTacToeBoard[2][1].setSprite(spriteTypes[player1Turn]);
							TicTacToeBoard[2][1].setOwner(player1Turn);

							sendData(2, 1);
						}
					}
				}
				else if (mouseX >= 703)
				{
					if (mouseY >= 543)
					{
						if (TicTacToeBoard[0][2].getOwner() == TileOwner::NOTOWNED)
						{
							TicTacToeBoard[0][2].setSprite(spriteTypes[player1Turn]);
							TicTacToeBoard[0][2].setOwner(player1Turn);

							sendData(0, 2);
						}
					}
					else if (mouseY >= 430 && mouseY <= 530)
					{
						if (TicTacToeBoard[1][2].getOwner() == TileOwner::NOTOWNED)
						{
							TicTacToeBoard[1][2].setSprite(spriteTypes[player1Turn]);
							TicTacToeBoard[1][2].setOwner(player1Turn);

							sendData(1, 2);
						}
					}
					else if (mouseY <= 416)
					{
						if (TicTacToeBoard[2][2].getOwner() == TileOwner::NOTOWNED)
						{
							TicTacToeBoard[2][2].setSprite(spriteTypes[player1Turn]);
							TicTacToeBoard[2][2].setOwner(player1Turn);

							sendData(2, 2);
						}
					}
				}
			}
		}
	}
	else
	{
		//Show Restart Button and coordinates
	}
}

void Application::onMouseReleased(int button)
{

}

void Application::onMouseHold(int button)
{

}

void Application::onMouseMoved(double mousePosX, double mousePosY)
{
	mouseX = mousePosX;
	mouseY = mousePosY;
}

void Application::UpdateBoard(int locX, int locY)
{

	TicTacToeBoard[locX][locY].setOwner(player1Turn);
	TicTacToeBoard[locX][locY].setSprite(spriteTypes[player1Turn]);

	CheckWinCondition();
}

void Application::SwitchTurns()
{
	player1Turn = !player1Turn;

	if (player1Turn)
	{
		playerTurn.setSprite(spriteTypes[7]);
	}
	else
	{
		playerTurn.setSprite(spriteTypes[8]);
	}

}

void Application::CheckWinCondition()
{
	turnCounter++; // increments no of turns

		  //Horizontal
	if (TicTacToeBoard[0][0].getOwner() != TileOwner::NOTOWNED && TicTacToeBoard[0][0].getOwner() == TicTacToeBoard[1][0].getOwner() && TicTacToeBoard[1][0].getOwner() == TicTacToeBoard[2][0].getOwner()
		|| TicTacToeBoard[0][1].getOwner() != TileOwner::NOTOWNED && TicTacToeBoard[0][1].getOwner() == TicTacToeBoard[1][1].getOwner() && TicTacToeBoard[1][1].getOwner() == TicTacToeBoard[2][1].getOwner()
		|| TicTacToeBoard[0][2].getOwner() != TileOwner::NOTOWNED && TicTacToeBoard[0][2].getOwner() == TicTacToeBoard[1][2].getOwner() && TicTacToeBoard[1][2].getOwner() == TicTacToeBoard[2][2].getOwner()

		//Vertical
		|| TicTacToeBoard[0][0].getOwner() != TileOwner::NOTOWNED && TicTacToeBoard[0][0].getOwner() == TicTacToeBoard[0][1].getOwner() && TicTacToeBoard[0][1].getOwner() == TicTacToeBoard[0][2].getOwner()
		|| TicTacToeBoard[1][0].getOwner() != TileOwner::NOTOWNED && TicTacToeBoard[1][0].getOwner() == TicTacToeBoard[1][1].getOwner() && TicTacToeBoard[1][1].getOwner() == TicTacToeBoard[1][2].getOwner()
		|| TicTacToeBoard[2][0].getOwner() != TileOwner::NOTOWNED && TicTacToeBoard[2][0].getOwner() == TicTacToeBoard[2][1].getOwner() && TicTacToeBoard[2][1].getOwner() == TicTacToeBoard[2][2].getOwner()

		//Diagonal Left
		|| TicTacToeBoard[0][0].getOwner() != TileOwner::NOTOWNED && TicTacToeBoard[0][0].getOwner() == TicTacToeBoard[1][1].getOwner() && TicTacToeBoard[2][2].getOwner()

		//Diagonal Right
		|| TicTacToeBoard[2][0].getOwner() != TileOwner::NOTOWNED && TicTacToeBoard[2][0].getOwner() == TicTacToeBoard[1][1].getOwner() && TicTacToeBoard[1][1].getOwner() == TicTacToeBoard[0][2].getOwner())
	{
		winner = player1Turn;
		isGameEnd = true;

		cout << "Winner: " << winner << endl;
		//Display Winner at top, Activate and Spawn Restart Button

		if (winner == 1) // P1 won
		{
			playerTurn.setSprite(spriteTypes[4]);
		}
		else // P2 won
		{
			playerTurn.setSprite(spriteTypes[5]);
		}

	}
	else if (turnCounter >= 9)
	{
		winner = 2;
		isGameEnd = true;

		cout << "Draw " << endl;
		playerTurn.setSprite(spriteTypes[9]);
		//Display Draw at top, Activate and spawn Restart Button
	}
	else
	{
		//Sets current turn to other player's turn
		SwitchTurns();
	}
}