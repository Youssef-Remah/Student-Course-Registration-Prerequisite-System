#include"courseTree.h"


//constructor   //we build our tree when the constructor is called
CourseTree::CourseTree() {
	root = NULL;
	constructTreeFromDataSource();
}






	void CourseTree:: preRequisiteChecking() {


		//printing messages and taking input
		cout << "Enter the courses which you already studied: (press Enter when done) \n";
		vector<string> takenCourses = readCoursesInput();

		cout << "Enter the courses that you want to study: (press Enter when done) \n";
		vector<string> wantedCourses = readCoursesInput();
		for (string course : takenCourses) {//checking whether a taken coursename exists in the wanted courses container or not, if exists then erase it
			auto it = find(wantedCourses.begin(), wantedCourses.end(), course);
			if (it != wantedCourses.end())
				wantedCourses.erase(it);
		}
		//creating a container of only codes of courses we want to check
		vector<string> wantedCoursesCodes;
		for (string course : wantedCourses) {
			wantedCoursesCodes.push_back(course.substr(0, 3));
		}

		vector<string> okCourses;

		// we traverse through the tree once looking for taken courses, when we find one , we check if its left or right is one of the wanted courses , if yes we add it to the ok list and remove it from the wanted list 
		//we stop when we have emtpied our wanted list properly or checked all courses in taken list 
		//by the end , ok courses are in ok list , and the ones remaining in wantedcourses list are the bad courses

		queue<BinaryTreeNode*> q;
		q.push(root);
		while (q.size() != 0 && !wantedCourses.empty() && !takenCourses.empty()) {
			BinaryTreeNode* node = q.front();
			q.pop();
			//when we find one of the taken courses we check its left and right if they match one of our wanted courses , if yes we add that to ok list and delete it form wanted list

			for (vector<string>::iterator it = takenCourses.begin(); it != takenCourses.end(); ++it) { //string course : takenCourses

				string courseCode = it->substr(0, 3);
				if (node->data == courseCode)
				{
					if (node->left) {

						auto itr = find(wantedCoursesCodes.begin(), wantedCoursesCodes.end(), node->left->data);//searching for child in taken course
						if (itr != wantedCoursesCodes.end()) {//removing child from wanted and moving it to ok
							okCourses.push_back(wantedCourses[(itr - wantedCoursesCodes.begin())]);
							wantedCourses.erase(wantedCourses.begin() + (itr - wantedCoursesCodes.begin()));
							wantedCoursesCodes.erase(itr);

						}
					}
					if (node->right) {
						auto itr = find(wantedCoursesCodes.begin(), wantedCoursesCodes.end(), node->right->data);//searching for child in taken course

						if (itr != wantedCoursesCodes.end()) {//removing child from wanted and moving it to ok
							okCourses.push_back(wantedCourses[(itr - wantedCoursesCodes.begin())]);
							wantedCourses.erase(wantedCourses.begin() + (itr - wantedCoursesCodes.begin()));
							wantedCoursesCodes.erase(itr);
						}
					}
					takenCourses.erase(it);
					break;
				}

			}
			//traversing breadth first
			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
		}

		cout << "ok courses are :\n";
		for (string course : okCourses) {
			cout << course << endl;
		}
		cout << "bad courses are :\n";
		for (string course : wantedCourses) {
			cout << course << endl;
		}
	}


	void CourseTree:: print() {
		queue<BinaryTreeNode*> q;
		q.push(root);
		while (q.size() != 0) {
			BinaryTreeNode* node = q.front();
			q.pop();
			cout << node->data << " ";
			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);

		}

	}


	//constructing our tree by adding values from the file "DataSource" , we hard coded the name since it is in the directory
	void CourseTree::constructTreeFromDataSource() {


		//reading our data from a csv file with name "DataSource.csv" this file will be in the directory, feel free to edit it in notepad but remember it is a comma separated file
		fstream fileCSV;
		string line;
		fileCSV.open("DataSource.csv", ios::in); // if we use ('r') the file is overwritten , must use input stream in

		//we read line by line
		while (getline(fileCSV, line)) {
			//fastest way to split the line into 2 would be by determining the comma location and splitting the string into 2 substrings
			int commaLocation;
			for (int i = 0; i < line.size(); i++)
				if (line[i] == ',') {
					commaLocation = i;
					break;
				}
			//following variables holds the code of courses to add and their preRequisits respectively 
			//we know the code will always be a 3 digit number so we take advantage like a boss

			string courseCode = line.substr(0, 3);
			string preReqCode = line.substr((commaLocation + 1), 3);

			//searching for the place to add the children as per task specifications

			//if the prerequisite code is not a number ie a word like None or none or NA , it will be made the root
			if (!(preReqCode[0] >= 48 && preReqCode[0] <= 57))
				root = new BinaryTreeNode(courseCode);

			else // in our file our courses must be arranged in logical order , meaning a child won't be entered before its parent so by locating the parent we can add children to it
			{
				//look for parent 
				BinaryTreeNode* parent = breadthFirstSearch(preReqCode);

				// first child is always the left , if left is occupied then add to right as per assignment
				if (parent->left == NULL)
					parent->left = new BinaryTreeNode(courseCode);
				else
					parent->right = new BinaryTreeNode(courseCode);
			}

		}
		fileCSV.close();



	}


	//helping methods

	// since nodes aren't sorted in the usual way , when we search for a node location we will use breadth first search 
	// we can only search an unsorted tree through brute force , we think bf search will work best in this scenario
	BinaryTreeNode* CourseTree:: breadthFirstSearch(string nodeToFind) {
		queue<BinaryTreeNode*> q;
		q.push(root);
		while (q.size() != 0) {
			BinaryTreeNode* node = q.front();
			if (nodeToFind == node->data)
				return node;
			q.pop();
			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
		}
		return NULL;

	}

	//read any input from user and store it for use
	vector<string> CourseTree::readCoursesInput() {// in order to be able to take infinite input , we keep reading lines until the user presses Enter twice(enterend an empty line)
		vector<string> allInput;
		string input = "placeHolder";
		while (!input.empty()) {
			getline(cin, input);
			//validating course code to be safe , making sure first 3 characters are numbers
			if ((input[0] >= 48 && input[0] <= 57) && (input[1] >= 48 && input[1] <= 57) && (input[2] >= 48 && input[2] <= 57)) {
				if (input[input.size() - 1] == '\r' || input[input.size() - 1] == '\n')
					input.erase(input.size() - 1);
				allInput.push_back(input);
			}
			else if (!input.empty())
				cout << "Last input was invalid , please enter it again \n";

		}
		return allInput;
	}