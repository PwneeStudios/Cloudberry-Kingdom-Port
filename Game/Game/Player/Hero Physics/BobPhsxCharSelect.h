#ifndef BOBPHSXCHARSELECT
#define BOBPHSXCHARSELECT

#include <global_header.h>





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
