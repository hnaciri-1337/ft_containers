#ifndef FILE_HPP
#define FILE_HPP
#include <iostream>
#include <string>
#include "includes/includes.hpp"
using namespace std;
 
 
struct Trunk
{
    Trunk *prev;
    string str;
 
    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};
 
void showTrunks(Trunk *p)
{
    if (p == nullptr) {
        return;
    }
 
    showTrunks(p->prev);
    std::cout << p->str;
}

template <class key, class val, class alloc>
void printTree(ft::Node<key, val, alloc>* root, Trunk *prev, bool isLeft)
{
    if (root == nullptr) {
        return;
    }
 
    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);
 
    printTree(root->right, trunk, true);
 
    if (!prev) {
        trunk->str = "———";
    }
    else if (isLeft)
    {
        trunk->str = ".———";
        prev_str = "   |";
    }
    else {
        trunk->str = "`———";
        prev->str = prev_str;
    }
 
    showTrunks(trunk);
    if (root->black)
        cout << " \033[32m" << root->value->first << "\033[0m" << endl;
    else
        cout << " \033[31m" << root->value->first << "\033[0m" << endl;
    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";
    printTree(root->left, trunk, false);
    free (trunk);
}
#endif
