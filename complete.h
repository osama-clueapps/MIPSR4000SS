#include <map>
using namespace std;

class complete
{
	private:
		struct inst 
		{
			unsigned int ReadData, RegWrite, MemtoReg;
			unsigned int ALUOut, WriteReg;
		};
		inst i;  
	public:
		complete();
		void next(unsigned int &ReadDataWB, unsigned int &RegWriteWB, unsigned int &MemtoRegWB, unsigned int &ALUOutWB, unsigned int &WriteRegWB);
		bool getnext();
		void insert(int n, unsigned int ReadDataC, unsigned int RegWriteC, unsigned int MemtoRegC, unsigned int ALUOutC, unsigned int WriteRegC);
		map <int, inst> m;
		int n;
	


};

complete::complete()
{
	n=1;
	m.clear();
}
void complete:: insert(int instNum, unsigned int ReadDataC, unsigned int RegWriteC, unsigned int MemtoRegC, unsigned int ALUOutC, unsigned int WriteRegC)
{
	inst i;
	i.ReadData = ReadDataC;
	i.RegWrite = RegWriteC;
	i.MemtoReg = MemtoRegC;
	i.ALUOut = ALUOutC;
	i.WriteReg = WriteRegC;
	
	m[instNum] = i;
}
bool complete::getnext() 
{
	return(m.count(n));
}
void complete:: next(unsigned int &ReadDataWB, unsigned int &RegWriteWB, unsigned int &MemtoRegWB, unsigned int &ALUOutWB, unsigned int &WriteRegWB)
{
	inst i = m[n];
	ReadDataWB = i.ReadData;
	RegWriteWB = i.RegWrite;
	MemtoRegWB = i.MemtoReg;
	ALUOutWB = i.ALUOut;
	WriteRegWB = i.WriteReg;
	m.erase(n);
	n++;
}
