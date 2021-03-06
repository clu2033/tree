#include <iostream>
#include <string>
#include "TreeType.h"
using namespace std;

int main()
{
	TreeType<int> t;
	QueType pre, post, in; 
	t.PutItem(3);
	t.PutItem(5);
	t.PutItem(1);
	t.PutItem(0);
	t.PutItem(2);
	t.PutItem(4);
	t.PutItem(6);
	t.PutItem(7);
	t.Print();
	t.Ancestors(0);
	t.LevelOrderPrint();
	t.PreOrderPrint(pre);
	t.PostOrderPrint(post);
	t.InOrderPrint(in);
	// t.LevelOrderPrint();
	// t.DeleteItem(4);
	// t.DeleteItem(1);
	t.DeleteItem(3);
	t.Print();
	t.Ancestors(0);
	t.LevelOrderPrint();
	t.PreOrderPrint(pre);
	t.PostOrderPrint(post);
	t.InOrderPrint(in);
	return 0;
}
