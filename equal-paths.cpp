#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)
#include <iostream>
#endif

#include "equal-paths.h"
using namespace std;

// You may add any prototypes of helper functions here

int pathLength(Node *root);

bool equalPaths(Node * root)
{
		return pathLength(root)!=(-1); //Will return true if the pathLength never returns -1

}


//This is depth first search but we will be marking visited nodes 
int pathLength(Node* root){

	if (root==NULL){ //This is the base case when empty tree 
		return 0;
	}

	if ((root->left==nullptr)&& (root->right==nullptr)){ //Means that the current node is a leaf 
		return 1; 
	}


	int left_subtree=pathLength(root->left); //Computes the length of left subtree
	int right_subtree=pathLength(root->right); //Computes the length of right subtree

	if (left_subtree==-1||right_subtree==-1){
		return -1; //if we have any previous -1 returns, this means path lengths aren't equal
	}

	if (root->left!=nullptr && root->right!=nullptr &&left_subtree!=right_subtree){
		return -1;  // this checks whether if the root has both leaf nodes and the paths are equal
	}

	if (root->left!=nullptr){ //If there is no right subtree, so it is only left subtree, this returns the length of left subtree
		return left_subtree+1; //This check works for skew trees
	}
	return right_subtree+1; 
}
