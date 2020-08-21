/*
Student Name: Nathan Cheshire
Student NetID: nvc29
Compiler Used: Visual Studio Community Edition 2019
Program Description:
This program is the fifth programming assignment for CSE2383; edit your AVL to allow loading of a tree from a file.
*/

#include <iostream>
#include <fstream>
#include "AVL.h"

using namespace std;

int main()
{
	avlTree ProgramTree;

	bool ProgramLoop = true;

	cout << "Choose an option" << endl;

	while (ProgramLoop)
	{
		try
		{
			bool ValidationLoop = true;

			string input = "";

			while (ValidationLoop)
			{
				cout << "[1] Insert a value\n[2] Search for value\n[3] Remove a value\n[4] Inorder listing\n[5] Preorder listing\n[6] Postorder listing\n[7] Create a new AVL\n[8] Save current AVL\n[9] Load AVL\n[10] Exit\n>> ";

				cin >> input;

				if (input != "1" && input != "2" && input != "3" && input != "4" && input != "5" && input != "6" && input != "7" && input != "8" && input != "9" && input != "10")
				{
					cout << "Error: invalid input" << endl;
				}

				else
				{
					ValidationLoop = false;
				}
			}

			//Search for a value
			if (input == "2")
			{
				string search = "";
				cout << "Enter the string you wish to search for\n>> ";
				cin >> search;

				bool found = ProgramTree.search(search);

				if (found)
				{
					cout << "The value \"" << search << "\" exists in the AVL." << endl;
				}

				else
				{
					cout << "The value \"" << search << "\" does not exist in the AVL." << endl;
				}
			}

			//Insert a value
			else if (input == "1")
			{
				string insert = "";
				cout << "Enter the string you wish to insert\n>> ";
				cin >> insert;

				bool success = ProgramTree.insert(insert);

				if (success)
				{
					cout << "The value \"" << insert << "\" was successfully inserted." << endl;
					cout << "Number of nodes: " << ProgramTree.numNodes() << endl;

					ProgramTree.updateHeight();

					ProgramTree.determineRotations();
				}

				else
				{
					cout << "The value \"" << insert << "\" already exists in the AVL. Consequently, nothing will happen." << endl;
				}
			}

			//Remove a value
			else if (input == "3")
			{
				string remove = "";
				cout << "Enter the string you wish to remove\n>> ";
				cin >> remove;

				bool found = ProgramTree.search(remove);

				if (!found)
				{
					cout << "The value \"" << remove << "\" does not exist in the AVL. Therefore, it cannot be removed." << endl;
				}

				else
				{
					bool success = ProgramTree.remove(remove);

					if (success)
					{
						cout << "The value \"" << remove << "\" was successfully removed." << endl;
						cout << "Number of nodes: " << ProgramTree.numNodes() << endl;

						ProgramTree.updateHeight();

						ProgramTree.determineRotations();
					}

					else
					{
						cout << "Error: the value \"" << remove << "\" was not removed." << endl;
					}
				}
			}

			//Inorder listing
			else if (input == "4")
			{
				cout << "Inorder listing: " << ProgramTree.inOrderList() << endl;
				cout << "Number of nodes: " << ProgramTree.numNodes() << endl;
			}

			//Preorder listing
			else if (input == "5")
			{
				cout << "Preorder listing: " << ProgramTree.preOrderList() << endl;
				cout << "Number of nodes: " << ProgramTree.numNodes() << endl;
			}

			//Postorder listing
			else if (input == "6")
			{
				cout << "Postorder listing: " << ProgramTree.postOrderList() << endl;
				cout << "Number of nodes: " << ProgramTree.numNodes() << endl;
			}

			//Create new AVL
			else if (input == "7")
			{
				cout << "Warning: creating a new tree will override the contents of the current tree.\nRemember, you could save the contents of the current tree by choosing option 8.\nAre you sure you wish to proceed (Y/N)?\n>> ";

				string confirm = "";

				cin >> confirm;

				if (confirm == "Y" || confirm == "y" || confirm == "yes" || confirm == "Yes")
				{
					cout << "Overriding current tree contents:" << endl;

					ProgramTree.reset();

					cout << "Finished: AVL reset to 0 nodes." << endl;
				}

				else
				{
					cout << "Very well; the contents of your current tree are safe for now." << endl;
				}
			}

			//Save current AVL to a file with a specified name
			else if (input == "8")
			{
				bool ValidName = false;

				string filename = "";

				while (!ValidName)
				{
					cout << "Enter the filename to store the contents of the current AVL to\n >> ";

					cin >> filename;

					if (filename == "")
					{
						cout << "Error: the proposed filename \"" << filename << "\" is not valid." << endl;
					}

					else
					{
						ValidName = true;
					}
				}

				ofstream saveTree;

				saveTree.open(filename + ".txt");

				saveTree << ProgramTree.postOrderList() << "\n";

				saveTree.close();

				cout << "The contents of your tree were successfully saved to the file \"" << filename << ".txt\"." << endl;
			}

			//Load
			else if (input == "9")
			{
				string confirm = "";

				bool loop = true;

				while (loop)
				{
					cout << "Warning: loading a previous tree will override the contents of the current tree.\nRemember, you could save the contents of the current tree by choosing option 8.\nAre you sure you wish to proceed (Y/N)?\n>> ";

					cin >> confirm;

					if (confirm == "N" || confirm == "n" || confirm == "no" || confirm == "No")
					{
						cout << "Very well; the contents of your current tree are safe for now." << endl;

						break;
					}

					else if (confirm == "Y" || confirm == "y" || confirm == "yes" || confirm == "Yes")
					{
						bool ValidName = false;

						string filename = "";

						while (!ValidName)
						{
							cout << "Enter the filename to load the AVL from\n >> ";

							cin >> filename;

							if (filename == "")
							{
								cout << "Error: the filename \"" << filename << "\" is not valid." << endl;
							}

							else
							{
								ValidName = true;
							}
						}

						bool success = ProgramTree.loadTree(filename);

						if (success)
						{
							ProgramTree.updateHeight();

							cout << "AVL Tree successfully loaded." << endl;

							cout << "Number of nodes: " << ProgramTree.numNodes() << endl;
						}

						else
						{
							cout << "Error: the tree was not loaded." << endl;
						}

						break;
					}

					else
					{
						cout << "Invalid option." << endl;
					}
				}
			}

			//Exit
			else if (input == "10")
			{
				//Exit program so we must clean up the tree
				ProgramTree.reset();

				exit(0);
			}

			else
			{
				//Something went horribly wrong if we are here so we should stop the program.
				ProgramLoop = false;
			}
		}

		//Catch an EmptyTreeExcpetion.
		catch (int e)
		{
			if (e == 117)
			{
				cout << "Empty Tree Exception" << endl;;
			}

			else
			{
				cout << "An unfortunate error occured" << endl;
			}
		}
	}
}