#include <global_header.h>

#include "Hacks/String.h"
#include "Hacks/Parse.h"

#include "Hacks/NET/FileStream.h"
#include "Hacks/NET/Path.h"

#include <MasterHack.h>
#include <Utility/Log.h>

namespace CloudberryKingdom
{

	boost::shared_ptr<ObjectClass> Prototypes::LoadAnimObj = 0;

	void Prototypes::LoadAnimation( const std::wstring &path )
	{
		//if (!path.Contains("double")) return;
		//if (path.Contains("double")) return;
		if ( path.find( std::wstring( L"bob_v2_trimmed" ) ) == std::string::npos )
			return;

		Tools::UseInvariantCulture();
		/*boost::shared_ptr<FileStream> rstream = File->Open( std::wstring( L"Content/Objects/TigarBob.smo" ), FileMode::Open, FileAccess::Read, FileShare::None );
		boost::shared_ptr<BinaryReader> rreader = boost::make_shared<FileBinaryReader>( rstream, Encoding::UTF8 );*/
		boost::shared_ptr<BinaryReader> rreader = boost::make_shared<FileBinaryReader>( std::wstring( L"Content/Objects/TigarBob.smo" ) );
		boost::shared_ptr<ObjectClass> obj = boost::make_shared<ObjectClass>( Tools::QDrawer, Tools::Device, Tools::Device->PP, 100, 100, Tools::BasicEffect, Tools::TextureWad->FindByName( std::wstring( L"White" ) ) );
		ObjectClass_PostConstruct( obj, Tools::QDrawer, Tools::Device, Tools::Device->PP, 100, 100, Tools::BasicEffect, Tools::TextureWad->FindByName( std::wstring( L"White" ) ) );
		obj->ReadFile( rreader, Tools::EffectWad, Tools::TextureWad );
		rreader->Close();
		//rstream->Close();

		LoadAnimObj = obj;

		SetTigarLoaded( obj );
		obj->ParentQuad->Scale( Vector2( 260, 260 ) );

		bool BrandNew = false;



		// Find path
		Tools::UseInvariantCulture();
		boost::shared_ptr<FileStream> stream = 0;
		std::wstring original_path = path;
		// FIXME: Find actual path.
		/*try
		{
			stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
		}
		catch ( ... )
		{
			try
			{
				path = Path::Combine( Globals::ContentDirectory, original_path );
				stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
			}
			catch ( ... )
			{
				try
				{
					path = Path::Combine( Globals::ContentDirectory, Path::Combine( std::wstring( L"DynamicLoad" ), original_path ) );
					stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
				}
				catch ( ... )
				{
					Tools::Log( Format( _T( "Attempting to load a .anim file. Path <{0}> not found." ) ) );
					return;
				}
			}
		}*/

		boost::shared_ptr<ObjectClass> p;
		if ( BrandNew )
		{
			p = MakeObj();
			p->LoadingRunSpeed = .85f;
			p->ParentQuad->Scale( Vector2( 260, 260 ) );
			p->ParentQuad->MyEffect = Tools::BasicEffect;
		}
		else
		{
			p = obj;
		}

		p->Play = true;
		for ( std::vector<boost::shared_ptr<BaseQuad> >::const_iterator quad = p->QuadList.begin(); quad != p->QuadList.end(); ++quad )
			( *quad )->MyDrawOrder = ObjectDrawOrder_AFTER_OUTLINE;

		boost::shared_ptr<CloudberryKingdom::BaseQuad> h = p->FindQuad( std::wstring( L"Head" ) );
		h->Show = false;

		boost::shared_ptr<CloudberryKingdom::BaseQuad> q = p->FindQuad( std::wstring( L"MainQuad" ) );
		q->MyEffect = Tools::BasicEffect;
		q->MyDrawOrder = ObjectDrawOrder_AFTER_OUTLINE;
		q->SetColor( Color::White );
		boost::shared_ptr<Quad> _quad = boost::dynamic_pointer_cast<Quad>( q );
		q->TextureAnim = boost::make_shared<AnimationData_Texture>();
		q->TextureAnim->Anims = std::vector<OneAnim_Texture>( 20 );

		boost::shared_ptr<std::map<std::wstring, int> > ToAnim = boost::make_shared<std::map<std::wstring, int> >();
		(*ToAnim)[ std::wstring( L"Stand" ) ] = 0;
		(*ToAnim)[ std::wstring( L"Run" ) ] = 1;
		(*ToAnim)[ std::wstring( L"Jump" ) ] = 2;
		(*ToAnim)[ std::wstring( L"DoubleJump" ) ] = 29;
		(*ToAnim)[ std::wstring( L"Fall" ) ] = 3;
		(*ToAnim)[ std::wstring( L"Duck" ) ] = 4;
		(*ToAnim)[ std::wstring( L"Turn" ) ] = 5;

		(*ToAnim)[ std::wstring( L"Wheel" ) ] = 25;
		(*ToAnim)[ std::wstring( L"Bouncy" ) ] = 24;
		(*ToAnim)[ std::wstring( L"Jump2" ) ] = 29;
		(*ToAnim)[ std::wstring( L"Flip" ) ] = 16;
		(*ToAnim)[ std::wstring( L"Wave" ) ] = 13;
		(*ToAnim)[ std::wstring( L"Box_Stand" ) ] = 6;
		(*ToAnim)[ std::wstring( L"Box_Jump" ) ] = 7;
		(*ToAnim)[ std::wstring( L"Box_Duck" ) ] = 8;

		LoadAnimObj = p;

		boost::shared_ptr<StreamReader> reader = boost::make_shared<StreamReader>( stream );

		std::wstring line;
		Vector2 shift = Vector2();
		float scale = 1;

		line = reader->ReadLine();
		while ( line != std::wstring( L"" ) )
		{
			std::vector<std::wstring> bits = Tools::GetBitsFromLine( line );

			if ( bits.size() > 1 )
			{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
				std::wstring name = bits[ 0 ];

				// Try to load line as an animation
				if ( ToAnim->find( name ) != ToAnim->end() )
				{
					int anim = (*ToAnim)[ name ];

					// Name, file, start frame, end frame
					std::wstring root = bits[ 1 ];
					int start_frame = 0; ParseInt( bits[ 2 ], start_frame );
					int end_frame = 0; ParseInt( bits[ 3 ], end_frame );

					// Speed or frame length
					bool _use_speed = false;
					int frame_length = 1;
					float speed = 1;
					if ( bits[ 4 ] == std::wstring( L"speed" ) )
					{
						ParseFloat( bits[ 5 ], speed );
						_use_speed = true;
					}
					else
						ParseInt( bits[ 4 ], frame_length );

					// Reverse
					bool reverse = false;
					if ( std::find( bits.begin(), bits.end(), std::wstring( L"reverse" ) ) != bits.end() )
						reverse = true;

					q->TextureAnim->ClearAnim( anim );

					//if (name.Contains("ounc")) Tools::Write("!");

					int num_frames = end_frame > start_frame ? end_frame - start_frame + 1 : start_frame - end_frame + 1;
					for ( int i = 0; i < num_frames; i++ )
					{
						int frame = end_frame > start_frame ? start_frame + i : start_frame - i;

						// Get the texture for this frame.
						boost::shared_ptr<EzTexture> texture = Tools::Texture( Format( _T( "%ls_%d" ), root.c_str(), frame ) );
						if ( texture == Tools::TextureWad->DefaultTexture )
							texture = Tools::Texture( Format( _T( "%ls_0000%d" ), root.c_str(), frame ) );
						if ( texture == Tools::TextureWad->DefaultTexture )
							texture = Tools::Texture( Format( _T( "%ls_000%d" ), root.c_str(), frame ) );
						if ( texture == Tools::TextureWad->DefaultTexture )
							texture = Tools::Texture( Format( _T( "%ls_00%d" ), root.c_str(), frame ) );
						if ( texture == Tools::TextureWad->DefaultTexture )
							texture = Tools::Texture( Format( _T( "%ls_0%d" ), root.c_str(), frame ) );

						// Record object quad positions
						int anim_to_mimick = 0;
						if ( anim == 4 )
							anim_to_mimick = 4;
						p->Read_NoTexture( anim_to_mimick, 0 );

						//if (BrandNew)
						if ( true )
						{
							_quad->Corner[ 0 ]->RelPos = Vector2( -1, 1 );
							_quad->Corner[ 1 ]->RelPos = Vector2( 1, 1 );
							_quad->Corner[ 2 ]->RelPos = Vector2( -1, -1 );
							_quad->Corner[ 3 ]->RelPos = Vector2( 1, -1 );
							_quad->xAxis->RelPos = Vector2( 1, 0 );
							_quad->yAxis->RelPos = Vector2( 0, 1 );

							//_quad.xAxis.RelPos.X = _quad.yAxis.RelPos.Y * (float)texture.Width / (float)texture.Height;
							//if (reverse)
							//    _quad.xAxis.RelPos.X = -System.Math.Abs(_quad.xAxis.RelPos.X);

							_quad->Center->RelPos = shift / scale;
							_quad->xAxis->RelPos.X = scale * static_cast<float>( texture->Width ) / static_cast<float>( texture->Height );
							if ( reverse )
								_quad->xAxis->RelPos.X = -fabs( _quad->xAxis->RelPos.X );
							_quad->yAxis->RelPos.Y = scale;

							if ( BrandNew )
								p->Record( anim, i, true );
							else
								q->Record( anim, i, true );
						}
						else
							q->Record( anim, i, true );

						p->AnimLength[ anim ] = num_frames - 1;

						// Record the texture
						q->TextureAnim->AddFrame( texture, anim );
					}

					if ( BrandNew )
					{
						_quad->Center->RelPos += shift / scale;

						_quad->Corner[ 0 ]->RelPos = Vector2( -1, 1 );
						_quad->Corner[ 1 ]->RelPos = Vector2( 1, 1 );
						_quad->Corner[ 2 ]->RelPos = Vector2( -1, -1 );
						_quad->Corner[ 3 ]->RelPos = Vector2( 1, -1 );

						_quad->xAxis->RelPos = Vector2( scale, 0 );
						_quad->yAxis->RelPos = Vector2( 0, scale );

						_quad->ModifyAllRecords( 0, 0, ChangeMode_ALL );
						p->Record( 0, 0, true );
					}

					if ( _use_speed )
						p->AnimSpeed[ anim ] = speed;
					else
						p->AnimSpeed[ anim ] = 1.f / frame_length;
				}
				else
//C# TO C++ CONVERTER NOTE: The following 'switch' operated on a string variable and was converted to C++ 'if-else' logic:
//				switch (bits[0])
//ORIGINAL LINE: case "Scale":
				if ( bits[ 0 ] == std::wstring( L"Scale" ) )
				{
						 ParseFloat( bits[ 1 ], scale );

				}
//ORIGINAL LINE: case "Shift":
				else if ( bits[ 0 ] == std::wstring( L"Shift" ) )
				{
						shift = Tools::ParseToVector2( bits[ 1 ], bits[ 2 ] );

				}
				else
				{
						Tools::Break();
						//Tools::ReadLineToObj(BobPhsxMario.Instance, bits);
				}
			}

			line = reader->ReadLine();
		}

		// Shift
		p->Read( 0, 0 );

		//if (BrandNew)
		//{
		//    _quad.Center.RelPos += shift / scale;

		//    _quad.Corner[0].RelPos = new Vector2(-1, 1);
		//    _quad.Corner[1].RelPos = new Vector2(1, 1);
		//    _quad.Corner[2].RelPos = new Vector2(-1, -1);
		//    _quad.Corner[3].RelPos = new Vector2(1, -1);

		//    _quad.xAxis.RelPos = new Vector2(scale, 0);
		//    _quad.yAxis.RelPos = new Vector2(0, scale);

		//    _quad.ModifyAllRecords(0, 0, ChangeMode.All);
		//    p.Record(0, 0, true);
		//}

		reader->Close();
		stream->Close();

		p->Read( 0, 0 );
		p->PlayUpdate( 0 );

		// Use object
		if ( Tools::CurLevel != 0 && Tools::CurLevel->Bobs.size() > 0 ) // && Tools::CurLevel.DefaultHeroType == BobPhsxNormal.Instance)
		{
			Tools::CurLevel->Bobs[ 0 ]->PlayerObject = boost::make_shared<ObjectClass>( p, false, false );
			ObjectClass_PostConstruct_3params( Tools::CurLevel->Bobs[ 0 ]->PlayerObject, p, false, false );
			std::queue<boost::shared_ptr<AnimQueueEntry> > empty;
			std::swap( Tools::CurLevel->Bobs[ 0 ]->PlayerObject->AnimQueue, empty );
			Tools::CurLevel->Bobs[ 0 ]->PlayerObject->EnqueueAnimation( 0, 0, true );
			//Tools::CurLevel.Bobs[0].MyPhsx.Prototype.PlayerObject = p;
			//BobPhsxNormal.Instance.Prototype.PlayerObject = p;
		}
		else
			Hero = p;



		////return;

		// Save object
	#if defined(DEBUG)
		/*Tools::UseInvariantCulture();
		boost::shared_ptr<FileStream> fstream = File->Open( std::wstring( L"C:/Users/Ezra/Desktop/TigarBob.smo" ), FileMode::Create, FileAccess::Write, FileShare::None );
		boost::shared_ptr<BinaryWriter> writer = boost::make_shared<BinaryWriter>( fstream, Encoding::UTF8 );
		p->Write( writer );
		writer->Close();
		fstream->Close();*/
	#endif
	}

	void Prototypes::SetTigarLoaded( const boost::shared_ptr<ObjectClass> &obj )
	{
		obj->LoadingRunSpeed = .85f;
		obj->CapeThickness = 8;
		obj->p1_Left = Vector2( -64, -64 );
		obj->p2_Left = Vector2( -24, -42 );
		obj->p1_Right = obj->p1_Left;
		obj->p1_Right.X *= -1;
		obj->p2_Right = obj->p2_Left;
		obj->p2_Right.X *= -1;

		boost::shared_ptr<CloudberryKingdom::BaseQuad> mq = obj->FindQuad( std::wstring( L"MainQuad" ) );
		if ( mq != 0 )
			mq->MyEffect = Tools::EffectWad->FindByName( std::wstring( L"Hsl_Green" ) );
		boost::shared_ptr<CloudberryKingdom::BaseQuad> rp = obj->FindQuad( std::wstring( L"Rocket" ) );
		if ( rp != 0 )
			rp->MyEffect = Tools::EffectWad->FindByName( std::wstring( L"Hsl" ) );
		obj->UpdateEffectList();
	}

	boost::shared_ptr<ObjectClass> Prototypes::MakeObj()
	{
		std::wstring path = std::wstring( L"Objects/SpriteHeroTemplate.smo" );
		//var path = "Objects/stickman.smo";
		path = Path::Combine( Globals::ContentDirectory, path );

		boost::shared_ptr<CloudberryKingdom::ObjectClass> obj = LoadObject( path );
		return obj;
	}

	boost::shared_ptr<FlyingBlob> Prototypes::FlyingBlobObj;
	boost::shared_ptr<FlyingBlob> Prototypes::goomba;
	std::map<boost::shared_ptr<BobPhsx>, boost::shared_ptr<Bob> > Prototypes::bob;
	boost::shared_ptr<Spike> Prototypes::SpikeObj;
	boost::shared_ptr<SimpleObject> Prototypes::GhostBlockObj, Prototypes::CheckpointObj, Prototypes::Door_Renamed, Prototypes::GrassDoor, Prototypes::ArrowObj;
	boost::shared_ptr<ObjectClass> Prototypes::Hero;
	boost::shared_ptr<ObjectClass> Prototypes::PlaceBob;

	boost::shared_ptr<SimpleObject> Prototypes::LoadSimple( const std::wstring &file )
	{
		boost::shared_ptr<ObjectClass> SourceObject;
		Tools::UseInvariantCulture();
		/*boost::shared_ptr<FileStream> stream = File->Open( file, FileMode::Open, FileAccess::Read, FileShare::None );
		boost::shared_ptr<BinaryReader> reader = boost::make_shared<FileBinaryReader>( stream, Encoding::UTF8 );*/
		boost::shared_ptr<BinaryReader> reader = boost::make_shared<FileBinaryReader>( file );
		SourceObject = boost::make_shared<ObjectClass>( Tools::QDrawer, Tools::Device, Tools::Device->PP, 100, 100, Tools::EffectWad->FindByName( std::wstring( L"BasicEffect" ) ), Tools::TextureWad->FindByName( std::wstring( L"White" ) ) );
		ObjectClass_PostConstruct( SourceObject, Tools::QDrawer, Tools::Device, Tools::Device->PP, 100, 100, Tools::EffectWad->FindByName( std::wstring( L"BasicEffect" ) ), Tools::TextureWad->FindByName( std::wstring( L"White" ) ) );
		SourceObject->ReadFile( reader, Tools::EffectWad, Tools::TextureWad );
		reader->Close();
		//stream->Close();

		SourceObject->ConvertForSimple();
		return boost::make_shared<SimpleObject>( SourceObject );
	}

	boost::shared_ptr<ObjectClass> Prototypes::LoadObject( const std::wstring &file )
	{
		boost::shared_ptr<ObjectClass> obj;
		Tools::UseInvariantCulture();
		/*boost::shared_ptr<FileStream> stream = File->Open( file, FileMode::Open, FileAccess::Read, FileShare::None );
		boost::shared_ptr<BinaryReader> reader = boost::make_shared<FileBinaryReader>( stream, Encoding::UTF8 );*/
		boost::shared_ptr<BinaryReader> reader = boost::make_shared<FileBinaryReader>( file );
		obj = boost::make_shared<ObjectClass>( Tools::QDrawer, Tools::Device, Tools::Device->PP, 100, 100, Tools::EffectWad->FindByName( std::wstring( L"BasicEffect" ) ), Tools::TextureWad->FindByName( std::wstring( L"White" ) ) );
		ObjectClass_PostConstruct( obj, Tools::QDrawer, Tools::Device, Tools::Device->PP, 100, 100, Tools::EffectWad->FindByName( std::wstring( L"BasicEffect" ) ), Tools::TextureWad->FindByName( std::wstring( L"White" ) ) );
		obj->ReadFile( reader, Tools::EffectWad, Tools::TextureWad );
		reader->Close();
		//stream->Close();

		return obj;
	}

	void Prototypes::LoadObjects()
	{
		Prototypes::CheckpointObj = Prototypes::LoadSimple( Path::Combine( Globals::ContentDirectory, std::wstring( L"Objects/FlyingCoin_v2.smo" ) ) );

		Prototypes::ArrowObj = Prototypes::LoadSimple( Path::Combine( Globals::ContentDirectory, std::wstring( L"Objects/Arrow.smo" ) ) );

		Prototypes::GhostBlockObj = Prototypes::LoadSimple( Path::Combine( Globals::ContentDirectory, std::wstring( L"Objects/GhostBlock.smo" ) ) );

		Prototypes::FlyingBlobObj = boost::make_shared<FlyingBlob>( Path::Combine( Globals::ContentDirectory, std::wstring( L"Objects/Blob.smo" ) ), Tools::EffectWad, Tools::TextureWad );
		Prototypes::FlyingBlobObj->getCore()->MyType = ObjectType_FLYING_BLOB;
		Vector2 BlobSize = Vector2( 1.11f, 1.11f );
		Prototypes::FlyingBlobObj->MyObject->Base.e1 *= BlobSize.X;
		Prototypes::FlyingBlobObj->MyObject->Base.e2 *= BlobSize.Y;

		Prototypes::SpikeObj = boost::make_shared<Spike>( Path::Combine( Globals::ContentDirectory, std::wstring( L"Objects/regular_spike.smo" ) ), Tools::EffectWad, Tools::TextureWad );

		// Create all the stickmen hero prototypes
		bob = std::map<boost::shared_ptr<BobPhsx> , boost::shared_ptr<Bob> >();
		boost::shared_ptr<Bob> NewBob;

		//// Bezier base object
		//NewBob = new Bob(Path.Combine(Globals.ContentDirectory, "Objects/stickman.smo"), Tools::EffectWad, Tools::TextureWad);
		//NewBob.MyObjectType = BobPhsxNormal.Instance;
		//NewBob.DrawOutline = true;
		//NewBob.CanHaveCape = true;
		//NewBob.PlayerObject.ParentQuad.MyEffect = Tools::BasicEffect;
		//NewBob.PlayerObject.FindQuad("Hat_FireHead").MyTexture = Fireball.FlameTexture;

		// Tigar base object
		std::wstring TigarBobPath = Path::Combine( Globals::ContentDirectory, std::wstring( L"Objects/TigarBob.smo" ) );
		NewBob = boost::make_shared<Bob>( TigarBobPath, Tools::EffectWad, Tools::TextureWad );
		NewBob->LoadFromFile( TigarBobPath, Tools::EffectWad, Tools::TextureWad, BobPhsxNormal::getInstance() );
		SetTigarLoaded( NewBob->PlayerObject );
		NewBob->IsSpriteBased = true;
		NewBob->MyObjectType = BobPhsxNormal::getInstance();
		NewBob->CanHaveCape = true;
		NewBob->PlayerObject->Linear = true;
		NewBob->PlayerObject->ParentQuad->MyEffect = Tools::BasicEffect;
		NewBob->PlayerObject->FindQuad( std::wstring( L"Hat_FireHead" ) )->MyTexture = Fireball::FlameTexture;

		// Classic Bob
		BobPhsxNormal::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxNormal::getInstance(), NewBob ) );

		// Invert
		BobPhsxInvert::getInstance()->Prototype = BobPhsxNormal::getInstance()->Prototype;
		bob.insert( std::make_pair( BobPhsxInvert::getInstance(), NewBob ) );

		// Time
		BobPhsxTime::getInstance()->Prototype = BobPhsxNormal::getInstance()->Prototype;
		bob.insert( std::make_pair( BobPhsxTime::getInstance(), NewBob ) );

		// Tiny Bob
		BobPhsxSmall::getInstance()->Prototype = BobPhsxNormal::getInstance()->Prototype;
		bob.insert( std::make_pair( BobPhsxSmall::getInstance(), NewBob ) );

		// Big
		BobPhsxBig::getInstance()->Prototype = BobPhsxNormal::getInstance()->Prototype;
		bob.insert( std::make_pair( BobPhsxBig::getInstance(), NewBob ) );

		// Phase
		BobPhsxScale::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxScale::getInstance(), NewBob ) );

		// Double Jump
		BobPhsxDouble::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxDouble::getInstance(), NewBob ) );

		// Rocket
		BobPhsxJetman::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxJetman::getInstance(), NewBob ) );

		// Bouncy
		NewBob = boost::make_shared<Bob>( BobPhsxNormal::getInstance(), false );
		Bob_PostConstruct( NewBob, BobPhsxNormal::getInstance(), false );
		NewBob->MyObjectType = BobPhsxBouncy::getInstance();
		NewBob->CanHaveCape = true;
		if ( !NewBob->IsSpriteBased )
			NewBob->PlayerObject->FindQuad( std::wstring( L"Bouncy" ) )->Show = true;

		BobPhsxBouncy::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxBouncy::getInstance(), NewBob ) );

		// Wheelie
		NewBob = boost::make_shared<Bob>( BobPhsxNormal::getInstance(), false );
		Bob_PostConstruct( NewBob, BobPhsxNormal::getInstance(), false );
		NewBob->MyObjectType = BobPhsxWheel::getInstance();
		NewBob->CanHaveCape = false;
		if ( !NewBob->IsSpriteBased )
			NewBob->PlayerObject->FindQuad( std::wstring( L"Wheel" ) )->Show = true;

		BobPhsxWheel::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxWheel::getInstance(), NewBob ) );

		// Hero in a Box
		NewBob = boost::make_shared<Bob>( BobPhsxNormal::getInstance(), false );
		Bob_PostConstruct( NewBob, BobPhsxNormal::getInstance(), false );
		NewBob->MyObjectType = BobPhsxBox::getInstance();
		if ( !NewBob->IsSpriteBased )
		{
			NewBob->PlayerObject->FindQuad( std::wstring( L"Box_Back" ) )->Show = true;
			NewBob->PlayerObject->FindQuad( std::wstring( L"Box_Front" ) )->Show = true;
			NewBob->PlayerObject->FindQuad( std::wstring( L"Leg_Left" ) )->Show = false;
			NewBob->PlayerObject->FindQuad( std::wstring( L"Leg_Right" ) )->Show = false;
		}

		BobPhsxBox::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxBox::getInstance(), NewBob ) );

		// Rocketbox
		NewBob = boost::make_shared<Bob>( BobPhsxBox::getInstance(), false );
		Bob_PostConstruct( NewBob, BobPhsxBox::getInstance(), false );
		NewBob->MyObjectType = BobPhsxBox::getInstance();
		if ( !NewBob->IsSpriteBased )
		{
			NewBob->PlayerObject->FindQuad( std::wstring( L"Wheel_Left" ) )->Show = true;
			NewBob->PlayerObject->FindQuad( std::wstring( L"Wheel_Right" ) )->Show = true;
		}

		BobPhsxRocketbox::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxRocketbox::getInstance(), NewBob ) );

		// Spaceship 
		std::wstring SpaceshipPath = Path::Combine( Globals::ContentDirectory, std::wstring( L"Objects/Spaceship.smo" ) );
		NewBob = boost::make_shared<Bob>( SpaceshipPath, Tools::EffectWad, Tools::TextureWad, BobPhsxSpaceship::getInstance(), false );
		NewBob->LoadFromFile( SpaceshipPath, Tools::EffectWad, Tools::TextureWad, BobPhsxSpaceship::getInstance() );
		NewBob->MyObjectType = BobPhsxSpaceship::getInstance();
		NewBob->PlayerObject->ParentQuad->Scale( Vector2( 3.5f, 3.5f ) );
		for ( std::vector<boost::shared_ptr<BaseQuad> >::const_iterator quad = NewBob->PlayerObject->QuadList.begin(); quad != NewBob->PlayerObject->QuadList.end(); ++quad )
			( *quad )->MyDrawOrder = ObjectDrawOrder_AFTER_OUTLINE;
		NewBob->CanHaveCape = false;
		NewBob->CanHaveHat = false;
		NewBob->PlayerObject->ParentQuad->MyEffect = Tools::BasicEffect;

		boost::shared_ptr<Quad> spaceship = boost::static_pointer_cast<Quad>( NewBob->PlayerObject->QuadList[ 1 ] );
		spaceship->MyTexture = Tools::Texture( std::wstring( L"Spaceship_Paper" ) );
		spaceship->Resize();
		NewBob->PlayerObject->QuadList[ 2 ]->Show = false;


		BobPhsxSpaceship::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxSpaceship::getInstance(), NewBob ) );

		BobPhsxTimeship::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxTimeship::getInstance(), NewBob ) );

		// Meat
		/*std::wstring MeatBoyPath = Path::Combine( Globals::ContentDirectory, std::wstring( L"Objects/meatboy.smo" ) );
		NewBob = boost::make_shared<Bob>( MeatBoyPath, Tools::EffectWad, Tools::TextureWad, BobPhsxMeat::getInstance(), true );
		NewBob->LoadFromFile( MeatBoyPath, Tools::EffectWad, Tools::TextureWad, BobPhsxMeat::getInstance() );
		NewBob->IsSpriteBased = false;
		NewBob->MyObjectType = BobPhsxMeat::getInstance();
		NewBob->PlayerObject->ParentQuad->Scale( Vector2( 2.75f, 2.75f ) );
		for ( std::vector<boost::shared_ptr<BaseQuad> >::const_iterator quad = NewBob->PlayerObject->QuadList.begin(); quad != NewBob->PlayerObject->QuadList.end(); ++quad )
			( *quad )->MyDrawOrder = ObjectDrawOrder_AFTER_OUTLINE;
		NewBob->CanHaveCape = true;
		NewBob->CanHaveHat = true;
		NewBob->PlayerObject->ParentQuad->MyEffect = Tools::BasicEffect;
		NewBob->PlayerObject->QuadList[ 0 ]->SetTexture( std::wstring( L"FallingBlock1" ), Tools::TextureWad );
		NewBob->PlayerObject->QuadList[ 1 ]->SetTexture( std::wstring( L"FallingBlock1" ), Tools::TextureWad );

		BobPhsxMeat::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxMeat::getInstance(), NewBob ) );*/


		// Freeplay Heroes
		//if (!(CloudberryKingdomGame.StartAsFreeplay && CloudberryKingdomGame.UseNewBob))
			CustomLevel_GUI::FreeplayHeroes = std::vector<boost::shared_ptr<BobPhsx> >( Bob::HeroTypes );

		// Associate the BobPhsx with each prototype
		for ( std::vector<boost::shared_ptr<BobPhsx> >::const_iterator HeroType = Bob::HeroTypes.begin(); HeroType != Bob::HeroTypes.end(); ++HeroType )
			Prototypes::bob[ *HeroType ]->MyHeroType = *HeroType;

		// Place bob
		//PlaceBob = LoadObject(Path.Combine(Globals.ContentDirectory, "Objects/place_bob.smo"));

		Resources::ResourceLoadedCountRef->MyFloat++;

		ArcadeMenu::StaticInit();
	}
}
