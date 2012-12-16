#ifndef DOORICON
#define DOORICON

#include <global_header.h>

namespace CloudberryKingdom
{

	struct DoorIcon : public GUI_Panel
	{
	
		int Level_Renamed;
	
		DoorIcon( int Level_Renamed );
		boost::shared_ptr<DoorIcon> DoorIcon_Construct( int Level_Renamed );

		DoorIcon( const boost::shared_ptr<BobPhsx> &PhsxType, Vector2 pos, float Scale );
		boost::shared_ptr<DoorIcon> DoorIcon_Construct( const boost::shared_ptr<BobPhsx> &PhsxType, Vector2 pos, float Scale );

		std::wstring s;
		Upgrade upgrade;
		boost::shared_ptr<BobPhsx> hero;
	
		boost::shared_ptr<ObjectIcon> icon;
	
		void SetIcon( const boost::shared_ptr<BobPhsx> &hero );
		void SetIcon( Upgrade upgrade );
		void SetIcon( IconType type );

		void Init( const std::wstring &text );

		void Kill();
		void Kill( bool sound );

	
		virtual void MyPhsxStep();

		virtual void MyDraw();
	};
}


#endif	//#ifndef DOORICON
