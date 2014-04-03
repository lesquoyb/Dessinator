#pragma once
#include "point2d.h"
class angle
{
	double	Angle;
public:
	angle();
	angle(const double&);
	angle(const point2D&, const point2D&, const point2D&);
	double get_angle() const;
	void set_angle(const double&);
    void affiche()const;
};
// 
