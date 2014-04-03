#include "quadrilatere.h"
#include <iostream>
#include <cmath>
using namespace std;


/*
double quadrilatere::aire()const{

}
*/
void quadrilatere::deplacement(const point2D &p){
	ObjetGeom::deplacement(p); // on déplace O et E grace à la méthode de objetgeom
	point2.deplacement(p);
	point3.deplacement(p);
}

double quadrilatere::get_perimetre() const{
	return perimetre;
}

point2D quadrilatere::get_point2() const{
	return point2;
}

point2D quadrilatere::get_point3() const{
    return point3;
}

string quadrilatere::get_type() const
{
    return type;
}

string quadrilatere::get_nom() const{
    return nom;
}


quadrilatere::quadrilatere(const point2D &p1, const point2D &p2, const point2D &p3, const point2D &p4)
: ObjetGeom(p1,p4){
	point2 = p2;
	point3 = p3;
	actualise_perimetre();
	nom = "quadrilatere";
}

void quadrilatere::set_point2(const point2D&p){
	point2 = p;
	actualise_perimetre();
}

void quadrilatere::set_point3(const point2D&p){
	point3 = p;
	actualise_perimetre();
}

void quadrilatere::actualise_perimetre(){
	perimetre = ObjetGeom::get_perimetre()									// la distance de l'origine à l'extremité

				+ sqrt(pow(get_extremite().get_x() - point3.get_x(), 2) +   // c'est la distance de l'extremité à point3
				pow(get_extremite().get_y() - point3.get_y(), 2))

				+ sqrt(pow(point3.get_x() - point2.get_x(), 2) +			// c'est la distance de point3 à point2
				pow(point3.get_y() - point2.get_y(), 2))

				+ sqrt(pow(get_origine().get_x() - point2.get_x(), 2) +		// c'est la distance de l'origine à point2
				pow(get_origine().get_y() - point2.get_y(), 2))
			  ;
}

void quadrilatere::affiche()const{
	ObjetGeom::affiche();
	cout << " 4 points de coordonnees : " << endl << "( ("
		<< this->get_origine().get_x() << " , " << this->get_origine().get_y() << " ) , ("
		<< this->point2.get_x() << " , " << this->point2.get_y() << " ),("
		<< this->point3.get_x() << " , " << this->point3.get_y() << " ),("
		<< this->get_extremite().get_x() << " , " << this->get_extremite().get_y() << " ) )"
        << "je suis donc un " << type.c_str()
		<< endl;
}
