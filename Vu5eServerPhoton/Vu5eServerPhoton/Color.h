#ifndef COLOR_H
#define COLOR_H

class Color
{
private:

public:
	/**
	*R, G, B, A correlates to the 4 float values in Colors, Red, Green, Blue, and Alpha
	*/
	float r, g, b, a;

	//!Default Constructor
	Color()
	{

	}

	/**
	*Constructor for RGBA values in Color
	*/
	Color(float red, float green, float blue, float alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	/*Changes RGBA values based on 4 parameters*/
	void SetColor(float red, float blue, float green, float alpha)
	{
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	/*Changes current Color with a Color instance */
	void SetColor(Color newColor)
	{
		r = newColor.r;
		g = newColor.g;
		b = newColor.b;
		a = newColor.a;
	}

	//! Returns a Color() with RGBA values of White
	Color White()
	{
		r = 1.0;
		g = 1.0;
		b = 1.0;
		a = 1.0;

		return Color(r, g, b, a);
	}

	//! Returns a Color() with RGBA values of Black
	Color Black()
	{
		r = 0.0;
		g = 0.0;
		b = 0.0;
		a = 1.0;

		return Color(r, g, b, a);
	}

	//! Returns a Color() with RGBA values of Red
	Color Red()
	{
		r = 1.0;
		g = 0.0;
		b = 0.0;
		a = 1.0;

		return Color(r, g, b, a);
	}

	//! Returns a Color() with RGBA values of Green
	Color Green()
	{
		r = 0.0;
		g = 1.0;
		b = 0.0;
		a = 1.0;

		return Color(r, g, b, a);
	}

	//! Returns a Color() with RGBA values of Blue
	Color Blue()
	{
		r = 0.0;
		g = 0.0;
		b = 1.0;
		a = 1.0;

		return Color(r, g, b, a);
	}

	//! Returns a Color() with RGBA values of Purple
	Color Purple()
	{
		r = 0.8;
		g = 0.1;
		b = 1.0;
		a = 0.8;

		return Color(r, g, b, a);
	}
};

#endif // !COLOR_H
