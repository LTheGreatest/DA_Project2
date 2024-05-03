//
// Created by lucas on 03/05/2024.
//
#include <iostream>
#include "graph.h"

int main(){
    Graph<NodeInfo> g;
    NodeInfo node(1);
    NodeInfo node2(2);
    g.addVertex(node);
    g.addVertex(node2);
    Vertex<NodeInfo> *v = g.findVertex(node2);
    std::cout << v->getInfo().getId();
    return 0;
}
