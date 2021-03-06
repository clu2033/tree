#ifndef TREETYPE_H
#define TREETYPE_H
#include <string>
#include <fstream>
#include "QueType.h"
typedef int ItemType;
struct TreeNode;
enum OrderType {PRE_ORDER, IN_ORDER, POST_ORDER};
template<class ItemType>
class TreeType
{
public:
  TreeType();                     // constructor
 ~TreeType();                    // destructor
  TreeType(const TreeType<ItemType>& originalTree); // copy constructor
  void operator=(const TreeType<ItemType>& originalTree);
  void MakeEmpty();
  bool IsEmpty() const;
  bool IsFull() const;
  int GetLength() const; 
  ItemType GetItem(ItemType item, bool& found);
  ItemType GetNextItem(OrderType order, bool& finished);
  void PutItem(ItemType item);
  void DeleteItem(ItemType item);
  void ResetTree(OrderType order); 
  void Print() const;
  void Destroy(TreeNode*& tree);
  void CopyTree(TreeNode*& copy, const TreeNode* originalTree);

  void LevelOrderPrint() const;
  void PreOrderPrint(QueType& queue);
  void InOrderPrint(QueType& queue);
  void PostOrderPrint(QueType& queue);

  void Ancestors(ItemType value);
  TreeType<ItemType> MirrorImage();

private:
  TreeNode* root;
  QueType preQue;
  QueType inQue;
  QueType postQue;
};

#endif /* TREE_TYPE_H */
