#include <global_header.h>

namespace CloudberryKingdom
{

	ObjectVector::DefaultCallbackLambda::DefaultCallbackLambda( const boost::shared_ptr<ObjectVector> &v )
	{
		this->v = v;
	}

	void ObjectVector::DefaultCallbackLambda::Apply( const Vector2 &NewPos )
	{
		v->Pos = NewPos;

		v->RelPosFromPos();
	}

	void ObjectVector::Release()
	{
		ParentQuad.reset();
		CenterPoint.reset();
		ModifiedEventCallback.reset();
	}

	void ObjectVector::Write( const boost::shared_ptr<BinaryWriter> &writer, const boost::shared_ptr<ObjectClass> &MainObject )
	{
		if ( ParentQuad == 0 || ParentQuad == MainObject->ParentQuad )
			writer->Write( -1 );
		else
		{
			std::vector<boost::shared_ptr<BaseQuad> >::iterator i = std::find( MainObject->QuadList.begin(),
				MainObject->QuadList.end(), ParentQuad );
			writer->Write( i - MainObject->QuadList.end() );
		}

		WriteReadTools::WriteVector2( writer, RelPos );
		WriteReadTools::WriteVector2( writer, Pos );
		AnimData.Write( writer );
	}

	void ObjectVector::Read( const boost::shared_ptr<BinaryReader> &reader, const boost::shared_ptr<ObjectClass> &MainObject )
	{
		int ParentQuadInt = reader->ReadInt32();
		if ( ParentQuadInt == -1 )
			ParentQuad = MainObject->ParentQuad;
		else
			ParentQuad = MainObject->QuadList[ ParentQuadInt ];

		WriteReadTools::ReadVector2( reader, RelPos );
		WriteReadTools::ReadVector2( reader, Pos );
		AnimData.Read( reader );
	}

#if defined(EDITOR)
	void ObjectVector::SaveState( int StateIndex )
	{
		SavedStates[ StateIndex ] = RelPos;
	}
#endif

#if defined(EDITOR)
	void ObjectVector::RecoverState( int StateIndex )
	{
		RelPos = SavedStates[ StateIndex ];
	}
#endif

	void ObjectVector::Clone( const boost::shared_ptr<ObjectVector> &dest )
	{
		Clone( dest, true );
	}

	void ObjectVector::Clone( const boost::shared_ptr<ObjectVector> &dest, bool CloneAnimData )
	{
		dest->Pos = Pos;
		dest->RelPos = RelPos;

		if ( CloneAnimData )
			dest->AnimData = AnimationData( AnimData );
		else
			dest->AnimData = AnimData;
	}

	void ObjectVector::CopyAnim( const boost::shared_ptr<ObjectVector> &vec, int Anim )
	{
		AnimData.CopyAnim( vec->AnimData, Anim );
	}

	ObjectVector::ObjectVector()
	{
		InitializeInstanceFields();
		AnimData.Init(); // = new AnimationData();

		Pos = Vector2();
		//ModifiedEventCallback = boost::make_shared<DefaultCallbackLambda>( this->shared_from_this() );

		CenterPoint.reset();
	}

	void ObjectVector::Move( Vector2 NewPos )
	{
		if ( ModifiedEventCallback != 0 )
			ModifiedEventCallback->Apply( NewPos );
	}

	void ObjectVector::RelPosFromPos()
	{
		if ( ParentQuad != 0 )
			ParentQuad->Set_RelPosFromPos( this->shared_from_this() );
		else
		{
			Vector2 C = Vector2();
			if ( CenterPoint != 0 )
				C = CenterPoint->Pos;

			RelPos = Pos - C;
		}
	}

	void ObjectVector::PosFromRelPos()
	{
		if ( ParentQuad != 0 )
			ParentQuad->Set_PosFromRelPos( this->shared_from_this() );
		else
		{
			Vector2 C = Vector2();
			if ( CenterPoint != 0 )
				C = CenterPoint->Pos;

			Pos = RelPos + C;
		}
	}

	void ObjectVector::InitializeInstanceFields()
	{
#if defined(EDITOR)
		SavedStates = std::vector<Vector2>( NumSaveStates );
#endif
	}
}
