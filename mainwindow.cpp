#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QtCore>
#include <qxmlstream.h>
#include "carre.h"

#include <QtPrintSupport/QAbstractPrintDialog>
#include <QtPrintSupport/QPrintEngine>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtXml/QDomDocument>
#include <QtXml/QtXml>
#include <QDialog>

#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    couleur = Qt::black;
    ui->select_couleur->setStyleSheet(QString::fromUtf8("background-color: rgb(")
                                +QString::number(couleur.red())
                                +QString::fromUtf8(", ")
                                +QString::number(couleur.green())
                                +QString::fromUtf8(", ")
                                +QString::number(couleur.blue())
                                +QString::fromUtf8(");"));
    g = ui->graphicsView;
    epaisseur = 1;
    g->epaisseur = epaisseur;
    g->couleur = couleur;
    ui->epaisseur->setValue(1);
    liste_actions << ui->actionCarre << ui->actionCercle <<ui->actionLosange << ui->actionMultisegment << ui->actionQuadrilatere
                     << ui->actionSegment << ui->actionTriangle ;
}

void MainWindow::paintEvent(QPaintEvent *)
{

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNouveau_triggered()
{
   g->reinitialiser();
    update();
}

void MainWindow::Ouvrir(){

    if (nomfichier != ""){
        QFile fich (nomfichier);
        QDomDocument document;
        if (!fich.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::warning(this,"erreur","impossible d'ouvrir le fichier");
            return;
        }
        else{
            // on lit le fichier
            if(!document.setContent(&fich)){
                QMessageBox::warning(this,"erreur","impossible de lire le fichier");
                return ;
            }

            on_actionNouveau_triggered();
            // on récupère la racine
           QDomElement root = document.firstChildElement();
           // on fait une liste de tout les objets du document
           QDomNodeList liste = root.elementsByTagName("objet");
           for(int i = 0; i < liste.size() ; i ++){
               QDomNode noeud = liste.at(i);
               //on converti le noeud en element
               QDomElement elem = noeud.toElement();

               // puis on créé les objet de la scène en fonction des attributs de elem
               QDomNode ori = elem.firstChild(); // le premier enfant est toujours origine
               QDomElement elemorigine = ori.toElement();
               point2D origine(elemorigine.attribute("x").toDouble(),elemorigine.attribute("y").toDouble());
               QColor coul(elem.attribute("r").toInt(),elem.attribute("g").toInt(),elem.attribute("b").toInt());
               double epais = elem.attribute("epaisseur").toDouble();

               if(elem.attribute("nom") == "quadrilatere"){
                    //on test le type de quadrilatere

                   if(elem.attribute("type")== "rectangle"){

                       rectangle* rec = new rectangle(origine,elem.attribute("longueur").toDouble(),elem.attribute("largeur").toDouble());
                        g->dessin->ajouter(rec);
                        Item* item = new Item(rec,coul,epais);
                        g->scene->addItem(item);
                        g->listeitem.push_back(item);

                   }
                   else if(elem.attribute("type")== "carre"){

                       carre* car = new carre(origine,elem.attribute("cote").toDouble());

                       g->dessin->ajouter(car);
                       Item* item = new Item(car,coul,epais);
                       g->scene->addItem(item);
                       g->listeitem.push_back(item);

                   }
                   else if(elem.attribute("type")== "losange"){
                       QDomNodeList liste = elem.childNodes();
                       QDomElement p2 = liste.at(1).toElement();
                       point2D point2(p2.attribute("x").toDouble(),p2.attribute("y").toDouble());
                        losange* l = new losange(origine,point2,elem.attribute("diagonal1").toDouble(),elem.attribute("diagonal2").toDouble());
                        g->dessin->ajouter(l);
                        Item* item = new Item(l,coul,epais);
                        g->scene->addItem(item);
                        g->listeitem.push_back(item);
                   }
               }
               else if(elem.attribute("nom") == "segment"){
                   QDomNodeList l =elem.childNodes();
                    // extremité est l'element à la position 1 du segment
                   QDomElement extrem = l.at(1).toElement();
                   point2D extremite(extrem.attribute("x").toDouble(),
                                     extrem.attribute("y").toDouble());
                   segment* s = new segment(origine,extremite);
                   g->dessin->ajouter(s);
                   Item* item = new Item(s,coul,epais);
                   g->scene->addItem(item);
                   g->listeitem.push_back(item);
               }
               else if(elem.attribute("nom") == "triangle"){
                   QDomNodeList l =elem.childNodes();
                    // extremité est l'element à la position 1 du segment
                   QDomElement p2 = l.at(1).toElement();
                   QDomElement extrem = l.at(2).toElement();

                   point2D point2(p2.attribute("x").toDouble(),
                                  p2.attribute("y").toDouble());
                   point2D extremite(extrem.attribute("x").toDouble(),
                                     extrem.attribute("y").toDouble());
                   triangle* s = new triangle(origine,point2,extremite);
                   g->dessin->ajouter(s);
                   Item* item = new Item(s,coul,epais);
                   g->scene->addItem(item);
                   g->listeitem.push_back(item);
               }
               else if(elem.attribute("nom") == "cercle"){
                   QDomNodeList l =elem.childNodes();
                    // extremité est l'element à la position 1 du segment
                   QDomElement p2 = l.at(1).toElement();
                   point2D centre(p2.attribute("x").toDouble(),
                                  p2.attribute("y").toDouble());
                   cercle* s = new cercle(centre,elem.attribute("rayon").toDouble());
                   g->dessin->ajouter(s);
                   Item* item = new Item(s,coul,epais);
                   g->scene->addItem(item);
                   g->listeitem.push_back(item);
               }
               else if(elem.attribute("nom") == "multisegment"){
                   QDomNodeList l =elem.childNodes();
                    // extremité est l'element à la position 1 du segment
                   QDomElement p1 = l.at(1).toElement();
                   QDomElement p2 = l.at(2).toElement();
                   QDomElement p3 = l.at(3).toElement();

                   segment s1(point2D(p1.attribute("x").toDouble(),
                                      p1.attribute("y").toDouble()),
                              point2D(p2.attribute("x").toDouble(),
                                      p2.attribute("y").toDouble()));
                   segment s2 (point2D(p2.attribute("x").toDouble(),
                                       p2.attribute("y").toDouble()),
                               point2D(p3.attribute("x").toDouble(),
                                       p3.attribute("y").toDouble()));

                   multisegment* s = new multisegment(s1,s2);
                   for(int k = 4 ; k < l.size(); k ++ ){
                       QDomElement p = l.at(k).toElement();
                       s2.set_origine(s2.get_extremite());
                       s2.set_extremite(point2D(p.attribute("x").toDouble(),p.attribute("y").toDouble()));
                       s->ajout_seg(s2);
                   }
                   g->dessin->ajouter(s);
                   Item* item = new Item(s,coul,epais);
                   g->scene->addItem(item);
                   g->listeitem.push_back(item);
               }

           }
        }
    }
}

void MainWindow::on_actionOuvrir_triggered()
{

    nomfichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Fichiers dessinator (*.dessinator)");
    if(nomfichier != "" ){
        Ouvrir();
    }
}

void MainWindow::on_actionSauvegarder_triggered()
{
    nomfichier = QFileDialog::getSaveFileName(this, "Ouvrir un fichier", QString(), "Fichiers dessinator (*.dessinator)");
    if(nomfichier != ""){
        sauver(nomfichier);
      }

}
void MainWindow::sauver(const QString &fichier){
    QFile fich(fichier);
    if(!fich.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::warning(this,"erreur","Impossible d'ouvrir le fichier");
        return;
    }
    else{
        //creation du document xml
        QDomDocument document;
        QDomElement dessin = document.createElement("dessin");

        vector<ObjetGeom*>liste = g->dessin->get_liste_objets();
        for(int unsigned i = 0 ; i < liste.size() ; i ++){
            Item* item =(Item*) g->listeitem.at(i);
            ObjetGeom* o = item->objet;
            //on doit mettre à jour les positions des points

            QDomElement objet = document.createElement("objet");
            objet.setAttribute("nom", o->nom.c_str());
            objet.setAttribute("epaisseur",QString::number(item->epaisseur));
            objet.setAttribute("r",QString::number(item->couleur.red()));
            objet.setAttribute("g",QString::number(item->couleur.green()) );
            objet.setAttribute("b",QString::number(item->couleur.blue()));

            //l'origine est commun à tout les objets
            QDomElement origine= document.createElement("origine");
            QPointF t = item->mapToScene(o->get_origine());
            origine.setAttribute("x", t.x());
            origine.setAttribute("y", t.y());
            objet.appendChild(origine);

            if(!o->nom.compare("quadrilatere")){

                quadrilatere* quad =(quadrilatere*) o;
                objet.setAttribute("type", quad->get_type().c_str());

                if(!quad->get_type().compare("losange")){
                    losange* l = (losange*) o;
                    QPointF t = item->mapToScene(o->get_origine());
                    point2D nouv(t.x(),t.y());
                    QPointF p2 = item->mapToScene(l->get_point2());

                    QDomElement point2 = document.createElement("point2");
                    point2.setAttribute("x", p2.x());
                    point2.setAttribute("y", p2.y());

                    objet.appendChild(point2);
                    objet.setAttribute("diagonal1",l->get_diag1());
                    objet.setAttribute("diagonal2",l->get_diag2());

                }
                else if(!quad->get_type().compare("carre")){

                    carre* c = (carre*) o;
                    objet.setAttribute("cote",c->get_cote());


                }
                else if(!quad->get_type().compare("rectangle")){

                    rectangle* r = (rectangle*) o;
                    QPointF t = item->mapToScene(o->get_origine());
                    point2D nouv(t.x(),t.y());
                    rectangle* rec = new rectangle(nouv,r->get_longueur(),r->get_largeur());

                    objet.setAttribute("largeur",rec->get_largeur());
                    objet.setAttribute("longueur", rec->get_longueur());

                }



            }else if(!o->nom.compare("triangle")){

                triangle* tri = (triangle*) o;
                QPointF p2 = item->mapToScene(tri->get_point2());
                QPointF extrem = item->mapToScene(o->get_extremite());

                QDomElement point2 = document.createElement("point2");
                point2.setAttribute("x", p2.x());
                point2.setAttribute("y", p2.y());

                QDomElement extremite = document.createElement("extremite");
                extremite.setAttribute("x",extrem.x());
                extremite.setAttribute("y", extrem.y());

                objet.appendChild(point2);
                objet.appendChild(extremite);

            }
            else if (!o->nom.compare("segment")){

                QDomElement extremite = document.createElement("extremite");
                QPointF t = item->mapToScene(o->get_extremite());
                extremite.setAttribute("x",t.x());
                extremite.setAttribute("y", t.y());
                objet.appendChild(extremite);

            }
            else if (!o->nom.compare("multisegment")){

                multisegment* multi = (multisegment *) o;
                vector<segment> liste = multi->get_liste_seg();
                QDomElement vraiorigine = document.createElement("vraiorigine");
                segment s1 = liste.at(0);
                QPointF t1 = item->mapToScene(s1.get_origine());
                vraiorigine.setAttribute("x",t1.x());
                vraiorigine.setAttribute("y",t1.y());
                objet.appendChild(vraiorigine);
                for(int unsigned i = 0; i < liste.size(); i ++){
                    segment s = liste.at(i);
                    QPointF t = item->mapToScene(s.get_extremite());
                    QDomElement point = document.createElement("point");
                    point.setAttribute("x", t.x());
                    point.setAttribute("y", t.y());
                    objet.appendChild(point);
                }


            }
            else if(!o->nom.compare("cercle")){

                cercle* c = (cercle* ) o;
                QPointF t = item->mapToScene(c->get_centre());
                QDomElement centre = document.createElement("centre");
                centre.setAttribute("x", t.x());
                centre.setAttribute("y",t.y());
                objet.setAttribute("rayon",c->get_rayon());
                objet.appendChild(centre);

            }

            //on organise le xml
            dessin.appendChild(objet);

        }
        // on remplis le fichier avec le document xml
        document.appendChild(dessin);
        QTextStream out(&fich);
        out << document.toString() <<endl;
        out.flush();
    }
}

void MainWindow::on_actionQuadrilatere_triggered()
{
    if (g->rect == false){

        QAction* action;
        foreach(action,liste_actions){
            if(action->objectName().compare("actionQuadrilatere")){
                action->setChecked(false);
            }
        }


        g->rect = true;
        g->multiseg = false;
        g->trois = false;
        g->premier = true;
        g->deux = false;
        g->carr = false;
        g->losang = false;
        g->triangl = false;
        g->seg = false;
    }
    else{
        g->rect = false;
    }
    update();
}

void MainWindow::on_actionCercle_triggered()
{

    point2D centre(30,10);
    double rayon = 30;
    g->ajoutcercle(new cercle(centre,rayon));


    QAction* action;
    foreach(action,liste_actions){
            action->setChecked(false);
    }


    g->rect = false;
    g->multiseg = false;
    g->trois = false;
    g->premier = true;
    g->deux = false;
    g->carr = false;
    g->losang = false;
    g->triangl = false;
    g->seg = false;
     update();
}

void MainWindow::on_actionTriangle_triggered()
{
    if (g->triangl){
        g->triangl = false;
    }
    else{


        QAction* action;
        foreach(action,liste_actions){
            if(action->objectName().compare("actionTriangle")){
                action->setChecked(false);
            }
        }




        g->triangl = true;
        g->multiseg = false;
        g->trois = false;
        g->premier = true;
        g->deux = false;
        g->carr = false;
        g->losang = false;
        g->rect = false;
        g->seg = false;
    }
}

void MainWindow::on_actionSegment_triggered()
{
    if(g->seg == true){
        g->seg = false;
        g->trois = false;
        g->premier = true;
        g->deux = false;
    }
    else{
        g->seg = true;

        QAction* action;
        foreach(action,liste_actions){
            if(action->objectName().compare("actionSegment")){
                action->setChecked(false);
            }
        }


        g->trois = false;
        g->premier = true;
        g->deux = false;
        g->multiseg = false;
        g->trois = false;
        g->premier = true;
        g->deux = false;
        g->carr = false;
        g->losang = false;
        g->triangl = false;
        g->rect = false;
    }
     update();
}

void MainWindow::on_actionMultisegment_triggered()
{
    if(g->multiseg == false){
        g->multiseg = true;
        g->trois = false;
        g->premier = true;
        g->deux = false;


        g->losang = true;
        QAction* action;
        foreach(action,liste_actions){
            if(action->objectName().compare("actionMultisegment")){
                action->setChecked(false);
            }
        }


        g->carr = false;
        g->losang = false;
        g->triangl = false;
        g->rect = false;
        g->seg = false;
    }
    else{
        g->multiseg = false;
        g->trois = false;
        g->premier = true;
        g->deux = false;


    }
}

void MainWindow::on_actionGomme_triggered()
{
    if(g->dessin->get_liste_objets().size() > 0 ){
    g->dessin->suppr_dernier();
    QGraphicsItem* temp = g->listeitem.at(g->listeitem.size()-1);
    g->listeitem.pop_back();
    g->scene->removeItem(temp);
    }
}

void MainWindow::on_pushButton_clicked()
{
    // on augment la largeur
    vector<ObjetGeom*> liste = g->dessin->get_liste_objets();
    vector<Item*> objetselect;

    for(int unsigned i = 0 ; i < liste.size() ; i ++){
        Item* temp =(Item*) g->listeitem.at(i);
        if (temp->isSelected()){

            if(!temp->objet->nom.compare("cercle")){

            cercle* temp2 = (cercle *) temp->objet;
            temp2->set_rayon(temp2->get_rayon() +10);
            cercle* nouveau = new cercle(temp2->get_centre(),temp2->get_rayon());
            Item* nouv = new Item(nouveau,couleur,epaisseur);
            nouv->moveBy(temp->pos().x(),temp->pos().y());

            g->scene->addItem(nouv);
            g->scene->removeItem(temp);
            liste.at(i) = nouveau;
            g->listeitem.at(i) = nouv;
            objetselect.push_back(nouv);
            }
            else if(!temp->objet->nom.compare("quadrilatere")){

                quadrilatere* quad = (quadrilatere*) temp->objet;

                if(!quad->get_type().compare("rectangle")){

                     rectangle* temp2 = (rectangle *) temp->objet;
                     rectangle* nouveau = new rectangle(point2D(temp2->get_origine().get_x()-5,temp2->get_origine().get_y()),
                                                        point2D(temp2->get_point2().get_x() +5,temp2->get_point2().get_y() ),
                                                        point2D(temp2->get_point3().get_x() +5,temp2->get_point3().get_y() ),
                                                        point2D(temp2->get_extremite().get_x()-5,temp2->get_extremite().get_y() ));
                     Item* nouv = new Item(nouveau,couleur,epaisseur);
                     nouv->moveBy(temp->pos().x(),temp->pos().y());
                     g->scene->addItem(nouv);
                     g->scene->removeItem(temp);
                     g->listeitem.at(i) = nouv;
                     objetselect.push_back(nouv);

                }
                else if(!quad->get_type().compare("carre")){

                    carre* temp2 = (carre*) temp->objet;
                    carre* nouveau = new carre(point2D(temp2->get_origine().get_x()-5,temp2->get_origine().get_y() -5),temp2->get_cote()+10);

                    Item* nouv = new Item(nouveau,couleur,epaisseur);
                    nouv->moveBy(temp->pos().x(),temp->pos().y());
                    g->scene->addItem(nouv);
                    g->scene->removeItem(temp);
                    g->listeitem.at(i) = nouv;
                    objetselect.push_back(nouv);
                }

                else if(!quad->get_type().compare("losange")){

                    losange* temp2 = (losange *) temp->objet;
                    losange* nouveau = new losange(point2D(temp2->get_origine().get_x()-5,temp2->get_origine().get_y()),
                                                   temp2->get_point2(),
                                                   temp2->get_diag1()+10,
                                                   temp2->get_diag2());
                    Item* nouv = new Item(nouveau,couleur,epaisseur);
                    nouv->moveBy(temp->pos().x(),temp->pos().y());
                    g->scene->addItem(nouv);
                    g->scene->removeItem(temp);
                    g->listeitem.at(i) = nouv;
                    objetselect.push_back(nouv);

                }


             }
            else if(!temp->objet->nom.compare("triangle")){
            triangle* temp2 = (triangle *) temp->objet;
            triangle* nouveau = new triangle(point2D(temp2->get_origine().get_x() -10, temp2->get_origine().get_y()),
                                             point2D(temp2->get_point2().get_x() ,temp2->get_point2().get_y()),
                                             point2D(temp2->get_extremite().get_x() +10,temp2->get_extremite().get_y()));
            Item* nouv = new Item(nouveau,couleur,epaisseur);
            nouv->moveBy(temp->pos().x(),temp->pos().y());

            g->scene->addItem(nouv);
            g->scene->removeItem(temp);
            g->listeitem.at(i) = nouv;
            objetselect.push_back(nouv);

            }
            else if(!temp->objet->nom.compare("segment")){

            segment* temp2 = (segment *) temp->objet;
            temp2->set_origine(point2D(temp2->get_origine().get_x() -5 ,
                                         temp2->get_origine().get_y() ));
            temp2->set_extremite(point2D(
                                        temp2->get_extremite().get_x() +5,
                                        temp2->get_extremite().get_y()));
            segment* nouveau = new segment(temp2->get_origine(),temp2->get_extremite());
            Item* nouv = new Item(nouveau,couleur,epaisseur);
            nouv->moveBy(temp->pos().x(),temp->pos().y());
            g->scene->addItem(nouv);
            g->scene->removeItem(temp);
            g->listeitem.at(i) = nouv;
            objetselect.push_back(nouv);

            }

        }
        for(int unsigned i = 0 ; i < objetselect.size(); i ++){
            Item* temp = objetselect.at(i);
            temp->setSelected(true);
        }
    }
}

void MainWindow::on_actionPerimetre_triggered()
{
    if(nomfichier == ""){
        QMessageBox::information(this,"sauver","vous devez sauver le fichier en cour pour acceder à cette fonctionnalité");
    }
    else{
        sauver(nomfichier);
        Ouvrir();
        double perimetre = g->perimetre();
        QString s = "Le perimetre cumulé de toutes les figures présentes dans la scene est: ";
        s += QString::number(perimetre);
        s += " pixels.\n";
        QMessageBox::information(this,"perimetre cumulé des figures",s);
    }
}

void MainWindow::on_actionAire_triggered()
{
    if(nomfichier == ""){
        QMessageBox::information(this,"sauver","vous devez sauver le fichier en cour pour acceder à cette fonctionnalité");
    }
    else{
        sauver(nomfichier);
        Ouvrir();
        double aire = g->aire();
        QString s = "Le cumulé de toutes les aires des figures présentes dans la scene est: ";
        s += QString::number(aire);
        s += " pixels.\n";
        QMessageBox::information(this,"aire cumulé des figures",s);
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    // on réduit la largeur
    vector<ObjetGeom*> liste = g->dessin->get_liste_objets();
    vector<Item*> objetselect;
    for(int unsigned i = 0 ; i < liste.size() ; i ++){
        Item* temp =(Item*) g->listeitem.at(i);
        if (temp->isSelected()){

            if(!temp->objet->nom.compare("cercle")){
            cercle* temp2 = (cercle *) temp->objet;
            temp2->set_rayon(temp2->get_rayon() -10);
            cercle* nouveau = new cercle(temp2->get_centre(),temp2->get_rayon());
            Item* nouv = new Item(nouveau);
            nouv->moveBy(temp->pos().x(),temp->pos().y());
            g->scene->addItem(nouv);
            g->scene->removeItem(temp);
            g->listeitem.at(i) = nouv;
            objetselect.push_back(nouv);
            }
            else if(!temp->objet->nom.compare("quadrilatere")){
                quadrilatere* quad = (quadrilatere*) temp->objet;
                if(!quad->get_type().compare("rectangle")){
                    rectangle* temp2 = (rectangle *) temp->objet;
                    rectangle* nouveau = new rectangle(point2D(temp2->get_origine().get_x()+5,temp2->get_origine().get_y()),
                                                       point2D(temp2->get_point2().get_x() -5,temp2->get_point2().get_y() ),
                                                       point2D(temp2->get_point3().get_x() -5,temp2->get_point3().get_y() ),
                                                       point2D(temp2->get_extremite().get_x()+5,temp2->get_extremite().get_y() ));
                    Item* nouv = new Item(nouveau,couleur,epaisseur);
                    nouv->moveBy(temp->pos().x(),temp->pos().y());
                    g->scene->addItem(nouv);
                    g->scene->removeItem(temp);
                    g->listeitem.at(i) = nouv;
                    objetselect.push_back(nouv);
                }
                else if(!quad->get_type().compare("carre")){

                    carre* temp2 = (carre*) temp->objet;
                    carre* nouveau = new carre(point2D(temp2->get_origine().get_x()+5,temp2->get_origine().get_y() +5),temp2->get_cote()-10);

                    Item* nouv = new Item(nouveau,couleur,epaisseur);
                    nouv->moveBy(temp->pos().x(),temp->pos().y());
                    g->scene->addItem(nouv);
                    g->scene->removeItem(temp);
                    g->listeitem.at(i) = nouv;
                    objetselect.push_back(nouv);
                }
                else if(!quad->get_type().compare("losange")){

                    losange* temp2 = (losange *) temp->objet;
                    losange* nouveau = new losange(point2D(temp2->get_origine().get_x()+5,temp2->get_origine().get_y()),
                                                   temp2->get_point2(),
                                                   temp2->get_diag1()-10,
                                                   temp2->get_diag2());
                    Item* nouv = new Item(nouveau,couleur,epaisseur);
                    nouv->moveBy(temp->pos().x(),temp->pos().y());
                    g->scene->addItem(nouv);
                    g->scene->removeItem(temp);
                    g->listeitem.at(i) = nouv;
                    objetselect.push_back(nouv);

                }

             }
            else if(!temp->objet->nom.compare("triangle")){
            triangle* temp2 = (triangle *) temp->objet;
            QPointF p(temp->vrai_pos());
            triangle* nouveau = new triangle(point2D(temp2->get_origine().get_x() + 5,temp2->get_origine().get_y()),
                                             point2D(temp2->get_point2().get_x(),temp2->get_point2().get_y()),
                                             point2D(temp2->get_extremite().get_x() -5,temp2->get_extremite().get_y()));
            Item* nouv = new Item(nouveau,couleur,epaisseur);
            nouv->moveBy(temp->pos().x(),temp->pos().y());
            g->scene->addItem(nouv);
            g->scene->removeItem(temp);
            g->listeitem.at(i) = nouv;
            objetselect.push_back(nouv);

            }
            else if(!temp->objet->nom.compare("segment")){
            segment* temp2 = (segment *) temp->objet;

            temp2->set_origine(point2D(temp2->get_origine().get_x() +5 ,
                                         temp2->get_origine().get_y() ));
            temp2->set_extremite(point2D(
                                        temp2->get_extremite().get_x() -5,
                                        temp2->get_extremite().get_y() ));
            segment* nouveau = new segment(temp2->get_origine(),temp2->get_extremite());
            Item* nouv = new Item(nouveau,couleur,epaisseur);
            nouv->moveBy(temp->pos().x(),temp->pos().y());
            g->scene->addItem(nouv);
            g->scene->removeItem(temp);
            g->listeitem.at(i) = nouv;
            objetselect.push_back(nouv);

            }
        }
        for(int unsigned i = 0 ; i < objetselect.size(); i ++){
            Item* temp = objetselect.at(i);
            temp->setSelected(true);
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    // on augmente la hauteur
    vector<ObjetGeom*> liste = g->dessin->get_liste_objets();
    vector<Item*> objetselect;
    for(int unsigned i = 0 ; i < liste.size() ; i ++){
        Item* temp =(Item*) g->listeitem.at(i);
        if (temp->isSelected()){

            if(!temp->objet->nom.compare("cercle")){
            cercle* temp2 = (cercle *) temp->objet;
            temp2->set_rayon(temp2->get_rayon() +10);
            cercle* nouveau = new cercle(temp2->get_centre(),temp2->get_rayon());
            Item* nouv = new Item(nouveau,couleur,epaisseur);
            nouv->moveBy(temp->pos().x(),temp->pos().y());
            g->scene->addItem(nouv);
            g->scene->removeItem(temp);
            g->listeitem.at(i) = nouv;
            objetselect.push_back(nouv);
            }

            else if(!temp->objet->nom.compare("quadrilatere")){

                quadrilatere* quad = (quadrilatere*) temp->objet;
                if(!quad->get_type().compare("rectangle")){
                     rectangle* temp2 = (rectangle *) temp->objet;
                     rectangle* nouveau = new rectangle(point2D(temp2->get_origine().get_x(),temp2->get_origine().get_y()-5),
                                                        point2D(temp2->get_point2().get_x() ,temp2->get_point2().get_y() -5),
                                                        point2D(temp2->get_point3().get_x() ,temp2->get_point3().get_y() +5),
                                                        point2D(temp2->get_extremite().get_x(),temp2->get_extremite().get_y() +5));
                     Item* nouv = new Item(nouveau,couleur,epaisseur);
                     nouv->moveBy(temp->pos().x(),temp->pos().y());
                     g->scene->addItem(nouv);
                     g->scene->removeItem(temp);
                     g->listeitem.at(i) = nouv;
                     objetselect.push_back(nouv);
                }
                else if(!quad->get_type().compare("carre")){

                    carre* temp2 = (carre*) temp->objet;
                    carre* nouveau = new carre(point2D(temp2->get_origine().get_x()-5,temp2->get_origine().get_y() -5),temp2->get_cote()+10);

                    Item* nouv = new Item(nouveau,couleur,epaisseur);
                    nouv->moveBy(temp->pos().x(),temp->pos().y());
                    g->scene->addItem(nouv);
                    g->scene->removeItem(temp);
                    g->listeitem.at(i) = nouv;
                    objetselect.push_back(nouv);
                }
                 else if(!quad->get_type().compare("losange")){

                     losange* temp2 = (losange *) temp->objet;
                     losange* nouveau = new losange(temp2->get_origine(),
                                                    point2D(temp2->get_point2().get_x(),temp2->get_point2().get_y()+5),
                                                    temp2->get_diag1(),
                                                    temp2->get_diag2()+10);
                     Item* nouv = new Item(nouveau,couleur,epaisseur);
                     nouv->moveBy(temp->pos().x(),temp->pos().y());
                     g->scene->addItem(nouv);
                     g->scene->removeItem(temp);
                     g->listeitem.at(i) = nouv;
                     objetselect.push_back(nouv);

                 }
             }
            else if(!temp->objet->nom.compare("triangle")){
            triangle* temp2 = (triangle *) temp->objet;
            triangle* nouveau = new triangle(point2D(temp2->get_origine().get_x(),temp2->get_origine().get_y() -5),
                                             point2D(temp2->get_point2().get_x(), temp2->get_point2().get_y() +5 ),
                                             point2D(temp2->get_extremite().get_x(),temp2->get_extremite().get_y() -5));
            Item* nouv = new Item(nouveau,couleur,epaisseur);
            nouv->moveBy(temp->pos().x(),temp->pos().y());
            g->scene->addItem(nouv);
            g->scene->removeItem(temp);
            g->listeitem.at(i) = nouv;
            objetselect.push_back(nouv);

            }
            else if(!temp->objet->nom.compare("segment")){
            segment* temp2 = (segment *) temp->objet;

            temp2->set_origine(point2D(temp2->get_origine().get_x() ,
                                         temp2->get_origine().get_y() - 5));
            temp2->set_extremite(point2D(temp2->get_extremite().get_x() ,
                                        temp2->get_extremite().get_y() + 5));
            segment* nouveau = new segment(temp2->get_origine(),temp2->get_extremite());
            Item* nouv = new Item(nouveau,couleur,epaisseur);
            nouv->moveBy(temp->pos().x(),temp->pos().y());
            g->scene->addItem(nouv);
            g->scene->removeItem(temp);
            g->listeitem.at(i) = nouv;
            objetselect.push_back(nouv);

            }

        }
        for(int unsigned i = 0 ; i < objetselect.size(); i ++){
            Item* temp = objetselect.at(i);
            temp->setSelected(true);
        }
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    // on réduit la hauteur
    vector<ObjetGeom*> liste = g->dessin->get_liste_objets();
    vector<Item*> objetselect;
    for(int unsigned i = 0 ; i < liste.size() ; i ++){
        Item* temp =(Item*) g->listeitem.at(i);
        if (temp->isSelected()){

            if(!temp->objet->nom.compare("cercle")){
            cercle* temp2 = (cercle *) temp->objet;
            temp2->set_rayon(temp2->get_rayon() -10);
            cercle* nouveau = new cercle(temp2->get_centre(),temp2->get_rayon());
            Item* nouv = new Item(nouveau,couleur,epaisseur);
            nouv->moveBy(temp->pos().x(),temp->pos().y());
            g->scene->addItem(nouv);
            g->scene->removeItem(temp);
            g->listeitem.at(i) = nouv;
            objetselect.push_back(nouv);
            }

            else if(!temp->objet->nom.compare("quadrilatere")){

                quadrilatere* quad =(quadrilatere*) temp->objet;

                if(!quad->get_type().compare("rectangle")){

                    rectangle* temp2 = (rectangle *) temp->objet;
                    rectangle* nouveau = new rectangle(point2D(temp2->get_origine().get_x(),temp2->get_origine().get_y()+5),
                                                       point2D(temp2->get_point2().get_x() ,temp2->get_point2().get_y() +5),
                                                       point2D(temp2->get_point3().get_x() ,temp2->get_point3().get_y() -5),
                                                       point2D(temp2->get_extremite().get_x(),temp2->get_extremite().get_y() -5));
                    Item* nouv = new Item(nouveau,couleur,epaisseur);
                    nouv->moveBy(temp->pos().x(),temp->pos().y());
                    g->scene->addItem(nouv);
                    g->scene->removeItem(temp);
                    g->listeitem.at(i) = nouv;
                    objetselect.push_back(nouv);
                }
                else if(!quad->get_type().compare("carre")){

                    carre* temp2 = (carre*) temp->objet;
                    carre* nouveau = new carre(point2D(temp2->get_origine().get_x()+5,temp2->get_origine().get_y() +5),temp2->get_cote()-10);

                    Item* nouv = new Item(nouveau,couleur,epaisseur);
                    nouv->moveBy(temp->pos().x(),temp->pos().y());
                    g->scene->addItem(nouv);
                    g->scene->removeItem(temp);
                    g->listeitem.at(i) = nouv;
                    objetselect.push_back(nouv);
                }
             else if(!quad->get_type().compare("losange")){

                 losange* temp2 = (losange *) temp->objet;
                 losange* nouveau = new losange(temp2->get_origine(),
                                                point2D(temp2->get_point2().get_x(),temp2->get_point2().get_y()-5),
                                                temp2->get_diag1(),
                                                temp2->get_diag2()-10);
                 Item* nouv = new Item(nouveau,couleur,epaisseur);
                 nouv->moveBy(temp->pos().x(),temp->pos().y());
                 g->scene->addItem(nouv);
                 g->scene->removeItem(temp);
                 g->listeitem.at(i) = nouv;
                 objetselect.push_back(nouv);

             }
             }
            else if(!temp->objet->nom.compare("triangle")){
            triangle* temp2 = (triangle *) temp->objet;
            triangle* nouveau = new triangle(point2D(temp2->get_origine().get_x(),temp2->get_origine().get_y() +5),
                                             point2D(temp2->get_point2().get_x(), temp2->get_point2().get_y() -5 ),
                                             point2D(temp2->get_extremite().get_x(),temp2->get_extremite().get_y() +5));
            Item* nouv = new Item(nouveau,couleur,epaisseur);
            nouv->moveBy(temp->pos().x(),temp->pos().y());
            g->scene->addItem(nouv);
            g->scene->removeItem(temp);
            g->listeitem.at(i) = nouv;
            objetselect.push_back(nouv);

            }
            else if(!temp->objet->nom.compare("segment")){
            segment* temp2 = (segment *) temp->objet;
            temp2->set_origine(point2D(temp2->get_origine().get_x() ,
                                         temp2->get_origine().get_y() + 5));
            temp2->set_extremite(point2D(temp2->get_extremite().get_x() ,
                                         temp2->get_extremite().get_y() - 5));
            segment* nouveau = new segment(temp2->get_origine(),temp2->get_extremite());
            Item* nouv = new Item(nouveau,couleur,epaisseur);
            nouv->moveBy(temp->pos().x(),temp->pos().y());
            g->scene->addItem(nouv);
            g->scene->removeItem(temp);
            g->listeitem.at(i) = nouv;
            objetselect.push_back(nouv);

            }
        }
        for(int unsigned i = 0 ; i < objetselect.size(); i ++){
            Item* temp = objetselect.at(i);
            temp->setSelected(true);
        }
    }
}

void MainWindow::on_pushButton_6_clicked()
{
    //réduire largeur et hauteur
    on_pushButton_2_clicked();
    on_pushButton_4_clicked();
}

void MainWindow::on_pushButton_5_clicked()
{
    //augmenter largeur et hauteur
    on_pushButton_3_clicked();
    on_pushButton_clicked();
}

void MainWindow::on_actionLosange_triggered()
{
    if(g->losang){
        g->losang = false;
    }else{

        g->losang = true;
        QAction* action;
        foreach(action,liste_actions){
            if(action->objectName().compare("actionLosange")){
                action->setChecked(false);
            }
        }

        g->multiseg = false;
        g->carr = false;
        g->triangl = false;
        g->rect = false;
        g->seg = false;
        g->trois = false;
        g->premier = true;
        g->deux = false;
    }
}



void MainWindow::on_actionCarre_triggered()
{
    if(g->carr){
        g->carr = false;
    }
    else{
        g->carr = true;

        QAction* action;
        foreach(action,liste_actions){
            if(action->objectName().compare("actionCarre")){
                action->setChecked(false);
            }
        }


        g->multiseg = false;
        g->losang = false;
        g->triangl = false;
        g->rect = false;
        g->seg = false;
        g->trois = false;
        g->premier = true;
        g->deux = false;
    }
}

void MainWindow::on_select_couleur_clicked()
{
    couleur = QColorDialog::getColor(Qt::white,this);

    ui->select_couleur->setStyleSheet(QString::fromUtf8("background-color: rgb(")
                                +QString::number(couleur.red())
                                +QString::fromUtf8(", ")
                                +QString::number(couleur.green())
                                +QString::fromUtf8(", ")
                                +QString::number(couleur.blue())
                                +QString::fromUtf8(");"));
    g->couleur = couleur;

}

void MainWindow::on_epaisseur_editingFinished()
{
    epaisseur = ui->epaisseur->value();
    g->epaisseur = epaisseur;
}

void MainWindow::on_epaisseur_valueChanged(double arg1)
{
      epaisseur = arg1;
      g->epaisseur = epaisseur;
}

void MainWindow::on_mise_a_jour_clicked()
{
    for(int unsigned i = 0 ; i < g->listeitem.size() ; i ++){
        Item* temp =(Item*) g->listeitem.at(i);
        if(temp->isSelected()){
            temp->couleur = couleur;
            temp->epaisseur = epaisseur;
        }
    }
}

void MainWindow::on_actionImprimer_triggered()
{
    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, this);
    dialog->setWindowTitle(tr("Imprimer le graphique"));
    if(dialog->exec() == QDialog::Accepted){
        QPainter painter(&printer);

        g->render(&painter,QRectF( 0,50,painter.viewport().width(),painter.viewport().height()));
        QDate actuelle = QDate::currentDate();
        QString date =  QString::number(actuelle.day()) + "-" + QString::number(actuelle.month()) +  "-" + QString::number(actuelle.year()) ;
        painter.drawText(g->width()/2+150,1000,date );
    }
    else{
    return;
   }
    return;
}
