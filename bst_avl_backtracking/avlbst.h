#ifndef RBBST_H
#define RBBST_H

#include "bst.h"
#include <algorithm>
#include <cstdlib>
#include <exception>
#include <iostream>

struct KeyError {};

/**
 * A special kind of node for an AVL tree, which adds the height as a data member, plus
 * other additional helper functions. You do NOT need to implement any functionality or
 * add additional data members or helper functions.
 */
template<typename Key, typename Value>
class AVLNode : public Node<Key, Value> {
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight() const;
    void setHeight(int height);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
 * An explicit constructor to initialize the elements by calling the base class constructor and setting
 * the color to red since every new node will be red when it is first inserted.
 */
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
        : Node<Key, Value>(key, value, parent), height_(1) {}

/**
 * A destructor which does nothing.
 */
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode() {}

/**
 * A getter for the height of a AVLNode.
 */
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const {
    return height_;
}

/**
 * A setter for the height of a AVLNode.
 */
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height) {
    height_ = height;
}

/**
 * An overridden function for getting the parent since a static_cast is necessary to make sure
 * that our node is a AVLNode.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const {
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const {
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
 * Overridden for the same reasons as above.
 */
template<class Key, class Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const {
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}

/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/

template<class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value> {
public:
    virtual void insert(const std::pair<const Key, Value>& new_item);  // TODO
    virtual void remove(const Key& key);                               // TODO
protected:
    virtual void nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2);

    // Add helper functions here
    AVLNode<Key, Value>* avlinserthelp(const std::pair<const Key, Value>& keyValuePair);
    void singleCounterCWrotation(
            Node<Key, Value>* z, Node<Key, Value>* y, Node<Key, Value>* x, Node<Key, Value>* t1, Node<Key, Value>* t2);
    void singleCWrotation(
            Node<Key, Value>* z, Node<Key, Value>* y, Node<Key, Value>* x, Node<Key, Value>* t1, Node<Key, Value>* t2);
    void LRZIGZAGrotation(
            Node<Key, Value>* z, Node<Key, Value>* y, Node<Key, Value>* x, Node<Key, Value>* t1, Node<Key, Value>* t2);
    void RLZIGZAGrotation(
            Node<Key, Value>* z, Node<Key, Value>* y, Node<Key, Value>* x, Node<Key, Value>* t1, Node<Key, Value>* t2);
};

// is very similar to the bst implementation, but dynamically allocates an AVLNode
// instead of a Node so that height members and methods can be used when Node
// pointers are casted down
template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::avlinserthelp(const std::pair<const Key, Value>& keyValuePair) {

    Node<Key, Value>* findspot = this->root_;

    if (this->root_ == NULL) {
        AVLNode<Key, Value>* addition = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL);
        this->root_ = addition;
        return addition;
    }

    while (true)
        if (keyValuePair.first > findspot->getKey()) {
            if (findspot->getRight() == NULL) {
                AVLNode<Key, Value>* addition = new AVLNode<Key, Value>(
                        keyValuePair.first, keyValuePair.second, static_cast<AVLNode<Key, Value>*>(findspot));
                findspot->setRight(addition);
                return addition;
            } else {
                findspot = findspot->getRight();
            }
        } else if (keyValuePair.first < findspot->getKey()) {
            if (findspot->getLeft() == NULL) {
                AVLNode<Key, Value>* addition = new AVLNode<Key, Value>(
                        keyValuePair.first, keyValuePair.second, static_cast<AVLNode<Key, Value>*>(findspot));
                findspot->setLeft(addition);
                return addition;
            } else {
                findspot = findspot->getLeft();
            }

        } else {  // they are equal, update . . .
            findspot->setValue(keyValuePair.second);
            return NULL;
        }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value>& new_item) {
    // TODO

    Node<Key, Value>* newnode = avlinserthelp(new_item);
    // don't set height if the node was just updated instead of inserted
    if (newnode == NULL) {
        return;
    }
    static_cast<AVLNode<Key, Value>*>(newnode)->setHeight(0);
    if (newnode == this->root_) {
        return;
    }

    Node<Key, Value>* climber = newnode->getParent();
    Node<Key, Value>* laststep = newnode;

    Node<Key, Value>*z, *y, *x;
    bool whichsideyison;  // false if left of z, true if right of z
    bool whichsidexison;  // false if left of y, true if right of y
    while (true) {        // keep climbing tree until it is unbalanced, then define z,y, and x
        int climberheight = static_cast<AVLNode<Key, Value>*>(climber)->getHeight();
        int laststepheight = static_cast<AVLNode<Key, Value>*>(laststep)->getHeight();

        if (climberheight == laststepheight) {

            static_cast<AVLNode<Key, Value>*>(climber)->setHeight(
                    static_cast<AVLNode<Key, Value>*>(climber)->getHeight() + 1);
        }
        int leftheight, rightheight;
        if (climber->getLeft() == NULL) {
            leftheight = -1;
        } else {
            leftheight = static_cast<AVLNode<Key, Value>*>(climber->getLeft())->getHeight();
        }
        if (climber->getRight() == NULL) {
            rightheight = -1;
        } else {
            rightheight = static_cast<AVLNode<Key, Value>*>(climber->getRight())->getHeight();
        }

        // not balanced
        if (((rightheight - leftheight) * (rightheight - leftheight)) > 1) {
            z = climber;

            if (leftheight > rightheight) {
                y = climber->getLeft();
                whichsideyison = false;
            } else {
                y = climber->getRight();
                whichsideyison = true;
            }

            int yleftheight, yrightheight;
            if (y->getLeft() == NULL) {
                x = y->getRight();
                whichsidexison = true;
            } else if (y->getRight() == NULL) {
                x = y->getLeft();
                whichsidexison = false;
            }

            else {
                yleftheight = static_cast<AVLNode<Key, Value>*>(y->getLeft())->getHeight();
                yrightheight = static_cast<AVLNode<Key, Value>*>(y->getRight())->getHeight();
                if (yrightheight > yleftheight) {
                    x = y->getRight();
                    whichsidexison = true;
                } else if (yrightheight < yleftheight) {
                    x = y->getLeft();
                    whichsidexison = false;
                } else {  // they are equal heights, make it a single rotation
                    if (whichsideyison) {
                        x = y->getRight();
                        whichsidexison = true;
                    } else {
                        x = y->getLeft();
                        whichsidexison = false;
                    }
                }
            }

            break;
        }
        // no problems all the way up
        if (climber->getParent() == NULL) {
            return;
        } else {
            laststep = climber;
            climber = climber->getParent();
        }
    }

    Node<Key, Value>* t1 = NULL;
    Node<Key, Value>* t2 = NULL;
    if (whichsidexison == whichsideyison) {  // single rotation

        if (z == this->root_) {
            this->root_ = y;
        } else {
            if (z->getParent()->getLeft() == z) {  // z is a left child
                z->getParent()->setLeft(y);
            } else {  // z is a right child
                z->getParent()->setRight(y);
            }
        }

        if (whichsideyison) {  // nodes go down to the right
            singleCounterCWrotation(z, y, x, t1, t2);
        }

        else {  // nodes go down to the left
            singleCWrotation(z, y, x, t1, t2);
        }
    }

    else {  // double rotation
        // adjust heights
        static_cast<AVLNode<Key, Value>*>(y)->setHeight(static_cast<AVLNode<Key, Value>*>(y)->getHeight() - 1);
        static_cast<AVLNode<Key, Value>*>(x)->setHeight(static_cast<AVLNode<Key, Value>*>(x)->getHeight() + 1);
        static_cast<AVLNode<Key, Value>*>(z)->setHeight(static_cast<AVLNode<Key, Value>*>(z)->getHeight() - 2);

        if (z == this->root_) {
            this->root_ = x;
        } else {
            if (z->getParent()->getLeft() == z) {  // z is a left child
                z->getParent()->setLeft(x);
            } else {  // z is a right child
                z->getParent()->setRight(x);
            }
        }

        if (whichsideyison) {  // zigzag right then left
            RLZIGZAGrotation(z, y, x, t1, t2);
        } else {  // zigzag left then right
            LRZIGZAGrotation(z, y, x, t1, t2);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::singleCWrotation(
        Node<Key, Value>* z, Node<Key, Value>* y, Node<Key, Value>* x, Node<Key, Value>* t1, Node<Key, Value>* t2) {
    t1 = x->getRight();
    t2 = y->getRight();

    if (t2 != NULL)
        t2->setParent(z);
    z->setLeft(t2);
    y->setRight(z);
    y->setParent(z->getParent());
    z->setParent(y);

    // adjust heights
    int t2height;
    if (t2 == NULL) {
        t2height = -1;
    } else {
        t2height = static_cast<AVLNode<Key, Value>*>(t2)->getHeight();
    }

    if (static_cast<AVLNode<Key, Value>*>(z)->getHeight() - t2height == 3) {
        static_cast<AVLNode<Key, Value>*>(z)->setHeight(static_cast<AVLNode<Key, Value>*>(z)->getHeight() - 2);
    } else if (static_cast<AVLNode<Key, Value>*>(z)->getHeight() - t2height == 2) {
        static_cast<AVLNode<Key, Value>*>(z)->setHeight(static_cast<AVLNode<Key, Value>*>(z)->getHeight() - 1);
    } else {
        std::cout << "ERROR, height calculations done incorrectly" << std::endl;
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::singleCounterCWrotation(
        Node<Key, Value>* z, Node<Key, Value>* y, Node<Key, Value>* x, Node<Key, Value>* t1, Node<Key, Value>* t2) {
    t1 = y->getLeft();
    t2 = x->getLeft();

    if (t1 != NULL)
        t1->setParent(z);
    z->setRight(t1);
    y->setLeft(z);
    y->setParent(z->getParent());
    z->setParent(y);

    // adjust heights
    int t1height;
    if (t1 == NULL) {
        t1height = -1;
    } else {
        t1height = static_cast<AVLNode<Key, Value>*>(t1)->getHeight();
    }

    if (static_cast<AVLNode<Key, Value>*>(z)->getHeight() - t1height == 3) {
        static_cast<AVLNode<Key, Value>*>(z)->setHeight(static_cast<AVLNode<Key, Value>*>(z)->getHeight() - 2);
    } else if (static_cast<AVLNode<Key, Value>*>(z)->getHeight() - t1height == 2) {
        static_cast<AVLNode<Key, Value>*>(z)->setHeight(static_cast<AVLNode<Key, Value>*>(z)->getHeight() - 1);
    } else {
        std::cout << "ERROR, height calculations done incorrectly" << std::endl;
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::RLZIGZAGrotation(
        Node<Key, Value>* z, Node<Key, Value>* y, Node<Key, Value>* x, Node<Key, Value>* t1, Node<Key, Value>* t2) {
    t1 = x->getLeft();
    t2 = x->getRight();
    if (z == this->root_) {
        this->root_ = x;
    }
    if (t1 != NULL)
        t1->setParent(z);
    z->setRight(t1);
    if (t2 != NULL)
        t2->setParent(y);
    y->setLeft(t2);
    x->setParent(z->getParent());
    z->setParent(x);
    y->setParent(x);
    x->setRight(y);
    x->setLeft(z);
}

template<class Key, class Value>
void AVLTree<Key, Value>::LRZIGZAGrotation(
        Node<Key, Value>* z, Node<Key, Value>* y, Node<Key, Value>* x, Node<Key, Value>* t1, Node<Key, Value>* t2) {
    t1 = x->getLeft();
    t2 = x->getRight();
    if (z == this->root_) {
        this->root_ = x;
    }
    if (t1 != NULL)
        t1->setParent(y);
    y->setRight(t1);
    if (t2 != NULL)
        t2->setParent(z);
    z->setLeft(t2);
    x->setParent(z->getParent());
    z->setParent(x);
    y->setParent(x);
    x->setRight(z);
    x->setLeft(y);
}

template<class Key, class Value>
void AVLTree<Key, Value>::remove(const Key& key) {
    // TODO
    Node<Key, Value>* theNode = this->internalFind(key);
    // no node with this key is in the tree
    if (theNode == NULL) {
        return;
    }

    Node<Key, Value>* parentdel = BinarySearchTree<Key, Value>::removalParent(theNode);

    // if the root was the only thing in the tree and it got deleted
    if (parentdel == NULL) {
        return;
    }

    Node<Key, Value>* climber = parentdel;
    while (true) {
        Node<Key, Value>*z, *y, *x;
        bool whichsideyison;  // false if left of z, true if right of z
        bool whichsidexison;  // false if left of y, true if right of y
        while (true) {        // keep climbing tree until it is unbalanced, then define z,y, and x
            int parentlh, parentrh;
            if (climber->getLeft() == NULL)
                parentlh = -1;
            else {
                parentlh = static_cast<AVLNode<Key, Value>*>(climber->getLeft())->getHeight();
            }
            if (climber->getRight() == NULL)
                parentrh = -1;
            else {
                parentrh = static_cast<AVLNode<Key, Value>*>(climber->getRight())->getHeight();
            }

            if (parentlh > parentrh)
                static_cast<AVLNode<Key, Value>*>(climber)->setHeight(parentlh + 1);
            else {
                static_cast<AVLNode<Key, Value>*>(climber)->setHeight(parentrh + 1);
            }

            // not balanced
            if (((parentlh - parentrh) * (parentlh - parentrh)) > 1) {
                z = climber;

                if (parentlh > parentrh) {
                    y = climber->getLeft();
                    whichsideyison = false;
                } else {
                    y = climber->getRight();
                    whichsideyison = true;
                }

                int yleftheight, yrightheight;
                if (y->getLeft() == NULL) {
                    x = y->getRight();
                    whichsidexison = true;
                } else if (y->getRight() == NULL) {
                    x = y->getLeft();
                    whichsidexison = false;
                }

                else {
                    yleftheight = static_cast<AVLNode<Key, Value>*>(y->getLeft())->getHeight();
                    yrightheight = static_cast<AVLNode<Key, Value>*>(y->getRight())->getHeight();
                    if (yrightheight > yleftheight) {
                        x = y->getRight();
                        whichsidexison = true;
                    } else if (yrightheight < yleftheight) {
                        x = y->getLeft();
                        whichsidexison = false;
                    } else {  // they are equal heights, make it a single rotation
                        if (whichsideyison) {
                            x = y->getRight();
                            whichsidexison = true;
                        } else {
                            x = y->getLeft();
                            whichsidexison = false;
                        }
                    }
                }

                break;
            }
            // no problems all the way up
            if (climber->getParent() == NULL) {
                return;
            } else {
                climber = climber->getParent();
            }
        }

        Node<Key, Value>* t1 = NULL;
        Node<Key, Value>* t2 = NULL;
        if (whichsidexison == whichsideyison) {  // single rotation
            if (z == this->root_) {
                this->root_ = y;
            } else {
                if (z->getParent()->getLeft() == z) {  // z is a left child
                    z->getParent()->setLeft(y);
                } else {  // z is a right child
                    z->getParent()->setRight(y);
                }
            }

            if (whichsideyison) {  // nodes go down to the right
                singleCounterCWrotation(z, y, x, t2, t2);
            } else {  // nodes go down to the left
                singleCWrotation(z, y, x, t1, t2);
            }

        }

        else {  // double rotation
            // adjust heights
            static_cast<AVLNode<Key, Value>*>(y)->setHeight(static_cast<AVLNode<Key, Value>*>(y)->getHeight() - 1);
            static_cast<AVLNode<Key, Value>*>(x)->setHeight(static_cast<AVLNode<Key, Value>*>(x)->getHeight() + 1);
            static_cast<AVLNode<Key, Value>*>(z)->setHeight(static_cast<AVLNode<Key, Value>*>(z)->getHeight() - 2);

            if (z == this->root_) {
                this->root_ = x;
            } else {
                if (z->getParent()->getLeft() == z) {  // z is a left child
                    z->getParent()->setLeft(x);
                } else {  // z is a right child
                    z->getParent()->setRight(x);
                }
            }

            if (whichsideyison) {  // zigzag right then left
                RLZIGZAGrotation(z, y, x, t1, t2);
            } else {  // zigzag left then right
                LRZIGZAGrotation(z, y, x, t1, t2);
            }
        }
        if (z == this->root_)
            return;
        climber = z->getParent();
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap(AVLNode<Key, Value>* n1, AVLNode<Key, Value>* n2) {
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}

#endif
