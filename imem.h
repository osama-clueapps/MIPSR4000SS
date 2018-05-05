#pragma once
#pragma once
#ifndef IMEM_H
#define IMEM_H
#include "cache.h"
class imem
{
public:
	imem();
	~imem();
	void IF1();
	void IF2(unsigned int address, unsigned int& instruction);
	void WriteInst(unsigned int address, unsigned int data);
private:
	cache instcache;
};

imem::imem()
{
}
void imem::IF1() {
	//NOTHING
}
void imem::IF2(unsigned int address, unsigned int& instruction) {
	//NOTHING
	unsigned int tag;
	int valid;
	instcache.read(address, tag, instruction, valid);
}
void imem::WriteInst(unsigned int address, unsigned int data)
{
	instcache.write(address, data);
}
imem::~imem()
{
}
#endif