#include "GeoEntities.h"
#include <math.h>
using namespace Geoutils;
#include <iostream>

Coordinates Point::GetCoordinates() const {
    return this->coordinates;
}

Coordinates Vector::GetCoordinates() const {
    return this->value;
}

Vector::Vector(float x, float y){
    this->value=Coordinates(x,y);
}

Vector::Vector(Coordinates coordinates) {
    this->value = coordinates;
};

Vector Geoutils::DirectVector(const IPointOperatable& from, const IPointOperatable& to) {
    return Vector(to.GetCoordinates()-from.GetCoordinates());
}
Vector Vector::operator*(const float& multiplier) {
    return Vector(this->value.x*multiplier, this->value.y * multiplier);
}

Point::Point(float x,float y) {
    this->coordinates = Coordinates(x,y);
};

Point::Point(Coordinates coordinates) {
    this->coordinates = coordinates;
};

Point Point::Translate(Vector v){
    return Point(this->GetCoordinates() + v.GetCoordinates());
}

Vector Vector::GetPerpendicular() const{
    return Vector(this->value.y, this->value.x * -1);
}

float Vector::GetNorm() const{
    return sqrtf((this->value.x) * (this->value.x) + (this->value.y) * (this->value.y));
}

Line::Line(Point a, Vector v) {
    this->origin = a;
    this->v = v;
}

Line::Line(Point a, Point b) {
    this->origin = a;
    this->v = DirectVector(a, b);
}

Point Line::GetIntersection(Line l) {
    auto xV = this->v.GetCoordinates().x;
    auto yV = this->v.GetCoordinates().y;
    auto xU = l.v.GetCoordinates().x;
    auto yU = l.v.GetCoordinates().y;
    auto xB = l.origin.GetCoordinates().x;
    auto yB = l.origin.GetCoordinates().y;
    auto xA = this->origin.GetCoordinates().x;
    auto yA = this->origin.GetCoordinates().x;

    if (xV == xU && yV == yU) {
        return NULL_POINT;
    }
    auto t = ((xB - xA) * yU - (yB - yA) * xU) / (xV * yU - yV * xU);
    return this->origin.Translate(this->v * t);

}

Point Line::GetIntersection(Line l, float lowerBound, float upperBound, float secondLowerBound, float secondUpperBound) {
    auto xV = this->v.GetCoordinates().x;
    auto yV = this->v.GetCoordinates().y;
    auto xU = l.v.GetCoordinates().x;
    auto yU = l.v.GetCoordinates().y;
    auto xB = l.origin.GetCoordinates().x;
    auto yB = l.origin.GetCoordinates().y;
    auto xA = this->origin.GetCoordinates().x;
    auto yA = this->origin.GetCoordinates().y;


    if (xV == xU && yV == yU) {
        return NULL_POINT;
    }
    float t = ((xB - xA) * yU - (yB - yA) * xU) / (xV * yU - yV * xU);
    float T = ((xB - xA) * yV - (yB - yA) * xV) / (xV * yU - yV * xU);
    if (t >= lowerBound && t <= upperBound && T>=secondLowerBound && T<=secondUpperBound) {
        //std::cout << "T:" << T<< std::endl;
        //std::cout << "t:" << t << std::endl;
        return this->origin.Translate(this->v * t);
    }
    return NULL_POINT;

}

Vector Vector::Rotate(float angle) const{
    auto alpha=acos(this->GetCoordinates().x/this->GetNorm());
    if (this->GetCoordinates().y<0){
        alpha=-alpha;
    }
    return Vector(cos(alpha+angle)*this->GetNorm(),sin(alpha+angle)*this->GetNorm());
}


Point Point::Rotate(Point center, float angle){
    auto v = DirectVector(center,*this);
    return this->Translate(v.Rotate(angle));
}