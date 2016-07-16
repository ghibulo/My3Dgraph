#include "CoordSystem.h"
#include <cmath>

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
    return Pos3(getDistance(vx*point.x+centrum), getDistance(vy*point.y+centrum), getDistance(vz*point.z+centrum));
}

double CoordSystem::getDistance(Pos3 point) {

    return sqrt(pow(point.x,2)+pow(point.y,2)+pow(point.y,2));
}
