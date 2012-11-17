#include "CloudberryKingdom.h"

#include <Content/Texture.h>
#include <Content/Wad.h>
#include <Core.h>
#include <cstdlib>
#include <Graphics/QuadDrawer.h>
#include <Graphics/TextDrawer.h>
#include <Graphics/Types.h>
#include <Utility/Log.h>
#include <vector>

//#include <cafe/pad.h>

/*static void ConnectCallback( s32 chan, s32 reason )
{
	if( reason >= 0 )
		WPADSetDataFormat( chan, WPAD_FMT_CORE );
}*/

void CloudberryKingdomWrapper::Initialize()
{
	std::vector< std::string > paths;

	for( size_t i = 0; i < paths.size(); ++i )
		CONTENT->Load< Texture >( paths[ i ] );

	/*PADInit();
	WPADInit();

	for( int i = 0; i < WPAD_MAX_CONTROLLERS; i++ )
		WPADSetConnectCallback( i, ConnectCallback );*/
}

void CloudberryKingdomWrapper::Update()
{
	/*PADStatus status[ PAD_MAX_CONTROLLERS ];
	memset( status, 0, sizeof( status ) );

	for( int i = 0; i < WPAD_MAX_CONTROLLERS; i++ )
	{
		u32 type;
		s32 status = WPADProbe( i, &type );

		if( status != WPAD_ERR_NO_CONTROLLER )
		{
			WPADStatus      cr;
			WPADFSStatus    fs;
			WPADCLStatus    cl;

			u16 button;
			WPADRead( i, &cr );

			if( cr.err == WPAD_ERR_NONE
				|| cr.err == WPAD_ERR_CORRUPTED )
			{
			}
		}
	}*/

	/*PADStatus status[ PAD_MAX_CONTROLLERS ];
	memset( status, 0, sizeof( status ) );
	PADRead( status );
	static Vector2 textPos( 0, 0 );

	for( int i = 0; i < PAD_MAX_CONTROLLERS; ++i )
	{
		if( status[ i ].button & PAD_BUTTON_LEFT
			|| status[ i ].stickX < -64
			|| status[ i ].substickX < -64)
			textPos += Vector2( -10, 0 );
		if( status[ i ].button & PAD_BUTTON_RIGHT
			|| status[ i ].stickX >= 64
			|| status[ i ].substickX >= 64)
			textPos += Vector2( 10, 0 );
		if( status[ i ].button & PAD_BUTTON_UP
			|| status[ i ].stickY >= 64
			|| status[ i ].substickY >= 64)
			textPos += Vector2( 0, -10 );
		if( status[ i ].button & PAD_BUTTON_DOWN
			|| status[ i ].stickY < -64
			|| status[ i ].substickY < -64 )
			textPos += Vector2( 0, 10 );
	}*/

	Vector2 textPos( 0 );

	ResourcePtr< Texture > texture = CONTENT->Load< Texture >( "Art/Bob/Bob_Trimmed/Bob_Run_0001.png" );
	ResourcePtr< Texture > background = CONTENT->Load< Texture >( "Art/Title/Title_Screen.png" );
	ResourcePtr< Texture > title = CONTENT->Load< Texture >( "Art/Title/Title.png" );

	SimpleQuad quad;
	quad.Color = Vector4( 1 );
	quad.V[ 0 ] = Vector2( 0, 0 );
	quad.V[ 1 ] = Vector2( 0, 720 );
	quad.V[ 2 ] = Vector2( 1280, 720 );
	quad.V[ 3 ] = Vector2( 1280, 0 );

	quad.T[ 0 ] = Vector2( 0, 0 );
	quad.T[ 1 ] = Vector2( 0, 1 );
	quad.T[ 2 ] = Vector2( 1, 1 );
	quad.T[ 3 ] = Vector2( 1, 0 );

	// Draw background.
	quad.Diffuse = background;
	QUAD_DRAWER->Draw( quad );

	// Draw title.
	quad.Diffuse = title;
	QUAD_DRAWER->Draw( quad );

	TEXT_DRAWER->Draw( "Game Over", textPos );
}
