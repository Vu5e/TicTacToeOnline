#pragma once
#include <string>
#include <GLFW/glfw3.h>
#include "bitmap.h"
#include "Vector.h"

enum BlendMode
{
	NONE = 0,
	ADDITIVE,
	ALPHA,
	MULTIPLY
};

struct Color
{
	float m_r;
	float m_g;
	float m_b;
	float m_a;

	Color()
	{
		m_r = 1.0f;
		m_g = 1.0f;
		m_b = 1.0f;
		m_a = 1.0f;
	}

	Color(float r, float g, float b, float a)
	{
		this->m_r = r;
		this->m_g = g;
		this->m_b = b;
		this->m_a = a;
	}
};


class Sprite
{
private:
	unsigned int m_width;
	unsigned int m_height;
	GLuint	m_textureID;

public:
	Sprite();
	Sprite(const std::string& file);
	~Sprite();

	void loadTexture(const std::string& file);

	void draw(Vector position, Color color, Vector scale, float radian, BlendMode blendMode);
};

