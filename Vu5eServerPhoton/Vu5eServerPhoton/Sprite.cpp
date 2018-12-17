#include "Sprite.h"


Sprite::Sprite()
{
	m_width = 100;
	m_height = 100;
	m_textureID = 0;
}

Sprite::Sprite(const std::string& file)
{
	//m_textureID = file; notsure
	m_textureID = 0;

	m_width = 100;
	m_height = 100;

	glGenTextures(1, &m_textureID);

	LoadSprite(file);
}

Sprite::~Sprite()
{
	printf("Deleted Sprite\n");
}

void Sprite::draw(float x, float y, Vector scale, float rotation, Color col)
{
	Matrix originTranslate = Matrix::makeTranslationMatrix(-x, -y, 0);

	Matrix translateMatrix = Matrix::makeTranslationMatrix(x, y, 0.0f);
	Matrix scaleMatrix = Matrix::makeScaleMatrix(scale);
	Matrix rotationMatrix = Matrix::makeRotateMatrix(rotation, Vector(0.0f, 0.0f, 1.0f));

	Matrix modelMatrix = translateMatrix * rotationMatrix * scaleMatrix * originTranslate;

	glLoadMatrixf((GLfloat*)modelMatrix.mVal);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_ALPHA_TEST);

	//==============vertex array method
	glColor4f(col.m_r, col.m_g, col.m_b, col.m_a);

	float halfW = m_width * 0.5f;
	float halfH = m_height * 0.5f;

	GLfloat vertices[] =
	{
		x - halfW, y - halfH, 0,
		x + halfW, y - halfH, 0,
		x + halfW, y + halfH, 0,

		x + halfW, y + halfH, 0,
		x - halfW, y + halfH, 0,
		x - halfW, y - halfH, 0
	};

	GLfloat textureUV[] =
	{
		0, 1,
		1, 1,
		1, 0,

		1, 0,
		0, 0,
		0, 1
	};

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, textureUV);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}

void Sprite::draw(Vector pos, Vector scale, float rotation, Color col)
{
	Matrix originTranslate = Matrix::makeTranslationMatrix(-pos.mVal[0], -pos.mVal[1], 0);

	Matrix translateMatrix = Matrix::makeTranslationMatrix(pos.mVal[0], pos.mVal[1], 0.0f);
	Matrix scaleMatrix = Matrix::makeScaleMatrix(scale);
	Matrix rotationMatrix = Matrix::makeRotateMatrix(rotation, Vector(0.0f, 0.0f, 1.0f));

	Matrix modelMatrix = translateMatrix * rotationMatrix * scaleMatrix * originTranslate;

	glLoadMatrixf((GLfloat*)modelMatrix.mVal);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);

	//==============vertex array method
	glColor4f(col.m_r, col.m_g, col.m_b, col.m_a);
	//glColor4f(0, 0, col.m_b, col.m_a);

	float halfW = m_width * 0.5f;
	float halfH = m_height * 0.5f;

	GLfloat vertices[] =
	{
		pos.mVal[0] - halfW, pos.mVal[1] - halfH, 0,
		pos.mVal[0] + halfW, pos.mVal[1] - halfH, 0,
		pos.mVal[0] + halfW, pos.mVal[1] + halfH, 0,

		pos.mVal[0] + halfW, pos.mVal[1] + halfH, 0,
		pos.mVal[0] - halfW, pos.mVal[1] + halfH, 0,
		pos.mVal[0] - halfW, pos.mVal[1] - halfH, 0
	};

	GLfloat textureUV[] =
	{
		0, 1,
		1, 1,
		1, 0,

		1, 0,
		0, 0,
		0, 1
	};

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, textureUV);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
}


void Sprite::LoadSprite(const std::string& path)
{
	std::vector<unsigned char> image;
	unsigned width, height;
	unsigned error = lodepng::decode(image, width, height, path);

	if (error != 0)
	{
		std::cout << "png load error :" << lodepng_error_text(error) << std::endl;
		return;
	}

	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//bilinear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

}
