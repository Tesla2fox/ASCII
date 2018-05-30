#include "stadfx.h"
#include "ReadConfig.h"
#include "Obmap.h"
#include "Splan.hpp"
#include "MultiPlan.hpp"
int main(int argc, char * argv[])
{
	char * conFileName = "D:\\py_code\\\ASCII\\data\\CPP_cfg.txt";

	if (argc > 1) {
		cout << argv[1] << endl;
		conFileName = argv[1];
	}
	cfg::ReadConfig readCfg(conFileName);
	readCfg.read();

	pl::Obmap 	demonMap(readCfg._RangePtr, 10);
	demonMap.writeRange();

	bex::DRing obRing;
	obRing.push_back(bex::DPoint(20, 30));
	obRing.push_back(bex::DPoint(50, 30));
	obRing.push_back(bex::DPoint(50, 60));
	obRing.push_back(bex::DPoint(20, 60));
	obRing.push_back(bex::DPoint(20, 30));

	demonMap.addObRing(obRing);

	demonMap.addObPnt(bex::DPoint(0, 60));
	demonMap.addObPnt(bex::DPoint(80, 80));

	demonMap.addObPnt(bex::DPoint(80, 0));
	demonMap.addObPnt(bex::DPoint(60, 0));
	demonMap.addObPnt(bex::DPoint(90, 0));
	demonMap.addObPnt(bex::DPoint(90, 15));
	demonMap.addObPnt(bex::DPoint(80, 15));


	demonMap.addObPnt(bex::DPoint(0, 100));
	demonMap.addObPnt(bex::DPoint(10, 100));
	demonMap.addObPnt(bex::DPoint(25, 100));

	std::default_random_engine engP(1);
	std::uniform_real_distribution<double> dis(0, 315);
	for (size_t i = 0; i < 35; i++)
	{
		double px = dis(engP);
		double py = dis(engP);
		demonMap.addObPnt(bex::DPoint(px, py));
	}

	demonMap.map2sGrid();
	demonMap.map2tGrid();

	demonMap.writeGraph(pl::graphType::base);
	demonMap.writeGraph(pl::graphType::span);
	//	obmap.spanningTree();
	demonMap.saveGraphSvg(pl::graphType::base);
	demonMap.saveGraphSvg(pl::graphType::span);
	demonMap.saveSvg();

	vector<bex::DPoint> demonPnt;
	demonPnt.push_back(bex::DPoint(20, 0));
	demonPnt.push_back(bex::DPoint(200, 30));
	demonPnt.push_back(bex::DPoint(150, 170));
	demonPnt.push_back(bex::DPoint(10, 310));
//	demonPnt.push_back(bex::DPoint(300, 250));

//	demonPnt.push_back(bex::DPoint(20, 0));

	pl::MultiPlan demonPlan(demonMap, demonPnt);
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


	obmap.addObRing(obRing);

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


