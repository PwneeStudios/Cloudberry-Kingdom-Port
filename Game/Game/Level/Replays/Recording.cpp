#include <global_header.h>

#include "Hacks/NET/Path.h"
#include "Hacks/NET/Directory.h"

namespace CloudberryKingdom
{

	std::wstring Recording::DefaultRecordingDirectory()
	{
		return Path::Combine( Globals::ContentDirectory, std::wstring( L"Recordings" ) );
	}

	std::wstring Recording::SourceRecordingDirectory()
	{
		return Path::Combine( Path::GetDirectoryName( Path::GetDirectoryName( Path::GetDirectoryName( Directory::GetCurrentDirectory() ) ) ), std::wstring( L"Content/Recordings" ) );
	}

	void Recording::Save( const std::wstring &file, bool Bin )
	{
		// First move to standard directory for .rec files
		std::wstring fullpath;
		if ( Bin )
			fullpath = Path::Combine( DefaultRecordingDirectory(), file );
		else
			fullpath = Path::Combine( SourceRecordingDirectory(), file );

		// Now write to file
		Tools::UseInvariantCulture();
		//boost::shared_ptr<FileStream> stream = File->Open( fullpath, FileMode::Create, FileAccess::Write, FileShare::None );
		//boost::shared_ptr<BinaryWriter> writer = boost::make_shared<BinaryWriter>( stream, Encoding::UTF8 );
		{
			boost::shared_ptr<BinaryWriter> writer = boost::make_shared<FileBinaryWriter>( fullpath );
			Write( writer );
		}
		//writer->Close();
		//stream->Close();
	}

	void Recording::Load( const std::wstring &file )
	{
		SourceFile = file;

		// First move to standard directory for .rec files
		std::wstring fullpath = Path::Combine( DefaultRecordingDirectory(), file );

		// Now read the file
		Tools::UseInvariantCulture();
		//boost::shared_ptr<FileStream> stream = File->Open( fullpath, FileMode::Open, FileAccess::Read, FileShare::None );
		//boost::shared_ptr<BinaryReader> reader = boost::make_shared<FileBinaryReader>( stream, Encoding::UTF8 );
		boost::shared_ptr<BinaryReader> reader = boost::make_shared<FileBinaryReader>( fullpath );
		Read( reader );
		//reader->Close();
		//stream->Close();
	}

	void Recording::Write( const boost::shared_ptr<BinaryWriter> &writer )
	{
		writer->Write( NumBobs );
		writer->Write( Length );

		for ( int i = 0; i < NumBobs; i++ )
			Recordings[ i ]->Write( writer, Length );
	}

	void Recording::Read( const boost::shared_ptr<BinaryReader> &reader )
	{
		NumBobs = reader->ReadInt32();
		Length = reader->ReadInt32();
		Init( NumBobs, Length );

		for ( int i = 0; i < NumBobs; i++ )
			Recordings[ i ]->Read( reader, Length );
	}

	void Recording::Draw( const boost::shared_ptr<QuadClass> &BobQuad, int Step, const boost::shared_ptr<Level> &level, std::vector<boost::shared_ptr<SpriteAnimGroup> > AnimGroup, std::vector<boost::shared_ptr<BobLink> > &BobLinks )
	{
		if ( level->MyGame->MyGameFlags.IsTethered && Step < Length - 1 )
		{
			for ( std::vector<boost::shared_ptr<BobLink> >::const_iterator link = BobLinks.begin(); link != BobLinks.end(); ++link )
			{
				if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 &&
					( Recordings[ ( *link )->_j ]->Gett( Step ) == 0 || Recordings[ ( *link )->_k ]->Gett( Step ) == 0 ) )
					continue;
				( *link )->Draw( Recordings[ ( *link )->_j ]->GetBoxCenter( Step ), Recordings[ ( *link )->_k ]->GetBoxCenter( Step ) );
			}
		}

		for ( int i = 0; i < NumBobs; i++ )
		{
			if ( i >= static_cast<int>( level->Bobs.size() ) ) continue;
			if ( Step > 2 && Step == Recordings[i]->Box_BL.size() - 2 ) ParticleEffects::AddPop( level, Recordings[i]->GetBoxCenter( Step - 2 ) );
			if ( Step >= Recordings[ i ]->Box_BL.size() ) continue;

			if ( Step < Length - 1 )
			{
				//if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 )
					if ( Step > 0 && Recordings[ i ]->Gett( Step ) <= 0 )
					{
						if ( Recordings[ i ]->Gett( Step - 1 ) > 0 )
						{
							ParticleEffects::AddPop( level, Recordings[ i ]->GetBoxCenter( Step ) );
						}
						continue;
					}

				Vector2 padding = Vector2();

				//BobQuad->Quad_Renamed.getMyTexture()->setTex( AnimGroup[ i ]->Get( anim, Recordings[ i ]->Gett( Step ), padding ) );
				int texture_index = Recordings[ i ]->Gett( Step );
				if ( texture_index == 0 ) continue;
				BobQuad->Quad_Renamed.getMyTexture()->_Tex = Tools::TextureWad->TextureList[ texture_index ]->_Tex;

				Vector2 size = Recordings[ i ]->GetBoxSize( Step ) / 2.0f;

				BobQuad->Base.e1 = Vector2( size.X, 0 );
				BobQuad->Base.e2 = Vector2( 0, size.Y );

				float a = Bob::UnpackIntIntoVector_Angle( Recordings[ i ]->Box_Size[ Step ] );
				if (a != 0)
					CoreMath::PointxAxisToAngle( BobQuad->Base, a );
  
				BobQuad->Base.Origin = Recordings[ i ]->GetBoxCenter( Step );
				if ( BobQuad->Base.Origin == Vector2() )
					continue;

				BobQuad->Draw();
				Tools::QDrawer->Flush();
			}
			//else
			//	if ( Step == Length - 1 && !level->ReplayPaused && !( boost::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 && !Recordings[ i ]->GetAlive( Length - 1 ) ) )
			//		ParticleEffects::AddPop( level, Recordings[ i ]->GetBoxCenter( Length - 1 ) );
		}
	}

	void Recording::ConvertToSuperSparse( int Step )
	{
		for ( int i = 0; i < static_cast<int>( Recordings.size() ); i++ )
		{
			Recordings[ i ]->ConvertToSuperSparse( this->Length );
		}
	}

	void Recording::Release()
	{
		if ( Recordings.size() > 0 )
		for ( int i = 0; i < static_cast<int>( Recordings.size() ); i++ )
		{
			Recordings[ i ]->Release();
		}
		Recordings.clear();
	}

	Recording::Recording( int NumBobs, int Length ) :
		Length( 0 )
	{
		Init( NumBobs, Length );
	}

	void Recording::Init( int NumBobs, int Length )
	{
		this->NumBobs = NumBobs;

		Recordings = std::vector<boost::shared_ptr<ComputerRecording> >( NumBobs );
		for ( int i = 0; i < NumBobs; i++ )
		{
			Recordings[ i ] = boost::make_shared<ComputerRecording>();
			Recordings[ i ]->Init( Length, true );
		}
	}

	void Recording::Record( const boost::shared_ptr<Level> &level )
	{
		if ( level->Bobs.size() <= 0 )
			return;
		if ( level->PlayMode != 0 || level->Watching )
			return;
		if ( level->CurPhsxStep < 0 )
			return;

		Length = level->CurPhsxStep;
		for ( int i = 0; i < NumBobs; i++ )
		{
			if ( i >= static_cast<int>( level->Bobs.size() ) ) continue;

			Recordings[i]->t[ level->CurPhsxStep ] = level->Bobs[i]->StoredRecordTexture;

			if (level->CurPhsxStep < Recordings[i]->Box_BL.size() )
			{
				Recordings[i]->Box_BL[ level->CurPhsxStep ] = level->Bobs[i]->StoredRecord_BL;
				Recordings[i]->Box_Size[ level->CurPhsxStep ] = level->Bobs[i]->StoredRecord_QuadSize;
			}

			Recordings[ i ]->AutoLocs[ level->CurPhsxStep ] = level->Bobs[ i ]->getCore()->Data.Position;
			Recordings[ i ]->AutoVel[ level->CurPhsxStep ] = level->Bobs[ i ]->getCore()->Data.Velocity;
			Recordings[ i ]->Input[ level->CurPhsxStep ] = level->Bobs[ i ]->CurInput;

			if ( !level->Bobs[ i ]->getCore()->Show )
			{
				Recordings[ i ]->t[ level->CurPhsxStep ] = 0;
				Recordings[ i ]->Box_BL[ level->CurPhsxStep ] = 0;
				Recordings[ i ]->AutoLocs[ level->CurPhsxStep ] = Vector2();
			}
		}
	}

	void Recording::MarkEnd( const boost::shared_ptr<Level> &level )
	{
		Length = level->CurPhsxStep;
	}
}
