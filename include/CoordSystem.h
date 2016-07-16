#ifndef COORDSYSTEM_H
#define COORDSYSTEM_H



struct Pos2 {
    double x,y;
    Pos2(double x1=0,double y1=0){ x=x1;y=y1;}
};

struct Pos3 {
    double x,y,z;
    Pos3(double x1=0,double y1=0, double z1=0){ x=x1;y=y1;z=z1;}
    Pos3 operator*(double k) {return Pos3(k*x,k*y,k*z);}
    Pos3 operator+(Pos3 p) {return Pos3(p.x+x,p.y+y,p.z+z);}
};


class CoordSystem
{
    public:

        CoordSystem(Pos2 c, Pos3 x, Pos3 y, Pos3 z);
        virtual ~CoordSystem();
        Pos2 getAbsPosition(Pos3 point);    //from Pos3 to Cartesian coord.
        Pos3 transformPosition(Pos3 point); //transform according to vx,vy,vz
        double getDistance(Pos3 point);
    protected:

    private:
    Pos2 center; //abs centrum of the screen
    Pos3 centrum; //abs centrum + (z=0)
    Pos3 vx,vy,vz; //axis vectors
};

#endif // COORDSYSTEM_H
