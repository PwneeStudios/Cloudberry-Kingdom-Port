#ifndef _DEATH
#define _DEATH

#include "_Obstacle.h"
#include "../Game/Objects/Bob/Bob.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
using namespace Microsoft::Xna::Framework;

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{
	class _Death : public _Obstacle
	{
	protected:
		Bob::BobDeathType DeathType;

	private:
		void InitializeInstanceFields();

public:
		_Death()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef _DEATH
