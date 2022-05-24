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
            friend ostream& operator<<(ostream& out, const OrgChart &organization);
            OrgChart& add_root(const string &name);
            OrgChart& add_sub(const string& dad_name, const string& son_name);
            bool search_dad(Node* root, const string& dad, const string& son);
            void free_chart(Node *root);

        
        class Iterator{
            
            private:
                Node* curr;
                vector<Node*> itList;
            
            public:
                
                Iterator(int mode, Node *ptr = nullptr) {
                    if (ptr != nullptr) {
                        switch (mode) {
                            case 1:  
                                build_level(ptr);
                                break;
                            case 2:
                                build_reverse(ptr);
                                break;
                            case 3:
                                build_preorder(ptr);
                                break;
                        }
                        this->curr = itList.at(0);
                        itList.erase(itList.begin());
                    } else {
                        this->curr = nullptr;
                    }
                }

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