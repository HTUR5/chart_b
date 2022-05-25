#include "OrgChart.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <list>

using namespace std;
using namespace ariel;

    OrgChart::OrgChart() {
        this->root = nullptr;
    }

    OrgChart::~OrgChart() {
        (*this).free_chart(this->root);
    }
    
    OrgChart& OrgChart::add_root(const string &name) {
        if (name.empty()) {
            throw invalid_argument("the string is not illegal");
        }
        if(this->root != nullptr) {
            (*this->root).set_name(name);
        } else {
            this->root = new Node(name);
        }
        return *this;
    }

    OrgChart& OrgChart::add_sub(const string& dad, const string& son) {
        if (dad.empty() || son.empty()) {
            throw invalid_argument("the string is not illegal");
        }
        if (this->root == nullptr) {
            throw invalid_argument("enter a root first");
        }
        //search the dad node and add the son to its childs
        if(!search_dad(this->root ,dad,son)) {
            throw invalid_argument("the dad is not exist");
        }
        return *this;
    }

    bool OrgChart::search_dad(Node* root, const string& dad, const string& son) {
        if((*root).get_name()==dad){
            Node* new_son = new Node(son);
            (*root).add_child(new_son);
            return true;
        }
        for (size_t i = 0; i < (*root).get_childs().size(); i++) {
            if (search_dad( (*root).get_childs().at(i), dad, son)) {
                return true;
            }
        }
        return false;
    }

    ostream& ariel::operator<<(ostream& os, const OrgChart &orgChart) {
        return os;
    }

    OrgChart::Iterator OrgChart::begin_level_order() {
        if (this->root == nullptr) {
            throw invalid_argument("the chart is empty, enter a root first");
        }
        return Iterator{1, root};    
    }

    OrgChart::Iterator OrgChart::end_level_order() {
        if (this->root == nullptr) {
            throw invalid_argument("the chart is empty, enter a root first");
        }
        return Iterator{1, nullptr};    
    }

    OrgChart::Iterator OrgChart::begin_preorder() {
        if (this->root == nullptr) {
            throw invalid_argument("the chart is empty, enter a root first");
        }
        return Iterator{3, root};    
    }
    
    OrgChart::Iterator OrgChart::end_preorder() {
        if (this->root == nullptr) {
            throw invalid_argument("the chart is empty, enter a root first");
        }
        return Iterator{3, nullptr}; 
    }

    OrgChart::Iterator OrgChart::begin_reverse_order() {
        if (this->root == nullptr) {
            throw invalid_argument("the chart is empty, enter a root first");
        }
        return Iterator{2, this->root};  
    }
    
    OrgChart::Iterator OrgChart::reverse_order() {
        if (this->root == nullptr) {
            throw invalid_argument("the chart is empty, enter a root first");
        }
        return Iterator{2, nullptr};  
    }

    OrgChart::Iterator OrgChart::begin() {
        if (this->root == nullptr) {
            throw invalid_argument("the chart is empty, enter a root first");
        }
        return Iterator{1, root};
    }

    OrgChart::Iterator OrgChart::end() {
        if (this->root == nullptr) {
            throw invalid_argument("the chart is empty, enter a root first");
        }
        return Iterator{1, nullptr};
    }

    void OrgChart::Iterator::build_level(Node* root) {
        vector<Node*> temp;
        temp.push_back(root);
        while(!temp.empty()){ 
            Node* curr =  temp[0];
            this->itList.push_back(curr); 
            for(unsigned long j = 0; j < (*curr).get_childs().size(); j++){
                temp.push_back((*curr).get_childs().at(j));
            }
            temp.erase(temp.begin());
        }  
    }

    void OrgChart::Iterator::build_reverse(Node* root) {
        vector<Node*> temp;
        temp.push_back(root);
        int sizeVector = temp.size();  
        for(unsigned int i= 0;i<sizeVector;i++){
            Node* curr =  temp[i];
            for(int  j = (int)(*curr).get_childs().size()-1; j >= 0; j--) {
                temp.push_back((*curr).get_childs().at((unsigned)j));
            }
            sizeVector = temp.size();   
        } 
        for(int i = (int)temp.size()-1; i >= 0; i--) {
            itList.push_back(temp.at((unsigned)i));
        }
    }

    void OrgChart::Iterator::build_preorder(Node* root) {
        this->itList.push_back(root);
        unsigned int vecSize = (*root).get_childs().size();
        for(unsigned int i=0; i<vecSize; i++) {
            Node* curr = (*root).get_childs().at(i);
            build_preorder(curr);
        }
    }

    void OrgChart::free_chart(Node *root) {
        if (this->root == nullptr) { 
            return;
        }
        if (!this->root->get_childs().empty()) {
            for (unsigned int i = 0; i < root->get_childs().size(); i++) {
                free_chart(root->get_childs()[i]);
            }
        }
        delete root;
    }
    