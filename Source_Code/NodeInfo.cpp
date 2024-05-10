//
// Created by lucas on 03/05/2024.
//

#include "NodeInfo.h"
using namespace std;

/**
 * @file NodeInfo.cpp
 * @brief Implementation of class NodeInfo.
 *
 */

/*
 * Gets the node id.
 * Complexity: O(1)
 * @return node id
 */
int NodeInfo::getId() const {
    return id;
}
/**
 * Gets the node label.
 * Complexity: O(1)
 * @return node label
 */
string NodeInfo::getLabel() const {
    return label;
}
/**
 * Gets the node latitude.
 * Complexity: O(1)
 * @return node latitude
 */
double NodeInfo::getLatitude() const {
    return latitude;
}
/**
 * Gets the node longitude.
 * Complexity: O(1)
 * @return node longitude
 */
double NodeInfo::getLongitude() const {
    return longitude;
}

bool NodeInfo::operator==(const NodeInfo &info) const {
    return this->id == info.id && this->label == info.label && this->latitude == info.latitude && this->longitude == info.longitude;
}
