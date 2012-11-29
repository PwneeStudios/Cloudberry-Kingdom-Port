#ifndef SCREENSAVER
#define SCREENSAVER

#include <global_header.h>

namespace CloudberryKingdom
{
	class ScreenSaver : public StringWorldGameData
	{
	private:
		class ConstructorPressAListenerHelper : public Lambda
		{
		private:
			std::shared_ptr<ScreenSaver> ss;

		public:
			ConstructorPressAListenerHelper( const std::shared_ptr<ScreenSaver> &ss );

			void Apply();
		};

	private:
		class ScreenSaverReleaseHelper : public Lambda
		{
		private:
			std::shared_ptr<ScreenSaver> ss;

		public:
			ScreenSaverReleaseHelper( const std::shared_ptr<ScreenSaver> &ss );

			void Apply();
		};

	private:
		class ConstructorPressAListenerHelperHelper : public Lambda
		{
		private:
			std::shared_ptr<ScreenSaver> ss;

		public:
			ConstructorPressAListenerHelperHelper( const std::shared_ptr<ScreenSaver> &ss );

			void Apply();
		};

	private:
		class OnSwapLambda : public Lambda_1<std::shared_ptr<LevelSeedData> >
		{
		public:
			OnSwapLambda();

			void Apply( const std::shared_ptr<LevelSeedData> &data );
		};

	private:
		class GetSeedFuncLambdaSS : public LambdaFunc_1<int, std::shared_ptr<LevelSeedData> >
		{
		private:
			std::shared_ptr<ScreenSaver> ss;

		public:
			GetSeedFuncLambdaSS( const std::shared_ptr<ScreenSaver> &ss );

			std::shared_ptr<LevelSeedData> Apply( const int &index );
		};

	private:
		class ConstructorOnSwapToLevelHelper : public Lambda_1<int>
		{
		private:
			std::shared_ptr<ScreenSaver> ss;

		public:
			ConstructorOnSwapToLevelHelper( const std::shared_ptr<ScreenSaver> &ss );

			void Apply( const int &index );
		};

	private:
		class MakePressALambda : public Lambda
		{
		private:
			std::shared_ptr<ScreenSaver> ss;
			bool ForTrailer;

		public:
			MakePressALambda( const std::shared_ptr<ScreenSaver> &ss, bool ForTrailer );

			void Apply();
		};

	private:
		class AddListenerLambda : public Lambda
		{
		private:
			std::shared_ptr<ScreenSaver> ss;
		public:
			AddListenerLambda( const std::shared_ptr<ScreenSaver> &ss );

			void Apply();
		};
	private:
		class StartMusicLambda : public Lambda
		{
		public:
			StartMusicLambda();

			void Apply();
		};

	private:
		class RecordScratchLambda : public Lambda
		{
		public:
			RecordScratchLambda();

			void Apply();
		};

	private:
		class WindLambda : public Lambda
		{
		private:
			std::shared_ptr<FancyVector2> wind_t;
		public:
			WindLambda( const std::shared_ptr<FancyVector2> &wind_t );

			void Apply();
		};

	private:
		class PosLerpToLambda : public Lambda
		{
		private:
			std::shared_ptr<FancyVector2> pos_t;
			int zoomout_length;
			LerpStyle style;
		public:
			PosLerpToLambda( const std::shared_ptr<FancyVector2> &pos_t, int zoomout_length, LerpStyle style );

			void Apply();
		};

	private:
		class ZoomLerpToLambda : public Lambda
		{
		private:
			std::shared_ptr<FancyVector2> zoom_t;
			int zoomout_length;
			LerpStyle style;
		public:
			ZoomLerpToLambda( const std::shared_ptr<FancyVector2> &zoom_t, int zoomout_length, LerpStyle style );

			void Apply();
		};

	private:
		class SigmoidLambda : public Lambda
		{
		private:
			std::shared_ptr<FancyVector2> zoom_t;
		public:
			SigmoidLambda( const std::shared_ptr<FancyVector2> &zoom_t );

			void Apply();
		};

	private:
		class FadeInLambda : public Lambda
		{
		private:
			std::shared_ptr<Level> lvl;
			float InitialFadeInSpeed;
		public:
			FadeInLambda( const std::shared_ptr<Level> &lvl, float InitialFadeInSpeed );

			void Apply();
		};

	private:
		class MultiplayerBlobsMyModParamsHelper : public Lambda_2<std::shared_ptr<Level>, std::shared_ptr<PieceSeedData> >
		{
		private:
			std::shared_ptr<ScreenSaver> ss;

		public:
			MultiplayerBlobsMyModParamsHelper( const std::shared_ptr<ScreenSaver> &ss );

			void Apply( const std::shared_ptr<Level> &level, const std::shared_ptr<PieceSeedData> &p );
		};

	public:
		bool ForTrailer;

	private:
		bool Bungee;
		bool AllHeroes;
		int Difficulty;
		int Paths;
		std::shared_ptr<BobPhsx> FixedHero;
		std::shared_ptr<TileSet> FixedTileSet;

		float InitialZoom;
		void ForTrailerParams();

	public:
		virtual void Init();

		std::shared_ptr<GUI_Text> PressA;

		const static int getMandatoryWatchLength();
	private:
		static const int MandatoryWatchLength_Initial = 400;

		float InitialFadeInSpeed;
		static int InitialDarkness;
		int PartialZoomOut, FullZoomOut, KillCapeDelay;
		int InitialDelay;
	public:
		ScreenSaver();
		ScreenSaver( bool ForTrailer );

	private:
		void Constructor();

	public:
		std::shared_ptr<Listener> PressA_Listener;

		virtual void Release();

	private:
		int PhsxCount;

		int Duration;
		std::shared_ptr<FancyVector2> pos_t, zoom_t, wind_t;

	public:
		virtual void UpdateGamePause();

	private:
		bool DoBackgroundPhsx;
	public:
		virtual void BackgroundPhsx();

	private:
		std::shared_ptr<LevelSeedData> Make( int index );

		void FirstLevel( int index, const std::shared_ptr<PieceSeedData> &piece );

		void MultiplayerBlobs( int index, const std::shared_ptr<PieceSeedData> &piece );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SCREENSAVER
