//
// Created by lucas on 05/05/2024.
//

#ifndef PROJECT2_MENU_H
#define PROJECT2_MENU_H


#include "TSP.h"

/**
 * @file Menu.h
 * @brief Definition of class Menu.
 *
 * \class Menu
 * Where are preformed functions related to the user interface(menus).
 * Stores a WaterSupplySystem object.
 */
class Menu {
public:
    int mainMenu();
    int backtracking();
    int triangularAproximation();
    int otherHeuristic();
    int realWorld();


    //choose the dataset
    int chooseDataset();
    int smallDataset();
    int mediumDataset();
    int bigDataset();

    //auxiliary function
    int inputCheck(int &option, int min, int max);

private:
    TSP tsp;
    bool isSystemReset;
};


#endif //PROJECT2_MENU_H
