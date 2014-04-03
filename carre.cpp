#include "carre.h"
#include <iostream>
#include <cmath>

using namespace std;

carre::carre(const point2D &p,const double &taille)
    :quadrilatere(p,p,p,p){ // initialisation d'un quadrilatére
    point2D p1 = p;
    p1.deplacementX(abs(taille));
   set_point2(p1);
   p1.deplacementY(abs(taille));
   set_point3(p1);
   p1.deplacementX(-abs(taille));
   set_extremite(p1);
   cote = taille;
   perimetre = cote * 4;
   type = "carre";
}

double carre::get_cote() const{
	return cote;
}

void carre::set_cote(const double &d){
	cote = d;
    perimetre = cote * 4;
}

void carre::affiche() const{
	quadrilatere::affiche();
    cout << "et je possËde un cÙtÈ de : " << cote <<endl;
}

double carre::aire() const{
	return cote * cote;
}

