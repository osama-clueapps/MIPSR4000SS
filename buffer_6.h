/*
This buffer is between the two stages of dmemory DF2 AND TC
*/
#ifndef BUFFER_6_H
#define BUFFER_6_H
class buffer_6
{
public:
	buffer_6();
	~buffer_6();
	unsigned int ReadDataM2, RegWriteM2, MemtoRegM2;
	unsigned int ReadDataM3, RegWriteM3, MemtoRegM3;
	unsigned int ALUOutM2, WriteRegM2;
	unsigned int ALUOutM3, WriteRegM3;
	void inputData(unsigned int RegWriteM2, unsigned int ReadDataM2, unsigned int MemtoRegM2
		, unsigned int ALUOutM2, unsigned int WriteRegM2);
	void updateData();
	int inst_num = -1, inst_num_in = -1;
	unsigned int pc;
	void setInstNum(int num, unsigned int p)
	{
		inst_num_in = num;
		pc = p;
	}
private:

};

buffer_6::buffer_6()
{
	RegWriteM3 = 0;
	ReadDataM3 = 0;
	ALUOutM3 = 0;
	WriteRegM3 = 0;
	ReadDataM3 = 0;
}

buffer_6::~buffer_6()
{
}
void buffer_6::inputData(unsigned int RegWriteM2_in, unsigned int ReadDataM2_in, unsigned int MemtoRegM2_in
	, unsigned int ALUOutM2_in, unsigned int WriteRegM2_in)
{
	RegWriteM2 = RegWriteM2_in;
	MemtoRegM2 = MemtoRegM2_in;
	ALUOutM2 = ALUOutM2_in;
	WriteRegM2 = WriteRegM2_in;
	ReadDataM2 = ReadDataM2_in;
}
void buffer_6::updateData()
{
	RegWriteM3 = RegWriteM2;
	MemtoRegM3 = MemtoRegM2;
	ALUOutM3 = ALUOutM2;
	WriteRegM3 = WriteRegM2;
	ReadDataM3 = ReadDataM2;
	inst_num = inst_num_in;
}
#endif