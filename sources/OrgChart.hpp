#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Node.hpp"


using namespace std;


namespace ariel {

    class OrgChart{
        
        private:

            Node* root; 
                
        public:
            OrgChart(OrgChart&) = default;
            OrgChart(OrgChart&&) = default;
            OrgChart();
            ~OrgChart();   
            OrgChart &operator=(OrgChart const &other) = default;
            OrgChart &operator=(OrgChart &&other) = default;
            friend ostream& operator<<(ostream& os, const OrgChart &orgChart);
            OrgChart& add_root(const string &name);
            OrgChart& add_sub(const string& dad_name, const string& son_name);
            bool search_dad(Node* root, const string& dad, const string& son);
            void free_chart(Node *root);

        
        class Iterator{
            
            private:
                Node* curr;
                vector<Node*> itList;
            
            public:
                
                //the constructor get mode and pointer and build a tree 
                //which begin in the pointer in some order according to the mode
                Iterator(int chooseOrder, Node *pointer = nullptr) {
                    if (pointer != nullptr) {
                        switch (chooseOrder) {
                            case 1:  //level-order
                                build_level(pointer);
                                break;
                            case 2: //reverse-level-order
                                build_reverse(pointer);
                                break;
                            case 3: //preorder
                                build_preorder(pointer);
                                break;
                        }
                        this->curr = itList.at(0);
                        itList.erase(itList.begin());
                    } else {
                        this->curr = nullptr;
                    }
                }

                //this functions build the itList according to the order
                void build_level(Node* root);
                void build_reverse(Node* root);
                void build_preorder(Node* root);

                bool operator!=(const Iterator& it) {
                    return this->curr != it.curr;
                }

                bool operator==(const Iterator& it) {
                    return this->curr == it.curr;
                }

                string operator*() {
                    return (*this->curr).get_name(); 
                }

                Iterator operator++(int) {
                    Iterator tmp = *this;
                    return tmp;
                }

                Iterator& operator++() {
                    if (!itList.empty()) {
                        this->curr = itList.at(0);
                        itList.erase(itList.begin());
                    }
                    else {
                        this->curr = nullptr;
                    }
                    return *this;                
                }

                string* operator->() {
                    return &curr->_name;
                }

            };
            
            //orgChart functions
            Iterator begin_reverse_order();
            Iterator reverse_order();
            Iterator begin_level_order();
            Iterator end_level_order();
            Iterator begin_preorder();
            Iterator end_preorder();
            Iterator begin();
            Iterator end();
    };
   
}