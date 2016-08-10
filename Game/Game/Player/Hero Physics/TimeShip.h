#ifndef TIMESHIP
#define TIMESHIP

#include <small_header.h>

#include "Game/Player/Hero Physics/Spaceship.h"

namespace CloudberryKingdom
{

	struct BobPhsxTimeship : public BobPhsxSpaceship
	{

		virtual ~BobPhsxTimeship()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxTimeship" );
#endif
		}

	
		static void InitializeStatics();
	
		static float KeepUnused( float UpgradeLevel );

		// Singleton

		virtual void InitSingleton();
		static boost::shared_ptr<BobPhsxTimeship> instance;
		const static boost::shared_ptr<BobPhsxTimeship> &getInstance();

		//virtual boost::shared_ptr<BobPhsx> Clone();
		//void CopyTo( const boost::shared_ptr<BobPhsxSpaceship> &bob );

		// Instancable struct
        int AutoMoveLength, AutoMoveType, AutoStrafeLength;
        int AutoDirLength, AutoDir;

        int RndMoveType;
	
		BobPhsxTimeship();

		virtual void DefaultValues();

		virtual void Init( const boost::shared_ptr<Bob> &bob );

		virtual void PhsxStep();

		virtual void SideHit( ColType side, const boost::shared_ptr<BlockBase> &block );

		virtual void ModData( boost::shared_ptr<MakeData> &makeData, const boost::shared_ptr<StyleData> &Style );

		void InitializeInstanceFields();
	};

}


#endif	//#ifndef TIMESHIP
