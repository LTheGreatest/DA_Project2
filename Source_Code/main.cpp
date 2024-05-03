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
    readNodes(DataSetSelection::MEDIUM, map, g,n);
    return 0;
}
