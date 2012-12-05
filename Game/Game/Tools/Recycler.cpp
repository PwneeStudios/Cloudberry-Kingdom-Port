#include <global_header.h>



namespace CloudberryKingdom
{

	void RecycleBin::Release()
	{
		for ( std::vector<std::shared_ptr<ObjectBase> >::const_iterator obj = FullObject.begin(); obj != FullObject.end(); ++obj )
			if ( ( *obj )->getCore()->MyLevel == 0 )
				( *obj )->Release();

		for ( std::vector<std::shared_ptr<ObjectBase> >::const_iterator obj = BoxObject.begin(); obj != BoxObject.end(); ++obj )
			if ( ( *obj )->getCore()->MyLevel == 0 )
				( *obj )->Release();
	}

	RecycleBin::RecycleBin( ObjectType type )
	{
		MyType = type;

		/*FullObject = std::stack<std::shared_ptr<ObjectBase> >();
		BoxObject = std::stack<std::shared_ptr<ObjectBase> >();*/
	}

	std::shared_ptr<ObjectBase> RecycleBin::GetObject( bool BoxesOnly )
	{
		if ( BoxesOnly )
			return GetObject_BoxesOnly();
		else
			return GetObject_Graphical();
	}

	std::shared_ptr<ObjectBase> RecycleBin::GetObject_BoxesOnly()
	{
		return __GetObject( true );
	}

	std::shared_ptr<ObjectBase> RecycleBin::GetObject_Graphical()
	{
		return __GetObject( false );
	}

	std::shared_ptr<ObjectBase> RecycleBin::__GetObject( bool BoxesOnly )
	{
		std::shared_ptr<ObjectBase> obj = 0;

		//lock (this)
		{
			if ( BoxesOnly )
			{
				if ( BoxObject.size() > 0 )
				{
					obj = BoxObject.back();
					BoxObject.pop_back();
				}
			}
			else
			{
				if ( FullObject.size() > 0 )
				{
					obj = FullObject.back();
					FullObject.pop_back();
				}
			}

			if ( obj != 0 )
				obj->MakeNew();
			else
				obj = NewObject( BoxesOnly );
		}

		return obj;
	}

	void RecycleBin::CollectObject( const std::shared_ptr<ObjectBase> &obj )
	{
		if ( obj->getCore()->MarkedForDeletion )
			return;

		obj->getCore()->MarkedForDeletion = true;
		obj->getCore()->Active = false;
		obj->getCore()->Show = false;

		// If the object belongs to a level, add this object to the level's
		// pre-recycle bin, to be actually recycled when the level cleans its
		// object lists.
		if ( obj->getCore()->MyLevel != 0 )
		{
			obj->getCore()->MyLevel->PreRecycleBin.push_back(obj);
			return;
		}

		//lock (this)
		{
			if ( obj->getCore()->BoxesOnly )
				BoxObject.push_back( obj );
			else
			{
	//                    if (FullObject.Contains(obj))
	  //                      Console.WriteLine("@@@@@@ Double recyled!");
				FullObject.push_back( obj );
			}
		}
	}

	std::shared_ptr<ObjectBase> RecycleBin::NewObject( bool BoxesOnly )
	{
		switch ( MyType )
		{
			case ObjectType_FLYING_BLOB:
				return std::make_shared<FlyingBlob>( BoxesOnly );
			case ObjectType_BLOCK_EMITTER:
				return std::make_shared<BlockEmitter>( BoxesOnly );
			case ObjectType_COIN:
				return std::make_shared<Coin>( BoxesOnly );
			case ObjectType_SPIKE:
				return std::make_shared<Spike>( BoxesOnly );
			case ObjectType_FIREBALL:
				return std::make_shared<Fireball>( BoxesOnly );
			case ObjectType_FIRE_SPINNER:
				return std::make_shared<FireSpinner>( BoxesOnly );
			case ObjectType_NORMAL_BLOCK:
				return std::make_shared<NormalBlock>( BoxesOnly );
			case ObjectType_MOVING_PLATFORM:
				return std::make_shared<MovingPlatform>( BoxesOnly );
			case ObjectType_MOVING_BLOCK:
				return std::make_shared<MovingBlock>( BoxesOnly );
			case ObjectType_FALLING_BLOCK:
				return std::make_shared<FallingBlock>( BoxesOnly );
			case ObjectType_BOUNCY_BLOCK:
				return std::make_shared<BouncyBlock>( BoxesOnly );
			case ObjectType_LAVA_BLOCK:
				//return new LavaBlock(BoxesOnly);
				return std::make_shared<LavaBlock_Castle>( BoxesOnly );
			case ObjectType_BOULDER:
				return std::make_shared<Boulder>( BoxesOnly );
			case ObjectType_SPIKEY_GUY:
				return std::make_shared<SpikeyGuy>( BoxesOnly );
			case ObjectType_CAMERA_ZONE:
				return std::make_shared<CameraZone>();
			case ObjectType_DOOR:
				return std::make_shared<Door>( BoxesOnly );
			case ObjectType_CHECKPOINT:
				return std::make_shared<Checkpoint>();
			case ObjectType_LASER:
				return std::make_shared<Laser>( BoxesOnly );
			case ObjectType_CLOUD:
				return std::make_shared<Cloud>( BoxesOnly );
			case ObjectType_GHOST_BLOCK:
				return std::make_shared<GhostBlock>( BoxesOnly );
			case ObjectType_CONVEYOR_BLOCK:
				return std::make_shared<ConveyorBlock>( BoxesOnly );
			case ObjectType_SPIKEY_LINE:
				return std::make_shared<SpikeyLine>( BoxesOnly );
			case ObjectType_FIRESNAKE:
				return std::make_shared<Firesnake>( BoxesOnly );

			case ObjectType_PENDULUM:
				return std::make_shared<Pendulum>( BoxesOnly );
			case ObjectType_SERPENT:
				return std::make_shared<Serpent>( BoxesOnly );
			case ObjectType_LAVA_DRIP:
				return std::make_shared<LavaDrip>( BoxesOnly );

			default:
				return 0;
				assert( !"No type found for desired object" );
				//throw ( std::exception( _T( "No type found for desired object" ) ) );
		}
	}

int Recycler::MetaCount = 0;
std::vector<std::shared_ptr<Recycler> > Recycler::MetaBin;

	std::shared_ptr<Recycler> Recycler::GetRecycler()
	{
		std::shared_ptr<Recycler> bin = 0;

//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( MetaBin )
		{
			MetaBinLock.Lock();

			MetaCount++;
			if ( MetaBin.empty() )
				return std::make_shared<Recycler>();

			bin = MetaBin.back();
			MetaBin.pop_back();

			MetaBinLock.Unlock();
		}

		return bin;
	}

	void Recycler::ReturnRecycler( const std::shared_ptr<Recycler> &recycler )
	{
		recycler->Empty();
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( MetaBin )
		{
			MetaBinLock.Lock();

			MetaCount--;
			MetaBin.push_back( recycler );

			MetaBinLock.Unlock();
		}
	}

	void Recycler::DumpMetaBin()
	{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
		//lock ( MetaBin )
		{
			MetaBinLock.Lock();

			for ( std::vector<std::shared_ptr<Recycler> >::const_iterator recycler = MetaBin.begin(); recycler != MetaBin.end(); ++recycler )
				( *recycler )->Empty( false );
			//GC::Collect();

			MetaBinLock.Unlock();
		}
	}

	Recycler::Recycler()
	{
		Init();
	}

	void Recycler::Init()
	{
		//Bins = new Dictionary<ObjectType, RecycleBin>();
		int N = ObjectType_LENGTH; //Tools::GetValues<ObjectType>()->Count(); //Enum.GetValues(typeof(ObjectType)).Length;
		Bins = std::vector<std::shared_ptr<RecycleBin> >( N );
	}

	std::shared_ptr<ObjectBase> Recycler::GetNewObject( ObjectType type, bool BoxesOnly )
	{
		if ( type == ObjectType_UNDEFINED )
			return 0;

		if ( Bins[ static_cast<int>( type ) ] == 0 )
			Bins[ static_cast<int>( type ) ] = std::make_shared<RecycleBin>( type );

		std::shared_ptr<ObjectBase> obj = Bins[ static_cast<int>( type ) ]->NewObject( BoxesOnly );

		return obj;
	}

	/*std::shared_ptr <ObjectBase> Recycler::operator []( ObjectType type, bool BoxesOnly )
	{
		return GetObject( type, BoxesOnly );
	}*/

	std::shared_ptr<ObjectBase> Recycler::GetObject( ObjectType type, bool BoxesOnly )
	{
		//if (type == ObjectType.FlyingBlob)
		//    Tools.Write("!");

		if ( type == ObjectType_UNDEFINED )
			//throw (new System.Exception("No type found for desired object"));
			return 0;

		//if (!Bins.ContainsKey(type))
		  //  Bins.Add(type, new RecycleBin(type));

		if ( Bins[ static_cast<int>( type ) ] == 0 )
			Bins[ static_cast<int>( type ) ] = std::make_shared<RecycleBin>( type );

		//return Bins[type].GetObject(BoxesOnly);
		std::shared_ptr<ObjectBase> obj = Bins[ static_cast<int>( type ) ]->GetObject( BoxesOnly );

		return obj;
	}

	void Recycler::CollectObject( const std::shared_ptr<ObjectBase> &obj )
	{
		CollectObject( obj, true );
	}

	void Recycler::CollectObject( const std::shared_ptr<ObjectBase> &obj, bool CollectAssociates )
	{
		if ( obj == 0 || obj->getCore()->MarkedForDeletion )
			return;

		// Actions to be taken when the object is deleted
		if ( !obj->getCore()->OnDeletionCodeRan )
		{
			if ( obj->getCore()->GenData.OnMarkedForDeletion != 0 )
				obj->getCore()->GenData.OnMarkedForDeletion->Apply();
			obj->OnMarkedForDeletion();

			obj->getCore()->OnDeletionCodeRan = true;
		}

		// Get the object type
		ObjectType type = obj->getCore()->MyType;
		if ( type == ObjectType_UNDEFINED )
		{
			obj->getCore()->MarkedForDeletion = true;
			obj->getCore()->Active = false;
			obj->getCore()->Show = false;
			return;
		}

		if ( Bins[ static_cast<int>( type ) ] == 0 )
			Bins[ static_cast<int>( type ) ] = std::make_shared<RecycleBin>( type );

		Bins[ static_cast<int>( type ) ]->CollectObject( obj );

		// Collect associate objects
		if ( CollectAssociates && obj->getCore()->Associations.size() > 0 )
			for ( size_t i = 0; i < obj->getCore()->Associations.size(); i++ )
				if ( obj->getCore()->Associations[ i ].Guid > 0 )
				{
					std::shared_ptr<ObjectBase> _obj = obj->getCore()->MyLevel->LookupGUID(obj->getCore()->Associations[ i ].Guid);
					if ( _obj == 0 )
						continue;

					// Delete the associated object if DeleteWhenDeleted flag is set
					if ( obj->getCore()->Associations[ i ].DeleteWhenDeleted )
						CollectObject( _obj );
					// Otherwise remove the association
					else
					{
						if ( _obj->getCore()->Associations.size() > 0 )
						{
							for ( size_t j = 0; j < _obj->getCore()->Associations.size(); j++ )
								if ( _obj->getCore()->Associations[ j ].Guid == obj->getCore()->MyGuid )
									_obj->getCore()->Associations[ j ].Guid = 0;
						}
					}
				}
	}

	void Recycler::Empty()
	{
		Empty( true );
	}

	void Recycler::Empty( bool DoGC )
	{
		for ( size_t i = 0; i < Bins.size(); i++ )
			if ( Bins[ i ] != 0 )
				Bins[ i ]->Release();

		Init();

		// FIXME: No GC.
		/*if ( DoGC )
			GC::Collect();*/
	}
}
