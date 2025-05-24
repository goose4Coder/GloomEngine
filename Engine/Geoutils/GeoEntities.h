#ifndef GEO_ENTITIES_H
#define GEO_ENTITIES_H

namespace Geoutils{

    class Vector {
    public:
        Vector(){};
        Vector(bool exists){this->isNull=!exists;}
        Vector(float x, float y){
            this->x=x;
            this->y=y;
        };
         Vector operator*(const float& multiplier) const;
        Vector operator+(const Vector& adder) const;
        Vector operator-(const Vector& substractor) const;
        Vector GetPerpendicular() const;
        float GetNorm() const;
        Vector Rotate(float angle) const;
        Vector Rotate(Vector center,float angle);
        float GetRotation();
        inline bool Exists() {
            return !this->isNull;
        }
        float x=0;
        float y=0;
    protected:
        
        bool isNull=false;
    };

# define NULL_POINT Vector(false)
# define Point Vector
   

    class Line {
    public:
        Line();
        Line(Point a, Vector v, float multiplier);
        Line(Point a, Point b);
        Point GetIntersection(Line l, float lowerBound, float upperBound, float secondLowerBound, float secondUpperBound);
        Point GetIntersection(Line l);
        inline Vector GetVector() { return this->v; }
        inline Point GetProjection(Point p) {
            return this->GetIntersection(Line(p, this->v.GetPerpendicular()));
        };
    protected:
        Vector v = Vector(0, 0);
        Point origin = Point(0, 0);
    };

};
#endif