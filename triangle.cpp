#include "triangle.h"
#include <iostream>
#include <cmath>
using namespace std;

point2D triangle::get_point2() const {
	return point2;
}

void triangle::set_point2(const point2D &p){
	point2 = p;
}


triangle::triangle()
    : ObjetGeom(point2D(10,10),point2D(150,150))	{	// on appelle le constructeur d'objetgeom
    point2 = point2D(100,50);
        nom = "triangle";
}


triangle::triangle(const point2D &p1,const point2D &p2,const point2D &p3)
	: ObjetGeom(p1,p3)	{	// on appelle le constructeur d'objetgeom
		point2 = p2;
		nom = "triangle";
}

double triangle::aire() const{
	//aire calcul� en partant du principe que l'aire du triangle est �gale � la moiti� de celle du parrallelogramme associ�

	return	 (  		ObjetGeom::get_perimetre()												// c'est la distance de l'origine � l'extremit�, d�finie dans ObjetGeom
				
				*		 sqrt(pow(get_origine().get_x() - point2.get_x(), 2) +					// c'est la distance de l'origine � point2
						 pow(get_origine().get_y() - point2.get_y(), 2))
				/ 2.0 );
}

void triangle::deplacement(const point2D &p) {
	ObjetGeom::deplacement(p); // on deplace l'origine et l'extremit� � l'aide de la methode d'objetgeom
	point2.deplacement(p);		//puis on deplace point2
}

void triangle::affiche() const{
	ObjetGeom::affiche();
	cout << "points de coordonn�es:( (" << get_origine().get_x() << " , " << get_origine().get_y() << ") , ("
										<< point2.get_x() << " , " << point2.get_y()  << ") , ("
										<< get_extremite().get_x() << " , " << get_extremite().get_y() << ") )" << endl;
}

double triangle::perimetre()const{
	return	(				ObjetGeom::get_perimetre()												// c'est la distance de l'origine � l'extremit�, d�finie dans ObjetGeom
			 
			 +				sqrt(pow(get_extremite().get_x() - point2.get_x(), 2) +    // c'est la distance de l'extremit� � point2
								 pow(get_extremite().get_y() - point2.get_y(), 2))
			
			 +				 sqrt(pow(get_origine().get_x() - point2.get_x(), 2) +		// c'est la distance de l'origine � point2
								  pow(get_origine().get_y() - point2.get_y(), 2))
			);

}

