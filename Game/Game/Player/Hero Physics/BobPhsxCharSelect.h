#ifndef BOBPHSXCHARSELECT
#define BOBPHSXCHARSELECT

#include <global_header.h>
namespace CloudberryKingdom
{
	struct BobPhsxCharSelect : public BobPhsxNormal
	{
	
		bool OverrideAnimBehavior;

		virtual void PhsxStep2();

		virtual void AnimStep();

	
		void InitializeInstanceFields();

	
		BobPhsxCharSelect()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef BOBPHSXCHARSELECT
