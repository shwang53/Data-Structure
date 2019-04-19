#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();

}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  int count = 0;

  for(auto edge : edgeList){
    if(edge.source() == v || edge.dest() == v){
      count ++;
    }
  }
  return count;
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & temp = *(new V(key));

  string str = temp.key();

  vertexMap.insert({str,temp});

  return temp;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2

  for(E_byRef edge : edgeList) {
    std::string check1 = edge.get().source().key();
    std::string check2 = edge.get().dest().key();

    if(check1 == key || check2 == key){
      removeEdge(edge.source(), edge.dest());
    }
  }

  vertexMap.erase(key);
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & temp = *(new E(v1, v2));
  edgeList.push_back(temp);

  return temp;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2

  // for(E_byRef edge : edgeList){
  //   std::string check1 = edge.get().source().key();
  //   std::string check2 = edge.get().dest().key();
  //
  //   if(check1 == key1 && check2 == key2){
  //     edgeList.erase(edge);
  //     return;
  //   }
  // }
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;


  for(auto edge : edgeList){
    std::string check1 = edge.get().source().key();
    std::string check2 = edge.get().dest().key();

    if(check1 == key ||  check2 == key){
      edges.push_back(edge);
    }
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  for(E_byRef edge : edgeList){
    std::string check1 = edge.get().source().key();
    std::string check2 = edge.get().dest().key();
    if(check1 == key1 && check2 == key2){
      return true;
    }
  }
  return false;
}
