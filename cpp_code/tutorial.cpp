#include "stadfx.h"
#include "ReadConfig.h"
#include "Obmap.h"
#include "Splan.hpp"
int main(int argc, char * argv[])
{
	char * conFileName = "D:\\py_code\\\ASCII\\data\\CPP_cfg.txt";

	if (argc > 1){
		cout << argv[1] << endl;
		conFileName = argv[1];
	}
	cfg::ReadConfig readCfg(conFileName);
	readCfg.read();

	pl::Obmap obmap(readCfg._RangePtr,3);
	obmap.writeRange();


	//bex::DRing obRing;
	//obRing.push_back(bex::DPoint(20, 30));
	//obRing.push_back(bex::DPoint(50, 30));
	//obRing.push_back(bex::DPoint(50, 60));
	//obRing.push_back(bex::DPoint(20, 60));
	//obRing.push_back(bex::DPoint(20, 30));
	//obmap.addObRing(obRing);
	

	obmap.map2tGrid();
	obmap.map2sGrid();
	obmap.writeGraph(pl::graphType::base);
	obmap.writeGraph(pl::graphType::span);
	obmap.spanningTree();
	obmap.saveGraphSvg(pl::graphType::base);
	obmap.saveGraphSvg(pl::graphType::span);
	obmap.saveSvg();

	pl::Splan  splan(obmap);
	splan.setStartPnt(bex::DPoint(20,0));
	splan.pathPlanning();
	//splan.drawGraph(pl::graphType::base,true);
	splan.drawGraph(pl::graphType::tree, false);

//	splan.drawGraph(pl::graphType::span,false);
//	splan.drawTree();
	splan.drawPath();
	

	splan.savePic();

	cout << "ggq' code" << endl;
	if (argc <= 1){
		size_t input_val;
		std::cin >> input_val;
	}
}


