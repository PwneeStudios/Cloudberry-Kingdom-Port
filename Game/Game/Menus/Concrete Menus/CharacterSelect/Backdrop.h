#ifndef BACKDROP
#define BACKDROP

#include <global_header.h>

namespace CloudberryKingdom
{
	struct MenuItem;
}




namespace CloudberryKingdom
{
	struct CharSelectBackdrop : public CkBaseMenu
	{
	
		CharSelectBackdrop();

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const PresetPos &Preset, int Frames );

	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	
		virtual void OnAdd();

		virtual void Init();

	
		void SetPos();
	};
}


#endif	//#ifndef BACKDROP
