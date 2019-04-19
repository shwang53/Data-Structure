/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
      // Your code here
    if(s.empty()){
      return T(); // stub return value (0 for primitive types). Change this!
                  // Note: T() is the default value for objects, and 0 for
                  // primitive types

    }else{
      T temp = s.top();
      T total = s.top();

     s.pop();
     total += sum(s);

      s.push(temp);

     return total;

    }

}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of
 * square bracket characters, [, ], and other characters. This function will return
 * true if and only if the square bracket characters in the given
 * string are balanced. For this to be true,
 * all brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is balanced,
 * "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is balanced.
 *
 * For this function, you may only create a single local variable of type stack<char>!
 * No other stack or queue local objects may be declared. Note that you may still
 * declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{

    // @TODO: Make less optimistic
    stack<char> mystack;
    int count1 =0;
    int count2 =0;
    //bool check = false;

    if(input.empty()){ return true;}
    else{
      while(!input.empty()) {
            //switch(input.front())
            if(input.front() == '['){
                mystack.push(input.front());
                count1++;
            }
            if(input.front() ==  ']'){
              if(mystack.empty()){ return false;}
              if(mystack.top() == '['){mystack.pop();}
              count2++;
            }
            input.pop();
      }
      if(count1 == count2 && mystack.empty()){
          return true;
      }else{
        return false;
      }

  }

}



/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{

    // Your code here

    stack<T> s;
    int count = 0, part = 1, capacity = q.size();

    while(count<capacity) {
        if(part % 2 == 1) { // odd
            int length = part > (capacity-count) ? (capacity-count) : part;
            for(int i = 0; i < length; i++) {
                q.push(q.front());
                q.pop();
            }
            part++; count += length;
        }

        else if(part % 2 == 0) { //even reverse
            int length = part > (capacity-count) ? (capacity-count) : part;
            for(int i = 0; i < length; i++) {
                s.push(q.front());
                q.pop();
            }
            for(int i = 0; i < length; i++) {
                q.push(s.top());
                s.pop();
            }
            part++; count += length;
        }
    }
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note The back of the queue corresponds to the top of the stack!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q){

    // Your code here
    bool same = true; // reset to be true.

    if(s.empty()) {return true;} // if the stack is empty, return true.
    else{
        T temp = s.top(); // temp stores the top of first stack
        s.pop(); //and pop the stack.

        same = verifySame(s, q); //temp stores stack values until the stack is empty.(recursively)
        s.push(temp); // push the originial stack value back to the stack, so it is unmodified.

        //if same is true and this moment's(recursive case of) values of queue and stack(temp)
        // are equal then same is true, will return true.
        //if not equal, same is false, will return false.
        //**check if matching bottom(lastest) stack and front queue.
        if (same == true && (q.front() == temp)){
            same = true;
        }else{
            same = false;
        }

        q.push(q.front()); //push the front value in the back of itself, so next queue fron can be compared with the stack.
      //  T temp2 = q.front();
        q.pop(); // pop the oldest so can get next value, no overlap value in the end. = unmodified.

        return same;
      }
    }

}
