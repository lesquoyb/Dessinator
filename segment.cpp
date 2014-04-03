#include "segment.h"
#include <iostream>
using namespace std;

segment::segment()
    :ObjetGeom(){
         longueur = perimetre;
         nom = "segment";
  }

segment::segment(const point2D &p1, const point2D &p2)
:ObjetGeom(p1,p2)
{
    longueur = perimetre;
    nom = "segment";

}


double segment::get_longueur()const
{
	return longueur;
}

void segment::set_origine(const point2D &p)
{
	ObjetGeom::set_origine(p);
	longueur = perimetre;
}

void segment::set_extremite(const point2D &p)
{
	ObjetGeom::set_extremite(p);
	longueur = perimetre;
}

void segment::affiche()const{
	ObjetGeom::affiche();
	cout<< origine << " et " << extremite << "d'une longueur de "<< longueur << endl;
}




double segment::aire()const{
    return 0;
}
