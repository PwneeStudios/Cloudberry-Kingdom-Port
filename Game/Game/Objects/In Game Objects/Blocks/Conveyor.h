#ifndef CONVEYOR
#define CONVEYOR

#include <global_header.h>

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;



namespace CloudberryKingdom
{
	class ConveyorBlock : public BlockBase
	{
	public:
		std::shared_ptr<QuadClass> MyQuad, LeftEnd, RightEnd;

		virtual void MakeNew();

		virtual void Release();

		ConveyorBlock( bool BoxesOnly );

		float Speed;
	private:
		float u_offset;
		Vector2 texture_size;
		void SetUV();

		Vector2 Size;
	public:
		void Init( Vector2 center, Vector2 size );

		virtual void Reset( bool BoxesOnly );

		virtual void PhsxStep();

		virtual void PhsxStep2();

		void Update();

		virtual void Extend( Side side, float pos );

		virtual void Move( Vector2 shift );

		virtual void Draw();

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CONVEYOR
