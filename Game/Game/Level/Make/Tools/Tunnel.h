#ifndef TUNNEL
#define TUNNEL

#include <global_header.h>

namespace CloudberryKingdom
{
	class ObjectBase;
}

namespace CloudberryKingdom
{
	class Level;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;

namespace CloudberryKingdom
{
	class TunnelFill
	{
		/// <summary>
		/// Whether the tunnel has a ceiling.
		/// </summary>
	public:
		bool TunnelCeiling;
		bool TunnelFloor;

		bool RemoveWarts;
		int HeadRoom;
		int Thickness;

		std::vector<std::vector<unsigned long long> > TunnelGUIDs;
		std::vector<std::vector<ObjectBase*> > TunnelObjs;

		TunnelFill();

	private:
		int N, M;
	public:
		void Init( int N, int M );

	private:
		void SetTunnelObjParameter( const std::shared_ptr<ObjectBase> &obj );

		void Clean();

		void Clean( int i, int j );

	public:
		void CleanupTunnel( const std::shared_ptr<Level> &level );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TUNNEL
