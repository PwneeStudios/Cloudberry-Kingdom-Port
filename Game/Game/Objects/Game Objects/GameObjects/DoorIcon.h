#ifndef DOORICON
#define DOORICON

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BobPhsx;
}

namespace CloudberryKingdom
{
	struct ObjectIcon;
}



namespace CloudberryKingdom
{
	struct DoorIcon : public GUI_Panel
	{
	
//C# TO C++ CONVERTER NOTE: The variable Level was renamed since it is named the same as a user-defined type:
		int Level_Renamed;
	
//C# TO C++ CONVERTER NOTE: The parameter Level was renamed since it is named the same as a user-defined type:
		DoorIcon( int Level_Renamed );

		DoorIcon( const std::shared_ptr<BobPhsx> &PhsxType, Vector2 pos, float Scale );

		std::wstring s;
		Upgrade upgrade;
		std::shared_ptr<BobPhsx> hero;
	
		std::shared_ptr<ObjectIcon> icon;
	
		void SetIcon( const std::shared_ptr<BobPhsx> &hero );
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
