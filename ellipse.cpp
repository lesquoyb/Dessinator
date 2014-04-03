#include "ellipse.h"


ellipse::ellipse(const cercle &c,const cercle &d)
	:ObjetGeom(c.get_centre(),d.get_centre()) {
	c1 = c;
	c2 = d;
	nom = "ellipse";
}


void ellipse::deplacement(const point2D &p){
	c1.deplacement(p);
	c2.deplacement(p);
}

cercle ellipse::get_c1()const{
	return c1;
}

cercle ellipse::get_c2()const{
	return c2;
}

double ellipse::perimetre(){
     cout << "le calcul étant trop complexe, cette classe retourne 0"<<endl;
return 0;
}

void ellipse::set_c1(const cercle &c){
	c1 = c;
}

void ellipse::set_c2(const cercle &c){
	c2 = c;
}


//instanciation des fonctions virtuelles de ObjetGeom
void ellipse::affiche()const{
	ObjetGeom::affiche();
	cout << c1 << " et " << c2 << endl;
}

double ellipse::aire() const{
    cout << "le calcul étant trop complexe, cette classe retourne 0"<<endl;
return 0;
}
