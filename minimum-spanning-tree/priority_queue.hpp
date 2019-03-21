#ifndef __INC_PRIORITY_QUEUE_HPP
#define __INC_PRIORITY_QUEUE_HPP

#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

#ifndef _BEGIN_ZHF_LIB
#define _BEGIN_ZHF_LIB namespace zhf_lib{
#endif // !_BEGIN_ZHF_LIB

#ifndef _END_ZHF_LIB
#define _END_ZHF_LIB }
#endif // !_END_ZHF_LIB

_BEGIN_ZHF_LIB

typedef unsigned _Index;


class IndexOverFlow
{
public:
	_Index index;
	IndexOverFlow(_Index i):index(i){ }
};

class EmptyQueue{ };


/*minimum priority queue with index, index only increase by 1 
when insert an element but do not decrease when pop an element*/
template<class _Data, 
	class _Pr = std::greater<_Data>>
class PriorityQueue
{
public:
	PriorityQueue();
	// only reserve 'reserve_size'
	PriorityQueue(size_t reserve_size);
	explicit PriorityQueue(const vector<_Data> &elements);
	// size
	bool empty()const;
	size_t size()const;

	// with element
	_Index parent_id(_Index id)const;
	_Index left_id(_Index id)const;
	_Index right_id(_Index id)const;
	
	const _Data &at(_Index id)const;
	bool has_id(_Index id)const;

	_Index id_to_heap(_Index id)const;
	_Index heap_to_id(_Index heap_id)const;

	// interface with change the heap
	void make_heap(const vector<_Data> &elements);
	void pop();
	inline const _Data &top()const;
	void push(const _Data &d);
	void change_key(_Index id, const _Data &new_data);

	static const _Index NoIndex;

private:
	/*id - heap onto map*/
	vector<_Index> id_heap_map;		// map from insert id to heap index
	vector<_Index> heap_id_map;		// map from heap index to insert id
	vector<_Data> min_heap;	// map to record data
	static const unsigned HeapSizeDefault;
	const _Pr pred_function;
	unsigned heap_size;
	_Index new_id;

	// maintain the heap
	void min_heapify(_Index id);
	void decrease_key(_Index id, const _Data &new_data);
	void increase_key(_Index id, const _Data &new_data);
	void swap_heap_id(_Index heap_id_1, _Index heap_id_2);
	
	// use with out check
	_Index parent(_Index heap_id) const;
	_Index left(_Index heap_id)const;
	_Index right(_Index heap_id)const;
	// check
	void index_check_0_and_max(_Index index)const;
	void index_check_0(_Index index)const;
	void index_check_max(_Index index)const;
};

///////////////////////////////////////////////////////////////////////////////////////
template <class _Data, class _Pr>
const unsigned PriorityQueue<_Data, _Pr>::HeapSizeDefault = 100;

template <class _Data, class _Pr>
const unsigned PriorityQueue<_Data, _Pr>::NoIndex = std::numeric_limits<_Index>::max();

template <class _Data, class _Pr>
PriorityQueue<_Data, _Pr>::PriorityQueue()
	:pred_function()
{
	heap_size = 0;
	new_id = 0;
	id_heap_map.reserve(HeapSizeDefault);
	min_heap.reserve(HeapSizeDefault);
	heap_id_map.reserve(HeapSizeDefault);
}

template <class _Data, class _Pr>
PriorityQueue<_Data, _Pr>::PriorityQueue(size_t reserve_size)
	:pred_function()
{
	heap_size = 0;
	new_id = 0;
	id_heap_map.reserve(reserve_size);
	min_heap.reserve(reserve_size);
	heap_id_map.reserve(reserve_size);
}

template <class _Data, class _Pr>
PriorityQueue<_Data, _Pr>::PriorityQueue(const vector<_Data> &elements)
	:pred_function()
{
	heap_size = 0;
	new_id = 0;
	min_heap.reserve(elements.size());
	id_heap_map.reserve(elements.size());
	heap_id_map.reserve(elements.size());
	make_heap(elements);
}

// size
template <class _Data, class _Pr>
bool PriorityQueue<_Data, _Pr>::empty()const
{
	return heap_size == 0;
}

template <class _Data, class _Pr>
size_t PriorityQueue<_Data, _Pr>::size()const
{
	return heap_size;
}

// with element
template <class _Data, class _Pr>
_Index PriorityQueue<_Data, _Pr>::parent_id(_Index id)const
{
	index_check_0_and_max(id);
	id = (id_heap_map[id] - 1)/2;
	return heap_id_map[id];
}

template <class _Data, class _Pr>
_Index PriorityQueue<_Data, _Pr>::parent(_Index heap_id)const
{
	return (heap_id - 1) / 2;
}

template <class _Data, class _Pr>
_Index PriorityQueue<_Data, _Pr>::left_id(_Index id)const
{
	index_check_max(id);
	id = id_heap_map[id] * 2 + 1;
	id = heap_id_map[id];
	index_check_max(id);
	return id;
}

template <class _Data, class _Pr>
_Index PriorityQueue<_Data, _Pr>::left(_Index heap_id)const
{
	return heap_id * 2 + 1;
}

template <class _Data, class _Pr>
_Index PriorityQueue<_Data, _Pr>::right_id(_Index id)const
{
	index_check_max(id);
	id = (id_heap_map[id] + 1) * 2;
	id = heap_id_map[id];
	index_check_max(id);
	return id;
}

template <class _Data, class _Pr>
_Index PriorityQueue<_Data, _Pr>::right(_Index heap_id)const
{
	return (heap_id + 1) * 2;
}

template<class _Data, class _Pr>
inline const _Data & PriorityQueue<_Data, _Pr>::at(_Index id) const
{
	index_check_max(id);
	id = id_heap_map.at(id);
	return min_heap[id];
}

template<class _Data, class _Pr>
inline bool PriorityQueue<_Data, _Pr>::has_id(_Index id) const
{
	if (id > id_heap_map.size() || id_heap_map[id] == NoIndex)
	{
		return false;
	}
	else
	{
		return true;
	}
}

template<class _Data, class _Pr>
inline _Index PriorityQueue<_Data, _Pr>::id_to_heap(_Index id) const
{
	index_check_max(id);
	return id_heap_map[id];
}

template<class _Data, class _Pr>
inline _Index PriorityQueue<_Data, _Pr>::heap_to_id(_Index heap_id) const
{
	if (heap_id >= heap_size)
	{
		throw IndexOverFlow(heap_id);
	}
	return heap_id_map[heap_id];
}

// interface with change the heap
template <class _Data, class _Pr>
void PriorityQueue<_Data, _Pr>::make_heap(const vector<_Data> &elements)
{
	if (heap_size != 0)
	{
		min_heap.clear();
		id_heap_map.clear();
	}

	heap_size = elements.size();
	min_heap.resize(heap_size);
	id_heap_map.resize(heap_size);
	heap_id_map.resize(heap_size);
	// build map
	for (int i = 0; i < heap_size; i++)
	{
		id_heap_map[i] = i;
		heap_id_map[i] = i;
	}
	std::copy(elements.begin(), elements.end(), min_heap.begin());
	for (int i = parent(heap_size - 1); i >= 0; i--)
	{
		min_heapify(heap_id_map[i]);
	}
	new_id = heap_size;
}

template <class _Data, class _Pr>
void PriorityQueue<_Data, _Pr>::pop()
{
	if (heap_size == 0)
	{
		throw EmptyQueue();
	}
	min_heap[0] = min_heap.back();
	min_heap.pop_back();
	heap_size--;
	// set id of top element be NO_ID
	id_heap_map[heap_id_map[0]] = NoIndex;
	if (heap_size == 0)		// now is a empty queue
	{
		heap_id_map.pop_back();
	}
	else
	{
		// set id of bottem element be heap top
		id_heap_map[heap_id_map.back()] = 0;
		// set heap top corresponds to its new id
		heap_id_map[0] = heap_id_map.back();
		heap_id_map.pop_back();
		min_heapify(heap_id_map[0]);
	}
}

template <class _Data, class _Pr>
inline const _Data &PriorityQueue<_Data, _Pr>::top()const
{
	return min_heap.at(0);
}

template <class _Data, class _Pr>
void PriorityQueue<_Data, _Pr>::push(const _Data &d)
{
	heap_size++;
	min_heap.push_back(d);
	heap_id_map.push_back(new_id++);
	id_heap_map.push_back(heap_size - 1);
	if (heap_size != 1 && pred_function(min_heap[parent(heap_size - 1)], min_heap[heap_size - 1]))
	{
		increase_key(new_id - 1, d);
	}
}

template <class _Data, class _Pr>
void PriorityQueue<_Data, _Pr>::increase_key(_Index id, const _Data &new_data)
{
	index_check_max(id);
	min_heap[id_heap_map[id]] = new_data;
	min_heapify(id);
}

template <class _Data, class _Pr>
void PriorityQueue<_Data, _Pr>::decrease_key(_Index id, const _Data &new_data)
{
	index_check_max(id);
	min_heap[id_heap_map[id]] = new_data;
	_Index heap_index = id_heap_map[id];
	while (heap_index > 0)
	{
		_Index p = parent(heap_index);
		if (pred_function(min_heap[heap_index], min_heap[p]))
		{
			break;
		}
		// exchange id and parent
		std::swap(min_heap[p], min_heap[heap_index]);
		swap_heap_id(p, heap_index);
		heap_index = p;
	}
}

template <class _Data, class _Pr>
void PriorityQueue<_Data, _Pr>::change_key(_Index id, const _Data &new_data)
{
	index_check_max(id);
	if (pred_function(new_data, min_heap[id_heap_map[id]]))	// increase key
	{
		increase_key(id, new_data);
	}
	else
	{
		decrease_key(id, new_data);
	}
}

// maintain the heap
template <class _Data, class _Pr>
void PriorityQueue<_Data, _Pr>::min_heapify(_Index id)
{
	index_check_max(id);
	_Index heap_id = id_heap_map[id];
	while (heap_id <= parent(heap_size - 1))
	{
		_Index l = left(heap_id);
		_Index r = right(heap_id);
		_Index smallest;
		if (l < heap_size && pred_function(min_heap[heap_id], min_heap[l]))	// left is smaller
		{
			smallest = l;
		}
		else
		{
			smallest = heap_id;
		}
		if (r < heap_size && pred_function(min_heap[smallest], min_heap[r]))	// right is smaller
		{
			smallest = r;
		}
		if (smallest != heap_id)
		{
			std::swap(min_heap[smallest], min_heap[heap_id]);
			swap_heap_id(smallest, heap_id);
			heap_id = smallest;
		}
		else
		{
			break;
		}
	}
}

template<class _Data, class _Pr>
void PriorityQueue<_Data, _Pr>::swap_heap_id(_Index heap_id_1, _Index heap_id_2)
{
	_Index id1, id2;
	id1 = heap_id_map[heap_id_1];
	id2 = heap_id_map[heap_id_2];
	id_heap_map[id1] = heap_id_2;
	id_heap_map[id2] = heap_id_1;
	heap_id_map[heap_id_1] = id2;
	heap_id_map[heap_id_2] = id1;
}

template <class _Data, class _Pr>
void PriorityQueue<_Data, _Pr>::index_check_0_and_max(_Index index)const
{
	index_check_0(index);
	index_check_max(index);
}

template <class _Data, class _Pr>
void PriorityQueue<_Data, _Pr>::index_check_0(_Index index)const
{
	if (0 == index)
	{
		throw IndexOverFlow(index);
	}
}

template <class _Data, class _Pr>
void PriorityQueue<_Data, _Pr>::index_check_max(_Index index)const
{
	if (index >= id_heap_map.size() || id_heap_map[index] == NoIndex)
	{
		throw IndexOverFlow(index);
	}
}

_END_ZHF_LIB
#endif