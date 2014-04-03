#include "cercle.h"
#include <cmath>
#include <iostream>
using namespace std;


cercle::cercle(const point2D &p, const double &r)
	:ObjetGeom() {
	centre = p;
	rayon = abs(r);
	actualise_perimetre();
	nom = "cercle";
}
;
cercle::cercle()
	: ObjetGeom(){
	centre = point2D(0.0, 0.0);
    rayon = 50;
	actualise_perimetre();
	nom = "cercle";
}

void cercle::set_rayon(const double &r){
	rayon = r;
	actualise_perimetre();
}

double cercle::get_rayon()const{
	return rayon;
}

void cercle::actualise_perimetre(){
	perimetre = 2 * 4 * atan(1.0) * rayon;
}

double cercle::aire() const{
	return pow(rayon, 2) * 4 * atan(1.0);
}


void cercle::deplacement(const point2D &p){
	centre.deplacement(p);
}
void cercle::set_centre(const point2D &p){
	centre = p;
}

point2D cercle::get_centre()const{
	return centre;
}

void cercle::affiche()const{
	ObjetGeom::affiche();
	cout << "un centre: " << centre << ", et d'un rayon: " << rayon << endl;
}

ostream &operator <<(ostream &os, const cercle &p){
	p.ecrire(os);
	return os;
}

void cercle::ecrire(ostream &os)const{
	os << " un cercle de centre " << centre << " et de rayon " << rayon << endl;
}
