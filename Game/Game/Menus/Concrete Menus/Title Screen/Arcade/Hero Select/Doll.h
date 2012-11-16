#ifndef DOLL
#define DOLL

#include <global_header.h>

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class PlayerData;
}

namespace CloudberryKingdom
{
	class BobPhsx;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;


#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)

#endif



namespace CloudberryKingdom
{
	class HeroDoll : public CkBaseMenu
	{
	public:
		HeroDoll( int Control );

	protected:
		virtual void ReleaseBody();

	public:
		std::shared_ptr<Bob> MyDoll;
		virtual void Init();

		virtual void OnAdd();

	private:
		std::shared_ptr<PlayerData> player;
	public:
		void MakeHeroDoll( const std::shared_ptr<BobPhsx> &hero );

	private:
		void SetPos();

	public:
		void SetPhsx();

		void UpdateColorScheme();

	protected:
		virtual void MyPhsxStep();

	public:
		void DrawBob();

	protected:
		virtual void MyDraw();
	};
}


#endif	//#ifndef DOLL
