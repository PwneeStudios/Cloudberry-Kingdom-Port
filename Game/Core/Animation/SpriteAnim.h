#ifndef SPRITEANIM
#define SPRITEANIM

#include <global_header.h>

#include "Hacks/XNA/Texture2D.h"

namespace CloudberryKingdom
{

	struct SpriteAnim
	{
	
		float dt;
		std::vector<std::shared_ptr<Texture2D> > Frames;
		Vector2 Padding;

		void Release();
	};

	/// <summary>
	/// Should be replaced. Right now this is used for drawing the players in the replays, but replays should instead be reusing the same draw code for the player as the normal draw code.
	/// </summary>
	struct SpriteAnimGroup
	{
	
		std::map<int, std::shared_ptr<SpriteAnim> > SpriteAnims;

		void Release();

		SpriteAnimGroup();

		void Init( const std::shared_ptr<ObjectClass> &Obj, Vector2 ExtraPadding,
			std::shared_ptr<Lambda_2<std::map<int, std::shared_ptr<SpriteAnim> >, Vector2> > SpriteFunc );

		std::shared_ptr<Texture2D> Get( int anim, float t, Vector2 &padding );
	};

}


#endif	//#ifndef SPRITEANIM
