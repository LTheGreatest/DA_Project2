//
// Created by lucas on 04/05/2024.
//

#ifndef PROJECT2_TSP_H
#define PROJECT2_TSP_H


#include "Graph.h"
#include <unordered_map>
#include <chrono>
/**
 * @file TSP.h
 * @brief Definition of class TSP.
 *
 * \class TSP
 * Where are stored the graph and the map from the ids to the vertexes.
 * Is also where the TSP algorithms are performed.
 */
class TSP {

    public:
    //Backtracking
    void backtrackingSolutionDFS(Vertex<NodeInfo> *v, double currentWeight, double *minWeight, std::vector<NodeInfo> currentSol, std::vector<NodeInfo> *bestSol, int count) const;
    void backtrackingSolution() const;

    //Triangular Approximation Heuristic
    void triangularAproxSolution();

    //Other heuristic
    void otherHeuristic();



    //Auxiliary
    void displayPathFound(double minWeight, const std::vector<NodeInfo>& solution, std::chrono::duration<double> time) const;

    //setters
    void setGraph(const Graph<NodeInfo>& graph);
    void setIdToNode(const std::unordered_map<int, NodeInfo>& idToNode);

    //getters
    std::unordered_map<int, NodeInfo> getIdToNode() const;
    Graph<NodeInfo> getGraph() const;


    private:
        std::unordered_map<int, NodeInfo> idToNode;
        Graph<NodeInfo> graph;
};


#endif //PROJECT2_TSP_H
