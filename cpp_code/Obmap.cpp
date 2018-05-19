#include "Obmap.h"

namespace pl
{
	Obmap::~Obmap()
	{
	}
	//write txt 
	void Obmap::writeRange()
	{
		c_deg<<"range_x ";
		for (size_t i = 0; i < _m_range.size(); i++)
		{
			c_deg << " " << _m_range.at(i).x();
		}
		c_deg << endl;

		c_deg << "range_y ";
		for (size_t i = 0; i < _m_range.size(); i++)
		{
			c_deg << " " << _m_range.at(i).y();
		}
		c_deg << endl;
	}
	void Obmap::writeGraph(const size_t &type)
	{
		
		c_deg << "gridStep " << this->_gridStep << endl;
		vector<string> vStr;
		size_t vstrIndex = 0;
		bex::Graph *graphPtr;

		if (type == graphType::base)
		{
			graphPtr = &_tGraph;
			vStr.push_back("grid_x");
			vStr.push_back("grid_y");
			vStr.push_back("svd");
			vStr.push_back("tvd");
		}
		else
		{
			graphPtr = &_sGraph;
			vStr.push_back("s_grid_x");
			vStr.push_back("s_grid_y");
			vStr.push_back("s_svd");
			vStr.push_back("s_tvd");
		}

		std::pair<bex::VertexIterator,bex::VertexIterator> _b2e_vi = boost::vertices(*graphPtr);

		std::vector<double> vx, vy;
		for (bex::VertexIterator vit = _b2e_vi.first; vit != _b2e_vi.second; vit++)
		{
			bex::VertexDescriptor vd =*vit;
			bex::VertexProperty &vp = (*graphPtr)[vd];
			auto const & pnt = vp.pnt;
			vx.push_back(pnt.x());
			vy.push_back(pnt.y());
		}
		c_deg << vStr[vstrIndex++];
		for (auto & it:vx)
		{
			c_deg << " " << it;
		}
		c_deg << endl;

		c_deg << vStr[vstrIndex++];
		for (auto & it : vy)
		{
			c_deg << " " << it;
		}
		c_deg << endl;

		std::pair<bex::EdgeIterator, bex::EdgeIterator> _b2e_ei = boost::edges(*graphPtr);
		
		vector<size_t> vSvd,vTvd;

		for (auto eit = _b2e_ei.first; eit != _b2e_ei.second; eit++)
		{
			bex::EdgeDescriptor ed = *eit;
			bex::EdgeProperty &ep = (*graphPtr)[ed];
			bex::VertexDescriptor sVertd = boost::source(ed, *graphPtr);
			bex::VertexDescriptor tVertd = boost::target(ed, *graphPtr);
			vSvd.push_back(sVertd);
			vTvd.push_back(tVertd);
		}

		c_deg << vStr[vstrIndex++];
		for (auto &it :vSvd)
		{
			c_deg << "  " << it;
		}
		c_deg << endl;

		c_deg << vStr[vstrIndex++];
		for (auto &it : vTvd)
		{
			c_deg << "  " << it;
		}
		c_deg << endl;
		
	}
	void Obmap::spanningTree()
	{
		typedef bt::adjacency_list < bt::vecS, bt::vecS, bt::undirectedS,
			bt::property<bt::vertex_distance_t, int>, bt::property < bt::edge_weight_t, int > > SGraph;
		typedef std::pair < int, int >SE;
		const int num_nodes = bt::num_vertices(this->_sGraph);

		SE edges[] = { SE(0, 2), SE(1, 3), SE(1, 4), SE(2, 1), SE(2, 3),
			SE(3, 4), SE(4, 0)
		};

		int weights[] = { 1, 1, 2, 7, 3, 1, 1 };


		std::pair<bex::EdgeIterator, bex::EdgeIterator> _b2e_ei = boost::edges(this->_sGraph);

		vector<size_t> vSvd, vTvd;
		auto edgeNum = bt::num_edges(_sGraph);
		//auto edgesPtr = make_shared<SE>(new SE[edgeNum]);
		SE * edgesPtr = new SE[edgeNum];
		int * weightPtr = new int[edgeNum];
		//auto edgesPtr = make_shared<std::array<SE,edgeNum>>();
		size_t i = 0;
		for (auto eit = _b2e_ei.first; eit != _b2e_ei.second; eit++)
		{
			bex::EdgeDescriptor ed = *eit;
			bex::EdgeProperty &ep = _sGraph[ed];
			bex::VertexDescriptor sVertd = boost::source(ed, _sGraph);
			bex::VertexDescriptor tVertd = boost::target(ed, _sGraph);
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

		for (std::size_t i = 0; i != p.size(); ++i)
		{
			vtree.push_back(p[i]);
			if (p[i] != i)
				std::cout << "parent[" << i << "] = " << p[i] << std::endl;
			else
				std::cout << "parent[" << i << "] = no parent" << std::endl;
		}
	}
	//
	void Obmap::addObRing(std::vector<double> const & vx, std::vector<double> const & vy)
	{
		bex::DRing ring;
		for (size_t i = 0; i < vx.size(); i++)
		{
			ring.push_back(bex::DPoint(vx.at(i), vy.at(i)));
		}
		m_vDRing.push_back(ring);

	}
	bool Obmap::map2tGrid()
	{
		this->_tGrid.clear();
		auto bais_x = this->mWsPoint3.x() - this->mWsPoint1.x();
		auto bais_y = this->mWsPoint3.y() - this->mWsPoint1.y();

		//the max col and the max row
		this->m_MaxCol = ceil(bais_x / this->_gridStep);
		this->m_MaxRow = ceil(bais_y / this->_gridStep);

		
		bex::PointVert pntUnit;
		for (size_t i = 0; i < m_MaxCol; i++)
		{
			pntUnit.pnt = this->mWsPoint1;
			//auto &pntW= pntUnit.pnt;
			pntUnit.pnt.x(this->_gridStep*i + pntUnit.pnt.x());
			for (size_t j = 0; j < m_MaxRow; j++)
			{
				pntUnit.pnt.y(this->_gridStep*j + this->mWsPoint1.y());
				pntUnit.type = bex::vertType::WayVert;

				for (auto &it : this->m_vDRing)
				{
					auto _BWithIn = bg::within(pntUnit.pnt, it);
					if (_BWithIn)
					{
						pntUnit.type = bex::vertType::ObVert;
						goto insertPnt;
					}
				}
				//for (auto &it : this->vSegment)
				//{
				//	double dis = bg::distance(pntUnit.pnt, it);
				//	if (dis < (this->gridStep/4))
				//	{
				//		pntUnit.type = bgeo::vertType::ShoulderVert;
				//		goto insertPnt;
				//	}
				//}


			insertPnt:
				std::pair<size_t, size_t> pntIndex(i, j);
				pntUnit.PntIndex = pntIndex;
				this->_tGrid.insert(std::pair<std::pair<int, int>, bex::PointVert>(pntUnit.PntIndex, pntUnit));
				//boost::add_vertex(pntUnit, this->_tGraph);
			}
		}
		//create graph
		int i = 0;
		for (auto & it : this->_tGrid)
		{
			bex::VertexProperty vp;
			vp.PntIndex = it.second.PntIndex;
			vp.pnt = it.second.pnt;
			vp.Type = it.second.type;
			vp.EdgeState = false;
			boost::add_vertex(vp, this->_tGraph);
			std::pair<int, int> localIndex;
			localIndex = it.first;
			tmap2graph.insert(std::pair<std::pair<int, int>, int>(localIndex, i));
			tgraph2map.insert(std::pair<int, std::pair<int, int>>(i, localIndex));
			i++;
		}
		//add edges of the graph 

		std::pair<bex::VertexIterator, bex::VertexIterator> vi = boost::vertices(this->_tGraph);
		for (bex::VertexIterator vit = vi.first; vit != vi.second; vit++)
		{
			bex::VertexDescriptor vd = *vit;
			if (this->_tGraph[vd].Type == bex::vertType::WayVert)
			{
				auto localIndex = tgraph2map[vd];
//				auto vlocalIndex = getSearchNeighbor(localIndex, graphType::base);
				auto vlocalIndex = getSearchVerticalNeighbor(localIndex, graphType::base);

				std::vector<int> vvd;
				for (auto &it : vlocalIndex)
				{
					vvd.push_back(tmap2graph[it]);
				}

				for (auto &it : vvd)
				{
					if (this->_tGraph[it].EdgeState == false)
					{
//						bgeo::DSegment sg(this->Tgraph[it].pnt, this->Tgraph[vd].pnt);
//						if (this->MapIntersection(sg))
						//判断是否相交
						{

						}
						{
							bex::EdgeProperty ep;
							ep.weight = bg::distance(_tGraph[vd].pnt, _tGraph[it].pnt);
							boost::add_edge(it, vd, ep, _tGraph);
						}
					}
				}
			}
			this->_tGraph[vd].EdgeState = true;
		}
		auto num_edges = boost::num_edges(this->_tGraph);
		cout << "num_edges = " << num_edges << endl;
		return false;
	}
	bool Obmap::map2sGrid()
	{
		this->_sGrid.clear();
		auto &sGrid = this->_sGrid;
		auto &sGraph = this->_sGraph;

		auto bais_x = this->mWsPoint3.x() - this->mWsPoint1.x();
		auto bais_y = this->mWsPoint3.y() - this->mWsPoint1.y();

		//the max col and the max row
		this->m_sMaxCol = ceil(bais_x / this->_gridStep/2);
		this->m_sMaxRow = ceil(bais_y / this->_gridStep/2);


		auto gridStep = _gridStep * 2;
		bex::PointVert pntUnit;
		bex::DPoint pnt(mWsPoint1.x() + _gridStep / 2, mWsPoint1.y() + _gridStep / 2);
		for (size_t i = 0; i < m_sMaxCol; i++)
		{
			pntUnit.pnt = pnt;
			//auto &pntW= pntUnit.pnt;
			pntUnit.pnt.x(gridStep*i + pntUnit.pnt.x());
			for (size_t j = 0; j < m_sMaxRow; j++)
			{
				pntUnit.pnt.y(gridStep*j + this->mWsPoint1.y()+ _gridStep / 2);
				pntUnit.type = bex::vertType::WayVert;

				for (auto &it : this->m_vDRing)
				{
					auto _BWithIn = bg::within(pntUnit.pnt, it);
					if (_BWithIn)
					{
						pntUnit.type = bex::vertType::ObVert;
						goto insertPnt;
					}
				}
				//for (auto &it : this->vSegment)
				//{
				//	double dis = bg::distance(pntUnit.pnt, it);
				//	if (dis < (this->gridStep/4))
				//	{
				//		pntUnit.type = bgeo::vertType::ShoulderVert;
				//		goto insertPnt;
				//	}
				//}


			insertPnt:
				std::pair<size_t, size_t> pntIndex(i, j);
				pntUnit.PntIndex = pntIndex;
				sGrid.insert(std::pair<std::pair<int, int>, bex::PointVert>(pntUnit.PntIndex, pntUnit));
				//boost::add_vertex(pntUnit, this->_tGraph);
			}
		}
		//create graph
		int i = 0;
		for (auto & it : sGrid)
		{
			bex::VertexProperty vp;
			vp.PntIndex = it.second.PntIndex;
			vp.pnt = it.second.pnt;
			vp.Type = it.second.type;
			vp.EdgeState = false;
			boost::add_vertex(vp, sGraph);
			std::pair<int, int> localIndex;
			localIndex = it.first;
			smap2graph.insert(std::pair<std::pair<int, int>, int>(localIndex, i));
			sgraph2map.insert(std::pair<int, std::pair<int, int>>(i, localIndex));
			i++;
		}
		//add edges of the graph 

		std::pair<bex::VertexIterator, bex::VertexIterator> vi = boost::vertices(sGraph);
		for (bex::VertexIterator vit = vi.first; vit != vi.second; vit++)
		{
			bex::VertexDescriptor vd = *vit;
			if (sGraph[vd].Type == bex::vertType::WayVert)
			{
				auto localIndex = sgraph2map[vd];
				//auto vlocalIndex = getSearchNeighbor(localIndex,graphType::span);
				auto vlocalIndex = getSearchVerticalNeighbor(localIndex, graphType::span);
				std::vector<int> vvd;
				for (auto &it : vlocalIndex)
				{
					vvd.push_back(smap2graph[it]);
				}

				for (auto &it : vvd)
				{
					if (sGraph[it].EdgeState == false)
					{
						//						bgeo::DSegment sg(this->Tgraph[it].pnt, this->Tgraph[vd].pnt);
						//						if (this->MapIntersection(sg))
						//判断是否相交
						{

						}
						{
							bex::EdgeProperty ep;
							ep.weight = bg::distance(sGraph[vd].pnt, sGraph[it].pnt);
							boost::add_edge(it, vd, ep, sGraph);
						}
					}
				}
			}
			sGraph[vd].EdgeState = true;
		}
		auto num_edges = boost::num_edges(sGraph);
		cout << "num_edges = " << num_edges << endl;
		return false;
	}
	bool Obmap::saveGraphSvg(size_t const & type)
	{
		{
		size_t *maxColPtr;
		size_t *maxRowPtr;
		double const *gridStepPtr;
		bex::Graph *graphPtr;
		string fileName;
		double gridStep;
		if (type == graphType::base)
		{
			maxColPtr = &m_MaxCol;
			maxRowPtr = &m_MaxRow;
			//gridStepPtr = &_gridStep;
			gridStep = _gridStep;
			graphPtr = &this->_tGraph;
			fileName = "base.svg";
		}
		else
		{
			maxColPtr = &m_sMaxCol;
			maxRowPtr = &m_sMaxRow;
			//gridStepPtr = &_sgridStep;
			graphPtr = &this->_sGraph;
			fileName = "span.svg";
			gridStep = _gridStep * 2;
		}

		auto &maxCol = (*maxColPtr);
		auto &maxRow = (*maxRowPtr);
		auto &graph = (*graphPtr);

		std::cout << "maxCol = " << maxCol << std::endl;
		std::cout << "maxRow = " << maxRow << std::endl;


		svg::Dimensions dimensions(this->mWsPoint3.x(), this->mWsPoint3.y());

		auto wtf = dimensions.height;
		std::cout << "height" << wtf << " width " << dimensions.width << std::endl;
		//deg::conf_debug << "height" << wtf << " width " << dimensions.width << std::endl;


		svg::Document doc(fileName, svg::Layout(dimensions, svg::Layout::BottomLeft));

		svg::Polygon border(svg::Stroke(2, svg::Color::Red));
		border << svg::Point(0, 0) << svg::Point(dimensions.width, 0)
			<< svg::Point(dimensions.width, dimensions.height) << svg::Point(0, dimensions.height);
		doc << border;


		for (auto &it : this->m_vDRing)
		{
			svg::Polygon ob(svg::Stroke(1, svg::Color::Green));

			for (size_t i = 0; i < it.size(); i++)
			{
				ob << svg::Point(it[i].x(), it[i].y());
			}
			doc << ob;
		}


		

		auto InitVp = graph[0];
		double init_x = InitVp.pnt.x();
		double init_y = InitVp.pnt.y();

		std::pair<bex::VertexIterator, bex::VertexIterator> _b2e_vi = boost::vertices(graph);
		size_t  i = 0;
		for (bex::VertexIterator vit = _b2e_vi.first; vit != _b2e_vi.second; vit++)
		{
			bex::VertexDescriptor vd = *vit;
			bex::VertexProperty &vp = graph[vd];
			double px = vp.pnt.x();
			double py = vp.pnt.y();
			//std::cout << "px" << px << std::endl;
			//std::cout << "py" << py << std::endl;

			//deg::conf_debug << "px" << px << std::endl;
			//deg::conf_debug << "py" << py << std::endl;

			svg::Point pnt(px, py);
			svg::Fill fill();
			svg::Stroke stroke(1, svg::Color::Cyan);

			switch (vp.Type)
			{
			case bex::vertType::ObVert:
			{
				doc << svg::Circle(pnt, gridStep, svg::Fill(svg::Color::Fuchsia), svg::Stroke(0.1, svg::Color(200, 250, 150)));
				break;
			}
			case bex::vertType::WayVert:
			{
				doc << svg::Circle(pnt, gridStep, svg::Fill(), svg::Stroke(0.1, svg::Color::Cyan));
				break;
			}
			case bex::vertType::EdgeObVert:
			{
				doc << svg::Circle(pnt, 5, svg::Color::Red);
				break;
			}
			case bex::vertType::ShoulderVert:
			{
				doc << svg::Circle(pnt, 5, svg::Color::Brown);
				break;
			}
			default:
				break;
			}
		}
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

			double spx = sVert.pnt.x() ;
			double spy = sVert.pnt.y() ;
			//std::cout << "px" << px << std::endl;
			//std::cout << "py" << py << std::endl;
			svg::Point spnt(spx, spy);

			double tpx = tVert.pnt.x() ;
			double tpy = tVert.pnt.y() ;
			//std::cout << "px" << px << std::endl;
			//std::cout << "py" << py << std::endl;
			svg::Point tpnt(tpx, tpy);
			polyline_a << spnt << tpnt;
			doc << polyline_a;
		}

		doc.save();
	}

		return false;
	}
	bool Obmap::saveSvg()
	{

		svg::Dimensions dimensions(this->mWsPoint3.x(), this->mWsPoint3.y());

		auto wtf = dimensions.height;
		std::cout << "height" << wtf << " width " << dimensions.width << std::endl;
		//deg::conf_debug << "height" << wtf << " width " << dimensions.width << std::endl;


		svg::Document doc("b2.svg", svg::Layout(dimensions, svg::Layout::BottomLeft));

		//不画出界限
		//svg::Polygon border(svg::Stroke(2, svg::Color::Red));
		//border << svg::Point(0, 0) << svg::Point(dimensions.width, 0)
		//	<< svg::Point(dimensions.width, dimensions.height) << svg::Point(0, dimensions.height);
		//doc << border;


		std::pair<bex::VertexIterator, bex::VertexIterator> _b2e_vi = boost::vertices(this->_tGraph);
		size_t  i = 0;
		for (bex::VertexIterator vit = _b2e_vi.first; vit != _b2e_vi.second; vit++)
		{
			bex::VertexDescriptor vd = *vit;
			bex::VertexProperty &vp = this->_tGraph[vd];
			double px = vp.pnt.x();
			double py = vp.pnt.y();
//			std::cout << "px" << px << std::endl;
//			std::cout << "py" << py << std::endl;

			//deg::conf_debug << "px" << px << std::endl;
			//deg::conf_debug << "py" << py << std::endl;

			svg::Point pntc(px, py);
			svg::Point pnt(px - _gridStep / 2, py + _gridStep / 2);
			svg::Fill fill();
			svg::Stroke stroke(1, svg::Color::Cyan);

			switch (vp.Type)
			{
			case bex::vertType::ObVert:
			{
				doc << svg::Rectangle(pnt, _gridStep, _gridStep, svg::Fill(svg::Color::Fuchsia), svg::Stroke(0.1, svg::Color::Cyan));
				doc << svg::Circle(pntc, _gridStep, svg::Fill(svg::Color::Fuchsia), svg::Stroke(0.1, svg::Color::Cyan));
				break;
			}
			case bex::vertType::WayVert:
			{
				doc << svg::Rectangle(pnt, _gridStep,_gridStep, svg::Fill(), svg::Stroke(0.1, svg::Color::Cyan));
				doc << svg::Circle(pntc, _gridStep, svg::Fill(), svg::Stroke(0.1, svg::Color::Cyan));
				break;
			}
			case bex::vertType::EdgeObVert:
			{
				doc << svg::Circle(pnt, 5, svg::Color::Red);
				break;
			}
			case bex::vertType::ShoulderVert:
			{
				doc << svg::Circle(pnt, 5, svg::Color::Brown);
				break;
			}
			default:
				break;
			}
		}


		doc.save();
		return false;
	}
	GridIndex Obmap::pnt2Index(bex::DPoint const & pnt, int const & type)
	{
		GridMap * gridPtr;
		double gridStep;
		if (type == pl::graphType::base)
		{
			gridPtr = &this->_tGrid;
			gridStep = _gridStep;
		}
		else
		{
			gridPtr = &this->_sGrid;
			gridStep = _gridStep * 2;
		}
		GridIndex rindex;
		rindex.first = -1;
		rindex.second = -1;

		GridIndex initIndex;
		initIndex.first = 0;
		initIndex.second = 0;

		double _min_x = (*gridPtr)[initIndex].pnt.x() - gridStep/2;
		double _min_y = (*gridPtr)[initIndex].pnt.y() - gridStep/2;

		double _i_x = (*gridPtr)[initIndex].pnt.x();
		double _i_y = (*gridPtr)[initIndex].pnt.y();

		
		if (pnt.y()<_min_y)
		{
			return rindex;
		}
		if (pnt.x()<_min_x)
		{
			return rindex;
		}
		auto bais_x = pnt.x() - _min_x;
		auto bais_y = pnt.y() - _min_y;
		auto p_col = floor(bais_x / gridStep);
		auto p_row = floor(bais_y / gridStep);

		if (p_col>m_MaxCol)
		{
			return rindex;
		}
		if (p_row>this->m_MaxRow)
		{
			return rindex;
		}
		rindex.first = p_col;
		rindex.second = p_row;
		return rindex;
	}
	bool Obmap::allConnected(vector<bex::VertexDescriptor> const & v_vd) 
	{
		using CGraph = boost::adjacency_list<bt::vecS, bt::vecS, bt::undirectedS>;
		CGraph cg;
		for (size_t i = 0; i < v_vd.size(); i++)
		{
			for (size_t j = i; j < v_vd.size(); j++)
			{
				if (IsConnected(v_vd[i], v_vd[j],pl::graphType::span))
				{
					bt::add_edge(i, j, cg);
				}
			}
		}
		vector<int> component(bt::num_vertices(cg));
		int num = bt::connected_components(cg, &component[0]);
		if (num == 1) return true;
		return false;
	}
	std::vector<GridIndex> Obmap::getSearchNeighbor(GridIndex const & mindex, size_t const &gridType)
	{
		///return std::vector<GridIndex>();
		//
		GridMap *gridPtr;
		if (gridType == graphType::base)
		{
			gridPtr = &this->_tGrid;
		}
		else
		{
			gridPtr = &this->_sGrid;
		}
		auto &grid = (*gridPtr);

		std::vector<GridIndex> vIndex;
		//size_t dirIndex = 0;
		for (auto i = mindex.first - 1; i <= (mindex.first + 1); i++)
		{
			for (auto j = mindex.second - 1; j <= (mindex.second + 1); j++)
			{

				if (grid.count(GridIndex(i, j)) == 1)
				{
					if ((i == mindex.first) && (j == mindex.second))
					{
					}
					else
					{
						if (grid[GridIndex(i, j)].type == bex::vertType::WayVert)
						{
							vIndex.push_back(GridIndex(i, j));
						}
					}
				}
			}
		}
		return vIndex;
	}
	std::vector<GridIndex> Obmap::getSearchVerticalNeighbor(GridIndex const & cen_index, size_t const & gridType)
	{
		GridMap *gridPtr;
		if (gridType == graphType::base)
		{
			gridPtr = &this->_tGrid;
		}
		else
		{
			gridPtr = &this->_sGrid;
		}
		auto &grid = (*gridPtr);

		vector<pair<GridIndex, size_t>> res;
		vector<GridIndex> vIndex;

		auto &i = cen_index.first;
		auto &j = cen_index.second;
		auto neighbour = [=](GridIndex &ind, vector<GridIndex>  &vInd) {
			if (grid.count(ind))
			{
				if (grid.at(ind).type == bex::vertType::WayVert)
				{
					vInd.push_back(ind);
					return true;
				}
			}
			return false;
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
	bool Obmap::IsConnected(bex::VertexDescriptor const & vd0, bex::VertexDescriptor const & vd1, size_t const & gridType)
	{

		const GridMap *gridPtr;
//		map<std::pair<int, int>, int>  map2graphPtr;
//		const map<int, std::pair<int, int>>  graph2mapPtr;
		GridIndex gridInd0;
		GridIndex gridInd1;
		if (gridType == graphType::base)
		{
			gridPtr = &this->_tGrid;
			gridInd0  = sgraph2map[vd0];
			gridInd1  = sgraph2map[vd1];
		}
		else
		{
			gridPtr = &this->_sGrid;
			gridInd0 = tgraph2map[vd0];
			gridInd1 = tgraph2map[vd1];
		}
		auto &grid = (*gridPtr);	
		if (gridInd0.first == gridInd1.first)
		{
			if (gridInd0.second == (gridInd1.second - 1)) return true;
			if (gridInd0.second == (gridInd1.second + 1)) return true;
		}
		if (gridInd0.second == gridInd1.second)
		{
			if (gridInd0.first == (gridInd1.first - 1)) return true;
			if (gridInd0.first == (gridInd1.first + 1)) return true;
		}
		return false;
	}
}