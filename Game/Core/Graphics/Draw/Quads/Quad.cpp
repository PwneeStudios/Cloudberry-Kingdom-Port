#include <global_header.h>










namespace CloudberryKingdom
{

	Quad::UpdateCenterLambda::UpdateCenterLambda( const std::shared_ptr<Quad> &quad )
	{
		this->quad = quad;
	}

	void Quad::UpdateCenterLambda::Apply( Vector2 NewPos )
	{
		quad->Center->Pos = NewPos;
		quad->Center->RelPosFromPos();
	}

	Quad::UpdatexAxisLambda::UpdatexAxisLambda( const std::shared_ptr<Quad> &quad )
	{
		this->quad = quad;
	}

	void Quad::UpdatexAxisLambda::Apply( Vector2 NewPos )
	{
		float l = ( NewPos - quad->Center->Pos )->Length();
		Vector2 axis = NewPos - quad->Center->Pos;
		axis.Normalize();
		quad->xAxis->Pos = __max( l,.0125f ) * axis + quad->Center->Pos;

		quad->yAxis->Pos.X = -( NewPos.Y - quad->Center->Pos.Y );
		quad->yAxis->Pos.Y = NewPos.X - quad->Center->Pos.X;
		quad->yAxis->Pos += quad->Center->Pos;

		quad->xAxis->RelPosFromPos();
		quad->yAxis->RelPosFromPos();
	}

	Quad::UpdateyAxisLambda::UpdateyAxisLambda( const std::shared_ptr<Quad> &quad )
	{
		this->quad = quad;
	}

	void Quad::UpdateyAxisLambda::Apply( Vector2 NewPos )
	{
		float L = Vector2::Distance( quad->yAxis->Pos, quad->Center->Pos );

		quad->yAxis->Pos = NewPos - quad->Center->Pos;
		quad->yAxis->Pos.Normalize();
		quad->yAxis->Pos *= L;
		quad->yAxis->Pos += quad->Center->Pos;

		quad->xAxis->Pos = quad->xAxis->Pos - ( quad->yAxis->Pos - quad->Center->Pos ) * Vector2::Dot( quad->xAxis->Pos - quad->Center->Pos, quad->yAxis->Pos - quad->Center->Pos ) / ( quad->yAxis->Pos - quad->Center->Pos )->LengthSquared();
		quad->xAxis->Pos = quad->xAxis->Pos - quad->Center->Pos;
		quad->xAxis->Pos.Normalize();
		quad->xAxis->Pos *= L;
		quad->xAxis->Pos += quad->Center->Pos;

		quad->xAxis->RelPosFromPos();
		quad->yAxis->RelPosFromPos();
	}

	void Quad::Release()
	{
		BaseQuad::Release();

		Center->Release();
		Center.reset();
		xAxis->Release();
		xAxis.reset();
		yAxis->Release();
		yAxis.reset();
		for ( int i = 0; i < 4; i++ )
			Corner[ i ]->Release();
		Corner.clear();
	}

	void Quad::Resize()
	{
		float width = ( Corner[ 1 ]->RelPos - Corner[ 0 ]->RelPos )->Length();
		Vector2 NewSize = Vector2( MyTexture->Width, MyTexture->Height );
		NewSize *= .5f * width / MyTexture->Width;
		ScaleCorners( NewSize );
	}

	void Quad::MirrorUV_Horizontal()
	{
		Vector2 hold;

		hold = Vertices[ 0 ].uv;
		Vertices[ 0 ].uv = Vertices[ 1 ].uv;
		Vertices[ 1 ].uv = hold;

		hold = Vertices[ 2 ].uv;
		Vertices[ 2 ].uv = Vertices[ 3 ].uv;
		Vertices[ 3 ].uv = hold;
	}

	void Quad::CopyAnim( const std::shared_ptr<BaseQuad> &basequad, int Anim )
	{
		std::shared_ptr<Quad> quad = dynamic_cast<Quad*>( basequad );
		if ( 0 != quad )
		{
			Center->CopyAnim( quad->Center, Anim );
			xAxis->CopyAnim( quad->xAxis, Anim );
			yAxis->CopyAnim( quad->yAxis, Anim );
			for ( int i = 0; i < 4; i++ )
				Corner[ i ]->CopyAnim( quad->Corner[ i ], Anim );
		}
	}

	void Quad::CopyAnimShallow( const std::shared_ptr<BaseQuad> &basequad, int Anim )
	{
		std::shared_ptr<Quad> quad = dynamic_cast<Quad*>( basequad );
		if ( 0 != quad )
		{
			Center->AnimData = quad->Center->AnimData;
			xAxis->AnimData = quad->xAxis->AnimData;
			yAxis->AnimData = quad->yAxis->AnimData;
			for ( int i = 0; i < 4; i++ )
				Corner[ i ]->AnimData = quad->Corner[ i ]->AnimData;
		}
	}

	void Quad::SetHold()
	{
		Center->AnimData.Hold = Center->RelPos;
		xAxis->AnimData.Hold = xAxis->RelPos;
		yAxis->AnimData.Hold = yAxis->RelPos;
		for ( int i = 0; i < 4; i++ )
			Corner[ i ]->AnimData->Hold = Corner[ i ]->RelPos;
	}

	void Quad::ReadAnim( int anim, int frame )
	{
		Center->RelPos = Center->AnimData.Get( anim, frame );
		xAxis->RelPos = xAxis->AnimData.Get( anim, frame );
		yAxis->RelPos = yAxis->AnimData.Get( anim, frame );
		for ( int i = 0; i < 4; i++ )
			Corner[ i ]->RelPos = Corner[ i ]->AnimData->Get( anim, frame );

		if ( getTextureIsAnimated() && UpdateSpriteAnim && anim < TextureAnim->Anims.size() && TextureAnim->Anims[ anim ].Data.size() > 0 )
		{
			std::shared_ptr<CloudberryKingdom::EzTexture> data = TextureAnim->Calc( anim, frame );
			MyTexture = data;

			Vertices[ 0 ].uv = Vector2( 0, 0 );
			Vertices[ 1 ].uv = Vector2( 1, 0 );
			Vertices[ 2 ].uv = Vector2( 0, 1 );
			Vertices[ 3 ].uv = Vector2( 1, 1 );
		}
	}

	void Quad::Record( int anim, int frame, bool UseRelativeCoords )
	{
		if ( UseRelativeCoords )
		{
			Center->AnimData.Set( Center->RelPos, anim, frame );
			xAxis->AnimData.Set( xAxis->RelPos, anim, frame );
			yAxis->AnimData.Set( yAxis->RelPos, anim, frame );
			for ( int i = 0; i < 4; i++ )
				Corner[ i ]->AnimData->Set( Corner[ i ]->RelPos, anim, frame );
		}
		else
		{
			Center->AnimData.Set( Center->Pos, anim, frame );
			xAxis->AnimData.Set( xAxis->Pos, anim, frame );
			yAxis->AnimData.Set( yAxis->Pos, anim, frame );
			for ( int i = 0; i < 4; i++ )
				Corner[ i ]->AnimData->Set( Corner[ i ]->Pos, anim, frame );
		}
	}

	void Quad::ModifyAxis( const std::shared_ptr<ObjectVector> &axis, int anim, int frame, ChangeMode RecordMode )
	{
		Vector2 Change_axis = CoreMath::CartesianToPolar( axis->RelPos ) - CoreMath::CartesianToPolar( axis->AnimData.Get( anim, frame ) );
		Change_axis.Y = 1 + Change_axis.Y / axis->AnimData.Get( anim, frame ).Length();

		for ( int _anim = 0; _anim < axis->AnimData.Anims.size(); _anim++ )
		{
			if ( RecordMode == ChangeMode_SINGLE_ANIM && _anim != anim )
				continue;

			if ( axis->AnimData.Anims[ _anim ].Data.size() > 0 )
				for ( int _frame = 0; _frame < axis->AnimData.Anims[ _anim ].Data.size(); _frame++ )
					if ( anim != _anim || frame != _frame )
					{
						Vector2 polar = CoreMath::CartesianToPolar( axis->AnimData.Anims[ _anim ].Data[ _frame ] );
						polar.X += Change_axis.X;
						polar.Y *= Change_axis.Y;
						axis->AnimData.Anims[ _anim ].Data[ _frame ] = CoreMath::PolarToCartesian( polar );
					}
		}
	}

	Microsoft::Xna::Framework::Vector2 Quad::ToAxisCoordinates( Vector2 v, Vector2 xAxisPos, Vector2 yAxisPos )
	{
		return Vector2( Vector2::Dot( v, xAxisPos ) / xAxisPos.Length(), Vector2::Dot(v, yAxisPos) / yAxisPos.Length() );
	}

	Microsoft::Xna::Framework::Vector2 Quad::FromAxisCoordinates( Vector2 v, Vector2 xAxisPos, Vector2 yAxisPos )
	{
		return v.X * xAxisPos / xAxisPos.Length() + v.Y * yAxisPos / yAxisPos.Length();
	}

	void Quad::ModifyPoint( const std::shared_ptr<ObjectVector> &point, int anim, int frame, ChangeMode RecordMode )
	{
		Vector2 Change_point = ToAxisCoordinates( point->RelPos - point->AnimData.Get( anim, frame ), xAxis->RelPos, yAxis->RelPos );

		for ( int _anim = 0; _anim < point->AnimData.Anims.size(); _anim++ )
		{
			if ( RecordMode == ChangeMode_SINGLE_ANIM && _anim != anim )
				continue;

			if ( point->AnimData.Anims[ _anim ].Data.size() > 0 )
				for ( int _frame = 0; _frame < point->AnimData.Anims[ _anim ].Data.size(); _frame++ )
					if ( anim != _anim || frame != _frame )
					{
						Vector2 v = ToAxisCoordinates( point->AnimData.Get( _anim, _frame ), xAxis->AnimData.Get( _anim, _frame ), yAxis->AnimData.Get( _anim, _frame ) );
						v += Change_point;
						point->AnimData.Anims[ _anim ].Data[ _frame ] = FromAxisCoordinates( v, xAxis->AnimData.Get( _anim, _frame ), yAxis->AnimData.Get( _anim, _frame ) );
					}
		}
	}

	void Quad::ModifyAllRecords( int anim, int frame, ChangeMode RecordMode )
	{
		for ( int i = 0; i < 4; i++ )
			ModifyPoint( Corner[ i ], anim, frame, RecordMode );

		ModifyAxis( xAxis, anim, frame, RecordMode );
		ModifyAxis( yAxis, anim, frame, RecordMode );

		ModifyPoint( Center, anim, frame, RecordMode );
	}

	void Quad::ShowChildren()
	{
		for ( std::vector<BaseQuad*>::const_iterator child = Children.begin(); child != Children.end(); ++child )
			( *child )->Show = true;
	}

	void Quad::HideChildren()
	{
		for ( std::vector<BaseQuad*>::const_iterator child = Children.begin(); child != Children.end(); ++child )
			( *child )->Show = false;
	}

	void Quad::Transfer( int anim, float DestT, int AnimLength, bool Loop, bool Linear, float t )
	{
		Center->RelPos = Center->AnimData.Transfer( anim, DestT, AnimLength, Loop, Linear, t );
		xAxis->RelPos = xAxis->AnimData.Transfer( anim, DestT, AnimLength, Loop, Linear, t );
		yAxis->RelPos = yAxis->AnimData.Transfer( anim, DestT, AnimLength, Loop, Linear, t );
		for ( int i = 0; i < 4; i++ )
			Corner[ i ]->RelPos = Corner[ i ]->AnimData->Transfer( anim, DestT, AnimLength, Loop, Linear, t );
	}

	void Quad::Calc( int anim, float t, int AnimLength, bool Loop, bool Linear )
	{
		if ( !Show && Children.empty() )
			return;

		if ( getTextureIsAnimated() && UpdateSpriteAnim )
		{
			t = t + .5f;
			std::shared_ptr<CloudberryKingdom::EzTexture> data = TextureAnim->Calc( anim, t, AnimLength, Loop );
			MyTexture = data;

			Vertices[ 0 ].uv = Vector2( 0, 0 );
			Vertices[ 1 ].uv = Vector2( 1, 0 );
			Vertices[ 2 ].uv = Vector2( 0, 1 );
			Vertices[ 3 ].uv = Vector2( 1, 1 );

			int frame = static_cast<int>( floor( t ) );
			Center->RelPos = Center->AnimData.Get( anim, frame );
			xAxis->RelPos = xAxis->AnimData.Get( anim, frame );
			yAxis->RelPos = yAxis->AnimData.Get( anim, frame );
			for ( int i = 0; i < 4; i++ )
				Corner[ i ]->RelPos = Corner[ i ]->AnimData->Get( anim, frame );
		}
		else
		{
			Center->RelPos = Center->AnimData.Calc( anim, t, AnimLength, Loop, Linear );
			xAxis->RelPos = xAxis->AnimData.CalcAxis( anim, t, AnimLength, Loop, Linear );
			yAxis->RelPos = yAxis->AnimData.CalcAxis( anim, t, AnimLength, Loop, Linear );
			for ( int i = 0; i < 4; i++ )
				Corner[ i ]->RelPos = Corner[ i ]->AnimData->Calc( anim, t, AnimLength, Loop, Linear );
		}
	}

	void Quad::Write( const std::shared_ptr<BinaryWriter> &writer )
	{
		BaseQuad::Write( writer );

		if ( ParentQuad == 0 || ParentQuad == ParentObject->ParentQuad )
			writer->Write( -1 );
		else
			writer->Write( ParentObject->QuadList.find( ParentQuad ) );

		Center->Write( writer, ParentObject );
		xAxis->Write( writer, ParentObject );
		yAxis->Write( writer, ParentObject );

		for ( int i = 0; i < NumVertices; i++ )
			Corner[ i ]->Write( writer, ParentObject );

		for ( int i = 0; i < NumVertices; i++ )
			WriteReadTools::WriteVertex( writer, Vertices[ i ] );

		WriteReadTools::WriteColor( writer, MyColor );

		if ( MyTexture->Path == _T( "" ) )
			writer->Write( _T( "White" ) );
		else
			writer->Write( MyTexture->Path );
		writer->Write( MyEffect->Name );
	}

	void Quad::Read( const std::shared_ptr<BinaryReader> &reader, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<EzTextureWad> &TextureWad, int VersionNumber )
	{
		BaseQuad::Read( reader, EffectWad, TextureWad, VersionNumber );

		int ParentQuadInt = reader->ReadInt32();
		if ( ParentQuadInt == -1 )
			ParentQuad = ParentObject->ParentQuad;
		else
			( static_cast<Quad*>( ParentObject->QuadList[ ParentQuadInt ] ) )->AddQuadChild( this );

		Center->Read( reader, ParentObject );
		xAxis->Read( reader, ParentObject );
		yAxis->Read( reader, ParentObject );

		for ( int i = 0; i < 4; i++ )
			Corner[ i ]->Read( reader, ParentObject );

		for ( int i = 0; i < NumVertices; i++ )
			WriteReadTools::ReadVertex( reader, Vertices[ i ] );

		WriteReadTools::ReadColor( reader, MyColor );

		std::wstring name = reader->ReadString();
		MyTexture = TextureWad->FindByPathOrName( name );
		if ( MyTexture == TextureWad->DefaultTexture )
			MyTexture = TextureWad->FindByPathOrName( Name );

		MyEffect = EffectWad->FindByName( reader->ReadString() );
	}

#if defined(EDITOR)
	void Quad::SaveState( int StateIndex )
	{
		BaseQuad::SaveState( StateIndex );

		for ( int i = 0; i < 4; i++ )
			Corner[ i ]->SaveState( StateIndex );

		Center->SaveState( StateIndex );
		xAxis->SaveState( StateIndex );
		yAxis->SaveState( StateIndex );
	}
#endif

#if defined(EDITOR)
	void Quad::RecoverState( int StateIndex )
	{
		BaseQuad::RecoverState( StateIndex );

		for ( int i = 0; i < 4; i++ )
			Corner[ i ]->RecoverState( StateIndex );

		Center->RecoverState( StateIndex );
		xAxis->RecoverState( StateIndex );
		yAxis->RecoverState( StateIndex );
	}
#endif

	std::vector<BaseQuad*> Quad::GetAllChildren()
	{
		std::vector<BaseQuad*> list = std::vector<BaseQuad*>();

		for ( std::vector<BaseQuad*>::const_iterator quad = Children.begin(); quad != Children.end(); ++quad )
		{
			list.push_back( *quad );
			if ( dynamic_cast<Quad*>( *quad ) != 0 )
				list.AddRange( ( static_cast<Quad*>( *quad ) )->GetAllChildren() );
		}

		return list;
	}

	bool Quad::HitTest( Vector2 x )
	{
		bool SameSign = true;
		float sign = 0;
		for ( int i = 0; i < 3; i++ )
		{
			Vector2 d = ( Vertices[ ( i + 1 ) % 3 ].xy - Vertices[ i ].xy );
			Vector2 n = Vector2( -d.Y, d.X );

			float hold = Vector2::Dot( n, x - Vertices[ i ].xy );
			if ( sign != 0 && Math::Sign( sign ) != Math::Sign( hold ) )
				SameSign = false;
			sign = hold;
		}

		if ( SameSign )
			return true;
		else
			SameSign = true;

		sign = 0;
		for ( int i = 0; i < 3; i++ )
		{
			Vector2 d = ( Vertices[ ( i + 1 ) % 3 + 1 ].xy - Vertices[ i + 1 ].xy );
			Vector2 n = Vector2( -d.Y, d.X );

			float hold = Vector2::Dot( n, x - Vertices[ i + 1 ].xy );
			if ( sign != 0 && Math::Sign( sign ) != Math::Sign( hold ) )
				SameSign = false;
			sign = hold;
		}

		return SameSign;
	}

#if defined(EDITOR)
	std::vector<ObjectVector*> Quad::GetObjectVectors()
	{
		std::vector<ObjectVector*> ObjectVectorList = std::vector<ObjectVector*>();

		for ( int i = 0; i < 4; i++ )
			ObjectVectorList.push_back( Corner[ i ] );

		ObjectVectorList.push_back( Center );
		ObjectVectorList.push_back( xAxis );
		ObjectVectorList.push_back( yAxis );

		ObjectVectorList.push_back( ParentPoint );
		ObjectVectorList.push_back( ChildPoint );
		ObjectVectorList.push_back( ReleasePoint );

		return ObjectVectorList;
	}
#endif

	void Quad::RemoveQuadChild( const std::shared_ptr<BaseQuad> &child )
	{
		RemoveQuadChild( child, true );
	}

	void Quad::RemoveQuadChild( const std::shared_ptr<BaseQuad> &child, bool AddToRoot )
	{
		if ( std::find( Children.begin(), Children.end(), child ) != Children.end() )
		{
			if ( dynamic_cast<Quad*>( child ) != 0 )
			{
				std::shared_ptr<Quad> child_quad = static_cast<Quad*>( child );
				child_quad->Center->ParentQuad.reset();
				child_quad->Center->RelPosFromPos();
				child_quad->xAxis->ParentQuad.reset();
				child_quad->xAxis->RelPosFromPos();
				child_quad->yAxis->ParentQuad.reset();
				child_quad->yAxis->RelPosFromPos();
			}

			if ( child->ParentQuad == ParentObject->ParentQuad )
				child->ParentQuad.reset();
			else
			{
				child->ParentQuad.reset();
				if ( AddToRoot )
					ParentObject->ParentQuad->AddQuadChild( child );
			}

			Children.Remove( child );
		}
	}

	void Quad::AddQuadChild( const std::shared_ptr<BaseQuad> &child, bool KeepNumericData )
	{
		if ( this == child )
			return;

		if ( child->ParentQuad != 0 )
			child->ParentQuad->RemoveQuadChild( child, false );

		if ( dynamic_cast<Quad*>( child ) != 0 )
		{
			std::shared_ptr<Quad> child_quad = static_cast<Quad*>( child );

			if ( std::find( child_quad->GetAllChildren().begin(), child_quad->GetAllChildren().end(), this ) != child_quad->GetAllChildren().end() )
				return;

			child_quad->Center->ParentQuad = this;
			if ( !KeepNumericData )
				child_quad->Center->RelPosFromPos();
			child_quad->xAxis->ParentQuad = this;
			if ( !KeepNumericData )
				child_quad->xAxis->RelPosFromPos();
			child_quad->yAxis->ParentQuad = this;
			if ( !KeepNumericData )
				child_quad->yAxis->RelPosFromPos();
		}

		child->ParentQuad = this;

		Children.push_back( child );
	}

	void Quad::AddQuadChild( const std::shared_ptr<BaseQuad> &child )
	{
		AddQuadChild( child, false );
	}

#if defined(EDITOR)
	void Quad::ClickOnParentButton()
	{
		SetToBeParent = !SetToBeParent;

		if ( SetToBeParent )
		{
			for ( std::vector<BaseQuad*>::const_iterator quad = ParentObject->QuadList.begin(); quad != ParentObject->QuadList.end(); ++quad )
			{
				if ( ( *quad )->SetToBeChild && quad != this )
					AddQuadChild( *quad );
				( *quad )->SetToBeChild = false;
				if ( dynamic_cast<Quad*>( *quad ) != 0 )
					( static_cast<Quad*>( *quad ) )->SetToBeParent = false;
			}
		}
	}
#endif

	void Quad::FinishLoading( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzTextureWad> &TexWad, const std::shared_ptr<EzEffectWad> &EffectWad )
	{
		FinishLoading( device, TexWad, EffectWad, true );
	}

	void Quad::FinishLoading( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzTextureWad> &TexWad, const std::shared_ptr<EzEffectWad> &EffectWad, bool UseNames )
	{
		Center->ModifiedEventCallback = std::make_shared<UpdateCenterLambda>( this );
		xAxis->ModifiedEventCallback = std::make_shared<UpdatexAxisLambda>( this );
		yAxis->ModifiedEventCallback = std::make_shared<UpdateyAxisLambda>( this );

	#if defined(EDITOR)
		ParentPoint->ClickEventCallback = ClickOnParentButton;
		ChildPoint->ClickEventCallback = ClickOnChildButton;
		ReleasePoint->ClickEventCallback = ClickOnReleaseButton;
	#endif

		if ( UseNames )
		{
			if ( MyTexture->Name != _T( "" ) )
				MyTexture = TexWad->FindByPathOrName( MyTexture->Path );
			MyEffect = EffectWad->FindByName( MyEffect->Name );
		}
	}

	void Quad::InitVertices()
	{
		Children = std::vector<BaseQuad*>();

		NumVertices = 4;

		Vertices = std::vector<MyOwnVertexFormat>( 4 );

		Vertices[ 0 ].uv = Vector2( 0, 0 );
		Vertices[ 1 ].uv = Vector2( 1, 0 );
		Vertices[ 2 ].uv = Vector2( 0, 1 );
		Vertices[ 3 ].uv = Vector2( 1, 1 );

		Center = std::make_shared<ObjectVector>();
		Center->ModifiedEventCallback = std::make_shared<UpdateCenterLambda>( this );
		xAxis = std::make_shared<ObjectVector>();
		yAxis = std::make_shared<ObjectVector>();
		xAxis->CenterPoint = Center;
		yAxis->CenterPoint = Center;
		xAxis->Move( Vector2( 1, 0 ) );
		yAxis->Move( Vector2( 0, 1 ) );
		xAxis->ModifiedEventCallback = std::make_shared<UpdatexAxisLambda>( this );
		yAxis->ModifiedEventCallback = std::make_shared<UpdateyAxisLambda>( this );

	#if defined(EDITOR)
		ParentPoint = std::make_shared<ObjectVector>();
		ChildPoint = std::make_shared<ObjectVector>();
		ReleasePoint = std::make_shared<ObjectVector>();
		ParentPoint->ParentQuad = this;
		ChildPoint->ParentQuad = this;
		ParentPoint->ClickEventCallback = ClickOnParentButton;
		ChildPoint->ClickEventCallback = ClickOnChildButton;
		ReleasePoint->ClickEventCallback = ClickOnReleaseButton;
		SetToBeParent = SetToBeChild = false;
	#endif

		Corner = std::vector<ObjectVector*>( 4 );
		for ( int i = 0; i < 4; i++ )
		{
			Corner[ i ] = std::make_shared<ObjectVector>();
			Corner[ i ]->ParentQuad = this;
		}

		Corner[ 0 ]->Move( Vector2( -1, 1 ) );
		Corner[ 1 ]->Move( Vector2( 1, 1 ) );
		Corner[ 2 ]->Move( Vector2( -1, -1 ) );
		Corner[ 3 ]->Move( Vector2( 1, -1 ) );
	}

	void Quad::ScaleCorners( Vector2 size )
	{
		Corner[ 0 ]->RelPos = Vector2( -size.X, size.Y );
		Corner[ 1 ]->RelPos = Vector2( size.X, size.Y );
		Corner[ 2 ]->RelPos = Vector2( -size.X, -size.Y );
		Corner[ 3 ]->RelPos = Vector2( size.X, -size.Y );
	}

	Quad::Quad( const std::shared_ptr<Quad> &quad, bool DeepClone )
	{
		BaseQuad::Clone( quad );

		if ( DeepClone && quad->TextureAnim != 0 )
			TextureAnim = std::make_shared<AnimationData_Texture>( quad->TextureAnim );
		else
			TextureAnim = quad->TextureAnim;

		InitVertices();

		quad->Center->Clone( Center, DeepClone );
		quad->xAxis->Clone( xAxis, DeepClone );
		quad->yAxis->Clone( yAxis, DeepClone );
		for ( int i = 0; i < 4; i++ )
			quad->Corner[ i ]->Clone( Corner[ i ], DeepClone );

		for ( int i = 0; i < NumVertices; i++ )
			Vertices[ i ] = quad->Vertices[ i ];
	}

	Quad::Quad()
	{
		Name = _T( "Quad" );

		InitVertices();

		SetColor( Color( 1, 1, 1 ) );
	}

	const Microsoft::Xna::Framework::Vector2 &Quad::getSize() const
	{
		return Vector2( xAxis->RelPos.Length(), yAxis->RelPos.Length() );
	}

	void Quad::setSize( const Vector2 &value )
	{
		xAxis->RelPos.Normalize();
		yAxis->RelPos.Normalize();
		Scale( value );
	}

	void Quad::Scale( Vector2 Stretch )
	{
		xAxis->RelPos *= Stretch.X;
		yAxis->RelPos *= Stretch.Y;
	}

	void Quad::PointxAxisTo( Vector2 dir )
	{
		dir.Normalize();

		float l = xAxis->RelPos.Length();
		xAxis->RelPos = dir * l;
		xAxis->PosFromRelPos();

		l = yAxis->RelPos.Length();
		yAxis->RelPos.X = -xAxis->RelPos.Y;
		yAxis->RelPos.Y = xAxis->RelPos.X;
		yAxis->RelPos.Normalize();
		yAxis->RelPos *= l;
		yAxis->PosFromRelPos();
	}

	Microsoft::Xna::Framework::Vector2 Quad::CalcBLBound()
	{
		Vector2 BL = Center->Pos;
		for ( int i = 0; i < NumVertices; i++ )
			BL = Vector2::Min( BL, Vertices[ i ].xy );

		return BL;
	}

	Microsoft::Xna::Framework::Vector2 Quad::CalcTRBound()
	{
		Vector2 TR = Center->Pos;
		for ( int i = 0; i < NumVertices; i++ )
			TR = Vector2::Max( TR, Vertices[ i ].xy );

		return TR;
	}

	void Quad::Update( float Expand )
	{
		if ( !Show && Children.empty() )
			return;

		Center->PosFromRelPos();
		xAxis->PosFromRelPos();
		yAxis->PosFromRelPos();

	#if defined(EDITOR)
		Vector2 BL = CalcBLBound();

		ParentPoint->Pos = BL + Vector2( -.08f, -.03f );
		ChildPoint->Pos = BL + Vector2( -.08f, -.065f );
		ReleasePoint->Pos = BL + Vector2( -.08f, -.1f );
		if ( SetToBeParent )
			ParentPoint->Pos += Vector2( .025f, 0 );
		if ( SetToBeChild )
			ChildPoint->Pos += Vector2( .025f, 0 );
		if ( ParentQuad != 0 && ParentQuad != ParentObject->ParentQuad )
			ReleasePoint->Pos += Vector2( .025f, 0 );
	#endif

		for ( int i = 0; i < 4; i++ )
		{
			Vector2 HoldRelPos = Corner[ i ]->RelPos;
			Corner[ i ]->RelPos *= Expand;
			Corner[ i ]->PosFromRelPos();
			Corner[ i ]->RelPos = HoldRelPos;

			Vertices[ i ].xy = Corner[ i ]->Pos;
		}
	}

	void Quad::Set_PosFromRelPos( const std::shared_ptr<ObjectVector> &v )
	{
		Vector2 C1 = Vector2::Zero;
		Vector2 C2 = Vector2::Zero;
		if ( v->CenterPoint != 0 )
			C1 = v->CenterPoint->Pos;

		C2 = Center->Pos;
		if ( v->CenterPoint == 0 )
			C1 = Center->Pos;

		v->Pos = C1 + v->RelPos.X * ( xAxis->Pos - C2 ) + v->RelPos.Y * ( yAxis->Pos - C2 );
	}

	void Quad::Set_RelPosFromPos( const std::shared_ptr<ObjectVector> &v )
	{
		Vector2 C = Vector2( 0, 0 );
		if ( v->CenterPoint != 0 )
			C = v->CenterPoint->Pos;

		if ( v->CenterPoint == 0 )
			C = Center->Pos;

		Vector2 Dif = v->Pos - C;
		Vector2 axis = xAxis->Pos - Center->Pos;
		v->RelPos.X = Vector2::Dot( Dif, axis ) / axis.LengthSquared();
		axis = yAxis->Pos - Center->Pos;
		v->RelPos.Y = Vector2::Dot( Dif, axis ) / axis.LengthSquared();
	}

	void Quad::Draw()
	{
		Draw( Tools::QDrawer );
	}

	void Quad::Draw( const std::shared_ptr<QuadDrawer> &Drawer )
	{
		if ( !Show )
			return;

		Drawer->DrawQuad( this );
	}

#if defined(EDITOR)
	void Quad::DrawChildren( const std::shared_ptr<QuadDrawer> &Drawer )
	{
		for ( std::vector<BaseQuad*>::const_iterator child_quad = GetAllChildren().begin(); child_quad != GetAllChildren().end(); ++child_quad )
		{
			( *child_quad )->ColoredDraw( Drawer, Color::PowderBlue );
		}
	}
#endif

#if defined(EDITOR)
	void Quad::DrawExtra( const std::shared_ptr<QuadDrawer> &Drawer, bool Additional, float ScaleLines )
	{
		if ( !Show )
			return;

		for ( std::vector<ObjectVector*>::const_iterator point = GetObjectVectors().begin(); point != GetObjectVectors().end(); ++point )
		{
			if ( dynamic_cast<BendableQuad*>( ( *point )->ParentQuad ) != 0 )
			{
				Vector2 SplineLoc = ( static_cast<BendableQuad*>( ( *point )->ParentQuad ) )->MySpline->GetVector( ( *point )->RelPos.X, 0 );
				Drawer->DrawSquareDot( SplineLoc, Color( .2f,.8f,.9f ),.03f * ScaleLines );
			}
		}

		if ( Additional )
			if ( ParentQuad != 0 )
			{
				Drawer->DrawLine( Corner[ 0 ]->Pos, ParentQuad->Corner[ 0 ]->Pos, Color( 192, 192, 192, 50 ),.05f * ScaleLines );
				Drawer->DrawLine( Corner[ 3 ]->Pos, ParentQuad->Corner[ 3 ]->Pos, Color( 192, 192, 192, 50 ),.05f * ScaleLines );
			}

		Drawer->DrawLine( Center->Pos, xAxis->Pos, Color( .2f,.6f,.2f ),.015f * ScaleLines );
		Drawer->DrawLine( Center->Pos, yAxis->Pos, Color( .2f,.6f,.2f ),.015f * ScaleLines );
		Drawer->DrawSquareDot( Center->Pos, Color( .4f,.8f,.4f ),.033f * ScaleLines );
		Drawer->DrawSquareDot( xAxis->Pos, Color( .8f,.4f,.4f ),.033f * ScaleLines );
		Drawer->DrawSquareDot( yAxis->Pos, Color( .4f,.4f,.8f ),.033f * ScaleLines );

		Vector2 BL = CalcBLBound();
		Vector2 TR = CalcTRBound();

		if ( Additional )
		{
			Drawer->DrawLine( BL + Vector2( -.08f, -.03f ) + Vector2( -.01f, 0 ), BL + Vector2( -.08f, -.03f ) + Vector2( .035f, 0 ), Color::SeaGreen,.015f * ScaleLines );
			Drawer->DrawSquareDot( ParentPoint->Pos, Color::Sienna,.03f * ScaleLines );
			Drawer->DrawLine( BL + Vector2( -.08f, -.065f ) + Vector2( -.01f, 0 ), BL + Vector2( -.08f, -.065f ) + Vector2( .035f, 0 ), Color::SeaGreen,.015f * ScaleLines );
			Drawer->DrawSquareDot( ChildPoint->Pos, Color::SeaShell,.03f * ScaleLines );
			Drawer->DrawLine( BL + Vector2( -.08f, -.1f ) + Vector2( -.01f, 0 ), BL + Vector2( -.08f, -.1f ) + Vector2( .035f, 0 ), Color::SeaGreen,.015f * ScaleLines );
			Drawer->DrawSquareDot( ReleasePoint->Pos, Color::SeaShell,.03f * ScaleLines );
		}

		for ( int i = 0; i < 4; i++ )
			Drawer->DrawSquareDot( Corner[ i ]->Pos, Color( .8f,.4f,.4f ),.035f * ScaleLines );

		if ( Additional )
		{
			float H = TR.Y - BL.Y;
			float W = TR.X - BL.X;

			Drawer->DrawLine( BL, BL + Vector2( W / 2, 0 ), Color::PapayaWhip,.006f * ScaleLines );
			Drawer->DrawLine( BL, BL + Vector2( 0, H / 2 ), Color::PapayaWhip,.006f * ScaleLines );
			Drawer->DrawLine( TR, TR + Vector2( -W / 2, 0 ), Color::PapayaWhip,.006f * ScaleLines );
			Drawer->DrawLine( TR, TR + Vector2( 0, -H / 2 ), Color::PapayaWhip,.006f * ScaleLines );
		}
	}
#endif
}
