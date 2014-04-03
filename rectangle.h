#pragma once
#include "quadrilatere.h"

class rectangle : public quadrilatere
{
private:
	double largeur;
	double longueur;
public:
    virtual double aire() const;
    virtual void affiche()const;

	double get_largeur()const;
	double get_longueur() const;
	void set_largeur(const double&);
	void set_longueur(const double&);
    rectangle(const point2D&, const double &l,const double &L);
    rectangle(const point2D &p1,const point2D &p2, const point2D &p3, const point2D &p4);
};

