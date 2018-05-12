#pragma once
#include "stadfx.h"
#include <tuple>
#include "ssconfig.hpp"
#include "bgeometry.h"

namespace cfg
{
	class ReadConfig
	{
	public:
		ReadConfig(const char *filename) :
			_m_fileName(filename)
		{}
		~ReadConfig();
		void read();
		//cfgTuple getCfg();
		//vTaskAgentPtr _m_vTaskAgentPtr;
		//vTaskPntPtr _m_vTaskPntPtr;
		//DisMapPtr _taskDisMatPtr;
		//DisMapPtr _ag2taskDisMatPtr;
		//vector<size_t> _encode;
		shared_ptr<vector<double>> _vRange_xPtr = nullptr;
		shared_ptr<vector<double>> _vRange_yPtr = nullptr;
		shared_ptr<bex::DRing> _RangePtr = nullptr;
	private:
		const char *_m_fileName;

	};
}