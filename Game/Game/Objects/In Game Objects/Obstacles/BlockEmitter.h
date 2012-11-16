#ifndef BLOCKEMITTER
#define BLOCKEMITTER

#include <global_header.h>

namespace CloudberryKingdom
{
	class MovingPlatform;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}




namespace CloudberryKingdom
{
	class BlockEmitter : public ObjectBase
	{
	public:
		MovingPlatform::MoveType MyMoveType;
		float Amp;

	private:
		std::vector<MovingPlatform*> Platforms;

	public:
		virtual void Release();

		bool AlwaysOn, Active;
		Vector2 Range;

		PhsxData EmitData;
		int Delay, Offset;
		Vector2 Size;

		virtual void OnUsed();

		virtual void OnMarkedForDeletion();

		virtual void MakeNew();

		BlockEmitter( bool BoxesOnly );

		/// <summary>
		/// If true the emitter emits multiple blocks prior to the level starting.
		/// This simulates the behavior of the level having been running before starting.
		/// </summary>
		bool DoPreEmit;

		/// <summary>
		/// When true the emitter will PreEmit on the next phsx step
		/// </summary>
	private:
		bool SetToPreEmit;

	public:
		virtual void Reset( bool BoxesOnly );

	private:
		void PreEmit();

	public:
		bool GiveCustomRange;
		bool GiveLayer;
	private:
		void Emit( int offset );

	public:
		void AddPlatform( const std::shared_ptr<MovingPlatform> &platform );

		void RemovePlatform( const std::shared_ptr<MovingPlatform> &platform );

		virtual void PhsxStep();

		virtual void Move( Vector2 shift );

	private:
		BlockEmitter_Parameters::BoxStyle MyBoxStyle;
	public:
		void Init( Vector2 pos, const std::shared_ptr<Level> &level, BlockEmitter_Parameters::BoxStyle MyBoxStyle );

		virtual void Clone( const std::shared_ptr<ObjectBase> &A );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BLOCKEMITTER
