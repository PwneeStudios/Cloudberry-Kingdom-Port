#ifndef FLYINGBLOB__AUTO
#define FLYINGBLOB__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	struct FlyingBlob_Parameters : public AutoGen_Parameters
	{
	
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
	
		struct _Special
		{
			/// <summary>
			/// A special fill type. Creates a tunnel of flying blobs.
			/// </summary>
		
			bool Tunnel;

			/// <summary>
			/// A special fill type. One giant circle. All blobs orbit the same point.
			/// </summary>
			bool Pinwheel;

			_Special() : Tunnel( false ), Pinwheel( false ) { }
		};
	
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

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();
	};

	struct FlyingBlob_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<FlyingBlob_AutoGen> instance;
	
		const static boost::shared_ptr<FlyingBlob_AutoGen> &getInstance();

	
		FlyingBlob_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

	
		void Circle( const boost::shared_ptr<Level> &level, Vector2 Center, float Radius, int Num, int Dir );
		void Circle( const boost::shared_ptr<Level> &level, Vector2 Center, float Radius, int Num, int Dir, float ModPeriod );

		void Pinwheel( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );


		void SetTunnelBlobParameter( const boost::shared_ptr<FlyingBlob> &blob, const boost::shared_ptr<FlyingBlob_Parameters> &Params, const boost::shared_ptr<Rand> &Rnd );

		void Tunnel( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		/*void Clean( array_Renamed<boost::shared_ptr<ObjectBase> , 2> *array_Renamed );
		void Clean( array_Renamed<boost::shared_ptr<ObjectBase> , 2> *array_Renamed, int i, int j );
		void CleanupTunnel( const boost::shared_ptr<Level> &level );*/

	
		void PreFill_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void PreFill_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void SetMoveType( const boost::shared_ptr<FlyingBlob> &fblob, float Displacement, FlyingBlob_Parameters::MotionType mtype, const boost::shared_ptr<Rand> &Rnd );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, Vector2 BL, Vector2 TR );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos );

	
		boost::shared_ptr<ObjectBase> BasicCreateAt( const boost::shared_ptr<Level> &level, Vector2 pos );
	};
}


#endif	//#ifndef FLYINGBLOB__AUTO
