#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <limits.h>

int max_neighbours;

// A tuple
struct Tuple
{
	int cost;
	int to;
};

/*
A planet has three coordinates
in 3D space, x, y and z
*/
typedef struct
{
	int x;
	int y;
	int z;
} Planet;

/*
Calculate the absolute value
of an integer
*/
int abs(int a)
{
	if (a<0) {
		return -1*a; // If the number is less than zero, we invert it
	} else {
		return a;
	}

}

/*
Find the smallest of two integers
*/
int min(int a, int b)
{
	if (a<b)
	{
		return a;
	} else {
		return b;
	}

}

/*
Calculate the cost of building
a teleporter between two planets
*/
int calculate_cost(Planet from, Planet to)
{

	return min(min(abs(from.x-to.x),abs(from.y-to.y)),abs(from.z-to.z));

}

/*
See if an array of length size contains value
*/
int contains(int size, int array[], int value){
  for (int i = 0; i < size; i++){
    if (array[i]==value) return 0;
  }
  return -1;
}

/*
Given a matrix and a source node,
find the "cheapest" edge eminating
from the source node to a node not
already visited
*/

struct Tuple find_minimal_edge(int from, int size, int **g, int *visited){

	struct Tuple minimum;

	int min = INT_MAX;

	for (int i = 0; i < size; i++){
		if(g[from][i]>=0&&g[from][i]<min&&contains(size, visited, i)==-1){// Distance from a node to itself is -1
			min = g[from][i];
			minimum.cost = min;
			minimum.to = i;
		}
	}
//  fprintf(stderr, "Minimal edge is returning cost:%d to:%d\n", minimum.cost, minimum.to);
	return minimum;
}

/*
If an entry in the array is -1, we have not visited every node
*/
int unvisited(int size, int *array){

  for(int i = 0; i < size; i++){
    if (array[i]==-1) return 0;
  }

  return -1;
}

/*
Print an array of integers
*/
void printArray(int size, int *array){
  for (int i = 0; i < size; i++){
//    fprintf(stderr, "%d,", array[i]);
  }
//  fprintf(stderr, "%s\n", "\n");
}


/*
Calculate the minimum spanning tree
using prims algorithm, return the total
value of the tree
*/

int prim(int size, int **g)
{
  int totalCost = 0;
  int seen = 0; // This variable will hold the number of planets we have visited so far
	//int visited[max_neighbours];
	int *visited = malloc(max_neighbours*sizeof(int));
  memset( visited, -1, max_neighbours*sizeof(int) ); // all elements to -1
  printArray(size, visited);
	int startNode = 0; // select the first node
	visited[seen] = startNode; // The first unoccupied index will contain the value of the visited node
  seen ++;
	struct Tuple cost = find_minimal_edge(startNode, size, g, visited); // find minimal edge from start node
  visited[seen] = cost.to; // set the second node to visited
  totalCost = totalCost + cost.cost;
  seen ++;
//  fprintf(stderr, "First edge found, from %d to %d with cost %d, totalCost is now%d\n", startNode, cost.to, cost.cost, totalCost);
  int next = unvisited(size, visited); // see if there are still nodes that we have not visited
//  fprintf(stderr, "%s\n", "Unvisited nodes are: ");
  printArray(size, visited);
  while(next!=-1){//While there are still nodes that we have not visited
  //  fprintf(stderr, "Next is %d, doing another loop\n", next);
    int cheapest = INT_MAX;
    for (int i = 0; i < seen; i++){ // Find the cheapest edge from all visited planets
      //fprintf(stderr, "finding cheapest edge from %d\n", i);
      struct Tuple newCost = find_minimal_edge(visited[i], size, g, visited);
    //  fprintf(stderr, "cheapest edge is %d to %d with cost %d\n", i, newCost.to, newCost.cost);
      if(newCost.cost<cheapest&&contains(size, visited, newCost.to)==-1){
    //    fprintf(stderr, "New cheapest connection found from %d to %d, contains is:%d\n", i, newCost.to, contains(size, visited, newCost.to));
        int someCost = newCost.cost;
        int someTo = newCost.to;
        cost.cost = someCost; //save the cheapest edge
        cost.to = someTo;
      }
    }
    visited[seen] = cost.to;
    //fprintf(stderr, "Adding %d to seen\n", cost.to);
    seen ++;
  //  fprintf(stderr, "Adding %d to total cost %d = %d\n", cost.cost, totalCost, totalCost+cost.cost);
    totalCost = totalCost + cost.cost;
    //printArray(size, visited);
    next = unvisited(size, visited);
  }
	free(visited);
  return totalCost;

}

/*
Print incidency matrix to stderr
*/
int print_matrix(int size, int g[size][size])
{
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
		//	fprintf(stderr, "	%d	", g[i][j]);
		}
	//	fprintf(stderr, "\n");
	}
	return 0;
}

int kruskal(int size, int **g){
	Edge *edges = malloc((size*(size-1)/2)*sizeof(Edge));
	edges = sortEdges(g);
	for
	//find smallest edge for remaining edges
	//no cycle?
	//add to total cost
	//all nodes visited?
}

/*
To calculate the minimal cost of building teleporters
between all planets we add each planet as a node, in a graph.
We then create a complete graph where every node is connected
to every other node. The cost of the connection is the
cost of building a teleporter. Then we use Prims algorithm
to find the minimum spanning tree and use the cost of the tree
as the cost of connecting all n planets with n-1 teleporters.
*/
int main()
{
	//fprintf(stderr, "Starting program.\n");
	int num_planets;
	int x_temp;
	int y_temp;
	int z_temp;
	//fprintf(stderr, "Please type how many planets: ");
	scanf("%d",&num_planets); // read total number of planets
	max_neighbours = num_planets;
	//fprintf(stderr, "Number of planets: %d\n", num_planets);
	//Planet planets[num_planets];
	Planet *planets = malloc(num_planets*sizeof(Planet)); // create list of all planets
	//int g[num_planets][num_planets];

	// create cost matrix for teleporters between planets
	int **g;
	g = malloc(num_planets*sizeof(int *));
	for (int i = 0; i < num_planets; i++){
		g[i] = malloc(num_planets * sizeof(int));
	}

	for (int i = 0; i < num_planets; ++i) { // iterate over all planets, read data and add planet
		//fprintf(stderr, "Enter coordinates for planet %d\n", i);
		scanf("%d %d %d", &x_temp, &y_temp, &z_temp);
		planets[i].x = x_temp;
		planets[i].y = y_temp;
		planets[i].z = z_temp;
		//fprintf(stderr,"Read planet %d x:%d y:%d z:%d \n", i+1, planets[i].x, planets[i].y, planets[i].z);
	}

	int edge_count = (num_planets*(num_planets-1))/2; // The total number of edges needed to connect all vertices in a complete graph (n(n-1))/2
	//fprintf(stderr, "Will build %d edges\n", edge_count);

	for (int j = 0; j < num_planets; j++) { // Loop over the whole matrix and add calculated cost
		for (int h = 0; h < num_planets; h++) {
			if(h==j) { // The cost to connect to one self is -1
				g[h][j] = -1;
				g[j][h] = -1;
			} else {
				int weight = calculate_cost(planets[j],planets[h]);
				g[h][j] = weight;
				g[j][h] = weight;
				//addEdge(graph, j, h, weight);
			}
			//fprintf(stderr, "Built edge from %d %d %d to %d %d %d with cost %d\n", planets[j].x, planets[j].y, planets[j].z, planets[h].x, planets[h].y, planets[h].z, g[h][j]);
		}

	}

  fprintf(stderr, "%d\n", prim(num_planets, g));

	free(planets);
	free(g);

	return 0;
}
