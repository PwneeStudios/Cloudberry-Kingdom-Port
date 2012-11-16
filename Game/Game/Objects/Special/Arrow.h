#ifndef ARROW
#define ARROW

#include "../Game/Objects/Game Objects/GameObject.h"
#include "../Core/Graphics/Draw/Quads/PieceQuad.h"

namespace CloudberryKingdom
{
	class SimpleObject;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Arrow : public GameObject
	{
	public:
		enum Orientation
		{
			Orientation_LEFT,
			Orientation_RIGHT
		};
	public:
		std::shared_ptr<SimpleObject> MyObject;

		Arrow();

	private:
		int MyOrientation;

		/// <summary>
		/// Set the orientation of the arrow, to point left or to point right.
		/// </summary>
	public:
		void SetOrientation( Orientation orientation );

	private:
		float Scale;
	public:
		void SetScale( float Scale );

	private:
		void SetAnimation();

	public:
		void AnimStep();

	protected:
		virtual void MyPhsxStep();

	private:
		Vector2 PointToPos;
	public:
		void PointTo( Vector2 pos );

		void Update();

	protected:
		virtual void MyDraw();

	public:
		virtual void Move( Vector2 shift );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef ARROW
