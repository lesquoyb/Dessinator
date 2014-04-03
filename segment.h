#pragma once
#include "objetgeom.h"

class segment :public ObjetGeom
{
	double longueur;
public:
    segment();
	segment(const point2D&,const point2D&);
	virtual void affiche() const;
	double get_longueur()const;
	void set_origine(const point2D&);
	void set_extremite(const point2D&);

private:
	virtual double aire() const;
};

