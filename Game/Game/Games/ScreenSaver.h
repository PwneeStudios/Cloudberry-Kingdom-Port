#ifndef SCREENSAVER
#define SCREENSAVER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ScreenSaver : public StringWorldGameData
	{
	
		struct ConstructorPressAListenerHelper : public Lambda
		{
		
			boost::shared_ptr<ScreenSaver> ss;

		
			ConstructorPressAListenerHelper( const boost::shared_ptr<ScreenSaver> &ss );

			void Apply();
		};

	
		struct ScreenSaverReleaseHelper : public Lambda
		{
		
			boost::shared_ptr<ScreenSaver> ss;

		
			ScreenSaverReleaseHelper( const boost::shared_ptr<ScreenSaver> &ss );

			void Apply();
		};

	
		struct ConstructorPressAListenerHelperHelper : public Lambda
		{
		
			boost::shared_ptr<ScreenSaver> ss;

		
			ConstructorPressAListenerHelperHelper( const boost::shared_ptr<ScreenSaver> &ss );

			void Apply();
		};

	
		struct OnSwapLambda : public Lambda_1<boost::shared_ptr<LevelSeedData> >
		{
		
			OnSwapLambda();

			void Apply( const boost::shared_ptr<LevelSeedData> &data );
		};

	
		struct GetSeedFuncLambdaSS : public LambdaFunc_1<int, boost::shared_ptr<LevelSeedData> >
		{
		
			boost::shared_ptr<ScreenSaver> ss;

		
			GetSeedFuncLambdaSS( const boost::shared_ptr<ScreenSaver> &ss );

			boost::shared_ptr<LevelSeedData> Apply( const int &index );
		};

	
		struct ConstructorOnSwapToLevelHelper : public Lambda_1<int>
		{
		
			boost::shared_ptr<ScreenSaver> ss;

		
			ConstructorOnSwapToLevelHelper( const boost::shared_ptr<ScreenSaver> &ss );

			void Apply( const int &index );
		};

	
		struct MakePressALambda : public Lambda
		{
		
			boost::shared_ptr<ScreenSaver> ss;
			bool ForTrailer;

		
			MakePressALambda( const boost::shared_ptr<ScreenSaver> &ss, bool ForTrailer );

			void Apply();
		};

	
		struct AddListenerLambda : public Lambda
		{
		
			boost::shared_ptr<ScreenSaver> ss;
		
			AddListenerLambda( const boost::shared_ptr<ScreenSaver> &ss );

			void Apply();
		};
	
		struct StartMusicLambda : public Lambda
		{
		
			StartMusicLambda();

			void Apply();
		};

	
		struct RecordScratchLambda : public Lambda
		{
		
			RecordScratchLambda();

			void Apply();
		};

	
		struct WindLambda : public Lambda
		{
		
			boost::shared_ptr<FancyVector2> wind_t;
		
			WindLambda( const boost::shared_ptr<FancyVector2> &wind_t );

			void Apply();
		};

	
		struct PosLerpToLambda : public Lambda
		{
		
			boost::shared_ptr<FancyVector2> pos_t;
			int zoomout_length;
			LerpStyle style;
		
			PosLerpToLambda( const boost::shared_ptr<FancyVector2> &pos_t, int zoomout_length, LerpStyle style );

			void Apply();
		};

	
		struct ZoomLerpToLambda : public Lambda
		{
		
			boost::shared_ptr<FancyVector2> zoom_t;
			int zoomout_length;
			LerpStyle style;
		
			ZoomLerpToLambda( const boost::shared_ptr<FancyVector2> &zoom_t, int zoomout_length, LerpStyle style );

			void Apply();
		};

	
		struct SigmoidLambda : public Lambda
		{
		
			boost::shared_ptr<FancyVector2> zoom_t;
		
			SigmoidLambda( const boost::shared_ptr<FancyVector2> &zoom_t );

			void Apply();
		};

	
		struct FadeInLambda : public Lambda
		{
		
			boost::shared_ptr<Level> lvl;
			float InitialFadeInSpeed;
		
			FadeInLambda( const boost::shared_ptr<Level> &lvl, float InitialFadeInSpeed );

			void Apply();
		};

	
		struct MultiplayerBlobsMyModParamsHelper : public Lambda_2<boost::shared_ptr<Level>, boost::shared_ptr<PieceSeedData> >
		{
		
			boost::shared_ptr<ScreenSaver> ss;

		
			MultiplayerBlobsMyModParamsHelper( const boost::shared_ptr<ScreenSaver> &ss );

			void Apply( const boost::shared_ptr<Level> &level, const boost::shared_ptr<PieceSeedData> &p );
		};

	
		bool ForTrailer;

	
		bool Bungee;
		bool AllHeroes;
		int Difficulty;
		int Paths;
		boost::shared_ptr<BobPhsx> FixedHero;
		boost::shared_ptr<TileSet> FixedTileSet;

		float InitialZoom;
		void ForTrailerParams();

	
		virtual void Init();

		boost::shared_ptr<GUI_Text> PressA;

		const static int getMandatoryWatchLength();
	
		static const int MandatoryWatchLength_Initial = 400;

		float InitialFadeInSpeed;
		static int InitialDarkness;
		int PartialZoomOut, FullZoomOut, KillCapeDelay;
		int InitialDelay;
	
		ScreenSaver();
		ScreenSaver( bool ForTrailer );

	
		void Constructor();

	
		boost::shared_ptr<Listener> PressA_Listener;

		virtual void Release();

	
		int PhsxCount;

		int Duration;
		boost::shared_ptr<FancyVector2> pos_t, zoom_t, wind_t;

	
		virtual void UpdateGamePause();

	
		bool DoBackgroundPhsx;
	
		virtual void BackgroundPhsx();

	
		boost::shared_ptr<LevelSeedData> Make( int index );

		void FirstLevel( int index, const boost::shared_ptr<PieceSeedData> &piece );

		void MultiplayerBlobs( int index, const boost::shared_ptr<PieceSeedData> &piece );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SCREENSAVER
