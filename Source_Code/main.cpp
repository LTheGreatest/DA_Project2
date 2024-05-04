//
// Created by lucas on 03/05/2024.
//
#include <iostream>
#include "graph.h"
#include "parse.h"

int main(){
    Graph<NodeInfo> g;
    int n = 1;
    std::unordered_map<int, NodeInfo> map;
    readNodes(DataSetSelection::SMALL, map, g,n);
    readEdges(DataSetSelection::SMALL,map,g,n);

    for(auto a : g.getVertexSet()){
        std::cout << "Vertex with ID of: " << a->getInfo().getId() << " has this edges :" << std::endl;
        for (auto e : a->getAdj()){
            std::cout << "To " << e->getDest()->getInfo().getId() << " with distance of " << e->getWeight() << std::endl;
        }
    }
    return 0;
}
