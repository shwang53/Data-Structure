/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* node = t->right;
   t->right = node->left;
   node->left = t;
   t = node;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* node = t->left;
   t->left = node->right;
   node->right = t;
   t = node;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL)
     return;

   if(heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) == -2){
      if(heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left) == -1){rotateRight(subtree);}
      else if(heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left) == 1){rotateLeftRight(subtree);}
   }
   else if (heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left) == 2){
     if(heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left) == 1){rotateLeft(subtree);}
     else if (heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left) == -1){ rotateRightLeft(subtree);}
   }

   subtree->height = 1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
   if(subtree->left != NULL){subtree->left->height = 1 + max(heightOrNeg1(subtree->left->left), heightOrNeg1(subtree->left->right));}
   if(subtree->right != NULL){subtree->right->height = 1 + max(heightOrNeg1(subtree->right->left), heightOrNeg1(subtree->right->right));
}

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree == NULL){
      subtree = new Node(key, value);
      return;
    }
    else if (subtree->key > key){
      insert(subtree->left, key, value);
      rebalance(subtree);
    }
    else if (subtree->key < key){
      insert(subtree->right, key, value);
      rebalance(subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;

        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here

            Node* node = subtree->left;
            while (node->right){node = node->right;}
            swap(subtree, node);
            remove(subtree->left, key);


        } else {
            /* one-child remove */
            // your code here

            Node* left = subtree->left;
            Node* right = subtree->right;
           delete subtree;
           if (left != NULL) {subtree = left;}
           else {subtree = right;}
        }

        rebalance(subtree);

    }
    if (subtree != NULL) {rebalance(subtree);}
}
