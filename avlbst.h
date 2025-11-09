#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
		void balanceCheck(AVLNode< Key, Value> *current);
		void leftRotation(AVLNode< Key, Value> *current);
		void rightRotation(AVLNode< Key, Value> *current);
		void removeFix(AVLNode<Key,Value>* n, int difference);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
  // TODO
	if (this->root_==nullptr){
		this->root_= new AVLNode<Key,Value> (new_item.first, new_item.second, nullptr);
		return; 
	}

	//CASE 1: If KEY is already in the tree, we will find it and update it's value
		AVLNode<Key,Value> *found= static_cast<AVLNode<Key,Value>*>(this->internalFind(new_item.first)); 
		if (found!=nullptr){ //If KEY found
			found->setValue(new_item.second); //Updating the VALUE
			return;
		}

		//CASE 2: If the KEY doesn't already exist we insert normally

		AVLNode<Key, Value> *temp= static_cast<AVLNode<Key,Value>*>(this->root_); //We can access the root itself
		AVLNode<Key, Value> *parent= nullptr; //this is going to be our parent that updates as we go through the tree

		const Key& keyNew=new_item.first; //This is our new KEY to insert
		const Value& valueNew=new_item.second; //This is our new VALUE to insert

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
		AVLNode<Key, Value> *toInsert= new AVLNode<Key, Value>(keyNew, valueNew, parent); 
		toInsert->setBalance(0);

		//Checking whether we should insert it to the left or right of the parent
		if(keyNew<parent->getKey()){
				parent->setLeft(toInsert); 
		}else{
			parent->setRight(toInsert);
		}

		//NOW CHECKING BALANCE
		balanceCheck(toInsert); 
}



template<class Key, class Value>
void AVLTree<Key, Value>::balanceCheck(AVLNode< Key, Value> *current)
{
	AVLNode<Key, Value> *parent= current->getParent(); 

	//We keep checking till we reach the root node 
	while (parent!=NULL){ 

		//CASE 1:If we added to the left subtree, the balance of the parent increases
		if (parent->getLeft()==current){ 
				parent->updateBalance(1);
			}
		//CASE 2: If we added to the right subtree, the balance of the parent decreases
		else if (parent->getRight()==current){ 
			parent->updateBalance(-1);
		}

		//Now we check for balances: 
		//CASE 1: if balance is 0, we can stop and no rotation is needed. 
		if (0==parent->getBalance()){
			return; 
		}

		//CASE 2: if balance is -1 or 1, we keep moving up to check for parents 
		else if (parent->getBalance()==-1 || parent->getBalance()==1){
			current=parent; 
			parent= parent->getParent(); 
			continue;
		}

		//CASE 3: Now we need to rotate and update our balances
		//With the Double rotations, the balance updates depends on the grandchildren
		//With single rotations, the balance updates are simply 0

		//This is LR Imbalance
		if (parent->getBalance()==-2 && current->getBalance()==1){

			//We need to save the grandcild balances to determine the balance updates
			AVLNode<Key,Value> *gChild= current->getLeft();
			int grandChildB= 0; 
			if (gChild!=nullptr){
				grandChildB= gChild->getBalance(); 
			}
			rightRotation(current);
			leftRotation(parent);

			if (grandChildB==0){
				current->setBalance(0);
				parent->setBalance(0);
				gChild->setBalance(0);
			}
			else if (grandChildB==1){
				current->setBalance(-1);
				parent->setBalance(0);
				gChild->setBalance(0);
			}
			else{
				current->setBalance(0);
				parent->setBalance(1);
				gChild->setBalance(0);
			}
		}
		//This is RR Imbalance
		else if(parent->getBalance()==-2 && current->getBalance()==-1){
			leftRotation(parent);
			current->setBalance(0);
			parent->setBalance(0); 
		}

		//This is RL Imbalance
		else if(parent->getBalance()==2 && current->getBalance()==-1){

			//We need to save the grandcild balances to determine the balance updates
			AVLNode<Key,Value> *gChild= current->getRight();
			int grandChildB= 0; 
			if (gChild!=nullptr){
				grandChildB= gChild->getBalance(); 
			}

			leftRotation(current);
			rightRotation(parent);

			if (grandChildB==0){
				current->setBalance(0);
				parent->setBalance(0);
				gChild->setBalance(0);
			}
			else if (grandChildB==1){
				current->setBalance(0);
				parent->setBalance(-1);
				gChild->setBalance(0);
			}
			else{
				current->setBalance(1);
				parent->setBalance(0);
				gChild->setBalance(0);
			}
		}

		//This is LL Imbalance
		else{
			rightRotation(parent);
			current->setBalance(0);
			parent->setBalance(0); 
		}
		break;
	}
}



template<class Key, class Value>
void AVLTree<Key, Value>::rightRotation(AVLNode< Key, Value> *current)
{
	//This is the right subtree of the middle node, we will use this later:
	AVLNode<Key,Value> *tempRSubtree= current->getLeft()->getRight();
	AVLNode<Key,Value> *newRoot= current->getLeft();

	//Saving the current's parents before we modify it
	AVLNode<Key,Value> *oldParent= current->getParent();


	//Now we do the rotation
	newRoot->setRight(current);
	current->setLeft(tempRSubtree);

	if (tempRSubtree!=nullptr){ //If there is a right subtree, we update its pointers
		tempRSubtree->setParent(current);
	}

	//Now we update the parent pointers
	newRoot->setParent(oldParent);
	current->setParent(newRoot);

	//Now we update the initial root's child pointers
	if (oldParent!=nullptr){
		if (oldParent->getLeft()==current){
			oldParent->setLeft(newRoot);
		}else{
			oldParent->setRight(newRoot);
		}
	}else{
		this->root_=newRoot;
	}

}



template<class Key, class Value>
void AVLTree<Key, Value>::leftRotation(AVLNode< Key, Value> *current)
{
	//This is the left subtree of the middle node, we will use this later:
	AVLNode<Key,Value> *tempLSubtree= current->getRight()->getLeft();
	AVLNode<Key,Value> *newRoot= current->getRight();

	//Saving the current's parents before we modify it
	AVLNode<Key,Value> *oldParent= current->getParent();


	//Now we do the rotation
	newRoot->setLeft(current);
	current->setRight(tempLSubtree);

	if (tempLSubtree!=nullptr){ //If there is a left subtree, we update its pointers
		tempLSubtree->setParent(current);
	}

	//Now we update the parent pointers
	newRoot->setParent(oldParent);
	current->setParent(newRoot);

	//Now we update the initial root's child pointers
	if (oldParent!=nullptr){
		if (oldParent->getLeft()==current){
			oldParent->setLeft(newRoot);
		}else{
			oldParent->setRight(newRoot);
		}
	}else{
		this->root_=newRoot;
	}

}




/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
		//Find the node to remove
		AVLNode<Key, Value> *current=static_cast<AVLNode<Key,Value>*>(this->internalFind(key));

		//CASE 1: node does not exist
		if (current==nullptr){
			return; 
		}
		int difference=0;

		AVLNode <Key,Value> *rChild= current->getRight();
		AVLNode<Key,Value> *lChild= current->getLeft();
		AVLNode<Key,Value> *parent= current->getParent();

		//CASE 2:There are two children
		if (rChild!=nullptr &&lChild!=nullptr){
			//Finding the successor to swap, this will ensure that we have 0 or 1 child to delete
			AVLNode<Key, Value> *predecessor=static_cast<AVLNode<Key,Value>*>(this->predecessor(current));
			
			if (predecessor==nullptr){
				return; 
			}

			nodeSwap(current, predecessor); 

			//We set the links before deletion
			parent= current->getParent(); 
			rChild= current->getRight();
			lChild=current->getLeft();
		} 

		//CASE 3: There is only one child
		AVLNode<Key, Value>* child=nullptr; 
		if (lChild!=nullptr){
			child=lChild;
		}else if (rChild!=nullptr){
			child=rChild;
		}

		//Now we find the balance differences
		if (parent!=nullptr){
			if (parent->getLeft() ==current){
				difference=-1;
			}else{
				difference=1;
			}
		}
		
		//Handle the root case
		if (parent==nullptr){ 
				this->root_=child; 
				if (child!=nullptr){
					child->setParent(nullptr); //A root node's parent is null
				}
		}else{//Handling all other cases
				if (parent->getLeft()==current){
					parent->setLeft(child); //This is if we came down from the left
					if (child!=nullptr){
						child->setParent(parent); //Reattaching the parent 
					}
				}else{
					parent->setRight(child); //This is if we came down from the right
					if (child!=nullptr){
						child->setParent(parent); //Reattaching the parent
					}
				}

		}
		//we delete at the end
		delete current; 

		if (parent!=nullptr){
			removeFix(parent, difference); 
		}
}

template<class Key, class Value>
void AVLTree<Key, Value>:: removeFix(AVLNode<Key,Value>* n, int difference)
{

		//BASE CASE: if n is NULL, we return
		if (n==nullptr){
			return; 
		}

	

		//We compute the ndiff for the parent before any rotations because they alter the tree's structure
		AVLNode<Key,Value> *newParent= n->getParent(); 


		int ndifference=0; //This is the update needed on the balance factor of the parent
		if (newParent!=nullptr){
			if (newParent->getLeft()==n){ //If n is the right child 
				ndifference=-1;
			}
			else if (newParent->getRight()==n){ //If n is the left child 
				ndifference=1; 
			}
		}

		//NOW WE CHECK FOR ROTATIONS AND RECURSE:
		int currBalance= n->getBalance()+ difference; 
		//CASE 1:
		if (currBalance==-1){ //We don't need further alteration
			n->setBalance(-1);
			return; 
		}

		else if (currBalance==1){ //We don't need further alteration
			n->setBalance(1);
			return; 
		}


		//CASE 2:
		else if (currBalance==0){
			n->setBalance(0);
			removeFix(newParent, ndifference); //Now we have to check for parents and recurse up the tree

		}

		//CASE 3: Rotations needed 
		else if (currBalance==-2){ 
			//We find the taller child, which is the left
			AVLNode <Key, Value> *rChild= n->getRight(); 
			if (rChild==nullptr){return;}
			int rBalance= rChild->getBalance(); 


			if (rBalance==-1){//This is the LL Imbalance
				leftRotation(n);
				n->setBalance(0);
				rChild->setBalance(0); 
				removeFix( newParent, ndifference); //Keep updating
			}

			else if (rBalance==0){
				leftRotation(n);
				n->setBalance(-1);
				rChild->setBalance(1); 
				//We are done!
			}

			else if (rBalance==1){
				AVLNode <Key, Value> *grandLChild= rChild->getLeft(); 
				if (grandLChild==nullptr){
					return; 
				}
				rightRotation(n->getRight());
				leftRotation(n); 

				//Updating Balances:
				int rBalance= grandLChild->getBalance();
				if (rBalance==1 ){
						n->setBalance(0); 
						rChild->setBalance(-1);
						grandLChild->setBalance(0); 
				}
				else if (rBalance==-1){
						n->setBalance(1); 
						rChild->setBalance(0);
						grandLChild->setBalance(0); 
				}
				else if (rBalance==0){
						n->setBalance(0); 
						rChild->setBalance(0);
						grandLChild->setBalance(0); 
				}
				removeFix(newParent, ndifference); 
			}
		}
		else if (currBalance==2){ 
			//We find the taller child, which is the left
			AVLNode <Key, Value> *lChild= n->getLeft(); 
			if (lChild==nullptr){
				return; 
			}
			int rBalance= lChild->getBalance(); 

			if (rBalance==1){//This is the LL Imbalance
				rightRotation(n); 
				n->setBalance(0);
				lChild->setBalance(0); 
				removeFix( newParent, ndifference); //Keep updating
			}

			else if (rBalance==0){
				rightRotation(n); 
				n->setBalance(1);
				lChild->setBalance(-1); 
				//We are done!
			}

			else if (rBalance==-1){
				AVLNode <Key, Value> *grandRChild= lChild->getRight(); 
				if (grandRChild==nullptr){
					return;
				}
				leftRotation(lChild);
				rightRotation(n); 

				//Updating Balances:
				int lLBalance= grandRChild->getBalance();
				if (lLBalance==1 ){
						n->setBalance(-1); 
						lChild->setBalance(0);
						grandRChild->setBalance(0); 
				}
				else if (lLBalance==-1 ){
						n->setBalance(0); 
						lChild->setBalance(1);
						grandRChild->setBalance(0); 
				}
				else if (lLBalance==0){
						n->setBalance(0); 
						lChild->setBalance(0);
						grandRChild->setBalance(0); 
				}
				removeFix(newParent, ndifference); 
			}
		}
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
