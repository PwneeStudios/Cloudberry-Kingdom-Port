#ifndef LAVA
#define LAVA

#include <global_header.h>

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class Bob;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}







namespace CloudberryKingdom
{
	class LavaBlock : public BlockBase
	{
	public:
		std::shared_ptr<QuadClass> MyQuad;

		virtual void MakeNew();

		virtual void Release();

		LavaBlock( bool BoxesOnly );

	protected:
		float u_offset;
		Vector2 TextureSize;
		void SetUV();

	public:
		void Init( float top, float left, float right, float depth );

	private:
		Vector2 Size;
	public:
		void Init( Vector2 center, Vector2 size );

	protected:
		virtual void SetQuad( Vector2 center, Vector2 size );

	public:
		virtual void Reset( bool BoxesOnly );

	private:
		void CollisionCheck( const std::shared_ptr<Bob> &bob );

	public:
		virtual void PhsxStep();

		virtual void PhsxStep2();

		void Update();

		virtual void Extend( Side side, float pos );

		virtual void Move( Vector2 shift );

		virtual void Draw();

		virtual bool PreDecision( const std::shared_ptr<Bob> &bob );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef LAVA
