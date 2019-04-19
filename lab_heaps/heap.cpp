
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    //return 0;
    return (currentIdx * 2 );
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    //return 0;
     return (currentIdx * 2 + 1);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    //return 0;
    return (currentIdx )/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    //return false;
    // if(_elems[leftChild(currentIdx)].empty() == false){
    //   return true;
    // }
    // else{return false;}
     return currentIdx * 2 < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority

    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);

    if(_elems.size()-1 < 2 * currentIdx +1){ return left; }

    if(higherPriority(_elems[left], _elems[right])){  return left; }

    else{return right;}

}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.

    if ( hasAChild(currentIdx) == false ) {
      return;
    }

    size_t min = maxPriorityChild(currentIdx);

    if (higherPriority(_elems[min], _elems[currentIdx])) {
      std::swap(_elems[min], _elems[currentIdx]);
      heapifyDown(min);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root()){
      return;
    }
    if (higherPriority(_elems[currentIdx], _elems[parent(currentIdx)])) {
        std::swap(_elems[currentIdx], _elems[parent(currentIdx)]);
        heapifyUp(parent(currentIdx));
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // @TODO Construct a heap using the buildHeap algorithm
    // _elems = elems;
    // for(int i = _elems.size()/2; i >= 0; i--) {
    //     heapifyDown(i);
    // }
    _elems.push_back(T());
    for(size_t i = 0; i < elems.size(); i++)
    {
      _elems.push_back(elems[i]);
    }
    for(size_t i = parent(_elems.size()-1); i >0 ; i--)
    {
      heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority

    if(empty()) { return T(); }

    T min = _elems[root()];
    size_t lastIdx = _elems.size() -1;
   _elems[root()] = _elems[lastIdx];
    _elems.pop_back();
   heapifyDown(root());
   return min;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    //return T();
     return _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    // _elems.push_back(elem);
    // int i = _elems.size() - 1;
    // while(i != 0 && _elems[parent(i)] > _elems[i]) {
    //     std::swap(_elems[i],_elems[parent(i)]);
    //     i = parent(i);
    // }
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    int tempIdx = idx + 1;

    if(_elems[tempIdx] == elem){
      return;
    }

    if(elem <= _elems[tempIdx]){
      _elems[tempIdx] = elem;
      heapifyUp(tempIdx);
    }

    else{
      _elems[tempIdx] = elem;
      heapifyDown(tempIdx);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty


    if(_elems.size() <= 1){
      return true;
    }else{
      return false;
    }
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
