#ifndef SIGN
#define SIGN

#include <global_header.h>

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class Level;
}


namespace CloudberryKingdom
{
	class Sign : public ObjectBase
	{
	public:
		bool SkipPhsx;

		std::shared_ptr<QuadClass> MyQuad;

		virtual void MakeNew();

		Sign( bool BoxesOnly, const std::shared_ptr<Level> &level );

	private:
		int Count;
		bool OnState;
		void SetState( bool NewOnState );

	public:
		static int OffLength, OnLength;
		virtual void PhsxStep();

	private:
		bool OnScreen();

	public:
		virtual void Draw();

		Vector2 GetBottom();

		/// <summary>
		/// Moves the foot of the Sign to the specified position.
		/// </summary>
		/// <param name="pos"></param>
		void PlaceAt( Vector2 pos );

		void Update();

		virtual void Move( Vector2 shift );

		virtual void Reset( bool BoxesOnly );

		virtual void Write( const std::shared_ptr<BinaryWriter> &writer );
		virtual void Read( const std::shared_ptr<BinaryReader> &reader );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SIGN
