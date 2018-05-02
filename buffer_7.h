/*
This is the  buffer between the TC stage and the write back stage
*/
#ifndef BUFFER_7_H
#define BUFFER_7_H
class buffer_7
{
public:
	buffer_7();
	~buffer_7();
	unsigned int ReadDataM3, RegWriteM3, MemtoRegM3;
	unsigned int ReadDataW, RegWriteW, MemtoRegW;
	unsigned int ALUOutM3, WriteRegM3;
	unsigned int ALUOutW, WriteRegW;
	void inputData(unsigned int RegWriteM3, unsigned int ReadDataM3, unsigned int MemtoRegM3
		, unsigned int ALUOutM3, unsigned int WriteRegM3);
	void updateData();
	int inst_num = 0;
	unsigned int pc;
	void setInstNum(int num, unsigned int p)
	{
		inst_num = num;
		pc = p;
	}
private:

};

buffer_7::buffer_7()
{
	RegWriteW = 0;
	ReadDataW = 0;
	ALUOutW = 0;
	WriteRegW = 0;
	ReadDataW = 0;
}

buffer_7::~buffer_7()
{
}
void buffer_7::inputData(unsigned int RegWriteM3_in, unsigned int ReadDataM3_in, unsigned int MemtoRegM3_in
	, unsigned int ALUOutM3_in, unsigned int WriteRegM3_in)
{
	RegWriteM3 = RegWriteM3_in;
	MemtoRegM3 = MemtoRegM3_in;
	ALUOutM3 = ALUOutM3_in;
	WriteRegM3 = WriteRegM3_in;
	ReadDataM3 = ReadDataM3_in;
}
void buffer_7::updateData()
{
	RegWriteW = RegWriteM3;
	MemtoRegW = MemtoRegM3;
	ALUOutW = ALUOutM3;
	WriteRegW = WriteRegM3;
	ReadDataW = ReadDataM3;
}
#endif