/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

     //if it is tie, break it using Point's operator <.
     if(first[curDim] == second[curDim]){
       if(first < second) {return true;}
       else {return false;}
     }

    //check between first and second value on given dimension
    //and return true if frst < sec.
    if(first[curDim] < second[curDim]) {return true;}
    else {return false;}

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

     //reset distance(=0) from target to potential and currentBest.
     double potential_sum = 0, current_sum = 0;

     //calculating the distance from target to potential and currentBest.
     for(double i=0; i< Dim; i++){
        //potential_sum += pow(potential[i]-target[i],2);
        //current_sum += pow(currentBest[i]-target[i],2);
        potential_sum += (potential[i]-target[i]) * (potential[i]-target[i]) ;
        current_sum += (currentBest[i]-target[i]) * (currentBest[i]-target[i]) ;
     }

     //if the distances are same, return true if current is bigger than potential.
     if(potential_sum == current_sum){
       if(potential < currentBest) {return true;}
       else {return false;}
    }

    //return true, if potential distance is smaller than current.
    else{
      if(potential_sum < current_sum) {return true;}
      else {return false;}
    }

}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

     //initialize theArray and root.
     theArray = newPoints;
    //  if (newPoints.size() == 1) return;
     root = buildKDTree(theArray, 0, newPoints.size()-1, 0);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */

   //copy constructor: copy variables.
   theArray = other.theArray;
   root = buildKDTree(other.theArray, 0, other.theArray.size()-1, 0);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */

   //assignment operator:
   if(this != &rhs){
      treeDestroy(this);
      theArray = rhs.theArray;
      root = buildKDTree(rhs.theArray, 0, rhs.theArray.size()-1, 0);
    }
   return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   //tree destructor.
    treeDestroy(root);
    root = nullptr;
}

template <int Dim>
void KDTree<Dim>:: treeDestroy(KDTreeNode * node){
  //helper function : destroy tree.
  if(node != NULL){
    treeDestroy(node->left);
    treeDestroy(node->right);
    delete node;
  }
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
     //helper functions to implement this function.
    return helper_findNearest(query, root, 0);

}

template <int Dim>
Point<Dim> KDTree<Dim>::helper_findNearest(const Point<Dim>& query, KDTreeNode* theNode, int dimension) const {
    //Purpose : Finds the closest point to the parameter point in the KDTree.
    // calculates the distance between target and currentBest node
    Point<Dim> currentBest, potential;

    // return theNode, if leaves.
    if (!theNode->left && !theNode->right) {return theNode->point;}

    // going left or right depending on 'smallerDimval'
    if(smallerDimVal(query, theNode->point, dimension % Dim)) {
        if(theNode->left != NULL){
          currentBest = helper_findNearest(query, theNode->left, dimension + 1);
        }
    }
    else {
        if (theNode->right != NULL){
          currentBest = helper_findNearest(query, theNode->right, dimension + 1);
        }
    }

    // replace if theNode is nearer than currentBest.
    if (shouldReplace(query, currentBest, theNode->point) == true){
        currentBest = theNode->point;
    }

    //find potential, if other theNode can be nearer.
    if(smallerDimVal(query, theNode->point, dimension % Dim)) {
        double tempo1 = ( theNode->point[dimension%Dim] - query[dimension%Dim]) * ( theNode->point[dimension%Dim] - query[dimension%Dim]);
        double tempo2 =0;
        for(double i = 0; i< Dim; i++){
          tempo2 += (query[i]-currentBest[i]) * (query[i]-currentBest[i]);
        }

        if (theNode->right != NULL && tempo1 <= tempo2) {
            potential = helper_findNearest(query, theNode->right, dimension + 1);
        }
        else{
          return currentBest;
        }

    }
    else {
        double tempo3 = ( theNode->point[dimension%Dim] - query[dimension%Dim]) * ( theNode->point[dimension%Dim] - query[dimension%Dim]);
        double tempo4 =0;
        for(double i = 0; i< Dim; i++){
          tempo4 += (query[i]-currentBest[i]) * (query[i]-currentBest[i]);
        }
        if (theNode->left != NULL && tempo3 <= tempo4) {
            potential = helper_findNearest(query, theNode->left, dimension + 1);
        }
        else{
          return currentBest;
        }

    }
    //if potential is nearer than currentBest, then replace.
    if (shouldReplace(query, currentBest, potential)){
        currentBest = potential;
    }

    return currentBest;
}

/*
buildKDTree functions purpose : literally build a KDTree.
when left > right , return null. (the base case.)
create new node that carrys theArray[median] and spread to left and then right.
Used recursive method () parameter : left, right, and dimensions gets changed.
*/
template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::buildKDTree(vector<Point<Dim>>&theArray, int left, int right, int dimension)
{
  //(the base case) if left > right, return nullptr;
  if(left > right) {return NULL;}

  double median = floor((left + right)/2);
  quick_select(theArray, left, right, median, dimension);

  //create new node that carrys theArray[median] and spread to left and then right.
  KDTreeNode *temp = new KDTreeNode(theArray[median]);

  //Used recursive method () parameter : left, right, and dimensions gets changed.
  temp->left = buildKDTree(theArray, left, median-1, (dimension+1)%Dim);
  temp->right = buildKDTree(theArray, median+1, right, (dimension+1)%Dim);
  return temp;

}

/*
quick_select Function:
- start with select (0,n,k)
- put dimension'th smallest element in dimension'th position
- partition around kth elemnt.

 Perform a Binary search for the kth element.
 - take a guess at the elements
 - check your gueses (using partition)
 - if wrong try again on one of the two partitions.
 **is a selection algorithm to find the k-th smallest element in an unordered list.
*/
template <int Dim>
void KDTree<Dim>::quick_select(vector<Point<Dim>>& theArray, int left, int right, int median, int dimension)
{
  if (left >= right) {return;}

  //create pivotIndex at median (take a guess).
  double pivotIndex = partition(theArray, left, right,  floor((left + right)/2), dimension);

  //if wrong, adjust little bit to the median.
  if(median > pivotIndex) { quick_select(theArray, pivotIndex+1, right, median, dimension);}
  else if (median < pivotIndex) { quick_select(theArray, left, pivotIndex-1, median, dimension);}

}

/*
Partition Funcion:
- pull element at pivot index from array.
- put smaller elements on left.
- put larger elements on right.
- replace pivot element.
*/
template <int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& theArray, int left, int right, int pivotIndex, int dimension){

  //pull element at pivot index from array.
  Point<Dim> data_ = theArray[pivotIndex];
  double count = left;

  // Point<Dim> temp = theArray[pivotIndex];
  // theArray[pivotIndex] = theArray[right];
  // theArray[right] = temp;
  swap(theArray[pivotIndex], theArray[right]);

  //- put smaller elements on left.
  //- put larger elements on right.
  for(double i = left; i < right; i++){
    if (smallerDimVal(theArray[i], data_, dimension)==true) {
        swap(theArray[count], theArray[i]);
        count++;
    }
  }

  // Point<Dim> temp3 = theArray[right];
  // theArray[right] = theArray[count];
  // theArray[count] = temp3;
  swap(theArray[right], theArray[count]);
  return count;
}
