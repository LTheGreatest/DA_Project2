//
// Created by Utilizador on 5/3/2024.
//

#ifndef PROJECT2_NODEINFO_H
#define PROJECT2_NODEINFO_H

#include <iostream>

class NodeInfo {
    NodeInfo(int id_, std::string label_ = "", double longitude_ = 0, double latitude_ = 0) : id(id_),label(label_),longitude(longitude_),latitude(latitude_) {}

    //getters
    int getId() const;
    std::string getLabel() const;
    double getLatitude() const;
    double getLongitude() const;

    private:
        int id;
        std::string label;
        double longitude;
        double latitude;
};

int NodeInfo::getId() const {
    return id;
}
std::string NodeInfo::getLabel() const {
    return label;
}
double NodeInfo::getLatitude() const {
    return latitude;
}
double NodeInfo::getLongitude() const {
    return longitude;
}




#endif //PROJECT2_NODEINFO_H
