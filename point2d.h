#ifndef POINT2D_H
#define POINT2D_H
#include <iostream>
#include <QPointF>
using namespace std;
//#include <QtWidgets>

class point2D
{
private:

	double x;
	double y;

public:

	point2D();
	void set_x(const double &);
	void set_y(const double &);
	double get_x()const;
	double get_y() const;
	void deplacement(const point2D &);
    void deplacementX(const double &);
    void deplacementY(const double &);
	point2D(const double &, const double &);
    void ecrire(ostream &os) const;

    //surcharge de la conversion implicite vers QPointF et QPoint
    operator QPointF()const;
    operator QPoint()const ;


};

// on surcharge la lecture de point2D 
ostream &operator <<(ostream &os, const point2D &p);


#endif
