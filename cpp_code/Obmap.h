#pragma once
#include "stadfx.h"
#include "bgeometry.h"
#include "bgraph.h"
#include "simple_svg.hpp"

namespace pl
{
	using  DRingPtr = shared_ptr<bex::DRing>;
	using  GridMap = std::map <std::pair<int, int>, bex::PointVert>;
	using  GridIndex = pair<int, int>;
	enum graphType{span,base,tree};
	class Obmap
	{
	public:
		Obmap(DRingPtr const & ringPtr, double const &step) :
			_m_rangePtr(ringPtr), _m_range(*ringPtr), _gridStep(step)
		{
#ifdef _DEBUG
			c_deg.open("D:\\py_code\\ASCII\\data\\map_debug.txt", std::ios::trunc);
#endif // _DEBUG
			vector<double> vx, vy;
			for (size_t i = 0; i < _m_range.size(); i++)
			{
				vx.push_back(_m_range.at(i).x());
				vy.push_back(_m_range.at(i).y());
			}
			mWsPoint1.x(*std::min_element(vx.begin(), vx.end()));
			mWsPoint1.y(*std::min_element(vy.begin(), vy.end()));


			mWsPoint3.x(*std::max_element(vx.begin(), vx.end()));
			mWsPoint3.y(*std::max_element(vy.begin(), vy.end()));

		}
		~Obmap();

		//debug msg
		void writeRange();
		void writeGraph(const size_t &type);

		void spanningTree();
		//
		void addObRing(bex::DRing const & obring) { m_vDRing.push_back(obring); }
		void addObRing(std::vector<double> const &vx, std::vector<double> const &vy);
		void addObGrid(GridIndex const &obGrid);
		void addObPnt(bex::DPoint const &pnt);
		void addObRingSet(bex::DRing const &obring);

		bool map2tGrid();
		bool map2sGrid();

		bool saveGraphSvg(size_t const & type);
		bool saveSvg();

		//
		bex::Graph& getsGraph() { return _sGraph; }
		bex::Graph &getGraph(const size_t &type) { if (type == graphType::base) { return _tGraph; } return _sGraph; }
		GridMap &getGridMap(const size_t &type) { if (type == graphType::base) { return _tGrid; } return _sGrid; }

		//type no use
		GridIndex pnt2Index(bex::DPoint const & pnt, int const &type);

		
		/////
		std::map<std::pair<int, int>, int> tmap2graph;
		std::map<int, std::pair<int, int>> tgraph2map;

		std::map<std::pair<int, int>, int> smap2graph;
		std::map<int, std::pair<int, int>> sgraph2map;
		/////

		const double &getGridStep() { return _gridStep; }
		bex::DPoint &getWsPoint3() { return mWsPoint3; }

		bool allConnected(vector<bex::VertexDescriptor> const &v_vd);

		vector<bex::VertexDescriptor> getTgraphVd(bex::VertexDescriptor const &svd);
		vector<GridIndex> getTgraphGridInd(GridIndex const & cenInd);


		//获取4个邻居节点
		std::vector<bex::VertexDescriptor> getSearchVerticalNeighbor(bex::VertexDescriptor const &cvd, size_t const &gridType);

		set<GridIndex> getsObSet() { return _sObSet; }
	private:

		//tgrid and the tgraph means the based grid
		//sgrid and sgraph means the spanning grid
		bex::Graph _tGraph;
		GridMap _tGrid;

		bex::Graph _sGraph;
		GridMap _sGrid;

		set<GridIndex> _sObSet;
		set<GridIndex> _tObSet;

		vector < bt::graph_traits <bex::Graph>::vertex_descriptor > vtree;
		//
		DRingPtr const _m_rangePtr;
		bex::DRing & _m_range;
		bex::DPoint mWsPoint1;
		bex::DPoint mWsPoint3;

		const double _gridStep;


		//write txt
		std::ofstream c_deg;

	
		//最大行
		size_t m_MaxRow;
		//最大列
		size_t m_MaxCol;


		//最大s行
		size_t m_sMaxRow;
		//最大s列
		size_t m_sMaxCol;

		//障碍物的信息
		std::vector<bex::DRing> m_vDRing;

		//获取8个邻居节点
		std::vector<GridIndex> getSearchNeighbor(GridIndex const &mindex,size_t const &gridType);

		//获取4个邻居节点
		std::vector<GridIndex> getSearchVerticalNeighbor(GridIndex const &cen_index, size_t const &gridType);

		bool IsConnected(bex::VertexDescriptor const &vd0, bex::VertexDescriptor const &vd1, size_t const &gridType);
	};
}
