#ifndef BOBPHSXCHARSELECT
#define BOBPHSXCHARSELECT

#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class BobPhsxCharSelect : public BobPhsxNormal
	{
	public:
		bool OverrideAnimBehavior;

		virtual void PhsxStep2();

		virtual void AnimStep();

	private:
		void InitializeInstanceFields();

public:
		BobPhsxCharSelect()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef BOBPHSXCHARSELECT
