#include "Complex.h"
#include <strstream>

Complex operator+(const Complex& f, const Complex& s)
{
	return Complex(f.c_x + s.c_x, f.c_y + s.c_y);
}

Complex operator-(const Complex& f, const Complex& s)
{
	return Complex(f.c_x - s.c_x, f.c_y - s.c_y);
}

Complex operator*(const Complex& f, const Complex& s)
{
	return Complex(f.c_x * s.c_x - f.c_y * s.c_y, f.c_x * s.c_y + f.c_y * s.c_x);
}

Complex operator/(const Complex& f, const Complex& s)
{
	double div = s.c_x * s.c_x + s.c_y * s.c_y;
	return Complex((f.c_x * s.c_x + f.c_y * s.c_y) / div, (f.c_y * s.c_x - f.c_x * s.c_y) / div);
}

Complex operator+(const Complex& c, const double s)
{
	return Complex(c.c_x + s, c.c_y);
}

Complex operator-(const Complex& c, const double s)
{
	return Complex(c.c_x - s, c.c_y);
}

Complex operator*(const Complex& c, const double s)
{
	return Complex(c.c_x * s, c.c_y * s);
}

Complex operator/(const Complex& c, const double s)
{
	return Complex(c.c_x / s, c.c_y / s);
}

Complex operator^(const Complex& c, const double n)
{
	double m = pow(c.Module(), n), a = c.Arg() * n;
	return Complex(m * cos(a), m * sin(a));
}

const char* Complex::ToString() const
{
	std::strstream str;
	str << c_x << " + i * " << c_y << '\0';
	return str.str();
}

Complex& Complex::operator=(const Complex& c)
{
	c_x = c.c_x; c_y = c.c_y;
	return *this;
}

Complex& Complex::operator+=(const Complex& c)
{
	c_x += c.c_x;
	c_y += c.c_y;
	return *this;
}

Complex& Complex::operator-=(const Complex& c)
{
	c_x -= c.c_x;
	c_y -= c.c_y;
	return *this;
}

Complex& Complex::operator*=(const Complex& c)
{
	double x = c_x, y = c_y;
	c_x = x * c.c_x - y * c.c_y;
	c_y = x * c.c_y + y * c.c_x;
	return *this;
}

Complex& Complex::operator/=(const Complex& c)
{
	double x = c_x, y = c_y, 
		div = c.c_x * c.c_x + c.c_y * c.c_y;
	c_x = (x * c.c_x + y * c.c_y) / div;
	c_y = (y * c.c_x - x * c.c_y) / div;
	return *this;
}

Complex& Complex::operator+=(const double c)
{
	c_x += c;
	return *this;
}

Complex& Complex::operator-=(const double c)
{
	c_x -= c;
	return *this;
}

Complex& Complex::operator*=(const double c)
{
	c_x *= c;
	c_y *= c;
	return *this;
}

Complex& Complex::operator/=(const double c)
{
	c_x /= c;
	c_y /= c;
	return *this;
}

Complex& Complex::operator^(const double n)
{
	double m = pow(Module(), n), a = Arg() * n;
	c_x = m * cos(a);
	c_y = m * sin(a);
	return *this;
}
