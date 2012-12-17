#include <global_header.h>

namespace CloudberryKingdom
{

	void SpriteAnimGroup::Release()
	{
		for ( std::map<int, boost::shared_ptr<SpriteAnim> >::iterator anim = SpriteAnims.begin(); anim != SpriteAnims.end(); ++anim )
			anim->second->Release();

		SpriteAnims.clear();
	}

	SpriteAnimGroup::SpriteAnimGroup()
	{
		SpriteAnims = std::map<int, boost::shared_ptr<SpriteAnim> >();
	}

	void SpriteAnimGroup::Init( const boost::shared_ptr<ObjectClass> &Obj, Vector2 ExtraPadding,
		boost::shared_ptr<Lambda_2<std::map<int, boost::shared_ptr<SpriteAnim> >, Vector2> > SpriteFunc )
	{
		// Make sure stickman is oriented correctly            
		Obj->xFlip = false;
		Obj->yFlip = false;
		Obj->ContainedQuadAngle = 0;

		Vector2 Padding = Vector2( 10, 90 ) + ExtraPadding;

		SpriteFunc->Apply( SpriteAnims, Padding );

		for ( std::map<int, boost::shared_ptr<SpriteAnim> >::const_iterator sprite = SpriteAnims.begin(); sprite != SpriteAnims.end(); ++sprite )
			sprite->second->Padding = Padding;
	}

	// FIXME: This Texture2D * used to be boost::shared_ptr<Texture2D>.
	boost::shared_ptr<Texture2D> SpriteAnimGroup::Get( int anim, float t, Vector2 &padding )
	{
		if ( SpriteAnims.find( anim ) == SpriteAnims.end() )
		{
			t = 0.f;
			anim = 0;
		}

		float dt = SpriteAnims[ anim ]->dt;
		int frame = __min( static_cast<int>( t / dt ), static_cast<int>( SpriteAnims[ anim ]->Frames.size() ) - 1 );
		padding = SpriteAnims[ anim ]->Padding;
		return SpriteAnims[ anim ]->Frames[ frame ];
	}

	void SpriteAnim::Release()
	{
		if ( Frames.size() > 0 )
			for ( size_t i = 0; i < Frames.size(); i++ )
				Frames[ i ]->Dispose();
	}
}
