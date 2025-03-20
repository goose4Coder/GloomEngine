#ifndef GEO_ENTITIES_H
#define GEO_ENTITIES_H

namespace Geoutils{
    class Coordinates{
        public:
        Coordinates() {};
        Coordinates(float x,float y);
        Coordinates operator+(const Coordinates& adder);
        Coordinates operator-(const Coordinates& substractor);
        Coordinates operator*(const float& multiplier);

        float x=0;
        float y=0;
    };
    class IPointOperatable{
        public:
            virtual Coordinates GetCoordinates() const =0 ;
            virtual ~IPointOperatable(){};
    };

    class Vector : public IPointOperatable {
    public:
        Vector(float x, float y);
        Vector(Coordinates coordinates);
        Vector operator*(const float& multiplier);
        Vector GetPerpendicular() const;
        float GetNorm() const;
        Coordinates GetCoordinates() const override;
        Vector Rotate(float angle) const;
    protected:
        Coordinates value;
    };

    class Point: public IPointOperatable{
        public:
        Point(float x, float y);
        Point(Coordinates coordinates);
        Point(){this->isNull=true;}
        Coordinates GetCoordinates() const override;
        Point Translate(Vector v);
        Point Rotate(Point center,float angle);
        inline bool Exists() {
            return !this->isNull;
        }
        protected:
        bool isNull=false;
        Coordinates coordinates;
    };

# define NULL_POINT Point()

   

    class Line {
    public:
        Line(Point a, Vector v);
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

    Vector DirectVector(const IPointOperatable& from, const IPointOperatable& to);

}
#endif