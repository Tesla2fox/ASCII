#include "Splan.hpp"

namespace pl{
	void pl::Splan::pathPlanning()
	{
		spanningTreePrim();
		getNewGraph();
		searchPath();
	}

void Splan::drawGraph(size_t const &type,bool const &b_edge)
{
	bex::Graph *graphPtr;
	double gridStep;
	switch (type)
	{
	case graphType::base:{		
		gridStep = _mainMap.getGridStep();
		graphPtr = &_mainMap.getGraph(graphType::base);
		break;
	}
	case graphType::span: {
		gridStep = _mainMap.getGridStep() * 2;
		graphPtr = &_mainMap.getGraph(graphType::span);
		break;
	}
	case graphType::tree: {
		gridStep = _mainMap.getGridStep();
		graphPtr = &_m_tGraph;
		break;
	}
	default:
		break;
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

		if ((type == graphType::base)||(type ==graphType::tree))
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

void Splan::drawTree()
{
	auto &graph = _mainMap.getGraph(pl::graphType::span);
	for (size_t i = 0; i < _vTree.size(); i++)
	{
		bex::VertexProperty &sVert = graph[i];
		bex::VertexProperty &tVert = graph[_vTree[i]];


		svg::Polyline polyline_a(svg::Stroke(.3, svg::Color::Red));

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

void pl::Splan::spanningTreePrim()
{

	typedef bt::adjacency_list < bt::vecS, bt::vecS, bt::undirectedS,
		bt::property<bt::vertex_distance_t, int>, bt::property < bt::edge_weight_t, int > > SGraph;
	typedef std::pair < int, int >SE;
	auto &graph = _mainMap.getGraph(graphType::span);
	const int num_nodes = bt::num_vertices(graph);

	SE edges[] = { SE(0, 2), SE(1, 3), SE(1, 4), SE(2, 1), SE(2, 3),
		SE(3, 4), SE(4, 0)
	};

	int weights[] = { 1, 1, 2, 7, 3, 1, 1 };


	std::pair<bex::EdgeIterator, bex::EdgeIterator> _b2e_ei = boost::edges(graph);

	vector<size_t> vSvd, vTvd;
	auto edgeNum = bt::num_edges(graph);
	//auto edgesPtr = make_shared<SE>(new SE[edgeNum]);
	SE * edgesPtr = new SE[edgeNum];
	int * weightPtr = new int[edgeNum];
	//auto edgesPtr = make_shared<std::array<SE,edgeNum>>();
	size_t i = 0;
	for (auto eit = _b2e_ei.first; eit != _b2e_ei.second; eit++)
	{
		bex::EdgeDescriptor ed = *eit;
		bex::EdgeProperty &ep = graph[ed];
		bex::VertexDescriptor sVertd = boost::source(ed, graph);
		bex::VertexDescriptor tVertd = boost::target(ed, graph);
		vSvd.push_back(sVertd);
		vTvd.push_back(tVertd);
		edgesPtr[i] = SE(sVertd, tVertd);
		weightPtr[i] = ep.weight;
		i++;
		//cout << "w" << endl;
	}


#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
	Graph g(num_nodes);
	property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, g);
	for (std::size_t j = 0; j < sizeof(edges) / sizeof(E); ++j) {
		graph_traits<Graph>::edge_descriptor e; bool inserted;
		boost::tie(e, inserted) = add_edge(edges[j].first, edges[j].second, g);
		weightmap[e] = weights[j];
	}
#else
	//		SGraph g(edgesPtr, edgesPtr + sizeof(edgesPtr) / sizeof(SE), weightPtr, num_nodes);
	SGraph g(edgesPtr, edgesPtr + edgeNum, weightPtr, num_nodes);

#endif
	std::vector < bt::graph_traits < SGraph >::vertex_descriptor >
		p(num_vertices(g));

#if defined(BOOST_MSVC) && BOOST_MSVC <= 1300
	property_map<Graph, vertex_distance_t>::type distance = get(vertex_distance, g);
	property_map<Graph, vertex_index_t>::type indexmap = get(vertex_index, g);
	prim_minimum_spanning_tree
	(g, *vertices(g).first, &p[0], distance, weightmap, indexmap,
		default_dijkstra_visitor());
#else
	bt::prim_minimum_spanning_tree(g, &p[0]);
#endif
	_vTree.clear();
	_vTreeSg.clear();
	for (std::size_t i = 0; i != p.size(); ++i)
	{
		this->_vTree.push_back(p[i]);
#ifdef _DEBUG
		//cout << "_ob_sGraph_0   x =" << _ob_sGraph[i].pnt.x() << " y " << _ob_sGraph[i].pnt.y() << endl;
		//cout << "_ob_sGraph_1   x =" << _ob_sGraph[p[i]].pnt.x() << " y " << _ob_sGraph[p[i]].pnt.y() << endl;
#endif // _DEBUG
		this->_vTreeSg.push_back(bex::DSegment(_ob_sGraph[i].pnt, _ob_sGraph[p[i]].pnt));
		if (p[i] != i)
			std::cout << "parent[" << i << "] = " << p[i] << std::endl;
		else
			std::cout << "parent[" << i << "] = no parent" << std::endl;
	}
}

void Splan::getNewGraph()
{
	std::pair<bex::VertexIterator, bex::VertexIterator> _b2e_vi = boost::vertices(_ob_tGraph);
	size_t  i = 0;
	for (bex::VertexIterator vit = _b2e_vi.first; vit != _b2e_vi.second; vit++)
	{
		bex::VertexDescriptor vd = *vit;
		bex::VertexProperty vp = _ob_tGraph[vd];
		vp.EdgeState = false;
		boost::add_vertex(vp, _m_tGraph);
	}

	std::pair<bex::VertexIterator, bex::VertexIterator> vi = boost::vertices(_m_tGraph);
	for (bex::VertexIterator vit = vi.first; vit != vi.second; vit++)
	{
		bex::VertexDescriptor vd = *vit;
		if (_m_tGraph[vd].Type == bex::vertType::WayVert)
		{
			auto localIndex = _ob_tgraph2map[vd];
			auto vlocalIndex = getVerticalNeighbour(localIndex);
				//getSearchNeighbor(localIndex, graphType::span);
			std::vector<int> vvd;
			for (auto &it : vlocalIndex)
			{
				vvd.push_back(_ob_tmap2graph[it]);
			}

			for (auto &it : vvd)
			{
				if (_m_tGraph[it].EdgeState == false)
				{
					bex::DSegment sg(_m_tGraph[it].pnt, _m_tGraph[vd].pnt);
					if (this->treeIntersection(sg))
					//≈–∂œ «∑Òœ‡Ωª
					{
						//std::cout << "0-0" << endl;
					}
					else
					{
						bex::EdgeProperty ep;
						//ep.weight = bg::distance(sGraph[vd].pnt, sGraph[it].pnt);
						boost::add_edge(it, vd, ep, _m_tGraph);
					}
				}
			}
		}
		_m_tGraph[vd].EdgeState = true;
	}

}

void Splan::searchPath()
{
	GridIndex  cenGridIndex =  _mainMap.pnt2Index(_startPnt, 0);

}

bool Splan::treeIntersection(bex::DSegment const sg) const
{

	for (auto &it : this->_vTreeSg)
	{
		if (bg::intersects(it, sg))
		{
			return true;
		}
	}
	return false;

}

vector<GridIndex> Splan::getVerticalNeighbour(GridIndex const & cen_index)
{
	auto &grid = this->_ob_tGrid;

	vector<GridIndex> vIndex;

	auto &i = cen_index.first;
	auto &j = cen_index.second;
	auto neighbour = [=](GridIndex &ind, vector<GridIndex>  &vInd) {
		if (grid.count(ind))
		{
			if (grid.at(ind).type == bex::vertType::WayVert)
			{
				vInd.push_back(ind);
			}
		}
		return;
	};
	
	//left
	neighbour(GridIndex(i - 1, j), vIndex);
	//top 
	neighbour(GridIndex(i, j + 1), vIndex);
	//right
	neighbour(GridIndex(i + 1, j), vIndex);
	//botton
	neighbour(GridIndex(i, j - 1), vIndex);
	return vIndex;
}

}