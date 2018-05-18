#include "stadfx.h"
#include "ReadConfig.h"
#include "Obmap.h"
#include "Splan.hpp"
#include "MultiPlan.hpp"
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
//	obmap.spanningTree();
//	obmap.saveGraphSvg(pl::graphType::base);
//	obmap.saveGraphSvg(pl::graphType::span);
//	obmap.saveSvg();

//	pl::Splan  splan(obmap);
//	splan.setStartPnt(bex::DPoint(20,0));
//	splan.pathPlanning();
	//splan.drawGraph(pl::graphType::base,true);
//	splan.drawGraph(pl::graphType::tree, false);

//	splan.drawGraph(pl::graphType::span,false);
//	splan.drawTree();
//	splan.drawPath();
	

//	splan.savePic();

	vector<bex::DPoint> vRobPnt;
	vRobPnt.push_back(bex::DPoint(20, 0));
	vRobPnt.push_back(bex::DPoint(0, 20));
	vRobPnt.push_back(bex::DPoint(40, 0));
	pl::MultiPlan multi_plan(obmap, vRobPnt);
	multi_plan.drawGraph(pl::graphType::base, false);
	multi_plan.drawGraph(pl::graphType::span, false);
	multi_plan.pathPlanning();
	multi_plan.drawStartLocation();
	multi_plan.drawRobSet();
	multi_plan.savePic();

	cout << "ggq' code" << endl;
	if (argc <= 1){
		size_t input_val;
		std::cin >> input_val;
	}
}


