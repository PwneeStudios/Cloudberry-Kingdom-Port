#include <global_header.h>




namespace CloudberryKingdom
{

	void SimpleObject::Release()
	{
		//return;
		if ( Released )
			return;
		Released = true;

		if ( Quads.size() > 0 )
			for ( int i = 0; i < Quads.size(); i++ )
				Quads[ i ].Release();
			//foreach (SimpleQuad quad in Quads)
				//quad.Release();
		if ( Boxes.size() > 0 )
			for ( std::vector<CloudberryKingdom::SimpleBox*>::const_iterator box = Boxes.begin(); box != Boxes.end(); ++box )
				( *box )->Release();
		AnimQueue.clear();
		LastAnimEntry.reset();
		AnimLength.clear();
		AnimName.clear();
		AnimSpeed.clear();

		MyEffects.clear();
	}

	void SimpleObject::UpdateEffectList()
	{
		if ( Quads.empty() || Quads.empty() )
			return;

		if ( MyEffects.empty() )
			MyEffects = std::vector<EzEffect*>();
		else
			MyEffects.clear();

		for ( int i = 0; i < Quads.size(); i++ )
			if ( !std::find( MyEffects.begin(), MyEffects.end(), Quads[ i ].MyEffect ) != MyEffects.end() )
				MyEffects.push_back( Quads[ i ].MyEffect );
	}

	int SimpleObject::GetQuadIndex( const std::wstring &name )
	{
		for ( int i = 0; i < Quads.size(); i++ )
		{
//C# TO C++ CONVERTER TODO TASK: The following .NET 'String.Compare' reference is not converted:
			if ( std::wstring::Compare( Quads[ i ].Name, name, StringComparison::OrdinalIgnoreCase ) == 0 )
				return i;
		}

		return -1;
	}

	void SimpleObject::Scale( float scale )
	{
		Base.e1 *= scale;
		Base.e2 *= scale;
	}

	void SimpleObject::SetColor( Color color )
	{
		if ( Quads.size() > 0 )
			for ( int i = 0; i < Quads.size(); i++ )
				Quads[ i ].SetColor( color );
	}

	SimpleObject::SimpleObject( const std::shared_ptr<SimpleObject> &obj, bool BoxesOnly )
	{
		Constructor( obj, BoxesOnly, false );
	}

	void SimpleObject::Constructor( const std::shared_ptr<SimpleObject> &obj, bool BoxesOnly, bool DeepCopy )
	{
		Base = obj->Base;

		CenterFlipOnBox = obj->CenterFlipOnBox;

		if ( !BoxesOnly )
		{
			Quads = std::vector<SimpleQuad>( obj->Quads.size() );
			for ( int i = 0; i < obj->Quads.size(); i++ )
				Quads[ i ] = SimpleQuad( obj->Quads[ i ] );
		}

		Boxes = std::vector<SimpleBox*>( obj->Boxes.size() );
		for ( int i = 0; i < obj->Boxes.size(); i++ )
			Boxes[ i ] = std::make_shared<SimpleBox>( obj->Boxes[ i ] );

		AnimQueue = std::queue<AnimQueueEntry*>();
		std::vector<AnimQueueEntry*> array_Renamed = obj->AnimQueue.ToArray();
		if ( array_Renamed.size() > 0 )
		{
			LastAnimEntry = std::make_shared<AnimQueueEntry>( array_Renamed[ array_Renamed.size() - 1 ] );
			for ( int i = 0; i < array_Renamed.size() - 1; i++ )
				AnimQueue.push( std::make_shared<AnimQueueEntry>( array_Renamed[ i ] ) );
			AnimQueue.push( LastAnimEntry );
		}

		Play = obj->Play;
		Loop = obj->Loop;
		anim = obj->anim;
		t = obj->t;

		if ( DeepCopy )
		{
			AnimLength = std::vector<int>( 50 );
			obj->AnimLength.CopyTo( AnimLength, 0 );
			AnimSpeed = std::vector<float>( 50 );
			obj->AnimSpeed.CopyTo( AnimSpeed, 0 );
			AnimName = std::vector<std::wstring*>( 50 );
			obj->AnimName.CopyTo( AnimName, 0 );

			UpdateEffectList();
		}
		else
		{
			AnimLength = obj->AnimLength;
			AnimSpeed = obj->AnimSpeed;
			AnimName = obj->AnimName;

			MyEffects = obj->MyEffects;
		}
	}

	SimpleObject::SimpleObject( const std::shared_ptr<ObjectClass> &obj )
	{
		Base.Init();

		CenterFlipOnBox = obj->CenterFlipOnBox;

		Quads = std::vector<SimpleQuad>( obj->QuadList.size() );
		for ( int i = 0; i < obj->QuadList.size(); i++ )
			Quads[ i ] = SimpleQuad( static_cast<Quad*>( obj->QuadList[ i ] ) );

		Boxes = std::vector<SimpleBox*>( obj->BoxList.size() );
		for ( int i = 0; i < obj->BoxList.size(); i++ )
			Boxes[ i ] = std::make_shared<SimpleBox>( obj->BoxList[ i ] );

		AnimQueue = std::queue<AnimQueueEntry*>();
		std::vector<AnimQueueEntry*> array_Renamed = obj->AnimQueue.ToArray();
		if ( array_Renamed.size() > 0 )
		{
			LastAnimEntry = std::make_shared<AnimQueueEntry>( array_Renamed[ array_Renamed.size() - 1 ] );
			for ( int i = 0; i < array_Renamed.size() - 1; i++ )
				AnimQueue.push( std::make_shared<AnimQueueEntry>( array_Renamed[ i ] ) );
			AnimQueue.push( LastAnimEntry );
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

		UpdateEffectList();
	}

	Microsoft::Xna::Framework::Vector2 SimpleObject::GetBoxCenter( int i )
	{
		Vector2 c = Boxes[ i ]->Center();
		if ( xFlip )
			c.X = FlipCenter.X - ( c.X - FlipCenter.X );
		if ( yFlip )
			c.Y = FlipCenter.Y - ( c.Y - FlipCenter.Y );
		return c;
	}

	void SimpleObject::CopyUpdate( const std::shared_ptr<SimpleObject> &source )
	{
		Vector2 shift = Base.Origin - source->Base.Origin;

		if ( Quads.size() > 0 )
			for ( int i = 0; i < Quads.size(); i++ )
				Quads[ i ].CopyUpdate( source->Quads[ i ], shift );

		for ( int i = 0; i < Boxes.size(); i++ )
			Boxes[ i ]->CopyUpdate( source->Boxes[ i ], shift );

		if ( Boxes.size() > 0 )
			FlipCenter = Boxes[ 0 ]->Center();
		else
			FlipCenter = Base.Origin;
	}

	void SimpleObject::UpdateQuads()
	{
		if ( Quads.size() > 0 )
			for ( int i = 0; i < Quads.size(); i++ )
				Quads[ i ].Update( Base );
	}

	void SimpleObject::UpdateBoxes()
	{
		for ( int i = 0; i < Boxes.size(); i++ )
			Boxes[ i ]->Update( Base );

		if ( Boxes.size() > 0 )
			FlipCenter = Boxes[ 0 ]->Center();
		else
			FlipCenter = Base.Origin;
	}

	void SimpleObject::Update()
	{
		UpdateQuads();

		UpdateBoxes();
	}

	void SimpleObject::UpdatedShift( Vector2 shift )
	{
		for ( int i = 0; i < Quads.size(); i++ )
			Quads[ i ].UpdatedShift( shift );
	}

	void SimpleObject::Draw()
	{
		Draw( Tools::QDrawer, Tools::EffectWad );
	}

	void SimpleObject::Draw( const std::shared_ptr<QuadDrawer> &QDrawer, const std::shared_ptr<EzEffectWad> &EffectWad )
	{
		int n = 0;
		if ( Quads.size() > 0 )
			n = Quads.size();

		Draw( QDrawer, EffectWad, 0, n - 1 );
	}

	void SimpleObject::Draw( const std::shared_ptr<QuadDrawer> &QDrawer, const std::shared_ptr<EzEffectWad> &EffectWad, int StartIndex, int EndIndex )
	{
		if ( xFlip || yFlip )
			for ( std::vector<EzEffect*>::const_iterator fx = MyEffects.begin(); fx != MyEffects.end(); ++fx )
			{
				( *fx )->FlipCenter->SetValue( FlipCenter );
				( *fx )->FlipVector->SetValue( Vector2( xFlip ? 1 : -1, yFlip ? 1 : -1 ) );
			}


		for ( int i = StartIndex; i <= EndIndex; i++ )
			QDrawer->DrawQuad( Quads[ i ] );

		if ( xFlip || yFlip )
		{
			QDrawer->Flush();
			for ( std::vector<EzEffect*>::const_iterator fx = MyEffects.begin(); fx != MyEffects.end(); ++fx )
				( *fx )->FlipVector->SetValue( Vector2( -1, -1 ) );
		}
	}

	void SimpleObject::DrawQuad( SimpleQuad &Quad_Renamed )
	{
		if ( xFlip || yFlip )
			for ( std::vector<EzEffect*>::const_iterator fx = MyEffects.begin(); fx != MyEffects.end(); ++fx )
			{
				( *fx )->FlipCenter->SetValue( FlipCenter );
				( *fx )->FlipVector->SetValue( Vector2( xFlip ? 1 : -1, yFlip ? 1 : -1 ) );
			}

		Tools::QDrawer->DrawQuad( Quad_Renamed );

		if ( xFlip || yFlip )
		{
			Tools::QDrawer->Flush();
			for ( std::vector<EzEffect*>::const_iterator fx = MyEffects.begin(); fx != MyEffects.end(); ++fx )
				( *fx )->FlipVector->SetValue( Vector2( -1, -1 ) );
		}
	}

	void SimpleObject::EnqueueTransfer( int _anim, float _destT, float speed, bool DestLoop )
	{
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

	void SimpleObject::EnqueueAnimation( int _anim, float startT, bool loop )
	{
		EnqueueTransfer( _anim, startT,.5f, loop );

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

	int SimpleObject::DestinationAnim()
	{
		if ( AnimQueue.size() > 0 )
			return LastAnimEntry->anim;
		else
			return anim;
	}

	void SimpleObject::DequeueTransfers()
	{
		while ( AnimQueue.size() > 0 && AnimQueue.front()->Type == AnimQueueEntryType_TRANSFER )
			AnimQueue.pop();
	}

	void SimpleObject::PlayUpdate( float DeltaT )
	{
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
			if ( t > CurAnimQueueEntry->EndT && t - DeltaT <= CurAnimQueueEntry->EndT )
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
			if ( Quads.size() > 0 )
				for ( int i = 0; i < Quads.size(); i++ )
					if ( Quads[ i ].Animated )
						Quads[ i ].Calc( anim, t, AnimLength[ anim ], Loop, Linear );
			for ( int i = 0; i < Boxes.size(); i++ )
				if ( Boxes[ i ]->Animated )
					Boxes[ i ]->Calc( anim, t, AnimLength[ anim ], Loop, Linear );
		}
		else
		{
			if ( Quads.size() > 0 )
				for ( int i = 0; i < Quads.size(); i++ )
					Quads[ i ].Transfer( anim, CurAnimQueueEntry->DestT, AnimLength[ anim ], CurAnimQueueEntry->Loop, Linear, t );
			for ( int i = 0; i < Boxes.size(); i++ )
				Boxes[ i ]->Transfer( anim, CurAnimQueueEntry->DestT, AnimLength[ anim ], CurAnimQueueEntry->Loop, Linear, t );
		}
	}

	void SimpleObject::SetHold()
	{
		if ( Quads.size() > 0 )
			for ( int i = 0; i < Quads.size(); i++ )
				Quads[ i ].SetHold();
		for ( int i = 0; i < Boxes.size(); i++ )
			Boxes[ i ]->SetHold();
	}

	void SimpleObject::Read( int anim, int frame )
	{
		if ( Quads.size() > 0 )
			for ( int i = 0; i < Quads.size(); i++ )
				Quads[ i ].ReadAnim( anim, frame );
		for ( int i = 0; i < Boxes.size(); i++ )
			Boxes[ i ]->ReadAnim( anim, frame );
	}
}
