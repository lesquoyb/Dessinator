#pragma once
#include "objetgeom.h"
class quadrilatere : public ObjetGeom
{
public:
	virtual void affiche()const = 0;
	void deplacement(const point2D&);
    point2D get_point2() const;
    point2D get_point3() const;
    string get_type()const;
protected:
// on ajoute 2 points aux 2 déjà présents dans objetgeom
	point2D point2;
	point2D point3;
    string type;

//operations spécifiques aux quadrilateres

    virtual double aire()const = 0;

    string get_nom() const;
    double get_perimetre() const;
	quadrilatere(const point2D&, const point2D&, const point2D&, const point2D&);
	void set_point2(const point2D&);
	void set_point3(const point2D&);
	void actualise_perimetre();
	
};

