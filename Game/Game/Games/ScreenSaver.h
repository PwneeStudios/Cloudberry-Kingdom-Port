#ifndef SCREENSAVER
#define SCREENSAVER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct ScreenSaver : public StringWorldGameData
	{
	
		struct ConstructorPressAListenerHelper : public Lambda
		{
		
			std::shared_ptr<ScreenSaver> ss;

		
			ConstructorPressAListenerHelper( const std::shared_ptr<ScreenSaver> &ss );

			void Apply();
		};

	
		struct ScreenSaverReleaseHelper : public Lambda
		{
		
			std::shared_ptr<ScreenSaver> ss;

		
			ScreenSaverReleaseHelper( const std::shared_ptr<ScreenSaver> &ss );

			void Apply();
		};

	
		struct ConstructorPressAListenerHelperHelper : public Lambda
		{
		
			std::shared_ptr<ScreenSaver> ss;

		
			ConstructorPressAListenerHelperHelper( const std::shared_ptr<ScreenSaver> &ss );

			void Apply();
		};

	
		struct OnSwapLambda : public Lambda_1<std::shared_ptr<LevelSeedData> >
		{
		
			OnSwapLambda();

			void Apply( const std::shared_ptr<LevelSeedData> &data );
		};

	
		struct GetSeedFuncLambdaSS : public LambdaFunc_1<int, std::shared_ptr<LevelSeedData> >
		{
		
			std::shared_ptr<ScreenSaver> ss;

		
			GetSeedFuncLambdaSS( const std::shared_ptr<ScreenSaver> &ss );

			std::shared_ptr<LevelSeedData> Apply( const int &index );
		};

	
		struct ConstructorOnSwapToLevelHelper : public Lambda_1<int>
		{
		
			std::shared_ptr<ScreenSaver> ss;

		
			ConstructorOnSwapToLevelHelper( const std::shared_ptr<ScreenSaver> &ss );

			void Apply( const int &index );
		};

	
		struct MakePressALambda : public Lambda
		{
		
			std::shared_ptr<ScreenSaver> ss;
			bool ForTrailer;

		
			MakePressALambda( const std::shared_ptr<ScreenSaver> &ss, bool ForTrailer );

			void Apply();
		};

	
		struct AddListenerLambda : public Lambda
		{
		
			std::shared_ptr<ScreenSaver> ss;
		
			AddListenerLambda( const std::shared_ptr<ScreenSaver> &ss );

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
		
			std::shared_ptr<FancyVector2> wind_t;
		
			WindLambda( const std::shared_ptr<FancyVector2> &wind_t );

			void Apply();
		};

	
		struct PosLerpToLambda : public Lambda
		{
		
			std::shared_ptr<FancyVector2> pos_t;
			int zoomout_length;
			LerpStyle style;
		
			PosLerpToLambda( const std::shared_ptr<FancyVector2> &pos_t, int zoomout_length, LerpStyle style );

			void Apply();
		};

	
		struct ZoomLerpToLambda : public Lambda
		{
		
			std::shared_ptr<FancyVector2> zoom_t;
			int zoomout_length;
			LerpStyle style;
		
			ZoomLerpToLambda( const std::shared_ptr<FancyVector2> &zoom_t, int zoomout_length, LerpStyle style );

			void Apply();
		};

	
		struct SigmoidLambda : public Lambda
		{
		
			std::shared_ptr<FancyVector2> zoom_t;
		
			SigmoidLambda( const std::shared_ptr<FancyVector2> &zoom_t );

			void Apply();
		};

	
		struct FadeInLambda : public Lambda
		{
		
			std::shared_ptr<Level> lvl;
			float InitialFadeInSpeed;
		
			FadeInLambda( const std::shared_ptr<Level> &lvl, float InitialFadeInSpeed );

			void Apply();
		};

	
		struct MultiplayerBlobsMyModParamsHelper : public Lambda_2<std::shared_ptr<Level>, std::shared_ptr<PieceSeedData> >
		{
		
			std::shared_ptr<ScreenSaver> ss;

		
			MultiplayerBlobsMyModParamsHelper( const std::shared_ptr<ScreenSaver> &ss );

			void Apply( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &p );
		};

	
		bool ForTrailer;

	
		bool Bungee;
		bool AllHeroes;
		int Difficulty;
		int Paths;
		std::shared_ptr<BobPhsx> FixedHero;
		std::shared_ptr<TileSet> FixedTileSet;

		float InitialZoom;
		void ForTrailerParams();

	
		virtual void Init();

		std::shared_ptr<GUI_Text> PressA;

		const static int getMandatoryWatchLength();
	
		static const int MandatoryWatchLength_Initial = 400;

		float InitialFadeInSpeed;
		static int InitialDarkness;
		int PartialZoomOut, FullZoomOut, KillCapeDelay;
		int InitialDelay;
	
		ScreenSaver();
		ScreenSaver( bool ForTrailer );

	
		void Constructor();

	
		std::shared_ptr<Listener> PressA_Listener;

		virtual void Release();

	
		int PhsxCount;

		int Duration;
		std::shared_ptr<FancyVector2> pos_t, zoom_t, wind_t;

	
		virtual void UpdateGamePause();

	
		bool DoBackgroundPhsx;
	
		virtual void BackgroundPhsx();

	
		std::shared_ptr<LevelSeedData> Make( int index );

		void FirstLevel( int index, const std::shared_ptr<PieceSeedData> &piece );

		void MultiplayerBlobs( int index, const std::shared_ptr<PieceSeedData> &piece );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SCREENSAVER
