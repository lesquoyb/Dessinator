#include "dessinTechnique.h"
#include <iostream>
using namespace std;

dessinTechnique::dessinTechnique()
{
	origine = point2D(0.0, 0.0);
}

dessinTechnique::dessinTechnique(const point2D &p)
{
	origine = p;
}

void dessinTechnique::afficher() const{
	cout << "je suis un dessin technique, et je suis composé de :" << endl;
    for (int unsigned i = 0; i < liste_objets.size(); i++){
		cout << "\t -";
		liste_objets[i]->affiche();
	}
}
void dessinTechnique::set_origine(const point2D &p){
    origine = p;
}

void dessinTechnique::vider()
{
    liste_objets.clear();
}

point2D dessinTechnique::get_origine()const{
	return origine;
}

double dessinTechnique::aire()const{
	double somme = 0;
    for (int unsigned i = 0; i < liste_objets.size(); i++){
		somme += liste_objets[i]->aire();
	}
	return somme;
}
void dessinTechnique::ajouter(ObjetGeom* b){
	liste_objets.push_back(b);
	b->deplacement(origine);
}
void dessinTechnique::deplacement(const point2D &p){
    for (int unsigned i = 0; i < liste_objets.size(); i++){
		liste_objets[i]->deplacement(p);
	}
}

int dessinTechnique::nb_element()const{
	return liste_objets.size();
}
double dessinTechnique::perimetre() const{
	double somme = 0;
    for (int unsigned i = 0; i < liste_objets.size(); i++){
        somme += liste_objets[i]->get_perimetre();
	}
    return somme;
}

void dessinTechnique::suppr_dernier()
{
    liste_objets.pop_back();
}

vector<ObjetGeom *> dessinTechnique::get_liste_objets() const
{
 return liste_objets;
}
dessinTechnique::~dessinTechnique()
{
    for (int unsigned i = 0; i < liste_objets.size(); i++){
        liste_objets.pop_back();
	}
}
