#ifndef SPRITE_H
#define SPRITE_H

#include <GLFW/glfw3.h>
#include "matrix.h"
#include "lodepng.h"
#include <iostream>
#include <string>
//#include "color.h"

enum BlendMode
{
	NONE = 0,
	ADDITIVE,
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
	unsigned int m_width = 100;
	unsigned int m_height = 100;
	unsigned int m_textureID = 0;

public:
	Sprite();
	Sprite(const std::string& file);

	~Sprite();

	void draw(float x, float y, Vector scale, float rotation, Color col);

	void draw(Vector pos, Vector scale, float rotation, Color col);
	void LoadSprite(const std::string& path);
};



#endif