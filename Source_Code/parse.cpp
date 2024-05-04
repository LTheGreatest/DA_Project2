//
// Created by Pedro on 5/3/2024.
//

#include "DataSelection.h"
#include <iostream>
#include "parse.h"
#include <fstream>
#include <sstream>
using namespace std;
/**
 * Used to select the path to the desired dataset.
 * Complexity: O(1)
 * @param dataset Which dataset we want (Small/Medium/Big)
 * @param filepath Path to the file
 */
void selectDataSet(DataSetSelection dataset, std::string *filepath) {
    switch (dataset) {
        case DataSetSelection::SMALL:
            *filepath = "../Dataset/Toy-Graphs";
            break;
        case DataSetSelection::MEDIUM:
            *filepath = "../Dataset/Extra_Fully_Connected_Graphs";
            break;
        case DataSetSelection::BIG:
            *filepath = "../Dataset/Real-World Graphs";
            break;
    }
}

void selectSmallGraph(int n, std::string *filepath){
    switch (n) {
        case 1:
            *filepath += "/shipping.csv";
            break;
        case 2:
            *filepath += "/stadiums.csv";
            break;
        case 3:
            *filepath += "/tourism.csv";
            break;
    }
}

int selectMediumGraph(int n, std::string *filepath){
    switch (n) {
        case 1:
            *filepath += "/edges_25.csv";
            return 25;
        case 2:
            *filepath += "/edges_50.csv";
            return 50;
        case 3:
            *filepath += "/edges_75.csv";
            return 75;
        case 4:
            *filepath += "/edges_100.csv";
            return 100;
        case 5:
            *filepath += "/edges_200.csv";
            return 200;
        case 6:
            *filepath += "/edges_300.csv";
            return 300;
        case 7:
            *filepath += "/edges_400.csv";
            return 400;
        case 8:
            *filepath += "/edges_500.csv";
            return 500;
        case 9:
            *filepath += "/edges_600.csv";
            return 600;
        case 10:
            *filepath += "/edges_700.csv";
            return 700;
        case 11:
            *filepath += "/edges_800.csv";
            return 800;
        case 12:
            *filepath += "/edges_900.csv";
            return 900;
    }
    return -1;
}

void selectBigGraph(int n, std::string *filepath) {
    switch (n) {
        case 1:
            *filepath += "/graph1";
            break;
        case 2:
            *filepath += "/graph2";
            break;
        case 3:
            *filepath += "/graph3";
            break;
    }
}

void readNodes(DataSetSelection dataSetSelection, std::unordered_map<int, NodeInfo> &idToInfo, Graph<NodeInfo> &graph, int n){
    int numbOfNodes = 10000; //reads all the nodes
    string filepath;
    switch (dataSetSelection) {
        case DataSetSelection::SMALL :
            readNodesAndEdgesSmallGraphs(idToInfo,graph,n);
            return;
        case DataSetSelection::MEDIUM :
            selectDataSet(DataSetSelection::MEDIUM, &filepath);
            numbOfNodes =  selectMediumGraph(n, &filepath);
            filepath = "../Dataset/Extra_Fully_Connected_Graphs/nodes.csv";
            cout << filepath;
            break;
        case DataSetSelection::BIG:
            selectDataSet(DataSetSelection::BIG, &filepath);
            filepath += "/nodes.csv";
    }

    ifstream file(filepath);
    if(!file.is_open()){
        cerr << "Error: Unable to open the file." << '\n';
    }

    string line;

    getline(file,line); //header line

    int id;
    double latitude, longitude;

    while(getline(file,line) && numbOfNodes > 0) {
        numbOfNodes--;

        //get id
        size_t it = line.find_first_of(',');
        id = stoi(line.substr(0,it));
        line = line.substr(it + 1);

        //get longitude
        it = line.find_first_of(',');
        longitude = stod(line.substr(0,it));
        line = line.substr(it + 1);

        //get latitude
        latitude = stod(line);

        //create the new node info
        NodeInfo info {id, "",longitude, latitude};

        //insert the new node in the hashmap and into the graph
        idToInfo.emplace(id,info);
        graph.addVertex(info);
    }


}

void readEdges(DataSetSelection dataSetSelection,std::unordered_map<int, NodeInfo> &idToInfo, Graph<NodeInfo> &graph, int n){
    string filepath;
    switch (dataSetSelection) {
        case DataSetSelection::SMALL :
            return;
        case DataSetSelection::MEDIUM :
            selectDataSet(DataSetSelection::MEDIUM, &filepath);
            selectMediumGraph(n, &filepath);
            cout << filepath;
            break;
        case DataSetSelection::BIG:
            selectDataSet(DataSetSelection::BIG, &filepath);
            filepath += "/edges.csv";
    }

    ifstream file(filepath);
    if(!file.is_open()){
        cerr << "Error: Unable to open the file." << '\n';
    }

    string line;

    if (dataSetSelection != DataSetSelection::MEDIUM) getline(file,line); //header line

    int origID, destID;
    double distance;

    while(getline(file,line)){

        //get origID
        size_t it = line.find_first_of(',');
        origID = stoi(line.substr(0,it));
        line = line.substr(it+1);

        //get destID
        it = line.find_first_of(',');
        destID = stoi(line.substr(0,it));
        line = line.substr(it+1);

        //get distance
        it = line.find_first_of(',');
        distance = stod(line.substr(0,it));

        //add Edge to the graph
        graph.addEdge(idToInfo[origID],idToInfo[destID],distance);
    }

}

void readNodesAndEdgesSmallGraphs(std::unordered_map<int, NodeInfo> &idToInfo, Graph<NodeInfo> &graph, int n){
    string filepath;

    //Select small graph
    selectDataSet(DataSetSelection::SMALL, &filepath);
    selectSmallGraph(n,&filepath);

    ifstream file(filepath);
    if(!file.is_open()){
        cerr << "Error: Unable to open the file." << '\n';
    }

    string line;

    int origID, destID;
    double distance;
    bool hasLabels = 0;
    string labelOrig;
    string labelDest;

    getline(file,line); //header line

    if (line.size() > 24) hasLabels = 1;

    while(getline(file,line)) {

        //get origID
        size_t it = line.find_first_of(',');
        origID = stoi(line.substr(0,it));
        line = line.substr(it+1);

        //get destID
        it = line.find_first_of(',');
        destID = stoi(line.substr(0,it));
        line = line.substr(it+1);

        //get distance
        it = line.find_first_of(',');
        distance = stod(line.substr(0,it));

        if (hasLabels){

            line = line.substr(it+1);

            //get LabelOrigin
            it = line.find_first_of(',');
            labelOrig = line.substr(0,it);
            line = line.substr(it+1);

            //get LabelDest
            it = line.find_first_of(',');
            labelDest = line.substr(0,it);

        }

        //create the new node info
        NodeInfo origInfo {origID, labelOrig};
        NodeInfo destInfo {destID, labelDest};

        //insert the new node in the hashmap and into the graph
        idToInfo.emplace(origID,origInfo);
        idToInfo.emplace(destID,destInfo);
        graph.addVertex(origInfo);
        graph.addVertex(destInfo);

        //add Edge to the graph
        graph.addEdge(origInfo,destInfo,distance);
    }
}


