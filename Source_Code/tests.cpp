//
// Created by lucas on 04/05/2024.
//

#include <gtest/gtest.h>
#include "TSP.h"
#include "parse.h"

TEST(Backtracking, Backtracking_small_graph_3){
    Graph<NodeInfo> g;
    int n = 3;
    std::unordered_map<int, NodeInfo> map;
    readNodes(DataSetSelection::SMALL, map, g,n);
    readEdges(DataSetSelection::SMALL,map,g,n);

    NodeInfo info = map.find(0)->second;
    Vertex<NodeInfo> *start = g.findVertex(info);
    double currentWeight = 0;
    double minWeight = LONG_LONG_MAX;
    std::vector<NodeInfo> currentSol {start->getInfo()};
    std::vector<NodeInfo> bestSol;
    int count = 1;

    TSP tsp;
    tsp.setGraph(g);
    tsp.setIdToNode(map);

    tsp.backtrackingSolutionDFS(start, currentWeight, &minWeight, currentSol, &bestSol, count);

    EXPECT_EQ(minWeight, 2600);

}
