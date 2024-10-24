#include "bst.h"
#include <ostream>

BST::Node::Node(int _value, Node *_left, Node *_right) : value{_value}, left{_left}, right{_right}
{
}
BST::Node::Node() : value{0}, right{nullptr}, left{nullptr}
{
}
BST::Node::Node(const Node &node)
{
   value = node.value;
   left = node.left;
   right = node.right;
}
std::ostream &operator<<(std::ostream &os, BST::Node &node)
{
   os << "********************************************************************************" << std::endl;
   os << "adress of node: " << &node << std::endl;
   os << "adress of left: " << node.left << std::endl;
   os << "adress of right: " << node.right << std::endl;
   os << "Value is : " << node.value << std::endl;
   ;
   os << "********************************************************************************" << std::endl;
   return os;
}

bool operator<(BST::Node const &node, int value) { return node.value < value; }
bool operator<=(BST::Node const &node, int value) { return node.value <= value; }
bool operator>(BST::Node const &node, int value) { return node.value > value; }
bool operator>=(BST::Node const &node, int value) { return node.value >= value; }
bool operator==(BST::Node const &node, int value) { return node.value == value; }
bool operator<(int value, BST::Node const &node) { return value < node.value; }
bool operator<=(int value, BST::Node const &node) { return value <= node.value; }
bool operator>=(int value, BST::Node const &node) { return value >= node.value; }
bool operator>(int value, BST::Node const &node) { return value > node.value; }
bool operator==(int value, BST::Node const &node) { return node.value == value; }

BST::Node *&BST::get_root()
{
   return root;
}
bool BST::add_node(int value)
{
   if (!root)
   {
      root = new Node(value, nullptr, nullptr);
      return true;
   }
   auto *node{root};
   while (true)
   {

      if (node->value < value)
      {
         if (!node->right)
         {
            node->right = new Node(value, nullptr, nullptr);
            return true;
         }
         else
            node = node->right;
      }
      if (node->value > value)
      {
         if (!node->left)
         {
            node->left = new Node(value, nullptr, nullptr);
            return true;
         }
         node = node->left;
      }
      if (node->value == value)
         return false;
   }
}

void BST::bfs(std::function<void(Node *&node)> func) const
{
   std::stack<Node *> sta;
   sta.push(root);
   while (!sta.empty())
   {
      auto *node = sta.top();
      sta.pop();
      if (node != nullptr)
      {
         func(node);
         if (node->left)
            sta.push(node->left);
         if (node->right)
            sta.push(node->right);
      }
   }
}
size_t leng(BST::Node *node)
{
   if (!node->left && !node->right)
      return 1;
   else if (!node->left)
      return 1 + leng(node->right);
   else if (!node->right)
      return 1 + leng(node->left);
   return 1 + leng(node->left) + leng(node->right);
}
size_t BST::length()
{
   size_t a{0}, b{0};
   auto *node{root};
   if (!node)
   {
      return 0;
   }
   if (node->left)
      a = leng(node->left);
   if (node->right)
      b = leng(node->right);
   return 1 + a + b;
}
void pri(BST::Node &node)
{
   std::cout << &node << "     "
             << "=> Value:" << std::setw(11) << node.value
             << "   left:" << std::setw(11) << node.left
             << "   right:" << std::setw(11) << node.right << std::endl;
   if (node.left)
      pri(*node.left);
   if (node.right)
      pri(*node.right);
}
std::ostream &operator<<(std::ostream &os, BST &bst)
{
   auto roo = bst.get_root();
   std::cout << "********************************************************************************" << std::endl;
   pri(*roo);
   std::cout << "binary search tree size: " << bst.length() << std::endl;
   std::cout << "********************************************************************************" << std::endl;

   return os;
}

BST::Node **BST::find_node(int value)
{
   auto node{&root};
   while (true)
   {
      if ((*node)->value == value)
         return node;
      if ((*node)->value > value)
      {
         if (!(*node)->left)
            return nullptr;
         node = &(*node)->left;
      }
      else
      {
         if (!(*node)->right)
            return nullptr;
         node = &(*node)->right;
      }
   }
}

BST::Node **BST::find_parrent(int value)
{
   auto node{&root};
   if (value == (*node)->value)
   {
      return nullptr;
   }
   while (1)
   {
      if ((*node)->value > value)
      {
         if ((*node)->left->value == value)
            return node;
         else
         {
            if (!(*node)->left)
               return nullptr;
            node = &(*node)->left;
         }
      }
      else
      {
         if ((*node)->right->value == value)
            return node;
         {
            if (!(*node)->right)
               return nullptr;
            node = &(*node)->right;
         }
      }
   }
}
BST::Node **BST::find_successor(int value)
{
   auto node{&root};
   auto fin{find_node(value)};
   if (!(*fin)->left)
   {
      return fin;
   }
   else
   {
      fin = &(*fin)->left;
      while (1)
      {
         if (!(*fin)->right)
         {
            break;
         }
         fin = &(*fin)->right;
      }
   }
   return fin;
}
bool BST::delete_node(int value)
{
   auto node{find_node(value)};
   if (node == nullptr)
      return false;
   auto par1{find_parrent(value)};
   auto suc{find_successor(value)};
   auto par2{find_parrent((*suc)->value)};

   if ((*node)->left == nullptr && (*node)->right == nullptr)
   {
      if ((*node)->value > (*par1)->value)
         (*par1)->right = nullptr;
      else
         (*par1)->left = nullptr;
   }

   else if ((*node)->left == nullptr)
   {
      if ((*node)->value > (*par1)->value)
         (*par1)->right = (*node)->right;
      else
         (*par1)->left = (*node)->right;
   }

   else if ((*node)->right == nullptr)
   {
      if ((*node)->value > (*par1)->value)
         (*par1)->right = (*node)->left;
      else
         (*par1)->left = (*node)->left;
   }
   else if ((*node)->right && (*node)->left)
   {
      (*node)->value = (*suc)->value;
      if ((*suc)->value > (*par2)->value)
         (*par2)->right = nullptr;
      else
         (*par2)->left = nullptr;
   }
   return true;
}
BST::~BST()
{
   std::vector<Node *> nodes;
   bfs([&nodes](BST::Node *&node)
       { nodes.push_back(node); });
   for (auto &node : nodes)
      delete node;
}
BST::BST() : root{nullptr} {}
BST::BST(BST &bst) : root{nullptr}
{
   bst.bfs([this](BST::Node *&node)
           { this->add_node(node->value); });
}
BST::BST(BST &&bst)
{
   root = bst.root;
   bst.root = nullptr;
}
BST BST::operator=(BST &bst)
{
   bst.bfs([this](BST::Node *&node)
           { this->add_node(node->value); });
   return *this;
}
BST BST::operator=(BST &&bst)
{
   root = bst.root;
   bst.root = nullptr;
   return *this;
}
BST BST::operator++(int x)
{
   auto bfs{*this};
   this->bfs([this](BST::Node *&node)
             { node->value += 1; });
   return bfs;
}
BST &BST::operator++()
{
   this->bfs([this](BST::Node *&node)
             { node->value += 1; });
   return *this;
}
BST::BST(std::initializer_list<int> ini)
    : root{nullptr}
{
   for (int value : ini)
      add_node(value);
}