#pragma once
#include "cercle.h"
#include "angle.h"
class arcDeCercle : public cercle
{
private:
	angle a1;
	angle a2;

public:
	arcDeCercle(const point2D&,const double&,const angle&,const angle&);
	angle get_angle1() const;
	angle get_angle2() const;
    void set_angle1(const angle&);
    void set_angle2(const angle&);
	void affiche() const;
	double aire()const;

protected:
	void actualise_perimetre();

};

