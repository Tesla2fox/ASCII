#include "Obmap.h"

namespace pl
{
	Obmap::~Obmap()
	{
	}
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
}