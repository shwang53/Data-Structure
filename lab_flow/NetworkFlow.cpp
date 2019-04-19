/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  vector<Edge> tempEdge = g_.getEdges();

  for(auto it = tempEdge.begin(); it != tempEdge.end(); it++){

    residual_.insertEdge((*it).dest, (*it).source);
    residual_.insertEdge((*it).source, (*it).dest);
    residual_.setEdgeWeight((*it).dest, (*it).source, 0);
    residual_.setEdgeWeight((*it).source, (*it).dest, (*it).getWeight());


    flow_.insertEdge((*it).source, (*it).dest);
    flow_.setEdgeWeight((*it).source, (*it).dest, 0);
  }
  
  maxFlow_ = 0;

}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @@params: source -- The starting (tempent) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   * @@params: visited -- A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @@params: source -- The starting (tempent) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @@params: path   -- The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  int cap = INT_MAX;

  for(size_t i =0; i < path.size()-1; i++){

    int temp = residual_.getEdgeWeight(path[i], path[i+1]);

    cap = (cap>temp) ? temp : cap;

  }

  return cap;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @@outputs: The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  vector<Vertex> temp;
  vector<Vertex> tempAdj = flow_.getAdjacent(source_);

  while(findAugmentingPath(source_, sink_, temp) == true){

    size_t pathCap = pathCapacity(temp);

    for(size_t i = 0; i < temp.size()-1; i++){

      bool check = flow_.edgeExists(temp[i], temp[i+1]);

      if(check == false){
        flow_.setEdgeWeight(temp[i+1], temp[i], flow_.getEdgeWeight(temp[i+1], temp[i]) - pathCap);

      }

      if (check == true){
        flow_.setEdgeWeight(temp[i], temp[i+1], flow_.getEdgeWeight(temp[i], temp[i+1]) + pathCap);
      }

      residual_.setEdgeWeight(temp[i], temp[i+1], residual_.getEdgeWeight(temp[i], temp[i+1]) - pathCap);
      residual_.setEdgeWeight(temp[i+1], temp[i], residual_.getEdgeWeight(temp[i+1], temp[i]) + pathCap);
    }

  }


  while(tempAdj.empty() == false){
   int tempo = flow_.getEdgeWeight(source_,tempAdj.back());
    maxFlow_ += tempo;
    tempAdj.pop_back();
  }

  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
