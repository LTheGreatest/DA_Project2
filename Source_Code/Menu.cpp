//
// Created by lucas on 05/05/2024.
//

#include "Menu.h"
#include "parse.h"

using namespace std;

/** @file Menu.cpp
 *  @brief Implementation of Menu class
 */

/** Asks for an option (integer) and the user needs to write the option on the keyboard.
 * Complexity: O(1) (worst case is O(n) were n is the time the user writes wrong options)
 * @param option Were the option value is going to be stored
 * @param min   Minimum value accepted
 * @param max   Maximum value accepted
 * @return  If there was not any error 0. Else 1.
 */
int Menu::inputCheck(int &option, int min, int max) {
    while(cout << "Enter your Option:" ){
        if(not(cin >> option)) {
            if (cin.rdstate() & (std::ios::badbit | std::ios::eofbit)) {
                cout << "Aborted\n";
                return EXIT_FAILURE;
            }
            cout << "Please enter a valid Option (not an integer)\n";
            cin.clear();                            // clear the fail state
            // remove any lingering characters in the istream:
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if(option > max || option < min){
            cout << "Please enter a valid Option (integer out of range)\n";
            cin.clear();                            // clear the fail state
            // remove any lingering characters in the istream:
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else{
            //valid option inserted
            break;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * Main menu of the system.
 * Complexity: depends on the user choice of algorithm
 * @return 1 if an error occurred. 0 otherwise
 */
int Menu::mainMenu(){
    cout << "\nWELCOME TO THE TSP ALGORITHM ANALYSER SYSTEM\n\n";
    int s;
    while(true) {
        if (isSystemReset) {
            //when the system is reset or is started we need to select the data
            s = chooseDataset();
            if (s != 0) {
                cout << "Error found\n";
                return EXIT_FAILURE;
            }
            isSystemReset = false;
        }

        cout << "Please insert the number corresponding to the option you want to select\n\n";

        cout << "1.Backtracking solution\n";
        cout << "2.Triangular Approximation Heuristic\n";
        cout << "3.Other Heuristic\n";
        cout << "4.TSP in the Real World\n";
        cout << "5.TSP in the Real World other attempt at a solution\n";
        cout << "6.Change Dataset\n";
        cout << "7.EXIT\n\n";

        int option;

        s = inputCheck(option, 1, 7);
        if (s != 0) {
            cout << "Error found\n";
            return EXIT_FAILURE;
        }
        cout << '\n';

        switch (option) {
            case 1:
                s = backtracking();
                break;
            case 2:
                s = triangularAproximation();
                break;
            case 3:
                s = otherHeuristic();
                break;
            case 4:
                s = realWorld();

                break;
            case 5:
                s = realWorld2();
                break;
            case 6:
                isSystemReset = true;
                break;
            case 7:
                //exits the system
                cout << "Thank you for using our system. GOODBYE\n";
                return EXIT_SUCCESS;
            default:
                cout << "Error found\n";
                return EXIT_FAILURE;
        }

        if (s != 0) {
            cout << "Error found\n";
            return EXIT_FAILURE;
        }

    }
}

/**
 * Executes the backtracking algorithm.
 * @return 1 if an error occurred. 0 otherwise
 */
int Menu::backtracking() {
    tsp.backtrackingSolution(0);
    return 0;
}

/**
 * Executes the other heuristic algorithm.
 * @return 1 if an error occurred. 0 otherwise
 */
int Menu::otherHeuristic() {
    tsp.otherHeuristic();
    return 0;
}

/**
 * Executes the other triangular approximation algorithm.
 * @return 1 if an error occurred. 0 otherwise
 */
int Menu::triangularAproximation() {
    tsp.triangularAproxSolution();
    return 0;
}

/**
 * Executes the  algorithm for the real world graphs.
 * @return 1 if an error occurred. 0 otherwise
 */
int Menu::realWorld() {
    cout<<"Please input the id of the vertex where you want to start\n";
    int id;
    int s = inputCheck(id,0,(int) tsp.getGraph().getVertexSet().size() - 1);
    if(s !=0){
        return 1;
    }
    tsp.tspRealWord(id);
    return 0;
}

/**
 * Executes the  algorithm for the real world graphs with a different solution.
 * @return 1 if an error occurred. 0 otherwise
 */
int Menu::realWorld2() {
    cout<<"Please input the id of the vertex where you want to start\n";
    int id;
    int s = inputCheck(id,0,(int) tsp.getGraph().getVertexSet().size() - 1);
    if(s !=0){
        return 1;
    }
    tsp.tspRealWord2(id);
    return 0;
}

/**
 * Menu used to select the dataset.
 * Complexity: O(n)
 * @return 1 if an error occurred. 0 otherwise
 */
int Menu::chooseDataset() {
    cout << "Please choose a dataset to use in the system\n";

    cout << "1.SMALL\n";
    cout << "2.MEDIUM\n";
    cout << "3.BIG\n";

    int option, s;

    s = inputCheck(option, 1, 3);
    if (s != 0) {
        cout << "Error found\n";
        return EXIT_FAILURE;
    }
    cout << '\n';

    switch (option) {
        case 1:
            s = smallDataset();
            break;
        case 2:
            s = mediumDataset();
            break;
        case 3:
            s = bigDataset();
            break;

        default:
            cout << "Error found\n";
            return EXIT_FAILURE;
    }

    if (s != 0) {
        cout << "Error found\n";
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * Menu used to select the graph in the small dataset.
 * Complexity: O(n)
 * @return 1 if an error occurred. 0 otherwise
 */
int Menu::smallDataset() {
    cout << "Choose the small dataset you want to use\n";

    cout << "1.shipping.csv\n";
    cout << "2.stadiums.csv\n";
    cout << "3.tourism.csv\n";

    unordered_map<int, NodeInfo> map;
    Graph<NodeInfo> g;

    int option, s;

    s = inputCheck(option, 1, 3);
    if (s != 0) {
        cout << "Error found\n";
        return EXIT_FAILURE;
    }
    cout << '\n';

    switch (option) {
        case 1:
            readNodesAndEdgesSmallGraphs(map, g,1);
            break;
        case 2:
            readNodesAndEdgesSmallGraphs(map, g,2);
            break;
        case 3:
            readNodesAndEdgesSmallGraphs(map, g,3);
            break;

        default:
            cout << "Error found\n";
            return EXIT_FAILURE;
    }

    tsp.setIdToNode(map);
    tsp.setGraph(g);

    return EXIT_SUCCESS;

}

/**
 * Menu used to select the graph in the medium dataset.
 * Complexity: O(n)
 * @return 1 if an error occurred. 0 otherwise
 */
int Menu::mediumDataset() {
    cout << "Choose the number of nodes to use in the medium dataset\n";

    cout << "1. 25 nodes\n";
    cout << "2. 50 nodes\n";
    cout << "3. 75 nodes\n";
    cout << "4. 100 nodes\n";
    cout << "5. 200 nodes\n";
    cout << "6. 300 nodes\n";
    cout << "7. 400 nodes\n";
    cout << "8. 500 nodes\n";
    cout << "9. 600 nodes\n";
    cout << "10. 700 nodes\n";
    cout << "11. 800 nodes\n";
    cout << "12. 900 nodes\n";

    unordered_map<int, NodeInfo> map;
    Graph<NodeInfo> g;

    int option, s;

    s = inputCheck(option, 1, 12);
    if (s != 0) {
        cout << "Error found\n";
        return EXIT_FAILURE;
    }
    cout << '\n';

    switch (option) {
        case 1:
            readNodes(DataSetSelection::MEDIUM, map, g, 1);
            readEdges(DataSetSelection::MEDIUM, map, g, 1);
            break;
        case 2:
            readNodes(DataSetSelection::MEDIUM, map, g, 2);
            readEdges(DataSetSelection::MEDIUM, map, g, 2);
            break;
        case 3:
            readNodes(DataSetSelection::MEDIUM, map, g, 3);
            readEdges(DataSetSelection::MEDIUM, map, g, 3);
            break;
        case 4:
            readNodes(DataSetSelection::MEDIUM, map, g, 4);
            readEdges(DataSetSelection::MEDIUM, map, g, 4);
            break;
        case 5:
            readNodes(DataSetSelection::MEDIUM, map, g, 5);
            readEdges(DataSetSelection::MEDIUM, map, g, 5);
            break;
        case 6:
            readNodes(DataSetSelection::MEDIUM, map, g, 6);
            readEdges(DataSetSelection::MEDIUM, map, g, 6);
            break;
        case 7:
            readNodes(DataSetSelection::MEDIUM, map, g, 7);
            readEdges(DataSetSelection::MEDIUM, map, g, 7);
            break;
        case 8:
            readNodes(DataSetSelection::MEDIUM, map, g, 8);
            readEdges(DataSetSelection::MEDIUM, map, g, 8);
            break;
        case 9:
            readNodes(DataSetSelection::MEDIUM, map, g, 9);
            readEdges(DataSetSelection::MEDIUM, map, g, 9);
            break;
        case 10:
            readNodes(DataSetSelection::MEDIUM, map, g, 10);
            readEdges(DataSetSelection::MEDIUM, map, g, 10);
            break;
        case 11:
            readNodes(DataSetSelection::MEDIUM, map, g, 11);
            readEdges(DataSetSelection::MEDIUM, map, g, 11);
            break;
        case 12:
            readNodes(DataSetSelection::MEDIUM, map, g, 12);
            readEdges(DataSetSelection::MEDIUM, map, g, 12);
            break;

        default:
            cout << "Error found\n";
            return EXIT_FAILURE;
    }

    tsp.setIdToNode(map);
    tsp.setGraph(g);

    return EXIT_SUCCESS;

}

/**
 * Menu used to select the graph in the big dataset.
 * Complexity: O(n)
 * @return 1 if an error occurred. 0 otherwise
 */
int Menu::bigDataset() {
    cout << "Choose the Big graph (Real World) you want to use\n";

    cout << "1.Graph 1\n";
    cout << "2.Graph 2\n";
    cout << "3.Graph 3\n";

    unordered_map<int, NodeInfo> map;
    Graph<NodeInfo> g;

    int option, s;

    s = inputCheck(option, 1, 3);
    if (s != 0) {
        cout << "Error found\n";
        return EXIT_FAILURE;
    }
    cout << '\n';

    switch (option) {
        case 1:
            readNodes(DataSetSelection::BIG, map, g, 1);
            readEdges(DataSetSelection::BIG, map, g,1);
            break;
        case 2:
            readNodes(DataSetSelection::BIG, map, g, 2);
            readEdges(DataSetSelection::BIG, map, g, 2);
            break;
        case 3:
            readNodes(DataSetSelection::BIG, map, g, 3);
            readEdges(DataSetSelection::BIG, map, g, 3);
            break;
        default:
            cout << "Error found\n";
            return EXIT_FAILURE;

    }

    tsp.setIdToNode(map);
    tsp.setGraph(g);

    return EXIT_SUCCESS;
}