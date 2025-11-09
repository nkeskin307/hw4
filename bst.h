#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
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
    void setValue(const Value &value);

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
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
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
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO DONE
    virtual ~BinarySearchTree(); //TODO DONE
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO DONE
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO DONE
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO DONE
    Node<Key, Value> *getSmallestNode() const;  // TODO DONE 
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO DONE
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.
	  static Node<Key, Value>* successor(Node<Key, Value>* current); // TODO DONE
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
		int height(Node<Key,Value> *r) const; //I will use this while implementing the isBalanced() function
		void clearHelper(Node<Key, Value> *n); //This helper function is for when I am clearing the whole tree 


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
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
	current_=ptr; 
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
		current_=nullptr; 

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
		//This should check whether 'this' instantiation is equal to the right hand side that is passed through
    if (rhs.current_==this->current_){return true; } 
		return false;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    if (rhs.current_==this->current_){return false; } 
		return true; 

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
		current_ = successor(current_); 
		return *this; 

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
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    root_=nullptr; 
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    clear();

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{

	//CASE 1: If the tree is EMPTY, we set a new root
	if (root_==NULL){
		root_=new Node<Key,Value>(keyValuePair.first, keyValuePair.second, nullptr); //setting the parent as nullptr
	}

	//CASE 2: If KEY is already in the tree, we will find it and update it's value
	else{
		Node<Key,Value> *found= internalFind(keyValuePair.first); 
		if (found!=nullptr){ //If KEY found
			found->setValue(keyValuePair.second); //Updating the VALUE
		}

		//CASE 3: If the KEY doesn't already exist we insert normally
		else{ 

				Node<Key, Value> *temp= root_; //We can access the root itself
				Node<Key, Value> *parent= nullptr; //this is going to be our parent that updates as we go through the tree

				const Key& keyNew=keyValuePair.first; //This is our new KEY to insert
				const Value& valueNew=keyValuePair.second; //This is our new VALUE to insert

				while (temp!= NULL){ 
					parent=temp; //move down
					if(keyNew>temp->getKey()){ //If the new KEY is greater than the temporary one, calling the getter on the actual node
						temp=temp->getRight(); //We move to the right
					}
					else if (keyNew< temp->getKey()){ //If the new KEY is smaller than the temporary one, 
						temp=temp->getLeft(); //We move left
					}
				}

				//This is where we reached the leaf node to insert, we found where we are going to insert
				Node<Key, Value> *toInsert= new Node<Key, Value>(keyNew, valueNew, parent); 

				//Checking whether we should insert it to the left or right of the parent
				if(keyNew<parent->getKey()){
						parent->setLeft(toInsert);
				}else{
					parent->setRight(toInsert);
				}
		}
	}
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
	//Using our helper function to locate the key
	Node<Key,Value> *found= internalFind(key); 

	//Do nothing if KEY doesn't exist
	if(found==nullptr){
		return; 
	}

	//Finding the right and left children
	Node<Key,Value> *rChild= found->getRight(); 
	Node<Key,Value> *lChild= found->getLeft(); 


	//CASE 1: If there is two children, we perform a swap with the predecessor
	if (rChild!=nullptr && lChild!=nullptr){
		Node<Key,Value> *toSwap= predecessor(found); 
		nodeSwap(found, toSwap); 
		lChild=found->getLeft(); 
		rChild=found->getRight();
	}

	
	//We find the parent 
	Node<Key,Value>* parent= found->getParent();

	//CASE 2: LEAF NODE, NO CHILDREN 
  if (rChild==nullptr && lChild==nullptr){ 
		if (parent==nullptr){//If found is root
			root_=nullptr; 
		}else if (found==parent->getLeft()){
			parent->setLeft(nullptr); //we have to set it to nullptr before we delete
		}else{
			parent->setRight(nullptr);
		}
	}

	//CASE 3: ONE RIGHT CHILD OR ONE LEFT CHILD

	//If there is only RIGHT child
	else if (rChild!=nullptr && lChild==nullptr){ 

		//If the current node is the root node, we can just update the root and delete found
		if (parent==nullptr){
			root_=rChild; 
			root_->setParent(nullptr); 
		}
		else{
			if (found==parent->getRight()){  //If we came here from right
				parent->setRight(rChild);
			}else{
				parent->setLeft(rChild); //If we came from the left
			}
			rChild->setParent(parent); //Setting the parent
		}

	}

  //If there is only LEFT child
  else if (rChild==nullptr && lChild!=nullptr){ 

		//If the current node is the root node, we can just update the root and delete found
		if (parent==nullptr){
			root_=lChild; 
			root_->setParent(nullptr); 
		}
		else{
			if (found==parent->getRight()){ //If we came here from right
				parent->setRight(lChild); 
			}else{
				parent->setLeft(lChild); //If we came from the left
			}
			lChild->setParent(parent);  //Setting the parent
		}

  }
	delete found; //We delete our found key
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
		//The predecessor of a node is the one that comes right before a child

		//CASE 1: If the current node is nullptr
		if (current==nullptr){ 
			return nullptr;
		}

		//CASE 2: Our node has a left child, this means that maximum of the left subtree will be it's predecessor
		if(current->getLeft()!=nullptr){
			current=current->getLeft(); //We traverse down to the left subtree
			while((current->getRight())!=nullptr){ //We are reaching the right end of the left subtree
				current=current->getRight(); 
			} 
			return current;
		}


		//CASE 3: Our Node does not have a left child, this means a higher Parent node will be the predecessor
		Node<Key,Value> *temp= current->getParent();
		while(temp!=nullptr){
				if(temp->getRight()==current){ //If we came down to this node from a smaller node, then the parent wilol be our predecessor
							return temp;
					}
					current=temp; //Otherwise we keep traversing up till we meet this condition
					temp=temp->getParent();	 	
		}
		
		return NULL;
		
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
		//CASE 1: if nullptr
		if (current==nullptr){
			return nullptr; 
		}


		//Defining right and left children
		Node<Key, Value> *rChild= current->getRight();

		//CASE 2: If there is a right child, the minimum node in the right subtree is the successor
		if (rChild!=nullptr){
			Node<Key, Value>* temp= rChild; 
			while(temp->getLeft()!=nullptr){
				temp= temp->getLeft(); 
			}
			return temp; 
		}

		//CASE 3: If there is no right child, we can just keep moving up till we come down from a parent from the left
		else{
			Node <Key,Value> *temp =current; 
			Node <Key, Value> *newParent= current->getParent(); 
			while((newParent!=nullptr) && (newParent->getLeft()!=temp)){
				temp=newParent;
				newParent=newParent->getParent();
			}
			return newParent; 
		}
			
}



/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    //In order to avoid dangling pointers we have to do post-order tree traversal, deleting the subtrees first
		//To do this, I will use a helper function
		clearHelper(root_); 
		root_=nullptr; //Re-setting the root node for future use of the tree, avoiding dangling pointers

		

}		

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value> *n)
{
    //We will do post-order deletion recursively
		//Base case 
		if (n==nullptr){
			return; 
		}

		//Recurse on left subtree
		clearHelper(n->getLeft()); 

		//Recurse on right subtree
		clearHelper(n->getRight());

		//Deleting the current node
		delete n; 

}		



/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
		if (root_==NULL){
			return nullptr;
		}

    Node<Key,Value> *temp= root_;

		while(temp->getLeft()!=NULL){ //Keeps going left since this is a BST and it has to have left nodes that are smaller
			temp=temp->getLeft();
		}
		return temp; 
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
	
	Node<Key,Value>* temp= root_; //Starting from the root 

	while(temp!=NULL){ //Runs while our temporary key is not null , also checks for an empty tree
		if ((temp->getKey())==key){
			return temp; //Returns the pointer if key is found
		}
		if(key<(temp->getKey())){ //If given key value is smaller than our temporary key, we need to look for the left subtree
			temp=temp->getLeft();
		}else{
			temp=temp->getRight();  //Else right subtree
		}
	}
	return NULL; //if nothing found, returns NULL

}

/**
 * Return true if the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
	
		if (root_==NULL){
			return true; 
		}

		return(height(root_)!=-1);  
		
}


template<typename Key, typename Value>
int BinarySearchTree<Key,Value>:: height(Node<Key,Value>* r) const{
	
	//We will do post-order tree traversal where we process the left and right subtrees first, then the node

	//Base case when we hit a nullptr
	if (r==nullptr){
		return 0; 
	}
	
	//We recurse on the left subtree
	int leftH= height(r->getLeft());

	//We recurse on the right subtree
	int rightH=height(r->getRight());

	if((leftH==-1) || (rightH==-1)){
		return -1; 
	}

	//NOW WE CHECK
	int difference = (leftH-rightH); 

	if ((difference>1) || difference<-1){
		return -1; //this means that the tree is unbalanced already 
	}

	leftH+=1; 
	rightH+=1;

	if (leftH>rightH){
		return leftH;
	}
	return rightH; //Returning the height of the subtrees 
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


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

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
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
