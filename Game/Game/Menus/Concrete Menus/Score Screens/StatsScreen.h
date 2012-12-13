#ifndef STATSSCREEN
#define STATSSCREEN

#include <global_header.h>

namespace CloudberryKingdom
{

	struct StatsMenu : public CkBaseMenu
	{
	
		struct StringificationWrapper : public LambdaFunc_1<int, std::wstring>
		{
		
			std::shared_ptr<LambdaFunc_1<int, int> > f;

		
			StringificationWrapper( const std::shared_ptr<LambdaFunc_1<int, int> > &f );

			std::wstring Apply( const int &i );
		};

	
		struct StatsLevels : public LambdaFunc_1<int, int>
		{
		
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		
			StatsLevels( std::vector<std::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	
		struct StatsJumps : public LambdaFunc_1<int, int>
		{
		
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		
			StatsJumps( std::vector<std::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	
		struct StatsScore : public LambdaFunc_1<int, int>
		{
		
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		
			StatsScore( std::vector<std::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	
		struct StatsCoins : public LambdaFunc_1<int, int>
		{
		
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		
			StatsCoins( std::vector<std::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	
		struct StatsTotalCoins : public LambdaFunc_1<int, int>
		{
		
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		
			StatsTotalCoins( std::vector<std::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	
		struct StatsCoinPercentGotten : public LambdaFunc_1<int, std::wstring>
		{
		
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		
			StatsCoinPercentGotten( std::vector<std::shared_ptr<PlayerStats> > Stats );

			std::wstring Apply( const int &j );
		};

	
		struct StatsBlobs : public LambdaFunc_1<int, int>
		{
		
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		
			StatsBlobs( std::vector<std::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	
		struct StatsCheckpoints : public LambdaFunc_1<int, int>
		{
		
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		
			StatsCheckpoints( std::vector<std::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	
		struct StatsLifeExpectancy : public LambdaFunc_1<int, std::wstring>
		{
		
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		
			StatsLifeExpectancy( std::vector<std::shared_ptr<PlayerStats> > Stats );

			std::wstring Apply( const int &j );
		};

	
		struct StatsDeathsBy : public LambdaFunc_1<int, int>
		{
		
			std::vector<std::shared_ptr<PlayerStats> > Stats;
			int i;

		
			StatsDeathsBy( std::vector<std::shared_ptr<PlayerStats> > Stats, int i );

			int Apply( const int &j );
		};

	
		struct OnAddHelper : public LambdaFunc<bool>
		{
		
			std::shared_ptr<ScrollBar> bar;

		
			OnAddHelper( const std::shared_ptr<ScrollBar> &bar );

			bool Apply();
		};
	
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	
		static std::vector<Vector2> x1_name;
		static std::vector<Vector2> x2_name;
		static std::vector<Vector2> x3_name;
		static std::vector<Vector2> x4_name;

		static std::vector<float> x1;
		static std::vector<float> x2;
		static std::vector<float> x3;
		static std::vector<float> x4;

		static std::vector<std::vector<float> > x;
		static std::vector<std::vector<Vector2> > name_pos;

		std::shared_ptr<MenuItem> AddRow( const std::shared_ptr<MenuItem> &Item, const std::shared_ptr<LambdaFunc_1<int, int> > &f );
		std::shared_ptr<MenuItem> AddRow( const std::shared_ptr<MenuItem> &Item, const std::shared_ptr<LambdaFunc_1<int, std::wstring> > &f );

	
		virtual void Init();

#if defined(PC_VERSION)
	
		std::shared_ptr<ScrollBar> bar;
#endif

		int n;
		float HeaderPos;
		std::vector<std::shared_ptr<PlayerStats> > Stats;
	
		StatsMenu( StatGroup group );
		void StatsMenu_Construct( StatGroup group );


	
		void SetPos();

#if defined(PC_VERSION)
#endif

		Vector2 BarPos;
	
		virtual void OnAdd();

	
		void MakeBack();

	
		virtual void MyPhsxStep();

		virtual void MyDraw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef STATSSCREEN
