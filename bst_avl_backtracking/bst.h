#ifndef BST_H
#define BST_H

#include <cstdlib>
#include <exception>
#include <iostream>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template<typename Key, typename Value>
class Node {
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value& value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
 * Explicit constructor for a node.
 */
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent)
        : item_(key, value), parent_(parent), left_(NULL), right_(NULL) {}

/**
 * Destructor, which does not need to do anything since the pointers inside of a node
 * are only used as references to existing nodes. The nodes pointed to by parent/left/right
 * are freed within the deleteAll() helper method in the BinarySearchTree.
 */
template<typename Key, typename Value>
Node<Key, Value>::~Node() {}

/**
 * A const getter for the item.
 */
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const {
    return item_;
}

/**
 * A non-const getter for the item.
 */
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem() {
    return item_;
}

/**
 * A const getter for the key.
 */
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const {
    return item_.first;
}

/**
 * A const getter for the value.
 */
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const {
    return item_.second;
}

/**
 * A non-const getter for the value.
 */
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue() {
    return item_.second;
}

/**
 * An implementation of the virtual function for retreiving the parent.
 */
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const {
    return parent_;
}

/**
 * An implementation of the virtual function for retreiving the left child.
 */
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const {
    return left_;
}

/**
 * An implementation of the virtual function for retreiving the right child.
 */
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const {
    return right_;
}

/**
 * A setter for setting the parent of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent) {
    parent_ = parent;
}

/**
 * A setter for setting the left child of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left) {
    left_ = left;
}

/**
 * A setter for setting the right child of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right) {
    right_ = right;
}

/**
 * A setter for the value of a node.
 */
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value) {
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
 * A templated unbalanced binary search tree.
 */
template<typename Key, typename Value>
class BinarySearchTree {
public:
    BinarySearchTree();                                                    //
    virtual ~BinarySearchTree();                                           //
    virtual void insert(const std::pair<const Key, Value>& keyValuePair);  //
    virtual void remove(const Key& key);                                   // TODO
    void clear();                                                          //
    bool isBalanced() const;                                               //
    void print() const;
    bool empty() const;

public:
    /**
     * An internal iterator class for traversing the contents of the BST.
     */
    class iterator  //
    {
    public:
        iterator();

        std::pair<const Key, Value>& operator*() const;
        std::pair<const Key, Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key, Value>* ptr);
        Node<Key, Value>* current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const;               //
    Node<Key, Value>* getSmallestNode() const;                        //
    static Node<Key, Value>* predecessor(Node<Key, Value>* current);  //
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot(Node<Key, Value>* r) const;
    virtual void nodeSwap(Node<Key, Value>* n1, Node<Key, Value>* n2);

    // Add helper functions here
protected:
    Node<Key, Value>* inserthelper(const std::pair<const Key, Value>& keyValuePair);
    static Node<Key, Value>* getGreatestNode(Node<Key, Value>* top);
    Node<Key, Value>* removalParent(Node<Key, Value>* tobeDeleted);
    int getheight(Node<Key, Value>* start) const;
    void clearhelper(Node<Key, Value>* n);
    bool isBalancedhelper(Node<Key, Value>* s) const;

protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
 * Explicit constructor that initializes an iterator with a given node pointer.
 */
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key, Value>* ptr) {
    //
    current_ = ptr;
}

/**
 * A default constructor that initializes the iterator to NULL.
 */
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() : current_(NULL) {
    // TODO
}

/**
 * Provides access to the item.
 */
template<class Key, class Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() const {
    return current_->getItem();
}

/**
 * Provides access to the address of the item.
 */
template<class Key, class Value>
std::pair<const Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() const {
    return &(current_->getItem());
}

/**
 * Checks if 'this' iterator's internals have the same value
 * as 'rhs'
 */
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const {
    //
    if (rhs.current_ == current_) {
        return true;
    } else {
        return false;
    }
}

/**
 * Checks if 'this' iterator's internals have a different value
 * as 'rhs'
 */
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const {
    //
    if (rhs.current_ == current_) {
        return false;
    } else {
        return true;
    }
}

/**
 * Advances the iterator's location using an in-order sequencing
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++() {
    //
    if (current_->getRight() != NULL) {

        Node<Key, Value>* goingdown = current_->getRight();
        while (goingdown->getLeft() != NULL) {
            goingdown = goingdown->getLeft();
        }
        current_ = goingdown;
        return *this;  // figure this out
    } else {
        Node<Key, Value>* goingup = current_->getParent();
        while (goingup != NULL && current_ == goingup->getRight()) {
            current_ = goingup;
            goingup = goingup->getParent();
        }
        current_ = goingup;
        return *this;
    }
}

/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
 * Default constructor for a BinarySearchTree, which sets the root to NULL.
 */
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() : root_(NULL) {
    // TODO
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() {
    //
    clear();
}

/**
 * Returns true if tree is empty
 */
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const {
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const {
    printRoot(root_);
    std::cout << "\n";
}

/**
 * Returns an iterator to the "smallest" item in the tree
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin() const {
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
 * Returns an iterator whose value means INVALID
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end() const {
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
 * Returns an iterator to the item with the given key, k
 * or the end iterator if k does not exist in the tree
 */
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& k) const {
    Node<Key, Value>* curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * An insert method to insert into a Binary Search Tree.
 * The tree will not remain balanced when inserting.
 */
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair) {
    //
    inserthelper(keyValuePair);
}

// returns pointer to inserted node
template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::inserthelper(const std::pair<const Key, Value>& keyValuePair) {

    Node<Key, Value>* findspot = root_;

    if (root_ == NULL) {
        Node<Key, Value>* addition = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        root_ = addition;
        return addition;
    }

    while (true)
        if (keyValuePair.first > findspot->getKey()) {
            if (findspot->getRight() == NULL) {
                Node<Key, Value>* addition = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, findspot);
                findspot->setRight(addition);
                return addition;
            } else {
                findspot = findspot->getRight();
            }
        } else if (keyValuePair.first < findspot->getKey()) {
            if (findspot->getLeft() == NULL) {
                Node<Key, Value>* addition = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, findspot);
                findspot->setLeft(addition);
                return addition;
            } else {
                findspot = findspot->getLeft();
            }

        } else {  // they are equal, update . . .
            findspot->setValue(keyValuePair.second);
            return findspot;
        }
}

/**
 * A remove method to remove a specific key from a Binary Search Tree.
 * The tree may not remain balanced after removal.
 */
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key) {
    //
    Node<Key, Value>* theNode = internalFind(key);
    // no node with this key is in the tree
    if (theNode == NULL) {
        return;
    }
    removalParent(theNode);
}

// returns pointer to the parent of the removed node
template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::removalParent(Node<Key, Value>* theNode) {
    // if it is a leaf node
    if (theNode->getRight() == NULL && theNode->getLeft() == NULL) {
        if (theNode != root_) {
            if (theNode->getParent()->getLeft() == theNode) {
                theNode->getParent()->setLeft(NULL);
            } else {
                theNode->getParent()->setRight(NULL);
            }

        } else {
            root_ = NULL;
        }
    }

    // if it has two children
    else if (theNode->getRight() != NULL && theNode->getLeft() != NULL) {
        // find predecessor
        Node<Key, Value>* pred = predecessor(theNode);

        // swap with predecessor
        nodeSwap(pred, theNode);

        // if it is now a leaf, delete it
        if (theNode->getRight() == NULL && theNode->getLeft() == NULL) {
            if (theNode->getParent()->getLeft() == theNode) {  // theNode is a leftchild
                theNode->getParent()->setLeft(NULL);
            } else {
                theNode->getParent()->setRight(NULL);
            }
        } else {  // predecessor had one child - it will always be on the left
            if (theNode->getParent()->getLeft() == theNode) {  // theNode is a leftchild
                theNode->getParent()->setLeft(theNode->getLeft());
            } else {  // the node is a right child
                theNode->getParent()->setRight(theNode->getLeft());
            }
            theNode->getLeft()->setParent(theNode->getParent());
        }
    }

    else {                                  // if it has one child
        if (theNode->getRight() != NULL) {  // child is on the right
            if (theNode == root_) {
                theNode->getRight()->setParent(NULL);
                root_ = theNode->getRight();
            } else if (theNode->getParent()->getLeft() == theNode) {  // theNode is a leftchild
                theNode->getParent()->setLeft(theNode->getRight());
                theNode->getRight()->setParent(theNode->getParent());

            } else {  // thenode is a rightchild
                theNode->getParent()->setRight(theNode->getRight());
                theNode->getRight()->setParent(theNode->getParent());
            }

        } else {  // child is on the left
            if (theNode == root_) {
                theNode->getLeft()->setParent(NULL);
                root_ = theNode->getLeft();
            } else if (theNode->getParent()->getLeft() == theNode) {  // theNode is a leftchild
                theNode->getParent()->setLeft(theNode->getLeft());
                theNode->getLeft()->setParent(theNode->getParent());
            } else {  // thenode is a rightchild
                theNode->getParent()->setRight(theNode->getLeft());
                theNode->getLeft()->setParent(theNode->getParent());
            }
        }
    }
    // if not the root node
    if (theNode != root_) {
        Node<Key, Value>* temp = theNode->getParent();
        delete theNode;
        return temp;
    }
    // if it is the root node
    else {
        delete theNode;
        return NULL;
    }
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current) {
    // TODO

    if (current->getLeft() == NULL) {
        return current;
    } else {
        return getGreatestNode(current->getLeft());
    }
}

template<class Key, class Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getGreatestNode(Node<Key, Value>* top) {
    if (top->getRight() == NULL) {
        return top;
    } else {
        return getGreatestNode(top->getRight());
    }
}

/**
 * A method to remove all contents of the tree and
 * reset the values in the tree for use again.
 */
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear() {
    //
    clearhelper(root_);
    root_ = NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearhelper(Node<Key, Value>* n) {
    // base case
    if (n == NULL)
        return;

    // using postorder traversal (DFS)
    clearhelper(n->getLeft());
    clearhelper(n->getRight());
    delete n;
}

/**
 * A helper function to find the smallest node in the tree.
 */
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const {
    //
    if (empty()) {
        return NULL;
    }
    Node<Key, Value>* curr = root_;
    while (true) {
        if (curr->getLeft() == NULL) {
            return curr;
        }
        curr = curr->getLeft();
    }
}

/**
 * Helper function to find a node with given key, k and
 * return a pointer to it or NULL if no item with that key
 * exists
 */
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const {
    //
    if (root_ == NULL) {
        return NULL;
    }
    Node<Key, Value>* findspot = root_;
    while (true)
        if (key > findspot->getKey()) {
            if (findspot->getRight() == NULL) {
                return NULL;
            } else {
                findspot = findspot->getRight();
            }
        } else if (key < findspot->getKey()) {
            if (findspot->getLeft() == NULL) {
                return NULL;
            } else {
                findspot = findspot->getLeft();
            }
        } else {  // found!
            return findspot;
        }
}

/**
 * Return true if the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const {
    // TODO
    return isBalancedhelper(root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalancedhelper(Node<Key, Value>* s) const {
    if (s == NULL) {
        return true;
    }

    int hltree = getheight(s->getLeft());
    int hrtree = getheight(s->getRight());

    if (hltree == hrtree || ((hltree - hrtree) * (hltree - hrtree)) == 1) {
        return (isBalancedhelper(s->getLeft()) && isBalancedhelper(s->getRight()));
    }

    return false;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::getheight(Node<Key, Value>* start) const {
    if (start == NULL) {
        return -1;
    } else {
        int lheight = getheight(start->getLeft());
        int rheight = getheight(start->getRight());

        /*use the larger of the two*/
        if (lheight > rheight) {
            return (lheight + 1);
        } else {
            return (rheight + 1);
        }
    }
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap(Node<Key, Value>* n1, Node<Key, Value>* n2) {
    if ((n1 == n2) || (n1 == NULL) || (n2 == NULL)) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if (n1p != NULL && (n1 == n1p->getLeft()))
        n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if (n2p != NULL && (n2 == n2p->getLeft()))
        n2isLeft = true;

    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if ((n1r != NULL && n1r == n2)) {
        n2->setRight(n1);
        n1->setParent(n2);
    } else if (n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    } else if (n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    } else if (n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);
    }

    if (n1p != NULL && n1p != n2) {
        if (n1isLeft)
            n1p->setLeft(n2);
        else
            n1p->setRight(n2);
    }
    if (n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if (n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if (n2p != NULL && n2p != n1) {
        if (n2isLeft)
            n2p->setLeft(n1);
        else
            n2p->setRight(n1);
    }
    if (n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if (n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }

    if (this->root_ == n1) {
        this->root_ = n2;
    } else if (this->root_ == n2) {
        this->root_ = n1;
    }
}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
