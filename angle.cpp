#include "angle.h"
#include <math.h>


angle::angle()
{
	Angle = 0;
}

angle::angle(const double &d)
{
	Angle = d;
}

angle::angle(const point2D &p1, const point2D &p2, const point2D &p3)
{
	// on calcule l'angle en appliquant le théorème d'Al-Kashi
	Angle = (acos(
					(

						pow(sqrt(pow(p1.get_x() - p2.get_x(), 2) +						// c'est la distance de p1 à p2 au carré
						pow(p1.get_y() - p2.get_y(), 2)), 2)

						+ pow(sqrt(pow(p3.get_x() - p2.get_x(), 2) +					// c'est la distance de p3 à p2 au carré
						pow(p3.get_y() - p2.get_y(), 2)),2)

						- pow(sqrt(pow(p1.get_x() - p3.get_x(), 2) +					// c'est la distance de p1 à p3 au carré
						pow(p1.get_y() - p3.get_y(), 2)),2)
					)

				/
					
					(
					2 
					*
					sqrt(pow(p1.get_x() - p2.get_x(), 2) +								// c'est la distance de p1 à p2
					pow(p1.get_y() - p2.get_y(), 2))
					*
					sqrt(pow(p3.get_x() - p2.get_x(), 2) +								// c'est la distance de p3 à p2 
					pow(p3.get_y() - p2.get_y(), 2))

					)
				))
			 
				*180
				/
				(4.0*atan(1.0))// conversion en degres
				;
}

double angle::get_angle() const{
	return Angle;
}

void angle::set_angle(const double &a){
    Angle = a;
}

void angle::affiche()const{
   cout << "L'angle est de : " << this->get_angle();
}
