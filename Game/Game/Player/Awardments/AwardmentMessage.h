﻿#ifndef AWARDMENTMESSAGE
#define AWARDMENTMESSAGE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct AwardmentMessage : public CkBaseMenu
	{
	
		std::shared_ptr<QuadClass> Backdrop;

	
		AwardmentMessage( const std::shared_ptr<Awardment> &award );
		std::shared_ptr<AwardmentMessage> AwardmentMessage_Construct( const std::shared_ptr<Awardment> &award );

	
		virtual void MakeBackdrop();

	
		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

	
		std::shared_ptr<EzText> Text;
	
		void SetText( const std::shared_ptr<Awardment> &award );

	
		virtual void SizeAndPosition();

		int Step;
		virtual void MyPhsxStep();

	
		static const int Duration = static_cast<int>( 2.3 * 62 );
	
		bool ShouldDie();

	
		void Kill();
		void Kill( bool sound );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef AWARDMENTMESSAGE
