#include "triangle.h"


Triangle::Triangle(const Point &p1, const Point &p2, const Point &p3):
FormeGeom(),
_p1(p1),
_p2(p2),
_p3(p3)
{}

Triangle::Triangle(const string &couleur, const Point &p1, const Point &p2, const Point &p3):
FormeGeom(couleur),
_p1(p1),
_p2(p2),
_p3(p3)
{}


double Triangle::aire() const{
    //calcul de l'aire par la méthode de Héron
    double distP1P2 = sqrt( pow(_p1.getX() - _p2.getX(),2)+ pow(_p1.getY() - _p2.getY(),2) );
    double distP1P3 = sqrt( pow(_p1.getX() - _p3.getX() ,2)+ pow(_p1.getY() - _p3.getY() ,2) );
    double distP3P2 = sqrt( pow(_p3.getX() - _p2.getX() ,2)+ pow(_p3.getY() - _p2.getY() ,2) );
    double demiPerimetre = (distP1P2 + distP1P3 + distP3P2) / 2;
    return sqrt( demiPerimetre * (demiPerimetre - distP1P2) * (demiPerimetre - distP1P3) * (demiPerimetre - distP3P2) );
}

void Triangle::rotation(const Point &p, const Angle &angle){
    _p1.rotation(p,angle);
    _p2.rotation(p,angle);
    _p3.rotation(p,angle);
}

void Triangle::homothetie(const Point &p, const double scale){
    _p1.homothetie(p,scale);
    _p2.homothetie(p,scale);
    _p3.homothetie(p,scale);
}

void Triangle::translation(const Vecteur &v){
    _p1.translation(v);
    _p2.translation(v);
    _p3.translation(v);
}

void Triangle::dessin() const{
//TODO
}