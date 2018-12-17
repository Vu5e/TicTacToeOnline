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
	srand(time(0));

	MyPhoton::getInstance().connect();

	m_sprite01 = new Sprite("../media/Particle 01.bmp");

	m_object1.setSprite(m_sprite01);
	m_object1.setPos(Vector(rand() % 800, rand() % 600, 0));
	m_object1.setBlendMode(ADDITIVE);

	m_object2.setSprite(m_sprite01);
	m_object2.setPos(Vector(200, 200, 0));
	m_object2.setBlendMode(ADDITIVE);
}


void Application::update(double elapsedTime)
{
	MyPhoton::getInstance().run();

}

void Application::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_object1.draw();
	m_object2.draw();
}


void Application::OnReceivedOpponentData(unsigned char data)
{
	std::cout << "received : " << (int)data << std::endl;
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
	//test
	MyPhoton::getInstance().sendMyData((unsigned char)rand() % 256);
}

void Application::onMouseReleased(int button)
{

}

void Application::onMouseHold(int button)
{

}

void Application::onMouseMoved(double mousePosX, double mousePosY)
{

}
