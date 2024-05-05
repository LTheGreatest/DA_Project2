//
// Created by lucas on 03/05/2024.
//
#include <iostream>
#include "graph.h"
#include "parse.h"
#include "TSP.h"

int main(){
    Graph<NodeInfo> g;
    int n = 2;
    std::unordered_map<int, NodeInfo> map;
    readNodes(DataSetSelection::SMALL, map, g,n);
    readEdges(DataSetSelection::SMALL,map,g,n);

    TSP tsp;
    tsp.setGraph(g);
    tsp.setIdToNode(map);
    tsp.backtrackingSolution();
    tsp.triangularAproxSolution();
    return 0;
}
