//
//  androids.cpp
//  Spanning Tree
//
//  Created by Joel Kallin Kilman on 2017-06-11.
//  Copyright © 2017 Joel Kallin Kilman. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <map>
#include <stack>
#include <set>

using namespace std;

struct Planet {
        int x,y,z;
        int id;
};

struct Cost {
        int from, to;
        int value;
};

typedef struct {
    int a, b;
} Tuple;

int calculateCost(Planet* fst, Planet* snd){
        return std::min(std::min(abs(fst->x-snd->x),abs(fst->y-snd->y)),abs(fst->z-snd->z));
}

void printPlanets(std::vector<Planet*> planets){

        for(int i = 0; i < planets.size(); i++) {
                std::cout << "x:" << planets[i]->x << " y:" << planets[i]->y << " z:" << planets[i]->z << " id:" << planets[i]->id << std::endl;
        }
}

void printNeighbourGraph(std::vector< std::vector<Cost*> > neighbours){
        for(int i = 0; i < neighbours.size(); i++) {
          for(int j = 0; j < neighbours[i].size(); j++){
              std::cout << "from: " << neighbours[i][j]->from << " to: " << neighbours[i][j]->to << " cost: " << neighbours[i][j]->value << std::endl;
          }
        }
}

Tuple* minimumEdgeOfVertex(std::vector< std::vector<Cost*> >& neighbours, int vertex, std::set<int> visited){

  //std::cout << "Finding minimum edge of vertex: " << vertex << std::endl;

  int min = INT_MAX;

  int neighbour = -1;

    for(int i = 0; i < neighbours[vertex].size(); i++){
          //std::cout << "Neighbour: from->" << neighbours[vertex][i]->from << " to->" << neighbours[vertex][i]->to << std::endl;
          int value = neighbours[vertex][i]->value;
          //std::cout << "value: " << value << std::endl;
          if(value<min && visited.find(neighbours[vertex][i]->to) == visited.end()){
            min = value;
            neighbour = neighbours[vertex][i]->to;
            //std::cout << "found new min! vertex: " << neighbour << " value: " << min << std::endl;
          }
    }

    Tuple* tup = new Tuple();
    tup->a = neighbour;
    tup->b = min;

    return tup;
}

Tuple* findNearestNeighbour(std::vector< std::vector<Cost*> > neighbours, std::set<int> visited){

        int min = INT_MAX;

        int neighbour = -1;

        for (std::set<int>::iterator it=visited.begin(); it!=visited.end(); ++it) {
            Tuple* closestNeighbour = minimumEdgeOfVertex(neighbours, *it, visited);
            //std::cout << "closest neighbour is: " << closestNeighbour->a << " value: " << closestNeighbour->b << std::endl;
            if(closestNeighbour->b<min){
                min = closestNeighbour->b;
                neighbour = closestNeighbour->a;
                //std::cout << "new minimum node: " << neighbour << " cost: " << min << std::endl;
            }
        }

        Tuple* tup = new Tuple();
        tup->a = neighbour;
        tup->b = min;

        return tup;
}

void prim(std::vector< std::vector<Cost*> > neighbours){

        int treeCost = 0; // aggregate edge cost of tree

        std::set<int> unvisited; //unvisited nodes

        std::set<int> visited; //visited nodes

        for(int i = 1; i < neighbours.size(); i++){
            unvisited.insert(i); // initialize unvisited vertices
        }

        visited.insert(0);

        while(unvisited.size()>0){ // While we still have nodes that are not in the MST
            //std::cout << "size: " << unvisited.size() << std::endl;
            Tuple* nearestNeighbour = findNearestNeighbour(neighbours, visited); // find closest vertex to our set of visited nodes, should return the value?
            //std::cout << "nearest vertex: " << nearestNeighbour->a << " value: " << nearestNeighbour->b << std::endl;
            visited.insert(nearestNeighbour->a);
            //std::cout << "inserted: " << nearestNeighbour->a << std::endl;
            unvisited.erase(nearestNeighbour->a);
            //std::cout << "erased: " << nearestNeighbour->a << std::endl;
            treeCost+=nearestNeighbour->b;

        }

        std::cout << treeCost << std::endl;


}

int main(int argc, const char * argv[]) {


        int numOfPlanets;

        std::cin >> numOfPlanets;

        std::vector<Planet*> planets;

        std::vector<std::vector<Cost*> > neighbourGraph;

        for(int i = 0; i < numOfPlanets; i++) {
                Planet* tmp = new Planet;
                std::cin >> tmp->x >> tmp->y >> tmp->z;
                tmp->id = i;
                planets.push_back(tmp);
        }

        int edgeCount = (numOfPlanets*(numOfPlanets-1))/2; // The total number of edges needed to connect all vertices in a complete graph (n(n-1))/2

        for(int i = 0; i < numOfPlanets; i++) {
                std::vector<Cost*> v;
                for(int j = 0; j < numOfPlanets; j++) {
                        if(i!=j) {
                                Cost* tmp = new Cost;
                                tmp->from = planets.at(i)->id;
                                tmp->to = planets.at(j)->id;
                                tmp->value = calculateCost(planets[i], planets[j]);
                                v.push_back(tmp);
                        }
                }
                neighbourGraph.push_back(v);
        }

        //printNeighbourGraph(neighbourGraph);

        prim(neighbourGraph);

        for(int i = 0; i < numOfPlanets; i++) {
                Planet* planet = planets[i];
                delete planet;
        }

        for(int i = 0; i < neighbourGraph.size(); i++) {
                for(int j = 0; j < neighbourGraph[i].size(); j++) {
                        Cost* tmp = neighbourGraph[i].at(j);
                    //    cout << "deleting" << tmp->value << std::endl;
                        delete tmp;
                }
                //delete &neighbourGraph[i];
        }

        //delete &planets;
        //delete &neighbourGraph;

        return 0;
}
