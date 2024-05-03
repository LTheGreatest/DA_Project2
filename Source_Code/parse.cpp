//
// Created by Utilizador on 5/3/2024.
//

#include "DataSelection.h"
#include <iostream>

/**
 * Used to select the path to the desired dataset.
 * Complexity: O(1)
 * @param dataset Which dataset we want (Small/Medium/Big)
 * @param filepath Path to the file
 */

void selectDataSet(DataSetSelection dataset, std::string *filepath) {
    switch (dataset) {
        case DataSetSelection::SMALL:
            *filepath = "../DataSet/Toy-Graphs";
            break;
        case DataSetSelection::MEDIUM:
            *filepath = "../DataSet/ExtraFullyConnectedGraphs";
            break;
        case DataSetSelection::BIG:
            *filepath = "../DataSet/Real-World Graphs";
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

void selectMediumGraph(int n, std::string *filepath){
    switch (n) {
        case 1:
            *filepath += "/edges_25.csv";
            break;
        case 2:
            *filepath += "/edges_50.csv";
            break;
        case 3:
            *filepath += "/edges_75.csv";
            break;
        case 4:
            *filepath += "/edges_100.csv";
            break;
        case 5:
            *filepath += "/edges_200.csv";
            break;
        case 6:
            *filepath += "/edges_300.csv";
            break;
        case 7:
            *filepath += "/edges_400.csv";
            break;
        case 8:
            *filepath += "/edges_500.csv";
            break;
        case 9:
            *filepath += "/edges_600.csv";
            break;
        case 10:
            *filepath += "/edges_700.csv";
            break;
        case 11:
            *filepath += "/edges_800.csv";
            break;
        case 12:
            *filepath += "/edges_900.csv";
            break;
    }
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



