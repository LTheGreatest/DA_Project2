//
// Created by lucas on 04/05/2024.
//

#ifndef PROJECT2_TSP_H
#define PROJECT2_TSP_H


#include "Graph.h"
#include <unordered_map>

class TSP {

    //Backtracking
    void backtrackingSolutionDFS(Vertex<NodeInfo> *v, double currentWeight, double *minWeight, int count);
    void backtrackingSolution();



    //Auxiliary
    void displayPathFound(double minWeight);

    //getters
    std::unordered_map<int, NodeInfo> getIdToNode();
    Graph<NodeInfo> getGraph();
    private:
        std::unordered_map<int, NodeInfo> idToNode;
        Graph<NodeInfo> graph;
};


#endif //PROJECT2_TSP_H
