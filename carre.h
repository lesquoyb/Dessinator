#pragma once
#include "quadrilatere.h"
#include "point2d.h"
class carre : public quadrilatere
{
private:
	double cote;

public:

	carre(const point2D &,const double &);
	double get_cote() const;
	void set_cote(const double&);
	virtual void affiche()const;
	virtual double aire()const;
	
};

