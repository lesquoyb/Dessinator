#pragma once
#include "quadrilatere.h"
#include "cercle.h"

class quadrangle : public quadrilatere
{
	cercle c;
public:
	quadrangle(const point2D&, const point2D&, const point2D&, const point2D&,const cercle& );
	cercle get_cercle() const;
	void set_cercle(const cercle&);
	void affiche()const;
    double aire() const;
};

