#ifndef FLYINGBLOB__AUTO
#define FLYINGBLOB__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	class PieceSeedData;
}

namespace CloudberryKingdom
{
	class Level;
}

namespace CloudberryKingdom
{
	class AutoGen_Parameters;
}

namespace CloudberryKingdom
{
	class FlyingBlob;
}

namespace CloudberryKingdom
{
	class Rand;
}

namespace CloudberryKingdom
{
	class ObjectBase;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class FlyingBlob_Parameters : public AutoGen_Parameters
	{
	public:
		enum MotionType
		{
			MotionType_VERTICAL,
			MotionType_HORIZONTAL,
			MotionType_AA,
			MotionType_CROSS,
			MotionType_STRAIGHT,
			MotionType_CIRLCES,
			MotionType_HEART,
			MotionType_ALL
		};
	public:
		class _Special
		{
			/// <summary>
			/// A special fill type. Creates a tunnel of flying blobs.
			/// </summary>
		public:
			bool Tunnel;

			/// <summary>
			/// A special fill type. One giant circle. All blobs orbit the same point.
			/// </summary>
			bool Pinwheel;
		};
	public:
		Param Range, Period, KeepUnused, Size;

		/// <summary>
		/// How far from the lowest point on the blob the computer must be
		/// in order to be allowed to use the blob.
		/// </summary>
		Param EdgeSafety;

		std::vector<int> MotionLevel;
		MotionType Motion;

		_Special Special;

		/// <summary>
		/// Whether the tunnel has a ceiling of flying blobs.
		/// </summary>
		bool TunnelCeiling;
		/// <summary>
		/// The size of the displacement for the blobs comprising the tunnel.
		/// </summary>
		float TunnelDisplacement;
		/// <summary>
		/// The motion type of the blobs comprising the tunnel.
		/// </summary>
		MotionType TunnelMotionType;

		std::vector<std::vector<unsigned long long> > TunnelGUIDs;


		FlyingBlob_Parameters();

		virtual void SetParameters( const std::shared_ptr<PieceSeedData> &PieceSeed, const std::shared_ptr<Level> &level );

	private:
		void InitializeInstanceFields();
	};

	class FlyingBlob_AutoGen : public AutoGen
	{
	private:
		static const std::shared_ptr<FlyingBlob_AutoGen> instance;
	public:
		const static std::shared_ptr<FlyingBlob_AutoGen> &getInstance() const;

//C# TO C++ CONVERTER TODO TASK: Static constructors are not allowed in native C++:
		static FlyingBlob_AutoGen();
	private:
		FlyingBlob_AutoGen();

	public:
		std::shared_ptr<AutoGen_Parameters> SetParameters( const std::shared_ptr<PieceSeedData> &data, const std::shared_ptr<Level> &level );

	private:
		void Circle( const std::shared_ptr<Level> &level, Vector2 Center, float Radius, int Num, int Dir );
		void Circle( const std::shared_ptr<Level> &level, Vector2 Center, float Radius, int Num, int Dir, float ModPeriod );

		void Pinwheel( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );


		void SetTunnelBlobParameter( const std::shared_ptr<FlyingBlob> &blob, const std::shared_ptr<FlyingBlob_Parameters> &Params, const std::shared_ptr<Rand> &Rnd );

		void Tunnel( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Clean( array_Renamed<ObjectBase*, 2> *array_Renamed );
		void Clean( array_Renamed<ObjectBase*, 2> *array_Renamed, int i, int j );
		void CleanupTunnel( const std::shared_ptr<Level> &level );

	public:
		void PreFill_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_1( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void PreFill_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const std::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void SetMoveType( const std::shared_ptr<FlyingBlob> &fblob, float Displacement, FlyingBlob_Parameters::MotionType mtype, const std::shared_ptr<Rand> &Rnd );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );

		std::shared_ptr<ObjectBase> CreateAt( const std::shared_ptr<Level> &level, Vector2 pos );

	private:
		std::shared_ptr<ObjectBase> BasicCreateAt( const std::shared_ptr<Level> &level, Vector2 pos );
	};
}


#endif	//#ifndef FLYINGBLOB__AUTO
