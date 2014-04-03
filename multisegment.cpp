#include "multisegment.h"


multisegment::multisegment(const segment &s1, const segment &s2)
{
    ajout_seg(s1);
    ajout_seg(s2);
    nom = "multisegment";
}

void multisegment::ajout_seg(const segment &s){
   // si premier segment ajout
   if (liste_seg.size()==0)
   {
      liste_seg.push_back(s);
       set_longueur(s.get_longueur());
   }
   // sinon
   else
   {  //test si l'extremite et l'origine se rejoignent
       if ( (liste_seg[0].get_origine().get_x() == s.get_extremite().get_x())   &&  (liste_seg[0].get_origine().get_y() == s.get_extremite().get_y()) )
     {
        cout << "Ajout impossible car l'extremite est egale a l'origine du multisegments" << endl;
     } // test si les segments ne se suivent pas
       else if( (liste_seg[liste_seg.size() -1].get_extremite().get_x() != s.get_origine().get_x())
                ||  (liste_seg[liste_seg.size() -1].get_extremite().get_y() != s.get_origine().get_y()))
     {
        cout << "Ajout impossible car l'origine est differente de l'origine du segment precedent" << endl ;
     } // tout bon ajout du segment
     else
     {
        liste_seg.push_back(s);
         set_longueur(this->get_longueur() + s.get_longueur());
     }
   }
}

void multisegment::suppr_dern_seg(){
   if (liste_seg.size()==2)
   {
      cout << "Il n'y a que 2 segments on ne peut pas supprimer le dernier" << endl;
   }
   else
   {
	   segment dern = liste_seg[liste_seg.size() -1];
	   liste_seg.pop_back();
	   set_longueur(get_longueur() - dern.get_longueur());
   }
}

void multisegment::affiche() const{
	ObjetGeom::affiche();
    for (int unsigned i = 0; i < liste_seg.size(); i++){
		cout << "\t segment numero " << i << ": ";
		liste_seg[i].affiche();
	}
    cout << "la longueur totale du multisegment est: " <<  perimetre << endl
         <<"et est composé de " << liste_seg.size() <<" elements."<<endl;
}

double multisegment::aire()const{
    return 0;
}

multisegment::~multisegment()
{
	liste_seg.clear();
}

double multisegment::get_longueur()const{
    return perimetre;
}

void multisegment::set_longueur(const double &l){
    perimetre = l;
}

void multisegment::deplacement(const point2D &p)
{
    for (int unsigned i = 0 ; i < liste_seg.size() ; i ++){
        segment temp = liste_seg.at(i);
        temp.deplacement(p);
        liste_seg.at(i) = temp;
    }
}

vector<segment> multisegment::get_liste_seg()const
{
    return liste_seg;
}
