#pragma once
#ifndef CACHE_H
#define CACHE_H
#include <iostream>
using namespace std;
class cache
{
public:
	cache();
	~cache();
	void read(unsigned int address, unsigned int& tag, unsigned int& data, int& valid);
	void write(unsigned int address, unsigned int data);
private:
	struct cacheCell
	{
		int valid = 0;
		unsigned int tag = 0;
		unsigned int data;
	};
	int size = 32*4*8;
	unsigned int tagBits, indexBits;
	unsigned int offsetBits = 2;//because the line size is equal to 4 bytes so 2 = log2(4);
	cacheCell cacheArr[1000];
};
#endif
#include<cmath>
cache::cache()
{
	int blocks = size / 4;
	//cacheArr = new  cacheCell[blocks];
	indexBits = log2(blocks);
	tagBits = 32 - indexBits - offsetBits;
}
cache::~cache()
{
	//delete[] cacheArr;
}
void cache::read(unsigned int address, unsigned int& tag, unsigned int& data, int& valid)
{
	unsigned int temp, offset, index, tagaddress;
	offset = address & 3;
	address = address >> offsetBits;
	temp = pow(2, indexBits) - 1;
	index = address & temp;
	address = address >> indexBits;
	tagaddress = address;	
	tag = cacheArr[index].tag;
	data = cacheArr[index].data;
	valid = cacheArr[index].valid;
}
void cache::write(unsigned int address, unsigned int data)
{
	unsigned int temp, offset, index, tagaddress;
	offset = address & 3;
	address = address >> offsetBits;
	temp = pow(2, indexBits) - 1;
	index = address & temp;
	address = address >> indexBits;
	tagaddress = address;
	cacheArr[index].tag = tagaddress;
	cacheArr[index].data = data;
	cacheArr[index].valid = 1;
}