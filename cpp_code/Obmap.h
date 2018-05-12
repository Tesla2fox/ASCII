#pragma once
#include "stadfx.h"
#include "bgeometry.h"
namespace pl
{
	using  DRingPtr = shared_ptr<bex::DRing>;

	class Obmap
	{
	public:
		Obmap(DRingPtr const & ringPtr):
			_m_rangePtr(ringPtr),_m_range(*ringPtr)
			{
#ifdef _DEBUG
				c_deg.open("D:\\py_code\\coverageMotionPlanning\\data\\map_debug.txt", std::ios::trunc);
#endif // _DEBUG
		}
		~Obmap();

		//debug msg
		void writeRange();

	private:

		DRingPtr const _m_rangePtr;
		bex::DRing & _m_range;
		
		//write txt
		std::ofstream c_deg;
		
	};
}
