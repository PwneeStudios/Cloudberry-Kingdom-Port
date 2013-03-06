#ifndef LAVA
#define LAVA

#include <global_header.h>

namespace CloudberryKingdom
{
	struct QuadClass;
}

namespace CloudberryKingdom
{
	struct Bob;
}

namespace CloudberryKingdom
{
	struct ObjectBase;
}


namespace CloudberryKingdom
{
	struct LavaBlock : public BlockBase
	{
	
		virtual ~LavaBlock()
		{
#ifdef BOOST_BIN
			OnDestructor( "LavaBlock" );
#endif
		}


		boost::shared_ptr<QuadClass> MyQuad;

		virtual void MakeNew();

		virtual void Release();

		LavaBlock( bool BoxesOnly );

	
		float u_offset;
		Vector2 TextureSize;
		void SetUV();

	
		void Init( float top, float left, float right, float depth );

	
		Vector2 Size;
	
		void Init( Vector2 center, Vector2 size );

	
		virtual void SetQuad( Vector2 center, Vector2 size );

	
		virtual void Reset( bool BoxesOnly );

	
		void CollisionCheck( const boost::shared_ptr<Bob> &bob );

	
		virtual void PhsxStep();

		virtual void PhsxStep2();

		void Update();

		virtual void Extend( Side side, float pos );

		virtual void Move( Vector2 shift );

		virtual void Draw();

		virtual bool PreDecision( const boost::shared_ptr<Bob> &bob );

		virtual void Clone( const boost::shared_ptr<ObjectBase> &A );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LAVA
