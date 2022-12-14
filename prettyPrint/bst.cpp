#include "bst.h"

int BST::getDistanceToNode(Node* node, int searchKey)
{
    if(root == nullptr) return 0;

    if(searchKey == node->value) return 0;

    int distance = 0;

    if(searchKey> node->value) distance = getDistanceToNode(node->right, searchKey);
    else if(searchKey< node->value) distance = getDistanceToNode(node ->left, searchKey);

    return distance+1;
}
void BST::initializeTreeVector()
{
    std::vector<std::string> row(getHeight(), "e");
    std::vector<std::vector<std::string>> tree(orderedTree.size(),row);
    this->tree = tree;
}
void BST::printCeiling()
{
    for(int i = 0 ; i < orderedTree.size(); i++)
    {
        std::cout << "-----";
    }
    std::cout<< '-';
    std::cout << std::endl;
}
void BST::getTree()
{
    initializeTreeVector();
    for(int i = 0 ; i < orderedTree.size(); i++)
    {
        int column = i;
        int row = getDistanceToNode(root, orderedTree.at(i));
        tree.at(column).at(row) = std::to_string(orderedTree.at(i));
    }
}
void BST::prettyPrint()
{
    if(root == nullptr) return;
    getTree();
    printCeiling();

    for(int i = 0 ; i < getHeight(); i++)
    {
        for(int j = 0 ; j <orderedTree.size(); j++)
        {
           std::cout << "|";
           std::string number = tree.at(j).at(i);
           if(number != "e")
           {    
                if(number.length() == 4) std::cout << number;
                else if(number.length() == 3 ) std::cout << " " << number;
                else if(number.length() == 2) std::cout << "  " << number;
                else std::cout << "   " << number;
           }
           else std::cout << "    ";
        }
        std::cout << "|";
        std::cout << std::endl;
        printCeiling();
    }

}
void BST::deleteBST(Node* node)
{
    if(node == nullptr) return;

    deleteBST(node->left);
    deleteBST(node->right);

    delete node;
}

int BST::traverseHeight(Node* node)
{
    if(node == nullptr) return 0;

    int leftHeight = traverseHeight(node->left);
    int rightHeight = traverseHeight(node->right);

    return (leftHeight<rightHeight) ? rightHeight+1 : leftHeight+1;
}

bool BST::traverseSearch(int num, Node* node)
{
    if(node == nullptr) return false;

    if(num == node->value) return true;

    if(num > node->value) return traverseSearch(num, node->right);
    else if(num < node->value) return traverseSearch(num, node->left);
    
    return false;
}

bool BST::hasKey(int searchKey)
{
    if(root == nullptr) return false;

    return traverseSearch(searchKey,root);
}

void BST::traverseInsert(int num, Node* node) 
{
    if(node->right == nullptr)
    {
        if(num > node->value)
        {
            node->right = new Node(num);
            return;
        }
    }
    if(node->left == nullptr)
    {
        if(num < node->value)
        {
            node->left = new Node(num);
            return;
        }
    }

    if(num > node->value) traverseInsert(num, node->right);
    else if(num < node->value) traverseInsert(num, node->left);
}

void BST::insertKey(int newKey)
{
    if(root == nullptr)
    {
        root = new Node(newKey);
        return;
    }
    traverseInsert(newKey,root); 
}

void BST::traverseInOrder(Node* node)
{
    if(node == nullptr)
    {
        orderedTree.push_back(node->value);
        return;
    }

    if(node->left != nullptr) traverseInOrder(node->left);

    orderedTree.push_back(node->value);
 
    if(node->right != nullptr) traverseInOrder(node->right);
}
std::vector<int> BST::inOrder()
{
    if(root == nullptr) return orderedTree;

    traverseInOrder(root);
    return orderedTree;
}