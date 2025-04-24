#include "GeoEntities.h"
#include <math.h>
#include <iostream>

namespace Geoutils{


Vector Geoutils::Vector::operator+(const Vector& adder){
    return Vector(this->x+adder.x,this->y+adder.y);
}

Vector Geoutils::Vector::operator-(const Vector& substractor){
    return Vector(this->x-substractor.x,this->y-substractor.y);
}

Vector Geoutils::Vector::operator*(const float& multiplier){
    return Vector(this->x*multiplier,this->y* multiplier);
}

Vector Vector::GetPerpendicular() const{
    return Vector(this->y, this->x * -1);
}

float Vector::GetNorm() const{
    return sqrtf((this->x) * (this->x) + (this->y) * (this->y));
}

Line::Line(Point a, Vector v, float multiplier) {
    this->origin = a;
    this->v = v*multiplier;
}

Line::Line(Point a, Point b) {
    this->origin = a;
    this->v = b-a;
}

Point Line::GetIntersection(Line l) {
    auto xV = this->v.x;
    auto yV = this->v.y;
    auto xU = l.v.x;
    auto yU = l.v.y;
    auto xB = l.origin.x;
    auto yB = l.origin.y;
    auto xA = this->origin.x;
    auto yA = this->origin.x;

    if (xV == xU && yV == yU) {
        return NULL_POINT;
    }
    auto t = ((xB - xA) * yU - (yB - yA) * xU) / (xV * yU - yV * xU);
    return this->origin+v*t;

}

Point Line::GetIntersection(Line l, float lowerBound, float upperBound, float secondLowerBound, float secondUpperBound) {
    auto xV = this->v.x;
    auto yV = this->v.y;
    auto xU = l.v.x;
    auto yU = l.v.y;
    auto xB = l.origin.x;
    auto yB = l.origin.y;
    auto xA = this->origin.x;
    auto yA = this->origin.x;


    if (xV == xU && yV == yU) {
        return NULL_POINT;
    }
    float t = ((xB - xA) * yU - (yB - yA) * xU) / (xV * yU - yV * xU);
    float T = ((xB - xA) * yV - (yB - yA) * xV) / (xV * yU - yV * xU);
    if (t >= lowerBound && t <= upperBound && T>=secondLowerBound && T<=secondUpperBound) {
        //std::cout << "T:" << T<< std::endl;
        //std::cout << "t:" << t << std::endl;
        return this->origin+v*t;
    }
    return NULL_POINT;

}

Vector Vector::Rotate(float angle) const{
    auto alpha=acos(this->x/this->GetNorm());
    if (this->y<0){
        alpha=-alpha;
    }
    return Vector(cos(alpha+angle)*this->GetNorm(),sin(alpha+angle)*this->GetNorm());
}


Point Point::Rotate(Point center, float angle){
    auto v = *this-center;
    return *this+v.Rotate(angle);
}
}