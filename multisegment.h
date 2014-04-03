#pragma once
#include "segment.h"
#include <iostream>
#include <vector>
using namespace std;
class multisegment : public ObjetGeom
{
    vector<segment> liste_seg;
    double get_longueur()const;

public:
    multisegment(const segment &, const segment&);
	void ajout_seg(const segment&);
	void suppr_dern_seg();
	void set_longueur(const double&);
    void deplacement(const point2D &);
    vector<segment> get_liste_seg() const;
	~multisegment();

	//les instanciations des fonctions virtuelles:
	virtual void affiche() const;
	virtual double aire()const;

};

