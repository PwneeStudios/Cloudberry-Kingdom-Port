#ifndef HELPBLURB
#define HELPBLURB

#include <global_header.h>

namespace CloudberryKingdom
{
	class Lambda;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;


namespace CloudberryKingdom
{
	class HelpBlurb : public CkBaseMenu
	{
	private:
		class SetText_ActionHelper : public Lambda
		{
		private:
			std::shared_ptr<HelpBlurb> hb;
			Localization::Words Word;

		public:
			SetText_ActionHelper( const std::shared_ptr<HelpBlurb> &hb, Localization::Words Word );

			void Apply();
		};

	public:
		HelpBlurb();

		virtual void Init();

		std::shared_ptr<Lambda> SetText_Action( Localization::Words Word );

		void SetText( Localization::Words Word );
	};
}


#endif	//#ifndef HELPBLURB
