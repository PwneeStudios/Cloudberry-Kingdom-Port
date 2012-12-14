#ifndef TUNNEL
#define TUNNEL

#include <global_header.h>

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

	
		void SetTunnelObjParameter( const std::shared_ptr<ObjectBase> &obj );

		void Clean();

		void Clean( int i, int j );

	
		void CleanupTunnel( const std::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TUNNEL
