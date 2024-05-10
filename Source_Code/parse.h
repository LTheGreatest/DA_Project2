//
// Created by lucas on 03/05/2024.
//

#ifndef PROJECT2_PARSE_H
#define PROJECT2_PARSE_H

#include <string>
#include <unordered_map>
#include "DataSelection.h"
#include "NodeInfo.h"
#include "Graph.h"

/**
 * @file parse.h
 * @brief Definition of parse functions.
 */

void selectDataSet(DataSetSelection dataset, std::string *filepath);
void selectSmallGraph(int n, std::string *filepath);
int selectMediumGraph(int n, std::string *filepath);
void selectBigGraph(int n, std::string *filepath);
void readNodesAndEdgesSmallGraphs(std::unordered_map<int, NodeInfo> &idToInfo, Graph<NodeInfo> &graph, int n);
void readNodes(DataSetSelection dataSetSelection, std::unordered_map<int, NodeInfo> &idToInfo, Graph<NodeInfo> &graph, int n);
void readEdges(DataSetSelection dataSetSelection,std::unordered_map<int, NodeInfo> &idToInfo, Graph<NodeInfo> &graph, int n);
#endif //PROJECT2_PARSE_H
