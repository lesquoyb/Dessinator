#include "rectangle.h"
#include "segment.h"
#include <iostream>
#include <math.h>
using namespace std;

rectangle::rectangle(const point2D &p1, const double &L, const double &l)
    :  quadrilatere(p1,point2D(p1.get_x()+L, p1.get_y()),point2D(p1.get_x()+L, p1.get_y() + l),point2D(p1.get_x(), p1.get_y() + l)) {
    longueur = L;
    largeur = l;
    perimetre = (2 * largeur) + ( 2* longueur);
    type = "rectangle";
}

//ce constructeur est uniquement utilisé en interne, une fois qu'on est sur que le rectangle de base répond à nos exigeances
rectangle::rectangle(const point2D &p1, const point2D &p2, const point2D &p3, const point2D &p4)
    :  quadrilatere(p1, p2, p3, p4) {
    longueur = sqrt(pow(p1.get_x() - p2.get_x(),2));
    largeur = sqrt(pow(p2.get_y() - p3.get_y(),2));
    perimetre = (2 * largeur) + ( 2* longueur);
	type = "rectangle";
}

double rectangle::aire() const
{
    return longueur*largeur;
}

void rectangle::affiche()const{
    quadrilatere::affiche();
}



double rectangle::get_largeur() const
{
    return largeur;
}

double rectangle::get_longueur() const
{
    return longueur;
}

void rectangle::set_largeur(const double  &l)
{
    largeur = l;
    perimetre = (2 * largeur) + ( 2* longueur);

}

void rectangle::set_longueur(const double &l)
{
    longueur = l;
    perimetre = (2 * largeur) + ( 2* longueur);
}
