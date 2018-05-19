#include "MultiPlan.hpp"

namespace pl {

	void MultiPlan::drawGraph(size_t const & type, bool const & b_edge)
	{
		bex::Graph *graphPtr;
		double gridStep;
		switch (type)
		{
		case graphType::base: {
			gridStep = _mainMap.getGridStep();
			graphPtr = &_mainMap.getGraph(graphType::base);
			break;
		}
		case graphType::span: {
			gridStep = _mainMap.getGridStep() * 2;
			graphPtr = &_mainMap.getGraph(graphType::span);
			break;
		}
							  //case graphType::tree: {
							  //	gridStep = _mainMap.getGridStep();
							  //	graphPtr = &_m_tGraph;
							  //	break;
							  //}
		default:
		{
			cout << "error type" << endl;
			return;
			break;
		}
		}
		auto &graph = (*graphPtr);

		std::pair<bex::VertexIterator, bex::VertexIterator> _b2e_vi = boost::vertices(graph);
		size_t  i = 0;

		for (bex::VertexIterator vit = _b2e_vi.first; vit != _b2e_vi.second; vit++)
		{
			bex::VertexDescriptor vd = *vit;
			bex::VertexProperty &vp = graph[vd];
			double px = vp.pnt.x();
			double py = vp.pnt.y();
			//			std::cout << "px" << px << std::endl;
			//			std::cout << "py" << py << std::endl;

			//deg::conf_debug << "px" << px << std::endl;
			//deg::conf_debug << "py" << py << std::endl;

			svg::Point pntc(px, py);
			svg::Point pnt(px - gridStep / 2, py + gridStep / 2);
			svg::Fill fill();
			svg::Stroke stroke(1, svg::Color::Cyan);

			if ((type == graphType::base) || (type == graphType::tree))
			{
				switch (vp.Type)
				{
				case bex::vertType::ObVert:
				{
					doc << svg::Rectangle(pnt, gridStep, gridStep, svg::Fill(svg::Color::Fuchsia), svg::Stroke(0.1, svg::Color::Cyan));
					//doc << svg::Circle(pntc, gridStep, svg::Fill(svg::Color::Fuchsia), svg::Stroke(0.1, svg::Color::Cyan));
					break;
				}
				case bex::vertType::WayVert:
				{
					doc << svg::Rectangle(pnt, gridStep, gridStep, svg::Fill(), svg::Stroke(0.1, svg::Color::Cyan));
					//doc << svg::Circle(pntc, gridStep, svg::Fill(), svg::Stroke(0.1, svg::Color::Cyan));
					break;
				}
				default:
					break;
				}
			}
			else {
				switch (vp.Type)
				{
				case bex::vertType::ObVert:
				{
					doc << svg::Rectangle(pnt, gridStep, gridStep, svg::Fill(svg::Color::Fuchsia), svg::Stroke(0.5, svg::Color::Cyan));
					//				doc << svg::Circle(pntc, gridStep, svg::Fill(svg::Color::Fuchsia), svg::Stroke(0.3, svg::Color::Cyan));
					break;
				}
				case bex::vertType::WayVert:
				{
					doc << svg::Rectangle(pnt, gridStep, gridStep, svg::Fill(), svg::Stroke(0.4, svg::Color::Brown));
					//				doc << svg::Circle(pntc, gridStep, svg::Fill(), svg::Stroke(0.1, svg::Color::Brown));
					break;
				}
				default:
					break;
				}
			}
		}

		if (b_edge)
		{
			std::pair<bex::EdgeIterator, bex::EdgeIterator> _b2e_ei = boost::edges(graph);

			for (auto eit = _b2e_ei.first; eit != _b2e_ei.second; eit++)
			{
				bex::EdgeDescriptor ed = *eit;
				bex::EdgeProperty &ep = graph[ed];
				bex::VertexDescriptor sVertd = boost::source(ed, graph);
				bex::VertexDescriptor tVertd = boost::target(ed, graph);

				bex::VertexProperty &sVert = graph[sVertd];
				bex::VertexProperty &tVert = graph[tVertd];

				svg::Polyline polyline_a(svg::Stroke(.2, svg::Color::Blue));

				double spx = sVert.pnt.x();
				double spy = sVert.pnt.y();
				//std::cout << "px" << px << std::endl;
				//std::cout << "py" << py << std::endl;
				svg::Point spnt(spx, spy);

				double tpx = tVert.pnt.x();
				double tpy = tVert.pnt.y();
				//std::cout << "px" << px << std::endl;
				//std::cout << "py" << py << std::endl;
				svg::Point tpnt(tpx, tpy);
				polyline_a << spnt << tpnt;
				doc << polyline_a;
			}
		}
	}

	void MultiPlan::drawStartLocation()
	{
		double gridStep = _mainMap.getGridStep();
		for (auto &it : this->_vStartPnt)
		{
			svg::Point pntc(it.x(), it.y());
			doc << svg::Circle(pntc, gridStep, svg::Fill(svg::Color::Transparent), svg::Stroke(0.1, svg::Color::Purple));
		}
	}
	void MultiPlan::drawRobSet(bool const &neibool)
	{
		double gridStep = _mainMap.getGridStep();
		auto &graph = _ob_sGraph;
		vector<map<size_t, size_t>> &_vRobSet(*_vRobSetPtr);

		//		svg::Color color(1);
		//		svg::Fill  file();
		size_t robID = 0;
		for (auto &it : _vRobSet) {
			for (auto itSet = it.begin(); itSet != it.end(); ++itSet)
			{
				const bex::VertexDescriptor &vd = (*itSet).first;
				bex::VertexProperty &vp = graph[vd];
				double px = vp.pnt.x();
				double py = vp.pnt.y();


				svg::Polyline PloyTreeEdge(svg::Stroke(.25, svg::Color::Blue));
				bex::VertexDescriptor &tVertd = (*itSet).second;
				bex::VertexProperty &tVert = graph[tVertd];
				double tpx = tVert.pnt.x();
				double tpy = tVert.pnt.y();

				svg::Point spnt(px, py);
				svg::Point tpnt(tpx, tpy);
				PloyTreeEdge << spnt << tpnt;
				doc << PloyTreeEdge;

				svg::Point pnt(px - gridStep / 2, py + gridStep / 2);
				switch (robID)
				{
				case 0:
				{
					doc << svg::Rectangle(pnt, gridStep, gridStep, svg::Fill(), svg::Stroke(0.1, svg::Color::Fuchsia));
					break;
				}
				case 1:
				{
					doc << svg::Rectangle(pnt, gridStep, gridStep, svg::Fill(), svg::Stroke(0.1, svg::Color::Blue));
					break;
				}
				case 2:
				{
					doc << svg::Rectangle(pnt, gridStep, gridStep, svg::Fill(), svg::Stroke(0.1, svg::Color::Red));
					break;
				}
				default:
					doc << svg::Rectangle(pnt, gridStep, gridStep, svg::Fill(), svg::Stroke(0.1, svg::Color::Yellow));
					break;
				}

			}
			if (neibool)
			{
				for (auto itSet = _vRobNeiSetPtr->at(robID).begin(); itSet != _vRobNeiSetPtr->at(robID).end(); ++itSet)
				{

					const bex::VertexDescriptor &vd = (*itSet).first;
					bex::VertexProperty &vp = graph[vd];
					double px = vp.pnt.x();
					double py = vp.pnt.y();
					svg::Point pnt(px, py);

					svg::Polyline PloyTreeEdge(svg::Stroke(.25, svg::Color::Green));
					bex::VertexDescriptor &tVertd = (*itSet).second;
					bex::VertexProperty &tVert = graph[tVertd];
					double tpx = tVert.pnt.x();
					double tpy = tVert.pnt.y();

					svg::Point spnt(px, py);
					svg::Point tpnt(tpx, tpy);
					PloyTreeEdge << spnt << tpnt;
					doc << PloyTreeEdge;
					doc << svg::Circle(pnt, gridStep, svg::Fill(), svg::Stroke(0.2, svg::Color::Green));
				}
			}
			robID++;
		}

	}
	void MultiPlan::pathPlanning()
	{
		auction();
	}
	void MultiPlan::auction()
	{
		_vRobSetPtr = make_shared<vector<map<size_t, size_t>>>(_robNum);
		_vRobNeiSetPtr = make_shared<vector<map<size_t, size_t>>>(_robNum);
		_notBidSetPtr = make_shared<set<size_t>>();
		vector<map<size_t, size_t>> &_vRobSet(*_vRobSetPtr);
		vector<map<size_t, size_t>> &_vRobNeiSet(*_vRobNeiSetPtr);

		vector<bool> allAucEd(bt::num_vertices(_ob_sGraph), false);

		auto aucCompleted = [](vector<bool> const &vb) {
			auto iter = std::find(vb.begin(), vb.end(), false);
			if (iter == vb.end()) return true;
			return false;
		};


		for (size_t i = 0; i < this->_vStartPnt.size(); i++)
		{

			//vector<pair<size_t, size_t>> &robSpanTree = _vRobSpanTree[i];
			GridIndex robGridInd = _mainMap.pnt2Index(_vStartPnt[i], pl::graphType::span);
			bex::VertexDescriptor robVd = _ob_smap2graph[robGridInd];
			_vRobSet[i].insert(pair<size_t, size_t>(robVd, robVd));
			auto neighborsIter = bt::adjacent_vertices(robVd, _ob_sGraph);
			for (auto ni = neighborsIter.first; ni != neighborsIter.second; ++ni)
			{
				_vRobNeiSet[i].insert(pair<size_t, size_t>(*ni, robVd));
			}
			_notBidSetPtr->insert(robVd);
			allAucEd[robVd] = true;
		}

		//vector<set<size_t>> _vRobNei;
		size_t circleTime = 0;

		std::default_random_engine eng;
		eng.seed(2);
		std::uniform_int_distribution<int> dis(0, _robNum);
		do
		{

			size_t aucNeer = dis(eng);

			if (aucNeer == _robNum) aucNeer = _robNum - 1;
			//size_t aucNeer = 1;

			c_deg << "aucNeer  = " << aucNeer << endl;
			bex::VertexDescriptor aucInd;
			auto &robSet = _vRobSet[aucNeer];
			bool allCovered = getMinLeaf(aucNeer, aucInd);

			size_t successBidRobID = minBidRob(aucNeer, aucInd);

			if (allCovered)
			{
				updateSetWithErase(successBidRobID, aucInd);
				//if (successBidRobID == aucNeer) {
				//	drawRobSet(false);
				//	savePic();
				//	cout << "stop" << endl;
				//}				
			}
			else {
				updateSet(successBidRobID, aucInd);
			}


			allAucEd[aucInd] = true;
			circleTime++;
			cout << "circleTime  =" << circleTime << endl;
			if (circleTime > 320)
			{
				break;
			}
		} while (!aucCompleted(allAucEd));

		for (size_t i = 0; i < _robNum; i++)
		{
			cout << "rob" << i << "	set size = " << _vRobSetPtr->at(i).size() << endl;
		}

		cout << "auction end" << endl;
	}

	//bool MultiPlan::getMinLeaf(set<size_t> const & robSet, bex::VertexDescriptor &vd) const 
	//{
	//	double minDis = 99999;
	//	int resVd = -1;
	//	auto &graph = _ob_sGraph;
	//	for (auto it = robSet.begin(); it != robSet.end(); it++)
	//	{
	//		auto &cenInd = *it;
	//		auto neighborsIter = bt::adjacent_vertices(*it, _ob_sGraph);
	//		for (auto ni = neighborsIter.first; ni != neighborsIter.second; ++ni)
	//		{
	//			if (robSet.count(*ni) == 0)
	//			{
	//				//robSet.count
	//				double dis = bg::distance(graph[cenInd].pnt, graph[*ni].pnt);
	//				if (dis < minDis)
	//				{
	//					minDis = dis;
	//					resVd = *ni;
	//				}
	//			}
	//		}
	//	}
	//	if (resVd < 0)
	//	{
	//		return false;
	//	}
	//	vd = resVd;
	//	return true;
	//}

	bool MultiPlan::getMinLeaf(size_t const & robID, bex::VertexDescriptor & min_MegaBoxVd)
	{
		double UnCoverMinFit = 99999;
		double coverMinFit = 999999;
		int UnCoverResVd = -1;
		int coverResVd = -1;
		bool allCovered = true;
		auto &graph = _ob_sGraph;
		auto &robSet = (*_vRobSetPtr)[robID];
		auto &robNeiSet = (*_vRobNeiSetPtr)[robID];


		for (auto it = robNeiSet.begin(); it != robNeiSet.end(); it++)
		{
			bool inOtherSet = false;
			for (size_t i = 0; i < _robNum; i++)
			{
				if (i == robID) continue;
				if (_vRobSetPtr->at(i).count(it->first) == 1)
				{
					inOtherSet = true;
					break;
				}
			}
			if (!inOtherSet) {
				 double fit = -this->calFitNess(robID, it->first);
				// need optimal
				//double dis = bg::distance(graph[it->first].pnt, graph[it->second].pnt);
				if (fit < UnCoverMinFit)
				{
					UnCoverMinFit = fit;
					UnCoverResVd = it->first;
					allCovered = false;
				}
			}
			else
			{
				if (_notBidSetPtr->count(it->first) == 1) continue;
				double dis = bg::distance(graph[it->first].pnt, graph[it->second].pnt);
				if (dis < coverMinFit)
				{
					coverMinFit = dis;
					coverResVd = it->first;
				}
			}
		}
		if (UnCoverResVd != -1) min_MegaBoxVd = UnCoverResVd;
		else min_MegaBoxVd = coverResVd;
		return allCovered;
	}

	double MultiPlan::calFitNess(size_t const & robID, bex::VertexDescriptor const &megaBoxVd)
	{
		double fitNess = 0;
		auto &graph = _ob_sGraph;
		for (size_t i = 0; i < _robNum; i++)
		{
			auto &robSet = (*_vRobSetPtr)[i];
			if (i == robID) continue;
			for (auto it = robSet.begin(); it != robSet.end(); it++)
			{
				double dis = bg::distance(graph[it->first].pnt, graph[megaBoxVd].pnt);
				fitNess += dis;
			}
		}
		return fitNess;
	}

	size_t MultiPlan::minBidRob(size_t const & robAucNeer, bex::VertexDescriptor const & megaBoxID)
	{
		size_t minBid = 99999;
		size_t successBidID;
		for (size_t i = 0; i < _robNum; i++)
		{
			if (robAucNeer == i)
			{
				size_t bid = _vRobSetPtr->at(i).size();
				if (bid < minBid) {
					successBidID = i;
					minBid = bid;
				}
			}
			else
			{
				if (_vRobNeiSetPtr->at(i).count(megaBoxID) == 1)
				{
					size_t bid = _vRobSetPtr->at(i).size();
					if (bid < minBid) {
						successBidID = i;
						minBid = bid;
					}
				}
				if (_vRobSetPtr->at(i).count(megaBoxID) == 1)
				{
					auto &robSet = (*_vRobSetPtr)[i];
					vector<bex::VertexDescriptor> v_vd;
					for (auto it = robSet.begin(); it != robSet.end(); it++)
					{
						if (megaBoxID == it->first) continue;
						v_vd.push_back(it->first);
					}
					//all connect can bid
					if (_mainMap.allConnected(v_vd)) {
						size_t bid = _vRobSetPtr->at(i).size() - 1;
						if (bid < minBid) {
							successBidID = i;
							minBid = bid;
						}
					}
					else
					{
						minBid = 0;
						successBidID = i;
						_notBidSetPtr->insert(megaBoxID);
					}
				}
			}
		}
		return successBidID;
	}

	void MultiPlan::updateSet(size_t const & succBidID, bex::VertexDescriptor const & megaBoxVd)
	{

			auto &robSet = _vRobSetPtr->at(succBidID);
			auto &robNeiSet = _vRobNeiSetPtr->at(succBidID);
			robSet.insert(TreeEdge(megaBoxVd, robNeiSet[megaBoxVd]));
			//auto &robNeiSet = (*_vRobNeiSetPtr)[succBidID];
			robNeiSet.clear();

			for (auto it = robSet.begin(); it != robSet.end(); it++)
			{
				auto &cenInd = it->first;
				auto neighborsIter = bt::adjacent_vertices(cenInd, _ob_sGraph);
				for (auto ni = neighborsIter.first; ni != neighborsIter.second; ++ni)
				{
					if (robSet.count(*ni) == 0)
					{
						robNeiSet.insert(TreeEdge(*ni,cenInd));
					}
				}
			}
	}

	void MultiPlan::updateSetWithErase(size_t const & succBidID, bex::VertexDescriptor const & megaBoxVd)
	{
		size_t eraseID;
		for (size_t i = 0; i < _robNum; i++)
		{
			if (_vRobSetPtr->at(i).count(megaBoxVd) == 1)
			{
				eraseID = i;
				// do not need update
				if (succBidID == eraseID) return;
				_vRobSetPtr->at(i).erase(megaBoxVd);
				auto &eraseRobSet = _vRobSetPtr->at(i);
				vector< bex::VertexDescriptor> vEvd;
				for (auto &it: eraseRobSet)
				{
					if (megaBoxVd == it.second)
					{
						vEvd.push_back(it.first);
					}
				}
				for (auto &it: vEvd)
				{
					eraseRobSet.erase(it);
					auto neighborsIter = boost::adjacent_vertices(it, _ob_sGraph);
					for (auto ni = neighborsIter.first; ni != neighborsIter.second; ++ni)
					{
						if (eraseRobSet.count(*ni) == 1)
						{
							eraseRobSet.insert(TreeEdge(it, *ni));
							break;
						}
					}
				}
				//
				_notBidSetPtr->insert(megaBoxVd);
				break;
			}
		}

		auto &robSet = _vRobSetPtr->at(succBidID);
		auto &robNeiSet = _vRobNeiSetPtr->at(succBidID);
		robSet.insert(TreeEdge(megaBoxVd, robNeiSet[megaBoxVd]));
		//auto &robNeiSet = (*_vRobNeiSetPtr)[succBidID];
		robNeiSet.clear();

		for (auto it = robSet.begin(); it != robSet.end(); it++)
		{
			auto &cenInd = it->first;
			auto neighborsIter = bt::adjacent_vertices(cenInd, _ob_sGraph);
			for (auto ni = neighborsIter.first; ni != neighborsIter.second; ++ni)
			{
				if (robSet.count(*ni) == 0)
				{
					robNeiSet.insert(TreeEdge(*ni, cenInd));
				}
			}
		}
		


	}

	//size_t MultiPlan::minBidRob(size_t const & megaBoxID, size_t const & robAucNeer)
	//{
	//	size_t minBid = 99999;
	//	size_t successBidID;
	//	for (size_t i = 0; i < _robNum; i++)
	//	{
	//		if (robAucNeer == i)
	//		{
	//			size_t bid = _vRobSetPtr->at(i).size();
	//			if (bid < minBid) {
	//				successBidID = i;
	//				minBid = bid;
	//			}
	//		}
	//		else
	//		{
	//			if (_vRobNeiSetPtr->at(i).count(megaBoxID) == 1)
	//			{
	//				size_t bid = _vRobSetPtr->at(i).size();
	//				if (bid < minBid) {
	//					successBidID = i;
	//					minBid = bid;
	//				}
	//			}
	//			if (_vRobSetPtr->at(i).count(megaBoxID) == 1)
	//			{
	//				size_t bid = _vRobSetPtr->at(i).size() - 1;
	//				if (bid < minBid) {
	//					successBidID = i;
	//					minBid = bid;
	//				}
	//			}
	//		}
	//	}
	//	return successBidID;
	//}

	//void MultiPlan::updateSet(size_t const & succBidID, bex::VertexDescriptor const & MegaBoxVd)
	//{
	//	auto &robSet = _vRobSetPtr->at(succBidID);
	//	robSet.insert(MegaBoxVd);
	//	auto &robNeiSet = (*_vRobNeiSetPtr)[succBidID];
	//	robNeiSet.clear();

	//	for (auto it = robSet.begin(); it != robSet.end(); it++)
	//	{
	//		auto &cenInd = *it;
	//		auto neighborsIter = bt::adjacent_vertices(*it, _ob_sGraph);
	//		for (auto ni = neighborsIter.first; ni != neighborsIter.second; ++ni)
	//		{
	//			if (robSet.count(*ni) == 0)
	//			{
	//				robNeiSet.insert(*ni);
	//			}
	//		}
	//	}

	//}

}