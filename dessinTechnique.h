#pragma once
#include "objetgeom.h"
#include <vector>
using namespace std;
class dessinTechnique
{
	point2D origine;
	vector<ObjetGeom*> liste_objets;

public:
	dessinTechnique();
	dessinTechnique(const point2D &p);
	void set_origine(const point2D &); 
    void vider();
	point2D get_origine()const;
	void afficher() const;
	double aire()const;
	void ajouter(ObjetGeom*);
	int nb_element()const;
	void deplacement(const point2D&);
	double perimetre() const;
    void suppr_dernier();
    vector<ObjetGeom*> get_liste_objets()const;
	~dessinTechnique();
};

