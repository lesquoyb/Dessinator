#include "losange.h"
#include "segment.h"
#include <cmath>


losange::losange(const point2D &p1, const point2D &p2, const double &d1, const double &d2)
 : quadrilatere(p1,p1,p1,p1)
{
   // test abscisses ou ordonnees egales ou diagonale(s) nulle(s)
   // contrainte aussi diagonale > a la différence des coordonées

    if ( (p1.get_x() == p2.get_x())    ||  (p2.get_y() == p1.get_y())
            ||      ( d1 <= 0 ) || ( d2 <= 0)    ||
          ( (abs(p1.get_x()-p2.get_x()) >= d1) ||    ( abs (p2.get_y()-p1.get_y()) >= d2)))
     {

      cout << "Ceci n'est pas un losange voici un losange par defaut!\n";
     set_origine(p1);
     point2D save = p1;
     point2D p(50,50);
     point2D pt = p1;
     pt.deplacement(p);
     set_point2(pt);
     pt = save;
     pt.deplacementX(100);
     set_point3(pt);
     pt = save;
     pt.deplacement(point2D(50,-200));
     set_extremite(pt);
     segment s1(p1, get_point3());
     diagonale1 = s1.get_longueur();
     segment s2(get_point2(), get_extremite());
     diagonale2 = s2.get_longueur();
    }
     else
     {

     // test point 1 / abscisses
         point2D p2b = p2;
         point2D pt = p1;
      if (p1.get_x() > p2.get_x()) 
         {
         pt.set_x(p1.get_x()+2*(p1.get_x()-p2.get_x()));
         }
      // test point2 / ordonnées
      if (p2.get_y() < p1.get_y()) 
         {

         p2b.set_y(p2.get_y()+2*(p2.get_y()-p1.get_y()));
         }
      set_origine(pt);
      set_point2(p2b);
      pt.deplacementX(d1);
      set_point3(pt);
      p2b.deplacementY(-d2);
      set_extremite(p2b);
      diagonale1 = d1;
      diagonale2 = d2;
     }
     type = "losange";
}

void losange::affiche() const{
    quadrilatere::affiche();
    cout << "et je possede deux diagonales : la premiËre vaut "<< diagonale1 << ", et la seconde vaut " << diagonale2 << endl;
}

double losange::aire() const
{
    return (diagonale1*diagonale2) / 2;
}

double losange::get_diag1() const{
	return diagonale1;
}

double losange::get_diag2() const{
	return diagonale2;
}

void losange::set_diag1(const double &d){
	diagonale1 = d;
}

void losange::set_diag2(const double &d){
	diagonale2 = d;
}

