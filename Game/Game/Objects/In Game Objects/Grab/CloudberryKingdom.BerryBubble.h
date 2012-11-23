#ifndef CLOUDBERRYKINGDOM_BERRYBUBBLE
#define CLOUDBERRYKINGDOM_BERRYBUBBLE

#include <global_header.h>

namespace CloudberryKingdom
{
	class CircleBox;
}

namespace CloudberryKingdom
{
	class DrawPile;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class EzTexture;
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
	class BerryBubble : public ObjectBase
	{
	public:
		std::shared_ptr<CircleBox> Box;

		std::shared_ptr<DrawPile> MyPile;
		std::shared_ptr<QuadClass> Berry, Bubble;

		float RotateSpeed;

		void Rotate( float degrees );

		virtual void MakeNew();

	private:
		static bool _TexturesInitialized;
		static std::shared_ptr<EzTexture> PoppedTexture, UnpoppedTexture, BubbleTexture;
	protected:
		virtual void SetTexture();

	public:
		void Die();

		BerryBubble( Vector2 pos );
		BerryBubble( bool BoxesOnly );
	protected:
		void Init( bool BoxesOnly );

	public:
		float Radius, PoppedRadius;
	protected:
		float Gravity;
	public:
		void Initialize( Vector2 pos );

		bool Popped;
		virtual void PhsxStep();

		virtual void Draw();

		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		bool AllowJumpOffOf;
		virtual void Interact( const std::shared_ptr<Bob> &bob );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CLOUDBERRYKINGDOM_BERRYBUBBLE
