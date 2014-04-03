#ifndef GRAPHIQUE_H
#define GRAPHIQUE_H
#include <QGraphicsView>
#include <QMouseEvent>
#include <iostream>
#include "item.h"
#include "segment.h"
#include "multisegment.h"
#include "segment.h"
#include "dessinTechnique.h"
#include "cercle.h"
#include <QList>



class graphique : public QGraphicsView
{
    Q_OBJECT
public:
   explicit graphique(QWidget *parent = 0);
    void dessiner_axes();
    void reinitialiser();
    QPainterPath * p;
    vector<QGraphicsItem*> listeitem;
    vector<segment> segmentstempo;
    Item* selectionne;
    dessinTechnique* dessin;
    QPointF point1;
    QPointF point2;
    void ajoutcercle(cercle*);
    bool multiseg;
    bool premier;
    bool rect;
    bool deux;
    bool trois;
    bool seg;
    bool triangl;
    bool losang;
    bool carr;
    QColor couleur;
    double epaisseur;
    double perimetre()const;
    double aire()const;
    segment* segme;
    QGraphicsScene* scene;
signals:

public slots:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
};

#endif // GRAPHIQUE_H
