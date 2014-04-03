#pragma once
#include "quadrilatere.h"

class losange : public quadrilatere
{
private:
	double diagonale2;
	double diagonale1;
public:
	void affiche() const;
    double aire() const;
	double get_diag1() const;
	double get_diag2() const;
	void set_diag1(const double&);
	void set_diag2(const double&);
    losange(const point2D&, const point2D&, const double&, const double&);
};

