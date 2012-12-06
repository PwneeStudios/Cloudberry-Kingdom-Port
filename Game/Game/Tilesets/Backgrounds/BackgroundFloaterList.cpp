#include <global_header.h>

namespace CloudberryKingdom
{

	BackgroundFloaterList::ClearBackgroundListLambda::ClearBackgroundListLambda( const std::shared_ptr<FloatRectangle> &Area )
	{
		this->Area = Area;
	}

	bool BackgroundFloaterList::ClearBackgroundListLambda::Apply( const std::shared_ptr<BackgroundFloater> &floater )
	{
		if ( floater->Data.Position.X > Area->TR.X || floater->Data.Position.X < Area->BL.X || floater->Data.Position.Y > Area->TR.Y || floater->Data.Position.Y < Area->BL.Y )
			return false;
		else
			return true;
	}

#if defined(INCLUDE_EDITOR)
	const bool &BackgroundFloaterList::getEditable() const
	{
		return Show && !Lock;
	}
#endif

	void BackgroundFloaterList::Reset()
	{
		if ( Floaters.empty() )
			return;

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<std::shared_ptr<BackgroundFloater> >::const_iterator floater = Floaters.begin(); floater != Floaters.end(); ++floater )
			( *floater )->Reset();
	}

	void BackgroundFloaterList::SetParallaxAndPropagate( float Parallax )
	{
		float PrevParallax = this->Parallax;
		this->Parallax = Parallax;

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<std::shared_ptr<BackgroundFloater> >::const_iterator floater = Floaters.begin(); floater != Floaters.end(); ++floater )
			( *floater )->ChangeParallax( PrevParallax, Parallax );
	}

	BackgroundFloaterList::BackgroundFloaterList()
	{
		InitializeInstanceFields();
		//Floaters = std::vector<std::shared_ptr<BackgroundFloater> >();
	}

	void BackgroundFloaterList::Release()
	{
		MyLevel.reset();

		for ( std::vector<std::shared_ptr<BackgroundFloater> >::const_iterator floater = Floaters.begin(); floater != Floaters.end(); ++floater )
			( *floater )->Release();
	}

	void BackgroundFloaterList::SetLevel( const std::shared_ptr<Level> &level )
	{
		MyLevel = level;

		for ( std::vector<std::shared_ptr<BackgroundFloater> >::const_iterator floater = Floaters.begin(); floater != Floaters.end(); ++floater )
			( *floater )->SetLevel( level );
	}

	void BackgroundFloaterList::SetBackground( const std::shared_ptr<Background> &Background_Renamed )
	{
		for ( std::vector<std::shared_ptr<BackgroundFloater> >::const_iterator floater = Floaters.begin(); floater != Floaters.end(); ++floater )
			( *floater )->SetBackground( Background_Renamed );
	}

	void BackgroundFloaterList::Move( Vector2 shift )
	{
		for ( std::vector<std::shared_ptr<BackgroundFloater> >::const_iterator floater = Floaters.begin(); floater != Floaters.end(); ++floater )
			( *floater )->Move( shift );
	}

	void BackgroundFloaterList::Clear()
	{
		Floaters.clear();
	}

	void BackgroundFloaterList::Clear( const std::shared_ptr<FloatRectangle> &Area )
	{
		Tools::RemoveAll( Floaters, std::static_pointer_cast<LambdaFunc_1<std::shared_ptr<BackgroundFloater>, bool> >( std::make_shared<ClearBackgroundListLambda>( Area ) ) );
	}

	void BackgroundFloaterList::Absorb( const std::shared_ptr<BackgroundFloaterList> &list )
	{
		for ( std::vector<std::shared_ptr<BackgroundFloater> >::const_iterator floater = list->Floaters.begin(); floater != list->Floaters.end(); ++floater )
			( *floater )->SetLevel( MyLevel );

		//Floaters.AddRange( list->Floaters );
		AddRange( Floaters, list->Floaters );
	}

	void BackgroundFloaterList::PhsxStep()
	{
		TR = MyLevel->MyBackground->TR;
		BL = MyLevel->MyBackground->BL;
		Vector2 c = MyLevel->getMainCamera()->getPos();

		TR = c + ( TR - c ) / Parallax;
		BL = c + ( BL - c ) / Parallax;

		for ( std::vector<std::shared_ptr<BackgroundFloater> >::const_iterator Floater = Floaters.begin(); Floater != Floaters.end(); ++Floater )
			( *Floater )->PhsxStep( shared_from_this() );
	}

	void BackgroundFloaterList::Draw()
	{
		Draw( 1 );
	}

	void BackgroundFloaterList::Draw( float CamMod )
	{
		if ( !Show )
			return;

		if ( DoPreDraw )
			return;

		Tools::QDrawer->Flush();

		std::shared_ptr<Camera> Cam = MyLevel->getMainCamera();

		Cam->SetVertexZoom( Parallax * CamMod );

		for ( std::vector<std::shared_ptr<BackgroundFloater> >::const_iterator Floater = Floaters.begin(); Floater != Floaters.end(); ++Floater )
			( *Floater )->Draw();
	}

	void BackgroundFloaterList::InitializeInstanceFields()
	{
		Name = _T( "" );
		Foreground = false;
		Fixed = false;
		Show = true;
#if defined(INCLUDE_EDITOR)
		Lock = false;
#endif
		DoPreDraw = false;
	}
}
