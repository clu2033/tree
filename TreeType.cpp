#include<iostream>
#include "TreeType.h"
using namespace std;

struct TreeNode
{
    ItemType info;
    TreeNode* left;
    TreeNode* right;
};


// template<class ItemType>
int CountNodes(TreeNode* tree);
// template<class ItemType>
void Retrieve(TreeNode* tree, ItemType& item, bool& found);
// template<class ItemType>
void Insert(TreeNode*& tree, ItemType item);
// template<class ItemType>
void DeleteNode(TreeNode*& tree);
// template<class ItemType>
void Delete(TreeNode*& tree, ItemType item);
// template<class ItemType>
void GetPredecessor(TreeNode* tree, ItemType& data);
// template<class ItemType>
void PrintTree(TreeNode* tree);
// template<class ItemType>
void PreOrder(TreeNode*, QueType&);
// template<class ItemType>
void InOrder(TreeNode*, QueType&);
// template<class ItemType>
void PostOrder(TreeNode*, QueType&);
// template<class ItemType>
int GetHeight(TreeNode* tree);
// template<class ItemType>
void PrintLevel(TreeNode* tree);
// template<class ItemType>
void LevelOrder(TreeNode* tree);
// template<class ItemType>
TreeNode* PtrToSuccessor(TreeNode*& tree);
// template<class ItemType>
void GetSuccessor(TreeNode* tree, ItemType& data);
// template<class ItemType>
bool printAncestors(TreeNode* tree, ItemType value);



template<class ItemType>
TreeType<ItemType>::TreeType()
{
    root = NULL;
}

template<class ItemType>
TreeType<ItemType>::~TreeType()
// Calls recursive function Destroy to destroy the tree.
{
    Destroy(root);
}

template<class ItemType>
TreeType<ItemType>::TreeType(const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree into root.
{
    CopyTree(root, originalTree.root);
}


template<class ItemType>
bool TreeType<ItemType>::IsFull() const
{
    TreeNode* location;
    try
    {
        location = new TreeNode;
        delete location;
        return false;
    }
    catch(std::bad_alloc exception)
    {
        return true;
    }
}

template<class ItemType>
bool TreeType<ItemType>::IsEmpty() const
{
    return root == NULL;
}

// template<class ItemType>
int CountNodes(TreeNode* tree)
// Post: returns the number of nodes in the tree.
{
    if (tree == NULL)
        return 0;
    else 
        return CountNodes(tree->left) + CountNodes(tree->right) + 1;
}

template<class ItemType>
int TreeType<ItemType>::GetLength() const
// Calls recursive function CountNodes to count the nodes in the tree.
{
    return CountNodes(root);
}

template<class ItemType>
ItemType TreeType<ItemType>::GetItem(ItemType item, bool& found)
// Calls recursive function Retrieve to search the tree for item.
{
    Retrieve(root, item, found);
    return item;
}

// template<class ItemType>
void Retrieve(TreeNode* tree, ItemType& item, bool& found)
// Recursively searches tree for item.
// Post: If there is an element someItem whose key matches item's,
//       found is true and item is set to a copy of someItem; 
//       otherwise found is false and item is unchanged.
{
    if (tree == NULL)
        found = false;                     // item is not found.
    else if (item < tree->info)      
        Retrieve(tree->left, item, found); // Search left subtree.
    else if (item > tree->info)
        Retrieve(tree->right, item, found);// Search right subtree.
    else
    {
        item = tree->info;                 // item is found.
        found = true;
    }
} 

template<class ItemType>
void TreeType<ItemType>::PutItem(ItemType item)
{
    Insert(root, item);
}

// template<class ItemType>
void Insert(TreeNode*& tree, ItemType item)
// Inserts item into tree.
// Post:  item is in tree; search property is maintained.
{
    if (tree == NULL)
    {// Insertion place found.
        tree = new TreeNode;
        tree->right = NULL;
        tree->left = NULL;
        tree->info = item;
    }
    else if (item < tree->info)
        Insert(tree->left, item);    // Insert in left subtree.
    else
        Insert(tree->right, item);   // Insert in right subtree.
} 

template<class ItemType>
void TreeType<ItemType>::DeleteItem(ItemType item)
// Calls recursive function Delete to delete item from tree.
{
	bool found = false;
	GetItem(item, found);
	if (found)
		Delete(root, item);
	else
		cout << item << "is not in tree\n";
}

// template<class ItemType>
void DeleteNode(TreeNode*& tree)
// Deletes the node pointed to by tree.
// Post: The user's data in the node pointed to by tree is no 
//       longer in the tree.  If tree is a leaf node or has only 
//       non-NULL child pointer the node pointed to by tree is 
//       deleted; otherwise, the user's data is replaced by its 
//       logical predecessor and the predecessor's node is deleted.
{
    ItemType data;
    TreeNode* tempPtr;
    tempPtr = tree;
    if (tree->left == NULL)
    {
        tree = tree->right;
        delete tempPtr;
    }
    else if (tree->right == NULL)
    {
        tree = tree->left;
        delete tempPtr;
    }
    else
    {
        GetSuccessor(tree->right, data);
        tree->info = data;
        // cout << data << endl;
        Delete(tree->right, data);  // Delete successor node.
        // Delete(tree->left, data);  // Delete predecessor node.
    }
}

// template<class ItemType>
void Delete(TreeNode*& tree, ItemType item)
// Deletes item from tree.
// Post:  item is not in tree.
{
    if (item < tree->info)
        Delete(tree->left, item);   // Look in left subtree.
    else if (item > tree->info)
        Delete(tree->right, item);  // Look in right subtree.
    else
        DeleteNode(tree);           // Node found; call DeleteNode.
}   

// Requirement 4
// template<class ItemType>
TreeNode* PtrToSuccessor(TreeNode*& tree)
{
    while (tree->left != NULL)
        tree = tree->left;
    return tree;
}

// template<class ItemType>
void GetSuccessor(TreeNode* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
    while (tree->left != NULL)
        tree = tree->left;
    data = tree->info;
}

// template<class ItemType>
void GetPredecessor(TreeNode* tree, ItemType& data)
// Sets data to the info member of the right-most node in tree.
{
    while (tree->right != NULL)
        tree = tree->right;
    data = tree->info;
}

template<class ItemType>
void TreeType<ItemType>::Print() const
{
    PrintTree(root);
    cout << endl;
}

// template<class ItemType>
void PrintTree(TreeNode* tree) 
// Prints info member of items in tree in sorted order on screen.
{
    if (tree != NULL)
    {
        PrintTree(tree->left);   // Print left subtree.
        cout << tree->info << "  ";
        PrintTree(tree->right);  // Print right subtree.
    }
}

template<class ItemType>
void TreeType<ItemType>::Destroy(TreeNode*& tree)
// Post: tree is empty; nodes have been deallocated.
{
    if (tree != NULL)
    {
        Destroy(tree->left);
        Destroy(tree->right);
        delete tree;
    }
}

template<class ItemType>
void TreeType<ItemType>::MakeEmpty()
{
    Destroy(root);
    root = NULL;
}

template<class ItemType>
void TreeType<ItemType>::operator=(const TreeType& originalTree)
// Calls recursive function CopyTree to copy originalTree into root.
{
    {
    if (&originalTree == this)
        return;      // Ignore assigning self to self
    Destroy(root);   // Deallocate existing tree nodes
    CopyTree(root, originalTree.root);
    }
}

template<class ItemType>
void TreeType<ItemType>::CopyTree(TreeNode*& copy, const TreeNode* originalTree)
// Post: copy is the root of a tree that is a duplicate 
//       of originalTree.
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->info = originalTree->info;
        CopyTree(copy->left, originalTree->left);
        CopyTree(copy->right, originalTree->right);
    }
}

template<class ItemType>
void TreeType<ItemType>::ResetTree(OrderType order)
// Calls function to create a queue of the tree elements in 
// the desired order.
{
    switch (order)
    { 
    case PRE_ORDER:    
        preQue.MakeEmpty();
        PreOrder(root, preQue);
        break;
    case IN_ORDER:     
        inQue.MakeEmpty();
        InOrder(root, inQue);
        break;
    case POST_ORDER:  
        postQue.MakeEmpty();
        PostOrder(root, postQue);
        break;
    }
}

// template<class ItemType>
void PreOrder(TreeNode* tree, QueType& preQue)
// Post: preQue contains the tree items in preorder.
{
    if (tree != NULL)
    {
        preQue.Enqueue(tree->info);
        PreOrder(tree->left, preQue);
        PreOrder(tree->right, preQue);
    }
}

// template<class ItemType>
void InOrder(TreeNode* tree, QueType& inQue)
// Post: inQue contains the tree items in inorder.
{
    if (tree != NULL)
    {
        InOrder(tree->left, inQue);
        inQue.Enqueue(tree->info);
        InOrder(tree->right, inQue);
    }
}

// template<class ItemType>
void PostOrder(TreeNode* tree, QueType& postQue)
// Post: postQue contains the tree items in postorder.
{
    if (tree != NULL)
    {
        PostOrder(tree->left, postQue);
        PostOrder(tree->right, postQue);
        postQue.Enqueue(tree->info);
    }
}

template<class ItemType>
ItemType TreeType<ItemType>::GetNextItem(OrderType order, bool& finished)
// Returns the next item in the desired order.
// Post: For the desired order, item is the next item in the queue.
//       If item is the last one in the queue, finished is true; 
//       otherwise finished is false.
{
  finished = false;
  ItemType item;
  switch (order)
  {
    case PRE_ORDER: 
        preQue.Dequeue(item);
        if (preQue.IsEmpty())
            finished = true;
        break;
    case IN_ORDER: 
        inQue.Dequeue(item);
        if (inQue.IsEmpty())
            finished = true;
        break;
    case  POST_ORDER:
        postQue.Dequeue(item);
        if (postQue.IsEmpty())
            finished = true;
        break;
    }
    return item;
}

// template<class ItemType>
int GetHeight(TreeNode* tree)
{
    if (tree == NULL)
        return 0;
    else
    {
        int left = GetHeight(tree->left);
        int right = GetHeight(tree->right);
        if (left > right)
            return (left + 1);
        else
            return (right + 1);
    }
}

// template<class ItemType>
void PrintLevel(TreeNode* tree, int level)
{
    if (tree == NULL)
        return;
    if (level == 1)
        cout << tree->info << " ";
    else if (level > 1)
    {
        PrintLevel(tree->left, level-1);
        PrintLevel(tree->right, level-1);
    }
}

// template<class ItemType>
void LevelOrder(TreeNode* tree)
{
    int h = GetHeight(tree);
    for (int i=1; i<=h; i++)
    {
        cout << "level " << i << ": ";
        PrintLevel(tree, i);
        cout << endl;
    }
}

// Requirement 2
template<class ItemType>
void TreeType<ItemType>::LevelOrderPrint() const
{
    LevelOrder(root);
}

// Requirement 3
template<class ItemType>
void TreeType<ItemType>::PreOrderPrint(QueType& queue)
{
    PreOrder(root, queue);
    ItemType item;
    cout << "PreOrder:\t";
    while (!queue.IsEmpty())
    {
        queue.Dequeue(item);
        cout << item << " ";
    }
    cout << endl;
}

template<class ItemType>
void TreeType<ItemType>::InOrderPrint(QueType& queue)
{
    InOrder(root, queue);
    ItemType item;
    cout << "InOrder:\t";
    while (!queue.IsEmpty())
    {
        queue.Dequeue(item);
        cout << item << " ";
    }
    cout << endl;
}

template<class ItemType>
void TreeType<ItemType>::PostOrderPrint(QueType& queue)
{
    PostOrder(root, queue);
    ItemType item;
    cout << "PostOrder:\t";
    while (!queue.IsEmpty())
    {
        queue.Dequeue(item);
        cout << item << " ";
    }
    cout << endl;
}

// template<class ItemType>
bool printAncestors(TreeNode* tree, ItemType value)
{
    if (tree == NULL)
        return false;
    if (tree->info == value)
        return true;
    if (printAncestors(tree->left, value) || printAncestors(tree->right, value))
    {
        cout << tree->info << " ";
        return true;
    }
    return false;
}

template<class ItemType>
void TreeType<ItemType>::Ancestors(ItemType value)
{
    cout << "Ancestors: ";
    printAncestors(root, value);
    cout << endl;
}

// template<class ItemType>
void swap(TreeNode* root);
TreeType<ItemType> rootToTree(TreeNode* root);

// Requirement 8

void swap(TreeNode* root)
{   
   if(root != NULL)
   {
       TreeNode* temp = root->left;
       root->left = root->right;
       root->right = temp;
       swap(root->left);
       swap(root->right);
   }
}

// template<class ItemType>
TreeType<ItemType> rootToTree(TreeNode* root)
{
   TreeType<ItemType> newTree;
   QueType q;
   PreOrder(root, q);
   while (!q.IsEmpty())
   {
       ItemType item;
       q.Dequeue(item);
       newTree.PutItem(item);
   }
   return newTree;
}

template<class ItemType>
TreeType<ItemType> TreeType<ItemType>::MirrorImage()
{
    TreeType<ItemType> mirror = rootToTree(root);
    TreeType<ItemType> m = TreeType(mirror);
    swap(m.root);
    return m;
}

template class TreeType<int>;
// template class TreeType<char>;
