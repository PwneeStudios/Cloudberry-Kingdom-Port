#include <global_header.h>

#include "Hacks/NET/Path.h"
#include "Hacks/NET/Directory.h"

namespace CloudberryKingdom
{

	std::wstring Recording::DefaultRecordingDirectory()
	{
		return Path::Combine( Globals::ContentDirectory, _T( "Recordings" ) );
	}

	std::wstring Recording::SourceRecordingDirectory()
	{
		return Path::Combine( Path::GetDirectoryName( Path::GetDirectoryName( Path::GetDirectoryName( Directory::GetCurrentDirectory() ) ) ), _T("Content/Recordings") );
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
			boost::shared_ptr<BinaryWriter> writer = boost::make_shared<BinaryWriter>( fullpath );
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
		//boost::shared_ptr<BinaryReader> reader = boost::make_shared<BinaryReader>( stream, Encoding::UTF8 );
		boost::shared_ptr<BinaryReader> reader = boost::make_shared<BinaryReader>( fullpath );
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
				if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 && ( !Recordings[ ( *link )->_j ]->GetAlive( Step ) || !Recordings[ ( *link )->_k ]->GetAlive( Step ) ) )
					continue;
				( *link )->Draw( Recordings[ ( *link )->_j ]->GetBoxCenter( Step ), Recordings[ ( *link )->_k ]->GetBoxCenter( Step ) );
			}
		}

		for ( int i = 0; i < NumBobs; i++ )
		{
			if ( i >= static_cast<int>( level->Bobs.size() ) )
				continue;
			if ( Step < Length - 1 )
			{
				if ( boost::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 )
					if ( Step > 0 && !Recordings[ i ]->GetAlive( Step ) )
					{
						if ( Recordings[ i ]->GetAlive( Step - 1 ) )
						{
							ParticleEffects::AddPop( level, Recordings[ i ]->GetBoxCenter( Step ) );
						}
						continue;
					}

				Vector2 padding = Vector2();
				int anim = static_cast<int>( Recordings[ i ]->GetAnim( Step ) );
				if ( anim > 200 )
					continue;

				BobQuad->Quad_Renamed.getMyTexture()->setTex( AnimGroup[ i ]->Get( anim, Recordings[ i ]->Gett( Step ), padding ) );

				BobQuad->Base.e1 = Vector2( BoxSize.X + padding.X, 0 );
				BobQuad->Base.e2 = Vector2( 0, BoxSize.Y + padding.Y );
				BobQuad->Base.Origin = Recordings[ i ]->GetBoxCenter( Step );
				if ( BobQuad->Base.Origin == Vector2() )
					continue;

				BobQuad->Draw();
				Tools::QDrawer->Flush();
			}
			else
				if ( Step == Length - 1 && !level->ReplayPaused && !( boost::dynamic_pointer_cast<BobPhsxSpaceship>( level->DefaultHeroType ) != 0 && !Recordings[ i ]->GetAlive( Length - 1 ) ) )
					ParticleEffects::AddPop( level, Recordings[ i ]->GetBoxCenter( Length - 1 ) );
		}
	}

	void Recording::ConvertToSuperSparse()
	{
		for ( int i = 0; i < static_cast<int>( Recordings.size() ); i++ )
		{
			Recordings[ i ]->ConvertToSuperSparse();
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

	Recording::Recording( int NumBobs, int Length )
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

		BoxSize = level->Bobs[ 0 ]->PlayerObject->BoxList[ 0 ]->Size() / 2;

		Length = level->CurPhsxStep;
		for ( int i = 0; i < NumBobs; i++ )
		{
			if ( i >= static_cast<int>( level->Bobs.size() ) )
				continue;

			Recordings[ i ]->Anim[ level->CurPhsxStep ] = static_cast<unsigned char>( level->Bobs[ i ]->PlayerObject->anim );

			Recordings[ i ]->t[ level->CurPhsxStep ] = level->Bobs[ i ]->PlayerObject->t;
			Recordings[ i ]->BoxCenter[ level->CurPhsxStep ] = level->Bobs[ i ]->PlayerObject->BoxList[ 0 ]->Center();
			Recordings[ i ]->AutoLocs[ level->CurPhsxStep ] = level->Bobs[ i ]->getCore()->Data.Position;
			Recordings[ i ]->AutoVel[ level->CurPhsxStep ] = level->Bobs[ i ]->getCore()->Data.Velocity;
			Recordings[ i ]->Input[ level->CurPhsxStep ] = level->Bobs[ i ]->CurInput;
			Recordings[ i ]->Alive[ level->CurPhsxStep ] = !( level->Bobs[ i ]->Dead || level->Bobs[ i ]->Dying );

			if ( !level->Bobs[ i ]->getCore()->Show )
			{
				Recordings[ i ]->Anim[ level->CurPhsxStep ] = static_cast<unsigned char>( 255 );
				Recordings[ i ]->AutoLocs[ level->CurPhsxStep ] = level->getMainCamera()->Data.Position;
			Recordings[ i ]->BoxCenter[ level->CurPhsxStep ] = Recordings[ i ]->AutoLocs[ level->CurPhsxStep ];
			}
		}
	}

	void Recording::MarkEnd( const boost::shared_ptr<Level> &level )
	{
		Length = level->CurPhsxStep;
	}
}
