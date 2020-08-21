/*
Student Name: Nathan Cheshire
Student NetID: nvc29
Compiler Used: Visual Studio Community Edition 2019
Program Description:
This header file contains the code for the AVL and the Node which this fifth project, an AVL loader, utilizes.
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>

//standard namespace
using namespace std;

//Node class implementation
class avlNode
{
	//Everything is public since we are not accessing node directly through our main program
	public:

		//each node in this case has data and a left and right child pointer
		string data;
		int height;
		avlNode* leftChild;
		avlNode* rightChild;

		//Constructor
		avlNode(string data)
		{
			this->data = data;
			this->height = 1;
			this->leftChild = nullptr;
			this->rightChild = nullptr;
		}

		//Empty constructor
		avlNode()
		{
			this->data = "";
			this->height = 1;
			this->leftChild = nullptr;
			this->rightChild = nullptr;
		}
};

class avlTree
{
	private:
		avlNode* root;

		//Private search method so that we don't have to pass a node originally
		bool Psearch(string search, avlNode*& start)
		{
			if (root == nullptr)
			{
				throw EmptyTreeException;
			}

			else if (start == nullptr)
			{
				return false;
			}

			else if (start->data == search)
			{
				return true;
			}

			else if (start->data > search)
			{
				return this->Psearch(search, start->leftChild);
			}

			else if (start->data < search)
			{
				return this->Psearch(search, start->rightChild);
			}
		}

		//Private insert so that we don't have to pass a node originally
		bool Pinsert(string insert, avlNode*& start)
		{
			if (start == nullptr)
			{
				start = new avlNode(insert);

				return true;
			}

			else if (start->data == insert)
			{
				return false;
			}

			else if (start->data < insert)
			{
				return this->Pinsert(insert, start->rightChild);
			}

			else if (start->data > insert)
			{
				return this->Pinsert(insert, start->leftChild);
			}
		}

		//Private in order listing so that we don't have to pass a node originally
		string PinOrderList(avlNode*& start)
		{
			if (start == nullptr)
			{
				throw EmptyTreeException;
			}

			else if (start->leftChild == nullptr && start->rightChild == nullptr)
			{
				return start->data;
			}

			else if (start->leftChild == nullptr && start->rightChild != nullptr)
			{
				return start->data + "," + PinOrderList(start->rightChild);
			}

			else if (start->leftChild != nullptr && start->rightChild == nullptr)
			{
				return PinOrderList(start->leftChild) + "," + start->data;
			}

			else if (start->leftChild != nullptr && start->rightChild != nullptr)
			{
				return PinOrderList(start->leftChild) + "," + start->data + "," + PinOrderList(start->rightChild);
			}
		}
		//Private pre order listing so that we don't have to pass a node originally
		string PpreOrderList(avlNode*& start)
		{
			if (start == nullptr)
			{
				throw EmptyTreeException;
			}

			else if (start->leftChild == nullptr && start->rightChild == nullptr)
			{
				return start->data;
			}

			else if (start->leftChild == nullptr && start->rightChild != nullptr)
			{
				return start->data + "," + PpreOrderList(start->rightChild);
			}

			else if (start->leftChild != nullptr && start->rightChild == nullptr)
			{
				return start->data + "," + PpreOrderList(start->leftChild);
			}

			else if (start->leftChild != nullptr && start->rightChild != nullptr)
			{
				return start->data + "," + PpreOrderList(start->leftChild) + "," + PpreOrderList(start->rightChild);
			}
		}

		//Private post order listing so that we don't have to pass a node originally
		string PpostOrderList(avlNode*& start)
		{
			if (start == nullptr)
			{
				throw EmptyTreeException;
			}

			else if (start->leftChild == nullptr && start->rightChild == nullptr)
			{
				return start->data;
			}

			else if (start->leftChild == nullptr && start->rightChild != nullptr)
			{
				return PpostOrderList(start->rightChild) + "," + start->data;
			}

			else if (start->leftChild != nullptr && start->rightChild == nullptr)
			{
				return PpostOrderList(start->leftChild) + "," + start->data;
			}

			else if (start->leftChild != nullptr && start->rightChild != nullptr)
			{
				return PpostOrderList(start->leftChild) + "," + PpostOrderList(start->rightChild) + "," + start->data;
			}
		}

		//Private remove so that we don't have to pass a node originally
		bool Premove(string remove, avlNode*& start)
		{
			//If the tree is empty we definitely cannot remove anything from it
			if (root == nullptr)
			{
				return false;
			}
			//If we are at the end, we cannot traverse any farther and thus we cannot remove the node we wanted to
			else if (start == nullptr)
			{
				return false;
			}

			//If what we want to remove is less than the nodes data, go left
			else if (remove < start->data)
			{
				return this->Premove(remove, start->leftChild);
			}

			//If what we want to remove is greater than the nodes data, go right
			else if (remove > start->data)
			{
				return this->Premove(remove, start->rightChild);
			}

			//Now we have found the data
			else if (remove == start->data)
			{
				//Case 0: no kids: pass
				if (start->rightChild == nullptr && start->leftChild == nullptr)
				{
					//no kids so it is a leaf so we can simply delete it and point our pointer to null address.

					delete start;

					start = nullptr;

					return true;
				}

				//Case 1: only a left kid: pass
				else if (start->rightChild == nullptr && start->leftChild != nullptr)
				{
					//Steal left kid's data, its children, and then delete it

					avlNode* del = start->leftChild;

					start->data = del->data;

					start->leftChild = del->leftChild;

					start->rightChild = del->rightChild;

					delete del;

					del = nullptr;

					return true;
				}

				//Case 2: only a right kid: pass
				else if (start->rightChild != nullptr && start->leftChild == nullptr)
				{
					//Steal right kid's data, its children, and then delete it.

					avlNode* del = start->rightChild;

					start->data = del->data;

					start->leftChild = del->leftChild;

					start->rightChild = del->rightChild;

					delete del;

					del = nullptr;

					return true;
				}

				//Case 3 both a right kid and left kid: pass
				else if (start->rightChild != nullptr && start->leftChild != nullptr)
				{
					//Make a pointer to the node we are trying to delete's left child
					avlNode* swap = start->leftChild;

					//trailing pointer for swap to use for deletion later
					avlNode* swapTrail = start;

					//accumulator so that swapTrail can trail behind swap and skip an iteration
					int acc = 0;

					//Traverse to this child's right until we can't anymore
					//At this point there could be a left child or no children
					while (swap->rightChild != nullptr)
					{
						if (acc == 0)
						{
							swapTrail = start->leftChild;
						}

						else
						{
							swapTrail = swapTrail->rightChild;
						}

						swap = swap->rightChild;

						acc++;
					}

					//now we swap these two nodes data
					string tmp = swap->data;

					swap->data = start->data;

					start->data = tmp;

					//now we need to delete the node swap is pointing to

					//swap does not have a right child but does it have a left?
					if (swap->leftChild != nullptr)
					{
						//has a left child so we need to put it on the right or left of swaptrail depending on the size

						if (swapTrail->data > swap->data)
						{
							swapTrail->leftChild = swap->leftChild;
						}

						else
						{
							swapTrail->rightChild = swap->leftChild;
						}

						delete swap;

						swap = nullptr;

						swapTrail = nullptr;

						return true;
					}

					else
					{
						//does not have a left child so we can simply delete this node and set the trail that pointed to it to nullptr

						delete swap;

						swap = nullptr;

						if (acc == 0)
						{
							swapTrail->leftChild = nullptr;
						}

						else
						{
							swapTrail->rightChild = nullptr;
						}

						swapTrail = nullptr;

						return true;
					}
				}
			}
		}

		//Private program clean up method
		void Preset(avlNode*& start)
		{
			if (start == nullptr)
			{
				return;
			}

			if (start->leftChild != nullptr)
			{
				Preset(start->leftChild);
			}

			if (start->rightChild != nullptr)
			{
				Preset(start->rightChild);
			}

			delete start;

			start = nullptr;
		}

		//Private node counter (beautiful code)
		int PnumNodes(avlNode* start)
		{
			//if the current node exists, we return one plus the recursive count of its right and left child
			return ((start == nullptr) ? 0 : 1 + ((start->leftChild == nullptr) ? 0 : PnumNodes(start->leftChild)) + ((start->rightChild == nullptr) ? 0 : PnumNodes(start->rightChild)));
		}

		//Update the height of a node and its children
		void PupdateHeight(avlNode*& start)
		{
			//Empty tree since we only pass the root
			if (start == nullptr) throw EmptyTreeException;

			//Update the left child first if there is one
			if (start->leftChild != nullptr)
			{
				PupdateHeight(start->leftChild);
			}

			//Update the right child second if there is one
			if (start->rightChild != nullptr)
			{
				PupdateHeight(start->rightChild);
			}

			//Now we can update this node's height since its kids are updated

			//if no kids
			if (start->leftChild == nullptr && start->rightChild == nullptr)
			{
				start->height = 1;
			}

			//Just left kid
			else if (start->leftChild != nullptr && start->rightChild == nullptr)
			{
				start->height = start->leftChild->height + 1;
			}

			//Just right kid
			else if (start->leftChild == nullptr && start->rightChild != nullptr)
			{
				start->height = start->rightChild->height + 1;
			}

			//if two kids
			else if (start->leftChild != nullptr && start->rightChild != nullptr)
			{
				start->height = max(start->leftChild->height, start->rightChild->height) + 1;
			}
		}

		//Max of a number function for calculating height
		int max(int x, int y)
		{
			return (x < y ? y : x);
		}

		//Calculate balance factors from bottom of tree up and perform rotations if needed
		void PdetermineRotations(avlNode* start)
		{
			//Empty tree since we only pass the root
			if (start == nullptr) throw EmptyTreeException;

			//Rotations on the left sub-tree first
			if (start->leftChild != nullptr)
			{
				PdetermineRotations(start->leftChild);
			}

			//Rotations on the right sub-tree second
			if (start->rightChild != nullptr)
			{
				PdetermineRotations(start->rightChild);
			}

			//Now rotations on the whole tree starting from the passed node

			int bf = balance(start);

			//Right rotate
			if (bf == 2 && balance(start->leftChild) == 1)
			{
				rightRotate(start);
			}

			//Left rotate
			else if (bf == -2 && balance(start->rightChild) == -1)
			{
				leftRotate(start);
			}

			//Left-right rotate
			else if (bf == 2 && balance(start->leftChild) == -1)
			{
				leftRotate(start->leftChild);
				rightRotate(start);
			}

			//Right-left rotate
			else if (bf == -2 && balance(start->rightChild) == 1)
			{
				rightRotate(start->rightChild);
				leftRotate(start);
			}

			PupdateHeight(root);
		}

		//Rotate start right
		void rightRotate(avlNode* start)
		{
			//init parent node
			avlNode* parentOfStart = nullptr;

			//init bool var to indicate positioning of start relative to parent
			bool rightOfParent = false;

			//find out if it was the root (if it has a parent)
			bool wasRoot = (start == root);

			//if it has a parent we need to find out its parent and the positioning of it
			if (start != root)
			{
				parentOfStart = getParent(start->data, root);

				(parentOfStart->data < start->data ? rightOfParent = true : rightOfParent = false);
			}

			//new head of our subtree
			avlNode* newRoot = start->leftChild;

			//starts left child is taken from the head of our subtree's right child
			start->leftChild = newRoot->rightChild;

			//our new head's right child is assigned to start
			newRoot->rightChild = start;

			//now we will reconnect the rest of the tree to our subtree if needed
			if (start != root && rightOfParent)
			{
				parentOfStart->rightChild = newRoot;
			}

			else if (start != root && !rightOfParent)
			{
				parentOfStart->leftChild = newRoot;
			}

			//if it was the root, we now update it with newRoot
			if (wasRoot)
			{
				root = newRoot;
			}
		}

		//Rotate start left (exact same code as right rotate except negated)
		void leftRotate(avlNode* start)
		{
			avlNode* parentOfStart = nullptr;

			bool leftOfParent = false;

			bool wasRoot = (start == root);

			if (start != root)
			{
				parentOfStart = getParent(start->data, root);

				(parentOfStart->data > start->data ? leftOfParent = true : leftOfParent = false);
			}

			avlNode* newRoot = start->rightChild;

			start->rightChild = newRoot->leftChild;

			newRoot->leftChild = start;

			if (start != root && leftOfParent)
			{
				parentOfStart->leftChild = newRoot;
			}

			else if (start != root && !leftOfParent)
			{
				parentOfStart->rightChild = newRoot;
			}

			if (wasRoot)
			{
				root = newRoot;
			}
		}

		//Get the parent of a node so that we can change its child
		avlNode* getParent(string data, avlNode* start)
		{
			if (root == nullptr)
			{
				throw EmptyTreeException;
			}

			else if (start->leftChild != nullptr && start->leftChild->data == data)
			{
				return start;
			}

			else if (start->rightChild != nullptr && start->rightChild->data == data)
			{
				return start;
			}

			else if (start->data > data)
			{
				return this->getParent(data, start->leftChild);
			}

			else if (start->data < data)
			{
				return this->getParent(data, start->rightChild);
			}
		}

		//Balance factor of a node method
		int balance(avlNode* start)
		{
			if (start->leftChild == nullptr && start->rightChild == nullptr)
			{
				return 0;
			}

			if (start->leftChild != nullptr && start->rightChild == nullptr)
			{
				return height(start->leftChild);
			}

			if (start->leftChild == nullptr && start->rightChild != nullptr)
			{
				return  (-1) * height(start->rightChild);
			}

			if (start->leftChild != nullptr && start->rightChild != nullptr)
			{
				return (height(start->leftChild) - height(start->rightChild));
			}
		}

		//Load a tree from a local file
		bool PLoadTree(string filename)
		{
			string currentLine = "";

			ifstream AVLLoad(filename + ".txt");

			getline(AVLLoad, currentLine);

			vector<string> rawData;

			stringstream stream(currentLine);

			string temp = "";

			//get the post order from the file and put it in the vector split at commas
			while (getline(stream, temp, ','))
			{
				rawData.push_back(temp);
			}

			//Create the root and assign it the value of the last element in the vector
			avlNode* newRoot = new avlNode(rawData.back());

			//Create a stack and push the root to it
			stack<avlNode*> constructionStack;

			constructionStack.push(newRoot);

			//Iterate backwards from length of the array-2 to 0
			for (vector<string>::reverse_iterator riter = ++rawData.rbegin(); riter != rawData.rend(); riter++)
			{
				//declare a pointer to a node current and assign it the value of vector[riter]
				avlNode* current = new avlNode(*riter);

				//declare pointers to a node temp and top
				avlNode* temp = nullptr;
				avlNode* top = nullptr;

				//loop while the stack is not empty
				while (!constructionStack.empty())
				{
					//assign top the value of stack.peek
					top = constructionStack.top();

					//if this condition is met, break from the while loop
					if (current->data >= top->data)
					{
						break;
					}

					//assign temp the value of top
					temp = top;

					//pop an element from the stack
					constructionStack.pop();
				}

				//if temp has a value assigned to it
				if (temp != nullptr)
				{
					//set temp's left to current
					temp->leftChild = current;
				}

				//otherwise
				else
				{
					//asign top the value of stack.peek
					top = constructionStack.top();

					//set top's right to current
					top->rightChild = current;
				}

				constructionStack.push(current);
			}

			//Assign this new root with all the children linked to it to the root of this true
			root = newRoot;

			//We were successfull so return true
			return true;
		}

	public:

		//EmptyTreeExcpetion number
		static const int EmptyTreeException = 117;

		//Empty constructor
		avlTree()
		{
			root = nullptr;
		}

		avlTree(avlNode* constructed)
		{
			root = constructed;
		}

		//Constructor with initial node data
		avlTree(string data)
		{
			root = new avlNode(data);
		}

		//Public search method
		bool search(string search)
		{
			return Psearch(search, root);
		}

		//Public insert method
		bool insert(string insert)
		{
			return Pinsert(insert, root);
		}

		//Public remove method
		bool remove(string remove)
		{
			return Premove(remove, root);
		}

		//Public inorderlisting method
		string inOrderList()
		{
			return PinOrderList(root);
		}

		//Public preorderlisting method
		string preOrderList()
		{
			return PpreOrderList(root);
		}

		//Public postorderlisting method
		string postOrderList()
		{
			return PpostOrderList(root);
		}

		//Public reset method
		void reset()
		{
			Preset(root);

			root = nullptr;
		}

		//Public num nodes method
		int numNodes()
		{
			return PnumNodes(root);
		}

		//Height of a node method
		int height(avlNode* start)
		{
			return (start == nullptr ? -1 : start->height);
		}

		//Public update height method
		void updateHeight()
		{
			PupdateHeight(root);
		}

		//Public core of AVL tree
		void determineRotations()
		{
			PdetermineRotations(root);
		}

		bool loadTree(string fileLoadFrom)
		{
			Preset(root);

			root = nullptr;

			return PLoadTree(fileLoadFrom);
		}
};