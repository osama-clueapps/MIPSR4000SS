#pragma once
#ifndef DMEM_H
#define DMEM_H
#include "cache.h"
class dmem
{
public:
	dmem();
	~dmem();
	void DF1();
	void DF2(unsigned int address_in, unsigned int MEM_CT_in, unsigned int data_in, unsigned int& data_out);
	void TC();
private:
	cache datacache;
	unsigned int data;
};
dmem::dmem()
{
	data = 0;
}
dmem::~dmem()
{
}
void dmem::DF1()
{
	//NOTHING
}
void dmem::DF2(unsigned int address_in, unsigned int MEM_CT_in, unsigned int data_in, unsigned int& data_out)
{
	if (MEM_CT_in == 1)//write
	{
		datacache.write(address_in, data_in);
	}
	else if (MEM_CT_in == 0)//read
	{
		unsigned int tag;
		int valid;
		datacache.read(address_in, tag, data, valid);
		data_out = data;
	}
}
void dmem::TC()
{
	//NOTHING
}
#endif