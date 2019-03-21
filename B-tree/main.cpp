#include <iostream>

#include "B_tree_node_imp.hpp"
#include "B_Tree.hpp"
#include "disk.hpp"

using namespace std;
using namespace zhf_lib;


int main()
{
	try
	{
		BTree<int, string> B_tree(2);
		B_tree.insert(10, "hehe");

	}
	catch (BTreeNode<int, char>::Bad_Allocate)
	{
		cout << "too much tree nodes";
	}
	catch (BTreeNode<int, char>::Bad_InvalidData)
	{
		cout << "try to use invalid node construct BTreeNode_Disk" << endl;
	}
	catch (DiskSimulator<int, char>::Bad_DataInvalid)
	{
		cout << "try to write invalid data" << endl;
	}
	catch (DiskSimulator<int, char>::Bad_NodeNotFound)
	{
		cout << "try to read unexist data" << endl;
	}
	cout << "\nPress Enter to Terminate";
	cin.get();
	return 0;
}