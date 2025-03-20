#include "GeoEntities.h"

Geoutils::Coordinates::Coordinates(float x,float y){
    this->x=x;
    this->y=y;
}

Geoutils::Coordinates Geoutils::Coordinates::operator+(const Coordinates& adder){
    return Coordinates(this->x+adder.x,this->y+adder.y);
}

Geoutils::Coordinates Geoutils::Coordinates::operator-(const Coordinates& substractor){
    return Coordinates(this->x-substractor.x,this->y-substractor.y);
}

Geoutils::Coordinates Geoutils::Coordinates::operator*(const float& multiplier){
    return Coordinates(this->x*multiplier,this->y* multiplier);
}


