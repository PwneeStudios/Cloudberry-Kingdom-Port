#include <global_header.h>

namespace CloudberryKingdom
{

	BackgroundCollection::BackgroundCollection( const std::shared_ptr<Level> &level )
	{
		MyLevel = level;

		//Lists = std::vector<std::shared_ptr<BackgroundFloaterList> >();
	}

	void BackgroundCollection::Release()
	{
		MyLevel.reset();

		for ( std::vector<std::shared_ptr<BackgroundFloaterList> >::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->Release();
	}

	void BackgroundCollection::Reset()
	{
		if ( Lists.empty() )
			return;

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<std::shared_ptr<BackgroundFloaterList> >::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->Reset();
	}

	void BackgroundCollection::SetLevel( const std::shared_ptr<Level> &level )
	{
		MyLevel = level;

		for ( std::vector<std::shared_ptr<BackgroundFloaterList> >::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->SetLevel( level );
	}

	void BackgroundCollection::SetBackground( const std::shared_ptr<Background> &b )
	{
		for ( std::vector<std::shared_ptr<BackgroundFloaterList> >::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->SetBackground( b );
	}

	void BackgroundCollection::Move( Vector2 shift )
	{
		for ( std::vector<std::shared_ptr<BackgroundFloaterList> >::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->Move( shift );
	}

	void BackgroundCollection::Clear()
	{
		Clear( std::make_shared<FloatRectangle>( Vector2(), Vector2( 100000000 ) ) );
	}

	void BackgroundCollection::Clear( const std::shared_ptr<FloatRectangle> &Area )
	{
		for ( size_t i = 0; i < Lists.size(); i++ )
			Lists[ i ]->Clear( Area );
	}

	void BackgroundCollection::Absorb( const std::shared_ptr<BackgroundCollection> &collection )
	{
		for ( size_t i = 0; i < Lists.size(); i++ )
			Lists[ i ]->Absorb( collection->Lists[ i ] );
	}

	void BackgroundCollection::DrawLayer( int Layer )
	{
		if ( Layer < static_cast<int>( Lists.size() ) )
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
		for ( std::vector<std::shared_ptr<BackgroundFloaterList> >::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			if ( ( *list )->Foreground == Foreground )
				( *list )->Draw( CamMod );

		FinishDraw();
	}

	void BackgroundCollection::PhsxStep()
	{
		for ( std::vector<std::shared_ptr<BackgroundFloaterList> >::const_iterator list = Lists.begin(); list != Lists.end(); ++list )
			( *list )->PhsxStep();
	}

}
