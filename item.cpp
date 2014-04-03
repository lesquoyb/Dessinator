#include "item.h"
#include "quadrilatere.h"
#include "multisegment.h"
#include "cercle.h"
#include "rectangle.h"
#include "triangle.h"

#include <Qt>

Item::Item(ObjetGeom* o)
    : QGraphicsItem()   {
   this->setFlag(ItemIsFocusable);
    this->setFlag(ItemIsMovable);
    this->setFlag(ItemIsSelectable);
    objet = o;
    creation = true;
    couleur = Qt::black;
    QGraphicsItem::prepareGeometryChange();

}
Item::Item(ObjetGeom* o, QColor c ,double e)
    : QGraphicsItem()   {
   this->setFlag(ItemIsFocusable);
    this->setFlag(ItemIsMovable);
    this->setFlag(ItemIsSelectable);
    objet = o;
    creation = true;
    couleur = c;
    epaisseur = e;
    QGraphicsItem::prepareGeometryChange();

}

QRectF Item::boundingRect() const{

    if(!objet->nom.compare("triangle")){
            triangle* t = (triangle*) objet;
            QPolygonF p;
            p.append(t->get_origine());
            p.append(t->get_point2());
            p.append(t->get_extremite());
            return p.boundingRect();
        }
    else if (!objet->nom.compare("cercle")){
        cercle* o = (cercle*) objet;
        QGraphicsEllipseItem el(QRectF((o->get_centre() + QPointF( - o->get_rayon(),o->get_rayon())),  //haut à gauche
                         QPointF(o->get_centre() + QPointF(o->get_rayon(), - o->get_rayon())) ));
        return el.boundingRect();
    }
    else if(!objet->nom.compare("quadrilatere")){

                quadrilatere* o = (quadrilatere*) objet;
                QPolygonF p;
                p.append(o->get_origine());
                p.append(o->get_point2());
                p.append(o->get_point3());
                p.append(o->get_extremite());
                return p.boundingRect();

        }
    else if (! objet->nom.compare("segment")){
        segment* o = (segment*) objet;
        QLineF l(o->get_origine(),o->get_extremite());
        QGraphicsLineItem li(l);
        return li.boundingRect() ;
    }
    else if (!objet->nom.compare("multisegment")){
        multisegment* m = (multisegment*) objet;
        QPolygonF p;
        segment s = m->get_liste_seg().at(0);
        p.append(s.get_origine());
        for (int unsigned i = 0; i < m->get_liste_seg().size() ; i ++){
            segment s1 = m->get_liste_seg().at(i);
            p.append(s1.get_extremite());
        }
        return p.boundingRect();
    }
}



void Item::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pinceau(couleur,epaisseur);
    painter->setPen(pinceau);

     if(!objet->nom.compare("cercle")){
         QGraphicsItem::prepareGeometryChange();

         cercle* o = (cercle*) objet;
         QRectF rec((o->get_centre() + QPointF( - o->get_rayon(),o->get_rayon())),  //haut à gauche
                   QPointF(o->get_centre() + QPointF(o->get_rayon(), - o->get_rayon()))
                   );
         painter->drawEllipse(rec);
    }
    else if(!objet->nom.compare("multisegment")){
         QGraphicsItem::prepareGeometryChange();

        multisegment* o  = (multisegment*) objet;
        vector<segment> liste = o->get_liste_seg();
        for (int unsigned i = 0 ; i < liste.size() ; i ++ ){
            segment s1 = liste.at(i);
            QLine l(s1.get_origine(),s1.get_extremite());
            painter->drawLine(l);
        }
    }
     else if(!objet->nom.compare("triangle")){
         QGraphicsItem::prepareGeometryChange();

         triangle* tri = (triangle*) objet;
         QPolygonF p;
         p.append(tri->get_origine());
         p.append(tri->get_point2());
         p.append(tri->get_extremite());
         painter->drawPolygon(p);
     }
    else if (!objet->nom.compare("quadrilatere")){
         QGraphicsItem::prepareGeometryChange();
         quadrilatere* quad = (quadrilatere*) objet;
         if(!quad->get_type().compare("losange")){
             QPolygonF p;
             p.append(quad->get_origine());
             p.append(quad->get_point2());
             p.append(quad->get_point3());
             p.append(quad->get_extremite());
             painter->drawPolygon(p);
         }
         else{
             rectangle* rec = (rectangle*) objet;
             QRectF r(rec->get_origine(),rec->get_point3());
             painter->drawRect(r);
         }

    }
     else if(!objet->nom.compare("segment")){
         QGraphicsItem::prepareGeometryChange();
         segment* s = (segment*) objet;
         QLineF l(s->get_origine(),s->get_extremite());
         painter->drawLine(l);
     }




     if(this->isSelected() ){
         QGraphicsItem::prepareGeometryChange();
         QPen p(Qt::DashLine);
         painter->setPen(p);
         painter->drawRect(boundingRect());
     }
}

void Item::ajouter_ligne(const segment &s)
{
    multisegment* multi = (multisegment*) objet;
    multi->ajout_seg(s);
    QGraphicsItem::prepareGeometryChange();
    update();
}

QPointF Item::vrai_pos() const
{
    return mapFromItem(this,pos());
}



void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPainter p;
    QGraphicsItem::prepareGeometryChange();
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Item::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::prepareGeometryChange();
    QGraphicsItem::mouseReleaseEvent(event);
    update();

}

void Item::focusInEvent(QFocusEvent *event)
{
    QGraphicsItem::prepareGeometryChange();
 QGraphicsItem::focusInEvent(event);
 update();
}

void Item::focusOutEvent(QFocusEvent *event)
{
    QGraphicsItem::prepareGeometryChange();
    QGraphicsItem::focusOutEvent(event);
    update();
}

