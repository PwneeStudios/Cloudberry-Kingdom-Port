#include <global_header.h>




namespace CloudberryKingdom
{

std::shared_ptr<ObjectClass> Prototypes::LoadAnimObj = 0;

	void Prototypes::LoadAnimation( const std::wstring &path )
	{
		//if (!path.Contains("double")) return;
		//if (path.Contains("double")) return;
		if ( !path.find( _T( "bob_v2_trimmed" ) ) != std::string::npos )
			return;

		Tools::UseInvariantCulture();
		/*std::shared_ptr<FileStream> rstream = File->Open( _T( "Content\\Objects\\TigarBob.smo" ), FileMode::Open, FileAccess::Read, FileShare::None );
		std::shared_ptr<BinaryReader> rreader = std::make_shared<BinaryReader>( rstream, Encoding::UTF8 );*/
		std::shared_ptr<BinaryReader> rreader = std::make_shared<BinaryReader>( _T( "Content\\Objects\\TigarBob.smo" ) );
		std::shared_ptr<ObjectClass> obj = std::make_shared<ObjectClass>( Tools::QDrawer, Tools::Device, Tools::Device->PP, 100, 100, Tools::BasicEffect, Tools::TextureWad->FindByName( _T( "White" ) ) );
		obj->ReadFile( rreader, Tools::EffectWad, Tools::TextureWad );
		rreader->Close();
		//rstream->Close();

		LoadAnimObj = obj;

		SetTigarLoaded( obj );
		obj->ParentQuad->Scale( Vector2( 260, 260 ) );

		bool BrandNew = false;



		// Find path
		Tools::UseInvariantCulture();
		std::shared_ptr<FileStream> stream = 0;
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
					path = Path::Combine( Globals::ContentDirectory, Path::Combine( _T( "DynamicLoad" ), original_path ) );
					stream = File->Open( path, FileMode::Open, FileAccess::Read, FileShare::None );
				}
				catch ( ... )
				{
					Tools::Log( Format( _T( "Attempting to load a .anim file. Path <{0}> not found." ) ) );
					return;
				}
			}
		}*/

		std::shared_ptr<ObjectClass> p;
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
		for ( std::vector<std::shared_ptr<BaseQuad> >::const_iterator quad = p->QuadList.begin(); quad != p->QuadList.end(); ++quad )
			( *quad )->MyDrawOrder = ObjectDrawOrder_AFTER_OUTLINE;

		std::shared_ptr<CloudberryKingdom::BaseQuad> h = p->FindQuad( _T( "Head" ) );
		h->Show = false;

		std::shared_ptr<CloudberryKingdom::BaseQuad> q = p->FindQuad( _T( "MainQuad" ) );
		q->MyEffect = Tools::BasicEffect;
		q->MyDrawOrder = ObjectDrawOrder_AFTER_OUTLINE;
		q->SetColor( Color::White );
		std::shared_ptr<Quad> _quad = std::dynamic_pointer_cast<Quad>( q );
		q->TextureAnim = std::make_shared<AnimationData_Texture>();
		q->TextureAnim->Anims = std::vector<OneAnim_Texture>( 20 );

		std::shared_ptr<std::map<std::wstring, int> > ToAnim = std::make_shared<std::map<std::wstring, int> >();
		(*ToAnim)[ _T( "Stand" ) ] = 0;
		(*ToAnim)[ _T( "Run" ) ] = 1;
		(*ToAnim)[ _T( "Jump" ) ] = 2;
		(*ToAnim)[ _T( "DoubleJump" ) ] = 29;
		(*ToAnim)[ _T( "Fall" ) ] = 3;
		(*ToAnim)[ _T( "Duck" ) ] = 4;
		(*ToAnim)[ _T( "Turn" ) ] = 5;

		(*ToAnim)[ _T( "Wheel" ) ] = 25;
		(*ToAnim)[ _T( "Bouncy" ) ] = 24;
		(*ToAnim)[ _T( "Jump2" ) ] = 29;
		(*ToAnim)[ _T( "Flip" ) ] = 16;
		(*ToAnim)[ _T( "Wave" ) ] = 13;
		(*ToAnim)[ _T( "Box_Stand" ) ] = 6;
		(*ToAnim)[ _T( "Box_Jump" ) ] = 7;
		(*ToAnim)[ _T( "Box_Duck" ) ] = 8;

		LoadAnimObj = p;

		std::shared_ptr<StreamReader> reader = std::make_shared<StreamReader>( stream );

		std::wstring line;
		Vector2 shift = Vector2();
		float scale = 1;

		line = reader->ReadLine();
		while ( line != _T( "" ) )
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
					int start_frame = ParseInt( bits[ 2 ] );
					int end_frame = ParseInt( bits[ 3 ] );

					// Speed or frame length
					bool _use_speed = false;
					int frame_length = 1;
					float speed = 1;
					if ( bits[ 4 ] == _T( "speed" ) )
					{
						speed = ParseFloat( bits[ 5 ] );
						_use_speed = true;
					}
					else
						frame_length = ParseInt( bits[ 4 ] );

					// Reverse
					bool reverse = false;
					if ( std::find( bits.begin(), bits.end(), _T("reverse") ) != bits.end() )
						reverse = true;

					q->TextureAnim->ClearAnim( anim );

					//if (name.Contains("ounc")) Tools.Write("!");

					int num_frames = end_frame > start_frame ? end_frame - start_frame + 1 : start_frame - end_frame + 1;
					for ( int i = 0; i < num_frames; i++ )
					{
						int frame = end_frame > start_frame ? start_frame + i : start_frame - i;

						// Get the texture for this frame.
						std::shared_ptr<EzTexture> texture = Tools::Texture( Format( _T( "{0}_{1}" ), root, frame ) );
						if ( texture == Tools::TextureWad->DefaultTexture )
							texture = Tools::Texture( Format( _T( "{0}_0000{1}" ), root, frame ) );
						if ( texture == Tools::TextureWad->DefaultTexture )
							texture = Tools::Texture( Format( _T( "{0}_000{1}" ), root, frame ) );
						if ( texture == Tools::TextureWad->DefaultTexture )
							texture = Tools::Texture( Format( _T( "{0}_00{1}" ), root, frame ) );
						if ( texture == Tools::TextureWad->DefaultTexture )
							texture = Tools::Texture( Format( _T( "{0}_0{1}" ), root, frame ) );

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
								_quad->xAxis->RelPos.X = -abs( _quad->xAxis->RelPos.X );
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
				if ( bits[ 0 ] == _T( "Scale" ) )
				{
						scale = ParseFloat( bits[ 1 ] );

				}
//ORIGINAL LINE: case "Shift":
				else if ( bits[ 0 ] == _T( "Shift" ) )
				{
						shift = Tools::ParseToVector2( bits[ 1 ], bits[ 2 ] );

				}
				else
				{
						Tools::Break();
						//Tools.ReadLineToObj(BobPhsxMario.Instance, bits);
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
		if ( Tools::CurLevel != 0 && Tools::CurLevel->Bobs.size() > 0 ) // && Tools.CurLevel.DefaultHeroType == BobPhsxNormal.Instance)
		{
			Tools::CurLevel->Bobs[ 0 ]->PlayerObject = std::make_shared<ObjectClass>( p, false, false );
			std::queue<std::shared_ptr<AnimQueueEntry> > empty;
			std::swap( Tools::CurLevel->Bobs[ 0 ]->PlayerObject->AnimQueue, empty );
			Tools::CurLevel->Bobs[ 0 ]->PlayerObject->EnqueueAnimation( 0, 0, true );
			//Tools.CurLevel.Bobs[0].MyPhsx.Prototype.PlayerObject = p;
			//BobPhsxNormal.Instance.Prototype.PlayerObject = p;
		}
		else
			Hero = p;



		////return;

		// Save object
	#if defined(DEBUG)
		Tools::UseInvariantCulture();
		std::shared_ptr<FileStream> fstream = File->Open( _T( "C:\\Users\\Ezra\\Desktop\\TigarBob.smo" ), FileMode::Create, FileAccess::Write, FileShare::None );
		std::shared_ptr<BinaryWriter> writer = std::make_shared<BinaryWriter>( fstream, Encoding::UTF8 );
		p->Write( writer );
		writer->Close();
		fstream->Close();
	#endif
	}

	void Prototypes::SetTigarLoaded( const std::shared_ptr<ObjectClass> &obj )
	{
		obj->LoadingRunSpeed = .85f;
		obj->CapeThickness = 8;
		obj->p1_Left = Vector2( -64, -64 );
		obj->p2_Left = Vector2( -24, -42 );
		obj->p1_Right = obj->p1_Left;
		obj->p1_Right.X *= -1;
		obj->p2_Right = obj->p2_Left;
		obj->p2_Right.X *= -1;

		std::shared_ptr<CloudberryKingdom::BaseQuad> mq = obj->FindQuad( _T( "MainQuad" ) );
		if ( mq != 0 )
			mq->MyEffect = Tools::EffectWad->FindByName( _T( "Hsl_Green" ) );
		std::shared_ptr<CloudberryKingdom::BaseQuad> rp = obj->FindQuad( _T( "Rocket" ) );
		if ( rp != 0 )
			rp->MyEffect = Tools::EffectWad->FindByName( _T( "Hsl" ) );
		obj->UpdateEffectList();
	}

	std::shared_ptr<ObjectClass> Prototypes::MakeObj()
	{
		std::wstring path = _T( "Objects\\SpriteHeroTemplate.smo" );
		//var path = "Objects\\stickman.smo";
		path = Path::Combine( Globals::ContentDirectory, path );

		std::shared_ptr<CloudberryKingdom::ObjectClass> obj = LoadObject( path );
		return obj;
	}

std::shared_ptr<FlyingBlob> Prototypes::FlyingBlobObj = 0;
std::shared_ptr<FlyingBlob> Prototypes::goomba = 0;
std::map<std::shared_ptr<BobPhsx> , std::shared_ptr<Bob> > Prototypes::bob;
std::shared_ptr<Spike> Prototypes::SpikeObj = 0;
std::shared_ptr<SimpleObject> GhostBlockObj, CheckpointObj, Door, GrassDoor, Prototypes::ArrowObj = 0;
std::shared_ptr<ObjectClass> Prototypes::Hero = 0;
std::shared_ptr<ObjectClass> Prototypes::PlaceBob = 0;

	std::shared_ptr<SimpleObject> Prototypes::LoadSimple( const std::wstring &file )
	{
		std::shared_ptr<ObjectClass> SourceObject;
		Tools::UseInvariantCulture();
		/*std::shared_ptr<FileStream> stream = File->Open( file, FileMode::Open, FileAccess::Read, FileShare::None );
		std::shared_ptr<BinaryReader> reader = std::make_shared<BinaryReader>( stream, Encoding::UTF8 );*/
		std::shared_ptr<BinaryReader> reader = std::make_shared<BinaryReader>( file );
		SourceObject = std::make_shared<ObjectClass>( Tools::QDrawer, Tools::Device, Tools::Device->PP, 100, 100, Tools::EffectWad->FindByName( _T( "BasicEffect" ) ), Tools::TextureWad->FindByName( _T( "White" ) ) );
		SourceObject->ReadFile( reader, Tools::EffectWad, Tools::TextureWad );
		reader->Close();
		//stream->Close();

		SourceObject->ConvertForSimple();
		return std::make_shared<SimpleObject>( SourceObject );
	}

	std::shared_ptr<ObjectClass> Prototypes::LoadObject( const std::wstring &file )
	{
		std::shared_ptr<ObjectClass> obj;
		Tools::UseInvariantCulture();
		/*std::shared_ptr<FileStream> stream = File->Open( file, FileMode::Open, FileAccess::Read, FileShare::None );
		std::shared_ptr<BinaryReader> reader = std::make_shared<BinaryReader>( stream, Encoding::UTF8 );*/
		std::shared_ptr<BinaryReader> reader = std::make_shared<BinaryReader>( file );
		obj = std::make_shared<ObjectClass>( Tools::QDrawer, Tools::Device, Tools::Device->PP, 100, 100, Tools::EffectWad->FindByName( _T( "BasicEffect" ) ), Tools::TextureWad->FindByName( _T( "White" ) ) );
		obj->ReadFile( reader, Tools::EffectWad, Tools::TextureWad );
		reader->Close();
		//stream->Close();

		return obj;
	}

	void Prototypes::LoadObjects()
	{
		Prototypes::CheckpointObj = Prototypes::LoadSimple( Path::Combine( Globals::ContentDirectory, _T( "Objects\\FlyingCoin_v2.smo" ) ) );

		Prototypes::ArrowObj = Prototypes::LoadSimple( Path::Combine( Globals::ContentDirectory, _T( "Objects\\Arrow.smo" ) ) );

		Prototypes::GhostBlockObj = Prototypes::LoadSimple( Path::Combine( Globals::ContentDirectory, _T( "Objects\\GhostBlock.smo" ) ) );

		Prototypes::FlyingBlobObj = std::make_shared<FlyingBlob>( Path::Combine( Globals::ContentDirectory, _T( "Objects\\Blob.smo" ) ), Tools::EffectWad, Tools::TextureWad );
		Prototypes::FlyingBlobObj->getCore()->MyType = ObjectType_FLYING_BLOB;
		Vector2 BlobSize = Vector2( 1.11f, 1.11f );
		Prototypes::FlyingBlobObj->MyObject->Base.e1 *= BlobSize.X;
		Prototypes::FlyingBlobObj->MyObject->Base.e2 *= BlobSize.Y;

		Prototypes::SpikeObj = std::make_shared<Spike>( Path::Combine( Globals::ContentDirectory, _T( "Objects\\regular_spike.smo" ) ), Tools::EffectWad, Tools::TextureWad );

		// Create all the stickmen hero prototypes
		bob = std::map<std::shared_ptr<BobPhsx> , std::shared_ptr<Bob> >();
		std::shared_ptr<Bob> NewBob;

		//// Bezier base object
		//NewBob = new Bob(Path.Combine(Globals.ContentDirectory, "Objects\\stickman.smo"), Tools.EffectWad, Tools.TextureWad);
		//NewBob.MyObjectType = BobPhsxNormal.Instance;
		//NewBob.DrawOutline = true;
		//NewBob.CanHaveCape = true;
		//NewBob.PlayerObject.ParentQuad.MyEffect = Tools.BasicEffect;
		//NewBob.PlayerObject.FindQuad("Hat_FireHead").MyTexture = Fireball.FlameTexture;

		// Tigar base object
		NewBob = std::make_shared<Bob>( Path::Combine( Globals::ContentDirectory, _T( "Objects\\TigarBob.smo" ) ), Tools::EffectWad, Tools::TextureWad );
		SetTigarLoaded( NewBob->PlayerObject );
		NewBob->IsSpriteBased = true;
		NewBob->MyObjectType = BobPhsxNormal::getInstance();
		NewBob->CanHaveCape = true;
		NewBob->PlayerObject->Linear = true;
		NewBob->PlayerObject->ParentQuad->MyEffect = Tools::BasicEffect;
		NewBob->PlayerObject->FindQuad( _T( "Hat_FireHead" ) )->MyTexture = Fireball::FlameTexture;

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
		NewBob = std::make_shared<Bob>( BobPhsxNormal::getInstance(), false );
		NewBob->MyObjectType = BobPhsxBouncy::getInstance();
		NewBob->CanHaveCape = true;
		if ( !NewBob->IsSpriteBased )
			NewBob->PlayerObject->FindQuad( _T( "Bouncy" ) )->Show = true;

		BobPhsxBouncy::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxBouncy::getInstance(), NewBob ) );

		// Wheelie
		NewBob = std::make_shared<Bob>( BobPhsxNormal::getInstance(), false );
		NewBob->MyObjectType = BobPhsxWheel::getInstance();
		NewBob->CanHaveCape = false;
		if ( !NewBob->IsSpriteBased )
			NewBob->PlayerObject->FindQuad( _T( "Wheel" ) )->Show = true;

		BobPhsxWheel::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxWheel::getInstance(), NewBob ) );

		// Hero in a Box
		NewBob = std::make_shared<Bob>( BobPhsxNormal::getInstance(), false );
		NewBob->MyObjectType = BobPhsxBox::getInstance();
		if ( !NewBob->IsSpriteBased )
		{
			NewBob->PlayerObject->FindQuad( _T( "Box_Back" ) )->Show = true;
			NewBob->PlayerObject->FindQuad( _T( "Box_Front" ) )->Show = true;
			NewBob->PlayerObject->FindQuad( _T( "Leg_Left" ) )->Show = false;
			NewBob->PlayerObject->FindQuad( _T( "Leg_Right" ) )->Show = false;
		}

		BobPhsxBox::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxBox::getInstance(), NewBob ) );

		// Rocketbox
		NewBob = std::make_shared<Bob>( BobPhsxBox::getInstance(), false );
		NewBob->MyObjectType = BobPhsxBox::getInstance();
		if ( !NewBob->IsSpriteBased )
		{
			NewBob->PlayerObject->FindQuad( _T( "Wheel_Left" ) )->Show = true;
			NewBob->PlayerObject->FindQuad( _T( "Wheel_Right" ) )->Show = true;
		}

		BobPhsxRocketbox::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxRocketbox::getInstance(), NewBob ) );

		// Spaceship 
		NewBob = std::make_shared<Bob>( Path::Combine( Globals::ContentDirectory, _T( "Objects\\Spaceship.smo" ) ), Tools::EffectWad, Tools::TextureWad, BobPhsxSpaceship::getInstance(), false );
		NewBob->MyObjectType = BobPhsxSpaceship::getInstance();
		NewBob->PlayerObject->ParentQuad->Scale( Vector2( 3.5f, 3.5f ) );
		for ( std::vector<std::shared_ptr<BaseQuad> >::const_iterator quad = NewBob->PlayerObject->QuadList.begin(); quad != NewBob->PlayerObject->QuadList.end(); ++quad )
			( *quad )->MyDrawOrder = ObjectDrawOrder_AFTER_OUTLINE;
		NewBob->CanHaveCape = false;
		NewBob->CanHaveHat = false;
		NewBob->PlayerObject->ParentQuad->MyEffect = Tools::BasicEffect;

		std::shared_ptr<Quad> spaceship = std::static_pointer_cast<Quad>( NewBob->PlayerObject->QuadList[ 1 ] );
		spaceship->MyTexture = Tools::Texture( _T( "Spaceship_Paper" ) );
		spaceship->Resize();
		NewBob->PlayerObject->QuadList[ 2 ]->Show = false;


		BobPhsxSpaceship::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxSpaceship::getInstance(), NewBob ) );


		// Meat
		NewBob = std::make_shared<Bob>( Path::Combine( Globals::ContentDirectory, _T( "Objects\\MeatBoy.smo" ) ), Tools::EffectWad, Tools::TextureWad, BobPhsxMeat::getInstance(), true );
		NewBob->IsSpriteBased = false;
		NewBob->MyObjectType = BobPhsxMeat::getInstance();
		NewBob->PlayerObject->ParentQuad->Scale( Vector2( 2.75f, 2.75f ) );
		for ( std::vector<std::shared_ptr<BaseQuad> >::const_iterator quad = NewBob->PlayerObject->QuadList.begin(); quad != NewBob->PlayerObject->QuadList.end(); ++quad )
			( *quad )->MyDrawOrder = ObjectDrawOrder_AFTER_OUTLINE;
		NewBob->CanHaveCape = true;
		NewBob->CanHaveHat = true;
		NewBob->PlayerObject->ParentQuad->MyEffect = Tools::BasicEffect;
		NewBob->PlayerObject->QuadList[ 0 ]->SetTexture( _T( "FallingBlock1" ), Tools::TextureWad );
		NewBob->PlayerObject->QuadList[ 1 ]->SetTexture( _T( "FallingBlock1" ), Tools::TextureWad );

		BobPhsxMeat::getInstance()->Prototype = NewBob;
		bob.insert( std::make_pair( BobPhsxMeat::getInstance(), NewBob ) );


		// Freeplay Heroes
		//if (!(CloudberryKingdomGame.StartAsFreeplay && CloudberryKingdomGame.UseNewBob))
			CustomLevel_GUI::FreeplayHeroes = std::vector<std::shared_ptr<BobPhsx> >( Bob::HeroTypes );

		// Associate the BobPhsx with each prototype
		for ( std::vector<std::shared_ptr<BobPhsx> >::const_iterator HeroType = Bob::HeroTypes.begin(); HeroType != Bob::HeroTypes.end(); ++HeroType )
			Prototypes::bob[ *HeroType ]->MyHeroType = *HeroType;

		// Place bob
		//PlaceBob = LoadObject(Path.Combine(Globals.ContentDirectory, "Objects\\place_bob.smo"));

		Resources::ResourceLoadedCountRef->MyFloat++;
	}
}
