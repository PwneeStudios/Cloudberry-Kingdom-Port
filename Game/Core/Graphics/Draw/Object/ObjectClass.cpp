#include "ObjectClass.h"
#include "Core/Graphics/Draw/Quads/Quad.h"
#include "Core/Texture/EzTexture.h"
#include "Core/Effects/EzEffect.h"
#include "Core/Graphics/Draw/Quads/BaseQuad.h"
#include "Core/Graphics/QuadDrawer.h"
#include "Core/Animation/AnimQueue.h"
#include "Core/Graphics/Draw/Object/ObjectBox.h"
#include "Core/Animation/AnimationData_Vector.h"
#include "Game/Tools/EzReader.h"
#include "Game/Tools/Tools.h"
#include "Core/Effects/EzEffectWad.h"
#include "Core/Texture/CloudberryKingdom.EzTextureWad.h"
#include "Core/Graphics/Draw/Quads/ObjectVector.h"
#include "Game/Objects/Game Objects/GameObjects/Listener.h"
#include "Game/Tools/Oscillate.h"
#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
#include "Core/Animation/SpriteAnim.h"

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Graphics;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{

int ObjectClass::ObjectClassVersionNumber = 54;

	const bool &ObjectClass::getDonePlaying() const
	{
		return AnimQueue.empty();
	}

	void ObjectClass::Release()
	{
		if ( ObjectRenderTarget != 0 && OriginalRenderTarget )
			delete ObjectRenderTarget;

		ContainedQuad->Release();
		ParentQuad->Release();

		if ( QuadList.size() > 0 )
		for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
		{
			( *quad )->Release();
		}
		QuadList.clear();

		for ( std::vector<ObjectBox*>::const_iterator box = BoxList.begin(); box != BoxList.end(); ++box )
			( *box )->Release();
		BoxList.clear();

		QuadList.clear();
		BoxList.clear();

		AnimQueue.clear();
		AnimLength.clear();
		AnimName.clear();
		AnimSpeed.clear();
	}

	void ObjectClass::ConvertForSimple()
	{
		AnimationData::RecordAll = true;

		for ( int i = AnimName.size() - 1; i >= 0; i-- )
		{

			for ( int j = AnimLength[ i ]; j >= 0; j-- )
			{
				Read( i, j );
				Update( 0 );

				Record( i, j, false );
			}
		}
		AnimationData::RecordAll = false;
	}

	void ObjectClass::Write( const std::shared_ptr<BinaryWriter> &writer )
	{
		// Object version number
		writer->Write( VersionNumber );

		// Anim data
		writer->Write( AnimLength.size() );
		for ( int i = 0; i < AnimLength.size(); i++ )
			writer->Write( AnimLength[ i ] );

		writer->Write( AnimName.size() );
		for ( int i = 0; i < AnimName.size(); i++ )
			writer->Write( AnimName[ i ] );

		writer->Write( AnimSpeed.size() );
		for ( int i = 0; i < AnimSpeed.size(); i++ )
			writer->Write( AnimSpeed[ i ] );

		// Write number of quads and their type
		writer->Write( QuadList.size() );
		for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
		{
			if ( dynamic_cast<Quad*>( *quad ) != 0 )
				writer->Write( 0 );
			else
				writer->Write( 1 );
		}

		// Write each quad's data
		for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
		{
			( *quad )->Write( writer );
		}

		// Boxes
		writer->Write( BoxList.size() );
		for ( std::vector<ObjectBox*>::const_iterator box = BoxList.begin(); box != BoxList.end(); ++box )
			( *box )->Write( writer, this );
	}

	void ObjectClass::ReadFile( const std::shared_ptr<EzReader> &reader )
	{
		ReadFile( reader->reader, Tools::EffectWad, Tools::TextureWad );
	}

	void ObjectClass::ReadFile( const std::shared_ptr<BinaryReader> &reader, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<EzTextureWad> &TextureWad )
	{
		// Get object version number
		VersionNumber = reader->PeekChar();
		if ( VersionNumber > 50 )
			VersionNumber = reader->ReadInt32();

		// Get anim data
		int length;

		length = reader->ReadInt32();
		AnimLength = std::vector<int>( length );
		for ( int i = 0; i < length; i++ )
			AnimLength[ i ] = reader->ReadInt32();

		length = reader->ReadInt32();
		AnimName = std::vector<std::wstring*>( length );
		for ( int i = 0; i < length; i++ )
			AnimName[ i ] = reader->ReadString();

		length = reader->ReadInt32();
		AnimSpeed = std::vector<float>( length );
		for ( int i = 0; i < length; i++ )
			AnimSpeed[ i ] = reader->ReadSingle();

		// Get number of quads
		int n = reader->ReadInt32();

		// Create a list of quads to hold the data to be loaded
		for ( int i = 0; i < n; i++ )
		{
			int QuadType = reader->ReadInt32();

			if ( QuadType == 0 )
			{
				std::shared_ptr<Quad> NewQuad = std::make_shared<Quad>();
				AddQuad( NewQuad );
			}
			else
				Tools::Break();
		}

		// Load the quad data
		for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
		{
			( *quad )->Read( reader, EffectWad, TextureWad, VersionNumber );
		}

		// Load the box data
		n = reader->ReadInt32();
		for ( int i = 0; i < n; i++ )
		{
			std::shared_ptr<ObjectBox> NewBox = std::make_shared<ObjectBox>();
			NewBox->Read( reader, this, VersionNumber );
			AddBox( NewBox );
		}

		// Sort the quad list
		Sort();

		// Update object version number
		VersionNumber = ObjectClassVersionNumber;

		UpdateEffectList();
	}

#if defined(EDITOR)
	std::vector<ObjectVector*> ObjectClass::GetObjectVectors()
	{
		std::vector<ObjectVector*> L = std::vector<ObjectVector*>();
		for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
			L.AddRange( ( *quad )->GetObjectVectors() );
		return L;
	}
#endif

	void ObjectClass::UpdateEffectList()
	{
		if ( QuadList.empty() || QuadList.empty() )
			return;

		if ( MyEffects.empty() )
			MyEffects = std::vector<EzEffect*>();
		else
			MyEffects.clear();

		for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
			if ( !std::find( MyEffects.begin(), MyEffects.end(), (*quad)->MyEffect ) != MyEffects.end() )
				MyEffects.push_back( ( *quad )->MyEffect );
	}

	Microsoft::Xna::Framework::Vector2 ObjectClass::CalcBLBound()
	{
		Vector2 BL = Vector2( 10000000, 10000000 );

		for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
		{
			BL = Vector2::Min( BL, ( *quad )->BL() );
		}

		return BL;
	}

	Microsoft::Xna::Framework::Vector2 ObjectClass::CalcTRBound()
	{
		Vector2 TR = Vector2( -10000000, -10000000 );

		for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
		{
			TR = Vector2::Max( TR, ( *quad )->TR() );
		}

		return TR;
	}

	void ObjectClass::EnqueueTransfer( int _anim, float _destT, float speed, bool DestLoop )
	{
		EnqueueTransfer( _anim, _destT, speed, false, false );
	}

	void ObjectClass::EnqueueTransfer( int _anim, float _destT, float speed, bool DestLoop, bool KeepTransfers )
	{
		if ( !KeepTransfers )
			DequeueTransfers();

		std::shared_ptr<AnimQueueEntry> NewEntry = std::make_shared<AnimQueueEntry>();
		NewEntry->anim = _anim;
		NewEntry->AnimSpeed = speed;
		NewEntry->StartT = 0;
		NewEntry->EndT = 1;
		NewEntry->DestT = _destT;
		NewEntry->Loop = DestLoop;
		NewEntry->Type = AnimQueueEntryType_TRANSFER;
		NewEntry->Initialized = false;

		AnimQueue.push( NewEntry );
		LastAnimEntry = NewEntry;
	}

	void ObjectClass::ImportAnimData( const std::shared_ptr<ObjectClass> &SourceObj, std::vector<BaseQuad*> &SourceQuads, std::vector<std::wstring> &SourceAnims )
	{
		for ( std::vector<BaseQuad*>::const_iterator SourceQuad = SourceQuads.begin(); SourceQuad != SourceQuads.end(); ++SourceQuad )
		{
			// Find the corresponding quad
			std::shared_ptr<BaseQuad> quad = FindQuad( ( *SourceQuad )->Name );
			if ( quad != 0 )
			{
				// Loop through all the animations and copy the values
				for ( std::vector<std::wstring>::const_iterator AnimName = SourceAnims.begin(); AnimName != SourceAnims.end(); ++AnimName )
				{
					if ( HasAnim( *AnimName ) )
					{
						int AnimIndex = FindAnim( *AnimName );
						quad->CopyAnim( *SourceQuad, AnimIndex );
					}
				}
			}
		}
	}

	void ObjectClass::ImportAnimDataShallow( const std::shared_ptr<ObjectClass> &SourceObj, std::vector<BaseQuad*> &SourceQuads, std::vector<std::wstring> &SourceAnims )
	{
		for ( std::vector<BaseQuad*>::const_iterator SourceQuad = SourceQuads.begin(); SourceQuad != SourceQuads.end(); ++SourceQuad )
		{
			// Find the corresponding quad
			std::shared_ptr<BaseQuad> quad = FindQuad( ( *SourceQuad )->Name );
			if ( quad != 0 )
			{
				// Loop through all the animations and copy the values
				for ( std::vector<std::wstring>::const_iterator AnimName = SourceAnims.begin(); AnimName != SourceAnims.end(); ++AnimName )
				{
					if ( HasAnim( *AnimName ) )
					{
						int AnimIndex = FindAnim( *AnimName );
						quad->CopyAnimShallow( *SourceQuad, AnimIndex );
					}
				}
			}
		}
	}

	bool ObjectClass::HasAnim( const std::wstring &name )
	{
		for ( int i = 0; i < AnimName.size(); i++ )
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Compare' reference is not converted:
			if ( std::wstring::Compare( name, AnimName[ i ], StringComparison::OrdinalIgnoreCase ) == 0 )
				return true;
		return false;
	}

	int ObjectClass::FindAnim( const std::wstring &name )
	{
		for ( int i = 0; i < AnimName.size(); i++ )
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Compare' reference is not converted:
			if ( std::wstring::Compare( name, AnimName[ i ], StringComparison::OrdinalIgnoreCase ) == 0 )
				return i;
		return 0;
	}

	void ObjectClass::EnqueueAnimation( const std::wstring &name )
	{
		EnqueueAnimation( name, 0, false, true );
	}

	void ObjectClass::EnqueueAnimation( const std::wstring &name, float startT, bool loop, bool clear )
	{
		EnqueueAnimation( FindAnim( name ), startT, loop, clear );
	}

	void ObjectClass::EnqueueAnimation( const std::wstring &name, float startT, bool loop, bool clear, float TransferSpeed, float PlaySpeed )
	{
		EnqueueAnimation( name, startT, loop, clear, TransferSpeed, PlaySpeed, false );
	}

	void ObjectClass::EnqueueAnimation( const std::wstring &name, float startT, bool loop, bool clear, float TransferSpeed, float PlaySpeed, bool KeepTransfers )
	{
		EnqueueAnimation( FindAnim( name ), startT, loop, clear, KeepTransfers, TransferSpeed );
		//AnimQueue.Peek().AnimSpeed *= 5f;
		DestAnim()->AnimSpeed *= PlaySpeed;
	}

	void ObjectClass::EnqueueAnimation( int _anim, float startT, bool loop )
	{
		EnqueueAnimation( _anim, startT, loop, true, false, 1 );
	}

	void ObjectClass::EnqueueAnimation( int _anim, float startT, bool loop, bool clear )
	{
		EnqueueAnimation( _anim, startT, loop, true, false, 1 );
	}

	void ObjectClass::EnqueueAnimation( int _anim, float startT, bool loop, bool clear, bool KeepTransfers, float TransferSpeed )
	{
		if ( clear )
			AnimQueue.clear();

		EnqueueTransfer( _anim, startT,.5f * TransferSpeed, loop, KeepTransfers );

		std::shared_ptr<AnimQueueEntry> NewEntry = std::make_shared<AnimQueueEntry>();
		NewEntry->anim = _anim;
		NewEntry->AnimSpeed = 1;
		NewEntry->StartT = startT;
		NewEntry->EndT = -1;
		NewEntry->Loop = loop;
		NewEntry->Type = AnimQueueEntryType_PLAY;
		NewEntry->Initialized = false;

		AnimQueue.push( NewEntry );
		LastAnimEntry = NewEntry;
	}

	int ObjectClass::DestinationAnim()
	{
		if ( AnimQueue.size() > 0 )
			return LastAnimEntry->anim;
		else
			return anim;
	}

	std::shared_ptr<AnimQueueEntry> ObjectClass::DestAnim()
	{
		return LastAnimEntry;
	}

	void ObjectClass::DequeueTransfers()
	{
		while ( AnimQueue.size() > 0 && AnimQueue.front()->Type == AnimQueueEntryType_TRANSFER )
			AnimQueue.pop();
	}

	void ObjectClass::SetAnimT( float t, bool Loop )
	{
		this->t = t;

		for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
			( *quad )->Calc( anim, t, AnimLength[ anim ], Loop, false );
	}

	bool ObjectClass::AtTime( float time )
	{
		return t > time && OldT <= time;
	}

	void ObjectClass::PlayUpdate( float DeltaT )
	{
		OldT = t;

		if ( !Play )
			return;
		if ( AnimQueue.empty() )
			return;

		std::shared_ptr<AnimQueueEntry> CurAnimQueueEntry = AnimQueue.front();

		if ( !CurAnimQueueEntry->Initialized )
		{
			t = CurAnimQueueEntry->StartT;
			Loop = CurAnimQueueEntry->Loop;
			anim = CurAnimQueueEntry->anim;

			if ( CurAnimQueueEntry->Type == AnimQueueEntryType_TRANSFER )
				SetHold();

			CurAnimQueueEntry->Initialized = true;
		}

		t += DeltaT * AnimSpeed[ anim ] * CurAnimQueueEntry->AnimSpeed;
		if ( CurAnimQueueEntry->Type == AnimQueueEntryType_TRANSFER )
		{
			if ( t > 1 )
			{
				AnimQueue.pop();
				if ( AnimQueue.size() > 0 )
				{
					std::shared_ptr<AnimQueueEntry> Next = AnimQueue.front();
					if ( Next_ANIM == anim )
						Next_START_T = CurAnimQueueEntry->DestT;
				}

				t = 1;
			}
		}
		else
		{
			if ( !Loop && t > CurAnimQueueEntry->EndT && t - DeltaT <= CurAnimQueueEntry->EndT )
			{
				t = CurAnimQueueEntry->EndT;
				AnimQueue.pop();
			}
			else
			{
				if ( Loop )
				{
					if ( t <= 0 )
						t += AnimLength[ anim ] + 1;
					if ( t > AnimLength[ anim ] + 1 )
						t -= AnimLength[ anim ] + 1;
				}
				else
				{
					if ( t < 0 )
					{
						t = 0;
						AnimQueue.pop();
					}
					if ( t > AnimLength[ anim ] )
					{
						t = AnimLength[ anim ];
						AnimQueue.pop();
					}
				}
			}
		}

		if ( CurAnimQueueEntry->Type == AnimQueueEntryType_PLAY )
		{
			if ( !BoxesOnly && QuadList.size() > 0 )
				for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
				{
					( *quad )->UpdateSpriteAnim = DoSpriteAnim;
					( *quad )->Calc( anim, t, AnimLength[ anim ], Loop, Linear );
				}
			for ( std::vector<ObjectBox*>::const_iterator box = BoxList.begin(); box != BoxList.end(); ++box )
				( *box )->Calc( anim, t, AnimLength[ anim ], Loop, Linear );
		}
		else
		{
			if ( !BoxesOnly && QuadList.size() > 0 )
				for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
					( *quad )->Transfer( anim, CurAnimQueueEntry->DestT, AnimLength[ anim ], CurAnimQueueEntry->Loop, Linear, t );
			for ( std::vector<ObjectBox*>::const_iterator box = BoxList.begin(); box != BoxList.end(); ++box )
				( *box )->Transfer( anim, CurAnimQueueEntry->DestT, AnimLength[ anim ], CurAnimQueueEntry->Loop, Linear, t );
		}
	}

	void ObjectClass::SetHold()
	{
		if ( !BoxesOnly && QuadList.size() > 0 )
			for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
				( *quad )->SetHold();
		for ( std::vector<ObjectBox*>::const_iterator box = BoxList.begin(); box != BoxList.end(); ++box )
			( *box )->SetHold();
	}

#if defined(EDITOR)
	void ObjectClass::DeleteFrame( int anim, int frame )
	{
		if ( frame <= AnimLength[ anim ] )
		{
			AnimLength[ anim ]--;

			for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
				for ( std::vector<ObjectVector*>::const_iterator point = quad->GetObjectVectors().begin(); point != quad->GetObjectVectors().end(); ++point )
					( *point )->AnimData.DeleteFrame( anim, frame );
			for ( std::vector<ObjectBox*>::const_iterator box = BoxList.begin(); box != BoxList.end(); ++box )
				for ( std::vector<ObjectVector*>::const_iterator point = box->GetObjectVectors().begin(); point != box->GetObjectVectors().end(); ++point )
					( *point )->AnimData.DeleteFrame( anim, frame );
		}
	}
#endif

#if defined(EDITOR)
	void ObjectClass::InsertFrame( int anim, int frame )
	{
		if ( frame <= AnimLength[ anim ] )
		{
			AnimLength[ anim ]++;

			for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
				for ( std::vector<ObjectVector*>::const_iterator point = quad->GetObjectVectors().begin(); point != quad->GetObjectVectors().end(); ++point )
					( *point )->AnimData.InsertFrame( anim, frame );
			for ( std::vector<ObjectBox*>::const_iterator box = BoxList.begin(); box != BoxList.end(); ++box )
				for ( std::vector<ObjectVector*>::const_iterator point = box->GetObjectVectors().begin(); point != box->GetObjectVectors().end(); ++point )
					( *point )->AnimData.InsertFrame( anim, frame );
		}
	}
#endif

	void ObjectClass::Record( int anim, int frame, bool UseRelativeCoords )
	{
		for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
			( *quad )->Record( anim, frame, UseRelativeCoords );

		for ( std::vector<ObjectBox*>::const_iterator box = BoxList.begin(); box != BoxList.end(); ++box )
			( *box )->Record( anim, frame, UseRelativeCoords );
	}

	void ObjectClass::Read( int anim, int frame )
	{
		ReadQuadData( anim, frame );
		ReadBoxData( anim, frame );
	}

	void ObjectClass::Read_NoTexture( int anim, int frame )
	{
		if ( !BoxesOnly && QuadList.size() > 0 )
			for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
				if ( dynamic_cast<Quad*>( *quad ) != 0 )
					( *quad )->UpdateSpriteAnim = false;

		ReadQuadData( anim, frame );
		ReadBoxData( anim, frame );

		if ( !BoxesOnly && QuadList.size() > 0 )
			for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
				if ( dynamic_cast<Quad*>( *quad ) != 0 )
					( *quad )->UpdateSpriteAnim = DoSpriteAnim;
	}

	void ObjectClass::ReadQuadData( int anim, int frame )
	{
		if ( !BoxesOnly && QuadList.size() > 0 )
			for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
				( *quad )->ReadAnim( anim, frame );
	}

	void ObjectClass::ReadBoxData( int anim, int frame )
	{
		for ( std::vector<ObjectBox*>::const_iterator box = BoxList.begin(); box != BoxList.end(); ++box )
			( *box )->ReadAnim( anim, frame );
	}

	void ObjectClass::FinishLoading()
	{
		FinishLoading( Tools::QDrawer, Tools::Device, Tools::TextureWad, Tools::EffectWad, Tools::Device->PresentationParameters, 0, 0, true );
	}

	void ObjectClass::FinishLoading( const std::shared_ptr<QuadDrawer> &Drawer, const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzTextureWad> &TexWad, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<PresentationParameters> &pp, int Width, int Height )
	{
		FinishLoading( Drawer, device, TexWad, EffectWad, pp, Width, Height, true );
	}

	void ObjectClass::FinishLoading( const std::shared_ptr<QuadDrawer> &Drawer, const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzTextureWad> &TexWad, const std::shared_ptr<EzEffectWad> &EffectWad, const std::shared_ptr<PresentationParameters> &pp, int Width, int Height, bool UseNames )
	{
		QDrawer = Drawer;
		ParentQuad->FinishLoading( device, TexWad, EffectWad );
		if ( !BoxesOnly && QuadList.size() > 0 )
			for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
				( *quad )->FinishLoading( device, TexWad, EffectWad, UseNames );

		if ( Width > 0 && Height > 0 )
			InitRenderTargets( device, pp, Width, Height );
	}

	ObjectClass::ObjectClass()
	{
		InitializeInstanceFields();
		ObjectClassInit( Tools::QDrawer, Tools::Device, Tools::Device->PresentationParameters, 0, 0, Tools::EffectWad->FindByName( _T( "BasicEffect" ) ), Tools::TextureWad->FindByName( _T( "White" ) ) );
	}

	ObjectClass::ObjectClass( const std::shared_ptr<ObjectClass> &obj, bool _BoxesOnly, bool DeepClone )
	{
		InitializeInstanceFields();
		LoadingRunSpeed = obj->LoadingRunSpeed;

		CapeThickness = obj->CapeThickness;
		p1_Left = obj->p1_Left;
		p2_Left = obj->p2_Left;
		p1_Right = obj->p1_Right;
		p2_Right = obj->p2_Right;



		Linear = obj->Linear;

		VersionNumber = obj->VersionNumber;

		BoxesOnly = _BoxesOnly;

		LoadingRunSpeed = obj->LoadingRunSpeed;

		AnimQueue = std::queue<AnimQueueEntry*>();
		std::vector<AnimQueueEntry*> array_Renamed = obj->AnimQueue.ToArray();
		if ( array_Renamed.size() > 0 )
		{
			LastAnimEntry = std::make_shared<AnimQueueEntry>( array_Renamed[ array_Renamed.size() - 1 ] );
			for ( int i = 0; i < array_Renamed.size() - 1; i++ )
				AnimQueue.push( std::make_shared<AnimQueueEntry>( array_Renamed[ i ] ) );
			AnimQueue.push( LastAnimEntry );
		}



		CenterFlipOnBox = obj->CenterFlipOnBox;

		ParentQuad = std::make_shared<Quad>( obj->ParentQuad, DeepClone );
		ParentQuad->ParentObject = this;
		ParentQuad->MyEffect = obj->ParentQuad->MyEffect;
		ParentQuad->MyTexture = obj->ParentQuad->MyTexture;

		MySkinTexture = obj->MySkinTexture;
		MySkinEffect = obj->MySkinEffect;

		// Add quads and boxes            
		if ( !BoxesOnly )
		{
			QuadList = std::vector<BaseQuad*>();

			for ( std::vector<BaseQuad*>::const_iterator quad = obj->QuadList.begin(); quad != obj->QuadList.end(); ++quad )
			{
				if ( dynamic_cast<Quad*>( *quad ) != 0 )
				{
					std::shared_ptr<Quad> nquad = std::make_shared<Quad>( static_cast<Quad*>( *quad ), DeepClone );
					QuadList.push_back( nquad );
					nquad->ParentObject = this;
					if ( ( *quad )->ParentQuad == ( *quad )->ParentObject->ParentQuad )
						ParentQuad->AddQuadChild( nquad );
				}
			}
		}

		// Clone boxes
		BoxList = std::vector<ObjectBox*>();
		for ( std::vector<ObjectBox*>::const_iterator box = obj->BoxList.begin(); box != obj->BoxList.end(); ++box )
			BoxList.push_back( std::make_shared<ObjectBox>( *box, DeepClone ) );


		// Make sure pointers match up
		if ( !BoxesOnly && QuadList.size() > 0 )
		{
			for ( int i = 0; i < obj->QuadList.size(); i++ )
			{
				// Preserve Parent-Point relationship (for quads attached to splines)
				if ( dynamic_cast<Quad*>( obj->QuadList[ i ] ) != 0 )
				{
					std::shared_ptr<BaseQuad> parent = ( static_cast<Quad*>( obj->QuadList[ i ] ) )->Center->ParentQuad;
					if ( parent != 0 )
					{
						if ( parent == obj->ParentQuad )
							( static_cast<Quad*>( QuadList[ i ] ) )->Center->ParentQuad = ParentQuad;
						else
						{
							int j = obj->QuadList.find( static_cast<BaseQuad*>( parent ) );
							( static_cast<Quad*>( QuadList[ i ] ) )->Center->ParentQuad = QuadList[ j ];
						}
					}
				}

				// Preserve Parent-Child quad relationship
				if ( obj->QuadList[ i ]->ParentQuad != obj->ParentQuad )
					( static_cast<Quad*>( QuadList[ obj->QuadList.find( obj->QuadList[ i ]->ParentQuad ) ] ) )->AddQuadChild( QuadList[ i ] );
			}
		}
		for ( int i = 0; i < obj->BoxList.size(); i++ )
		{
			if ( !BoxesOnly && obj->BoxList[ i ]->BL->ParentQuad != obj->ParentQuad )
				BoxList[ i ]->TR->ParentQuad = BoxList[ i ]->BL->ParentQuad = static_cast<Quad*>( QuadList[ obj->QuadList.find( obj->BoxList[ i ]->BL->ParentQuad ) ] );
			else
				BoxList[ i ]->TR->ParentQuad = BoxList[ i ]->BL->ParentQuad = ParentQuad;
		}


		Play = obj->Play;
		Loop = obj->Loop;
		anim = obj->anim;
		t = obj->t;

		AnimLength = std::vector<int>( 50 );
		obj->AnimLength.CopyTo( AnimLength, 0 );
		AnimSpeed = std::vector<float>( 50 );
		obj->AnimSpeed.CopyTo( AnimSpeed, 0 );
		AnimName = std::vector<std::wstring*>( 50 );
		obj->AnimName.CopyTo( AnimName, 0 );

		QDrawer = obj->QDrawer;

		InitRenderTargets( obj );

		UpdateEffectList();
	}

	ObjectClass::ObjectClass( const std::shared_ptr<QuadDrawer> &Drawer, const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzEffect> &BaseEffect, const std::shared_ptr<EzTexture> &BaseTexture )
	{
		InitializeInstanceFields();
		ObjectClassInit( Drawer, device, device->PresentationParameters, 0, 0, BaseEffect, BaseTexture );
	}

	ObjectClass::ObjectClass( const std::shared_ptr<QuadDrawer> &Drawer, const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<PresentationParameters> &pp, int Width, int Height, const std::shared_ptr<EzEffect> &BaseEffect, const std::shared_ptr<EzTexture> &BaseTexture )
	{
		InitializeInstanceFields();
		ObjectClassInit( Drawer, device, device->PresentationParameters, Width, Height, BaseEffect, BaseTexture );
	}

	void ObjectClass::ObjectClassInit( const std::shared_ptr<QuadDrawer> &Drawer, const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<PresentationParameters> &pp, int Width, int Height, const std::shared_ptr<EzEffect> &BaseEffect, const std::shared_ptr<EzTexture> &BaseTexture )
	{
		VersionNumber = ObjectClassVersionNumber;

		AnimQueue = std::queue<AnimQueueEntry*>();

		CenterFlipOnBox = true;

		ParentQuad = std::make_shared<Quad>();
		ParentQuad->ParentObject = this;
		ParentQuad->MyEffect = BaseEffect;
		ParentQuad->MyTexture = BaseTexture;

		QuadList = std::vector<BaseQuad*>();
		BoxList = std::vector<ObjectBox*>();

		AnimLength = std::vector<int>( 50 );
		AnimSpeed = std::vector<float>( 50 );
		AnimName = std::vector<std::wstring*>( 50 );
		for ( int i = 0; i < 50; i++ )
		{
			AnimName[ i ] = _T( "Anim_" ) + StringConverterHelper::toString( i );
			AnimSpeed[ i ] = 1;
		}

		QDrawer = Drawer;

		if ( Height > 0 && Width > 0 )
			InitRenderTargets( device, pp, Width, Height );

		UpdateEffectList();
	}

	void ObjectClass::MakeRenderTargetUnique( int width, int height )
	{
		if ( !OriginalRenderTarget )
			InitRenderTargets( Tools::Device, Tools::Device->PresentationParameters, width, height );
	}

	void ObjectClass::InitRenderTargets( const std::shared_ptr<ObjectClass> &obj )
	{
		OriginalRenderTarget = false;

		DrawWidth = obj->DrawWidth;
		DrawHeight = obj->DrawHeight;

		ObjectRenderTarget = obj->ObjectRenderTarget;
	}

	void ObjectClass::InitRenderTargets( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<PresentationParameters> &pp, int Width, int Height )
	{
		OriginalRenderTarget = true;

		DrawWidth = Width;
		DrawHeight = Height;

		ObjectRenderTarget = std::make_shared<RenderTarget2D>( device, DrawWidth, DrawHeight, false, pp->BackBufferFormat, pp->DepthStencilFormat, pp->MultiSampleCount, RenderTargetUsage::DiscardContents );

		ToTextureRenderTarget = std::make_shared<RenderTarget2D>( device, DrawWidth, DrawHeight, false, pp->BackBufferFormat, pp->DepthStencilFormat, pp->MultiSampleCount, RenderTargetUsage::DiscardContents );
	}

	std::vector<BaseQuad*> ObjectClass::FindQuads( ... )
	{
		std::vector<BaseQuad*> list = std::vector<BaseQuad*>();
		for ( unknown::const_iterator name = names.begin(); name != names.end(); ++name )
			list.push_back( FindQuad( *name ) );
		return list;
	}

	std::shared_ptr<BaseQuad> ObjectClass::FindQuad( const std::wstring &name )
	{
		for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
		{
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Compare' reference is not converted:
			if ( std::wstring::Compare( ( *quad )->Name, name, StringComparison::OrdinalIgnoreCase ) == 0 )
				return quad;
		}

		return 0;
	}

	void ObjectClass::AddToNewList( std::vector<BaseQuad*> &NewList, const std::shared_ptr<BaseQuad> &quad )
	{
		if ( quad == ParentQuad || std::find( NewList.begin(), NewList.end(), quad ) != NewList.end() )
			return;
		if ( quad->ParentQuad != 0 )
			AddToNewList( NewList, quad->ParentQuad );
		NewList.push_back( quad );
	}

	void ObjectClass::Sort()
	{
		std::vector<BaseQuad*> NewList = std::vector<BaseQuad*>();

		for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
			AddToNewList( NewList, *quad );
		QuadList = NewList;
	}

	void ObjectClass::Scale( float scale )
	{
		ParentQuad->Scale( Vector2( scale, scale ) );
	}

	void ObjectClass::Scale( Vector2 scale )
	{
		ParentQuad->Scale( scale );
	}

	void ObjectClass::MoveTo( Vector2 NewPosition )
	{
		MoveTo( NewPosition, true );
	}

	void ObjectClass::MoveTo( Vector2 NewPosition, bool UpdateObject )
	{
		ParentQuad->Center->Move( NewPosition );
		ParentQuad->Update();
		if ( UpdateObject )
			Update( 0 );
	}

	void ObjectClass::SetColor( Color color )
	{
		for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
			( *quad )->SetColor( color );
	}

	void ObjectClass::UpdateBoxes()
	{
		for ( std::vector<ObjectBox*>::const_iterator box = BoxList.begin(); box != BoxList.end(); ++box )
			( *box )->Update();
	}

	void ObjectClass::Update( const std::shared_ptr<BaseQuad> &quad )
	{
		ParentQuad->Update();

		UpdateBoxes();

		if ( !BoxesOnly && QuadList.size() > 0 )
		{
			for ( std::vector<BaseQuad*>::const_iterator _quad = QuadList.begin(); _quad != QuadList.end(); ++_quad )
				( *_quad )->Update();
		}

		if ( BoxList.size() > 1 )
			FlipCenter = BoxList[ 1 ]->Center();
		else if ( BoxList.size() > 0 )
			FlipCenter = BoxList[ 0 ]->Center();
		else
			FlipCenter = ParentQuad->Center->Pos;
	}

	void ObjectClass::AddBox( const std::shared_ptr<ObjectBox> &box )
	{
		BoxList.push_back( box );
		box->TR->ParentQuad = ParentQuad;
		box->TR->RelPosFromPos();
		box->BL->ParentQuad = ParentQuad;
		box->BL->RelPosFromPos();
	}

	void ObjectClass::AddQuad( const std::shared_ptr<Quad> &quad )
	{
		AddQuad( quad, true );
	}

	void ObjectClass::AddQuad( const std::shared_ptr<Quad> &quad, bool ChangeParent )
	{
		quad->Update();
		QuadList.push_back( quad );
		quad->ParentObject = this;
		if ( ChangeParent )
			ParentQuad->AddQuadChild( quad );
	}

	void ObjectClass::RemoveQuad( const std::shared_ptr<BaseQuad> &quad )
	{
		if ( quad->ParentQuad != 0 )
			quad->ParentQuad->RemoveQuadChild( quad, false );

		if ( dynamic_cast<Quad*>( quad ) != 0 )
		{
			std::vector<BaseQuad*> ChildQuads = std::vector<BaseQuad*>( ( static_cast<Quad*>( quad ) )->Children );
			for ( std::vector<BaseQuad*>::const_iterator child_quad = ChildQuads.begin(); child_quad != ChildQuads.end(); ++child_quad )
				( static_cast<Quad*>( quad ) )->RemoveQuadChild( *child_quad );
		}

		QuadList.Remove( quad );
	}

	void ObjectClass::ContainedDraw()
	{
		if ( BoxList.size() > 0 )
		{
			float scalex = ( BoxList[ 0 ]->TR->Pos->X - BoxList[ 0 ]->BL->Pos->X ) / 2;
			float scaley = ( BoxList[ 0 ]->TR->Pos->Y - BoxList[ 0 ]->BL->Pos->Y ) / 2;
			float locx = ( BoxList[ 0 ]->TR->Pos->X + BoxList[ 0 ]->BL->Pos->X ) / 2;
			float locy = ( BoxList[ 0 ]->TR->Pos->Y + BoxList[ 0 ]->BL->Pos->Y ) / 2;
			if ( xFlip )
				locx = FlipCenter.X - ( locx - FlipCenter.X );
			if ( yFlip )
				locy = FlipCenter.Y - ( locy - FlipCenter.Y );

			ContainedQuad->Center->Move( Vector2( locx, locy ) );

			ContainedQuad->xAxis->RelPos = Vector2( 1, 0 );
			ContainedQuad->yAxis->RelPos = Vector2( 0, 1 );

			Tools::QDrawer->Flush();
			ContainedQuad->Scale( Vector2( scalex, scaley ) );

			Draw( true );
			Tools::QDrawer->Flush();
		}
	}

	void ObjectClass::Draw( bool UpdateFirst )
	{
		std::shared_ptr<CloudberryKingdom::EzEffectWad> EffectWad = Tools::EffectWad;

		if ( UpdateFirst )
			Update( 0 );

		if ( ( xFlip || yFlip ) && !BoxesOnly && QuadList.size() > 0 )
			for ( std::vector<EzEffect*>::const_iterator fx = MyEffects.begin(); fx != MyEffects.end(); ++fx )
				( *fx )->FlipVector->SetValue( Vector2( xFlip ? 1 : -1, yFlip ? 1 : -1 ) );
		if ( xFlip || yFlip )
			for ( std::vector<EzEffect*>::const_iterator fx = MyEffects.begin(); fx != MyEffects.end(); ++fx )
				( *fx )->FlipCenter->SetValue( FlipCenter );

		if ( !BoxesOnly && QuadList.size() > 0 )
			for ( std::vector<BaseQuad*>::const_iterator quad = QuadList.begin(); quad != QuadList.end(); ++quad )
				( *quad )->Draw();

		// Extra quad to draw. Pretty fucking leaky hack.
		if ( DrawExtraQuad && ExtraQuadToDraw != 0 )
		{
			QDrawer->Flush();

			std::shared_ptr<CloudberryKingdom::EzTexture> Hold = ExtraQuadToDraw->MyTexture;
			ExtraQuadToDraw->MyTexture = ExtraQuadToDrawTexture;
			ExtraQuadToDraw->Draw( QDrawer );
			ExtraQuadToDraw->MyTexture = Hold;
		}

		QDrawer->Flush();

		if ( ( xFlip || yFlip ) && !BoxesOnly && QuadList.size() > 0 )
			for ( std::vector<EzEffect*>::const_iterator fx = MyEffects.begin(); fx != MyEffects.end(); ++fx )
				( *fx )->FlipVector->SetValue( Vector2( -1, -1 ) );
	}

	std::shared_ptr<SpriteAnim> ObjectClass::AnimToSpriteFrames( int anim, int NumFrames, bool Loop, Vector2 Padding )
	{
		return AnimToSpriteFrames( anim, NumFrames, Loop, 0, AnimLength[ anim ], Padding );
	}

	std::shared_ptr<SpriteAnim> ObjectClass::AnimToSpriteFrames( int anim, int NumFrames, bool Loop, float StartT, float EndT, Vector2 Padding )
	{
		std::shared_ptr<SpriteAnim> Sprites = std::make_shared<SpriteAnim>();
		Sprites->Frames = std::vector<Texture2D*>( NumFrames );

		if ( NumFrames <= 1 )
			Sprites->dt = 1;
		else
		{
			if ( Loop )
				Sprites->dt = ( EndT + 1 ) / static_cast<float>( NumFrames );
			else
				Sprites->dt = EndT / static_cast<float>( NumFrames );
		}

		this->anim = anim;
		Update( 0 );
		for ( int i = 0; i < NumFrames; i++ )
		{
			SetAnimT( StartT + i * Sprites->dt, Loop );
			Update( 0 );

			Sprites->Frames[ i ] = DrawToTexture( Tools::Device, Tools::EffectWad, Padding );
		}

		return Sprites;
	}

	std::shared_ptr<Texture2D> ObjectClass::DrawToTexture( const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<EzEffectWad> &EffectWad, Vector2 Padding )
	{
		Vector4 HoldCameraPos = EffectWad->getCameraPosition();
		float HoldCameraAspect = EffectWad->EffectList[ 0 ]->xCameraAspect->GetValueSingle();

		device->SetRenderTarget( ToTextureRenderTarget );
		device->Clear( Color::Transparent );
		for ( std::vector<EzEffect*>::const_iterator fx = MyEffects.begin(); fx != MyEffects.end(); ++fx )
			( *fx )->effect->CurrentTechnique = ( *fx )->Simplest;
		float scalex = Padding.X + ( BoxList[ 0 ]->TR->Pos->X - BoxList[ 0 ]->BL->Pos->X ) / 2;
		float scaley = Padding.Y + ( BoxList[ 0 ]->TR->Pos->Y - BoxList[ 0 ]->BL->Pos->Y ) / 2;
		float posx = ( BoxList[ 0 ]->TR->Pos->X + BoxList[ 0 ]->BL->Pos->X ) / 2;
		float posy = ( BoxList[ 0 ]->TR->Pos->Y + BoxList[ 0 ]->BL->Pos->Y ) / 2;
		if ( xFlip )
			posx = FlipCenter.X - ( posx - FlipCenter.X );
		if ( yFlip )
			posy = FlipCenter.Y - ( posy - FlipCenter.Y );

		EffectWad->SetCameraPosition( Vector4( posx, posy, 1 / scalex, 1 / scaley ) );
		for ( std::vector<EzEffect*>::const_iterator fx = MyEffects.begin(); fx != MyEffects.end(); ++fx )
			( *fx )->xCameraAspect->SetValue( 1 );
		ContainedDraw();
		device->SetRenderTarget( Tools::DestinationRenderTarget );
		Tools::Render->ResetViewport();

		EffectWad->SetCameraPosition( HoldCameraPos );
		for ( std::vector<EzEffect*>::const_iterator fx = MyEffects.begin(); fx != MyEffects.end(); ++fx )
			( *fx )->xCameraAspect->SetValue( HoldCameraAspect );

		std::shared_ptr<Texture2D> tex = ToTextureRenderTarget;
		std::vector<Color> Array = std::vector<Color>( tex->Width * tex->Height );
		tex->GetData<Color>( Array );
		std::shared_ptr<Texture2D> tex2 = std::make_shared<Texture2D>( Tools::Device, tex->Width, tex->Height );
		tex2->SetData<Color>( Array );

		Array.clear();

		return tex2;
	}

	void ObjectClass::InitializeInstanceFields()
	{
		LoadingRunSpeed = .135f;
		CapeThickness = 16;
		p1_Left = Vector2( -63, -45 );
		p2_Left = Vector2( -27, 0 );
		p1_Right = Vector2( 63, -45 );
		p2_Right = Vector2( 27, 0 );
		ContainedQuadAngle = 0;
		ContainedQuad = std::make_shared<Quad>();
		DoSpriteAnim = true;
		OriginalRenderTarget = true;
		ExtraQuadToDraw = 0;
		ExtraQuadToDrawTexture = 0;
		DrawExtraQuad = false;
	}
}
