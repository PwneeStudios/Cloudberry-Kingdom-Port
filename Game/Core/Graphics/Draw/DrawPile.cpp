#include "DrawPile.h"
#include "Game/Tools/Tools.h"
#include "Core/Text/EzText.h"
#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Core/FancyVector2.h"
#include "Core/FancyColor.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{

	DrawPile::WaitThenPop::WaitThenPop( const std::shared_ptr<DrawPile> &MyDrawPile )
	{
		MyDrawPile_ = MyDrawPile;
	}

	void DrawPile::WaitThenPop::Apply()
	{
		Tools::Pop( MyDrawPile_->MyPopPitch );
	}

	void DrawPile::WaitThenPop2::Apply()
	{
		Tools::SoundWad->FindByName( _T( "Pop_2" ) )->Play();
	}

	std::vector<std::wstring> DrawPile::GetViewables()
	{
		const std::wstring* tempVector[] = { _T( "MyQuadList" ), _T( "MyTextList" ) };
		return std::vector<std::wstring*>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
	}

	std::wstring DrawPile::CopyToClipboard( const std::wstring &suffix )
	{
		if ( suffix == _T( "" ) || suffix == _T( "" ) )
			suffix = _T( "MyPile." );

		std::wstring s = _T( "" );

		if ( MyTextList.size() > 0 )
		{
			if ( MyTextList.size() > 0 )
				s += _T( "EzText _t;\n" );
			for ( std::vector<EzText*>::const_iterator text = MyTextList.begin(); text != MyTextList.end(); ++text )
				s += std::wstring::Format( _T( "_t = {0}FindEzText(\"{1}\"); if (_t != null) {{ _t.Pos = {2}; _t.Scale = {3}f; }}\n" ), suffix, ( *text )->Name, Tools::ToCode( ( *text )->getPos() ), (*text)->getScale() );
		}

		if ( MyQuadList.size() > 0 && MyQuadList.size() > 0 )
		{
			if ( MyTextList.size() > 0 )
				s += _T( "\n" );

			if ( MyQuadList.size() > 0 )
				s += _T( "QuadClass _q;\n" );
			for ( std::vector<QuadClass*>::const_iterator quad = MyQuadList.begin(); quad != MyQuadList.end(); ++quad )
			{
				s += std::wstring::Format( _T( "_q = {0}FindQuad(\"{1}\"); if (_q != null) {{ _q.Pos = {2}; _q.Size = {3}; }}\n" ), suffix, ( *quad )->Name, Tools::ToCode( ( *quad )->getPos() ), Tools::ToCode((*quad)->getSize()) );
			}

			s += _T( "\n" );
		}

		s += std::wstring::Format( _T( "{0}Pos = {1};\n" ), suffix, Tools::ToCode( getPos() ) );

		return s;
	}

	void DrawPile::ProcessMouseInput( Vector2 shift, bool ShiftDown )
	{
		if ( ShiftDown )
			Scale( ( shift.X + shift.Y ) *.00003f );
		else
			setPos( getPos() + shift );
	}

	void DrawPile::GetChildren( std::vector<InstancePlusName*> &ViewableChildren )
	{
		if ( MyQuadList.size() > 0 )
			for ( std::vector<QuadClass*>::const_iterator quad = MyQuadList.begin(); quad != MyQuadList.end(); ++quad )
			{
				std::wstring name = ( *quad )->Name;
				if ( name.length() == 0 )
					name = ( *quad )->getTextureName();
				ViewableChildren.push_back( std::make_shared<InstancePlusName>( *quad, name ) );
			}

		if ( MyTextList.size() > 0 )
			for ( std::vector<EzText*>::const_iterator text = MyTextList.begin(); text != MyTextList.end(); ++text )
			{
				std::wstring name = ( *text )->MyString;
				ViewableChildren.push_back( std::make_shared<InstancePlusName>( *text, name ) );
			}
	}

	const Microsoft::Xna::Framework::Vector2 &DrawPile::getSize() const
	{
		return FancyScale->RelVal;
	}

	void DrawPile::setSize( const Vector2 &value )
	{
		FancyScale->RelVal = value;
	}

	const Microsoft::Xna::Framework::Vector2 &DrawPile::getPos() const
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
		FancyPos = std::make_shared<FancyVector2>();

		FancyScale = std::make_shared<FancyVector2>();
		setSize( Vector2( 1, 1 ) );
	}

	DrawPile::DrawPile( const std::shared_ptr<FancyVector2> &Center )
	{
		InitializeInstanceFields();
		FancyPos = std::make_shared<FancyVector2>( Center );

		FancyScale = std::make_shared<FancyVector2>();
		setSize( Vector2( 1, 1 ) );
	}

	void DrawPile::Clear()
	{
		MyTextList.clear();
		MyQuadList.clear();
	}

	void DrawPile::Add( const std::shared_ptr<QuadClass> &quad )
	{
		Add( quad, false, 0 );
	}

	void DrawPile::Add( const std::shared_ptr<QuadClass> &quad, const std::wstring &name )
	{
		Add( quad, false, name );
	}

	void DrawPile::Add( const std::shared_ptr<QuadClass> &quad, bool KeepFancyCenter )
	{
		Add( quad, KeepFancyCenter, 0 );
	}

	void DrawPile::Add( const std::shared_ptr<QuadClass> &quad, bool KeepFancyCenter, const std::wstring &name )
	{
		if ( name != _T( "" ) )
			quad->Name = name;

		if ( KeepFancyCenter && quad->FancyPos != 0 && quad->FancyPos->Center != 0 && dynamic_cast<FancyVector2*>( quad->FancyPos->Center ) != 0 )
			( static_cast<FancyVector2*>( quad->FancyPos->Center ) )->SetCenter( FancyPos, true );
		else
		{
			quad->MakeFancyPos();
			quad->FancyPos->SetCenter( FancyPos, true );
		}

		MyQuadList.push_back( quad );
	}

	void DrawPile::Insert( int index, const std::shared_ptr<QuadClass> &quad )
	{
		quad->MakeFancyPos();
		quad->FancyPos->SetCenter( FancyPos, true );
		MyQuadList.Insert( index, quad );
	}

	void DrawPile::Add( const std::shared_ptr<EzText> &text )
	{
		text->MakeFancyPos();
		text->FancyPos->SetCenter( FancyPos, true );
		MyTextList.push_back( text );
	}

	void DrawPile::Add( const std::shared_ptr<EzText> &text, const std::wstring &name )
	{
		text->Name = name;
		text->MakeFancyPos();
		text->FancyPos->SetCenter( FancyPos, true );
		MyTextList.push_back( text );
	}

	void DrawPile::Remove( const std::shared_ptr<EzText> &text )
	{
		MyTextList.Remove( text );
	}

	std::shared_ptr<QuadClass> DrawPile::FindQuad( const std::wstring &Name )
	{
		return QuadClass::FindQuad( MyQuadList, Name );
	}

	std::shared_ptr<EzText> DrawPile::FindEzText( const std::wstring &Name )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<EzText*>::const_iterator text = MyTextList.begin(); text != MyTextList.end(); ++text )
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Compare' reference is not converted:
			if ( std::wstring::Compare( ( *text )->Name, Name, System::StringComparison::InvariantCultureIgnoreCase ) == 0 )
				return text;

		return 0;
	}

	const float &DrawPile::getAlpha() const
	{
		return MyFancyColor->getA();
	}

	void DrawPile::setAlpha( const float &value )
	{
		MyFancyColor->setColor( Color( 255, 255, 255, value ) );
	}

	void DrawPile::Scale( float scale )
	{
		for ( std::vector<QuadClass*>::const_iterator quad = MyQuadList.begin(); quad != MyQuadList.end(); ++quad )
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

		for ( std::vector<EzText*>::const_iterator text = MyTextList.begin(); text != MyTextList.end(); ++text )
		{
			( *text )->setPos( ( *text )->getPos() * scale );
			( *text )->setScale( ( *text )->getScale() * scale );
		}
	}

	void DrawPile::SaveScale()
	{
		SavedScales = std::vector<Vector2>();

		for ( std::vector<QuadClass*>::const_iterator quad = MyQuadList.begin(); quad != MyQuadList.end(); ++quad )
			SavedScales.push_back( ( *quad )->getSize() );

		SavedPositions = std::vector<Vector2>();

		for ( std::vector<QuadClass*>::const_iterator quad = MyQuadList.begin(); quad != MyQuadList.end(); ++quad )
			SavedPositions.push_back( ( *quad )->getPos() );

		SavedShadowOffsets = std::vector<Vector2>();

		for ( std::vector<QuadClass*>::const_iterator quad = MyQuadList.begin(); quad != MyQuadList.end(); ++quad )
			SavedShadowOffsets.push_back( ( *quad )->ShadowOffset );
	}

	void DrawPile::RevertScale()
	{
		for ( std::vector<QuadClass*>::const_iterator quad = MyQuadList.begin(); quad != MyQuadList.end(); ++quad )
		{
			( *quad )->setSize( SavedScales[ MyQuadList.find( *quad ) ] );

			( *quad )->setPos( SavedPositions[ MyQuadList.find( *quad ) ] );

			( *quad )->ShadowOffset = SavedShadowOffsets[ MyQuadList.find( *quad ) ];
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

		for ( std::vector<QuadClass*>::const_iterator quad = MyQuadList.begin(); quad != MyQuadList.end(); ++quad )
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
		for ( std::vector<EzText*>::const_iterator text = MyTextList.begin(); text != MyTextList.end(); ++text )
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

const Vector2 tempVector2[] = { Vector2( 0.001f ), Vector2( 1.15f ), Vector2( .94f ), Vector2( 1.05f ), Vector2( 1 ) };
std::vector<Vector2> DrawPile::BubbleScale = std::vector<Vector2>( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) );

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
			for ( int i = 0; i < BubbleScale.size(); i++ )
				scales[ i ] = ( BubbleScale[ i ] - Vector2::One ) * Intensity + Vector2::One;
		}

		FancyScale->MultiLerp( Length, scales );
		MyFancyColor->LerpTo( Vector4( 1, 1, 1, 1 ), Length );
		if ( sound )
			Tools::CurGameData->WaitThenDo( 2, std::make_shared<WaitThenPop>( this ) );
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
			Tools::SoundWad->FindByName( _T( "Pop_2" ) )->Play();
	}

const Vector2 tempVector3[] = { Vector2( 1.15f ), Vector2( .94f ), Vector2( 1.05f ), Vector2( 1 ) };
std::vector<Vector2> DrawPile::JiggleScale = std::vector<Vector2>( tempVector3, tempVector3 + sizeof( tempVector3 ) / sizeof( tempVector3[ 0 ] ) );

	void DrawPile::Jiggle( bool sound )
	{
		Jiggle( sound, 5, 1 );
	}

	void DrawPile::Jiggle( bool sound, int Length, float Intensity )
	{
		std::vector<Vector2> mapped = std::vector<Vector2>( JiggleScale.size() );
		for ( int i = 0; i < JiggleScale.size(); i++ )
			mapped[ i ] = ( JiggleScale[ i ] - Vector2::One ) * Intensity + Vector2::One;

		FancyScale->MultiLerp( Length, mapped );

		MyFancyColor->LerpTo( Vector4( 1, 1, 1, 1 ), Length );
		if ( sound )
			Tools::CurGameData->WaitThenDo( 2, std::make_shared<WaitThenPop2>() );
	}

	void DrawPile::InitializeInstanceFields()
	{
		MyTextList = std::vector<EzText*>();
		MyQuadList = std::vector<QuadClass*>();
		AlphaVel = 0;
		MyFancyColor = std::make_shared<FancyColor>();
		Fading = false;
		FadeSpeed = 0;
		MyPopPitch = 2;
	}
}
