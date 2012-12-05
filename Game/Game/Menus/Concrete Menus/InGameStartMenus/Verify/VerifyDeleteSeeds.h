#ifndef VERIFYDELETESEEDS
#define VERIFYDELETESEEDS

#include <global_header.h>

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class Menu;
}


namespace CloudberryKingdom
{
	class VerifyDeleteSeeds : public VerifyBaseMenu
	{
	private:
		class VerifyDeleteYesGoLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<VerifyDeleteSeeds> vds;
		public:
			VerifyDeleteYesGoLambda( const std::shared_ptr<VerifyDeleteSeeds> &vds );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};

	private:
		class VerifyDeleteOnXLambda : public LambdaFunc_1<std::shared_ptr<Menu> , bool>
		{
		private:
			std::shared_ptr<VerifyDeleteSeeds> vds;
		public:
			VerifyDeleteOnXLambda( const std::shared_ptr<VerifyDeleteSeeds> &vds );

			bool Apply( const std::shared_ptr<Menu> &item );
		};

	private:
		class VerifyDeleteNoGoLambda : public Lambda_1<std::shared_ptr<MenuItem> >
		{
		private:
			std::shared_ptr<VerifyDeleteSeeds> vds;
		public:
			VerifyDeleteNoGoLambda( const std::shared_ptr<VerifyDeleteSeeds> &vds );

			void Apply( const std::shared_ptr<MenuItem> &item );
		};
	private:
		int NumSeeds;
	public:
		VerifyDeleteSeeds( int Control, int NumSeeds );

		virtual void Init();

	};
}


#endif	//#ifndef VERIFYDELETESEEDS
