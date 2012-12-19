#include <global_header.h>

#include "Hacks/Queue.h"
#include "Hacks/List.h"
#include "Hacks/String.h"

namespace CloudberryKingdom
{

	void DrawPile::InitializeStatics()
	{
		Vector2 tempVector2[] = { Vector2( 0.001f ), Vector2( 1.15f ), Vector2( .94f ), Vector2( 1.05f ), Vector2( 1 ) };
		DrawPile::BubbleScale = VecFromArray( tempVector2 );

		Vector2 tempVector3[] = { Vector2( 1.15f ), Vector2( .94f ), Vector2( 1.05f ), Vector2( 1 ) };
		DrawPile::JiggleScale = VecFromArray( tempVector3 );
	}

	// Statics
	std::vector<Vector2> DrawPile::BubbleScale;
	std::vector<Vector2> DrawPile::JiggleScale;


	DrawPile::WaitThenPop::WaitThenPop( const boost::shared_ptr<DrawPile> &MyDrawPile )
	{
		MyDrawPile_ = MyDrawPile;
	}

	void DrawPile::WaitThenPop::Apply()
	{
		Tools::Pop( MyDrawPile_->MyPopPitch );
	}

	void DrawPile::WaitThenPop2::Apply()
	{
		Tools::SoundWad->FindByName( std::wstring( L"Pop_2" ) )->Play();
	}

	const Vector2 &DrawPile::getSize() const
	{
		return FancyScale->RelVal;
	}

	void DrawPile::setSize( const Vector2 &value )
	{
		FancyScale->RelVal = value;
	}

	const Vector2 &DrawPile::getPos() const
	{
		return FancyPos->RelVal;
	}

	void DrawPile::setPos( const Vector2 &value )
	{
		FancyPos->RelVal = value;
	}

	DrawPile::DrawPile()
	{
		InitializeInstanceFields();
		FancyPos = boost::make_shared<FancyVector2>();

		FancyScale = boost::make_shared<FancyVector2>();
		setSize( Vector2( 1, 1 ) );
	}

	DrawPile::DrawPile( const boost::shared_ptr<FancyVector2> &Center )
	{
		InitializeInstanceFields();
		FancyPos = boost::make_shared<FancyVector2>( Center );

		FancyScale = boost::make_shared<FancyVector2>();
		setSize( Vector2( 1, 1 ) );
	}

	void DrawPile::Clear()
	{
		MyTextList.clear();
		MyQuadList.clear();
	}

	void DrawPile::Add( const boost::shared_ptr<QuadClass> &quad )
	{
		Add( quad, false, std::wstring( L"" ) );
	}

	void DrawPile::Add( const boost::shared_ptr<QuadClass> &quad, const std::wstring &name )
	{
		Add( quad, false, name );
	}

	void DrawPile::Add( const boost::shared_ptr<QuadClass> &quad, bool KeepFancyCenter, const std::wstring &name )
	{
		if ( name != std::wstring( L"" ) )
			quad->Name = name;

		if ( KeepFancyCenter && quad->FancyPos != 0 && quad->FancyPos->Center != 0
			&& boost::dynamic_pointer_cast<FancyVector2>( quad->FancyPos->Center ) != 0 )
			( boost::static_pointer_cast<FancyVector2>( quad->FancyPos->Center ) )->SetCenter( FancyPos, true );
		else
		{
			quad->MakeFancyPos();
			quad->FancyPos->SetCenter( FancyPos, true );
		}

		MyQuadList.push_back( quad );
	}

	void DrawPile::Insert( int index, const boost::shared_ptr<QuadClass> &quad )
	{
		quad->MakeFancyPos();
		quad->FancyPos->SetCenter( FancyPos, true );
		MyQuadList.insert( MyQuadList.begin() + index, quad );
	}

	void DrawPile::Add( const boost::shared_ptr<EzText> &text )
	{
		text->MakeFancyPos();
		text->FancyPos->SetCenter( FancyPos, true );
		MyTextList.push_back( text );
	}

	void DrawPile::Add( const boost::shared_ptr<EzText> &text, const std::wstring &name )
	{
		text->Name = name;
		text->MakeFancyPos();
		text->FancyPos->SetCenter( FancyPos, true );
		MyTextList.push_back( text );
	}

	void DrawPile::Remove( const boost::shared_ptr<EzText> &text )
	{
		//MyTextList.Remove( text );
		::Remove( MyTextList, text );
	}

	boost::shared_ptr<QuadClass> DrawPile::FindQuad( const std::wstring &Name )
	{
		return QuadClass::FindQuad( MyQuadList, Name );
	}

	boost::shared_ptr<EzText> DrawPile::FindEzText( const std::wstring &Name )
	{
		for ( std::vector<boost::shared_ptr<EzText> >::const_iterator text = MyTextList.begin(); text != MyTextList.end(); ++text )
			if ( CompareIgnoreCase( ( *text )->Name, Name ) == 0 )
				return *text;

		return 0;
	}

	float DrawPile::getAlpha()
	{
		return MyFancyColor->getA();
	}

	void DrawPile::setAlpha( const float &value )
	{
		MyFancyColor->setColor( Color( 1.f, 1.f, 1.f, value ) );
	}

	void DrawPile::Scale( float scale )
	{
		for ( std::vector<boost::shared_ptr<QuadClass> >::const_iterator quad = MyQuadList.begin(); quad != MyQuadList.end(); ++quad )
		{
			( *quad )->setPos( ( *quad )->getPos() * scale );
			//quad.ShadowOffset *= scale;
			( *quad )->ShadowScale = 1 / scale;
			( *quad )->Scale( scale );

			( *quad )->ShadowOffset *= 18 * ( scale - 1 ) + 1;

			Vector2 PosShift = .5f * ( scale - 1 ) * ( *quad )->getSize();
			Vector2 Hold = ( *quad )->ShadowOffset;
			( *quad )->ShadowOffset += 1 * PosShift * Vector2( 1, 1.5f );
			( *quad )->ShadowOffset.X = .5f * ( ( *quad )->ShadowOffset.X + Hold.X - PosShift.X );
		}

		for ( std::vector<boost::shared_ptr<EzText> >::const_iterator text = MyTextList.begin(); text != MyTextList.end(); ++text )
		{
			( *text )->setPos( ( *text )->getPos() * scale );
			( *text )->setScale( ( *text )->getScale() * scale );
		}
	}

	void DrawPile::SaveScale()
	{
		SavedScales = std::vector<Vector2>();

		for ( std::vector<boost::shared_ptr<QuadClass> >::const_iterator quad = MyQuadList.begin(); quad != MyQuadList.end(); ++quad )
			SavedScales.push_back( ( *quad )->getSize() );

		SavedPositions = std::vector<Vector2>();

		for ( std::vector<boost::shared_ptr<QuadClass> >::const_iterator quad = MyQuadList.begin(); quad != MyQuadList.end(); ++quad )
			SavedPositions.push_back( ( *quad )->getPos() );

		SavedShadowOffsets = std::vector<Vector2>();

		for ( std::vector<boost::shared_ptr<QuadClass> >::const_iterator quad = MyQuadList.begin(); quad != MyQuadList.end(); ++quad )
			SavedShadowOffsets.push_back( ( *quad )->ShadowOffset );
	}

	void DrawPile::RevertScale()
	{
		for ( std::vector<boost::shared_ptr<QuadClass> >::const_iterator quad = MyQuadList.begin(); quad != MyQuadList.end(); ++quad )
		{
			( *quad )->setSize( SavedScales[ IndexOf( MyQuadList, *quad ) ] );

			( *quad )->setPos( SavedPositions[ IndexOf( MyQuadList, *quad ) ] );

			( *quad )->ShadowOffset = SavedShadowOffsets[ IndexOf( MyQuadList, *quad ) ];
			( *quad )->ShadowScale = 1;
		}
	}

	void DrawPile::Update()
	{
		setAlpha( getAlpha() + AlphaVel );
	}

	void DrawPile::Draw()
	{
		Draw( 0 );
	}

	void DrawPile::Draw( int Layer )
	{
		if ( Fading )
			Fade();

		if ( FancyScale != 0 )
			FancyScale->Update();
		if ( MyFancyColor != 0 )
			MyFancyColor->Update();

		if ( getAlpha() <= 0 )
			return;

		DrawNonText( Layer );

		DrawText( Layer );
		Tools::Render->EndSpriteBatch();
	}

	void DrawPile::DrawNonText( int Layer )
	{
		FancyPos->Update();

		for ( std::vector<boost::shared_ptr<QuadClass> >::const_iterator quad = MyQuadList.begin(); quad != MyQuadList.end(); ++quad )
		{
			if ( ( *quad )->Layer == Layer )
			{
				( *quad )->ParentScaling = getSize();
				( *quad )->ParentAlpha = getAlpha();
				( *quad )->Draw();
			}
		}

		Tools::QDrawer->Flush();
	}

	void DrawPile::DrawText( int Layer )
	{
		for ( std::vector<boost::shared_ptr<EzText> >::const_iterator text = MyTextList.begin(); text != MyTextList.end(); ++text )
		{
			if ( ( *text )->Layer == Layer )
			{
				( *text )->ParentScaling = getSize();
				( *text )->ParentAlpha = getAlpha();
				( *text )->Draw( Tools::getCurCamera(), false );
			}
		}
	}

	void DrawPile::Draw( bool Selected )
	{
		if ( Selected )
		{
			SaveScale();
			Scale( MyOscillateParams.GetScale() );
			Draw();
			RevertScale();
		}
		else
		{
			MyOscillateParams.Reset();
			Draw();
		}
	}

	void DrawPile::FadeIn( float speed )
	{
		setAlpha( 0 );
		Fading = true;
		FadeSpeed = speed;
	}

	void DrawPile::FadeOut( float speed )
	{
		setAlpha( 1 );
		Fading = true;
		FadeSpeed = -speed;
	}

	void DrawPile::Fade()
	{
		setAlpha( getAlpha() + FadeSpeed );
	}

	void DrawPile::BubbleDownAndFade( bool sound )
	{
		BubbleDown( sound, 5 );
		FadeOut( 1 / 20 );
	}

	void DrawPile::BubbleUp( bool sound )
	{
		BubbleUp( sound, 5, 1 );
	}

	void DrawPile::BubbleUp( bool sound, int Length, float Intensity )
	{
		std::vector<Vector2> scales;
		if ( Intensity == 1 )
			scales = BubbleScale;
		else
		{
			scales = std::vector<Vector2>( BubbleScale.size() );
			for ( size_t i = 0; i < BubbleScale.size(); i++ )
				scales[ i ] = ( BubbleScale[ i ] - Vector2(1) ) * Intensity + Vector2(1);
		}

		FancyScale->MultiLerp( Length, scales );
		MyFancyColor->LerpTo( Vector4( 1, 1, 1, 1 ), Length );
		if ( sound )
			Tools::CurGameData->WaitThenDo( 2, boost::make_shared<WaitThenPop>( this->shared_from_this() ) );
	}

	void DrawPile::BubbleDown( bool sound )
	{
		BubbleDown( sound, 5 );
	}

	void DrawPile::BubbleDown( bool sound, int Length )
	{
		FancyScale->LerpTo( Vector2( .1f ), Length + 1 );
		MyFancyColor->LerpTo( Vector4( 1, 1, 1, 0 ), Length );
		if ( sound )
			Tools::SoundWad->FindByName( std::wstring( L"Pop_2" ) )->Play();
	}

	void DrawPile::Jiggle( bool sound )
	{
		Jiggle( sound, 5, 1 );
	}

	void DrawPile::Jiggle( bool sound, int Length, float Intensity )
	{
		std::vector<Vector2> mapped = std::vector<Vector2>( JiggleScale.size() );
		for ( size_t i = 0; i < JiggleScale.size(); i++ )
			mapped[ i ] = ( JiggleScale[ i ] - Vector2(1) ) * Intensity + Vector2(1);

		FancyScale->MultiLerp( Length, mapped );

		MyFancyColor->LerpTo( Vector4( 1, 1, 1, 1 ), Length );
		if ( sound )
			Tools::CurGameData->WaitThenDo( 2, boost::make_shared<WaitThenPop2>() );
	}

	void DrawPile::InitializeInstanceFields()
	{
		MyTextList = std::vector<boost::shared_ptr<EzText> >();
		MyQuadList = std::vector<boost::shared_ptr<QuadClass> >();
		AlphaVel = 0;
		MyFancyColor = boost::make_shared<FancyColor>();
		Fading = false;
		FadeSpeed = 0;
		MyPopPitch = 2;
	}
}
