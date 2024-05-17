//
// Created by lucas on 04/05/2024.
//

#include "TSP.h"
#include <chrono>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;
/**
 * @file TSP.cpp
 * @brief Implementation of class TSP.
 */


// ========================================================== Getters =================================================================================
/** Gets the if to node info unordered map.
 * Complexity: O(1)
 * @return Map with the id and node information
 */
unordered_map<int, NodeInfo> TSP::getIdToNode() const{
    return idToNode;
}

/**
 *  Gets the graph.
 *  Complexity: O(1).
 * @return Graph
 */
Graph<NodeInfo> TSP::getGraph() const{
    return graph;
}

// ========================================================= Setters ==================================================================================
/**
 * Sets a new graph.
 * Complexity: O(1).
 * @param graph_ The new graph
 */
void TSP::setGraph(const Graph<NodeInfo>& graph_) {
    this->graph = graph_;
}

/**
 * Sets the id to node map to a new one.
 * Complexity: O(1).
 * @param idToNode_ The new map
 */
void TSP::setIdToNode(const unordered_map<int, NodeInfo>& idToNode_) {
    this->idToNode = idToNode_;
}

// ===================================================== DISPLAY FUNCTIONS ======================================================================
/**
 * Displays the results obtained by the algorithms.
 * Complexity: O(n) where n is the number of vertexes.
 * @param minWeight The min weight found in the solution
 * @param solution The solution found
 * @param time The execution time of the algorithm
 */
void TSP::displayPathFound(double minWeight, const vector<NodeInfo>& solution, std::chrono::duration<double> time) const{

    cout << "Cost: " << minWeight << "\n";
    cout << "Time: " << time.count() << '\n';

    for(const NodeInfo& info: solution){
        cout << info.getId() << '\n';
    }
    cout << "\n";

}

/**
 * Displays a error message to the user
 * @param error error number
 */
void TSP::displayNoSolution(int error) {
    switch (error) {
        case 1:
            cout << "That vertex does not exist" << "\n";
            break;
        case 2:
            cout << "Solution starting with that vertex is impossible" <<"\n";
            break;
        default:
            cout<<"error"<<"\n";
            break;
    }
}

// ================================================================== BACKTRACKING SOLUTION ==========================================================================
/**
 * DFS for seeking the best solution for the TSP problem.
 * Complexity: O(N!) where n is number os vertexes.
 * @param v Starting vertex.
 * @param currentWeight Current calculated weight
 * @param minWeight The minimum weight calculated
 * @param currentSol The current solution found
 * @param bestSol The best solution found
 * @param count Counts the number of iterations taken
 */
void TSP::backtrackingSolutionDFS(Vertex<NodeInfo> *v, double currentWeight, double *minWeight, vector<NodeInfo> currentSol, vector<NodeInfo> *bestSol, int count, int finalID) const{
    for(auto e: v->getAdj()){
        Vertex<NodeInfo> *w = e->getDest();


        if(currentWeight + e->getWeight() >= *minWeight){
            //this path isn't the solution
            continue;
        }

        if((size_t) count == graph.getVertexSet().size() && w->getInfo().getId() == finalID){
            //found a solution
            currentWeight += e->getWeight();
            currentSol.push_back(w->getInfo());

            if(currentWeight < *minWeight){
                //found a better solution
                *minWeight = currentWeight;
                *bestSol = currentSol;
            }
        }


        //if the node isn't visited continues the search with this node
        if(!w->isVisited() && w->getInfo().getId() != 0){
            w->setVisited(true);
            currentSol.push_back(w->getInfo());
            currentWeight += e->getWeight();
            backtrackingSolutionDFS(w,currentWeight, minWeight, currentSol, bestSol, count + 1, finalID);

            //eliminates the node from the solution for searching other solutions
            currentWeight -= e->getWeight();
            currentSol.erase(currentSol.end()--);
        }



    }

    v->setVisited(false);
}

/**
 * Calculates the backtracking solution for the TSP problem.
 * Complexity: O(N!) where n is number os vertexes.
 */
void TSP::backtrackingSolution(int id) const{
    auto clockStart= chrono::high_resolution_clock::now();
    //reset the Graph
    for(Vertex<NodeInfo> *v : graph.getVertexSet()){
        v->setVisited(false);
        v->setPath(nullptr);
        v->setProcesssing(false);
    }

    //create auxiliary data
    double currentWeight = 0;
    double minWeight = ULONG_LONG_MAX;
    NodeInfo info = idToNode.find(id)->second; //get the starting node info
    Vertex<NodeInfo> *start = graph.findVertex(info); //find the starting node in the graph
    vector<NodeInfo> currentSol {start->getInfo()};
    vector<NodeInfo> bestSol;


    //executes the backtracking search
    backtrackingSolutionDFS(start, currentWeight, &minWeight, currentSol, &bestSol, 1, id);

    auto clockEnd= chrono::high_resolution_clock::now();

    auto duration = clockEnd - clockStart;
    //displays the results
    displayPathFound(minWeight, bestSol, duration);
}




// ========================================================= TRIANGULAR APPROXIMATION =============================================================================

/**
 * Gets the pre-order-walk of the prim algorithm.
 * Complexity: O(E * log(V)) where E is the number of edges and V is the number of vertexes
 * @param v origin vertex
 * @param g graph
 * @return pre-order-walk of the prim algorithm
 */
vector<Vertex<NodeInfo> * > getPrimMst(Vertex<NodeInfo> *v,Graph<NodeInfo> &g){
    vector<Vertex<NodeInfo> * > mst;
    if (g.getVertexSet().empty()) {
        return {};
    }

    for(auto s : g.getVertexSet()) {
        s->setDist(ULONG_LONG_MAX); // Set distance to infinity
        s->setPath(nullptr); // Set path to null
        s->setVisited(false); // Mark as not visited
    }

    // Select the first vertex as the starting point
    v->setDist(0); // Set distance of the starting vertex to 0

    // Priority queue to store vertices based on their distances
    MutablePriorityQueue<Vertex<NodeInfo>> q;
    q.insert(v);

    // Main loop for the Prim's algorithm
    while(!q.empty()) {
        // Extract the vertex with the minimum distance from the priority queue
        auto a = q.extractMin();
        a->setVisited(true); // Mark the vertex as visited
        mst.push_back(a);

        // Iterate through the adjacent edges of the current vertex
        for(auto &e : a->getAdj()) {
            Vertex<NodeInfo>* w = e->getDest(); // Get the destination vertex of the edge

            // Check if the destination vertex is not visited
            if (!w->isVisited()) {
                auto oldDist = w->getDist(); // Get the current distance of the destination vertex

                // Check if the weight of the edge is less than the current distance of the destination vertex
                if(e->getWeight() < oldDist) {
                    w->setDist(e->getWeight()); // Update the distance of the destination vertex
                    w->setPath(e); // Update the path to the current edge

                    // If the destination vertex had infinite distance, insert it into the priority queue
                    if (oldDist == ULONG_LONG_MAX) {
                        q.insert(w);
                    }

                    // If the destination vertex had finite distance, decrease its key in the priority queue
                    else {
                        q.decreaseKey(w);
                    }
                }
            }
        }

    }
    // Return the set of vertices after the Prim's algorithm completes
    return mst;
}

/**
 * Calculates the distance between two coordinates using the haversine formula.
 * Complexity: O(log(n)) because of the pow function.
 * @param lat1 first latitude
 * @param lon1 first longitude
 * @param lat2 first latitude
 * @param lon2 first longitude
 * @return distance between the two coordinates
 */
double haversine(double lat1, double lon1,double lat2, double lon2){
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;
    // apply formula
    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c * 1000;
}

/**
 * Finds a edge in the graph.
 * Complexity: O(E) where E is the number of edges
 * @param first source vertex
 * @param second destination vertex
 * @return A pointer to the edge. If it doesn't exist, return nullptr
 */
Edge<NodeInfo> * findEdge(Vertex<NodeInfo> * first,Vertex<NodeInfo> * second){
    for (auto e : first->getAdj()){
        if (e->getDest()->getInfo().getId() == second->getInfo().getId()) return e;
    }
    return nullptr;
}

/**
 * Calculates the triangular approximation solution for the TSP problem.
 * Complexity: O(v * E) where V is the number of vertexes and E is the number of edges
 */
void TSP::triangularAproxSolution() {

    auto clockStart= chrono::high_resolution_clock::now();

    NodeInfo info = idToNode.find(0)->second; //get the starting node info
    Vertex<NodeInfo> *v = graph.findVertex(info);

    vector<Vertex<NodeInfo> * > mst_pre_order = getPrimMst(v,graph);

    mst_pre_order.push_back(v);

    for (auto x : graph.getVertexSet()) x->setVisited(false);

    vector<NodeInfo> res;
    double cost = 0;

    for (auto i = 0; i<mst_pre_order.size() - 1 ; i++){
        Vertex<NodeInfo> * first = mst_pre_order[i];
        Vertex<NodeInfo> * second = mst_pre_order[i+1];

        res.push_back(first->getInfo());

        Edge<NodeInfo> * edge = findEdge(first,second);

        if(edge == nullptr){
            auto weight =  haversine(first->getInfo().getLatitude(), first->getInfo().getLongitude(),second->getInfo().getLatitude(),second->getInfo().getLongitude());
            cost += weight;
        }

        if (edge != nullptr) cost += edge->getWeight();
    }

    res.push_back(v->getInfo());


    auto clockEnd= chrono::high_resolution_clock::now();

    displayPathFound(cost, res, clockEnd-clockStart);
}

//========================================================== OTHER HEURISTIC =====================================================================================================
/**
 * Gets the edge with the smallest cost from a given vertex.
 * Complexity: O(E) where E is the number of outgoing edges of v.
 * @param v Vertex we are analysing
 * @return edge with the smallest cost
 */
Edge<NodeInfo>* getShortestEdge(Vertex<NodeInfo> *v){
    double minWeight = LONG_LONG_MAX;
    Edge<NodeInfo> * minEdge = nullptr;

    for(Edge<NodeInfo> *e: v->getAdj()){
        if((e->getWeight() < minWeight) && (!e->getDest()->isVisited())){
            minEdge = e;
            minWeight = e->getWeight();
        }
    }


    return minEdge;
}

/**
 * Gets the smallest cost for a edge between given vertex and the unvisited nodes (only used if there is not possible to find a feasible outgoing edge in a not fully connected graphs)
 * Complexity: O(V) where v is the number of unvisited edges.
 * @param v Vertex to analyse
 * @param g graph
 * @param unvisited unvisited nodes
 * @return smallest cost for a edge between given vertex and the unvisited nodes
 */
Edge<NodeInfo> getShortestEdgeUnvisited(Vertex<NodeInfo> *v,Graph<NodeInfo> &g, unordered_map<int, NodeInfo> unvisited){
    int minVertexIDX = INT_MAX;
    double minDist = LONG_LONG_MAX;

    for(pair<int, NodeInfo> intToNode: unvisited){
        NodeInfo inf1 = v->getInfo();
        NodeInfo inf2 = intToNode.second;
        double dist = haversine(inf1.getLatitude(), inf1.getLongitude(), inf2.getLatitude(), inf2.getLongitude());
        if(dist < minDist){
            minDist = dist;
            minVertexIDX = intToNode.first;
        }
    }
    NodeInfo destInf = unvisited.find(minVertexIDX)->second;
    Vertex<NodeInfo> *dest = g.findVertex(destInf);

    Edge<NodeInfo> e {v, dest, minDist};

    return e;
}

/**
 * Calculates the TSP using other heuristics.
 * Complexity: O(V*E) where V is the number of vertexes and E is the number of edges.
 */
void TSP::otherHeuristic() {
    auto clockStart= chrono::high_resolution_clock::now();

    //initialize the variables
    NodeInfo info = idToNode.find(0)->second; //get the starting node info
    Vertex<NodeInfo> *v = graph.findVertex(info);

    unordered_map<int, NodeInfo> unvisited = idToNode;
    vector<NodeInfo> res;
    res.push_back(v->getInfo());
    unvisited.erase(0);
    double cost = 0;


    //reset the graph
    for(auto s : graph.getVertexSet()) {
        s->setDist(ULONG_LONG_MAX); // Set distance to infinity
        s->setPath(nullptr); // Set path to null
        s->setVisited(false); // Mark as not visited
    }

    v->setVisited(true);

    //check for the closest neighbor and inserts it into the path
    while(res.size() < graph.getVertexSet().size()){
        Edge<NodeInfo> *e = getShortestEdge(v);

        //there is no possible path (calculate the dist for paths that are not connected and are not visited)
        if(e == nullptr){
           Edge<NodeInfo> e2 = getShortestEdgeUnvisited(v, graph, unvisited);
           cost += e2.getWeight();
           v = e2.getDest();
        }
        //a path was found
        else {
            cost += e->getWeight();
            v = e->getDest();
        }

        res.push_back(v->getInfo());
        v->setVisited(true);
        unvisited.erase(v->getInfo().getId());
    }

    //connects the final node of the tour to the edge
    NodeInfo infoFinal = res.back();
    Vertex<NodeInfo> *finalVertex = graph.findVertex(infoFinal);
    Vertex<NodeInfo> *firstVertex = graph.findVertex(info);

    Edge<NodeInfo> *e = findEdge(finalVertex, firstVertex);

    if(e == nullptr){
        cost += haversine(infoFinal.getLatitude(), infoFinal.getLongitude(), info.getLatitude(), info.getLongitude());
    }
    else{
        cost += e->getWeight();
    }

    res.push_back(info);

    auto clockEnd= chrono::high_resolution_clock::now();
    displayPathFound(cost, res, clockEnd-clockStart);
}

// ============================================ TSP REAL WORLD ================================================================================

/**
 * DFS for seeking the best solution for the TSP problem adapted for thr real World graphs.
 * Complexity: O(N!) where n is number os vertexes.
 * @param v current vertex
 * @param currentWeight Current path weight
 * @param minWeight minimum weight found
 * @param currentSol Current path solution
 * @param bestSol Best solution found
 * @param count Counts the number of vertexes visited
 * @param tries Counts the number of tries for each vertex
 * @param currentAttempt Current trie number
 * @param targetId The id of the vertex where we want to finnish the path.
 */
void TSP::backtrackingForRealWorld(Vertex<NodeInfo> *v, double currentWeight, double *minWeight,
                                   std::vector<NodeInfo> currentSol, std::vector<NodeInfo> *bestSol, int count,
                                   int tries,int &currentAttempt ,int targetId) {



    for(auto e: v->getAdj()){
        Vertex<NodeInfo> *w = e->getDest();


        if(currentWeight + e->getWeight() >= *minWeight){
            //this path isn't the solution
            continue;
        }

        if((size_t) count == graph.getVertexSet().size() && w->getInfo().getId() == targetId){
            //found a solution


            if(currentWeight + e->getWeight() < *minWeight){
                //found a better solution

                *minWeight = currentWeight;
                *bestSol = currentSol;
            }
        }


        //if the node isn't visited continues the search with this node
        if(!w->isVisited() && w->getInfo().getId() != targetId){
            w->setVisited(true);
            currentSol.push_back(w->getInfo());
            currentWeight += e->getWeight();
            currentAttempt++;
            backtrackingForRealWorld(w,currentWeight,minWeight,currentSol,bestSol,count+1,tries,currentAttempt,targetId);

            //eliminates the node from the solution for searching other solutions
            currentWeight -= e->getWeight();
            currentSol.erase(currentSol.end()--);
        }

        if(currentAttempt >= tries){

            continue;
        }



    }

    v->setVisited(false);
}

/**
 * Solves the TSP problem for incomplete graphs (first solution with backtracking).
 * Complexity: O(V*E*V!)
 * @param id Id of the root vertex
 */
void TSP::tspRealWord(int id) {
    auto clockStart= chrono::high_resolution_clock::now();

    //initialize variables
    auto infoItr = idToNode.find(id);
    if(infoItr == idToNode.end()){
        displayNoSolution(1);
        return;
    }
    NodeInfo info = infoItr->second;
    Vertex<NodeInfo> *v = graph.findVertex(info);
    vector<NodeInfo> res;
    res.push_back(v->getInfo());
    double minWeight = LONG_LONG_MAX;
    int currentAttempt = 0;
    vector<NodeInfo> bestSol;
    double cost = 0;

    //resets the graph auxiliary values
    for(auto s : graph.getVertexSet()){
        s->setVisited(false);
        s->setDist(ULONG_LONG_MAX); // Set distance to infinity
        s->setPath(nullptr);

    }

    v->setVisited(true);

    //main loop
    while(res.size() < graph.getVertexSet().size()){
        Edge<NodeInfo> *e = getShortestEdge(v);

        if(e == nullptr){
            //tries to find cycle or breaks
            v = graph.findVertex(res.back());
            backtrackingForRealWorld(v,cost,&minWeight,res,&bestSol,res.size(),10,currentAttempt,id);
            break;
        }
        else{
            cost += e->getWeight();
            v = e->getDest();
            v->setVisited(true);
        }
        res.push_back(v->getInfo());
    }

    //if we have found a solution in the backtracking we update the current solution
    if(!bestSol.empty()){
        res=bestSol;
        cost=minWeight;
    }

    //checks if the current solution is valid
    if(res.size() != graph.getVertexSet().size()){
        displayNoSolution(2);
        return;
    }

    //Checks if there is a path from the last vertex to the first one
    NodeInfo infoFinal = res.back();
    Vertex<NodeInfo> *finalVertex = graph.findVertex(infoFinal);
    Vertex<NodeInfo> *firstVertex = graph.findVertex(info);

    Edge<NodeInfo> *e = findEdge(firstVertex,finalVertex);

    if(e == nullptr ){
        displayNoSolution(2);
    }
    else{
        res.push_back(info);
        cost += e->getWeight();
        auto clockEnd= chrono::high_resolution_clock::now();
        displayPathFound(cost, res, clockEnd-clockStart);
    }



}

/**
 * Gets the shortest edge adapted for the real world graphs problem.
 * Complexity: O(E) where E is the number of outgoing edges of v.
 * @param v Vertex we are analysing
 * @return edge with the smallest cost
 */
Edge<NodeInfo>* getShortestEdgeRealWorld(Vertex<NodeInfo> *v){
    double minWeight = LONG_LONG_MAX;
    Edge<NodeInfo> * minEdge = nullptr;

    for(Edge<NodeInfo> *e: v->getAdj()){
        if((e->getWeight() < minWeight) && (!e->getDest()->isVisited()) && (!e->isSelected())){
            minEdge = e;
            minWeight = e->getWeight();
        }
    }


    return minEdge;
}

/**
 * Solves the TSP problem for incomplete graphs (second solution).
 * Complexity: O(V*E)
 * @param id Id of the root vertex
 */
void TSP::tspRealWord2(int id) {

    if(graph.getVertexSet().size() < 30){
        //smalls graphs can use the backtracking solution instead
        backtrackingSolution(id);
        return;
    }

    auto clockStart= chrono::high_resolution_clock::now();

    auto infoItr = idToNode.find(id);

    //initialize variables
    if(infoItr == idToNode.end()){
        displayNoSolution(1);
        return;
    }
    NodeInfo info = infoItr->second;
    Vertex<NodeInfo> *v = graph.findVertex(info);
    vector<NodeInfo> res;
    res.push_back(v->getInfo());
    double cost = 0;

    //resets the graph auxiliary values
    for(auto s : graph.getVertexSet()){
        s->setVisited(false);
        s->setDist(ULONG_LONG_MAX); // Set distance to infinity
        s->setPath(nullptr);
        for(auto e: s->getAdj()){
            e->setSelected(false);
        }

    }

    v->setVisited(true);

    //initializes the auxiliary variables to limit the complexity of the algorithm
    int maxTriesGoingBack = 5000;
    Edge<NodeInfo> *prevEdge;

    //main loop
    while(res.size() < graph.getVertexSet().size()){
        Edge<NodeInfo> *e = getShortestEdgeRealWorld(v);

        if(e == nullptr){
            //tries to find cycle or breaks
            maxTriesGoingBack--;
            if(maxTriesGoingBack == 0){
                //no solution found
                break;
            }
            v->setVisited(false);
            res.erase(res.end() - 1);

            if(res.empty()){
                break;
            }

            v = graph.findVertex(res.back());

            if(prevEdge != nullptr){
                prevEdge->setSelected(true);
            }

        }
        else if(!e->isSelected()){
            //if we haven't tried this edge we continue
            cost += e->getWeight();
            v = e->getDest();
            v->setVisited(true);
            res.push_back(v->getInfo());
            prevEdge = e;
        }
        else{
            continue;
        }

    }

    //checks if the current solution is valid
    if(res.size() != graph.getVertexSet().size()){
        displayNoSolution(2);
        return;
    }

    //Checks if there is a path from the last vertex to the first one
    NodeInfo infoFinal = res.back();
    Vertex<NodeInfo> *finalVertex = graph.findVertex(infoFinal);
    Vertex<NodeInfo> *firstVertex = graph.findVertex(info);

    Edge<NodeInfo> *e = findEdge(firstVertex,finalVertex);

    if(e == nullptr ){
        displayNoSolution(2);
    }
    else{
        res.push_back(info);
        cost += e->getWeight();
        auto clockEnd= chrono::high_resolution_clock::now();
        displayPathFound(cost, res, clockEnd-clockStart);
    }



}

