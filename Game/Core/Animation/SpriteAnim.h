#ifndef SPRITEANIM
#define SPRITEANIM

#include <global_header.h>

namespace CloudberryKingdom
{
	/// <summary>
	/// Should be replaced. Right now this is used for drawing the players in the replays, but replays should instead be reusing the same draw code for the player as the normal draw code.
	/// </summary>
	class SpriteAnimGroup
	{
	public:
		std::map<int, SpriteAnim*> SpriteAnims;

		void Release();

		SpriteAnimGroup();

		void Init( const std::shared_ptr<ObjectClass> &Obj, Vector2 ExtraPadding, const std::shared_ptr<CloudberryKingdom::Lambda_2<std::unordered_map<int, SpriteAnim*>, Vector2> > &SpriteFunc );

		std::shared_ptr<Texture2D> Get( int anim, float t, Vector2 &padding );
	};

	class SpriteAnim
	{
	public:
		float dt;
		std::vector<Texture2D*> Frames;
		Vector2 Padding;

		void Release();
	};
}


#endif	//#ifndef SPRITEANIM
