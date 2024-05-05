//
// Created by lucas on 04/05/2024.
//

#include "TSP.h"
#include <chrono>

using namespace std;

unordered_map<int, NodeInfo> TSP::getIdToNode() const{
    return idToNode;
}

Graph<NodeInfo> TSP::getGraph() const{
    return graph;
}


void TSP::backtrackingSolutionDFS(Vertex<NodeInfo> *v, double currentWeight, double *minWeight, vector<NodeInfo> currentSol, vector<NodeInfo> *bestSol, int count) const{
    for(auto e: v->getAdj()){
        Vertex<NodeInfo> *w = e->getDest();


        if(currentWeight + e->getWeight() >= *minWeight){
            //this path isn't the solution
            continue;
        }

        if((size_t) count == graph.getVertexSet().size() && w->getInfo().getId() == 0){
            //found a solution
            currentWeight += e->getWeight();
            currentSol.push_back(w->getInfo());

            if(currentWeight < *minWeight){
                //found a better solution
                *minWeight = currentWeight;
                *bestSol = currentSol;
            }
        }


        //if the node isn't visited continues the search with this node
        if(!w->isVisited() && w->getInfo().getId() != 0){
            w->setVisited(true);
            currentSol.push_back(w->getInfo());
            currentWeight += e->getWeight();
            backtrackingSolutionDFS(w,currentWeight, minWeight, currentSol, bestSol, count + 1);

            //eliminates the node from the solution for searching other solutions
            currentWeight -= e->getWeight();
            currentSol.erase(currentSol.end()--);
        }



    }

    v->setVisited(false);
}


void TSP::backtrackingSolution() const{
    auto clockStart= chrono::high_resolution_clock::now();
    //reset the Graph
    for(Vertex<NodeInfo> *v : graph.getVertexSet()){
        v->setVisited(false);
        v->setPath(nullptr);
        v->setProcesssing(false);
    }

    //create auxiliary data
    double currentWeight = 0;
    double minWeight = ULONG_LONG_MAX;
    NodeInfo info = idToNode.find(0)->second; //get the starting node info
    Vertex<NodeInfo> *start = graph.findVertex(info); //find the starting node in the graph
    vector<NodeInfo> currentSol {start->getInfo()};
    vector<NodeInfo> bestSol;


    //executes the backtracking search
    backtrackingSolutionDFS(start, currentWeight, &minWeight, currentSol, &bestSol, 1);

    auto clockEnd= chrono::high_resolution_clock::now();

    auto duration = clockEnd - clockStart;
    //displays the results
    displayPathFound(minWeight, bestSol, duration);
}

void TSP::displayPathFound(double minWeight, const vector<NodeInfo>& solution, std::chrono::duration<double> time) const{

    cout << "Cost: " << minWeight << "\n";
    cout << "Time: " << time.count() << '\n';

    for(const NodeInfo& info: solution){
        cout << info.getId() << '\n';
    }
    cout << "\n";

}

void TSP::setGraph(const Graph<NodeInfo>& graph_) {
    this->graph = graph_;
}

void TSP::setIdToNode(const unordered_map<int, NodeInfo>& idToNode_) {
    this->idToNode = idToNode_;
}
