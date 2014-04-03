#include "arcDeCercle.h"
#include <cmath>

arcDeCercle::arcDeCercle(const point2D &p, const double &r, const angle &an1, const angle &an2)
	:cercle(p,r){
	a1 = an1;
	a2 = an2;
	actualise_perimetre();
}


angle arcDeCercle::get_angle1() const{
	return a1;
}

angle arcDeCercle::get_angle2() const{
	return a2;
}

void arcDeCercle::set_angle1(const angle &a){
	a1 = a;
	actualise_perimetre();
}

void arcDeCercle::set_angle2(const angle &a){
	a2 = a;
	actualise_perimetre();
}

void arcDeCercle::affiche() const{

}

void arcDeCercle::actualise_perimetre(){
	perimetre = (a2.get_angle() - a1.get_angle()) * get_rayon();
}
double arcDeCercle::aire() const{
	
	return (
				perimetre
			* get_rayon()
			/			2
		);
}
