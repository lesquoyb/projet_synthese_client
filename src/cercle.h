#ifndef CERCLE_H
#define CERCLE_H
#include "formegeom.h"
#include "point.h"

class Cercle : public FormeGeom{

private:

    Cercle();
    Point _centre;
    double _rayon;

public:

    Cercle(const Point& centre,double rayon);
    Cercle(const string &couleur,const Point& centre, double rayon);
    virtual double aire()const ;
    virtual void rotation(const Point &p, const Angle& angle) ;
    virtual void homothetie(const Point& p, const double scale) ;
    virtual void translation(const Vecteur& v) ;
    virtual void dessin()const;
};

#endif // CERCLE_H