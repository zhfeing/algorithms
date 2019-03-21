#ifndef __INC_B_TREE_NODE_HPP
#define __INC_B_TREE_NODE_HPP

#include <memory>

#ifndef _STD
#define _STD std::
#endif // !_STD

#ifndef _ZHF_LIB_BEGIN
#define _ZHF_LIB_BEGIN namespace zhf_lib{
#endif // !_ZHF_LIN_BEGIN

#ifndef _END_ZHF_LIB
#define _END_ZHF_LIB }
#endif // !_END_ZHF_LIB

_ZHF_LIB_BEGIN // begin namespace zhf_lib

template <typename _Key, typename _Val>
class BTreeNode;
template <typename _Key, typename _Val>
class BTreeNode_Disk;

template <typename _Key, typename _Val>
using pBTreeNode = _STD shared_ptr<BTreeNode<_Key, _Val>>;

template <typename _Key, typename _Val>
using pBTreeNode_Disk = _STD shared_ptr<BTreeNode_Disk<_Key, _Val>>;

// tool function
template <typename _Val, typename _Key>
void BTNode_Disk_to_BTNode(const pBTreeNode_Disk<_Key, _Val> &src, 
                            pBTreeNode<_Key, _Val> &dst)
{
    dst->_n = src->_n;
	dst->_valid = src->_valid;
	dst->_leaf = src->_leaf;
	dst->_keys = src->_keys;
	dst->_c = src->_c;
	dst->_vals = src->_vals;
}


_END_ZHF_LIB


#endif