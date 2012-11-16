#ifndef SINGLEDATA
#define SINGLEDATA

#include "StyleData.h"

namespace CloudberryKingdom
{
	class Rand;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class SingleData : public StyleData
	{
	public:
		Vector2 InitialDoorYRange;

		SingleData( const std::shared_ptr<Rand> &Rnd );

		virtual void Randomize();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SINGLEDATA
