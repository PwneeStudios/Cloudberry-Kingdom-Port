#ifndef BACKDROP
#define BACKDROP

#include <global_header.h>

namespace CloudberryKingdom
{

	struct CharSelectBackdrop : public CkBaseMenu
	{
	
		CharSelectBackdrop();
		boost::shared_ptr<CharSelectBackdrop> CharSelectBackdrop_Construct();

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		virtual void OnAdd();

		virtual void Init();

	
		void SetPos();
	};
}


#endif	//#ifndef BACKDROP
