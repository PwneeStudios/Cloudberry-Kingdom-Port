#ifndef OBJECTVECTOR
#define OBJECTVECTOR

#include "Core/Lambdas/Lambda_1.h"
#include "Core/Animation/AnimationData_Vector.h"
#include "Core/Animation/AnimationData_Integer.h"

#include <small_header.h>

//#include "Core/WriteReadTools.h"
//#include "Core/Animation/AnimationData_Vector.h"
//#include "Core/Graphics/Draw/Object/ObjectClass.h"
//#include "Core/Graphics/Draw/Quads/BaseQuad.h"


#include "Hacks/NET/BinaryWriter.h"
#include "Hacks/NET/BinaryReader.h"


namespace CloudberryKingdom
{

	struct ObjectVector : public boost::enable_shared_from_this<ObjectVector>
	{
	
		struct DefaultCallbackLambda : public Lambda_1<Vector2>
		{
		
			boost::shared_ptr<ObjectVector> v;

		
			DefaultCallbackLambda( const boost::shared_ptr<ObjectVector> &v );

			void Apply( const Vector2 &NewPos );
		};

	
		AnimationData AnimData;

		Vector2 Pos, RelPos;
		boost::shared_ptr<BaseQuad> ParentQuad;
		boost::shared_ptr<ObjectVector> CenterPoint;
		boost::shared_ptr<Lambda_1<Vector2> > ModifiedEventCallback;

		void Release();

#if defined(EDITOR)
		static const int NumSaveStates = 10;
		std::vector<Vector2> SavedStates;

		boost::shared_ptr<ClickCallback> ClickEventCallback;
#endif

		void Write( const boost::shared_ptr<BinaryWriter> &writer, const boost::shared_ptr<ObjectClass> &MainObject );

		void Read( const boost::shared_ptr<BinaryReader> &reader, const boost::shared_ptr<ObjectClass> &MainObject );

#if defined(EDITOR)
		void SaveState( int StateIndex );

		void RecoverState( int StateIndex );
#endif

		void Clone( const boost::shared_ptr<ObjectVector> &dest );

		void Clone( const boost::shared_ptr<ObjectVector> &dest, bool CloneAnimData );

		void CopyAnim( const boost::shared_ptr<ObjectVector> &vec, int Anim );

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

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef OBJECTVECTOR
