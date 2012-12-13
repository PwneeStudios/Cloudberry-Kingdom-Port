#ifndef HERO_DOLL_H
#define HERO_DOLL_H

#include <global_header.h>

namespace CloudberryKingdom
{
	struct HeroDoll : public CkBaseMenu
	{
	
		HeroDoll( int Control );
		std::shared_ptr<HeroDoll> HeroDoll_Construct( int Control );

	
		virtual void ReleaseBody();

	
		std::shared_ptr<Bob> MyDoll;
		virtual void Init();

		virtual void OnAdd();

	
		std::shared_ptr<PlayerData> player;
	
		void MakeHeroDoll( const std::shared_ptr<BobPhsx> &hero );

	
		void SetPos();

	
		void SetPhsx();

		void UpdateColorScheme();

	
		virtual void MyPhsxStep();

	
		void DrawBob();

	
		virtual void MyDraw();
	};
}


#endif	//#ifndef DOLL
