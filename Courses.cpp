#include <iostream>
#include <vector>
#include "CSVparser.h"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// Structure to hold course information 
struct Course {
    string number; // unique identifier
    string title;
    vector<string> prerequisites;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node() {
        left = nullptr;
        right = nullptr;
    }

    Node(Course c) {
        course = c;
        left = nullptr;
        right = nullptr;
    }

};
//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Course course);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);
    Node* removeNode(Node* node, string number);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PreOrder();
    void PostOrder();
    void Insert(Course course);
    void Remove(string number);
    Course Search(string number);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    //initialized housekeeping variables
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    // In order root
    // call inOrder fuction and pass root
    this->inOrder(root);
}


void BinarySearchTree::PostOrder() {
    // postOrder root
    this->postOrder(root);

}

void BinarySearchTree::PreOrder() {
    // preOrder root
    this->preOrder(root);
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // inserting a course into the tree
      // root is equal to new node course
    if (root == nullptr) {
        root = new Node(course);
    }
    else {
        this->addNode(root, course);
    }

}

/**
 * Remove a course
 */
void BinarySearchTree::Remove(string number) {
    // removing a course from the tree
    // remove node root course
    //this->removeNode(root, number);
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string number) {
    // searching the tree for a course
    // set current node equal to root

    Node* current = root;
    while (current != nullptr) {
        if (current->course.number.compare(number) == 0) {
            return current->course;
        }
        if (number.compare(current->course.number) < 0) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    Course course;
    return course;
}


void BinarySearchTree::addNode(Node* node, Course course) {
    // inserting a bid into the tree
    // if node is larger then add to left
    if (node->course.number.compare(course.number) > 0) {
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        else {
            this->addNode(node->left, course);
        }
    }
    else {
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        else {
            this->addNode(node->right, course);
        }
    }
}

void BinarySearchTree::inOrder(Node* node) {
    //Pre order root
    //output course number, title, and prerequisite/s (if needed)
    if (node != nullptr) {
        inOrder(node->left);

        cout << "Course number:" << node->course.number << endl;
        cout << "Course title:" << node->course.title << endl;
        if (node->course.prerequisites.size() > 0) {
            cout << "Prerequisites:";
            for (int i = 0; i < node->course.prerequisites.size(); i++) {
                cout << node->course.prerequisites[i];
                if (i != node->course.prerequisites.size() - 1)
                    cout << ", ";
            }

        }
        cout << endl;


        inOrder(node->right);
    }
}
void BinarySearchTree::postOrder(Node* node) {
    // Pre order root
    //output course number, title, and prerequisite/s (if needed)
    if (node != nullptr)
    {
        postOrder(node->left);
        postOrder(node->right);
        cout << "Course number:" << node->course.number << endl;
        cout << "Course title:" << node->course.title << endl;
        if (node->course.prerequisites.size() > 0) {
            cout << "Prerequisites:";
            for (int i = 0; i < node->course.prerequisites.size(); i++) {
                cout << node->course.prerequisites[i];
                if (i != node->course.prerequisites.size() - 1)
                    cout << ", ";
            }

        }
        cout << endl;
    }

}

void BinarySearchTree::preOrder(Node* node) {
    //Pre order root
    //output course number, title, and prerequisite/s (if needed)
    if (node != nullptr) {

        postOrder(node->left);
        postOrder(node->right);
        cout << "Course number:" << node->course.number << endl;
        cout << "Course title:" << node->course.title << endl;
        if (node->course.prerequisites.size() > 0) {
            cout << "Prerequisites:";
            for (int i = 0; i < node->course.prerequisites.size(); i++) {
                cout << node->course.prerequisites[i];
                if (i != node->course.prerequisites.size() - 1)
                    cout << ", ";
            }
        }
        cout << endl;
    }
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Displays the course information to the console (std::out)
 **/
void displayCourse(Course course) {
    cout << "Course number:" << course.number << endl;
    cout << "Course title:" << course.title << endl;
    if (course.prerequisites.size() > 0) {
        cout << "Prerequisites:";
        for (int i = 0; i < course.prerequisites.size(); i++) {
            cout << course.prerequisites[i];
            if (i != course.prerequisites.size() - 1)
                cout << ", ";
        }
    }
    cout << endl;
    return;
}

/**
 * Loads a CSV file containing courses into a container
 */
void loadCourses(string csvPath, BinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initializes the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Data Structure
            Course course;
            course.number = (file[i][0]);
            course.title = file[i][1];
            int columnCount = file.getRow(i).size();
            for (int j = 2; j < columnCount; j++) {
                course.prerequisites.push_back(file[i][j]);
            }


            //cout << "Course: " << course.title << ", Prerequisite: " << course.prerequisite << endl;

            // push course to the end
            bst->Insert(course);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // processes command line arguments
    string csvPath, numberKey;
    cout << "Enter the name of the data file:";
    cin >> csvPath;



    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = nullptr;
    Course course;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Data Structure" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Print course" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst = new BinarySearchTree();

            // This method loads the courses
            loadCourses(csvPath, bst);

            //cout << bst->Size() << " courses read" << endl;

            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            cout << "Enter the course number to search:";
            cin >> numberKey;

            course = bst->Search(numberKey);

            if (!course.number.empty()) {
                displayCourse(course);
            }
            else {
                cout << "course number " << numberKey << " not found." << endl;
            }

            break;

        }
    }

    cout << "Good bye." << endl;

    return 0;
}