#pragma once
#include "point2d.h"
#include <iostream>
using namespace std;

point2D::point2D(){
	this->x = 0.0;
	this->y = 0.0;
}

point2D::point2D(const double &a, const double &b){
	x = a;
	y = b;
}

void point2D::set_x(const double &a){
	x = a;
}

void point2D::set_y(const double &b){
	y = b;
}

double point2D::get_x() const{
	return x;
}

double point2D::get_y()const{
	return y;
}

void point2D::deplacement(const point2D &p){
		x += p.get_x();
		y += p.get_y();
}

void point2D::deplacementX(const double &x1){
      x += x1;
}

void point2D::deplacementY(const double &y1){
      y += y1;
}



ostream &operator <<(ostream &os, const point2D &p){
	p.ecrire(os);
	return os;
}


 point2D::operator QPointF() const{
    return QPointF(x,y);
    
}
void point2D::ecrire(ostream &os)const{
    os << " un point2D (" << x << " , " << y <<" ) "<< endl;
}



point2D::operator QPoint() const
{
    return QPoint(x,y);
}





