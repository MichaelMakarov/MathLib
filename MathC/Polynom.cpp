#include "Polynom.h"
#include <strstream>


Polynom::Polynom(const size_t n)
{
	p_size = n + 1;
	p_pValues = new double[p_size];
	for (size_t i = 0; i < p_size; ++i)
		p_pValues[i] = 1.0;
}

Polynom::Polynom(const size_t n, const double* const pCs)
{
	p_size = n;
	p_pValues = new double[p_size];
	std::memcpy(p_pValues, pCs, p_size * DOUBLE_SIZE);
}

Polynom::Polynom(const Polynom& p)
{
	p_size = p.p_size;
	p_pValues = new double[p_size];
	std::memcpy(p_pValues, p.p_pValues, p_size * DOUBLE_SIZE);
}

Polynom::Polynom(const size_t n, const double a0, ...)
{
	va_list args;
	p_size = n;
	p_pValues = new double[p_size];
	p_pValues[0] = a0;
	__crt_va_start(args, a0);
	for (size_t i = 1; i < p_size; ++i)
		p_pValues[i] = __crt_va_arg(args, double);
	__crt_va_end(args);
}

Polynom::Polynom(const std::initializer_list<double> cs)
{
	if (cs.size() == 0) throw "At least one coefficient should be provided!";
	p_size = cs.size();
	p_pValues = new double[p_size];
	size_t i = 0;
	for (const double& c : cs) p_pValues[i++] = c;
}

Polynom::~Polynom()
{
	delete[] p_pValues;
	p_pValues = nullptr;
	p_size = 0;
}

const char* Polynom::ToString(const char* s) const
{
	std::strstream str;
	for (size_t i = 0; i < p_size; ++i)
	{
		if (p_pValues[i] < 0.0) str << "- " << -p_pValues[i];
		else
		{
			if (i > 0) str << "+ ";
			str << p_pValues[i];
		}
		if (i > 0)
		{
			str << " * " << s;
			if (i > 1) str << "^" << i;
		}
		str << " ";
	}
	str << '\0';
	return str.str();
}

const size_t Polynom::Degree() const
{
	return p_size - 1;
}

const double* const Polynom::Coefficients() const
{
	return p_pValues;
}

Polynom& Polynom::operator=(const Polynom& p)
{
	p_size = p.p_size;
	p_pValues = new double[p_size];
	std::memcpy(p_pValues, p.p_pValues, p_size * DOUBLE_SIZE);
	return *this;
}

double& Polynom::operator[](const size_t index) const
{
	return p_pValues[index];
}

const double Polynom::operator()(const double arg) const
{
	double result = p_pValues[0], add = 1.0;
	for (size_t i = 1; i < p_size; ++i)
	{
		add *= arg;
		result += add;
	}
	return result;
}

Polynom operator+(const Polynom& f, const Polynom& s)
{
	if (s.p_size <= f.p_size)
	{
		Polynom p(f);
		for (size_t i = 0; i < s.p_size; ++i)
			p.p_pValues[i] += s.p_pValues[i];
		return p;
	}
	else {
		Polynom p(s);
		for (size_t i = 0; i < f.p_size; ++i)
			p.p_pValues[i] += f.p_pValues[i];
		return p;
	}
}

Polynom operator-(const Polynom& f, const Polynom& s)
{
	if (s.p_size <= f.p_size)
	{
		Polynom p(f);
		for (size_t i = 0; i < s.p_size; ++i)
			p.p_pValues[i] -= s.p_pValues[i];
		return p;
	}
	else {
		Polynom p(s);
		size_t i;
		for (i = 0; i < f.p_size; ++i)
			p.p_pValues[i] -= f.p_pValues[i];
		for (i = 0; i < p.p_size; ++i)
			p.p_pValues[i] = -p.p_pValues[i];
		return p;
	}
}

Polynom operator*(const Polynom& f, const Polynom& s)
{
	size_t size = f.p_size + s.p_size - 1, 
		i, j, diml, dimh;
	Polynom p(size - 1);
	const double* pArrl, * pArrh;
	if (f.p_size <= s.p_size)
	{
		pArrh = s.p_pValues;
		pArrl = f.p_pValues;
		diml = s.p_size;
		dimh = f.p_size;
	}
	else {
		pArrh = f.p_pValues;
		pArrl = s.p_pValues;
		diml = s.p_size;
		dimh = f.p_size;
	}
	for (i = 0; i < dimh; ++i)
	{
		p.p_pValues[i] = 0.0;
		for (j = 0; j <= i && j < diml; ++j)
			p.p_pValues[i] += pArrh[i - j] * pArrl[j];
	}
	for (i = dimh; i < size; ++i)
	{
		p.p_pValues[i] = 0.0;
		for (j = i - dimh + 1; j < diml; ++j)
			p.p_pValues[i] += pArrh[dimh - j] * pArrl[j];
	}
	return p;
}
