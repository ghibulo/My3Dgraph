#ifndef COORDSYSTEM_H
#define COORDSYSTEM_H
#include <cmath>
#include <iostream>

double adjustAngle(double angl);

//2D + 3D vectors + points
struct Pos2 {
    double x,y;
    Pos2(double x1=0,double y1=0){ x=x1;y=y1;}
};

struct Pos3 {
    double x,y,z;
    double alpha, beta; //alpha - angle in the plane xz, beta - angle in a plane perpendicular
    Pos3(double x1=0,double y1=0, double z1=0){ x=x1;y=y1;z=z1;calcPolar();}
    double getSize(bool ready=false){return ready?siz:siz=sqrt(pow(x,2)+pow(y,2)+pow(z,2));}

    Pos3 operator*(double k) {return Pos3(k*x,k*y,k*z);}
    Pos3 operator+(Pos3 p) {return Pos3(p.x+x,p.y+y,p.z+z);}
    void setAlpha(double a) {alpha = adjustAngle(a);calcCart();}
    void setBeta(double b) {beta = adjustAngle(b);calcCart();}
    private:
        double siz;
        void calcPolar() {
            beta = asin(y/getSize());
            alpha=acos(x/(siz*cos(beta)));
        }
        void calcCart() {
            x = getSize()*cos(alpha)*cos(beta);
            z = siz*sin(alpha)*cos(beta);
            y = siz*sin(beta);
        }
};


class CoordSystem
{
    public:

        CoordSystem(Pos2 c, Pos3 x, Pos3 y, Pos3 z);
        virtual ~CoordSystem();
        Pos2 getAbsPosition(Pos3 point);    //from Pos3 to Cartesian coord.
        Pos3 transformPosition(Pos3 point); //transform according to vx,vy,vz
        void setXYvectors(Pos3 vecx, Pos3 vecy);
        Pos3 resizeVector(Pos3 vec, double s);
        Pos2 pos3Topos2 (Pos3 vec);
        Pos2 drawLine(Pos2 st, Pos3 en);    //line from st -> en; return en transformed to absolute Pos2
        void addToAlpha(double dalpha);
        void addToBeta(double dbeta);

    protected:

    private:
    public:
    Pos2 center; //abs centrum of the screen
    Pos3 centrum; //abs centrum + (z=0)
    Pos3 vx,vy,vz; //axis vectors
};

#endif // COORDSYSTEM_H
