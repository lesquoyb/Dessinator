#ifndef ITEM_H
#define ITEM_H
#include <Qt>
#include <QtGui>
#include <QtWidgets>
#include <QGraphicsItem>
#include "objetgeom.h"
#include "segment.h"



class Item : public QGraphicsItem
{
public:
    ObjetGeom* objet;
    bool creation;
    double epaisseur;
    Item(ObjetGeom *);
    Item(ObjetGeom *, QColor, double);
    QRectF boundingRect()const;
    QColor couleur;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void ajouter_ligne(const segment &);
    QPointF vrai_pos()const;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void focusInEvent(QFocusEvent *event);
    void focusOutEvent(QFocusEvent *event);
};


#endif // ITEM_H
