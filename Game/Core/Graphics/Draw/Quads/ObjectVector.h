#ifndef OBJECTVECTOR
#define OBJECTVECTOR

#include <global_header.h>

namespace CloudberryKingdom
{
	class ObjectVector
	{
	private:
		class DefaultCallbackLambda : public Lambda_1<Vector2>
		{
		private:
			std::shared_ptr<ObjectVector> v;
		public:
			DefaultCallbackLambda( const std::shared_ptr<ObjectVector> &v );

			void Apply( Vector2 NewPos );
		};

	public:
		AnimationData AnimData;

		Vector2 Pos, RelPos;
		std::shared_ptr<BaseQuad> ParentQuad;
		std::shared_ptr<ObjectVector> CenterPoint;
		std::shared_ptr<Lambda_1<Vector2> > ModifiedEventCallback;

		void Release();

#if defined(EDITOR)
		static const int NumSaveStates = 10;
		std::vector<Vector2> SavedStates;

		std::shared_ptr<ClickCallback> ClickEventCallback;
#endif

		void Write( const std::shared_ptr<BinaryWriter> &writer, const std::shared_ptr<ObjectClass> &MainObject );

		void Read( const std::shared_ptr<BinaryReader> &reader, const std::shared_ptr<ObjectClass> &MainObject );

#if defined(EDITOR)
		void SaveState( int StateIndex );

		void RecoverState( int StateIndex );
#endif

		void Clone( const std::shared_ptr<ObjectVector> &dest );

		void Clone( const std::shared_ptr<ObjectVector> &dest, bool CloneAnimData );

		void CopyAnim( const std::shared_ptr<ObjectVector> &vec, int Anim );

		ObjectVector();

#if defined(EDITOR)
		void Click();
#endif

		void Move( Vector2 NewPos );

#if defined(EDITOR)
		void DefaultClickCallback();
#endif

		void RelPosFromPos();

		void PosFromRelPos();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef OBJECTVECTOR
