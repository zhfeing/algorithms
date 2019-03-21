#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const unsigned short KeyBits = 32;
const unsigned short HashTableBits = 5;
#define HASH_TABLE_SIZE 32	//require 2^3
#define NODE_AMOUNT 10

typedef int Data;
typedef unsigned Key;
typedef struct DataNode
{
	Key key;
	Data data;
}DataNode;

DataNode HashTable[HASH_TABLE_SIZE];

unsigned hash(Key k, int i);
unsigned h1(Key k);
unsigned h2(Key k);
Data search(Key k);
bool insert(DataNode d);
void printTable()
{
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
		if (HashTable[i].key != 0)
			printf("key: %d, data: %d\n", HashTable[i].key, HashTable[i].data);
	putchar('\n');
}

int main()
{
	//printTable();
	DataNode d1;
	for (int i = 1; i < NODE_AMOUNT; i++)
	{
		d1 = { i, 1 };
		int res = insert(d1);
		if (res == false)
		{
			printf("failed\n");
			return -1;
		}
	}
	printTable();
	return 0;
}

bool search(Key k, Data &data)
{
	if (k == 0)
		return (Data)0;
	unsigned address;
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		address = hash(k, i);
		if (HashTable[address].key == k)
		{
			data = HashTable[address].data;
			return true;
		}
	}
	return false;
}
unsigned hash(Key k, int i)
{
	unsigned address;
	address = (h1(k) + i*h2(k)) % HASH_TABLE_SIZE;
	//printf("hash num = %d\n", address);
	return address;
}
unsigned h1(Key k)
{
	unsigned address;
	unsigned A = 0xF785FFFF/2 + 0xEFFFF000/2;
	address = (A*k) >> (KeyBits - HashTableBits);
	return address;
}
unsigned h2(Key k)
{
	unsigned address;
	unsigned A = 0xF456FFFF / 2 + 0xEFFF123F / 2;
	address = (A*k) >> (KeyBits - HashTableBits);
	if (address == 0)
	{
		address += 1;
	}
	else if (address % 2 == 0)
	{
		address -= 1;
	}
	return address;
}
bool insert(DataNode d)
{
	if (d.key == 0)
		return false;
	unsigned address;
	for (int i = 0; i < HASH_TABLE_SIZE; i++)
	{
		address = hash(d.key, i);
		if (HashTable[address].key == d.key)
		{
			return false;
		}
		else if (HashTable[address].key == 0)
		{
			HashTable[address].key = d.key;
			HashTable[address].data = d.data;
			return true;
		}
	}
	return false;
}