#pragma once
#include "cercle.h"

class ellipse : public ObjetGeom
{
	cercle c1;
	cercle c2;

public:

	ellipse(const cercle&,const cercle&);
	void deplacement(const point2D&);
	cercle get_c1()const;
    cercle get_c2()const;
    double perimetre();
	void set_c1(const cercle &);
	void set_c2(const cercle &);

    //instanciation des fonctions virtuelles de ObjetGeom
    virtual void affiche()const;
    virtual double aire() const;
	
};

