#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{

	BackgroundCollection::BackgroundCollection( const std::shared_ptr<Level> &level )
	{
		MyLevel = level;

		Lists = std::vector<BackgroundFloaterList*>();
	}

	void BackgroundCollection::Release()
	{
		MyLevel.reset();

		for ( std::vector<BackgroundFloaterList*>::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->Release();
	}

	void BackgroundCollection::Reset()
	{
		if ( Lists.empty() )
			return;

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<BackgroundFloaterList*>::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->Reset();
	}

	void BackgroundCollection::SetLevel( const std::shared_ptr<Level> &level )
	{
		MyLevel = level;

		for ( std::vector<BackgroundFloaterList*>::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->SetLevel( level );
	}

	void BackgroundCollection::SetBackground( const std::shared_ptr<Background> &b )
	{
		for ( std::vector<BackgroundFloaterList*>::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->SetBackground( b );
	}

	void BackgroundCollection::Move( Vector2 shift )
	{
		for ( std::vector<BackgroundFloaterList*>::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->Move( shift );
	}

	void BackgroundCollection::Clear()
	{
		Clear( std::make_shared<FloatRectangle>( Vector2::Zero, Vector2( 100000000 ) ) );
	}

	void BackgroundCollection::Clear( const std::shared_ptr<FloatRectangle> &Area )
	{
		for ( int i = 0; i < Lists.size(); i++ )
			Lists[ i ]->Clear( Area );
	}

	void BackgroundCollection::Absorb( const std::shared_ptr<BackgroundCollection> &collection )
	{
		for ( int i = 0; i < Lists.size(); i++ )
			Lists[ i ]->Absorb( collection->Lists[ i ] );
	}

	void BackgroundCollection::DrawLayer( int Layer )
	{
		if ( Layer < Lists.size() )
			Lists[ Layer ]->Draw();
	}

	void BackgroundCollection::FinishDraw()
	{
		Tools::QDrawer->Flush();

		std::shared_ptr<Camera> Cam = MyLevel->getMainCamera();
		Cam->SetVertexCamera();
		//Vector4 cameraPos = new Vector4(Cam.Data.Position.X, Cam.Data.Position.Y, Cam.Zoom.X, Cam.Zoom.Y);
		//Tools.EffectWad.SetCameraPosition(cameraPos);
	}

	void BackgroundCollection::Draw()
	{
		Draw( 1, false );
	}

	void BackgroundCollection::Draw( float CamMod, bool Foreground )
	{
		for ( std::vector<BackgroundFloaterList*>::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			if ( ( *list )->Foreground == Foreground )
				( *list )->Draw( CamMod );

		FinishDraw();
	}

	void BackgroundCollection::PhsxStep()
	{
		for ( std::vector<BackgroundFloaterList*>::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->PhsxStep();
	}

	std::vector<std::wstring> BackgroundCollection::GetViewables()
	{
		const std::wstring* tempVector[] = { _T( "Lists" ) };
		return std::vector<std::wstring*>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) );
	}
}
