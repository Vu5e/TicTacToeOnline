#pragma once
#include "Sprite.h"
#include "GameObject.h"
//#include "LinearCompression.h"
#include "UIntPacker.h"

#include <list>

class Application
{
protected:

	void networkUpdate();


public:

	Application();
	~Application();


	static Application& getInstance()
	{
		static Application app;
		return app;
	}

	void sendData(unsigned int i, unsigned int j);
	void OnReceivedOpponentData(unsigned char data);

	virtual void start();
	virtual void update(double elapsedTime);
	virtual void draw();
	virtual void onKeyPressed(int key);
	virtual void onKeyReleased(int key);
	virtual void onKeyHold(int key);
	virtual void onMousePressed(int button);
	virtual void onMouseReleased(int button);
	virtual void onMouseHold(int button);
	virtual void onMouseMoved(double mousePosX, double mousePosY);

	void UpdateBoard(int locX, int locY);

	void SwitchTurns();

	void CheckWinCondition();

	//Packet* package = new Packet();
	UIntPacker* package = new UIntPacker();

	float receivedPackData = 0;

	int winner = 2;
	bool isGameEnd = false;
	int mouseX = 0, mouseY = 0;

	bool player1Turn;

	Sprite* spriteTypes[10];

	GameObject startBackground;
	GameObject playerTurn;

	GameObject P1Wins;
	GameObject P2Wins;

	GameObject DrawGames;

	GameObject restartButton;

	GameObject TicTacToeBoard[3][3];

	int turnCounter = 0;
};