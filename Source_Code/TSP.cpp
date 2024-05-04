//
// Created by lucas on 04/05/2024.
//

#include "TSP.h"

using namespace std;

unordered_map<int, NodeInfo> TSP::getIdToNode() {
    return idToNode;
}

Graph<NodeInfo> TSP::getGraph() {
    return graph;
}


void TSP::backtrackingSolutionDFS(Vertex<NodeInfo> *v, double currentWeight, double *minWeight, int count) {
    
}


void TSP::backtrackingSolution() {
    //reset the Graph
    for(Vertex<NodeInfo> *v : graph.getVertexSet()){
        v->setVisited(false);
        v->setPath(nullptr);
        v->setProcesssing(false);
    }

    //create auxiliary data
    double currentWeight = 0;
    double minWeight = ULONG_LONG_MAX;
    Vertex<NodeInfo> *start = graph.findVertex(0);

    //executes the backtracking search
    backtrackingSolutionDFS(start, currentWeight, &minWeight, 1);

    //displays the results
    displayPathFound(minWeight);
}

void TSP::displayPathFound(double minWeight) {

}
