#ifndef ALERTBASE
#define ALERTBASE

#include <global_header.h>

namespace CloudberryKingdom
{
	class Lambda;
}

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class QuadClass;
}


using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

namespace CloudberryKingdom
{
	class AlertBaseMenu : public CkBaseMenu
	{
	private:
		class OkProxy : public Lambda
		{
		private:
			std::shared_ptr<AlertBaseMenu> abm;

		public:
			OkProxy( const std::shared_ptr<AlertBaseMenu> &abm );

			void Apply();
		};

		/// <summary>
		/// Called when the user presses OK.
		/// </summary>
	public:
		std::shared_ptr<Lambda> OnOk;

	protected:
		void Ok();

		virtual void ReleaseBody();

	public:
		AlertBaseMenu();

	private:
		Localization::Words Message, OkText;
	public:
		AlertBaseMenu( int Control, Localization::Words Message, Localization::Words OkText );

		AlertBaseMenu( bool CallBaseConstructor );

	protected:
		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

		std::shared_ptr<QuadClass> Backdrop;
	public:
		virtual void MakeBackdrop();

		virtual void Init();
	};
}


#endif	//#ifndef ALERTBASE
