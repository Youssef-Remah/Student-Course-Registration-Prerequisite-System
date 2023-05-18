#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>


using namespace std;

class BinaryTreeNode
{
public:
	//data members
	string data; //no need to make it generic since course codes are whole numbers
	BinaryTreeNode* left;
	BinaryTreeNode* right;

	//constructors
	BinaryTreeNode(string dataIn, BinaryTreeNode* leftIn = 0, BinaryTreeNode* rightIn = 0) {
		data = dataIn;
		left = leftIn;
		right = rightIn;
	};
};

//we don't follow the classic way of sorting so the class needs a special way of adding data according to whats provided in task 
// Binary tree class but has specific ways of adding nodes and specific methods for our task
class CourseTree
{
public:

	//constructor   
	CourseTree();

	//public mehtods

	void preRequisiteChecking();
	
	//testing purposes
	void print();

	

private:

	//constructing our tree by adding values from the file "DataSource" , we hard coded the name since it is in the directory
	void constructTreeFromDataSource();



	//data members
	BinaryTreeNode* root;

	//helping methods

	//to find specific nodes 
	BinaryTreeNode* breadthFirstSearch(string nodeToFind);

	//read any input from user and store it for use
	vector<string> readCoursesInput();

};