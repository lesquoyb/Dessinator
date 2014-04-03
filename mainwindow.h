#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "graphique.h"
#include "carre.h"
#include "rectangle.h"
#include "losange.h"
#include "quadrangle.h"
#include "arcDeCercle.h"
#include "ellipse.h"
#include "cercle.h"
#include "dessinTechnique.h"
#include "objetgeom.h"
#include "triangle.h"
#include "angle.h"
#include "multisegment.h"
#include "point2d.h"
#include "quadrilatere.h"
#include "segment.h"
#include "losange.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void sauver(const QString &);
    void paintEvent(QPaintEvent *);
    void Ouvrir();
    graphique* g;
    QList<QAction*> liste_actions;
    Item* selectionne;
    ~MainWindow();

private slots:
    void on_actionNouveau_triggered();

    void on_actionOuvrir_triggered();

    void on_actionSauvegarder_triggered();

    void on_actionQuadrilatere_triggered();

    void on_actionCercle_triggered();

    void on_actionTriangle_triggered();

    void on_actionSegment_triggered();

    void on_actionMultisegment_triggered();

    void on_actionGomme_triggered();

    void on_pushButton_clicked();

    void on_actionPerimetre_triggered();

    void on_actionAire_triggered();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_actionLosange_triggered();


    void on_actionCarre_triggered();

    void on_select_couleur_clicked();

    void on_epaisseur_editingFinished();

    void on_epaisseur_valueChanged(double arg1);

    void on_mise_a_jour_clicked();

    void on_actionImprimer_triggered();


private:
    Ui::MainWindow *ui;
    QString nomfichier;
    QColor couleur;
    double epaisseur;
};

#endif // MAINWINDOW_H
