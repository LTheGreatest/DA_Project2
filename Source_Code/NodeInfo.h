//
// Created by Pedro on 5/3/2024.
//

#ifndef PROJECT2_NODEINFO_H
#define PROJECT2_NODEINFO_H

#include <iostream>

class NodeInfo {
    public:
        NodeInfo(int id_, std::string label_ = "", double longitude_ = 0, double latitude_ = 0) : id(id_),label(label_),longitude(longitude_),latitude(latitude_) {}
        NodeInfo() : id(0), latitude(0), longitude(0)  {};
        //getters
        int getId() const;
        std::string getLabel() const;
        double getLatitude() const;
        double getLongitude() const;

        bool operator==(const NodeInfo& info) const;

    private:
        int id;
        std::string label;
        double longitude;
        double latitude;
};

namespace  std
{
    template<>
    struct hash<NodeInfo>
    {
        size_t operator()(const NodeInfo& node) const {
            size_t idHash = hash<int>()(node.getId());
            size_t labelHash = hash<string>()(node.getLabel());
            size_t latitudeHash = hash<double>()(node.getLatitude());
            size_t longitudeHash = hash<double>()(node.getLongitude());
            return (idHash ^ labelHash ^ latitudeHash ^ longitudeHash) >> 1;
        }

        bool operator()(const NodeInfo& node1, const NodeInfo& node2) const{
            return node1.getId() == node2.getId()
            && node1.getLabel() == node2.getLabel()
            && node1.getLatitude() == node2.getLatitude()
            && node1.getLongitude() == node2.getLongitude();
        }
    };
}




#endif //PROJECT2_NODEINFO_H
