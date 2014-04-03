#include "graphique.h"
#include <QGraphicsItem>
#include "quadrilatere.h"
#include "rectangle.h"
#include "losange.h"
#include "cercle.h"
#include "triangle.h"
#include "carre.h"



graphique::graphique(QWidget *parent) :
    QGraphicsView(parent)
{
    scene =  new QGraphicsScene();
    this->setSceneRect(-100,-100,500,500);
    this->setScene(scene);
    this->setDragMode(RubberBandDrag);
    dessin = new dessinTechnique();
    multiseg = false;
    seg = false;
    rect = false;
    premier = true;
    deux = false;
    trois = false;
    triangl = false;
    losang = false;
    carr = false;
    this->scale(1,-1);
    dessiner_axes();


}

void graphique::dessiner_axes()
{
    //dessin des axes:
    QPen Axes(Qt::black,1.5);                              //stylo des axes

    QLineF  AxeY(QPointF(0,-200),QPointF(0,500));       //axe des ordonnés et la fleche
    QLineF fle1(QPointF(15,490),QPointF(0,500));
    QLineF fle2(QPointF(0,500),QPointF(-15,490));

    QLineF  AxeX(QPointF(-200,0),QPointF(500,0));       //axe des abscisses et la fleche
    QLineF fle3(QPointF(490,15),QPointF(500,0));
    QLineF fle4(QPointF(500,0),QPointF(490,-15));


    scene->addLine(AxeY,Axes);                           //dessin des axes et leurs fleches
    scene->addLine(fle1,Axes);
    scene->addLine(fle2,Axes);
    scene->addLine(AxeX,Axes);
    scene->addLine(fle3,Axes);
    scene->addLine(fle4,Axes);

    //on dessine les lignes du repère:
    int i = -200;
    QPen s(Qt::DashDotLine);
    s.setWidthF(0.2);
    while (i < 500) {
        QLineF l(QPointF(i,500),
                 QPointF(i,-200));

        QLineF l2(QPointF(-200,i),
                 QPointF(500,i));
        scene->addLine(l,s);
        scene->addLine(l2,s);
        QString s(QString::number(i));
        QString inv;
        // la matrice de transformation (car les images sont inversées)
        QTransform transf(-1,0,0,
                          0,1,0,
                          0,0,1);
        QGraphicsItem* i1 = scene->addText(s);
        QGraphicsItem* i2 = scene->addText(s);
        i1->setTransform(transf);
        i1->setRotation(180);
        i1->moveBy(i,0);
        i2->setTransform(transf);
        i2->setRotation(180);
        i2->moveBy(0,i);
        i += 100;
    }

}

void graphique::reinitialiser()
{
    this->listeitem.clear();
    this->dessin->vider();
    this->scene->clear();
    multiseg = false;
    seg = false;
    rect = false;
    premier = true;
    deux = false;
    trois = false;
    triangl = false;
    this->dessiner_axes();
    update();
}

void graphique::ajoutcercle(cercle* i)
{
    dessin->ajouter(i);
    Item* item= new Item(i,couleur,epaisseur );
    listeitem.push_back(item);
    scene->addItem(listeitem.at(listeitem.size()-1));
}

double graphique::perimetre() const
{
    return dessin->perimetre();
}

double graphique::aire() const
{
    double   somme = 0;
    for(int unsigned i = 0 ; i < listeitem.size() ; i ++){
        Item* item = (Item*) listeitem.at(i);
        somme += item->objet->aire();
    }
    return somme;
}

void graphique::mousePressEvent(QMouseEvent *event)
{

    if(multiseg  || seg){

        if(event->button() == Qt::LeftButton){
            // si on a cliqué sur le bouton gauche

            if(premier){
                //si c'est le premier click
                point1 = this->mapToScene(event->pos());
                premier = false;
            }
            else{
                // si c'est plus que le premier click

                if(deux){
                    // si on a plus de deux clicks

                    point1 = point2;
                    point2 = QPointF(this->mapToScene(event->pos()));
                    segment segtemp(point2D(point1.x(),point1.y()),point2D(point2.x(),point2.y()));

                            if (!trois){
                            multisegment* multi = new multisegment(*segme,segtemp);
                            Item* item = new Item(multi,couleur,epaisseur);

                            dessin->ajouter(multi);
                            scene->addItem(item);
                            scene->removeItem(listeitem.at(listeitem.size()-1));
                            listeitem.pop_back();
                            listeitem.push_back(item);
                            segmentstempo.push_back(*segme);
                            segmentstempo.push_back(segtemp);
                            trois = true;
                            }
                            else{
                                //si plus de 3 clicks
                                multisegment* multi = (multisegment*) dessin->get_liste_objets().at(dessin->nb_element()-1);
                                multi->ajout_seg(segtemp);
                                scene->removeItem(listeitem.at(listeitem.size()-1));
                                listeitem.pop_back();
                                Item* item = new Item(multi,couleur,epaisseur);
                                listeitem.push_back(item);
                                scene->addItem(item);
                                update();
                            }

                }
                else{
                        //si on veut juste faire un segment

                        point2 = this->mapToScene(event->pos());
                        segme = new segment( point2D(point1.x(),point1.y())
                                                  ,point2D(point2.x(),point2.y()));
                        Item* item = new Item(segme,couleur,epaisseur);
                        scene->addItem(item);
                        listeitem.push_back(item);
                        if(seg){
                            dessin->ajouter(segme);
                            premier = true;
                        }
                        if(multiseg){
                                // si on veut faire un multisegment
                                //on indique que le deuxieme click a été effectué
                                deux = true;
                            }

                }
            }

        }
    }
        if(rect){
            QPointF pos = this->mapToScene(event->pos());
            point2D actuelle(pos.x(),pos.y());
            rectangle* q = new rectangle(actuelle,100,50 );

            dessin->ajouter(q);
            Item* item= new Item(q,couleur,epaisseur);
            listeitem.push_back(item);
            scene->addItem(listeitem.at(listeitem.size()-1));
        }
        if(losang){
            QPointF p =  this->mapToScene(event->pos());
            point2D pos(p.x(),p.y());
            losange* l = new losange(pos, point2D(p.x() + 50, p.y() +100),100,200);

            dessin->ajouter(l);
            Item* item= new Item(l,couleur,epaisseur);
            listeitem.push_back(item);
            scene->addItem(listeitem.at(listeitem.size()-1));
        }
        if(triangl){
            QPointF p =  this->mapToScene(event->pos());
            point2D pos(p.x(),p.y());
            triangle * t = new triangle(pos,point2D(pos.get_x()+30,pos.get_y()+50),point2D(pos.get_x()+60,pos.get_y()));

            dessin->ajouter(t);
            Item* item = new Item(t,couleur,epaisseur);
            listeitem.push_back(item);
            scene->addItem(listeitem.at(listeitem.size()-1));
        }
        if(carr){
            QPointF p =  this->mapToScene(event->pos());
            point2D pos(p.x(),p.y());
            carre* c = new carre(pos,50);

            dessin->ajouter(c);
            Item* item = new Item(c,couleur,epaisseur );
            listeitem.push_back(item);
            scene->addItem(listeitem.at(listeitem.size()-1));
        }

   QGraphicsView::mousePressEvent(event);

}


void graphique::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void graphique::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

}

