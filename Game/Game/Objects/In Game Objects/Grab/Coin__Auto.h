#ifndef COIN__AUTO
#define COIN__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{

	struct Coin_Parameters : public AutoGen_Parameters
	{
	
		virtual ~Coin_Parameters() { }

		enum FillTypes
		{
			FillTypes_NONE,
			FillTypes_REGULAR,
			FillTypes_RUSH,
			FillTypes_COIN_GRAB
		};
	
		struct _Special
		{
		};
	
		bool Red;

		Param MinDist, PlaceDelay;

		FillTypes FillType;

		/// <summary> Whether coins should be placed on a grid lattice. </summary>
		bool Grid;
	
		Vector2 GridSpacing;
	
		Vector2 SnapToGrid( Vector2 pos );

		bool DoCleanup;

		/// <summary> The frame afterwhich coins can be placed. </summary>
		int StartFrame;

		/// <summary> Used to determine if a coin should be placed (Regular style) </summary>
		int Regular_Period, Regular_Offset, Regular_Period2, Regular_Offset2;
		/// <summary> Whehter a coin should be placed (Regular style) </summary>
		bool Regular_ReadyToPlace( const boost::shared_ptr<Level> &level, const boost::shared_ptr<Bob> &bob, int Step );

		bool CoinPlaced;

		Vector2 TR_Bound_Mod, BL_Bound_Mod;

		_Special Special;

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();

		Coin_Parameters();
	};

	struct Coin_AutoGen : public AutoGen
	{
	
		enum BobPos
		{
			BobPos_CENTER,
			BobPos_HIGH,
			BobPos_LOW,
			BobPos_REGULAR
		};
	
		static boost::shared_ptr<Coin_AutoGen> instance;
	
		const static boost::shared_ptr<Coin_AutoGen> &getInstance();

	
		Coin_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		void Cleanup_2( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos );
	
		int offset;
	
		boost::shared_ptr<ObjectBase> CreateAt( const boost::shared_ptr<Level> &level, Vector2 pos, bool NewOffset );

	
		Vector2 CalcPos( const boost::shared_ptr<Bob> &bob, Vector2 BL, Vector2 TR, BobPos pos );

	
		void ActiveFill_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );
	};

}


#endif	//#ifndef COIN__AUTO
