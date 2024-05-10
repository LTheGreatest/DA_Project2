//
// Created by lucas on 03/05/2024.
//
#include <iostream>
#include "graph.h"
#include "parse.h"
#include "TSP.h"
#include "Menu.h"

/**
 * @file main.cpp
 * @brief This file contains the main function of the project.
 *
  * \mainpage Description
 * This project consists in a set of classes and functions that allow the user to solve the TSP problem for a set of provided datasets.
 * With this simple system, you can solve the problem using different algorithms and check the execution time for each of them.
 *
 * \subsection Instructions How to use
 * You will be asked to choose an option. All the options will appear on the screen with a number near them.
 * Then, just type the number corresponding to the option you want to execute.
 */

int main(){
    Menu menu;
    return menu.mainMenu();
}
