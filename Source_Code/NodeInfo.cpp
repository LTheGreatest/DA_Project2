//
// Created by lucas on 03/05/2024.
//

#include "NodeInfo.h"
using namespace std;

int NodeInfo::getId() const {
    return id;
}
string NodeInfo::getLabel() const {
    return label;
}
double NodeInfo::getLatitude() const {
    return latitude;
}
double NodeInfo::getLongitude() const {
    return longitude;
}

bool NodeInfo::operator==(const NodeInfo &info) const {
    return this->id == info.id && this->label == info.label && this->latitude == info.latitude && this->longitude == info.longitude;
}
