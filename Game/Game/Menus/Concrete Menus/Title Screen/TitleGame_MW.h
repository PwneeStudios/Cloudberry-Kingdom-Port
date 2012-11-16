#ifndef TITLEGAME_MW
#define TITLEGAME_MW

#include <global_header.h>

namespace CloudberryKingdom
{
	class GameData;
}

namespace CloudberryKingdom
{
	class SimpleGameFactory;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class StartMenu_MW_Backpanel;
}

namespace CloudberryKingdom
{
	class StartMenu_MW_PressStart;
}


using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{
	class TitleGameData_MW_Factory : public SimpleGameFactory
	{
	public:
		virtual std::shared_ptr<GameData> Make();
	};

	class TitleGameData_MW : public TitleGameData
	{
	private:
		class _InitProxy : public Lambda
		{
		private:
			std::shared_ptr<TitleGameData_MW> tgdmw;

		public:
			_InitProxy( const std::shared_ptr<TitleGameData_MW> &tgdmw );

			void Apply();
		};

	public:
		static std::shared_ptr<SimpleGameFactory> Factory;

		virtual void Release();

		TitleGameData_MW();

		virtual void SetToReturnTo( int code );

		virtual void ReturnTo( int code );

	protected:
		virtual std::shared_ptr<Level> MakeLevel();

	public:
		std::shared_ptr<StartMenu_MW_Backpanel> BackPanel;
		std::shared_ptr<StartMenu_MW_PressStart> PressStart;
		virtual void Init();

	private:
		void _Init();

	public:
		virtual void AdditionalReset();

		virtual void PhsxStep();

		virtual void PostDraw();
	};
}


#endif	//#ifndef TITLEGAME_MW
