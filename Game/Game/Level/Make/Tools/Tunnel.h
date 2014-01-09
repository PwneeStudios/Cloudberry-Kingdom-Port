#ifndef TUNNEL
#define TUNNEL

#include <small_header.h>

//#include "Game/Objects/ObjectBase.h"
//#include "Game/Objects/In Game Objects/Grab/MakeData.h"
//#include "Game/Level/Level.h"


namespace CloudberryKingdom
{
	struct TunnelFill
	{
		/// <summary>
		/// Whether the tunnel has a ceiling.
		/// </summary>
	
		bool TunnelCeiling;
		bool TunnelFloor;

		bool RemoveWarts;
		int HeadRoom;
		int Thickness;

		std::vector<std::vector<unsigned long long> > TunnelGUIDs;
		std::vector<ObjectVec > TunnelObjs;

		TunnelFill();

	
		int N, M;
	
		void Init( int N, int M );

	
		void SetTunnelObjParameter( const boost::shared_ptr<ObjectBase> &obj );

		void Clean();

		void Clean( int i, int j );

	
		void CleanupTunnel( const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TUNNEL
