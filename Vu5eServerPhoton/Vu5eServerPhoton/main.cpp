#include <iostream>
#include <windows.h>
#include <GL/GLU.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include <set>

using namespace std;

const int RESOLUTION_X = 1280;
const int RESOLUTION_Y = 960;

Application& app = Application::getInstance();
set <int> gDownKeys;
set <int> gDownMouseButtons;

void onWindowResized(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//! Use ortho2D view
	gluOrtho2D(0, width, 0, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		app.onKeyPressed(key);
		gDownKeys.insert(key);

	}
	else if (action == GLFW_RELEASE)
	{
		app.onKeyReleased(key);
		gDownKeys.erase(key);

	}
}

static void keyHoldCallback()
{
	for (set <int>::iterator iter = gDownKeys.begin(); iter != gDownKeys.end(); ++iter)
	{
		app.onKeyHold(*iter);
	}
}

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		app.onMousePressed(button);
		gDownMouseButtons.insert(button);
	}
	else if (action == GLFW_RELEASE)
	{
		app.onMouseReleased(button);
		gDownMouseButtons.erase(button);
	}
}

//! Called in main function
static void mouseButtonHoldCallback()
{
	for (set <int>::iterator iter = gDownMouseButtons.begin(); iter != gDownMouseButtons.end(); ++iter)
	{
		app.onMouseHold(*iter);
	}
}

static void cursor_position_callback(GLFWwindow* window, double xPos, double yPos)
{
	//app.onMouseMoved (xPos, yPos);	
	app.onMouseMoved(xPos, RESOLUTION_Y - yPos);
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create m_a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(RESOLUTION_X, RESOLUTION_Y, "", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowSizeCallback(window, onWindowResized);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	onWindowResized(window, RESOLUTION_X, RESOLUTION_Y);

	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	double prevTime = glfwGetTime();
	app.start();

	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		double elapsedTime = currentTime - prevTime;

		app.update(elapsedTime);
		app.draw();

		keyHoldCallback();
		mouseButtonHoldCallback();

		glfwSwapBuffers(window);
		glfwPollEvents();

		prevTime = currentTime;
	}

	glfwTerminate();
	return 0;
}