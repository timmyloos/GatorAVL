#include <iostream>
#include <sstream>
#include "AVL.h"
#include <iomanip>
using namespace std;

// cited from Project 1 Breakdown Video
int main() {
	AVLTree tree;
	string numCommands;
	getline(cin, numCommands);  // read the number of commands

	for (int i = 0; i < stoi(numCommands); i++) {
		string commandLine;
		getline(cin, commandLine);  // read each command line

		istringstream ss(commandLine);
		string command;
		ss >> command;  // extract command type

		if (command == "insert") {
			string name, ufid;
			ss >> quoted(name) >> ufid;  // read quoted name and UFID
			tree.insert(name, ufid);
		}
		else if (command == "remove") {
			string ufid;
			ss >> ufid;
			tree.remove(ufid);
		}
		else if (command == "removeInorder") {
			int N;
			ss >> N;
			tree.removeInorder(N);
		}
		else if (command == "search") {
			string identifier;
			ss >> ws; // ignore whitespace
			if (ss.peek() == '"') {  // if it's a quoted name
				string name;
				ss >> quoted(name);
				tree.searchNAME(name);
			} else {  // if it's a UFID
				string ufid;
				ss >> ufid;
				tree.searchID(ufid);
			}
		}
		else if (command == "printInorder") {
			tree.printInorder();
		}
		else if (command == "printPreorder") {
			tree.printPreorder();
		}
		else if (command == "printPostorder") {
			tree.printPostorder();
		}
		else if (command == "printLevelCount") {
			tree.printLevelCount();
		}
		else {
			cout << "unsuccessful" << endl;
		}
	}

	return 0;
}
