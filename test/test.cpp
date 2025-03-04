/*
#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <sstream>
#include <unordered_set>


#include "AVL.h"

using namespace std;

// the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.

// test case from starter file
TEST_CASE("Example Test Name - Change me!", "[flag]"){
	// instantiate any class members that you need to test here
	int one = 1;

	// anything that evaluates to false in a REQUIRE block will result in a failing test 
	REQUIRE(one == 1); // fix me!

	// all REQUIRE blocks must evaluate to true for the whole test to pass
	REQUIRE(true); // also fix me!
}




// test case from starter file
TEST_CASE("Test 2", "[flag]"){
	// you can also use "sections" to share setup code between tests, for example:
	int one = 1;

	SECTION("num is 2") {
		int num = one + 1;
		REQUIRE(num == 2);
	};

	SECTION("num is 3") {
		int num = one + 2;
		REQUIRE(num == 3);
	};

	// each section runs the setup code independently to ensure that they don't affect each other
}

// you must write 5 unique, meaningful tests for credit on the testing portion of this project!

// the provided test from the template is below.


TEST_CASE("Example BST Insert", "[flag]"){
		AVLTree tree;   // Create a Tree object
		tree.insert(3);
		tree.insert(2);
		tree.insert(1);
		std::vector<int> actualOutput = tree.getInorder();
		std::vector<int> expectedOutput = {1, 2, 3};
		REQUIRE(expectedOutput.size() == actualOutput.size());
		REQUIRE(actualOutput == expectedOutput);

}


// capture cout output
string getOutput(function<void()> func) {
	ostringstream oss;
	streambuf* oldCout = std::cout.rdbuf(oss.rdbuf());
	func();
	cout.rdbuf(oldCout);
	return oss.str();
}

TEST_CASE("insert (valid cases)") {
	AVLTree tree;

	REQUIRE(getOutput([&]() { tree.insert("Timmy Loos", "12345678"); }) == "successful\n");
	REQUIRE(getOutput([&]() { tree.insert("Bob Poop", "87654321"); }) == "successful\n");
	REQUIRE(getOutput([&]() { tree.insert("Charlie Brown", "23456789"); }) == "successful\n");
}

TEST_CASE("insert (duplicate id)") {
	AVLTree tree;
	tree.insert("Timmy Loos", "12345678");

	REQUIRE(getOutput([&]() { tree.insert("Another Name", "12345678"); }) == "unsuccessful\n");
}

TEST_CASE("insert (invalid ids)") {
	AVLTree tree;

	REQUIRE(getOutput([&]() { tree.insert("David", "12345"); }) == "unsuccessful\n");
	REQUIRE(getOutput([&]() { tree.insert("Eve", "abcdefgh"); }) == "unsuccessful\n");
	REQUIRE(getOutput([&]() { tree.insert("Frank", "1234567a"); }) == "unsuccessful\n");
}

TEST_CASE("insert (invalid names)") {
	AVLTree tree;

	REQUIRE(getOutput([&]() { tree.insert("John123", "23456789"); }) == "unsuccessful\n");
	REQUIRE(getOutput([&]() { tree.insert("Jane_Doe", "34567890"); }) == "unsuccessful\n");
}

TEST_CASE("insert (ensuring AVL balance)") {
	AVLTree tree;

	tree.insert("A", "10000000");
	tree.insert("B", "20000000");
	tree.insert("C", "30000000");

	// check root node to see if balancing worked
	REQUIRE(getOutput([&]() { tree.insert("D", "40000000"); }) == "successful\n");
}


TEST_CASE("insert basic functionality") {
	AVLTree tree;

	tree.insert("Timmy", "12345678");
	tree.insert("Bob", "87654321");
	tree.insert("Charlie", "23456789");

	// expected inorder traversal
	std::vector<std::string> expectedOutput = {"Timmy", "Charlie", "Bob"};

	std::vector<std::string> actualOutput = tree.getInorder();

	REQUIRE(expectedOutput.size() == actualOutput.size());
	REQUIRE(actualOutput == expectedOutput);
}

TEST_CASE("traversals") {
	AVLTree tree;
	tree.insert("Charlie", "34567890");
	tree.insert("Timmy", "12345678");
	tree.insert("Bob", "23456789");

	REQUIRE(getOutput([&]() { tree.printInorder(); }) == "Timmy, Bob, Charlie\n");
	REQUIRE(getOutput([&]() { tree.printPreorder(); }) == "Bob, Timmy, Charlie\n");
	REQUIRE(getOutput([&]() { tree.printPostorder(); }) == "Timmy, Charlie, Bob\n");
}

TEST_CASE("search by id") {
	AVLTree tree;
	tree.insert("Timmy", "12345678");
	tree.insert("Bob", "87654321");

	REQUIRE(getOutput([&]() { tree.searchID("12345678"); }) == "Timmy\n");
	REQUIRE(getOutput([&]() { tree.searchID("87654321"); }) == "Bob\n");
	REQUIRE(getOutput([&]() { tree.searchID("99999999"); }) == "unsuccessful\n");
}


TEST_CASE("search by name") {
	AVLTree tree;
	tree.insert("Timmy", "12345678");
	tree.insert("Bob", "87654321");
	tree.insert("Timmy", "56781234"); // duplicate name with different id

	std::string output = getOutput([&]() { tree.searchNAME("Timmy"); });

	REQUIRE((output == "12345678\n56781234\n" || output == "56781234\n12345678\n"));

	REQUIRE(getOutput([&]() { tree.searchNAME("Bob"); }) == "87654321\n");
	REQUIRE(getOutput([&]() { tree.searchNAME("Charlie"); }) == "unsuccessful\n");
}




TEST_CASE("remove by id") {
	AVLTree tree;
	tree.insert("Timmy", "12345678");
	tree.insert("Bob", "87654321");
	tree.insert("Charlie", "34567890");

	REQUIRE(getOutput([&]() { tree.remove("87654321"); }) == "successful\n");
	REQUIRE(getOutput([&]() { tree.searchID("87654321"); }) == "unsuccessful\n");
	REQUIRE(getOutput([&]() { tree.remove("99999999"); }) == "unsuccessful\n");
}

TEST_CASE("remove by inorder pos") {
	AVLTree tree;
	tree.insert("Timmy", "12345678");
	tree.insert("Bob", "87654321");
	tree.insert("Charlie", "34567890");

	REQUIRE(getOutput([&]() { tree.printInorder(); }) == "Timmy, Charlie, Bob\n");

	// removing parent node
	REQUIRE(getOutput([&]() { tree.removeInorder(1); }) == "successful\n");
	REQUIRE(getOutput([&]() { tree.printInorder(); }) == "Timmy, Bob\n");

	// out of bounds check
	REQUIRE(getOutput([&]() { tree.removeInorder(5); }) == "unsuccessful\n");
}

TEST_CASE("print level count") {
	AVLTree tree;

	REQUIRE(getOutput([&]() { tree.printLevelCount(); }) == "0\n"); // empty tree

	tree.insert("Timmy", "12345678");
	REQUIRE(getOutput([&]() { tree.printLevelCount(); }) == "1\n");

	tree.insert("Bob", "87654321");
	REQUIRE(getOutput([&]() { tree.printLevelCount(); }) == "2\n");

	tree.insert("Charlie", "34567890");
	REQUIRE(getOutput([&]() { tree.printLevelCount(); }) == "2\n"); // tree rebalances, still 2

	tree.insert("David", "23456789");
	REQUIRE(getOutput([&]() { tree.printLevelCount(); }) == "3\n");
}

TEST_CASE("rotations (every case)") {
	AVLTree tree;

	tree.insert("A", "10000001");
	tree.insert("B", "10000002");
	tree.insert("C", "10000003"); // right rotation on A

	tree.insert("D", "10000004");
	tree.insert("E", "10000005"); // left rotation on C

	tree.insert("G", "10000007");
	tree.insert("F", "10000006"); // LR Rotation on E

	tree.insert("I", "10000009");
	tree.insert("H", "10000008"); // RL Rotation on G

	REQUIRE(getOutput([&]() { tree.printLevelCount(); }) == "4\n");
}

TEST_CASE("deletion (0, 1, 2) childs") {
	AVLTree tree;

	tree.insert("A", "10000001");
	tree.insert("B", "10000002");
	tree.insert("C", "10000003");

	// deleting a leaf node
	REQUIRE(getOutput([&]() { tree.remove("10000003"); }) == "successful\n");

	tree.insert("D", "10000004");
	tree.insert("E", "10000005");
	tree.insert("F", "10000006");

	// deleting node with one child
	REQUIRE(getOutput([&]() { tree.remove("10000002"); }) == "successful\n");

	// deleting node with two children
	REQUIRE(getOutput([&]() { tree.remove("10000004"); }) == "successful\n");

	REQUIRE(getOutput([&]() { tree.printInorder(); }) == "A, E, F\n");
}


TEST_CASE("bulk insert and remove") {
	AVLTree tree;
	std::unordered_set<std::string> insertedUFIDs;
	std::vector<std::string> ids;

	for (int i = 1; i <= 100; i++) {
		std::string name = "Student";
		std::string ufid = std::to_string(10000000 + i);
		if (ufid.length() > 8) ufid = ufid.substr(0, 8);

		if (insertedUFIDs.count(ufid) == 0) {
			REQUIRE(getOutput([&]() { tree.insert(name, ufid); }) == "successful\n");
			insertedUFIDs.insert(ufid);
			ids.push_back(ufid);
		}
	}

	// remove 10 random nodes
	for (int i = 0; i < 10; i++) {
		REQUIRE(getOutput([&]() { tree.remove(ids[i]); }) == "successful\n");
	}

	REQUIRE(getOutput([&]() { tree.printLevelCount(); }) != "0\n");
}

*/

