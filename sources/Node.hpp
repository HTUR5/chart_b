#pragma once
#include <iostream>
#include <string>
#include <vector>        

using namespace std;

namespace ariel {

/*
this class represent a person in the  organization tree.
each person has a name and a list of people under him in the tree.               
*/

class Node {
    
    //private:
    public:

        string _name;
        std::vector<Node*> _childs;

    //public:

        Node(const string &name) {
            this->_name = name;
        }

        string get_name() const{
            return this->_name;
        }

        void set_name(const string &name) {
            this->_name = name;
        }
       
        std::vector<Node*> get_childs() const{
            return this->_childs;
        }

        Node& add_child(Node* node) {
            this->_childs.push_back(node);
            return *this;
        }

        friend ostream &operator<<(ostream &output, Node *currNode) {
            output << currNode->_name;
            return output;
        }

};
}