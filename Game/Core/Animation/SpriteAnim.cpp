#include <global_header.h>















namespace CloudberryKingdom
{

	void SpriteAnimGroup::Release()
	{
		for ( std::unordered_map<int, SpriteAnim*>::const_iterator anim = SpriteAnims.begin(); anim != SpriteAnims.end(); ++anim )
			anim->second->Release();

		SpriteAnims.clear();
	}

	SpriteAnimGroup::SpriteAnimGroup()
	{
		SpriteAnims = std::unordered_map<int, SpriteAnim*>();
	}

	void SpriteAnimGroup::Init( const std::shared_ptr<ObjectClass> &Obj, Vector2 ExtraPadding, const std::shared_ptr<CloudberryKingdom::Lambda_2<std::unordered_map<int, SpriteAnim*>, Vector2> > &SpriteFunc )
	{
		// Make sure stickman is oriented correctly            
		Obj->xFlip = false;
		Obj->yFlip = false;
		Obj->ContainedQuadAngle = 0;

		Vector2 Padding = Vector2( 10, 90 ) + ExtraPadding;

		SpriteFunc->Apply( SpriteAnims, Padding );

		for ( std::unordered_map<int, SpriteAnim*>::const_iterator sprite = SpriteAnims.begin(); sprite != SpriteAnims.end(); ++sprite )
			sprite->second->Padding = Padding;
	}

	std::shared_ptr<Texture2D> SpriteAnimGroup::Get( int anim, float t, Vector2 &padding )
	{
		if ( !SpriteAnims.find( anim ) != SpriteAnims.end() )
			t = anim = 0;

		float dt = SpriteAnims[ anim ]->dt;
		int frame = __min( static_cast<int>( t / dt ), SpriteAnims[ anim ]->Frames->size() - 1 );
		padding = SpriteAnims[ anim ]->Padding;
		return SpriteAnims[ anim ]->Frames[ frame ];
	}

	void SpriteAnim::Release()
	{
		if ( Frames.size() > 0 )
			for ( int i = 0; i < Frames.size(); i++ )
				Frames[ i ]->Dispose();
	}
}
