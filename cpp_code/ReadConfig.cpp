#include "ReadConfig.h"
//#include "EncodeMat.hpp"

namespace cfg
{
	ReadConfig::~ReadConfig()
	{
	}

	void ReadConfig::read()
	{
		sscfg::ConfigFile co_list = sscfg::ConfigFile::load(_m_fileName);

		cout << "fileName is " << _m_fileName << endl;
		vector<double> range_x, range_y;
		_vRange_xPtr = make_shared<vector<double>>();
		_vRange_yPtr = make_shared<vector<double>>();
		_RangePtr = make_shared<bex::DRing>();
		co_list.get("range_x", range_x);
		co_list.get("range_y", range_y);

		for (size_t i = 0; i < range_x.size(); i++)
		{
			_vRange_xPtr->push_back(range_x[i]);
			_vRange_yPtr->push_back(range_y[i]);
			this->_RangePtr->push_back(bex::DPoint(range_x[i], range_y[i]));
		}

		
		cout << "read successs" << endl;
	}
}
