#include "MasterHack.h"

#include <global_header.h>

#include <Hacks\List.h>

namespace CloudberryKingdom
{

	void Bob_PostConstruct( const std::shared_ptr<Bob> &This, const std::shared_ptr<BobPhsx> &type, bool boxesOnly )
	{
		This->SetHeroPhsx( This->MyHeroType );
		This->SetColorScheme( This->MyHeroType->Prototype->MyColorScheme );
	}

	void Awardment_PostConstruct( const std::shared_ptr<Awardment> &This )
	{
		if ( This->Unlockable != 0 )
			This->Unlockable->AssociatedAward = This->shared_from_this();

		Awardments::Awards.push_back( This->shared_from_this() );
	}

	void Quad_PostConstruct( const std::shared_ptr<Quad> &This, const std::shared_ptr<Quad> &quad, bool DeepClone )
	{
		This->InitVertices();

		quad->Center->Clone( This->Center, DeepClone );
		quad->xAxis->Clone( This->xAxis, DeepClone );
		quad->yAxis->Clone( This->yAxis, DeepClone );
		for ( int i = 0; i < 4; i++ )
			quad->Corner[ i ]->Clone( This->Corner[ i ], DeepClone );

		for ( int i = 0; i < This->NumVertices; i++ )
			This->Vertices[ i ] = quad->Vertices[ i ];
	}

	void ObjectClass_PostConstruct( const std::shared_ptr<ObjectClass> &This, const std::shared_ptr<QuadDrawer> &Drawer, const std::shared_ptr<GraphicsDevice> &device, const std::shared_ptr<PresentationParameters> &pp, int Width, int Height, const std::shared_ptr<EzEffect> &BaseEffect, const std::shared_ptr<EzTexture> &BaseTexture )
	{
		This->VersionNumber = ObjectClass::ObjectClassVersionNumber;

		This->AnimQueue = std::queue<std::shared_ptr<AnimQueueEntry> >();

		This->CenterFlipOnBox = true;

		This->ParentQuad = std::make_shared<Quad>();
		This->ParentQuad->InitVertices();
		This->ParentQuad->SetColor( Color( 1.f, 1.f, 1.f ) );
		This->ParentQuad->ParentObject = This->shared_from_this();
		This->ParentQuad->MyEffect = BaseEffect;
		This->ParentQuad->MyTexture = BaseTexture;

		This->QuadList = std::vector<std::shared_ptr<BaseQuad> >();
		This->BoxList = std::vector<std::shared_ptr<ObjectBox> >();

		This->AnimLength = std::vector<int>( 50 );
		This->AnimSpeed = std::vector<float>( 50 );
		This->AnimName = std::vector<std::wstring>( 50 );
		for ( int i = 0; i < 50; i++ )
		{
			This->AnimName[ i ] = _T( "Anim_" ) + StringConverterHelper::toString( i );
			This->AnimSpeed[ i ] = 1;
		}

		This->QDrawer = Drawer;

		if ( Height > 0 && Width > 0 )
			This->InitRenderTargets( device, pp, Width, Height );

		This->UpdateEffectList();
	}

	void ObjectClass_PostConstruct_3params( const std::shared_ptr<ObjectClass> &This, const std::shared_ptr<ObjectClass> &obj, bool _BoxesOnly, bool DeepClone )
	{
		This->InitializeInstanceFields();
		This->LoadingRunSpeed = obj->LoadingRunSpeed;

		This->CapeThickness = obj->CapeThickness;
		This->p1_Left = obj->p1_Left;
		This->p2_Left = obj->p2_Left;
		This->p1_Right = obj->p1_Right;
		This->p2_Right = obj->p2_Right;



		This->Linear = obj->Linear;

		This->VersionNumber = obj->VersionNumber;

		This->BoxesOnly = _BoxesOnly;

		This->LoadingRunSpeed = obj->LoadingRunSpeed;

		This->AnimQueue = std::queue<std::shared_ptr<AnimQueueEntry> >();
		std::queue<std::shared_ptr<AnimQueueEntry> > QueueCopy = std::queue<std::shared_ptr<AnimQueueEntry> >( obj->AnimQueue );
		std::vector<std::shared_ptr<AnimQueueEntry> > array_Renamed;
		while( !QueueCopy.empty() )
		{
			array_Renamed.push_back( QueueCopy.front() );
			QueueCopy.pop();
		}

		// FIXME: Make sure make_shared actually copies the object.
		if ( array_Renamed.size() > 0 )
		{
			This->LastAnimEntry = std::make_shared<AnimQueueEntry>( array_Renamed[ array_Renamed.size() - 1 ] );
			for ( size_t i = 0; i < array_Renamed.size() - 1; i++ )
				This->AnimQueue.push( std::make_shared<AnimQueueEntry>( array_Renamed[ i ] ) );
			This->AnimQueue.push( This->LastAnimEntry );
		}



		This->CenterFlipOnBox = obj->CenterFlipOnBox;

		This->ParentQuad = std::make_shared<Quad>( obj->ParentQuad, DeepClone );
		Quad_PostConstruct( This->ParentQuad, obj->ParentQuad, DeepClone );
		This->ParentQuad->ParentObject = This->shared_from_this();
		This->ParentQuad->MyEffect = obj->ParentQuad->MyEffect;
		This->ParentQuad->MyTexture = obj->ParentQuad->MyTexture;

		This->MySkinTexture = obj->MySkinTexture;
		This->MySkinEffect = obj->MySkinEffect;

		// Add quads and boxes            
		if ( !This->BoxesOnly )
		{
			This->QuadList = std::vector<std::shared_ptr<BaseQuad> >();

			for ( std::vector<std::shared_ptr<BaseQuad> >::const_iterator quad = obj->QuadList.begin(); quad != obj->QuadList.end(); ++quad )
			{
				if ( dynamic_cast<Quad*>( ( *quad ).get() ) != 0 )
				{
					// FIXME: Check static_pointer_cast.
					std::shared_ptr<Quad> nquad = std::make_shared<Quad>( std::static_pointer_cast<Quad>( *quad ), DeepClone );
					Quad_PostConstruct( nquad, std::static_pointer_cast<Quad>( *quad ), DeepClone );
					This->QuadList.push_back( nquad );
					nquad->ParentObject = This->shared_from_this();
					if ( ( *quad )->ParentQuad == ( *quad )->ParentObject->ParentQuad )
						This->ParentQuad->AddQuadChild( nquad );
				}
			}
		}

		// Clone boxes
		This->BoxList = std::vector<std::shared_ptr<ObjectBox> >();
		for ( std::vector<std::shared_ptr<ObjectBox> >::const_iterator box = obj->BoxList.begin(); box != obj->BoxList.end(); ++box )
			This->BoxList.push_back( std::make_shared<ObjectBox>( *box, DeepClone ) );


		// Make sure pointers match up
		if ( !This->BoxesOnly && This->QuadList.size() > 0 )
		{
			for ( size_t i = 0; i < obj->QuadList.size(); i++ )
			{
				// Preserve Parent-Point relationship (for quads attached to splines)
				if ( dynamic_cast<Quad*>( obj->QuadList[ i ].get() ) != 0 )
				{
					// FIXME: Check static_pointer_cast.
					std::shared_ptr<BaseQuad> parent = ( std::static_pointer_cast<Quad>( obj->QuadList[ i ] ) )->Center->ParentQuad;
					if ( parent != 0 )
					{
						if ( parent == obj->ParentQuad )
							( std::static_pointer_cast<Quad>( This->QuadList[ i ] ) )->Center->ParentQuad = This->ParentQuad;
						else
						{
							int j = IndexOf( obj->QuadList, parent );
							( std::static_pointer_cast<Quad>( This->QuadList[ i ] ) )->Center->ParentQuad = This->QuadList[ j ];
						}
					}
				}

				// Preserve Parent-Child quad relationship
				if ( obj->QuadList[ i ]->ParentQuad != obj->ParentQuad )
				{
					//((Quad)QuadList[obj.QuadList.IndexOf(obj.QuadList[i].ParentQuad)]).AddQuadChild(QuadList[i]);
					//((Quad)                               QuadList[obj.QuadList.IndexOf(                                obj.QuadList[i].ParentQuad)]).          AddQuadChild(QuadList[i]);
					( std::static_pointer_cast<Quad>( This->QuadList[ IndexOf<std::shared_ptr<BaseQuad> >( obj->QuadList, obj->QuadList[ i ]->ParentQuad ) ] ) )->AddQuadChild( This->QuadList[ i ] );
				}
			}
		}
		for ( size_t i = 0; i < obj->BoxList.size(); i++ )
		{
			if ( !This->BoxesOnly && obj->BoxList[ i ]->BL->ParentQuad != obj->ParentQuad )
			{
				//BoxList[i].TR.ParentQuad = BoxList[i].BL.ParentQuad = (Quad)QuadList[obj.QuadList.IndexOf(obj.BoxList[i].BL.ParentQuad)];
				//    BoxList[i].TR.ParentQuad	   =       BoxList[i].BL.ParentQuad     = (Quad)							    QuadList[obj.QuadList.IndexOf(obj.BoxList[i].BL.ParentQuad)];
				This->BoxList[ i ]->TR->ParentQuad = This->BoxList[ i ]->BL->ParentQuad = std::static_pointer_cast<Quad>( This->QuadList[ IndexOf( obj->QuadList, obj->BoxList[ i ]->BL->ParentQuad ) ] );
			}
			else
				This->BoxList[ i ]->TR->ParentQuad = This->BoxList[ i ]->BL->ParentQuad = This->ParentQuad;
		}


		This->Play = obj->Play;
		This->Loop = obj->Loop;
		This->anim = obj->anim;
		This->t = obj->t;

		This->AnimLength = std::vector<int>( 50 );
		//obj->AnimLength.CopyTo( AnimLength, 0 );
		This->AnimLength.assign( obj->AnimLength.begin(), obj->AnimLength.end() );

		This->AnimSpeed = std::vector<float>( 50 );
		//obj->AnimSpeed.CopyTo( AnimSpeed, 0 );
		This->AnimSpeed.assign( obj->AnimSpeed.begin(), obj->AnimSpeed.end() );

		This->AnimName = std::vector<std::wstring>( 50 );
		//obj->AnimName.CopyTo( AnimName, 0 );
		This->AnimName.assign( obj->AnimName.begin(), obj->AnimName.end() );

		This->QDrawer = obj->QDrawer;

		This->InitRenderTargets( obj );

		This->UpdateEffectList();
	}

}