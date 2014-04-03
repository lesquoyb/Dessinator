#include "objetgeom.h"
#include <iostream>
#include <cmath>
#include <QtXml/qdom.h>

using namespace std;



void ObjetGeom::deplacement(const point2D &p){
	origine.deplacement(p);
    extremite.deplacement(p);
}

ObjetGeom::ObjetGeom(const point2D &p1, const point2D &p2)
{
	extremite = p2;
    origine = p1;
	actualise_perimetre();
}

ObjetGeom::ObjetGeom(){
    origine = point2D(0.0, 3.0);
    extremite = point2D(10.0, 20.0);
	actualise_perimetre();
}
point2D ObjetGeom::get_origine()const { return origine; }


point2D ObjetGeom::get_extremite() const { return extremite; }


double ObjetGeom::get_perimetre() const { return perimetre; }


void ObjetGeom::set_origine(const point2D &p)
{
	origine = p;
	actualise_perimetre();
}


void ObjetGeom::set_extremite(const point2D &p)
{
	extremite = p;
	actualise_perimetre();
}


void ObjetGeom::actualise_perimetre()
{
	perimetre = sqrt(pow(extremite.get_x() - origine.get_x(), 2) +
		pow(extremite.get_y() - origine.get_y(), 2));
}

void ObjetGeom::set_perimetre(const double &d){
	perimetre = d;
}

void ObjetGeom::affiche()const{
    cout << "un " << nom.c_str() << " compose de: ";
}
