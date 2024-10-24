#ifndef BST_H
#define BST_H

#include <iostream>
#include <memory>
#include <functional>
#include <iomanip>
#include <stack>

class BST
{

public:
    class Node
    {
    public:
        Node(int value, Node *left, Node *right);
        Node();
        Node(const Node &node);

        int value;
        Node *left;
        Node *right;

        friend bool operator<(BST::Node const &node, int value);
        friend bool operator<=(BST::Node const &node, int value);
        friend bool operator>=(BST::Node const &node, int value);
        friend bool operator>(BST::Node const &node, int value);
        friend bool operator==(BST::Node const &node, int value);
        friend bool operator<(int value, BST::Node const &node);
        friend bool operator<=(int value, BST::Node const &node);
        friend bool operator>=(int value, BST::Node const &node);
        friend bool operator>(int value, BST::Node const &node);
        friend bool operator==(int value, BST::Node const &node);
        friend std::ostream &operator<<(std::ostream &os, BST::Node &node);
    };
    BST();
    BST(BST &bst);
    BST(BST &&bst);
    Node *&get_root();
    void bfs(std::function<void(Node *&node)> func) const;
    size_t length();
    bool add_node(int value);
    Node **find_node(int value);
    Node **find_parrent(int value);
    Node **find_successor(int value);
    bool delete_node(int value);
    friend std::ostream &operator<<(std::ostream &os, BST &bst);
    BST operator=(BST &bst);
    BST operator=(BST &&bst);
    BST operator++(int x);
    BST &operator++();
    BST(std::initializer_list<int>);
    ~BST();

private:
    Node *root;
};

#endif // BST_H