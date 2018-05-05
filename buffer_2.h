#ifndef BUFFER_2_H
#define BUFFER_2_H
class buffer_2
{
public:
	buffer_2();
	~buffer_2();
	void inputData(unsigned int, unsigned int);
	void updateData();
	void clr();
	unsigned int inst, instD, PCPlus4, PCPlus4D;
	int inst_num = -1, inst_num_in = -1;
	unsigned int pc;
	void setInstNum(int num, unsigned int p)
	{
		inst_num_in = num;
		pc = p;
	}
private:

};

buffer_2::buffer_2()
{
	inst = 0;
	instD = 0;
	PCPlus4 = 0;
	PCPlus4D = 0;
}

buffer_2::~buffer_2()
{
}
void buffer_2::inputData(unsigned int instruction, unsigned int PC)
{
	inst = instruction;
	PCPlus4 = PC;
}
void buffer_2::updateData()
{
	instD = inst;
	PCPlus4D = PCPlus4;
	inst_num = inst_num_in;
}
void buffer_2::clr()
{
	PCPlus4 = 0;
	PCPlus4D = 0;
	inst_num = -1;
}
#endif