#ifndef CHARSELECTMANAGER
#define CHARSELECTMANAGER

#include <global_header.h>

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace GamerServices
			{
				class SignedInEventArgs;
			}
		}
	}
}

namespace CloudberryKingdom
{
	class CharacterSelect;
}

namespace CloudberryKingdom
{
	class Lambda;
}

namespace CloudberryKingdom
{
	class GUI_Panel;
}

namespace CloudberryKingdom
{
	class FancyVector2;
}

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class Set;
}

namespace CloudberryKingdom
{
	class Hat;
}

namespace CloudberryKingdom
{
	class CharSelectBackdrop;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;

#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)

#endif




namespace CloudberryKingdom
{
	class CharacterSelectManager : public ViewReadWrite
	{
	private:
		class SignInGamerLambda : public Lambda
		{
		private:
			std::shared_ptr<SignedInEventArgs> e;
		public:
			SignInGamerLambda( const std::shared_ptr<SignedInEventArgs> &e );

			void Apply();
		};
	private:
		class _StartAllProxy : public Lambda
		{
		public:
			void Apply();
		};

	private:
		class NullLambda : public LambdaFunc_1<CharacterSelect*, bool>
		{
		public:
			NullLambda();

			bool Apply( const std::shared_ptr<CharacterSelect> &select );
		};

	private:
		class AfterFinishedHelper : public Lambda
		{
		public:
			void Apply();
		};

	public:
		static std::shared_ptr<Lambda> OnBack, OnDone;

		static std::shared_ptr<GUI_Panel> ParentPanel;

		virtual std::vector<std::wstring> GetViewables();

	private:
		static const std::shared_ptr<CharacterSelectManager> instance;
	public:
		const static std::shared_ptr<CharacterSelectManager> &getInstance() const;

		static std::vector<CharacterSelect*> CharSelect;
		static bool IsShowing;

	private:
		static std::shared_ptr<FancyVector2> CamPos;
	public:
		static std::shared_ptr<EzText> ChooseYourHero_Text;
	private:
		static bool Show_ChooseYourHero;

		static int ChooseYourHero_LerpLength;

		static Vector2 HidePos, ShowPos;

	public:
		CharacterSelectManager();

#if defined(XBOX) || defined(XBOX_SIGNIN)
	private:
		void SignedInGamer_SignedIn( const std::shared_ptr<Object> &sender, const std::shared_ptr<SignedInEventArgs> &e );

#endif

	public:
		static std::shared_ptr<Set<Hat*> > AvailableHats;
		static void UpdateAvailableHats();

		static std::shared_ptr<Set<Hat*> > AvailableBeards;
	private:
		static void UpdateAvailableBeards();

		static std::shared_ptr<CharSelectBackdrop> Backdrop;
	public:
		static void Start( const std::shared_ptr<GUI_Panel> &Parent );

	private:
		static void _StartAll();

		static void Start( int PlayerIndex, bool QuickJoin );

	public:
		static void FinishAll();

		static void Finish( int PlayerIndex, bool Join );

	private:
		static void EndCharSelect( int DelayOnReturn, int DelayKillCharSelect );

		static void Cleanup();

		static bool AllExited();

		static bool AllFinished();

		static bool AllNull();

		static std::shared_ptr<NullLambda> NullLambda_static;
	public:
		static int DrawLayer;
		static float BobZoom;
		static float ZoomMod;
		static void Draw();

	private:
		static void AfterFinished();

		static bool Active;
	public:
		static void PhsxStep();
	};
}


#endif	//#ifndef CHARSELECTMANAGER
