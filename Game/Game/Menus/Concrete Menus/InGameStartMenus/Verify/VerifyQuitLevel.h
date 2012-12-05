#ifndef VERIFYQUITLEVEL
#define VERIFYQUITLEVEL

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuItem;
}




namespace CloudberryKingdom
{
	class VerifyQuitLevelMenu : public VerifyBaseMenu
	{
	private:
		class VerifyQuitOkLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		public:
			VerifyQuitOkLambda();

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	public:
		VerifyQuitLevelMenu( bool CallBaseConstructor );
		VerifyQuitLevelMenu( int Control );

		virtual void Init();

	private:
		void SetPos();
	};
}


#endif	//#ifndef VERIFYQUITLEVEL
