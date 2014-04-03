#ifndef OBJETGEOM_H
#define OBJETGEOM_H
#include "point2d.h"
#include <QString>
#include <QtXML/qdom.h>
class ObjetGeom
{
public:
    string nom;
	double get_perimetre() const;
	void set_perimetre(const double &);
	point2D get_origine() const;
	point2D get_extremite() const;
	void set_origine(const point2D&);
	void set_extremite(const point2D&);
	void deplacement(const point2D &);
	ObjetGeom(const point2D &, const point2D&);
	ObjetGeom();

	//ces operations ne seront d�finis que dans les enfants de ObjetGeom:
	virtual void  affiche()const = 0;
    virtual double  aire() const = 0;

protected:

	//ces attributs sont commun aux fils de ObjetGeom :
	point2D extremite;
	point2D origine;
    double perimetre;


	//ces operations sont communes aux fils de ObjetGeom : 
    void actualise_perimetre();





};

#endif // OBJETGEOM_H
