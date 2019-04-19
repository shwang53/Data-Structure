/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

#include <iostream>
/**
 * Returns a ListIterator with a position at the begininning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(tail_->next);
}

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <typename T>
List<T>::~List() {
  /// @todo Graded in MP3.1
    _destroy();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
    while(head_ != NULL){ //genius idea! yes
      ListNode * temp = head_;
      head_ = head_->next;
      delete temp;
      temp = NULL;
    }
    tail_ = NULL;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  // ListNode * temp = new ListNode(ndata);
  // temp->prev = NULL;
  // temp->next = NULL;
  // if(head_==NULL){
  //
  // //  head = temp;
  // //  temp->next =NULL;

  // length_++;
  // temp = NULL;

  // if(!this->empty()){
  //   ListNode* temp = new ListNode(ndata);
  //   head_->prev = temp;
  //   temp->next = head_;
  //   temp->prev = NULL;
  //   head_ = temp;
  // }
  // else{
  //   head_ = new ListNode(ndata);
  //   head_->next = NULL;
  //   head_->prev = NULL;
  //   tail_ = head_;
  // }
  // length_++;
  ListNode * temp = new ListNode(ndata);
  if(this->empty()){
    head_=temp;
    head_->next = NULL;
    head_->prev = NULL;
    tail_ = head_;
  }else{
    head_->prev = temp;
    temp->next = head_;
    temp->prev = NULL;
    head_ = temp;
  }
    length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if(this->empty()){
    ListNode * temp = new ListNode(ndata);
  //  head = temp;
  //  temp->next =NULL;
    head_ = temp;  // head_ is pointing temp;
    tail_ = head_; // what 'head_' is pointing is tail.
  }else {
    ListNode * temp = new ListNode(ndata);
    temp->next = NULL;
    temp->prev = tail_;
    tail_->next = temp;
    tail_ = temp;
  }
  length_++;
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
//  empty list or single node list stay the same.
  // if(startPoint == NULL || endPoint == NULL || startPoint == endPoint) {
  //   return;
  // }

  // ListNode * prev = NULL;
  // ListNode * curr = startPoint;
  // ListNode * next = NULL;
  //
  // while(curr != NULL){
  //     next = curr->next;
  //     curr->next = prev;
  //     prev = curr;
  //     curr = next;
  // }
  // startPoint = end ;
  // startPoint = prev;
  if(startPoint == NULL || endPoint == NULL || startPoint == endPoint)
  {return;}
  if (startPoint != endPoint) {
		ListNode * current  = startPoint;
		ListNode * after  = endPoint->next;
    ListNode * before = startPoint->prev;
		while (current != after) {
      ListNode* temp = current->prev;
      current->prev = current->next;
      current->next = temp;
			current = current->prev;
		}
    ListNode * stPoint = startPoint;
    ListNode * ePoint = endPoint;
		if (before == NULL) {
			ePoint->prev = NULL;
			head_ = ePoint;
		} else if(before != NULL) {
			before->next = ePoint;
			ePoint->prev = before;
		}
		if (after == NULL) {
			stPoint->next = NULL;
			tail_ = stPoint;
		} else if ( after != NULL) {
			after->prev = stPoint;
			stPoint->next = after;
		}
		startPoint = ePoint;
		endPoint = stPoint;
	}




}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1

  ListNode * start = head_;
  ListNode * end = head_;

  if((head_ == NULL || tail_ == NULL)) {return;}

  while(start != NULL) {
    end = start;
    for(int i=0; i<(n-1); i++) {
      if(end->next != NULL) {  end = end->next;  }
    }

    reverse(start,end);

    start = end->next;
  }
    // ListNode* current = head_;

    //    }
    //    endPoint = temp;
    //     //std::cout << remain << std::endl;
    //    reverse(startPoint, endPoint);
    //    startPoint = startPoint->next;
    //    temp = startPoint;
    //    remain = remain - n;
    //
    //   }
    //
    //   endPoint = tail_;
    //
    //   reverse(startPoint,endPoint);


  }



/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode * current = head_;
  ListNode * nexto = current->next;

 if((tail_ == NULL) || (head_ == NULL)) {return;}

 while((current->next != NULL)) {

   nexto = current->next;

   if(nexto->next != NULL) {
     current->next = nexto->next;
     nexto->prev = current;
   }
   tail_->next = nexto;
   nexto->prev = tail_;
   tail_ = nexto;
   tail_->next = NULL;
   current = current->next;
 }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <typename T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode * secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  if(splitPoint == 0){return start;}
  if (start == NULL){ return NULL;}
  for(int i = 0; i < splitPoint-1; i++) {  start = start->next; }
  ListNode*tempead = start->next;
  start->next = NULL;
  tempead->prev = NULL;
  return tempead;
  //return NULL;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
// template <typename T>
//  void List<T>::insertSorted(ListNode **head, ListNode *insert)const {
//  //   // your code here!
//
//    if( *head == NULL || (*head)->data >= insert->data){
//
//        insert->next = *head;
//        *head = insert;
//
//    }else{
//
//        ListNode * current = *head;
//        while(current->next != NULL && current->next->data < insert->data){
//            current = current->next;
//        }
//        insert->next = current->next;
//        current->next = insert;
//
//    }
//
//  }
// template <typename T>
//  void List<T>::sortList(ListNode **head) {
//
//
//    ListNode * tempead = NULL;
//    ListNode * curHead = *head;
//    ListNode * insert;
//
//    while ( curHead != NULL){
//      insert = curHead;
//      curHead = curHead->next;
//      insert->next = NULL;
//      insertSorted(&tempead, insert);
//    }
//    *head = tempead;
//  }


template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {


if(first==NULL && second==NULL){return NULL;}
else if(first == NULL) {return second;}
else if(second == NULL){return first;}
else{
  ListNode* temp1 = first;
  ListNode* temp2 = first;

  bool check = (first->data < second->data) ? true : false;
  temp1 = check ? first:second;
  temp2 = check ? first:second;
  first = check? first->next : first;
  second = check? second: second->next;

  while (first != NULL && second != NULL)
  {
      bool check = (first->data < second->data) ? true : false;
      temp2->next = check? first : second;
      temp2 = check?first : second;
      first = check? first->next : first;
      second = check? second:second->next;
  }
  temp2->next = first? first:second;
  return temp1;
}
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <typename T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the tempoinning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if(chainLength == 1){return start;}

  int total = chainLength;
  chainLength = chainLength/2;


  ListNode* temp1 = start;
  ListNode* temp2 = split(temp1, chainLength);

  ListNode* first = mergesort(temp1, chainLength);

  ListNode* second = mergesort(temp2, total - chainLength);

  ListNode* finally;
  finally = merge(first, second);
  return finally;


}
