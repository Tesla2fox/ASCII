#include "stadfx.h"
#include "ReadConfig.h"
#include "Obmap.h"
#include "Splan.hpp"
#include "MultiPlan.hpp"
int main(int argc, char * argv[])
{
	//char * conFileName = "D:\\py_code\\\ASCII\\data\\5_15_15CPP_Cfg.txt";
	//char * conFileName = "D:\\py_code\\\ASCII\\data\\20_50_50CPP_Cfg.txt";
	//char * conFileName = "D:\\py_code\\\ASCII\\data\\5_15_15_-1CPP_Cfg.txt";
	char * conFileName = "D:\\py_code\\\ASCII\\data\\test1_5_16_16_50CPP_Cfg.txt";
	//char * conFileName = "D:\\py_code\\\ASCII\\data\\1_7_8_15CPP_Cfg.txt";	
	//char * conFileName = "D:\\py_code\\\ASCII\\data\\10_15_15_-1CPP_Cfg.txt";
	//char * conFileName = "D:\\py_code\\\ASCII\\data\\80_50_50_400CPP_Cfg.txt";

	//char * conFileName

	if (argc > 1) {
		cout << argv[1] << endl;
		conFileName = argv[1];
	}
	cfg::ReadConfig readCfg(conFileName);
	readCfg.read();
	std::ofstream e_deg;
	e_deg.open("D:\\py_code\\ASCII\\data\\tutorial.txt", std::ios::trunc);

	clock_t start, finish;
	start = clock();
	pl::Obmap 	demonMap(readCfg._RangePtr, readCfg._gridStep);
	//demonMap.writeRange();
	std::cout << "obNum = " << readCfg._vObPntPtr->size();
	for (size_t i = 0; i < readCfg._vObPntPtr->size(); i++)
	{
		demonMap.addObPnt(readCfg._vObPntPtr->at(i));
		//e_deg << " x = " << readCfg._vObPntPtr->at(i).x() << "	y = " << readCfg._vObPntPtr->at(i).y() << endl;
		//cout << "size = " << i << endl;
	}
	e_deg << "Ob  = " << demonMap.obNum() << endl;

	cout << "Ob  = " << demonMap.obNum() << endl;

	demonMap.map2sGrid();
	demonMap.map2tGrid();

	if (!demonMap.reasonable())
	{
		cout << "wtf" << endl;
		return 1;
	}
	demonMap.writeGraph(pl::graphType::base);
	demonMap.writeGraph(pl::graphType::span);
	//demonMap.saveGraphSvg(pl::graphType::base);
	//demonMap.saveGraphSvg(pl::graphType::span);
	//demonMap.saveSvg();
	//_sleep(10000);
	pl::MultiPlan demonPlan(demonMap, *readCfg._vStartPntPtr);
	//demonPlan.disPathPlanning();
	//demonPlan.drawRobSet(false);
	//demonPlan.drawGraph(pl::graphType::base, false);
	//demonPlan.drawGraph(pl::graphType::span, false);
	//demonPlan.drawStartLocation();
	//demonPlan.drawPath();
	//demonPlan.savePic();
	//demonPlan.writeSgsTree();
	//return 1;
	vector<vector<size_t>> vvRobSetNum(readCfg._vStartPntPtr->size());
	vector<size_t> vMakeSpan;
	for (size_t i = 0; i < 200; i++)
	{
		demonPlan.setRandomSeed(i);
		demonPlan.disPathPlanning();
		auto vRobSetNum = demonPlan.getSetNum();
		for (size_t j = 0; j < readCfg._vStartPntPtr->size(); j++)
		{
			vvRobSetNum[j].push_back(vRobSetNum[j]);
		}
		vMakeSpan.push_back(*std::max_element(vRobSetNum.begin(), vRobSetNum.end()));
	}
	for (size_t i = 0; i < readCfg._vStartPntPtr->size(); i++)
	{
		e_deg << "set" << std::to_string(i);
		for (auto & it : vvRobSetNum[i])
		{
			e_deg << " " << it;
		}
		e_deg << endl;
	}
	e_deg << "makespan" ;
	for (auto & it : vMakeSpan)
	{
		e_deg << " " << it;
	}
	e_deg << endl;

	finish = clock();
	double totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	e_deg << "total time = " << totaltime << endl;
	return 1;
	demonPlan.drawRobSet(false);
	demonPlan.drawGraph(pl::graphType::base, false);
	demonPlan.drawGraph(pl::graphType::span, false);
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


