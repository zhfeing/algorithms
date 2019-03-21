#ifndef __INC_DDS_HPP
#define __INC_DDS_HPP

#pragma once

#include <functional>
#include <vector>

/* just for convenient */
#ifndef _BEGIN_ZHF_LIB
#define _BEGIN_ZHF_LIB namespace zhf_lib {
#endif // !_ZHF_LIB

#ifndef _END_ZHF_LIB
#define _END_ZHF_LIB }
#endif // !_END_ZHF_LIB

#ifndef _ZHF
#define _ZHF zhf_lib::
#endif // !_ZHF

/* begin dds.hpp */
_BEGIN_ZHF_LIB


#ifdef _STD
#undef _STD
#endif // !_STD
#define _STD ::std::

#ifndef TRACE
#define tcout 0 && cout
#else
#define tcout _STD cout
#endif


template<class _Ty, class _Pr = equal_to<_Ty>>
class SetElement
{
public:
	explicit SetElement(_Ty &val) :_val(val)
	{

	}

	_Ty _val;
};

// node of disjoint data set

template<class _Ty = int>
class DisjointDataSet
{
public:
	using _Node = SetElement<_Ty>;

	DisjointDataSet() :_size_of_elements(0), _size_of_sets(0)
	{

	}
	virtual void make_set(const _Ty &_val) = 0;
	virtual _Ty &find_set(const _Ty &_val) = 0;
	virtual void union_set(const _Ty &_val1, const _Ty &_val2) = 0;
	size_t size_of_elements()
	{
		return _size_of_elements;
	}
	size_t size_of_sets()
	{
		return _size_of_sets;
	}
	bool empty()
	{
		return _size_of_sets == 0;
	}
private:
	size_t _size_of_elements, _size_of_sets;
};


_END_ZHF_LIB

#endif // !__INC_DDS_HPP
