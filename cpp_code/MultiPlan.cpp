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
	void MultiPlan::pathPlanning()
	{
		auction();
	}
	void MultiPlan::auction()
	{
		vector<vector<size_t>> _vRobSet(_robNum);
		for (size_t i = 0; i < this->_vStartPnt.size(); i++)
		{
			
			GridIndex robGridInd = _mainMap.pnt2Index(_vStartPnt[i], pl::graphType::span);
			bex::VertexDescriptor robVd = _ob_smap2graph[robGridInd];
			_vRobSet[i].push_back(robVd);
		}


	}
}