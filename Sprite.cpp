#define _USE_MATH_DEFINES
#include "Sprite.h"
#include <cmath>



Sprite::Sprite()
{
	m_width = 10;
	m_height = 10;
	m_textureID = 0;
}

Sprite::Sprite(const std::string& file)
{
	loadTexture(file);
}

Sprite::~Sprite()
{}

void Sprite::loadTexture(const std::string& file)
{
	glGenTextures(1, &m_textureID);

	CBitmap bitmap(file.c_str());

	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bitmap.GetWidth(), bitmap.GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap.GetBits());

	m_width = bitmap.GetWidth();
	m_height = bitmap.GetHeight();
}


void Sprite::draw(Vector position, Color color, Vector scale, float radian, BlendMode blendMode)
{
	float halfW = m_width * 0.5f * scale.mVal[0];
	float halfH = m_height * 0.5f * scale.mVal[1];

	float displacementX = halfW * cos(radian) - halfH * sin(radian);
	float displacementY = halfW * sin(radian) + halfH * cos(radian);

	glColor4f(color.m_r, color.m_g, color.m_b, color.m_a);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_textureID);


	switch (blendMode)
	{

	case BlendMode::ADDITIVE:

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

		break;

	case BlendMode::ALPHA:

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		break;

	case BlendMode::MULTIPLY:

		glEnable(GL_BLEND);
		glBlendFunc(GL_DST_COLOR, GL_ZERO);

		break;
	}


	glEnable(GL_ALPHA_TEST);

	// Please note that GL_QUADS is not supported in OpenGL ES, switch it to GL_TRIANGLES for better compability
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 1.0);	glVertex3f(position.mVal[0] - displacementX, position.mVal[1] - displacementY, 0);
	glTexCoord2d(1.0, 1.0);	glVertex3f(position.mVal[0] + displacementY, position.mVal[1] - displacementX, 0);
	glTexCoord2d(1.0, 0.0);	glVertex3f(position.mVal[0] + displacementX, position.mVal[1] + displacementY, 0);
	glTexCoord2d(0.0, 0.0);	glVertex3f(position.mVal[0] - displacementY, position.mVal[1] + displacementX, 0);
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}


