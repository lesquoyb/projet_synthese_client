#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "erreur.h"
#include <qfiledialog.h>
#include <qmessagebox.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _connexion(NULL),
    _dessinManager(NULL)
    {
        ui->setupUi(this);
        listeFormes = ui->listeFormes;
    }

MainWindow::~MainWindow(){
    delete ui;
    //On vide uniquement forme car les autres vector partagent les même pointeurs
    for(FormeGeom* f : _formes){
        delete f;
    }
}

/**
 * @brief MainWindow::rafraichirListe
 * Rafraîchit l'affichage de la liste.
 */
void MainWindow::rafraichirListe(){
    listeFormes->clear();
    ui->listeGroupe->clear();
    for(FormeGeom* f : _formes){
        listeFormes->addItem(QString(f->toString().c_str()));
    }
    for(Groupe* g: _groupes){
        if ( g != NULL ){
            ui->listeGroupe->addItem(QString(g->toString().c_str()));
        }
    }
}

/**
 * @brief MainWindow::on_ajout_cercle_clicked
 * Ajoute un cercle à la liste.
 */
void MainWindow::on_ajout_cercle_clicked(){
    Point centre(ui->centreX->value(),ui->centreY->value());
    Couleurs::Couleur couleur = Couleurs::intToCouleur(ui->couleurCercle->currentIndex());
    Cercle c(couleur,centre,ui->rayon->value());
    _formes.push_back(c.clone());
    _polygones.push_back(NULL);
    rafraichirListe();
}


/**
 * @brief MainWindow::on_ajout_segment_clicked
 * Ajoute un segment à la liste
 */
void MainWindow::on_ajout_segment_clicked(){
    Point p1(ui->sP1X->value(),ui->sP1Y->value());
    Point p2(ui->sP2X->value(),ui->sP2Y->value());
    Couleurs::Couleur couleur = Couleurs::intToCouleur(ui->couleurSegment->currentIndex());
    Segment s(couleur,p1,p2);
    _formes.push_back(s.clone());
    _polygones.push_back(NULL);
    rafraichirListe();
}

/**
 * @brief MainWindow::on_ajout_triangle_clicked
 * Ajoute un triangle à la liste
 */
void MainWindow::on_ajout_triangle_clicked(){
    Point p1(ui->tP1X->value(),ui->tP1Y->value());
    Point p2(ui->tP2X->value(),ui->tP2Y->value());
    Point p3(ui->tP3X->value(),ui->tP3Y->value());
    Couleurs::Couleur couleur = Couleurs::intToCouleur(ui->couleurTriangle->currentIndex());
    Triangle t(couleur,p1,p2,p3);
    _formes.push_back(t.clone());
    _polygones.push_back(NULL);
    rafraichirListe();
}





/**
 * @brief MainWindow::on_ajouterPoint_clicked
 * ajoute un point au polygone selectionné
 */
void MainWindow::on_ajouterPoint_clicked(){
    int index = ui->listeFormes->currentRow();
    if(  (index != -1) and  (_polygones[index] != NULL) ){//On vérifie qu'on a bien selectionné un polygone
        Point p (ui->ajoutPX->value(),ui->ajoutPY->value());
        _polygones[index]->ajouterPoint(p);
    }
    rafraichirListe();
}

/**
 * @brief MainWindow::on_ajout_polygone_clicked
 * AJoute un point au polygone sélectionné.
 */
void MainWindow::on_ajout_polygone_clicked(){
    Point p1(ui->pP1X->value(),ui->pP1Y->value());
    Point p2(ui->pP2X->value(),ui->pP2Y->value());
    Point p3(ui->pP3X->value(),ui->pP3Y->value());
    Couleurs::Couleur couleur = Couleurs::intToCouleur(ui->couleurPolygone->currentIndex());
    Polygone p(couleur,p1,p2,p3);
    Polygone* poly = p.clone();
    _formes.push_back(poly);
    _polygones.push_back(poly);
    rafraichirListe();
}

void MainWindow::on_creer_groupe_clicked(){
    Couleurs::Couleur couleur = Couleurs::intToCouleur(ui->couleurGroupe->currentIndex());
    Groupe p(couleur);
    Groupe* groupe = p.clone();
    _formes.push_back(groupe);
    _groupes.push_back(groupe);
    _polygones.push_back(NULL);
    rafraichirListe();
}

void MainWindow::on_ajout_groupe_clicked(){
    int indexForme =  ui->listeFormes->currentRow();
    int indexGroupe = ui->listeGroupe->currentRow();
    if ( (indexForme != -1) and (indexGroupe != -1) and (_groupes[indexGroupe] != _formes[indexForme]) ){
        FormeGeom* f = _formes[indexForme];
        _groupes[indexGroupe]->ajouter(*f);

        // On supprime la forme des listes.
        int i = 0;
        for(Groupe* g: _groupes){
            if(g == f){
                _groupes.erase(_groupes.begin()+i);
                break;
            }
            i++;
        }

        delete f;
        _polygones.erase(_polygones.begin()+indexForme);
        _formes.erase( _formes.begin()+indexForme);

    }
    rafraichirListe();
}

void MainWindow::on_dessiner_tout_clicked(){
    if(_connexion != NULL){
        for(FormeGeom* f : _formes){
            f->dessin(*_dessinManager);
        }
    }
}

void MainWindow::on_dessiner_forme_clicked(){
    if(_connexion != NULL){
        int index =  ui->listeFormes->currentRow();
        if( index != -1 ){
            _formes[index]->dessin(*_dessinManager);
        }
    }
}

void MainWindow::on_connexion_clicked(){

    try{
        if(_connexion != NULL){
            delete _connexion;
            _connexion = NULL;
        }
        _connexion = new Connexion(ui->ip->text().toStdString(),ui->port->text().toInt());
    }
    catch(Erreur e){
        _connexion = NULL;
    }

    if(_connexion != NULL){
        delete _dessinManager;
        _dessinManager = new DessinManager(_connexion);
        ui->status_reseau->setPixmap(QPixmap(":images/ressources/images/Green_check.png"));
    }
    else{
        ui->status_reseau->setPixmap(QPixmap(":images/ressources/images/echec.png"));

    }
}

void MainWindow::on_chargement_clicked(){
    QString fileName = QFileDialog::getOpenFileName(this, tr("Chargement d'une forme géométrique"), "",tr("Text Files (*.txt);;Dessinator files (*.dess)"));
    if (fileName != "") {
       FormeGeom* f = FormeGeom::chargement(fileName.toStdString());
       if (f != NULL){
           if(f->toString().find("groupe") == 0){
                _groupes.push_back((Groupe*)f);
           }
           if(f->toString().find("polygone") == 0 ){
               _polygones.push_back((Polygone*)f);
           }
           else{
               _polygones.push_back(NULL);
           }
           _formes.push_back(f);
           rafraichirListe();
       }
    }

}

void MainWindow::on_sauver_clicked(){
    int index =  ui->listeFormes->currentRow();
    if( index != -1 ){
        QString fileName = QFileDialog::getSaveFileName(this, tr("Sauvegarde d'une forme géométrique"), "",tr("Text Files (*.txt);;Dessinator files (*.dess)"));
        if (fileName != "") {
           _formes[index]->sauvegarder(fileName.toStdString());
        }
    }
}

void MainWindow::on_supprimer_clicked(){
    int index =  ui->listeFormes->currentRow();
    if( index != -1 ){
        FormeGeom* f = _formes[index];
        int i = 0;
        for(Groupe* g: _groupes){
            if(g == f){
                _groupes.erase(_groupes.begin()+i);
                break;
            }
            i++;
        }
        delete f;
        _formes.erase( _formes.begin()+index);
        _polygones.erase(_polygones.begin()+index);

    }
    rafraichirListe();
}

void MainWindow::on_translation_clicked(){
    int index =  ui->listeFormes->currentRow();
    if( index != -1 ){
        Vecteur v(ui->deltaX->value(),ui->deltaY->value());
        FormeGeom* temp = _formes[index];
        FormeGeom* f = temp->translation(v);
        size_t i = 0;
        for(Groupe* g: _groupes){
            if(g == temp){
                _groupes[i] = (Groupe*) f;
                break;
            }
            i++;
        }
        i = 0;
        for(Polygone* p : _polygones){
            if (p == temp){
                _polygones[i] =  (Polygone*) f;
                break;
            }
            i++;
        }
        if(i == _polygones.size()){
            _polygones[index] = NULL;
        }
        _formes[index] = f;
        delete temp;

    }
    rafraichirListe();
}

void MainWindow::on_rotation_clicked(){
    int index =  ui->listeFormes->currentRow();
    if( index != -1 ){
        Point p(ui->rX->value(),ui->rY->value());
        FormeGeom* temp = _formes[index];
        FormeGeom* f = temp->rotation(p,ui->angle->value());
        size_t i = 0;
        for(Groupe* g: _groupes){
            if(g == temp){
                _groupes[i] = (Groupe*) f;
                break;
            }
            i++;
        }
        i = 0;
        for(Polygone* p : _polygones){
            if (p == temp){
                _polygones[i] =  (Polygone*) f;
                break;
            }
            i++;
        }
        if(i == _polygones.size()){
            _polygones[index] = NULL;
        }
        _formes[index] = f;
        delete temp;

    }
    rafraichirListe();
}

void MainWindow::on_homothetie_clicked(){
    int index =  ui->listeFormes->currentRow();
    if( index != -1 ){
        Point p(ui->hX->value(),ui->hY->value());
        FormeGeom* temp = _formes[index];
        FormeGeom* f = temp->homothetie(p,ui->scale->value());
        size_t i = 0;
        for(Groupe* g: _groupes){
            if(g == temp){
                _groupes[i] = (Groupe*) f;
                break;
            }
            i++;
        }
        i = 0;
        for(Polygone* p : _polygones){
            if (p == temp){
                _polygones[i] =  (Polygone*) f;
                break;
            }
            i++;
        }
        if(i == _polygones.size()){
            _polygones[index] = NULL;
        }
        _formes[index] = f;
        delete temp;
    }
    rafraichirListe();
}

void MainWindow::on_actionAire_triggered(){
    double somme = 0;
    for(FormeGeom* f : _formes){
        somme += f->aire();
    }
    QMessageBox box;
    QString mess = QString("L'aire totale cumlée des formes est de: ")+ QString::number(somme);//TODO
    box.critical(NULL,"Aire totale cumulée",mess);

}
