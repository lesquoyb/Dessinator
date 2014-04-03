#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "objetgeom.h"

class triangle : public ObjetGeom
{
private:
	point2D point2;
public:

	point2D get_point2() const;
	void set_point2(const point2D&);
    triangle(const point2D&,const point2D&,const point2D&);
    triangle();
	double aire() const;
	void deplacement(const point2D&);
	double perimetre() const;
	void affiche() const;										//l'affichage en console

};

#endif
