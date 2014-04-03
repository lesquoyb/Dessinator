#include "quadrangle.h"
#include "segment.h"


quadrangle::quadrangle(const point2D &p1, const point2D &p2, const point2D &p3, const point2D &p4, const cercle &cer)
    : quadrilatere(p1,p2,p3,p4)
   {
	c = cer;
   //test distance centre point = rayon cercle
   segment s1(p1,c.get_centre());
   segment s2(p2,c.get_centre());
   segment s3(p3,c.get_centre());
   segment s4(p4,c.get_centre());
   if ( (s1.get_longueur()== c.get_rayon())  &&  (s2.get_longueur() == c.get_rayon())
        &&  (s3.get_longueur() == c.get_rayon()) &&  (s4.get_longueur() == c.get_rayon()) )
   {
     set_origine(p1);
     set_point2(p2);
     set_point3(p3);
     set_extremite(p4);
   }
   else
   {
       point2D ori(c.get_centre());
       ori.deplacementX(-c.get_rayon());
     set_origine(ori);
     ori = c.get_centre();
     ori.deplacementY(c.get_rayon());
     set_point2(ori);
     ori =c.get_centre();
     ori.deplacementX(c.get_rayon());
     set_point3(ori);
     ori = c.get_centre();
     ori.deplacementY(-c.get_rayon());
     set_extremite(ori);
     cout << "ceci n'est pas un quadrangle en voici un par defaut" << endl ;
   }
     
     
      
	type = "quadrangle";
}


cercle quadrangle::get_cercle() const
{
	return c;
}

void quadrangle::set_cercle(const cercle &cer){
	c = cer;
}

void quadrangle::affiche()const{
    quadrilatere::affiche();
}

double quadrangle::aire() const
{
    cout << "le calcule de l'aire d'un quadrilatère quelconque étant très complexe, cette fonction n'est pas disponible avec le quadrangle, elle retournera donc 0.";
    return 0;
}
