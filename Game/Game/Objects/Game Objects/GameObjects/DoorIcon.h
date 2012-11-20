#ifndef DOORICON
#define DOORICON

#include <global_header.h>

namespace CloudberryKingdom
{
	class BobPhsx;
}

namespace CloudberryKingdom
{
	class ObjectIcon;
}



namespace CloudberryKingdom
{
	class DoorIcon : public GUI_Panel
	{
	private:
//C# TO C++ CONVERTER NOTE: The variable Level was renamed since it is named the same as a user-defined type:
		int Level_Renamed;
	public:
//C# TO C++ CONVERTER NOTE: The parameter Level was renamed since it is named the same as a user-defined type:
		DoorIcon( int Level_Renamed );

		DoorIcon( const std::shared_ptr<BobPhsx> &PhsxType, Vector2 pos, float Scale );

		std::wstring s;
		Upgrade upgrade;
		std::shared_ptr<BobPhsx> hero;
	private:
		std::shared_ptr<ObjectIcon> icon;
	public:
		void SetIcon( const std::shared_ptr<BobPhsx> &hero );
		void SetIcon( Upgrade upgrade );
		void SetIcon( IconType type );

		void Init( const std::wstring &text );

		void Kill();
		void Kill( bool sound );

	protected:
		virtual void MyPhsxStep();

		virtual void MyDraw();
	};
}


#endif	//#ifndef DOORICON
