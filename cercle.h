#pragma once
#include "objetgeom.h"
class cercle : public ObjetGeom
{
	double rayon;
	point2D centre;

public:
	cercle(const point2D&, const double&);
	cercle();
	point2D get_centre() const;
	void set_centre(const point2D&);
	void set_rayon(const double&);
	double get_rayon()const;
	double aire() const;
	void affiche()const;
	void ecrire(ostream &os) const;
	void deplacement(const point2D&);

protected:
	void actualise_perimetre();
};



// on surcharge la lecture de point2D 
ostream &operator <<(ostream &os, const cercle &p);

