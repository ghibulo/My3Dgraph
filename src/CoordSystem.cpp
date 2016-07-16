#include "CoordSystem.h"
#include <cmath>
#include <allegro5/allegro_primitives.h>
#define NDEBUG

double adjustAngle(double angl) {
    return(angl>2*M_PI)?(angl-2*M_PI):(angl<0)?(angl+2*M_PI):angl;
}

CoordSystem::CoordSystem(Pos2 c, Pos3 x, Pos3 y, Pos3 z)
{
    center=c;
    centrum=Pos3(c.x,c.y,0);
    vx=x;vy=y;vz=z;
}

CoordSystem::~CoordSystem()
{
    //dtor
}

Pos2 CoordSystem::getAbsPosition(Pos3 point) {
    Pos2 res;
    res.x = point.x+center.x+point.z/sqrt(2);
    res.y = center.y- point.y-point.z/sqrt(2);
    return res;
}

Pos3 CoordSystem::transformPosition(Pos3 point) {
#ifdef DEBUG
    std::cout << vx.x << "," << vx.y << ", "<< vx.z << ", " << vx.alpha << ", " << vx.beta << std::endl;
    std::cout << vy.x << "," << vy.y << ", "<< vy.z << ", " << vy.alpha << ", " << vy.beta << std::endl;
    std::cout << vz.x << "," << vz.y << ", "<< vz.z << ", " << vz.alpha << ", " << vz.beta << std::endl;
#endif
    return (vx*point.x)+(vy*point.y)+(vz*point.z);
/*
    return Pos3(copysign((vx*point.x).getSize(),point.x), //sign of point.x, value of vx*point.x
                copysign((vy*point.y).getSize(),point.y),
                copysign((vz*point.z).getSize(),point.z));
*/
}


//setting vx, vy and calculate vz to get Cartesian coord.
void CoordSystem::setXYvectors(Pos3 vecx, Pos3 vecy) {
    vx = vecx;
    vy=vecy;
    vz = Pos3(vx.y*vy.z-vy.y*vx.z, -vx.x*vy.z+vx.z*vy.x, vx.y*vy.z-vx.z*vy.y); //vector product
    vz = resizeVector(vz,vx.getSize()); // |vz| = |vx|
}

void CoordSystem::addToAlpha(double dalpha) {
    vx.setAlpha(vx.alpha+dalpha);
    vz.setAlpha(vz.alpha+dalpha);
}

void CoordSystem::addToBeta(double dbeta) {
    vz.setBeta(vz.beta+dbeta);
    vy.setBeta(vy.beta+dbeta);
}

Pos3 CoordSystem::resizeVector(Pos3 vec, double s) {
    return vec*(s/vec.getSize());
}

Pos2 CoordSystem::pos3Topos2 (Pos3 vec) {
    Pos3 vt = transformPosition(vec);
    Pos2 res = getAbsPosition(vt);
    return res; //getAbsPosition(transformPosition(vec));
}

Pos2 CoordSystem::drawLine(Pos2 st, Pos3 en) {
    Pos2 p2 = getAbsPosition(transformPosition(en));
    al_draw_line(st.x, st.y, p2.x, p2.y,al_map_rgb(255,0,255) , 1);
    return p2;
}
