#include "stadfx.h"
#include "ReadConfig.h"
#include "Obmap.h"
#include "Splan.hpp"
#include "MultiPlan.hpp"
int main(int argc, char * argv[])
{
	//char * conFileName = "D:\\py_code\\\ASCII\\data\\5_15_15CPP_Cfg.txt";
	//char * conFileName = "D:\\py_code\\\ASCII\\data\\20_50_50CPP_Cfg.txt";
	char * conFileName = "D:\\py_code\\\ASCII\\data\\5_15_15_-1CPP_Cfg.txt";
	//char * conFileName = "D:\\py_code\\\ASCII\\data\\80_50_50_-1CPP_Cfg.txt";


	if (argc > 1) {
		cout << argv[1] << endl;
		conFileName = argv[1];
	}
	cfg::ReadConfig readCfg(conFileName);
	readCfg.read();

	pl::Obmap 	demonMap(readCfg._RangePtr, readCfg._gridStep);
	demonMap.writeRange();
	std::cout << "obNum = " << readCfg._vObPntPtr->size();
	for (size_t i = 0; i < readCfg._vObPntPtr->size(); i++)
	{
		demonMap.addObPnt(readCfg._vObPntPtr->at(i));
	}
	cout << "Ob" << demonMap.obNum() << endl;

	demonMap.map2sGrid();
	demonMap.map2tGrid();

	if (!demonMap.reasonable())
	{
		cout << "wtf" << endl;
		return 1;
	}
	demonMap.writeGraph(pl::graphType::base);
	demonMap.writeGraph(pl::graphType::span);
	//	obmap.spanningTree();
	demonMap.saveGraphSvg(pl::graphType::base);
	demonMap.saveGraphSvg(pl::graphType::span);
	demonMap.saveSvg();

	pl::MultiPlan demonPlan(demonMap, *readCfg._vStartPntPtr);
	//demonPlan.cenPathPlanning();
	demonPlan.disPathPlanning();
	demonPlan.drawGraph(pl::graphType::base, false);
	demonPlan.drawGraph(pl::graphType::span, false);
	demonPlan.drawRobSet(false);
	// demonPlan.cenPathPlanning();
	//	multi_plan.disPathPlanning();
	demonPlan.drawStartLocation();
	demonPlan.drawPath();
	demonPlan.savePic();
	demonPlan.writeSgsTree();

	return 1;

	pl::Obmap obmap(readCfg._RangePtr, 3);
	obmap.writeRange();

	obmap.addObPnt(bex::DPoint(20, 60));
	obmap.addObPnt(bex::DPoint(25, 60));
	obmap.addObPnt(bex::DPoint(30, 60));
	obmap.addObPnt(bex::DPoint(35, 60));
	obmap.addObPnt(bex::DPoint(40, 60));
	obmap.addObPnt(bex::DPoint(45, 60));
	obmap.addObPnt(bex::DPoint(50, 60));
	obmap.addObPnt(bex::DPoint(55, 60));

	obmap.addObPnt(bex::DPoint(60, 60));
	obmap.addObPnt(bex::DPoint(65, 60));
	obmap.addObPnt(bex::DPoint(70, 60));
	obmap.addObPnt(bex::DPoint(75, 60));
	obmap.addObPnt(bex::DPoint(80, 60));
	obmap.addObPnt(bex::DPoint(85, 60));
	obmap.addObPnt(bex::DPoint(90, 60));
	obmap.addObPnt(bex::DPoint(120, 60));


	obmap.map2sGrid();
	obmap.map2tGrid();

	obmap.writeGraph(pl::graphType::base);
	obmap.writeGraph(pl::graphType::span);
	//	obmap.spanningTree();
	obmap.saveGraphSvg(pl::graphType::base);
	obmap.saveGraphSvg(pl::graphType::span);
	obmap.saveSvg();



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
	//	multi_plan.drawGraph(pl::graphType::span, false);
	//	multi_plan.pathPlanning();
	multi_plan.cenPathPlanning();
	//	multi_plan.disPathPlanning();
	multi_plan.drawStartLocation();
	//multi_plan.drawRobGraph();
	multi_plan.drawPath();
	//multi_plan.drawRobSet(false);
	multi_plan.savePic();

	cout << "ggq' code" << endl;
	if (argc <= 1) {
		size_t input_val;
		std::cin >> input_val;
	}
}


