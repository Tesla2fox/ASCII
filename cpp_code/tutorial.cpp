#include "stadfx.h"
#include "ReadConfig.h"
#include "Obmap.h"

int main(int argc, char * argv[])
{
	char * conFileName = "D:\\py_code\\coverageMotionPlanning\\data\\CPP_cfg.txt";

	if (argc > 1){
		cout << argv[1] << endl;
		conFileName = argv[1];
	}
	cfg::ReadConfig readCfg(conFileName);
	readCfg.read();

	pl::Obmap obmap(readCfg._RangePtr);
	obmap.writeRange();
	

	cout << "ggq' code" << endl;
	if (argc <= 1){
		size_t input_val;
		std::cin >> input_val;
	}
}


