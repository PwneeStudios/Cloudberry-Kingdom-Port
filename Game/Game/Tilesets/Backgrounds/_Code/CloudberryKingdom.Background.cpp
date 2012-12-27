#include <global_header.h>

#include "Hacks/Queue.h"

#include "Game/Tilesets/Backgrounds/_Code/CloudberryKingdom.Background.h"
#include "Game/Tilesets/Backgrounds/Background.h"
#include "Game/Tilesets/Backgrounds/BackgroundCollection.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloaterList.h"
#include "Game/Tilesets/Backgrounds/BackgroundFloater_Stationary.h"

namespace CloudberryKingdom
{
	
	// Statics
	bool Background::GreenScreen;
	boost::shared_ptr<QuadClass> Background::TestQuad;
	boost::shared_ptr<EzTexture> Background::TestTexture;

		void AddDarkLayer( boost::shared_ptr<Background> b )
        {
            boost::shared_ptr<BackgroundFloaterList> __46 = boost::make_shared<BackgroundFloaterList>();
            __46->Name = L"Dark";
            __46->Foreground = false;
            __46->Fixed = false;
            
            boost::shared_ptr<BackgroundFloater> __47 = boost::make_shared<BackgroundFloater>();
            __47->Name = L"Dark";
            __47->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
            __47->MyQuad->Quad_Renamed._MyTexture = Tools::TextureWad->DefaultTexture;
            __47->MyQuad->Quad_Renamed.MySetColor = bColor( 255, 255, 255, 158 );
            __47->MyQuad->Quad_Renamed.PremultipliedColor = bColor( 157, 157, 157, 191 );
            __47->MyQuad->Quad_Renamed.BlendAddRatio = 0.f;
            __47->MyQuad->Quad_Renamed.v0.Vertex = MyOwnVertexFormat( Vector2(-2697.719f, 1436.633f ), Vector2( 0.f, 0.f ), bColor( 157, 157, 157, 91 ));
            __47->MyQuad->Quad_Renamed.v0.Pos = Vector2(-1.f, 1.f );

            __47->MyQuad->Quad_Renamed.v1.Vertex = MyOwnVertexFormat( Vector2( 46939.48f, 1436.633f ), Vector2( 18.00215f, 0.f ), bColor( 157, 157, 157, 91 ));
            __47->MyQuad->Quad_Renamed.v1.Pos = Vector2( 1.f, 1.f );

            __47->MyQuad->Quad_Renamed.v2.Vertex = MyOwnVertexFormat( Vector2(-2697.719f, -1321.049f ), Vector2( 0.f, 0.9999274f ), bColor( 157, 157, 157, 91 ));
            __47->MyQuad->Quad_Renamed.v2.Pos = Vector2(-1.f, -1.f );

            __47->MyQuad->Quad_Renamed.v3.Vertex = MyOwnVertexFormat( Vector2( 46939.48f, -1321.049f ), Vector2( 18.00215f, 0.9999274f ), bColor( 157, 157, 157, 91 ));
            __47->MyQuad->Quad_Renamed.v3.Pos = Vector2( 1.f, -1.f );

            __47->MyQuad->Quad_Renamed.SetColor( bColor( 0, 0, 0, 125 ));
            __47->MyQuad->setAlpha( .5f );
            __47->MyQuad->Update();

            __47->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
            __47->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

            __47->MyQuad->Base = BasePoint( 24818.6f, 0.f, 0.f, 1378.841f, 22120.88f, 57.79195f );

            __47->uv_offset = Vector2( 0.f, 0.f );
            __47->Data = PhsxData( 22120.88f, 57.79195f, 0.f, 0.f, 0.f, 0.f );
            __47->StartData = PhsxData( 22120.88f, 57.79195f, 0.f, 0.f, 0.f, 0.f );
            __46->Floaters.push_back(__47 );

            __46->Parallax = 1.05f;
            __46->DoPreDraw = false;

            b->MyCollection->Lists.push_back(__46 );

            b->SetLevel( b->MyLevel );

            __47->MyQuad->Quad_Renamed.SetColor( bColor( 0, 0, 0, 100 ));
            __47->MyQuad->setAlpha( .4f );
            __47->InitialUpdate();
        }

	void Background::AddRainLayer( const boost::shared_ptr<Background> &b )
	{
		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __46 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__46->Name = std::wstring( L"Rain" );
		__46->Foreground = true;
		__46->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __47 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__47->Name = std::wstring( L"Rain" );
		__47->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__47->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"Rain" ) );
		__47->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 158 ) );
		__47->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 91 ) );
		__47->MyQuad->Quad_Renamed.BlendAddRatio = 0.42f;
		__47->MyQuad->Quad_Renamed.v0.Vertex = MyOwnVertexFormat( Vector2( -2697.719f, 1436.633f ), Vector2( 0, 0 ), Color( static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 91 ) ) );
		__47->MyQuad->Quad_Renamed.v0.Pos = Vector2( -1, 1 );

		__47->MyQuad->Quad_Renamed.v1.Vertex = MyOwnVertexFormat( Vector2( 46939.48f, 1436.633f ), Vector2( 18.00215f, 0 ), Color( static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 91 ) ) );
		__47->MyQuad->Quad_Renamed.v1.Pos = Vector2( 1, 1 );

		__47->MyQuad->Quad_Renamed.v2.Vertex = MyOwnVertexFormat( Vector2( -2697.719f, -1321.049f ), Vector2( 0, 0.9999274f ), Color( static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 91 ) ) );
		__47->MyQuad->Quad_Renamed.v2.Pos = Vector2( -1, -1 );

		__47->MyQuad->Quad_Renamed.v3.Vertex = MyOwnVertexFormat( Vector2( 46939.48f, -1321.049f ), Vector2( 18.00215f, 0.9999274f ), Color( static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 157 ), static_cast<unsigned char>( 91 ) ) );
		__47->MyQuad->Quad_Renamed.v3.Pos = Vector2( 1, -1 );

		__47->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__47->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__47->MyQuad->Base = BasePoint( 24818.6f, 0, 0, 1378.841f, 22120.88f, 57.79195f );

		__47->uv_speed = 1.05f * Vector2( 0.0037f, -0.01f );

		__47->uv_offset = Vector2( 0, 0 );
		__47->Data = PhsxData( 22120.88f, 57.79195f, 0, 0, 0, 0 );
		__47->StartData = PhsxData( 22120.88f, 57.79195f, 0, 0, 0, 0 );
		__46->Floaters.push_back( __47 );

		__46->Parallax = 1.05f;
		__46->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __46 );
	}

	void Background::TurnOnSnow( const boost::shared_ptr<Background> &b )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<BackgroundFloaterList> >::const_iterator l = b->MyCollection->Lists.begin(); l != b->MyCollection->Lists.end(); ++l )
			//if ( ( *l )->Name->Contains( std::wstring( L"Snow" ) ) )
			if( ( *l )->Name.find( std::wstring( L"Snow" ) ) != std::wstring::npos )
				( *l )->Show = true;
	}

	void Background::TurnOffSnow( const boost::shared_ptr<Background> &b )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<BackgroundFloaterList> >::const_iterator l = b->MyCollection->Lists.begin(); l != b->MyCollection->Lists.end(); ++l )
			//if ( ( *l )->Name->Contains( std::wstring( L"Snow" ) ) )
			if( ( *l )->Name.find( std::wstring( L"Snow" ) ) != std::wstring::npos )
				( *l )->Show = false;
	}

	void Background::_code_Forest( const boost::shared_ptr<Background> &b )
	{
		b->GuidCounter = 0;
		b->MyGlobalIllumination = 1;
		b->AllowLava = true;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __1 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__1->Name = std::wstring( L"Background" );
		__1->Foreground = false;
		__1->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __2 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__2->Name = std::wstring( L"forest_sky" );
		__2->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__2->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__2->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__2->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_sky" ) );
		__2->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__2->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__2->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__2->MyQuad->Base = BasePoint( 492237.9f, 0, 0, 104122.2f, 135500.6f, 165.7959f );

		__2->uv_speed = Vector2( 0, 0 );
		__2->uv_offset = Vector2( 0, 0 );
		__2->Data = PhsxData( 135500.6f, 165.7959f, 0, 0, 0, 0 );
		__2->StartData = PhsxData( 135500.6f, 165.7959f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __2 );

		__1->Parallax = 0.01f;
		__1->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __1 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __3 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__3->Name = std::wstring( L"Back_Hills" );
		__3->Foreground = false;
		__3->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __4 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__4->Name = std::wstring( L"forest_backhills_trim" );
		__4->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__4->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__4->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__4->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_backhills_trim" ) );
		__4->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__4->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__4->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__4->MyQuad->Base = BasePoint( 32099.83f, 0, 0, 7674.079f, 3356.908f, 7187.623f );

		__4->uv_speed = Vector2( 0, 0 );
		__4->uv_offset = Vector2( 0, 0 );
		__4->Data = PhsxData( 3356.908f, 7187.623f, 0, 0, 0, 0 );
		__4->StartData = PhsxData( 3356.908f, 7187.623f, 0, 0, 0, 0 );
		__3->Floaters.push_back( __4 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __5 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__5->Name = std::wstring( L"forest_backhills_p2_trim" );
		__5->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__5->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__5->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__5->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_backhills_p2_trim" ) );
		__5->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__5->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__5->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__5->MyQuad->Base = BasePoint( 32339.81f, 0, 0, 7936.709f, 44613.05f, 7009.296f );

		__5->uv_speed = Vector2( 0, 0 );
		__5->uv_offset = Vector2( 0, 0 );
		__5->Data = PhsxData( 44613.05f, 7009.296f, 0, 0, 0, 0 );
		__5->StartData = PhsxData( 67792.89f, 7009.296f, 0, 0, 0, 0 );
		__3->Floaters.push_back( __5 );

		__3->Parallax = 0.075f;
		__3->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __3 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __6 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__6->Name = std::wstring( L"Mid_Hills" );
		__6->Foreground = false;
		__6->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __7 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__7->Name = std::wstring( L"forest_mid_trim" );
		__7->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__7->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__7->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__7->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_mid_trim" ) );
		__7->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__7->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__7->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__7->MyQuad->Base = BasePoint( 16162.06f, 0, 0, 3841.054f, 4111.627f, 1395.922f );

		__7->uv_speed = Vector2( 0, 0 );
		__7->uv_offset = Vector2( 0, 0 );
		__7->Data = PhsxData( 4111.627f, 1395.922f, 0, 0, 0, 0 );
		__7->StartData = PhsxData( 4111.627f, 1395.922f, 0, 0, 0, 0 );
		__6->Floaters.push_back( __7 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __8 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__8->Name = std::wstring( L"forest_mid_p2_trim" );
		__8->MyQuad->Quad_Renamed.v0.Vertex = MyOwnVertexFormat( Vector2( 20274.01f, 4238.568f ), Vector2( 0, 0 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__8->MyQuad->Quad_Renamed.v0.Pos = Vector2( -0.724421f, 1.089628f );

		__8->MyQuad->Quad_Renamed.v1.Vertex = MyOwnVertexFormat( Vector2( 52735.53f, 4238.568f ), Vector2( 1, 0 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__8->MyQuad->Quad_Renamed.v1.Pos = Vector2( 1.275579f, 1.089628f );

		__8->MyQuad->Quad_Renamed.v2.Vertex = MyOwnVertexFormat( Vector2( 20274.01f, -2491.818f ), Vector2( 0, 1 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__8->MyQuad->Quad_Renamed.v2.Pos = Vector2( -0.724421f, -0.9103726f );

		__8->MyQuad->Quad_Renamed.v3.Vertex = MyOwnVertexFormat( Vector2( 52735.53f, -2491.818f ), Vector2( 1, 1 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__8->MyQuad->Quad_Renamed.v3.Pos = Vector2( 1.275579f, -0.9103726f );

		__8->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__8->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__8->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__8->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_mid_p2_trim" ) );
		__8->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__8->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__8->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__8->MyQuad->Base = BasePoint( 16230.76f, 0, 0, 3365.192f, 32031.91f, 571.7605f );

		__8->uv_speed = Vector2( 0, 0 );
		__8->uv_offset = Vector2( 0, 0 );
		__8->Data = PhsxData( 32031.91f, 571.7605f, 0, 0, 0, 0 );
		__8->StartData = PhsxData( 32031.91f, 571.7605f, 0, 0, 0, 0 );
		__6->Floaters.push_back( __8 );

		__6->Parallax = 0.15f;
		__6->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __6 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __9 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__9->Name = std::wstring( L"Clouds" );
		__9->Foreground = false;
		__9->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __10 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__10->Name = std::wstring( L"forest_clouds" );
		__10->MyQuad->Quad_Renamed.v0.Vertex = MyOwnVertexFormat( Vector2( -26948.33f, 5153.887f ), Vector2( 0.9800779f, 0 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__10->MyQuad->Quad_Renamed.v0.Pos = Vector2( -1, 1 );

		__10->MyQuad->Quad_Renamed.v1.Vertex = MyOwnVertexFormat( Vector2( 162881.6f, 5153.887f ), Vector2( 3.979689f, 0 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__10->MyQuad->Quad_Renamed.v1.Pos = Vector2( 1, 1 );

		__10->MyQuad->Quad_Renamed.v2.Vertex = MyOwnVertexFormat( Vector2( -26948.33f, -2755.695f ), Vector2( 0.9800779f, 1 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__10->MyQuad->Quad_Renamed.v2.Pos = Vector2( -1, -1 );

		__10->MyQuad->Quad_Renamed.v3.Vertex = MyOwnVertexFormat( Vector2( 162881.6f, -2755.695f ), Vector2( 3.979689f, 1 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__10->MyQuad->Quad_Renamed.v3.Pos = Vector2( 1, -1 );

		__10->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__10->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__10->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__10->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_clouds" ) );
		__10->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__10->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__10->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__10->MyQuad->Base = BasePoint( 94914.98f, 0, 0, 3954.791f, 67966.65f, 1199.096f );

		__10->uv_speed = Vector2( 0.0003f, 0 );
		__10->uv_offset = Vector2( 0, 0 );
		__10->Data = PhsxData( 67966.65f, 1199.096f, 0, 0, 0, 0 );
		__10->StartData = PhsxData( 67966.65f, 1199.096f, 0, 0, 0, 0 );
		__9->Floaters.push_back( __10 );

		__9->Parallax = 0.19f;
		__9->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __9 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __11 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__11->Name = std::wstring( L"Small_Trees" );
		__11->Foreground = false;
		__11->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __12 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__12->Name = std::wstring( L"forest_backtrees_p1_0" );
		__12->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__12->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__12->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__12->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_backtrees" ) );
		__12->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__12->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__12->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__12->MyQuad->Base = BasePoint( 10096.42f, 0, 0, 3263.351f, -1550.031f, -1179.254f );

		__12->uv_speed = Vector2( 0, 0 );
		__12->uv_offset = Vector2( 0, 0 );
		__12->Data = PhsxData( -1550.031f, -1179.254f, 0, 0, 0, 0 );
		__12->StartData = PhsxData( -1550.031f, -1179.254f, 0, 0, 0, 0 );
		__11->Floaters.push_back( __12 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __13 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__13->Name = std::wstring( L"forest_backtrees_p2_0" );
		__13->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__13->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__13->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__13->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_backtrees_p2" ) );
		__13->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__13->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__13->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__13->MyQuad->Base = BasePoint( 10576.94f, 0, 0, 3263.351f, 19061.51f, -1282.274f );

		__13->uv_speed = Vector2( 0, 0 );
		__13->uv_offset = Vector2( 0, 0 );
		__13->Data = PhsxData( 19061.51f, -1282.274f, 0, 0, 0, 0 );
		__13->StartData = PhsxData( 19061.51f, -1282.274f, 0, 0, 0, 0 );
		__11->Floaters.push_back( __13 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __14 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__14->Name = std::wstring( L"forest_backtrees_p1_0" );
		__14->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__14->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__14->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__14->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_backtrees" ) );
		__14->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__14->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__14->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__14->MyQuad->Base = BasePoint( 10072.41f, 0, 0, 3255.594f, 34797.7f, -1059.907f );

		__14->uv_speed = Vector2( 0, 0 );
		__14->uv_offset = Vector2( 0, 0 );
		__14->Data = PhsxData( 34797.7f, -1059.907f, 0, 0, 0, 0 );
		__14->StartData = PhsxData( 36512.66f, -1059.907f, 0, 0, 0, 0 );
		__11->Floaters.push_back( __14 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __15 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__15->Name = std::wstring( L"forest_backtrees_p2_0" );
		__15->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__15->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__15->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__15->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_backtrees_p2" ) );
		__15->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__15->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__15->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__15->MyQuad->Base = BasePoint( 10551.8f, 0, 0, 3255.594f, 35277.09f, -1059.907f );

		__15->uv_speed = Vector2( 0, 0 );
		__15->uv_offset = Vector2( 0, 0 );
		__15->Data = PhsxData( 35277.09f, -1059.907f, 0, 0, 0, 0 );
		__15->StartData = PhsxData( 57136.88f, -1059.907f, 0, 0, 0, 0 );
		__11->Floaters.push_back( __15 );

		__11->Parallax = 0.25f;
		__11->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __11 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __16 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__16->Name = std::wstring( L"Snow1" );
		__16->Foreground = false;
		__16->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __17 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__17->Name = std::wstring( L"Snow" );
		__17->MyQuad->Quad_Renamed.v0.Vertex = MyOwnVertexFormat( Vector2( -16817, 4586.932f ), 1 * Vector2( 21.61522f, -10.28082f ), Color( static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ) ) );
		__17->MyQuad->Quad_Renamed.v0.Pos = Vector2( -1, 1 );

		__17->MyQuad->Quad_Renamed.v1.Vertex = MyOwnVertexFormat( Vector2( 310331.8f, 4586.932f ), 1 * Vector2( 41.61494f, -10.28082f ), Color( static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ) ) );
		__17->MyQuad->Quad_Renamed.v1.Pos = Vector2( 1, 1 );

		__17->MyQuad->Quad_Renamed.v2.Vertex = MyOwnVertexFormat( Vector2( -16817, -4614.128f ), 1 * Vector2( 21.61522f, -9.277841f ), Color( static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ) ) );
		__17->MyQuad->Quad_Renamed.v2.Pos = Vector2( -1, -1 );

		__17->MyQuad->Quad_Renamed.v3.Vertex = MyOwnVertexFormat( Vector2( 310331.8f, -4614.128f ), 1 * Vector2( 41.61494f, -9.277841f ), Color( static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ) ) );
		__17->MyQuad->Quad_Renamed.v3.Pos = Vector2( 1, -1 );

		__17->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__17->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__17->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__17->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"Snow" ) );
		__17->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 89 ) );
		__17->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ), static_cast<unsigned char>( 88 ) );
		__17->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__17->MyQuad->setAlpha( .7f );

		__17->MyQuad->Base = BasePoint( 163574.4f, 0, 0, 4600.53f, 146757.4f, -13.5979f );

		__17->uv_speed = 1.25f * Vector2( 0.001f, -0.0009f );
		__17->uv_offset = Vector2( 18.35001f, -7.339994f );
		__17->Data = PhsxData( 146757.4f, -13.5979f, 0, 0, 0, 0 );
		__17->StartData = PhsxData( 146757.4f, -13.5979f, 0, 0, 0, 0 );
		__16->Floaters.push_back( __17 );

		__16->Parallax = 0.25f;
		__16->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __16 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __18 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__18->Name = std::wstring( L"Big_Trees" );
		__18->Foreground = false;
		__18->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __19 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__19->Name = std::wstring( L"forest_foretrees_p1_0" );
		__19->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__19->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__19->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__19->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_foretrees" ) );
		__19->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__19->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__19->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__19->MyQuad->Base = BasePoint( 4487.996f, 0, 0, 1898.676f, 2154.271f, -47.44482f );

		__19->uv_speed = Vector2( 0, 0 );
		__19->uv_offset = Vector2( 0, 0 );
		__19->Data = PhsxData( 2154.271f, -47.44482f, 0, 0, 0, 0 );
		__19->StartData = PhsxData( 2154.271f, -47.44482f, 0, 0, 0, 0 );
		__18->Floaters.push_back( __19 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __20 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__20->Name = std::wstring( L"forest_foretrees_p2_0" );
		__20->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__20->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__20->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__20->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_foretrees_p2" ) );
		__20->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__20->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__20->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__20->MyQuad->Base = BasePoint( 4487.996f, 0, 0, 1898.676f, 11130.26f, -47.44482f );

		__20->uv_speed = Vector2( 0, 0 );
		__20->uv_offset = Vector2( 0, 0 );
		__20->Data = PhsxData( 11130.26f, -47.44482f, 0, 0, 0, 0 );
		__20->StartData = PhsxData( 11130.26f, -47.44482f, 0, 0, 0, 0 );
		__18->Floaters.push_back( __20 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __21 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__21->Name = std::wstring( L"forest_foretrees_p1_0" );
		__21->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__21->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__21->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__21->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_foretrees" ) );
		__21->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__21->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__21->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__21->MyQuad->Base = BasePoint( 4441.479f, 0, 0, 1878.997f, 19630.17f, -49.1123f );

		__21->uv_speed = Vector2( 0, 0 );
		__21->uv_offset = Vector2( 0, 0 );
		__21->Data = PhsxData( 19630.17f, -49.1123f, 0, 0, 0, 0 );
		__21->StartData = PhsxData( 19630.17f, -49.1123f, 0, 0, 0, 0 );
		__18->Floaters.push_back( __21 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __22 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__22->Name = std::wstring( L"forest_foretrees_p2_0" );
		__22->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__22->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__22->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__22->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_foretrees_p2" ) );
		__22->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__22->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__22->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__22->MyQuad->Base = BasePoint( 4441.479f, 0, 0, 1878.997f, 28513.13f, -49.1123f );

		__22->uv_speed = Vector2( 0, 0 );
		__22->uv_offset = Vector2( 0, 0 );
		__22->Data = PhsxData( 28513.13f, -49.1123f, 0, 0, 0, 0 );
		__22->StartData = PhsxData( 28513.13f, -49.1123f, 0, 0, 0, 0 );
		__18->Floaters.push_back( __22 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __23 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__23->Name = std::wstring( L"forest_foretrees_p1_0" );
		__23->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__23->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__23->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__23->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_foretrees" ) );
		__23->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__23->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__23->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__23->MyQuad->Base = BasePoint( 4441.479f, 0, 0, 1878.997f, 32126.74f, -92.27881f );

		__23->uv_speed = Vector2( 0, 0 );
		__23->uv_offset = Vector2( 0, 0 );
		__23->Data = PhsxData( 32126.74f, -92.27881f, 0, 0, 0, 0 );
		__23->StartData = PhsxData( 37097.56f, -92.27881f, 0, 0, 0, 0 );
		__18->Floaters.push_back( __23 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __24 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__24->Name = std::wstring( L"forest_foretrees_p2_0" );
		__24->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__24->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__24->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__24->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"forest_foretrees_p2" ) );
		__24->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__24->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__24->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__24->MyQuad->Base = BasePoint( 4441.479f, 0, 0, 1878.997f, 32126.74f, -92.27881f );

		__24->uv_speed = Vector2( 0, 0 );
		__24->uv_offset = Vector2( 0, 0 );
		__24->Data = PhsxData( 32126.74f, -92.27881f, 0, 0, 0, 0 );
		__24->StartData = PhsxData( 45980.52f, -92.27881f, 0, 0, 0, 0 );
		__18->Floaters.push_back( __24 );

		__18->Parallax = 0.55f;
		__18->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __18 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __25 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__25->Name = std::wstring( L"Snow2" );
		__25->Foreground = true;
		__25->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __26 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__26->Name = std::wstring( L"Snow" );
		__26->MyQuad->Quad_Renamed.v0.Vertex = MyOwnVertexFormat( Vector2( -37182.87f, 1486.698f ), Vector2( 4.900445f, -4.900445f ), Color( static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ) ) );
		__26->MyQuad->Quad_Renamed.v0.Pos = Vector2( -1, 1 );

		__26->MyQuad->Quad_Renamed.v1.Vertex = MyOwnVertexFormat( Vector2( 68532.89f, 1486.698f ), Vector2( 24.8849f, -4.900445f ), Color( static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ) ) );
		__26->MyQuad->Quad_Renamed.v1.Pos = Vector2( 1, 1 );

		__26->MyQuad->Quad_Renamed.v2.Vertex = MyOwnVertexFormat( Vector2( -37182.87f, -1486.698f ), Vector2( 4.900445f, -3.900311f ), Color( static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ) ) );
		__26->MyQuad->Quad_Renamed.v2.Pos = Vector2( -1, -1 );

		__26->MyQuad->Quad_Renamed.v3.Vertex = MyOwnVertexFormat( Vector2( 68532.89f, -1486.698f ), Vector2( 24.8849f, -3.900311f ), Color( static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ) ) );
		__26->MyQuad->Quad_Renamed.v3.Pos = Vector2( 1, -1 );

		__26->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__26->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__26->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__26->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"Snow" ) );
		__26->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 196 ) );
		__26->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ), static_cast<unsigned char>( 195 ) );
		__26->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__26->MyQuad->Base = BasePoint( 52857.88f, 0, 0, 1486.698f, 15675.01f, 0 );

		__26->uv_speed = Vector2( 0.0015f, -0.0015f );
		__26->uv_offset = Vector2( 0, 0 );
		__26->Data = PhsxData( 15675.01f, 0, 0, 0, 0, 0 );
		__26->StartData = PhsxData( 15675.01f, 0, 0, 0, 0, 0 );
		__25->Floaters.push_back( __26 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __27 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__27->Name = std::wstring( L"Snow" );
		__27->MyQuad->Quad_Renamed.v0.Vertex = MyOwnVertexFormat( Vector2( -4499.879f, 1865.506f ), Vector2( 6.533891f, -7.513808f ), Color( static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ) ) );
		__27->MyQuad->Quad_Renamed.v0.Pos = Vector2( -1, 1 );

		__27->MyQuad->Quad_Renamed.v1.Vertex = MyOwnVertexFormat( Vector2( 118981.7f, 1865.506f ), Vector2( 26.55114f, -7.513808f ), Color( static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ) ) );
		__27->MyQuad->Quad_Renamed.v1.Pos = Vector2( 1, 1 );

		__27->MyQuad->Quad_Renamed.v2.Vertex = MyOwnVertexFormat( Vector2( -4499.879f, -1605.93f ), Vector2( 6.533891f, -6.514019f ), Color( static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ) ) );
		__27->MyQuad->Quad_Renamed.v2.Pos = Vector2( -1, -1 );

		__27->MyQuad->Quad_Renamed.v3.Vertex = MyOwnVertexFormat( Vector2( 118981.7f, -1605.93f ), Vector2( 26.55114f, -6.514019f ), Color( static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ) ) );
		__27->MyQuad->Quad_Renamed.v3.Pos = Vector2( 1, -1 );

		__27->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__27->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__27->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__27->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"Snow" ) );
		__27->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 224 ) );
		__27->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ), static_cast<unsigned char>( 223 ) );
		__27->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__27->MyQuad->Base = BasePoint( 61740.77f, 0, 0, 1735.718f, 57240.89f, 129.7882f );

		__27->uv_speed = Vector2( 0.002f, -0.0023f );
		__27->uv_offset = Vector2( 0, 0 );
		__27->Data = PhsxData( 57240.89f, 129.7882f, 0, 0, 0, 0 );
		__27->StartData = PhsxData( 57240.89f, 129.7882f, 0, 0, 0, 0 );
		__25->Floaters.push_back( __27 );

		__25->Parallax = 0.9f;
		__25->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __25 );

		b->Light = 1;
		//b.BL = new Vector2(-4900f, -4500f);
		//b.TR = new Vector2(28677.74f, 2055.556f);
		b->BL = Vector2( -100000, -10000 );
		b->TR = Vector2( 100000, 10000 );
	}

	void Background::_code_Cloud( const boost::shared_ptr<Background> &b )
	{
		b->GuidCounter = 0;
		b->MyGlobalIllumination = 1;
		b->AllowLava = true;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __1 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__1->Name = std::wstring( L"Layer" );
		__1->Foreground = false;
		__1->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __2 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__2->Name = std::wstring( L"cloud_castle_layer5" );
		__2->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__2->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__2->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__2->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer5" ) );
		__2->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__2->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__2->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__2->MyQuad->Base = BasePoint( 23579.31f, 0, 0, 10479.69f, 5485.83f, -9.382813f );

		__2->uv_speed = Vector2( 0, 0 );
		__2->uv_offset = Vector2( 0, 0 );
		__2->Data = PhsxData( 5485.83f, -9.382813f, 0, 0, 0, 0 );
		__2->StartData = PhsxData( 5485.83f, -9.382813f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __2 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __3 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__3->Name = std::wstring( L"cloud_castle_layer5" );
		__3->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__3->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer5_p2" ) );
		__3->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__3->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__3->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__3->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__3->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__3->MyQuad->Base = BasePoint( 23579.31f, 0, 0, 10479.69f, 52644.45f, -9.382813f );

		__3->uv_speed = Vector2( 0, 0 );
		__3->uv_offset = Vector2( 0, 0 );
		__3->Data = PhsxData( 52644.45f, -9.382813f, 0, 0, 0, 0 );
		__3->StartData = PhsxData( 52644.45f, -9.382813f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __3 );

		__1->Parallax = 0.1f;
		__1->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __1 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __4 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__4->Name = std::wstring( L"Layer" );
		__4->Foreground = false;
		__4->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __5 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__5->Name = std::wstring( L"cloud_castle_layer4" );
		__5->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__5->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer4" ) );
		__5->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__5->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__5->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__5->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__5->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__5->MyQuad->Base = BasePoint( 13583.82f, 0, 0, 6025.19f, 3683.155f, -164.6855f );

		__5->uv_speed = Vector2( 0, 0 );
		__5->uv_offset = Vector2( 0, 0 );
		__5->Data = PhsxData( 3683.155f, -164.6855f, 0, 0, 0, 0 );
		__5->StartData = PhsxData( 3683.155f, -164.6855f, 0, 0, 0, 0 );
		__4->Floaters.push_back( __5 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __6 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__6->Name = std::wstring( L"cloud_castle_layer4" );
		__6->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__6->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer4_p2" ) );
		__6->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__6->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__6->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__6->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__6->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__6->MyQuad->Base = BasePoint( 13583.82f, 0, 0, 6025.19f, 30850.79f, -164.6855f );

		__6->uv_speed = Vector2( 0, 0 );
		__6->uv_offset = Vector2( 0, 0 );
		__6->Data = PhsxData( 30850.79f, -164.6855f, 0, 0, 0, 0 );
		__6->StartData = PhsxData( 30850.79f, -164.6855f, 0, 0, 0, 0 );
		__4->Floaters.push_back( __6 );

		__4->Parallax = 0.17f;
		__4->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __4 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __7 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__7->Name = std::wstring( L"cloud_3" );
		__7->Foreground = false;
		__7->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __8 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__8->Name = std::wstring( L"cloud_cloud_layer3_1" );
		__8->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__8->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer3_1" ) );
		__8->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__8->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__8->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__8->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__8->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__8->MyQuad->Base = BasePoint( 1440, 0, 0, 813.913f, -7449.813f, 713.1904f );

		__8->uv_speed = Vector2( 0, 0 );
		__8->uv_offset = Vector2( 0, 0 );
		__8->Data = PhsxData( -7449.813f, 713.1904f, 0, 0, 0, 0 );
		__8->StartData = PhsxData( -7449.813f, 713.1904f, 0, 0, 0, 0 );
		__7->Floaters.push_back( __8 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __9 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__9->Name = std::wstring( L"cloud_cloud_layer3_2" );
		__9->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__9->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer3_2" ) );
		__9->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__9->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__9->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__9->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__9->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__9->MyQuad->Base = BasePoint( 1440, 0, 0, 872.7272f, -2406.215f, 935.2354f );

		__9->uv_speed = Vector2( 0, 0 );
		__9->uv_offset = Vector2( 0, 0 );
		__9->Data = PhsxData( -2406.215f, 935.2354f, 0, 0, 0, 0 );
		__9->StartData = PhsxData( -2406.215f, 935.2354f, 0, 0, 0, 0 );
		__7->Floaters.push_back( __9 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __10 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__10->Name = std::wstring( L"cloud_cloud_layer3_3" );
		__10->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__10->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer3_3" ) );
		__10->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__10->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__10->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__10->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__10->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__10->MyQuad->Base = BasePoint( 1440, 0, 0, 804.7058f, 2447.061f, 205.6582f );

		__10->uv_speed = Vector2( 0, 0 );
		__10->uv_offset = Vector2( 0, 0 );
		__10->Data = PhsxData( 2447.061f, 205.6582f, 0, 0, 0, 0 );
		__10->StartData = PhsxData( 2447.061f, 205.6582f, 0, 0, 0, 0 );
		__7->Floaters.push_back( __10 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __11 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__11->Name = std::wstring( L"cloud_cloud_layer3_4" );
		__11->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__11->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer3_4" ) );
		__11->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__11->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__11->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__11->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__11->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__11->MyQuad->Base = BasePoint( 1440, 0, 0, 854.9999f, 5904.623f, 78.77539f );

		__11->uv_speed = Vector2( 0, 0 );
		__11->uv_offset = Vector2( 0, 0 );
		__11->Data = PhsxData( 5904.623f, 78.77539f, 0, 0, 0, 0 );
		__11->StartData = PhsxData( 5904.623f, 78.77539f, 0, 0, 0, 0 );
		__7->Floaters.push_back( __11 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __12 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__12->Name = std::wstring( L"cloud_cloud_layer3_5" );
		__12->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__12->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer3_5" ) );
		__12->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__12->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__12->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__12->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__12->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__12->MyQuad->Base = BasePoint( 1440, 0, 0, 606.8827f, 9330.461f, 522.8662f );

		__12->uv_speed = Vector2( 0, 0 );
		__12->uv_offset = Vector2( 0, 0 );
		__12->Data = PhsxData( 9330.461f, 522.8662f, 0, 0, 0, 0 );
		__12->StartData = PhsxData( 9330.461f, 522.8662f, 0, 0, 0, 0 );
		__7->Floaters.push_back( __12 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __13 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__13->Name = std::wstring( L"cloud_cloud_layer3_6" );
		__13->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__13->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer3_6" ) );
		__13->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__13->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__13->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__13->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__13->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__13->MyQuad->Base = BasePoint( 1440, 0, 0, 1008, 12312.21f, 15.33398f );

		__13->uv_speed = Vector2( 0, 0 );
		__13->uv_offset = Vector2( 0, 0 );
		__13->Data = PhsxData( 12312.21f, 15.33398f, 0, 0, 0, 0 );
		__13->StartData = PhsxData( 12312.21f, 15.33398f, 0, 0, 0, 0 );
		__7->Floaters.push_back( __13 );

		__7->Parallax = 0.25f;
		__7->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __7 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __14 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__14->Name = std::wstring( L"castle_3" );
		__14->Foreground = false;
		__14->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __15 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__15->Name = std::wstring( L"cloud_castle_layer3_1" );
		__15->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__15->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer3_1" ) );
		__15->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__15->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__15->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__15->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__15->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__15->MyQuad->Base = BasePoint( 1619.587f, 0, 0, 1574.057f, -3419.336f, -1515.219f );

		__15->uv_speed = Vector2( 0, 0 );
		__15->uv_offset = Vector2( 0, 0 );
		__15->Data = PhsxData( -3419.336f, -1515.219f, 0, 0, 0, 0 );
		__15->StartData = PhsxData( -3419.336f, -1515.219f, 0, 0, 0, 0 );
		__14->Floaters.push_back( __15 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __16 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__16->Name = std::wstring( L"cloud_castle_layer3_2" );
		__16->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__16->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer3_2" ) );
		__16->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__16->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__16->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__16->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__16->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__16->MyQuad->Base = BasePoint( 1090.909f, 0, 0, 1556.735f, 6745.723f, -1731.496f );

		__16->uv_speed = Vector2( 0, 0 );
		__16->uv_offset = Vector2( 0, 0 );
		__16->Data = PhsxData( 6745.723f, -1731.496f, 0, 0, 0, 0 );
		__16->StartData = PhsxData( 6745.723f, -1731.496f, 0, 0, 0, 0 );
		__14->Floaters.push_back( __16 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __17 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__17->Name = std::wstring( L"cloud_castle_layer3_3" );
		__17->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__17->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer3_3" ) );
		__17->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__17->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__17->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__17->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__17->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__17->MyQuad->Base = BasePoint( 1114.938f, 0, 0, 2341.099f, 10662.76f, -1642.704f );

		__17->uv_speed = Vector2( 0, 0 );
		__17->uv_offset = Vector2( 0, 0 );
		__17->Data = PhsxData( 10662.76f, -1642.704f, 0, 0, 0, 0 );
		__17->StartData = PhsxData( 10662.76f, -1642.704f, 0, 0, 0, 0 );
		__14->Floaters.push_back( __17 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __18 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__18->Name = std::wstring( L"cloud_castle_layer3_1" );
		__18->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__18->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer3_1" ) );
		__18->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__18->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__18->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__18->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__18->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__18->MyQuad->Base = BasePoint( 1619.587f, 0, 0, 1574.057f, 18973.14f, -1646.107f );

		__18->uv_speed = Vector2( 0, 0 );
		__18->uv_offset = Vector2( 0, 0 );
		__18->Data = PhsxData( 18973.14f, -1646.107f, 0, 0, 0, 0 );
		__18->StartData = PhsxData( 18973.14f, -1646.107f, 0, 0, 0, 0 );
		__14->Floaters.push_back( __18 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __19 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__19->Name = std::wstring( L"cloud_castle_layer3_2" );
		__19->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__19->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer3_2" ) );
		__19->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__19->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__19->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__19->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__19->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__19->MyQuad->Base = BasePoint( 1090.909f, 0, 0, 1556.735f, 24460.43f, -1646.107f );

		__19->uv_speed = Vector2( 0, 0 );
		__19->uv_offset = Vector2( 0, 0 );
		__19->Data = PhsxData( 24460.43f, -1646.107f, 0, 0, 0, 0 );
		__19->StartData = PhsxData( 24460.43f, -1646.107f, 0, 0, 0, 0 );
		__14->Floaters.push_back( __19 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __20 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__20->Name = std::wstring( L"cloud_castle_layer3_3" );
		__20->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__20->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer3_3" ) );
		__20->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__20->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__20->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__20->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__20->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__20->MyQuad->Base = BasePoint( 1114.938f, 0, 0, 2341.099f, 27066.12f, -1891.348f );

		__20->uv_speed = Vector2( 0, 0 );
		__20->uv_offset = Vector2( 0, 0 );
		__20->Data = PhsxData( 27066.12f, -1891.348f, 0, 0, 0, 0 );
		__20->StartData = PhsxData( 27066.12f, -1891.348f, 0, 0, 0, 0 );
		__14->Floaters.push_back( __20 );

		__14->Parallax = 0.33f;
		__14->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __14 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __21 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__21->Name = std::wstring( L"cloud_2" );
		__21->Foreground = false;
		__21->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __22 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__22->Name = std::wstring( L"cloud_cloud_layer2_1" );
		__22->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__22->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer2_1" ) );
		__22->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__22->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__22->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__22->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__22->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__22->MyQuad->Base = BasePoint( 4429.467f, 0, 0, 1100.83f, 1758.984f, 54.01685f );

		__22->uv_speed = Vector2( 0, 0 );
		__22->uv_offset = Vector2( 0, 0 );
		__22->Data = PhsxData( 1758.984f, 54.01685f, 0, 0, 0, 0 );
		__22->StartData = PhsxData( 1758.984f, 54.01685f, 0, 0, 0, 0 );
		__21->Floaters.push_back( __22 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __23 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__23->Name = std::wstring( L"cloud_cloud_layer2_1" );
		__23->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__23->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer2_1" ) );
		__23->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__23->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__23->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__23->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__23->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__23->MyQuad->Base = BasePoint( 4429.467f, 0, 0, 1100.83f, 15294.52f, 3.80072f );

		__23->uv_speed = Vector2( 0, 0 );
		__23->uv_offset = Vector2( 0, 0 );
		__23->Data = PhsxData( 15294.52f, 3.80072f, 0, 0, 0, 0 );
		__23->StartData = PhsxData( 15294.52f, 3.80072f, 0, 0, 0, 0 );
		__21->Floaters.push_back( __23 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __24 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__24->Name = std::wstring( L"cloud_cloud_layer2_1" );
		__24->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__24->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer2_1" ) );
		__24->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__24->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__24->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__24->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__24->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__24->MyQuad->Base = BasePoint( 4429.467f, 0, 0, 1100.83f, 26639.14f, -429.751f );

		__24->uv_speed = Vector2( 0, 0 );
		__24->uv_offset = Vector2( 0, 0 );
		__24->Data = PhsxData( 26639.14f, -429.751f, 0, 0, 0, 0 );
		__24->StartData = PhsxData( 26639.14f, -429.751f, 0, 0, 0, 0 );
		__21->Floaters.push_back( __24 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __25 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__25->Name = std::wstring( L"cloud_cloud_layer2_1" );
		__25->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__25->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer2_1" ) );
		__25->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__25->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__25->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__25->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__25->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__25->MyQuad->Base = BasePoint( 4429.467f, 0, 0, 1100.83f, 38561.82f, -502.0099f );

		__25->uv_speed = Vector2( 0, 0 );
		__25->uv_offset = Vector2( 0, 0 );
		__25->Data = PhsxData( 38561.82f, -502.0099f, 0, 0, 0, 0 );
		__25->StartData = PhsxData( 38561.82f, -502.0099f, 0, 0, 0, 0 );
		__21->Floaters.push_back( __25 );

		__21->Parallax = 0.28f;
		__21->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __21 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __26 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__26->Name = std::wstring( L"castle_2" );
		__26->Foreground = false;
		__26->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __27 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__27->Name = std::wstring( L"cloud_castle_layer2_1" );
		__27->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__27->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer2_1" ) );
		__27->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__27->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__27->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__27->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__27->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__27->MyQuad->Base = BasePoint( 1350.048f, 0, 0, 2798.974f, -2574.793f, -1026.896f );

		__27->uv_speed = Vector2( 0, 0 );
		__27->uv_offset = Vector2( 0, 0 );
		__27->Data = PhsxData( -2574.793f, -1026.896f, 0, 0, 0, 0 );
		__27->StartData = PhsxData( -2574.793f, -1026.896f, 0, 0, 0, 0 );
		__26->Floaters.push_back( __27 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __28 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__28->Name = std::wstring( L"cloud_castle_layer2_2" );
		__28->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__28->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer2_2" ) );
		__28->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__28->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__28->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__28->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__28->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__28->MyQuad->Base = BasePoint( 1415.46f, 0, 0, 2348.253f, 4617.543f, -726.7338f );

		__28->uv_speed = Vector2( 0, 0 );
		__28->uv_offset = Vector2( 0, 0 );
		__28->Data = PhsxData( 4617.543f, -726.7338f, 0, 0, 0, 0 );
		__28->StartData = PhsxData( 4617.543f, -726.7338f, 0, 0, 0, 0 );
		__26->Floaters.push_back( __28 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __29 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__29->Name = std::wstring( L"cloud_castle_layer2_3" );
		__29->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__29->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer2_3" ) );
		__29->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__29->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__29->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__29->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__29->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__29->MyQuad->Base = BasePoint( 1256.856f, 0, 0, 2094.533f, 13222.73f, -543.1658f );

		__29->uv_speed = Vector2( 0, 0 );
		__29->uv_offset = Vector2( 0, 0 );
		__29->Data = PhsxData( 13222.73f, -543.1658f, 0, 0, 0, 0 );
		__29->StartData = PhsxData( 13222.73f, -543.1658f, 0, 0, 0, 0 );
		__26->Floaters.push_back( __29 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __30 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__30->Name = std::wstring( L"cloud_castle_layer2_1" );
		__30->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__30->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer2_1" ) );
		__30->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__30->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__30->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__30->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__30->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__30->MyQuad->Base = BasePoint( 1350.048f, 0, 0, 2798.974f, 17024.4f, -1760.757f );

		__30->uv_speed = Vector2( 0, 0 );
		__30->uv_offset = Vector2( 0, 0 );
		__30->Data = PhsxData( 17024.4f, -1760.757f, 0, 0, 0, 0 );
		__30->StartData = PhsxData( 17024.4f, -1760.757f, 0, 0, 0, 0 );
		__26->Floaters.push_back( __30 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __31 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__31->Name = std::wstring( L"cloud_castle_layer2_2" );
		__31->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__31->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer2_2" ) );
		__31->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__31->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__31->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__31->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__31->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__31->MyQuad->Base = BasePoint( 1415.46f, 0, 0, 2348.253f, 21905.47f, -1027.331f );

		__31->uv_speed = Vector2( 0, 0 );
		__31->uv_offset = Vector2( 0, 0 );
		__31->Data = PhsxData( 21905.47f, -1027.331f, 0, 0, 0, 0 );
		__31->StartData = PhsxData( 21905.47f, -1027.331f, 0, 0, 0, 0 );
		__26->Floaters.push_back( __31 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __32 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__32->Name = std::wstring( L"cloud_castle_layer2_3" );
		__32->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__32->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer2_3" ) );
		__32->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__32->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__32->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__32->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__32->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__32->MyQuad->Base = BasePoint( 1590.616f, 0, 0, 2662.089f, 29651.78f, -1127.46f );

		__32->uv_speed = Vector2( 0, 0 );
		__32->uv_offset = Vector2( 0, 0 );
		__32->Data = PhsxData( 29651.78f, -1127.46f, 0, 0, 0, 0 );
		__32->StartData = PhsxData( 29651.78f, -1127.46f, 0, 0, 0, 0 );
		__26->Floaters.push_back( __32 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __33 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__33->Name = std::wstring( L"cloud_castle_layer2_1" );
		__33->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__33->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer2_1" ) );
		__33->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__33->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__33->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__33->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__33->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__33->MyQuad->Base = BasePoint( 882.7829f, 0, 0, 1830.22f, 33324.57f, -2302.971f );

		__33->uv_speed = Vector2( 0, 0 );
		__33->uv_offset = Vector2( 0, 0 );
		__33->Data = PhsxData( 33324.57f, -2302.971f, 0, 0, 0, 0 );
		__33->StartData = PhsxData( 33324.57f, -2302.971f, 0, 0, 0, 0 );
		__26->Floaters.push_back( __33 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __34 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__34->Name = std::wstring( L"cloud_castle_layer2_2" );
		__34->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__34->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer2_2" ) );
		__34->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__34->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__34->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__34->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__34->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__34->MyQuad->Base = BasePoint( 1415.46f, 0, 0, 2348.253f, 37953.88f, -2136.087f );

		__34->uv_speed = Vector2( 0, 0 );
		__34->uv_offset = Vector2( 0, 0 );
		__34->Data = PhsxData( 37953.88f, -2136.087f, 0, 0, 0, 0 );
		__34->StartData = PhsxData( 37953.88f, -2136.087f, 0, 0, 0, 0 );
		__26->Floaters.push_back( __34 );

		__26->Parallax = 0.4f;
		__26->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __26 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __35 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__35->Name = std::wstring( L"cloud_1" );
		__35->Foreground = false;
		__35->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __36 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__36->Name = std::wstring( L"cloud_cloud_layer1_1" );
		__36->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__36->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer1_1" ) );
		__36->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__36->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__36->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__36->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__36->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__36->MyQuad->Base = BasePoint( 1286.25f, 0, 0, 706.0881f, -106.0938f, -291.884f );

		__36->uv_speed = Vector2( 0, 0 );
		__36->uv_offset = Vector2( 0, 0 );
		__36->Data = PhsxData( -106.0938f, -291.884f, 0, 0, 0, 0 );
		__36->StartData = PhsxData( -106.0938f, -291.884f, 0, 0, 0, 0 );
		__35->Floaters.push_back( __36 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __37 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__37->Name = std::wstring( L"cloud_cloud_layer1_2" );
		__37->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__37->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer1_2" ) );
		__37->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__37->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__37->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__37->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__37->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__37->MyQuad->Base = BasePoint( 1153.097f, 0, 0, 600.9785f, 4506.916f, -181.2072f );

		__37->uv_speed = Vector2( 0, 0 );
		__37->uv_offset = Vector2( 0, 0 );
		__37->Data = PhsxData( 4506.916f, -181.2072f, 0, 0, 0, 0 );
		__37->StartData = PhsxData( 4506.916f, -181.2072f, 0, 0, 0, 0 );
		__35->Floaters.push_back( __37 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __38 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__38->Name = std::wstring( L"cloud_cloud_layer1_3" );
		__38->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__38->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer1_3" ) );
		__38->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__38->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__38->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__38->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__38->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__38->MyQuad->Base = BasePoint( 1163.339f, 0, 0, 451.3339f, 7103.76f, -501.3638f );

		__38->uv_speed = Vector2( 0, 0 );
		__38->uv_offset = Vector2( 0, 0 );
		__38->Data = PhsxData( 7103.76f, -501.3638f, 0, 0, 0, 0 );
		__38->StartData = PhsxData( 7103.76f, -501.3638f, 0, 0, 0, 0 );
		__35->Floaters.push_back( __38 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __39 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__39->Name = std::wstring( L"cloud_cloud_layer1_4" );
		__39->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__39->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer1_4" ) );
		__39->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__39->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__39->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__39->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__39->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__39->MyQuad->Base = BasePoint( 978.9733f, 0, 0, 644.0235f, 10113.27f, -203.6833f );

		__39->uv_speed = Vector2( 0, 0 );
		__39->uv_offset = Vector2( 0, 0 );
		__39->Data = PhsxData( 10113.27f, -203.6833f, 0, 0, 0, 0 );
		__39->StartData = PhsxData( 10113.27f, -203.6833f, 0, 0, 0, 0 );
		__35->Floaters.push_back( __39 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __40 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__40->Name = std::wstring( L"cloud_cloud_layer1_1" );
		__40->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__40->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer1_1" ) );
		__40->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__40->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__40->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__40->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__40->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__40->MyQuad->Base = BasePoint( 1286.25f, 0, 0, 706.0881f, 14141.27f, -125.3017f );

		__40->uv_speed = Vector2( 0, 0 );
		__40->uv_offset = Vector2( 0, 0 );
		__40->Data = PhsxData( 14141.27f, -125.3017f, 0, 0, 0, 0 );
		__40->StartData = PhsxData( 14141.27f, -125.3017f, 0, 0, 0, 0 );
		__35->Floaters.push_back( __40 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __41 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__41->Name = std::wstring( L"cloud_cloud_layer1_2" );
		__41->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__41->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer1_2" ) );
		__41->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__41->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__41->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__41->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__41->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__41->MyQuad->Base = BasePoint( 1153.097f, 0, 0, 600.9785f, 17429.04f, -327.6263f );

		__41->uv_speed = Vector2( 0, 0 );
		__41->uv_offset = Vector2( 0, 0 );
		__41->Data = PhsxData( 17429.04f, -327.6263f, 0, 0, 0, 0 );
		__41->StartData = PhsxData( 17429.04f, -327.6263f, 0, 0, 0, 0 );
		__35->Floaters.push_back( __41 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __42 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__42->Name = std::wstring( L"cloud_cloud_layer1_3" );
		__42->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__42->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer1_3" ) );
		__42->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__42->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__42->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__42->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__42->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__42->MyQuad->Base = BasePoint( 1163.339f, 0, 0, 451.3339f, 20784.25f, -445.6487f );

		__42->uv_speed = Vector2( 0, 0 );
		__42->uv_offset = Vector2( 0, 0 );
		__42->Data = PhsxData( 20784.25f, -445.6487f, 0, 0, 0, 0 );
		__42->StartData = PhsxData( 20784.25f, -445.6487f, 0, 0, 0, 0 );
		__35->Floaters.push_back( __42 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __43 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__43->Name = std::wstring( L"cloud_cloud_layer1_4" );
		__43->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__43->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_cloud_layer1_4" ) );
		__43->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__43->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__43->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__43->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__43->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__43->MyQuad->Base = BasePoint( 978.9733f, 0, 0, 644.0235f, 24527.25f, 110.7433f );

		__43->uv_speed = Vector2( 0, 0 );
		__43->uv_offset = Vector2( 0, 0 );
		__43->Data = PhsxData( 24527.25f, 110.7433f, 0, 0, 0, 0 );
		__43->StartData = PhsxData( 24527.25f, 110.7433f, 0, 0, 0, 0 );
		__35->Floaters.push_back( __43 );

		__35->Parallax = 0.6f;
		__35->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __35 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __44 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__44->Name = std::wstring( L"castle_1" );
		__44->Foreground = false;
		__44->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __45 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__45->Name = std::wstring( L"cloud_castle_layer1" );
		__45->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__45->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cloud_castle_layer1" ) );
		__45->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__45->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__45->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__45->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__45->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__45->MyQuad->Base = BasePoint( 1231.156f, 0, 0, 2231.931f, 761.7891f, 296.3109f );

		__45->uv_speed = Vector2( 0, 0 );
		__45->uv_offset = Vector2( 0, 0 );
		__45->Data = PhsxData( 761.7891f, 296.3109f, 0, 0, 0, 0 );
		__45->StartData = PhsxData( 761.7891f, 296.3109f, 0, 0, 0, 0 );
		__44->Floaters.push_back( __45 );

		__44->Parallax = 0.666f;
		__44->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __44 );

		b->Light = 1;
		//b.BL = new Vector2(-4848.254f, -4500f);
		//b.TR = new Vector2(42470f, 3600f);
		b->BL = Vector2( -100000, -10000 );
		b->TR = Vector2( 100000, 10000 );
	}

	void Background::_code_Cave( const boost::shared_ptr<Background> &b )
	{
		b->GuidCounter = 0;
		b->MyGlobalIllumination = 1;
		b->AllowLava = true;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __1 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__1->Name = std::wstring( L"Backdrop" );
		__1->Foreground = false;
		__1->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __2 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__2->Name = std::wstring( L"cave_backdrop_p1_0" );
		__2->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__2->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__2->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__2->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_backdrop" ) );
		__2->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__2->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__2->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__2->MyQuad->Base = BasePoint( 10952.22f, 0, 0, 4632.95f, -14739.01f, 157.4063f );

		__2->uv_speed = Vector2( 0, 0 );
		__2->uv_offset = Vector2( 0, 0 );
		__2->Data = PhsxData( -14739.01f, 157.4063f, 0, 0, 0, 0 );
		__2->StartData = PhsxData( -14739.01f, 157.4063f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __2 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __3 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__3->Name = std::wstring( L"cave_backdrop_p2_0" );
		__3->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__3->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__3->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__3->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_backdrop_p2" ) );
		__3->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__3->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__3->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__3->MyQuad->Base = BasePoint( 10952.22f, 0, 0, 4632.95f, 7165.438f, 157.4063f );

		__3->uv_speed = Vector2( 0, 0 );
		__3->uv_offset = Vector2( 0, 0 );
		__3->Data = PhsxData( 7165.438f, 157.4063f, 0, 0, 0, 0 );
		__3->StartData = PhsxData( 7165.438f, 157.4063f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __3 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __4 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__4->Name = std::wstring( L"cave_backdrop_p1_1" );
		__4->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__4->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__4->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__4->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_backdrop" ) );
		__4->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__4->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__4->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__4->MyQuad->Base = BasePoint( 10952.22f, 0, 0, 4632.95f, 29069.88f, 157.4063f );

		__4->uv_speed = Vector2( 0, 0 );
		__4->uv_offset = Vector2( 0, 0 );
		__4->Data = PhsxData( 29069.88f, 157.4063f, 0, 0, 0, 0 );
		__4->StartData = PhsxData( 29069.88f, 157.4063f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __4 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __5 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__5->Name = std::wstring( L"cave_backdrop_p2_1" );
		__5->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__5->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__5->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__5->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_backdrop_p2" ) );
		__5->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__5->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__5->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__5->MyQuad->Base = BasePoint( 10952.22f, 0, 0, 4632.95f, 50974.33f, 157.4063f );

		__5->uv_speed = Vector2( 0, 0 );
		__5->uv_offset = Vector2( 0, 0 );
		__5->Data = PhsxData( 50974.33f, 157.4063f, 0, 0, 0, 0 );
		__5->StartData = PhsxData( 50974.33f, 157.4063f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __5 );

		__1->Parallax = 0.235f;
		__1->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __1 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __6 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__6->Name = std::wstring( L"Top_2" );
		__6->Foreground = false;
		__6->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __7 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__7->Name = std::wstring( L"cave_top_2_p1_0" );
		__7->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__7->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__7->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__7->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_top_2" ) );
		__7->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__7->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__7->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__7->MyQuad->Base = BasePoint( 7364.382f, 0, 0, 3116.508f, -9290.906f, 81.43799f );

		__7->uv_speed = Vector2( 0, 0 );
		__7->uv_offset = Vector2( 0, 0 );
		__7->Data = PhsxData( -9290.906f, 81.43799f, 0, 0, 0, 0 );
		__7->StartData = PhsxData( -9290.906f, 81.43799f, 0, 0, 0, 0 );
		__6->Floaters.push_back( __7 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __8 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__8->Name = std::wstring( L"cave_top_2_p2_0" );
		__8->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__8->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__8->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__8->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_top_2_p2" ) );
		__8->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__8->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__8->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__8->MyQuad->Base = BasePoint( 7364.382f, 0, 0, 3116.508f, 5437.859f, 81.43799f );

		__8->uv_speed = Vector2( 0, 0 );
		__8->uv_offset = Vector2( 0, 0 );
		__8->Data = PhsxData( 5437.859f, 81.43799f, 0, 0, 0, 0 );
		__8->StartData = PhsxData( 5437.859f, 81.43799f, 0, 0, 0, 0 );
		__6->Floaters.push_back( __8 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __9 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__9->Name = std::wstring( L"cave_top_2_p1_1" );
		__9->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__9->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__9->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__9->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_top_2" ) );
		__9->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__9->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__9->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__9->MyQuad->Base = BasePoint( 7364.382f, 0, 0, 3116.508f, 20166.62f, 81.43799f );

		__9->uv_speed = Vector2( 0, 0 );
		__9->uv_offset = Vector2( 0, 0 );
		__9->Data = PhsxData( 20166.62f, 81.43799f, 0, 0, 0, 0 );
		__9->StartData = PhsxData( 20166.62f, 81.43799f, 0, 0, 0, 0 );
		__6->Floaters.push_back( __9 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __10 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__10->Name = std::wstring( L"cave_top_2_p2_1" );
		__10->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__10->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__10->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__10->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_top_2_p2" ) );
		__10->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__10->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__10->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__10->MyQuad->Base = BasePoint( 7364.382f, 0, 0, 3116.508f, 34895.39f, 81.43799f );

		__10->uv_speed = Vector2( 0, 0 );
		__10->uv_offset = Vector2( 0, 0 );
		__10->Data = PhsxData( 34895.39f, 81.43799f, 0, 0, 0, 0 );
		__10->StartData = PhsxData( 34895.39f, 81.43799f, 0, 0, 0, 0 );
		__6->Floaters.push_back( __10 );

		__6->Parallax = 0.34f;
		__6->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __6 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __11 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__11->Name = std::wstring( L"Bottom_2" );
		__11->Foreground = false;
		__11->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __12 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__12->Name = std::wstring( L"cave_bottom_2_p1" );
		__12->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__12->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__12->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__12->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_bottom_2_p1" ) );
		__12->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__12->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__12->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__12->MyQuad->Base = BasePoint( 4499.655f, 0, 0, 1242.685f, -2566.051f, -1868.793f );

		__12->uv_speed = Vector2( 0, 0 );
		__12->uv_offset = Vector2( 0, 0 );
		__12->Data = PhsxData( -2566.051f, -1868.793f, 0, 0, 0, 0 );
		__12->StartData = PhsxData( -2566.051f, -1868.793f, 0, 0, 0, 0 );
		__11->Floaters.push_back( __12 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __13 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__13->Name = std::wstring( L"cave_bottom_2_p2" );
		__13->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__13->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__13->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__13->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_bottom_2_p2" ) );
		__13->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__13->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__13->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__13->MyQuad->Base = BasePoint( 4745.988f, 0, 0, 2350.854f, 8166.965f, -813.0869f );

		__13->uv_speed = Vector2( 0, 0 );
		__13->uv_offset = Vector2( 0, 0 );
		__13->Data = PhsxData( 8166.965f, -813.0869f, 0, 0, 0, 0 );
		__13->StartData = PhsxData( 8166.965f, -813.0869f, 0, 0, 0, 0 );
		__11->Floaters.push_back( __13 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __14 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__14->Name = std::wstring( L"cave_bottom_2_p1" );
		__14->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__14->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__14->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__14->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_bottom_2_p1" ) );
		__14->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__14->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__14->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__14->MyQuad->Base = BasePoint( 4499.655f, 0, 0, 1242.685f, 19126.95f, -1801.052f );

		__14->uv_speed = Vector2( 0, 0 );
		__14->uv_offset = Vector2( 0, 0 );
		__14->Data = PhsxData( 19126.95f, -1801.052f, 0, 0, 0, 0 );
		__14->StartData = PhsxData( 19126.95f, -1801.052f, 0, 0, 0, 0 );
		__11->Floaters.push_back( __14 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __15 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__15->Name = std::wstring( L"cave_bottom_2_p2" );
		__15->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__15->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__15->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__15->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_bottom_2_p2" ) );
		__15->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__15->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__15->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__15->MyQuad->Base = BasePoint( 4745.988f, 0, 0, 2350.854f, 29756.15f, -843.8784f );

		__15->uv_speed = Vector2( 0, 0 );
		__15->uv_offset = Vector2( 0, 0 );
		__15->Data = PhsxData( 29756.15f, -843.8784f, 0, 0, 0, 0 );
		__15->StartData = PhsxData( 29756.15f, -843.8784f, 0, 0, 0, 0 );
		__11->Floaters.push_back( __15 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __16 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__16->Name = std::wstring( L"cave_bottom_2_p1" );
		__16->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__16->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__16->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__16->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_bottom_2_p1" ) );
		__16->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__16->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__16->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__16->MyQuad->Base = BasePoint( 4499.655f, 0, 0, 1242.685f, 40610.07f, -1603.306f );

		__16->uv_speed = Vector2( 0, 0 );
		__16->uv_offset = Vector2( 0, 0 );
		__16->Data = PhsxData( 40610.07f, -1603.306f, 0, 0, 0, 0 );
		__16->StartData = PhsxData( 40610.07f, -1603.306f, 0, 0, 0, 0 );
		__11->Floaters.push_back( __16 );

		__11->Parallax = 0.35f;
		__11->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __11 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __17 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__17->Name = std::wstring( L"Bottom_1" );
		__17->Foreground = false;
		__17->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __18 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__18->Name = std::wstring( L"cave_bottom_1_p2_trim1" );
		__18->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__18->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__18->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__18->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_bottom_1_p2_trim1" ) );
		__18->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__18->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__18->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__18->MyQuad->Base = BasePoint( 1193.933f, 0, 0, 964.7405f, 2967.173f, -1099.445f );

		__18->uv_speed = Vector2( 0, 0 );
		__18->uv_offset = Vector2( 0, 0 );
		__18->Data = PhsxData( 2967.173f, -1099.445f, 0, 0, 0, 0 );
		__18->StartData = PhsxData( 2967.173f, -1099.445f, 0, 0, 0, 0 );
		__17->Floaters.push_back( __18 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __19 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__19->Name = std::wstring( L"cave_bottom_1_p2_trim2" );
		__19->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__19->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__19->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__19->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_bottom_1_p2_trim2" ) );
		__19->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__19->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__19->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__19->MyQuad->Base = BasePoint( 3174.72f, 0, 0, 1819.886f, 8139.643f, -271.6292f );

		__19->uv_speed = Vector2( 0, 0 );
		__19->uv_offset = Vector2( 0, 0 );
		__19->Data = PhsxData( 8139.643f, -271.6292f, 0, 0, 0, 0 );
		__19->StartData = PhsxData( 8139.643f, -271.6292f, 0, 0, 0, 0 );
		__17->Floaters.push_back( __19 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __20 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__20->Name = std::wstring( L"cave_bottom_1_trim1" );
		__20->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__20->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__20->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__20->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_bottom_1_trim1" ) );
		__20->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__20->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__20->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__20->MyQuad->Base = BasePoint( 798.1164f, 0, 0, 1067.863f, -7564.104f, -1065.574f );

		__20->uv_speed = Vector2( 0, 0 );
		__20->uv_offset = Vector2( 0, 0 );
		__20->Data = PhsxData( -7564.104f, -1065.574f, 0, 0, 0, 0 );
		__20->StartData = PhsxData( -7564.104f, -1065.574f, 0, 0, 0, 0 );
		__17->Floaters.push_back( __20 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __21 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__21->Name = std::wstring( L"cave_bottom_1_trim2" );
		__21->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__21->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__21->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__21->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_bottom_1_trim2" ) );
		__21->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__21->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__21->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__21->MyQuad->Base = BasePoint( 1169.693f, 0, 0, 558.5469f, -3669.087f, -1468.35f );

		__21->uv_speed = Vector2( 0, 0 );
		__21->uv_offset = Vector2( 0, 0 );
		__21->Data = PhsxData( -3669.087f, -1468.35f, 0, 0, 0, 0 );
		__21->StartData = PhsxData( -3669.087f, -1468.35f, 0, 0, 0, 0 );
		__17->Floaters.push_back( __21 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __22 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__22->Name = std::wstring( L"cave_bottom_1_p2_trim1" );
		__22->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__22->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__22->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__22->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_bottom_1_p2_trim1" ) );
		__22->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__22->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__22->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__22->MyQuad->Base = BasePoint( 1193.933f, 0, 0, 964.7405f, 23295.67f, -1171.816f );

		__22->uv_speed = Vector2( 0, 0 );
		__22->uv_offset = Vector2( 0, 0 );
		__22->Data = PhsxData( 23295.67f, -1171.816f, 0, 0, 0, 0 );
		__22->StartData = PhsxData( 23295.67f, -1171.816f, 0, 0, 0, 0 );
		__17->Floaters.push_back( __22 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __23 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__23->Name = std::wstring( L"cave_bottom_1_p2_trim2" );
		__23->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__23->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__23->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__23->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_bottom_1_p2_trim2" ) );
		__23->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__23->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__23->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__23->MyQuad->Base = BasePoint( 3174.72f, 0, 0, 1819.886f, 28381.08f, -351.9041f );

		__23->uv_speed = Vector2( 0, 0 );
		__23->uv_offset = Vector2( 0, 0 );
		__23->Data = PhsxData( 28381.08f, -351.9041f, 0, 0, 0, 0 );
		__23->StartData = PhsxData( 28381.08f, -351.9041f, 0, 0, 0, 0 );
		__17->Floaters.push_back( __23 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __24 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__24->Name = std::wstring( L"cave_bottom_1_trim1" );
		__24->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__24->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__24->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__24->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_bottom_1_trim1" ) );
		__24->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__24->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__24->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__24->MyQuad->Base = BasePoint( 798.1164f, 0, 0, 1067.863f, 12685.62f, -1074.208f );

		__24->uv_speed = Vector2( 0, 0 );
		__24->uv_offset = Vector2( 0, 0 );
		__24->Data = PhsxData( 12685.62f, -1074.208f, 0, 0, 0, 0 );
		__24->StartData = PhsxData( 12685.62f, -1074.208f, 0, 0, 0, 0 );
		__17->Floaters.push_back( __24 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __25 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__25->Name = std::wstring( L"cave_bottom_1_trim2" );
		__25->MyQuad->Quad_Renamed.v0.Vertex = MyOwnVertexFormat( Vector2( 15360.32f, -998.902f ), Vector2( 0, 0 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__25->MyQuad->Quad_Renamed.v0.Pos = Vector2( -1.1347f, 0.9736457f );

		__25->MyQuad->Quad_Renamed.v1.Vertex = MyOwnVertexFormat( Vector2( 17699.71f, -998.902f ), Vector2( 1, 0 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__25->MyQuad->Quad_Renamed.v1.Pos = Vector2( 0.8653001f, 0.9736457f );

		__25->MyQuad->Quad_Renamed.v2.Vertex = MyOwnVertexFormat( Vector2( 15360.32f, -2115.996f ), Vector2( 0, 1 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__25->MyQuad->Quad_Renamed.v2.Pos = Vector2( -1.1347f, -1.026354f );

		__25->MyQuad->Quad_Renamed.v3.Vertex = MyOwnVertexFormat( Vector2( 17699.71f, -2115.996f ), Vector2( 1, 1 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__25->MyQuad->Quad_Renamed.v3.Pos = Vector2( 0.8653001f, -1.026354f );

		__25->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__25->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__25->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__25->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_bottom_1_trim2" ) );
		__25->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__25->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__25->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__25->MyQuad->Base = BasePoint( 1169.693f, 0, 0, 558.5469f, 16687.57f, -1542.729f );

		__25->uv_speed = Vector2( 0, 0 );
		__25->uv_offset = Vector2( 0, 0 );
		__25->Data = PhsxData( 16687.57f, -1542.729f, 0, 0, 0, 0 );
		__25->StartData = PhsxData( 16687.57f, -1542.729f, 0, 0, 0, 0 );
		__17->Floaters.push_back( __25 );

		__17->Parallax = 0.5f;
		__17->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __17 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __26 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__26->Name = std::wstring( L"Top_1" );
		__26->Foreground = false;
		__26->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __27 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__27->Name = std::wstring( L"cave_top_1_p1_0" );
		__27->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__27->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__27->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__27->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_top_1" ) );
		__27->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__27->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__27->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__27->MyQuad->Base = BasePoint( 4329.43f, 0, 0, 1832.563f, -2258.242f, 30.32861f );

		__27->uv_speed = Vector2( 0, 0 );
		__27->uv_offset = Vector2( 0, 0 );
		__27->Data = PhsxData( -2258.242f, 30.32861f, 0, 0, 0, 0 );
		__27->StartData = PhsxData( -2258.242f, 30.32861f, 0, 0, 0, 0 );
		__26->Floaters.push_back( __27 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __28 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__28->Name = std::wstring( L"cave_top_1_p2_0" );
		__28->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__28->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__28->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__28->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_top_1_p2" ) );
		__28->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__28->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__28->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__28->MyQuad->Base = BasePoint( 4329.43f, 0, 0, 1832.563f, 6400.621f, 30.32861f );

		__28->uv_speed = Vector2( 0, 0 );
		__28->uv_offset = Vector2( 0, 0 );
		__28->Data = PhsxData( 6400.621f, 30.32861f, 0, 0, 0, 0 );
		__28->StartData = PhsxData( 6400.621f, 30.32861f, 0, 0, 0, 0 );
		__26->Floaters.push_back( __28 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __29 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__29->Name = std::wstring( L"cave_top_1_p1_1" );
		__29->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__29->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__29->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__29->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_top_1" ) );
		__29->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__29->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__29->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__29->MyQuad->Base = BasePoint( 4329.43f, 0, 0, 1832.563f, 15059.48f, 30.32861f );

		__29->uv_speed = Vector2( 0, 0 );
		__29->uv_offset = Vector2( 0, 0 );
		__29->Data = PhsxData( 15059.48f, 30.32861f, 0, 0, 0, 0 );
		__29->StartData = PhsxData( 15059.48f, 30.32861f, 0, 0, 0, 0 );
		__26->Floaters.push_back( __29 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __30 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__30->Name = std::wstring( L"cave_top_1_p2_1" );
		__30->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__30->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__30->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__30->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_top_1_p2" ) );
		__30->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__30->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__30->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__30->MyQuad->Base = BasePoint( 4329.43f, 0, 0, 1832.563f, 23718.34f, 30.32861f );

		__30->uv_speed = Vector2( 0, 0 );
		__30->uv_offset = Vector2( 0, 0 );
		__30->Data = PhsxData( 23718.34f, 30.32861f, 0, 0, 0, 0 );
		__30->StartData = PhsxData( 23718.34f, 30.32861f, 0, 0, 0, 0 );
		__26->Floaters.push_back( __30 );

		__26->Parallax = 0.6f;
		__26->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __26 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __31 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__31->Name = std::wstring( L"Lights" );
		__31->Foreground = false;
		__31->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __32 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__32->Name = std::wstring( L"cave_lightshafts_p1_0" );
		__32->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__32->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__32->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__32->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_lightshafts" ) );
		__32->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__32->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__32->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__32->MyQuad->Base = BasePoint( 3582.637f, 0, 0, 1516.46f, 2142.867f, -1.561279f );

		__32->uv_speed = Vector2( 0, 0 );
		__32->uv_offset = Vector2( 0, 0 );
		__32->Data = PhsxData( 2142.867f, -1.561279f, 0, 0, 0, 0 );
		__32->StartData = PhsxData( 2142.867f, -1.561279f, 0, 0, 0, 0 );
		__31->Floaters.push_back( __32 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __33 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__33->Name = std::wstring( L"cave_lightshafts_p2_0" );
		__33->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__33->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__33->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__33->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_lightshafts_p2" ) );
		__33->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__33->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__33->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__33->MyQuad->Base = BasePoint( 3582.637f, 0, 0, 1516.46f, 9308.145f, -1.561279f );

		__33->uv_speed = Vector2( 0, 0 );
		__33->uv_offset = Vector2( 0, 0 );
		__33->Data = PhsxData( 9308.145f, -1.561279f, 0, 0, 0, 0 );
		__33->StartData = PhsxData( 9308.145f, -1.561279f, 0, 0, 0, 0 );
		__31->Floaters.push_back( __33 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __34 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__34->Name = std::wstring( L"cave_lightshafts_p1_1" );
		__34->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__34->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__34->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__34->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_lightshafts" ) );
		__34->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__34->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__34->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__34->MyQuad->Base = BasePoint( 3582.637f, 0, 0, 1516.46f, 16473.42f, -1.561279f );

		__34->uv_speed = Vector2( 0, 0 );
		__34->uv_offset = Vector2( 0, 0 );
		__34->Data = PhsxData( 16473.42f, -1.561279f, 0, 0, 0, 0 );
		__34->StartData = PhsxData( 16473.42f, -1.561279f, 0, 0, 0, 0 );
		__31->Floaters.push_back( __34 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __35 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__35->Name = std::wstring( L"cave_lightshafts_p2_1" );
		__35->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__35->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__35->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__35->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"cave_lightshafts_p2" ) );
		__35->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__35->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__35->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__35->MyQuad->Base = BasePoint( 3582.637f, 0, 0, 1516.46f, 23638.69f, -1.561279f );

		__35->uv_speed = Vector2( 0, 0 );
		__35->uv_offset = Vector2( 0, 0 );
		__35->Data = PhsxData( 23638.69f, -1.561279f, 0, 0, 0, 0 );
		__35->StartData = PhsxData( 23638.69f, -1.561279f, 0, 0, 0, 0 );
		__31->Floaters.push_back( __35 );

		__31->Parallax = 0.68f;
		__31->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __31 );

		b->Light = 1;
		//b.BL = new Vector2(-4670f, -4500f);
		//b.TR = new Vector2(42470f, 2071.545f);
		b->BL = Vector2( -100000, -10000 );
		b->TR = Vector2( 100000, 10000 );
	}

	void Background::_code_Hills( const boost::shared_ptr<Background> &b )
	{
		b->GuidCounter = 0;
		b->MyGlobalIllumination = 1;
		b->AllowLava = true;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __1 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__1->Name = std::wstring( L"Backdrop" );
		__1->Foreground = false;
		__1->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __2 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__2->Name = std::wstring( L"hills_backdrop_p1_0" );
		__2->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__2->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__2->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__2->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_backdrop" ) );
		__2->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__2->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__2->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__2->MyQuad->Base = BasePoint( 81277.7f, 0, 0, 34106.41f, -4469.054f, 784.0586f );

		__2->uv_speed = Vector2( 0, 0 );
		__2->uv_offset = Vector2( 0, 0 );
		__2->Data = PhsxData( -4469.054f, 784.0586f, 0, 0, 0, 0 );
		__2->StartData = PhsxData( -4469.054f, 784.0586f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __2 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __3 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__3->Name = std::wstring( L"hills_backdrop_p2_0" );
		__3->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__3->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__3->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__3->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_backdrop_p2" ) );
		__3->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__3->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__3->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__3->MyQuad->Base = BasePoint( 81277.7f, 0, 0, 34106.41f, 158086.3f, 784.0586f );

		__3->uv_speed = Vector2( 0, 0 );
		__3->uv_offset = Vector2( 0, 0 );
		__3->Data = PhsxData( 158086.3f, 784.0586f, 0, 0, 0, 0 );
		__3->StartData = PhsxData( 158086.3f, 784.0586f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __3 );

		__1->Parallax = 0.03f;
		__1->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __1 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __4 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__4->Name = std::wstring( L"Back_Castles" );
		__4->Foreground = false;
		__4->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __5 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__5->Name = std::wstring( L"hills_backcastles_trim" );
		__5->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__5->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__5->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__5->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_backcastles_trim" ) );
		__5->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__5->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__5->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__5->MyQuad->Base = BasePoint( 19649.94f, 0, 0, 6075.512f, 3557.881f, 4444.444f );

		__5->uv_speed = Vector2( 0, 0 );
		__5->uv_offset = Vector2( 0, 0 );
		__5->Data = PhsxData( 3557.881f, 4444.444f, 0, 0, 0, 0 );
		__5->StartData = PhsxData( 3557.881f, 4444.444f, 0, 0, 0, 0 );
		__4->Floaters.push_back( __5 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __6 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__6->Name = std::wstring( L"hills_backcastles_p2_trim" );
		__6->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__6->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__6->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__6->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_backcastles_p2_trim" ) );
		__6->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__6->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__6->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__6->MyQuad->Base = BasePoint( 21693.85f, 0, 0, 6280.27f, 44884.28f, 4316.639f );

		__6->uv_speed = Vector2( 0, 0 );
		__6->uv_offset = Vector2( 0, 0 );
		__6->Data = PhsxData( 44884.28f, 4316.639f, 0, 0, 0, 0 );
		__6->StartData = PhsxData( 44884.28f, 4316.639f, 0, 0, 0, 0 );
		__4->Floaters.push_back( __6 );

		__4->Parallax = 0.1f;
		__4->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __4 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __7 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__7->Name = std::wstring( L"Hill" );
		__7->Foreground = false;
		__7->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __8 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__8->Name = std::wstring( L"hills_backhills_p1_0" );
		__8->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__8->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__8->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__8->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_backhills" ) );
		__8->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__8->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__8->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__8->MyQuad->Base = BasePoint( 10593.01f, 0, 0, 4445.094f, 2926.976f, 102.2695f );

		__8->uv_speed = Vector2( 0, 0 );
		__8->uv_offset = Vector2( 0, 0 );
		__8->Data = PhsxData( 2926.976f, 102.2695f, 0, 0, 0, 0 );
		__8->StartData = PhsxData( 2926.976f, 102.2695f, 0, 0, 0, 0 );
		__7->Floaters.push_back( __8 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __9 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__9->Name = std::wstring( L"hills_backhills_p2_0" );
		__9->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__9->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__9->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__9->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_backhills_p2" ) );
		__9->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__9->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__9->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__9->MyQuad->Base = BasePoint( 10593.01f, 0, 0, 4445.094f, 24113, 102.2695f );

		__9->uv_speed = Vector2( 0, 0 );
		__9->uv_offset = Vector2( 0, 0 );
		__9->Data = PhsxData( 24113, 102.2695f, 0, 0, 0, 0 );
		__9->StartData = PhsxData( 24113, 102.2695f, 0, 0, 0, 0 );
		__7->Floaters.push_back( __9 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __10 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__10->Name = std::wstring( L"hills_backhills_p1_0" );
		__10->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__10->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__10->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__10->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_backhills" ) );
		__10->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__10->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__10->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__10->MyQuad->Base = BasePoint( 10593.01f, 0, 0, 4445.094f, 39921.59f, 451.0566f );

		__10->uv_speed = Vector2( 0, 0 );
		__10->uv_offset = Vector2( 0, 0 );
		__10->Data = PhsxData( 39921.59f, 451.0566f, 0, 0, 0, 0 );
		__10->StartData = PhsxData( 39921.59f, 451.0566f, 0, 0, 0, 0 );
		__7->Floaters.push_back( __10 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __11 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__11->Name = std::wstring( L"hills_backhills_p2_0" );
		__11->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__11->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__11->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__11->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_backhills_p2" ) );
		__11->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__11->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__11->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__11->MyQuad->Base = BasePoint( 10593.01f, 0, 0, 4445.094f, 61107.63f, 451.0566f );

		__11->uv_speed = Vector2( 0, 0 );
		__11->uv_offset = Vector2( 0, 0 );
		__11->Data = PhsxData( 61107.63f, 451.0566f, 0, 0, 0, 0 );
		__11->StartData = PhsxData( 61107.63f, 451.0566f, 0, 0, 0, 0 );
		__7->Floaters.push_back( __11 );

		__7->Parallax = 0.23f;
		__7->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __7 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __12 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__12->Name = std::wstring( L"Hill" );
		__12->Foreground = false;
		__12->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __13 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__13->Name = std::wstring( L"hills_backhills2_trim" );
		__13->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__13->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__13->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__13->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_backhills2_trim" ) );
		__13->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__13->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__13->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__13->MyQuad->Base = BasePoint( 5887, 0, 0, 1970.189f, 4186.129f, -1231.915f );

		__13->uv_speed = Vector2( 0, 0 );
		__13->uv_offset = Vector2( 0, 0 );
		__13->Data = PhsxData( 4186.129f, -1231.915f, 0, 0, 0, 0 );
		__13->StartData = PhsxData( 4186.129f, -1231.915f, 0, 0, 0, 0 );
		__12->Floaters.push_back( __13 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __14 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__14->Name = std::wstring( L"hills_backhills2_p2_trim" );
		__14->MyQuad->Quad_Renamed.v0.Vertex = MyOwnVertexFormat( Vector2( 10065.5f, -192.9017f ), Vector2( 0, 0 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__14->MyQuad->Quad_Renamed.v0.Pos = Vector2( -1.000975f, 0.9990253f );

		__14->MyQuad->Quad_Renamed.v1.Vertex = MyOwnVertexFormat( Vector2( 25706.37f, -192.9017f ), Vector2( 1, 0 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__14->MyQuad->Quad_Renamed.v1.Pos = Vector2( 0.999025f, 0.9990253f );

		__14->MyQuad->Quad_Renamed.v2.Vertex = MyOwnVertexFormat( Vector2( 10065.5f, -3209.26f ), Vector2( 0, 1 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__14->MyQuad->Quad_Renamed.v2.Pos = Vector2( -1.000975f, -1.000975f );

		__14->MyQuad->Quad_Renamed.v3.Vertex = MyOwnVertexFormat( Vector2( 25706.37f, -3209.26f ), Vector2( 1, 1 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__14->MyQuad->Quad_Renamed.v3.Pos = Vector2( 0.999025f, -1.000975f );

		__14->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__14->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__14->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__14->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_backhills2_p2_trim" ) );
		__14->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__14->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__14->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__14->MyQuad->Base = BasePoint( 7820.432f, 0, 0, 1508.179f, 17893.56f, -1699.611f );

		__14->uv_speed = Vector2( 0, 0 );
		__14->uv_offset = Vector2( 0, 0 );
		__14->Data = PhsxData( 17893.56f, -1699.611f, 0, 0, 0, 0 );
		__14->StartData = PhsxData( 17893.56f, -1699.611f, 0, 0, 0, 0 );
		__12->Floaters.push_back( __14 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __15 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__15->Name = std::wstring( L"hills_backhills2_trim" );
		__15->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__15->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__15->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__15->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_backhills2_trim" ) );
		__15->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__15->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__15->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__15->MyQuad->Base = BasePoint( 5887, 0, 0, 1970.189f, 32150.93f, -1535.743f );

		__15->uv_speed = Vector2( 0, 0 );
		__15->uv_offset = Vector2( 0, 0 );
		__15->Data = PhsxData( 32150.93f, -1535.743f, 0, 0, 0, 0 );
		__15->StartData = PhsxData( 32150.93f, -1535.743f, 0, 0, 0, 0 );
		__12->Floaters.push_back( __15 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __16 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__16->Name = std::wstring( L"hills_backhills2_p2_trim" );
		__16->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__16->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__16->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__16->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_backhills2_p2_trim" ) );
		__16->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__16->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__16->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__16->MyQuad->Base = BasePoint( 7820.432f, 0, 0, 1508.179f, 45858.36f, -1998.595f );

		__16->uv_speed = Vector2( 0, 0 );
		__16->uv_offset = Vector2( 0, 0 );
		__16->Data = PhsxData( 45858.36f, -1998.595f, 0, 0, 0, 0 );
		__16->StartData = PhsxData( 45858.36f, -1998.595f, 0, 0, 0, 0 );
		__12->Floaters.push_back( __16 );

		__12->Parallax = 0.31f;
		__12->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __12 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __17 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__17->Name = std::wstring( L"Clouds" );
		__17->Foreground = false;
		__17->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __18 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__18->Name = std::wstring( L"hills_clouds" );
		__18->MyQuad->Quad_Renamed.v0.Vertex = MyOwnVertexFormat( Vector2( -4171.699f, 2314.271f ), Vector2( 0.7512081f, 0 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__18->MyQuad->Quad_Renamed.v0.Pos = Vector2( -1, 1 );

		__18->MyQuad->Quad_Renamed.v1.Vertex = MyOwnVertexFormat( Vector2( 40964.18f, 2314.271f ), Vector2( 3.749899f, 0 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__18->MyQuad->Quad_Renamed.v1.Pos = Vector2( 1, 1 );

		__18->MyQuad->Quad_Renamed.v2.Vertex = MyOwnVertexFormat( Vector2( -4171.699f, -1292.736f ), Vector2( 0.7512081f, 1 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__18->MyQuad->Quad_Renamed.v2.Pos = Vector2( -1, -1 );

		__18->MyQuad->Quad_Renamed.v3.Vertex = MyOwnVertexFormat( Vector2( 40964.18f, -1292.736f ), Vector2( 3.749899f, 1 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__18->MyQuad->Quad_Renamed.v3.Pos = Vector2( 1, -1 );

		__18->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__18->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__18->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__18->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_clouds" ) );
		__18->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__18->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__18->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__18->MyQuad->Base = BasePoint( 22567.94f, 0, 0, 1803.504f, 18396.24f, 510.7676f );

		__18->uv_speed = Vector2( 0.0008f, 0 );
		__18->uv_offset = Vector2( 0, 0 );
		__18->Data = PhsxData( 18396.24f, 510.7676f, 0, 0, 0, 0 );
		__18->StartData = PhsxData( 18396.24f, 510.7676f, 0, 0, 0, 0 );
		__17->Floaters.push_back( __18 );

		__17->Parallax = 0.4f;
		__17->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __17 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __19 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__19->Name = std::wstring( L"Hills" );
		__19->Foreground = false;
		__19->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __20 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__20->Name = std::wstring( L"hills_hill1" );
		__20->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__20->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__20->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__20->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_hill1" ) );
		__20->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__20->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__20->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__20->MyQuad->Base = BasePoint( 5711.815f, 0, 0, 1410.282f, 8635.98f, -926.418f );

		__20->uv_speed = Vector2( 0, 0 );
		__20->uv_offset = Vector2( 0, 0 );
		__20->Data = PhsxData( 8635.98f, -926.418f, 0, 0, 0, 0 );
		__20->StartData = PhsxData( 8635.98f, -926.418f, 0, 0, 0, 0 );
		__19->Floaters.push_back( __20 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __21 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__21->Name = std::wstring( L"hills_hillandtree" );
		__21->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__21->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__21->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__21->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_hillandtree" ) );
		__21->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__21->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__21->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__21->MyQuad->Base = BasePoint( 5250.666f, 0, 0, 1960.848f, 34.27734f, -34.0918f );

		__21->uv_speed = Vector2( 0, 0 );
		__21->uv_offset = Vector2( 0, 0 );
		__21->Data = PhsxData( 34.27734f, -34.0918f, 0, 0, 0, 0 );
		__21->StartData = PhsxData( 34.27734f, -34.0918f, 0, 0, 0, 0 );
		__19->Floaters.push_back( __21 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __22 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__22->Name = std::wstring( L"hills_hillandtree" );
		__22->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__22->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__22->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__22->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_hillandtree" ) );
		__22->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__22->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__22->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__22->MyQuad->Base = BasePoint( 5250.666f, 0, 0, 1960.848f, 17604.08f, -34.0918f );

		__22->uv_speed = Vector2( 0, 0 );
		__22->uv_offset = Vector2( 0, 0 );
		__22->Data = PhsxData( 17604.08f, -34.0918f, 0, 0, 0, 0 );
		__22->StartData = PhsxData( 17604.08f, -34.0918f, 0, 0, 0, 0 );
		__19->Floaters.push_back( __22 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __23 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__23->Name = std::wstring( L"hills_hill2" );
		__23->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__23->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__23->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__23->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_hill2" ) );
		__23->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__23->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__23->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__23->MyQuad->Base = BasePoint( 4082.421f, 0, 0, 1469.273f, 10419.8f, -1173.33f );

		__23->uv_speed = Vector2( 0, 0 );
		__23->uv_offset = Vector2( 0, 0 );
		__23->Data = PhsxData( 10419.8f, -1173.33f, 0, 0, 0, 0 );
		__23->StartData = PhsxData( 10419.8f, -1173.33f, 0, 0, 0, 0 );
		__19->Floaters.push_back( __23 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __24 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__24->Name = std::wstring( L"hills_hill1" );
		__24->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__24->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__24->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__24->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_hill1" ) );
		__24->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__24->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__24->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__24->MyQuad->Base = BasePoint( 5711.815f, 0, 0, 1410.282f, 27956.91f, -438.7754f );

		__24->uv_speed = Vector2( 0, 0 );
		__24->uv_offset = Vector2( 0, 0 );
		__24->Data = PhsxData( 27956.91f, -438.7754f, 0, 0, 0, 0 );
		__24->StartData = PhsxData( 27956.91f, -438.7754f, 0, 0, 0, 0 );
		__19->Floaters.push_back( __24 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __25 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__25->Name = std::wstring( L"hills_hillandtree" );
		__25->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__25->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__25->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__25->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_hillandtree" ) );
		__25->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__25->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__25->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__25->MyQuad->Base = BasePoint( 5250.666f, 0, 0, 1960.848f, 34432.56f, -336.752f );

		__25->uv_speed = Vector2( 0, 0 );
		__25->uv_offset = Vector2( 0, 0 );
		__25->Data = PhsxData( 34432.56f, -336.752f, 0, 0, 0, 0 );
		__25->StartData = PhsxData( 34432.56f, -336.752f, 0, 0, 0, 0 );
		__19->Floaters.push_back( __25 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __26 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__26->Name = std::wstring( L"hills_hill1" );
		__26->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__26->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__26->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__26->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_hill1" ) );
		__26->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__26->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__26->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__26->MyQuad->Base = BasePoint( 5711.815f, 0, 0, 1410.282f, 43620.78f, -565.0293f );

		__26->uv_speed = Vector2( 0, 0 );
		__26->uv_offset = Vector2( 0, 0 );
		__26->Data = PhsxData( 43620.78f, -565.0293f, 0, 0, 0, 0 );
		__26->StartData = PhsxData( 43620.78f, -565.0293f, 0, 0, 0, 0 );
		__19->Floaters.push_back( __26 );

		__19->Parallax = 0.55f;
		__19->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __19 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __27 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__27->Name = std::wstring( L"Plants" );
		__27->Foreground = false;
		__27->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __28 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__28->Name = std::wstring( L"hills_plants_1" );
		__28->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__28->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__28->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__28->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_1" ) );
		__28->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__28->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__28->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__28->MyQuad->Base = BasePoint( 646.1251f, 0, 0, 486.9349f, -8483.381f, -959.5684f );

		__28->uv_speed = Vector2( 0, 0 );
		__28->uv_offset = Vector2( 0, 0 );
		__28->Data = PhsxData( -8483.381f, -959.5684f, 0, 0, 0, 0 );
		__28->StartData = PhsxData( -8483.381f, -959.5684f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __28 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __29 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__29->Name = std::wstring( L"hills_plants_2" );
		__29->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__29->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__29->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__29->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_2" ) );
		__29->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__29->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__29->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__29->MyQuad->Base = BasePoint( 974.2943f, 0, 0, 843.0762f, -6522.574f, -951.364f );

		__29->uv_speed = Vector2( 0, 0 );
		__29->uv_offset = Vector2( 0, 0 );
		__29->Data = PhsxData( -6522.574f, -951.364f, 0, 0, 0, 0 );
		__29->StartData = PhsxData( -6522.574f, -951.364f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __29 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __30 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__30->Name = std::wstring( L"hills_plants_3" );
		__30->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__30->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__30->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__30->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_3" ) );
		__30->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__30->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__30->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__30->MyQuad->Base = BasePoint( 892.2518f, 0, 0, 804.9318f, -4241.8f, -1058.019f );

		__30->uv_speed = Vector2( 0, 0 );
		__30->uv_offset = Vector2( 0, 0 );
		__30->Data = PhsxData( -4241.8f, -1058.019f, 0, 0, 0, 0 );
		__30->StartData = PhsxData( -4241.8f, -1058.019f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __30 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __31 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__31->Name = std::wstring( L"hills_plants_4" );
		__31->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__31->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__31->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__31->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_4" ) );
		__31->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__31->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__31->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__31->MyQuad->Base = BasePoint( 957.8854f, 0, 0, 524.0001f, -2026.664f, -1213.899f );

		__31->uv_speed = Vector2( 0, 0 );
		__31->uv_offset = Vector2( 0, 0 );
		__31->Data = PhsxData( -2026.664f, -1213.899f, 0, 0, 0, 0 );
		__31->StartData = PhsxData( -2026.664f, -1213.899f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __31 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __32 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__32->Name = std::wstring( L"hills_plants_5" );
		__32->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__32->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__32->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__32->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_5" ) );
		__32->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__32->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__32->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__32->MyQuad->Base = BasePoint( 695.9648f, 0, 0, 565.1686f, -4.105469f, -1058.24f );

		__32->uv_speed = Vector2( 0, 0 );
		__32->uv_offset = Vector2( 0, 0 );
		__32->Data = PhsxData( -4.105469f, -1058.24f, 0, 0, 0, 0 );
		__32->StartData = PhsxData( -4.105469f, -1058.24f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __32 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __33 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__33->Name = std::wstring( L"hills_plants_6" );
		__33->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__33->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__33->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__33->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_6" ) );
		__33->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__33->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__33->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__33->MyQuad->Base = BasePoint( 1266.809f, 0, 0, 1009.208f, 2359.654f, -917.8555f );

		__33->uv_speed = Vector2( 0, 0 );
		__33->uv_offset = Vector2( 0, 0 );
		__33->Data = PhsxData( 2359.654f, -917.8555f, 0, 0, 0, 0 );
		__33->StartData = PhsxData( 2359.654f, -917.8555f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __33 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __34 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__34->Name = std::wstring( L"hills_plants_1" );
		__34->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__34->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__34->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__34->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_1" ) );
		__34->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__34->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__34->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__34->MyQuad->Base = BasePoint( 646.1251f, 0, 0, 486.9349f, 4476.271f, -1029.628f );

		__34->uv_speed = Vector2( 0, 0 );
		__34->uv_offset = Vector2( 0, 0 );
		__34->Data = PhsxData( 4476.271f, -1029.628f, 0, 0, 0, 0 );
		__34->StartData = PhsxData( 4476.271f, -1029.628f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __34 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __35 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__35->Name = std::wstring( L"hills_plants_2" );
		__35->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__35->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__35->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__35->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_2" ) );
		__35->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__35->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__35->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__35->MyQuad->Base = BasePoint( 974.2943f, 0, 0, 843.0762f, 6329.44f, -981.4927f );

		__35->uv_speed = Vector2( 0, 0 );
		__35->uv_offset = Vector2( 0, 0 );
		__35->Data = PhsxData( 6329.44f, -981.4927f, 0, 0, 0, 0 );
		__35->StartData = PhsxData( 6329.44f, -981.4927f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __35 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __36 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__36->Name = std::wstring( L"hills_plants_3" );
		__36->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__36->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__36->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__36->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_3" ) );
		__36->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__36->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__36->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__36->MyQuad->Base = BasePoint( 892.2518f, 0, 0, 804.9318f, 8591.752f, -933.3588f );

		__36->uv_speed = Vector2( 0, 0 );
		__36->uv_offset = Vector2( 0, 0 );
		__36->Data = PhsxData( 8591.752f, -933.3588f, 0, 0, 0, 0 );
		__36->StartData = PhsxData( 8591.752f, -933.3588f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __36 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __37 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__37->Name = std::wstring( L"hills_plants_4" );
		__37->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__37->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__37->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__37->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_4" ) );
		__37->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__37->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__37->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__37->MyQuad->Base = BasePoint( 957.8854f, 0, 0, 524.0001f, 10830, -1125.896f );

		__37->uv_speed = Vector2( 0, 0 );
		__37->uv_offset = Vector2( 0, 0 );
		__37->Data = PhsxData( 10830, -1125.896f, 0, 0, 0, 0 );
		__37->StartData = PhsxData( 10830, -1125.896f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __37 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __38 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__38->Name = std::wstring( L"hills_plants_5" );
		__38->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__38->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__38->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__38->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_5" ) );
		__38->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__38->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__38->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__38->MyQuad->Base = BasePoint( 695.9648f, 0, 0, 565.1686f, 13020.1f, -1053.695f );

		__38->uv_speed = Vector2( 0, 0 );
		__38->uv_offset = Vector2( 0, 0 );
		__38->Data = PhsxData( 13020.1f, -1053.695f, 0, 0, 0, 0 );
		__38->StartData = PhsxData( 13020.1f, -1053.695f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __38 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __39 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__39->Name = std::wstring( L"hills_plants_6" );
		__39->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__39->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__39->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__39->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_6" ) );
		__39->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__39->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__39->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__39->MyQuad->Base = BasePoint( 1266.809f, 0, 0, 1009.208f, 15234.28f, -933.358f );

		__39->uv_speed = Vector2( 0, 0 );
		__39->uv_offset = Vector2( 0, 0 );
		__39->Data = PhsxData( 15234.28f, -933.358f, 0, 0, 0, 0 );
		__39->StartData = PhsxData( 15234.28f, -933.358f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __39 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __40 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__40->Name = std::wstring( L"hills_plants_1" );
		__40->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__40->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__40->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__40->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_1" ) );
		__40->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__40->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__40->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__40->MyQuad->Base = BasePoint( 646.1251f, 0, 0, 486.9349f, 17219.33f, -986.3066f );

		__40->uv_speed = Vector2( 0, 0 );
		__40->uv_offset = Vector2( 0, 0 );
		__40->Data = PhsxData( 17219.33f, -986.3066f, 0, 0, 0, 0 );
		__40->StartData = PhsxData( 17219.33f, -986.3066f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __40 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __41 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__41->Name = std::wstring( L"hills_plants_2" );
		__41->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__41->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__41->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__41->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_2" ) );
		__41->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__41->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__41->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__41->MyQuad->Base = BasePoint( 974.2943f, 0, 0, 843.0762f, 19203.91f, -1006.042f );

		__41->uv_speed = Vector2( 0, 0 );
		__41->uv_offset = Vector2( 0, 0 );
		__41->Data = PhsxData( 19203.91f, -1006.042f, 0, 0, 0, 0 );
		__41->StartData = PhsxData( 19203.91f, -1006.042f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __41 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __42 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__42->Name = std::wstring( L"hills_plants_3" );
		__42->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__42->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__42->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__42->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_3" ) );
		__42->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__42->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__42->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__42->MyQuad->Base = BasePoint( 892.2518f, 0, 0, 804.9318f, 21566.81f, -1132.153f );

		__42->uv_speed = Vector2( 0, 0 );
		__42->uv_offset = Vector2( 0, 0 );
		__42->Data = PhsxData( 21566.81f, -1132.153f, 0, 0, 0, 0 );
		__42->StartData = PhsxData( 21566.81f, -1132.153f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __42 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __43 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__43->Name = std::wstring( L"hills_plants_4" );
		__43->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__43->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__43->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__43->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_4" ) );
		__43->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__43->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__43->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__43->MyQuad->Base = BasePoint( 957.8854f, 0, 0, 524.0001f, 23854.63f, -1173.068f );

		__43->uv_speed = Vector2( 0, 0 );
		__43->uv_offset = Vector2( 0, 0 );
		__43->Data = PhsxData( 23854.63f, -1173.068f, 0, 0, 0, 0 );
		__43->StartData = PhsxData( 23854.63f, -1173.068f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __43 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __44 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__44->Name = std::wstring( L"hills_plants_5" );
		__44->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__44->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__44->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__44->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_5" ) );
		__44->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__44->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__44->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__44->MyQuad->Base = BasePoint( 695.9648f, 0, 0, 565.1686f, 25828.14f, -1124.934f );

		__44->uv_speed = Vector2( 0, 0 );
		__44->uv_offset = Vector2( 0, 0 );
		__44->Data = PhsxData( 25828.14f, -1124.934f, 0, 0, 0, 0 );
		__44->StartData = PhsxData( 25828.14f, -1124.934f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __44 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __45 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__45->Name = std::wstring( L"hills_plants_6" );
		__45->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__45->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__45->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__45->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"hills_plants_6" ) );
		__45->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__45->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__45->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__45->MyQuad->Base = BasePoint( 1266.809f, 0, 0, 1009.208f, 28090.46f, -860.1955f );

		__45->uv_speed = Vector2( 0, 0 );
		__45->uv_offset = Vector2( 0, 0 );
		__45->Data = PhsxData( 28090.46f, -860.1955f, 0, 0, 0, 0 );
		__45->StartData = PhsxData( 28090.46f, -860.1955f, 0, 0, 0, 0 );
		__27->Floaters.push_back( __45 );

		__27->Parallax = 0.78f;
		__27->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __27 );

		b->Light = 1;
		//b.BL = new Vector2(-4750f, -4500f);
		//b.TR = new Vector2(42470f, 2000f);
		b->BL = Vector2( -100000, -10000 );
		b->TR = Vector2( 100000, 10000 );
	}

	void Background::_code_Castle( const boost::shared_ptr<Background> &b )
	{
		b->GuidCounter = 0;
		b->MyGlobalIllumination = 1;
		b->AllowLava = true;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __1 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__1->Name = std::wstring( L"Wall" );
		__1->Foreground = false;
		__1->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __2 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__2->Name = std::wstring( L"castle_wall" );
		__2->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__2->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_wall" ) );
		__2->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__2->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__2->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__2->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__2->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__2->MyQuad->Base = BasePoint( 8090.417f, 0, 0, 3422.704f, 0, 0 );

		__2->uv_speed = Vector2( 0, 0 );
		__2->uv_offset = Vector2( 0, 0 );
		__2->Data = PhsxData( 0, 0, 0, 0, 0, 0 );
		__2->StartData = PhsxData( 0, 0, 0, 0, 0, 0 );
		__1->Floaters.push_back( __2 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __3 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__3->Name = std::wstring( L"castle_wall_p2" );
		__3->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__3->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_wall_p2" ) );
		__3->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__3->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__3->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__3->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__3->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__3->MyQuad->Base = BasePoint( 8090.417f, 0, 0, 3422.704f, 16180.76f, 0.06445313f );

		__3->uv_speed = Vector2( 0, 0 );
		__3->uv_offset = Vector2( 0, 0 );
		__3->Data = PhsxData( 16180.76f, 0.06445313f, 0, 0, 0, 0 );
		__3->StartData = PhsxData( 16180.76f, 0.06445313f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __3 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __4 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__4->Name = std::wstring( L"castle_wall" );
		__4->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__4->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_wall" ) );
		__4->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__4->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__4->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__4->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__4->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__4->MyQuad->Base = BasePoint( 8090.417f, 0, 0, 3422.704f, 32361.51f, -0.03735352f );

		__4->uv_speed = Vector2( 0, 0 );
		__4->uv_offset = Vector2( 0, 0 );
		__4->Data = PhsxData( 32361.51f, -0.03735352f, 0, 0, 0, 0 );
		__4->StartData = PhsxData( 32361.51f, -0.03735352f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __4 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __5 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__5->Name = std::wstring( L"castle_wall_p2" );
		__5->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__5->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_wall_p2" ) );
		__5->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__5->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__5->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__5->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__5->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__5->MyQuad->Base = BasePoint( 8090.417f, 0, 0, 3422.704f, 48542.02f, 0.08365631f );

		__5->uv_speed = Vector2( 0, 0 );
		__5->uv_offset = Vector2( 0, 0 );
		__5->Data = PhsxData( 48542.02f, 0.08365631f, 0, 0, 0, 0 );
		__5->StartData = PhsxData( 48542.02f, 0.08365631f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __5 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __6 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__6->Name = std::wstring( L"Castle_Window_Left_Frame" );
		__6->MyQuad->Quad_Renamed.MyEffect = Tools::WindowEffect;
		__6->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"Castle_Window_Left_Frame" ) );
		__6->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__6->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__6->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__6->MyQuad->Quad_Renamed.ExtraTexture1 = Tools::Texture( std::wstring( L"Castle_Backdrop_2" ) );
		__6->MyQuad->Quad_Renamed.ExtraTexture2 = Tools::Texture( std::wstring( L"Castle_Window_Left_Mask" ) );

		__6->MyQuad->Base = BasePoint( 821.9902f, 0, 0, 1827.779f, 1229.637f, -119.3635f );

		__6->uv_speed = Vector2( 0, 0 );
		__6->uv_offset = Vector2( 0, 0 );
		__6->Data = PhsxData( 1229.637f, -119.3635f, 0, 0, 0, 0 );
		__6->StartData = PhsxData( 1229.637f, -119.3635f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __6 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __7 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__7->Name = std::wstring( L"Castle_Window_Center_Frame" );
		__7->MyQuad->Quad_Renamed.MyEffect = Tools::WindowEffect;
		__7->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"Castle_Window_Center_Frame" ) );
		__7->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__7->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__7->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__7->MyQuad->Quad_Renamed.ExtraTexture1 = Tools::Texture( std::wstring( L"Castle_Backdrop_2" ) );
		__7->MyQuad->Quad_Renamed.ExtraTexture2 = Tools::Texture( std::wstring( L"Castle_Window_Center_Mask" ) );

		__7->MyQuad->Base = BasePoint( 1069.899f, 0, 0, 2655.173f, 3022.709f, -70.24944f );

		__7->uv_speed = Vector2( 0, 0 );
		__7->uv_offset = Vector2( 0, 0 );
		__7->Data = PhsxData( 3022.709f, -70.24944f, 0, 0, 0, 0 );
		__7->StartData = PhsxData( 3022.709f, -70.24944f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __7 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __8 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__8->Name = std::wstring( L"Castle_Window_Right_Frame" );
		__8->MyQuad->Quad_Renamed.MyEffect = Tools::WindowEffect;
		__8->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"Castle_Window_Right_Frame" ) );
		__8->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__8->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__8->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__8->MyQuad->Quad_Renamed.ExtraTexture1 = Tools::Texture( std::wstring( L"Castle_Backdrop_2" ) );
		__8->MyQuad->Quad_Renamed.ExtraTexture2 = Tools::Texture( std::wstring( L"Castle_Window_Right_Mask" ) );

		__8->MyQuad->Base = BasePoint( 868.2858f, 0, 0, 1843.033f, 4746.968f, -156.1684f );

		__8->uv_speed = Vector2( 0, 0 );
		__8->uv_offset = Vector2( 0, 0 );
		__8->Data = PhsxData( 4746.968f, -156.1684f, 0, 0, 0, 0 );
		__8->StartData = PhsxData( 4746.968f, -156.1684f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __8 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __9 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__9->Name = std::wstring( L"Castle_Window_Left_Frame" );
		__9->MyQuad->Quad_Renamed.MyEffect = Tools::WindowEffect;
		__9->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"Castle_Window_Left_Frame" ) );
		__9->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__9->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__9->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__9->MyQuad->Quad_Renamed.ExtraTexture1 = Tools::Texture( std::wstring( L"Castle_Backdrop_2" ) );
		__9->MyQuad->Quad_Renamed.ExtraTexture2 = Tools::Texture( std::wstring( L"Castle_Window_Left_Mask" ) );

		__9->MyQuad->Base = BasePoint( 821.9902f, 0, 0, 1827.779f, 10648.15f, -214.8148f );

		__9->uv_speed = Vector2( 0, 0 );
		__9->uv_offset = Vector2( 0, 0 );
		__9->Data = PhsxData( 10648.15f, -214.8148f, 0, 0, 0, 0 );
		__9->StartData = PhsxData( 10648.15f, -214.8148f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __9 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __10 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__10->Name = std::wstring( L"Castle_Window_Center_Frame" );
		__10->MyQuad->Quad_Renamed.MyEffect = Tools::WindowEffect;
		__10->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"Castle_Window_Center_Frame" ) );
		__10->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__10->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__10->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__10->MyQuad->Quad_Renamed.ExtraTexture1 = Tools::Texture( std::wstring( L"Castle_Backdrop_2" ) );
		__10->MyQuad->Quad_Renamed.ExtraTexture2 = Tools::Texture( std::wstring( L"Castle_Window_Center_Mask" ) );

		__10->MyQuad->Base = BasePoint( 1069.899f, 0, 0, 2655.173f, 12472.22f, -112.9629f );

		__10->uv_speed = Vector2( 0, 0 );
		__10->uv_offset = Vector2( 0, 0 );
		__10->Data = PhsxData( 12472.22f, -112.9629f, 0, 0, 0, 0 );
		__10->StartData = PhsxData( 12472.22f, -112.9629f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __10 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __11 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__11->Name = std::wstring( L"Castle_Window_Right_Frame" );
		__11->MyQuad->Quad_Renamed.MyEffect = Tools::WindowEffect;
		__11->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"Castle_Window_Right_Frame" ) );
		__11->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__11->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__11->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__11->MyQuad->Quad_Renamed.ExtraTexture1 = Tools::Texture( std::wstring( L"Castle_Backdrop_2" ) );
		__11->MyQuad->Quad_Renamed.ExtraTexture2 = Tools::Texture( std::wstring( L"Castle_Window_Right_Mask" ) );

		__11->MyQuad->Base = BasePoint( 868.2858f, 0, 0, 1843.033f, 14259.26f, -279.6296f );

		__11->uv_speed = Vector2( 0, 0 );
		__11->uv_offset = Vector2( 0, 0 );
		__11->Data = PhsxData( 14259.26f, -279.6296f, 0, 0, 0, 0 );
		__11->StartData = PhsxData( 14259.26f, -279.6296f, 0, 0, 0, 0 );
		__1->Floaters.push_back( __11 );

		__1->Parallax = 0.3f;
		__1->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __1 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __12 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__12->Name = std::wstring( L"Pillars" );
		__12->Foreground = false;
		__12->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __13 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__13->Name = std::wstring( L"castle_pillar" );
		__13->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__13->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_pillar" ) );
		__13->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__13->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__13->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__13->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__13->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__13->MyQuad->Base = BasePoint( 851.4517f, 0, 0, 3055.162f, -432.9412f, -40.13337f );

		__13->uv_speed = Vector2( 0, 0 );
		__13->uv_offset = Vector2( 0, 0 );
		__13->Data = PhsxData( -432.9412f, -40.13337f, 0, 0, 0, 0 );
		__13->StartData = PhsxData( -432.9412f, -40.13337f, 0, 0, 0, 0 );
		__12->Floaters.push_back( __13 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __14 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__14->Name = std::wstring( L"castle_pillar" );
		__14->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__14->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_pillar" ) );
		__14->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__14->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__14->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__14->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__14->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__14->MyQuad->Base = BasePoint( 851.4517f, 0, 0, 3055.162f, 6537.952f, -69.89888f );

		__14->uv_speed = Vector2( 0, 0 );
		__14->uv_offset = Vector2( 0, 0 );
		__14->Data = PhsxData( 6537.952f, -69.89888f, 0, 0, 0, 0 );
		__14->StartData = PhsxData( 6537.952f, -69.89888f, 0, 0, 0, 0 );
		__12->Floaters.push_back( __14 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __15 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__15->Name = std::wstring( L"castle_pillar" );
		__15->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__15->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_pillar" ) );
		__15->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__15->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__15->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__15->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__15->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__15->MyQuad->Base = BasePoint( 851.4517f, 0, 0, 3055.162f, 8990.559f, -131.1371f );

		__15->uv_speed = Vector2( 0, 0 );
		__15->uv_offset = Vector2( 0, 0 );
		__15->Data = PhsxData( 8990.559f, -131.1371f, 0, 0, 0, 0 );
		__15->StartData = PhsxData( 8990.559f, -131.1371f, 0, 0, 0, 0 );
		__12->Floaters.push_back( __15 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __16 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__16->Name = std::wstring( L"castle_pillar" );
		__16->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__16->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_pillar" ) );
		__16->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__16->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__16->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__16->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__16->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__16->MyQuad->Base = BasePoint( 851.4517f, 0, 0, 3055.162f, -2508.168f, -225.2005f );

		__16->uv_speed = Vector2( 0, 0 );
		__16->uv_offset = Vector2( 0, 0 );
		__16->Data = PhsxData( -2508.168f, -225.2005f, 0, 0, 0, 0 );
		__16->StartData = PhsxData( -2508.168f, -225.2005f, 0, 0, 0, 0 );
		__12->Floaters.push_back( __16 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __17 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__17->Name = std::wstring( L"castle_pillar" );
		__17->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__17->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_pillar" ) );
		__17->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__17->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__17->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__17->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__17->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__17->MyQuad->Base = BasePoint( 851.4517f, 0, 0, 3055.162f, -7470.558f, -152.276f );

		__17->uv_speed = Vector2( 0, 0 );
		__17->uv_offset = Vector2( 0, 0 );
		__17->Data = PhsxData( -7470.558f, -152.276f, 0, 0, 0, 0 );
		__17->StartData = PhsxData( -7470.558f, -152.276f, 0, 0, 0, 0 );
		__12->Floaters.push_back( __17 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __18 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__18->Name = std::wstring( L"castle_pillar" );
		__18->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__18->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_pillar" ) );
		__18->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__18->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__18->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__18->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__18->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__18->MyQuad->Base = BasePoint( 851.4517f, 0, 0, 3055.162f, 15948.25f, 6.882294f );

		__18->uv_speed = Vector2( 0, 0 );
		__18->uv_offset = Vector2( 0, 0 );
		__18->Data = PhsxData( 15948.25f, 6.882294f, 0, 0, 0, 0 );
		__18->StartData = PhsxData( 15948.25f, 6.882294f, 0, 0, 0, 0 );
		__12->Floaters.push_back( __18 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __19 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__19->Name = std::wstring( L"castle_pillar" );
		__19->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__19->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_pillar" ) );
		__19->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__19->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__19->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__19->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__19->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__19->MyQuad->Base = BasePoint( 851.4517f, 0, 0, 3055.162f, 18275.31f, -203.903f );

		__19->uv_speed = Vector2( 0, 0 );
		__19->uv_offset = Vector2( 0, 0 );
		__19->Data = PhsxData( 18275.31f, -203.903f, 0, 0, 0, 0 );
		__19->StartData = PhsxData( 18275.31f, -203.903f, 0, 0, 0, 0 );
		__12->Floaters.push_back( __19 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __20 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__20->Name = std::wstring( L"castle_pillar" );
		__20->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__20->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_pillar" ) );
		__20->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__20->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__20->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__20->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__20->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__20->MyQuad->Base = BasePoint( 851.4517f, 0, 0, 3055.162f, 25510.57f, -232.6846f );

		__20->uv_speed = Vector2( 0, 0 );
		__20->uv_offset = Vector2( 0, 0 );
		__20->Data = PhsxData( 25510.57f, -232.6846f, 0, 0, 0, 0 );
		__20->StartData = PhsxData( 25510.57f, -232.6846f, 0, 0, 0, 0 );
		__12->Floaters.push_back( __20 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __21 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__21->Name = std::wstring( L"castle_pillar" );
		__21->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__21->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_pillar" ) );
		__21->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__21->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__21->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__21->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__21->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__21->MyQuad->Base = BasePoint( 851.4517f, 0, 0, 3055.162f, 28404.66f, -225.4594f );

		__21->uv_speed = Vector2( 0, 0 );
		__21->uv_offset = Vector2( 0, 0 );
		__21->Data = PhsxData( 28404.66f, -225.4594f, 0, 0, 0, 0 );
		__21->StartData = PhsxData( 28404.66f, -225.4594f, 0, 0, 0, 0 );
		__12->Floaters.push_back( __21 );

		__12->Parallax = 0.36f;
		__12->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __12 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __22 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__22->Name = std::wstring( L"Chandeliers_Far" );
		__22->Foreground = false;
		__22->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __23 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__23->Name = std::wstring( L"castle_chandelier_far" );
		__23->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__23->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__23->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__23->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__23->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__23->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__23->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__23->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, -12552.62f, 2073.532f );

		__23->uv_speed = Vector2( 0, 0 );
		__23->uv_offset = Vector2( 0, 0 );
		__23->Data = PhsxData( -12552.62f, 2073.532f, 0, 0, 0, 0 );
		__23->StartData = PhsxData( -12552.62f, 2073.532f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __23 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __24 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__24->Name = std::wstring( L"castle_chandelier_far" );
		__24->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__24->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__24->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__24->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__24->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__24->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__24->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__24->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, -9512.358f, 2305.82f );

		__24->uv_speed = Vector2( 0, 0 );
		__24->uv_offset = Vector2( 0, 0 );
		__24->Data = PhsxData( -9512.358f, 2305.82f, 0, 0, 0, 0 );
		__24->StartData = PhsxData( -9512.358f, 2305.82f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __24 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __25 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__25->Name = std::wstring( L"castle_chandelier_far" );
		__25->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__25->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__25->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__25->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__25->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__25->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__25->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__25->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, -6887.27f, 2162.044f );

		__25->uv_speed = Vector2( 0, 0 );
		__25->uv_offset = Vector2( 0, 0 );
		__25->Data = PhsxData( -6887.27f, 2162.044f, 0, 0, 0, 0 );
		__25->StartData = PhsxData( -6887.27f, 2162.044f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __25 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __26 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__26->Name = std::wstring( L"castle_chandelier_far" );
		__26->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__26->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__26->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__26->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__26->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__26->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__26->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__26->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, -3205.039f, 2042.446f );

		__26->uv_speed = Vector2( 0, 0 );
		__26->uv_offset = Vector2( 0, 0 );
		__26->Data = PhsxData( -3205.039f, 2042.446f, 0, 0, 0, 0 );
		__26->StartData = PhsxData( -3205.039f, 2042.446f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __26 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __27 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__27->Name = std::wstring( L"castle_chandelier_far" );
		__27->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__27->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__27->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__27->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__27->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__27->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__27->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__27->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, -849.4259f, 1762.513f );

		__27->uv_speed = Vector2( 0, 0 );
		__27->uv_offset = Vector2( 0, 0 );
		__27->Data = PhsxData( -849.4259f, 1762.513f, 0, 0, 0, 0 );
		__27->StartData = PhsxData( -849.4259f, 1762.513f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __27 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __28 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__28->Name = std::wstring( L"castle_chandelier_far" );
		__28->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__28->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__28->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__28->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__28->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__28->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__28->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__28->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, 1569.904f, 1935.758f );

		__28->uv_speed = Vector2( 0, 0 );
		__28->uv_offset = Vector2( 0, 0 );
		__28->Data = PhsxData( 1569.904f, 1935.758f, 0, 0, 0, 0 );
		__28->StartData = PhsxData( 1569.904f, 1935.758f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __28 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __29 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__29->Name = std::wstring( L"castle_chandelier_far" );
		__29->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__29->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__29->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__29->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__29->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__29->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__29->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__29->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, 3734.492f, 1787.61f );

		__29->uv_speed = Vector2( 0, 0 );
		__29->uv_offset = Vector2( 0, 0 );
		__29->Data = PhsxData( 3734.492f, 1787.61f, 0, 0, 0, 0 );
		__29->StartData = PhsxData( 3734.492f, 1787.61f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __29 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __30 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__30->Name = std::wstring( L"castle_chandelier_far" );
		__30->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__30->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__30->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__30->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__30->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__30->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__30->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__30->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, 6327.063f, 1954.761f );

		__30->uv_speed = Vector2( 0, 0 );
		__30->uv_offset = Vector2( 0, 0 );
		__30->Data = PhsxData( 6327.063f, 1954.761f, 0, 0, 0, 0 );
		__30->StartData = PhsxData( 6327.063f, 1954.761f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __30 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __31 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__31->Name = std::wstring( L"castle_chandelier_far" );
		__31->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__31->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__31->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__31->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__31->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__31->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__31->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__31->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, 8253.275f, 1765.66f );

		__31->uv_speed = Vector2( 0, 0 );
		__31->uv_offset = Vector2( 0, 0 );
		__31->Data = PhsxData( 8253.275f, 1765.66f, 0, 0, 0, 0 );
		__31->StartData = PhsxData( 8253.275f, 1765.66f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __31 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __32 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__32->Name = std::wstring( L"castle_chandelier_far" );
		__32->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__32->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__32->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__32->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__32->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__32->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__32->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__32->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, 10659.29f, 2202.28f );

		__32->uv_speed = Vector2( 0, 0 );
		__32->uv_offset = Vector2( 0, 0 );
		__32->Data = PhsxData( 10659.29f, 2202.28f, 0, 0, 0, 0 );
		__32->StartData = PhsxData( 10659.29f, 2202.28f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __32 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __33 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__33->Name = std::wstring( L"castle_chandelier_far" );
		__33->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__33->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__33->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__33->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__33->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__33->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__33->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__33->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, 12939.41f, 1861.483f );

		__33->uv_speed = Vector2( 0, 0 );
		__33->uv_offset = Vector2( 0, 0 );
		__33->Data = PhsxData( 12939.41f, 1861.483f, 0, 0, 0, 0 );
		__33->StartData = PhsxData( 12939.41f, 1861.483f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __33 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __34 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__34->Name = std::wstring( L"castle_chandelier_far" );
		__34->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__34->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__34->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__34->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__34->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__34->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__34->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__34->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, 14887.88f, 2277.576f );

		__34->uv_speed = Vector2( 0, 0 );
		__34->uv_offset = Vector2( 0, 0 );
		__34->Data = PhsxData( 14887.88f, 2277.576f, 0, 0, 0, 0 );
		__34->StartData = PhsxData( 14887.88f, 2277.576f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __34 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __35 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__35->Name = std::wstring( L"castle_chandelier_far" );
		__35->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__35->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__35->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__35->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__35->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__35->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__35->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__35->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, 16950.35f, 1941.349f );

		__35->uv_speed = Vector2( 0, 0 );
		__35->uv_offset = Vector2( 0, 0 );
		__35->Data = PhsxData( 16950.35f, 1941.349f, 0, 0, 0, 0 );
		__35->StartData = PhsxData( 16950.35f, 1941.349f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __35 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __36 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__36->Name = std::wstring( L"castle_chandelier_far" );
		__36->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__36->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__36->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__36->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__36->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__36->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__36->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__36->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, 19168.29f, 2669.889f );

		__36->uv_speed = Vector2( 0, 0 );
		__36->uv_offset = Vector2( 0, 0 );
		__36->Data = PhsxData( 19168.29f, 2669.889f, 0, 0, 0, 0 );
		__36->StartData = PhsxData( 19168.29f, 2669.889f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __36 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __37 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__37->Name = std::wstring( L"castle_chandelier_far" );
		__37->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__37->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__37->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__37->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__37->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__37->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__37->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__37->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, 21178.94f, 1858.435f );

		__37->uv_speed = Vector2( 0, 0 );
		__37->uv_offset = Vector2( 0, 0 );
		__37->Data = PhsxData( 21178.94f, 1858.435f, 0, 0, 0, 0 );
		__37->StartData = PhsxData( 21178.94f, 1858.435f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __37 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __38 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__38->Name = std::wstring( L"castle_chandelier_far" );
		__38->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__38->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_far" ) );
		__38->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__38->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__38->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__38->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__38->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__38->MyQuad->Base = BasePoint( 619.2842f, 0, 0, 2095.021f, 24296.85f, 1994.823f );

		__38->uv_speed = Vector2( 0, 0 );
		__38->uv_offset = Vector2( 0, 0 );
		__38->Data = PhsxData( 24296.85f, 1994.823f, 0, 0, 0, 0 );
		__38->StartData = PhsxData( 24296.85f, 1994.823f, 0, 0, 0, 0 );
		__22->Floaters.push_back( __38 );

		__22->Parallax = 0.42f;
		__22->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __22 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __39 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__39->Name = std::wstring( L"Chandeliers_Close" );
		__39->Foreground = false;
		__39->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __40 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__40->Name = std::wstring( L"castle_chandelier_close" );
		__40->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__40->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_close" ) );
		__40->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__40->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__40->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__40->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__40->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__40->MyQuad->Base = BasePoint( 928.205f, 0, 0, 790.1899f, 3612.716f, 1209.252f );

		__40->uv_speed = Vector2( 0, 0 );
		__40->uv_offset = Vector2( 0, 0 );
		__40->Data = PhsxData( 3612.716f, 1209.252f, 0, 0, 0, 0 );
		__40->StartData = PhsxData( 3612.716f, 1209.252f, 0, 0, 0, 0 );
		__39->Floaters.push_back( __40 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __41 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__41->Name = std::wstring( L"castle_chandelier_close" );
		__41->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__41->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_close" ) );
		__41->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__41->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__41->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__41->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__41->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__41->MyQuad->Base = BasePoint( 928.205f, 0, 0, 790.1899f, -652.3344f, 1221.809f );

		__41->uv_speed = Vector2( 0, 0 );
		__41->uv_offset = Vector2( 0, 0 );
		__41->Data = PhsxData( -652.3344f, 1221.809f, 0, 0, 0, 0 );
		__41->StartData = PhsxData( -652.3344f, 1221.809f, 0, 0, 0, 0 );
		__39->Floaters.push_back( __41 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __42 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__42->Name = std::wstring( L"castle_chandelier_close" );
		__42->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__42->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_close" ) );
		__42->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__42->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__42->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__42->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__42->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__42->MyQuad->Base = BasePoint( 928.205f, 0, 0, 790.1899f, 7568.055f, 1272.035f );

		__42->uv_speed = Vector2( 0, 0 );
		__42->uv_offset = Vector2( 0, 0 );
		__42->Data = PhsxData( 7568.055f, 1272.035f, 0, 0, 0, 0 );
		__42->StartData = PhsxData( 7568.055f, 1272.035f, 0, 0, 0, 0 );
		__39->Floaters.push_back( __42 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __43 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__43->Name = std::wstring( L"castle_chandelier_close" );
		__43->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__43->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_close" ) );
		__43->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__43->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__43->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__43->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__43->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__43->MyQuad->Base = BasePoint( 928.205f, 0, 0, 790.1899f, 12490.26f, 1238.551f );

		__43->uv_speed = Vector2( 0, 0 );
		__43->uv_offset = Vector2( 0, 0 );
		__43->Data = PhsxData( 12490.26f, 1238.551f, 0, 0, 0, 0 );
		__43->StartData = PhsxData( 12490.26f, 1238.551f, 0, 0, 0, 0 );
		__39->Floaters.push_back( __43 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __44 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__44->Name = std::wstring( L"castle_chandelier_close" );
		__44->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__44->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_close" ) );
		__44->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__44->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__44->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__44->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__44->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__44->MyQuad->Base = BasePoint( 928.205f, 0, 0, 790.1899f, -4636.972f, 1288.777f );

		__44->uv_speed = Vector2( 0, 0 );
		__44->uv_offset = Vector2( 0, 0 );
		__44->Data = PhsxData( -4636.972f, 1288.777f, 0, 0, 0, 0 );
		__44->StartData = PhsxData( -4636.972f, 1288.777f, 0, 0, 0, 0 );
		__39->Floaters.push_back( __44 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __45 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__45->Name = std::wstring( L"castle_chandelier_close" );
		__45->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__45->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_close" ) );
		__45->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__45->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__45->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__45->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__45->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__45->MyQuad->Base = BasePoint( 928.205f, 0, 0, 790.1899f, -9182.47f, 1196.696f );

		__45->uv_speed = Vector2( 0, 0 );
		__45->uv_offset = Vector2( 0, 0 );
		__45->Data = PhsxData( -9182.47f, 1196.696f, 0, 0, 0, 0 );
		__45->StartData = PhsxData( -9182.47f, 1196.696f, 0, 0, 0, 0 );
		__39->Floaters.push_back( __45 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __46 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__46->Name = std::wstring( L"castle_chandelier_close" );
		__46->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__46->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_close" ) );
		__46->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__46->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__46->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__46->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__46->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__46->MyQuad->Base = BasePoint( 928.205f, 0, 0, 790.1899f, 16752.85f, 1337.078f );

		__46->uv_speed = Vector2( 0, 0 );
		__46->uv_offset = Vector2( 0, 0 );
		__46->Data = PhsxData( 16752.85f, 1337.078f, 0, 0, 0, 0 );
		__46->StartData = PhsxData( 16752.85f, 1337.078f, 0, 0, 0, 0 );
		__39->Floaters.push_back( __46 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __47 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__47->Name = std::wstring( L"castle_chandelier_close" );
		__47->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__47->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_close" ) );
		__47->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__47->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__47->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__47->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__47->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__47->MyQuad->Base = BasePoint( 928.205f, 0, 0, 790.1899f, 20212.56f, 1004.161f );

		__47->uv_speed = Vector2( 0, 0 );
		__47->uv_offset = Vector2( 0, 0 );
		__47->Data = PhsxData( 20212.56f, 1004.161f, 0, 0, 0, 0 );
		__47->StartData = PhsxData( 20212.56f, 1004.161f, 0, 0, 0, 0 );
		__39->Floaters.push_back( __47 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __48 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__48->Name = std::wstring( L"castle_chandelier_close" );
		__48->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__48->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"castle_chandelier_close" ) );
		__48->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__48->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__48->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__48->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__48->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__48->MyQuad->Base = BasePoint( 928.205f, 0, 0, 790.1899f, 23463.48f, 1307.482f );

		__48->uv_speed = Vector2( 0, 0 );
		__48->uv_offset = Vector2( 0, 0 );
		__48->Data = PhsxData( 23463.48f, 1307.482f, 0, 0, 0, 0 );
		__48->StartData = PhsxData( 23463.48f, 1307.482f, 0, 0, 0, 0 );
		__39->Floaters.push_back( __48 );

		__39->Parallax = 0.52f;
		__39->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __39 );

		b->Light = 1;
		//b.BL = new Vector2(-20555.55f, -6177.398f);
		//b.TR = new Vector2(31313.13f, 2446.58f);
		b->BL = Vector2( -100000, -10000 );
		b->TR = Vector2( 100000, 10000 );
	}

	void Background::_code_Sea( const boost::shared_ptr<Background> &b )
	{
		b->GuidCounter = 0;
		b->MyGlobalIllumination = 1;
		b->AllowLava = true;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __1 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__1->Name = std::wstring( L"Layer" );
		__1->Foreground = false;
		__1->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __2 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__2->Name = std::wstring( L"sea_backdrop_p1_0" );
		__2->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__2->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__2->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__2->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_backdrop" ) );
		__2->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__2->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__2->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__2->MyQuad->Base = BasePoint( 40199, 0, 0, 17007.27f, -3333.766f, 0 );

		__2->uv_speed = Vector2( 0, 0 );
		__2->uv_offset = Vector2( 0, 0 );
		__2->Data = PhsxData( -3333.766f, 0, 0, 0, 0, 0 );
		__2->StartData = PhsxData( -3333.766f, 0, 0, 0, 0, 0 );
		__1->Floaters.push_back( __2 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __3 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__3->Name = std::wstring( L"sea_backdrop_p2_0" );
		__3->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__3->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__3->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__3->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_backdrop_p2" ) );
		__3->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__3->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__3->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__3->MyQuad->Base = BasePoint( 40199, 0, 0, 17007.27f, 77064.23f, 0 );

		__3->uv_speed = Vector2( 0, 0 );
		__3->uv_offset = Vector2( 0, 0 );
		__3->Data = PhsxData( 77064.23f, 0, 0, 0, 0, 0 );
		__3->StartData = PhsxData( 77064.23f, 0, 0, 0, 0, 0 );
		__1->Floaters.push_back( __3 );

		__1->Parallax = 0.06f;
		__1->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __1 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __4 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__4->Name = std::wstring( L"Layer" );
		__4->Foreground = false;
		__4->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __5 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__5->Name = std::wstring( L"sea_behind_water_1" );
		__5->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__5->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__5->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__5->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_behind_water_1" ) );
		__5->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__5->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__5->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__5->MyQuad->Base = BasePoint( 2439.164f, 0, 0, 5446.352f, -13367.37f, -754.4899f );

		__5->uv_speed = Vector2( 0, 0 );
		__5->uv_offset = Vector2( 0, 0 );
		__5->Data = PhsxData( -13367.37f, -754.4899f, 0, 0, 0, 0 );
		__5->StartData = PhsxData( -13367.37f, -754.4899f, 0, 0, 0, 0 );
		__4->Floaters.push_back( __5 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __6 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__6->Name = std::wstring( L"sea_behind_water_3" );
		__6->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__6->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__6->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__6->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_behind_water_3" ) );
		__6->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__6->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__6->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__6->MyQuad->Base = BasePoint( 8032.311f, 0.f, 0.f, 2956.285f, 1839.004f, -3958.902f );

		__6->uv_speed = Vector2( 0, 0 );
		__6->uv_offset = Vector2( 0, 0 );
		__6->Data = PhsxData( 1839.004f, -3958.902f, 0, 0, 0, 0 );
		__6->StartData = PhsxData( 1839.004f, -3958.902f, 0, 0, 0, 0 );
		__4->Floaters.push_back( __6 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __7 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__7->Name = std::wstring( L"sea_behind_water_2" );
		__7->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__7->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__7->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__7->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_behind_water_2" ) );
		__7->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__7->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__7->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__7->MyQuad->Base = BasePoint( 3021.783f, 0, 0, 4421.52f, 14889.68f, -2327.567f );

		__7->uv_speed = Vector2( 0, 0 );
		__7->uv_offset = Vector2( 0, 0 );
		__7->Data = PhsxData( 14889.68f, -2327.567f, 0, 0, 0, 0 );
		__7->StartData = PhsxData( 14889.68f, -2327.567f, 0, 0, 0, 0 );
		__4->Floaters.push_back( __7 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __8 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__8->Name = std::wstring( L"sea_behind_water_3" );
		__8->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__8->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__8->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__8->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_behind_water_3" ) );
		__8->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__8->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__8->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__8->MyQuad->Base = BasePoint( 8032.311f, 0, 0, 2956.285f, 33263.91f, -4019.146f );

		__8->uv_speed = Vector2( 0, 0 );
		__8->uv_offset = Vector2( 0, 0 );
		__8->Data = PhsxData( 33263.91f, -4019.146f, 0, 0, 0, 0 );
		__8->StartData = PhsxData( 33263.91f, -4019.146f, 0, 0, 0, 0 );
		__4->Floaters.push_back( __8 );

		__4->Parallax = 0.15f;
		__4->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __4 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __9 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__9->Name = std::wstring( L"Layer" );
		__9->Foreground = false;
		__9->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __10 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__10->Name = std::wstring( L"sea_seamonster" );
		__10->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__10->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__10->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__10->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_seamonster" ) );
		__10->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__10->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__10->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__10->MyQuad->Base = BasePoint( 1440, 0, 0, 817.7778f, 4668.236f, -2436.043f );

		__10->uv_speed = Vector2( 0, 0 );
		__10->uv_offset = Vector2( 0, 0 );
		__10->Data = PhsxData( 4668.236f, -2436.043f, 10, 0, 0, 0 );
		__10->StartData = PhsxData( 4668.236f, -2436.043f, 10, 0, 0, 0 );
		__9->Floaters.push_back( __10 );

		__9->Parallax = 0.25f;
		__9->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __9 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __11 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__11->Name = std::wstring( L"Layer" );
		__11->Foreground = false;
		__11->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __12 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__12->Name = std::wstring( L"sea_clouds" );

		__12->MyQuad->Quad_Renamed.v0.Vertex = MyOwnVertexFormat( Vector2( -9694.891f, 3457.797f ), Vector2( 1.591826f, 0 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__12->MyQuad->Quad_Renamed.v0.Pos = Vector2( -1, 1 );

		__12->MyQuad->Quad_Renamed.v1.Vertex = MyOwnVertexFormat( Vector2( 47179.37f, 3457.797f ), Vector2( 3.592155f, 0 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__12->MyQuad->Quad_Renamed.v1.Pos = Vector2( 1, 1 );

		__12->MyQuad->Quad_Renamed.v2.Vertex = MyOwnVertexFormat( Vector2( -9694.891f, -3651.485f ), Vector2( 1.591826f, 1 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__12->MyQuad->Quad_Renamed.v2.Pos = Vector2( -1, -1 );

		__12->MyQuad->Quad_Renamed.v3.Vertex = MyOwnVertexFormat( Vector2( 47179.37f, -3651.485f ), Vector2( 3.592155f, 1 ), Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) ) );
		__12->MyQuad->Quad_Renamed.v3.Pos = Vector2( 1, -1 );

		__12->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__12->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__12->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__12->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_clouds" ) );
		__12->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__12->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__12->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__12->MyQuad->Base = BasePoint( 28437.13f, 0, 0, 3554.641f, 18742.24f, -96.84418f );

		__12->uv_speed = Vector2( 0.00025f, 0 );
		__12->uv_offset = Vector2( 1.241851f, 0 );
		__12->Data = PhsxData( 18742.24f, -96.84418f, 0, 0, 0, 0 );
		__12->StartData = PhsxData( 18742.24f, -96.84418f, 0, 0, 0, 0 );
		__11->Floaters.push_back( __12 );

		__11->Parallax = 0.2f;
		__11->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __11 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloaterList> __13 = boost::make_shared<CloudberryKingdom::BackgroundFloaterList>();
		__13->Name = std::wstring( L"Layer" );
		__13->Foreground = false;
		__13->Fixed = false;
		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __14 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__14->Name = std::wstring( L"sea_water_1" );
		__14->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__14->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__14->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__14->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_water_1" ) );
		__14->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__14->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__14->MyQuad->Quad_Renamed.BlendAddRatio = 0;
		__14->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__14->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__14->MyQuad->Quad_Renamed.ExtraTexture2 = 0;

		__14->MyQuad->Base = BasePoint( 7761.776f, 0, 0, 557.1197f, 1360.16f, -2833.725f );

		__14->uv_speed = Vector2( 0, 0 );
		__14->uv_offset = Vector2( 0, 0 );
		__14->Data = PhsxData( 1360.16f, -2833.725f, 0, 0, 0, 0 );
		__14->StartData = PhsxData( 1360.16f, -2833.725f, 0, 0, 0, 0 );
		__13->Floaters.push_back( __14 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __15 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__15->Name = std::wstring( L"sea_water_2" );
		__15->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__15->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__15->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__15->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_water_2" ) );
		__15->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__15->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__15->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__15->MyQuad->Base = BasePoint( 7761.776f, 0, 0, 557.1197f, 16882.17f, -2834.259f );

		__15->uv_speed = Vector2( 0, 0 );
		__15->uv_offset = Vector2( 0, 0 );
		__15->Data = PhsxData( 16882.17f, -2834.259f, 0, 0, 0, 0 );
		__15->StartData = PhsxData( 16882.17f, -2834.259f, 0, 0, 0, 0 );
		__13->Floaters.push_back( __15 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __16 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__16->Name = std::wstring( L"sea_water_3" );
		__16->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__16->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__16->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__16->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_water_1" ) );
		__16->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__16->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__16->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__16->MyQuad->Base = BasePoint( 7761.776f, 0.f, 0.f, 557.1197f, 32405.72f, -2833.575f );

		__16->uv_speed = Vector2( 0, 0 );
		__16->uv_offset = Vector2( 0, 0 );
		__16->Data = PhsxData( 32405.72f, -2833.575f, 0.f, 0.f, 0.f, 0.f );
		__16->StartData = PhsxData( 32405.72f, -2833.575f, 0, 0, 0, 0 );
		__13->Floaters.push_back( __16 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __17 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__17->Name = std::wstring( L"sea_rock_1" );
		__17->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__17->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__17->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__17->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_rock_1" ) );
		__17->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__17->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__17->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__17->MyQuad->Base = BasePoint( 1200, 0, 0, 1316.289f, 644.2549f, -1623.055f );

		__17->uv_speed = Vector2( 0, 0 );
		__17->uv_offset = Vector2( 0, 0 );
		__17->Data = PhsxData( 644.2549f, -1623.055f, 0.f, 0.f, 0.f, 0.f );
		__17->StartData = PhsxData( 644.2549f, -1623.055f, 0.f, 0.f, 0.f, 0.f );
		__13->Floaters.push_back( __17 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __18 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__18->Name = std::wstring( L"sea_rock_2" );
		__18->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__18->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__18->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__18->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_rock_2" ) );
		__18->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__18->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__18->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__18->MyQuad->Base = BasePoint( 1200.f, 0.f, 0.f, 1008.589f, 10703.01f, -2166.667f );

		__18->uv_speed = Vector2( 0, 0 );
		__18->uv_offset = Vector2( 0, 0 );
		__18->Data = PhsxData( 10703.01f, -2166.667f, 0, 0, 0, 0 );
		__18->StartData = PhsxData( 10703.01f, -2166.667f, 0, 0, 0, 0 );
		__13->Floaters.push_back( __18 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __19 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__19->Name = std::wstring( L"sea_rock_3" );
		__19->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__19->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__19->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__19->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_rock_3" ) );
		__19->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__19->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__19->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__19->MyQuad->Base = BasePoint( 3412.958f, 0.f, 0.f, 3211.681f, -3843.27f, -342.5923f );

		__19->uv_speed = Vector2( 0, 0 );
		__19->uv_offset = Vector2( 0, 0 );
		__19->Data = PhsxData( -3843.27f, -342.5923f, 0, 0, 0, 0 );
		__19->StartData = PhsxData( -3843.27f, -342.5923f, 0, 0, 0, 0 );
		__13->Floaters.push_back( __19 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __20 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__20->Name = std::wstring( L"sea_rock_4" );
		__20->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__20->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__20->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__20->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_rock_4" ) );
		__20->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__20->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__20->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__20->MyQuad->Base = BasePoint( 220.506f, 0.f, 0.f, 162.2992f, 9069.232f, -2839.639f );

		__20->uv_speed = Vector2( 0, 0 );
		__20->uv_offset = Vector2( 0, 0 );
		__20->Data = PhsxData( 9069.232f, -2839.639f, 0, 0, 0, 0 );
		__20->StartData = PhsxData( 9069.232f, -2839.639f, 0, 0, 0, 0 );
		__13->Floaters.push_back( __20 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __21 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__21->Name = std::wstring( L"sea_rock_5" );
		__21->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__21->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__21->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__21->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_rock_5" ) );
		__21->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__21->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__21->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__21->MyQuad->Base = BasePoint( 2536.874f, 0.f, 0.f, 1736.723f, 14098.87f, -1460.87f );

		__21->uv_speed = Vector2( 0, 0 );
		__21->uv_offset = Vector2( 0, 0 );
		__21->Data = PhsxData( 14098.87f, -1460.87f, 0, 0, 0, 0 );
		__21->StartData = PhsxData( 14098.87f, -1460.87f, 0, 0, 0, 0 );
		__13->Floaters.push_back( __21 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __22 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__22->Name = std::wstring( L"sea_rock_1" );
		__22->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__22->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__22->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__22->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_rock_1" ) );
		__22->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__22->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__22->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__22->MyQuad->Base = BasePoint( 1200, 0, 0, 1316.289f, 6594.551f, -1877.636f );

		__22->uv_speed = Vector2( 0, 0 );
		__22->uv_offset = Vector2( 0, 0 );
		__22->Data = PhsxData( 6594.551f, -1877.636f, 0, 0, 0, 0 );
		__22->StartData = PhsxData( 6594.551f, -1877.636f, 0, 0, 0, 0 );
		__13->Floaters.push_back( __22 );

		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __23 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__23->Name = std::wstring( L"sea_rock_2" );
		__23->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__23->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__23->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__23->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_rock_2" ) );
		__23->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__23->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__23->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__23->MyQuad->Base = BasePoint( 1200.f, 0.f, 0.f, 1008.589f, 18768.2f, -2215.924f );

		__23->uv_speed = Vector2( 0, 0 );
		__23->uv_offset = Vector2( 0, 0 );
		__23->Data = PhsxData( 18768.2f, -2215.924f, 0, 0, 0, 0 );
		__23->StartData = PhsxData( 18768.2f, -2215.924f, 0, 0, 0, 0 );
		__13->Floaters.push_back( __23 );



		boost::shared_ptr<CloudberryKingdom::BackgroundFloater> __24 = boost::make_shared<CloudberryKingdom::BackgroundFloater>();
		__24->Name = std::wstring( L"sea_rock_4" );
		__24->MyQuad->Quad_Renamed.MyEffect = Tools::BasicEffect;
		__24->MyQuad->Quad_Renamed.ExtraTexture1 = 0;
		__24->MyQuad->Quad_Renamed.ExtraTexture2 = 0;
		__24->MyQuad->Quad_Renamed._MyTexture = Tools::Texture( std::wstring( L"sea_rock_4" ) );
		__24->MyQuad->Quad_Renamed.MySetColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__24->MyQuad->Quad_Renamed.PremultipliedColor = Color( static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ), static_cast<unsigned char>( 255 ) );
		__24->MyQuad->Quad_Renamed.BlendAddRatio = 0;

		__24->MyQuad->Base = BasePoint( 220.506f, 0.f, 0.f, 162.2992f, 4206.418f, -2972.248f );

		__24->uv_speed = Vector2( 0, 0 );
		__24->uv_offset = Vector2( 0, 0 );
		__24->Data = PhsxData( 4206.418f, -2972.248f, 0.f, 0.f, 0.f, 0.f );
		__24->StartData = PhsxData( 4206.418f, -2972.248f, 0.f, 0.f, 0.f, 0.f );
		__13->Floaters.push_back( __24 );



		__13->Parallax = 0.3f;
		__13->DoPreDraw = false;
		b->MyCollection->Lists.push_back( __13 );

		b->Light = 1;

		b->BL = Vector2( -100000.f, -10000.f );
		b->TR = Vector2( 100000.f, 10000.f );
	}

	int Background::GetGuid()
	{
		if ( GuidCounter <= 0 )
			GuidCounter = 1;

		return GuidCounter++;
	}

	const boost::shared_ptr<Rand> &Background::getRnd() const
	{
		return MyLevel->getRnd();
	}

	void Background::Release()
	{
		MyLevel.reset();
	}

	void Background::Reset()
	{
		if ( MyCollection == 0 )
			return;

		MyCollection->Reset();
	}

	boost::shared_ptr<Background> Background::UseCode( const boost::shared_ptr<BackgroundTemplate> &template_Renamed, const boost::shared_ptr<Background> &b )
	{
		b->MyCollection->Lists.clear();

		template_Renamed->Code( b );

		b->SetLevel( b->MyLevel );
		b->SetBackground( b );
		b->Reset();

		return b;
	}

	boost::shared_ptr<Background> Background::Get( const std::wstring &name )
	{
		return BackgroundType::NameLookup[ name ]->MakeInstanceOf();
	}

	boost::shared_ptr<Background> Background::Get( const boost::shared_ptr<BackgroundTemplate> &Type )
	{
		return Type->MakeInstanceOf();
	}

	Background::Background()
	{
		InitializeInstanceFields();
		Tools::QDrawer->setGlobalIllumination( 1 );
	}

	void Background::Init( const boost::shared_ptr<Level> &level )
	{
	}

	void Background::Move( Vector2 shift )
	{
		OffsetOffset -= shift;

		if ( MyCollection != 0 )
			MyCollection->Move( shift );

		TR += shift;
		BL += shift;
	}

	void Background::SetLevel( const boost::shared_ptr<Level> &level )
	{
		MyLevel = level;

		if ( MyCollection != 0 )
			MyCollection->SetLevel( level );
	}

	void Background::SetBackground( const boost::shared_ptr<Background> &b )
	{
		if ( MyCollection != 0 )
			MyCollection->SetBackground( b );
	}

	void Background::Absorb( const boost::shared_ptr<Background> &background )
	{
		if ( MyCollection != 0 && background->MyCollection != 0 )
			MyCollection->Absorb( background->MyCollection );
	}

	void Background::Clear()
	{
		boost::shared_ptr<FloatRectangle> rect = boost::make_shared<FloatRectangle>();
		rect->TR = TR + Vector2( 10000, 10000 );
		rect->BL = BL - Vector2( 10000, 10000 );
		Clear( rect );
	}

	void Background::Clear( const boost::shared_ptr<FloatRectangle> &Area )
	{
		if ( MyCollection != 0 )
			MyCollection->Clear( Area );
	}

	void Background::DrawTest()
	{
		boost::shared_ptr<Camera> Cam = Tools::getCurCamera();

		if ( GreenScreen )
		{
			TestQuad->Quad_Renamed.SetColor( Color( Vector3( 0, 1, 0 ) ) );
			TestQuad->setTextureName( std::wstring( L"White" ) );
			TestQuad->FullScreen( Cam );
		}
		else
		{
			TestQuad->Quad_Renamed.SetColor( Color( Vector3( 1, 1, 1 ) ) );

			if ( TestTexture == 0 )
			{
				//TestTexture = Tools.Texture("BGPlain");
				TestTexture = Tools::Texture( std::wstring( L"11 hill_4" ) );
			}
			TestQuad->Quad_Renamed.setMyTexture( TestTexture );

			TestQuad->Quad_Renamed.SetColor( ColorHelper::GrayColor( .825f ) );
			TestQuad->FullScreen( Cam );
			TestQuad->ScaleXToMatchRatio();
		}

		Cam->SetVertexCamera();

		TestQuad->Draw();
	}

	void Background::Draw()
	{
		Tools::QDrawer->setGlobalIllumination( MyGlobalIllumination );
	}

	void Background::DrawForeground()
	{
	}

	void Background::DimAll( float dim )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<BackgroundFloaterList> >::const_iterator c = MyCollection->Lists.begin(); c != MyCollection->Lists.end(); ++c )
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
			for ( std::vector<boost::shared_ptr<BackgroundFloater> >::const_iterator fl = ( *c )->Floaters.begin(); fl != ( *c )->Floaters.end(); ++fl )
			{
				Vector4 clr = ( *fl )->MyQuad->Quad_Renamed.MySetColor.ToVector4();
				clr *= dim;
				clr.W = ( *fl )->MyQuad->Quad_Renamed.MySetColor.ToVector4().W;
				( *fl )->MyQuad->Quad_Renamed.SetColor( clr );
			}
	}

	void Background::Save( const std::wstring &path )
	{
		// FIXME: Implement this; maybe?
		/*boost::shared_ptr<System::IO::FileStream> stream = File->Open( path, FileMode::OpenOrCreate, FileAccess::Write, FileShare::None );
		boost::shared_ptr<StreamWriter> writer = boost::make_shared<StreamWriter>( stream );

		Write( writer );

		writer->Close();
		stream->Close();*/
	}

	void Background::Load( const std::wstring &path )
	{
		// FIXME: Implement this; maybe?
		/*Tools::UseInvariantCulture();
		boost::shared_ptr<System::IO::FileStream> stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
		boost::shared_ptr<StreamReader> reader = boost::make_shared<StreamReader>( stream );

		Read( reader );

		reader->Close();
		stream->Close();*/
	}

	void Background::SetWeatherIntensity( float Intensity )
	{
		// Mod snow
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<BackgroundFloaterList> >::const_iterator l = MyCollection->Lists.begin(); l != MyCollection->Lists.end(); ++l )
			if ( ( *l )->Name.find( std::wstring( L"Snow" ) ) != std::wstring::npos )
			{
				( *l )->Show = true;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
				for ( std::vector<boost::shared_ptr<BackgroundFloater> >::const_iterator f = ( *l )->Floaters.begin(); f != ( *l )->Floaters.end(); ++f )
				{
					( *f )->MyQuad->setAlpha( ( *f )->MyQuad->getAlpha() * Intensity );
					( *f )->uv_speed *= 1;
				}
			}

		// Mod rain
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<boost::shared_ptr<BackgroundFloaterList> >::const_iterator l = MyCollection->Lists.begin(); l != MyCollection->Lists.end(); ++l )
			if ( ( *l )->Name.find( std::wstring( L"Rain" ) ) != std::wstring::npos )
			{
				( *l )->Show = true;
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
				for ( std::vector<boost::shared_ptr<BackgroundFloater> >::const_iterator f = ( *l )->Floaters.begin(); f != ( *l )->Floaters.end(); ++f )
				{
					( *f )->MyQuad->setAlpha( ( *f )->MyQuad->getAlpha() * Intensity );
					( *f )->uv_speed *= 1;
				}
			}
	}

	void Background::InitializeInstanceFields()
	{
		GuidCounter = 0;
		MyGlobalIllumination = 1;
		AllowLava = true;
		Wind = Vector2();
		OffsetOffset = Vector2();
		Light = 1;
	}
}
