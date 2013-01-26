#ifndef STATSSCREEN
#define STATSSCREEN

#include <global_header.h>

namespace CloudberryKingdom
{

	struct StatsMenu : public CkBaseMenu
	{

		virtual ~StatsMenu() { }
	
		struct StringificationWrapper : public LambdaFunc_1<int, std::wstring>
		{
		
			boost::shared_ptr<LambdaFunc_1<int, int> > f;

		
			StringificationWrapper( const boost::shared_ptr<LambdaFunc_1<int, int> > &f );

			std::wstring Apply( const int &i );
		};

	
		struct StatsLevels : public LambdaFunc_1<int, int>
		{
		
			std::vector<boost::shared_ptr<PlayerStats> > Stats;

		
			StatsLevels( std::vector<boost::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	
		struct StatsJumps : public LambdaFunc_1<int, int>
		{
		
			std::vector<boost::shared_ptr<PlayerStats> > Stats;

		
			StatsJumps( std::vector<boost::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	
		struct StatsScore : public LambdaFunc_1<int, int>
		{
		
			std::vector<boost::shared_ptr<PlayerStats> > Stats;

		
			StatsScore( std::vector<boost::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	
		struct StatsCoins : public LambdaFunc_1<int, int>
		{
		
			std::vector<boost::shared_ptr<PlayerStats> > Stats;

		
			StatsCoins( std::vector<boost::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	
		struct StatsTotalCoins : public LambdaFunc_1<int, int>
		{
		
			std::vector<boost::shared_ptr<PlayerStats> > Stats;

		
			StatsTotalCoins( std::vector<boost::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	
		struct StatsCoinPercentGotten : public LambdaFunc_1<int, std::wstring>
		{
		
			std::vector<boost::shared_ptr<PlayerStats> > Stats;

		
			StatsCoinPercentGotten( std::vector<boost::shared_ptr<PlayerStats> > Stats );

			std::wstring Apply( const int &j );
		};

	
		struct StatsBlobs : public LambdaFunc_1<int, int>
		{
		
			std::vector<boost::shared_ptr<PlayerStats> > Stats;

		
			StatsBlobs( std::vector<boost::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	
		struct StatsCheckpoints : public LambdaFunc_1<int, int>
		{
		
			std::vector<boost::shared_ptr<PlayerStats> > Stats;

		
			StatsCheckpoints( std::vector<boost::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	
		struct StatsLifeExpectancy : public LambdaFunc_1<int, std::wstring>
		{
		
			std::vector<boost::shared_ptr<PlayerStats> > Stats;

		
			StatsLifeExpectancy( std::vector<boost::shared_ptr<PlayerStats> > Stats );

			std::wstring Apply( const int &j );
		};

	
		struct StatsDeathsBy : public LambdaFunc_1<int, int>
		{
		
			std::vector<boost::shared_ptr<PlayerStats> > Stats;
			int i;

		
			StatsDeathsBy( std::vector<boost::shared_ptr<PlayerStats> > Stats, int i );

			int Apply( const int &j );
		};

	
		struct OnAddHelper : public LambdaFunc<bool>
		{
		
			boost::shared_ptr<ScrollBar> bar;

		
			OnAddHelper( const boost::shared_ptr<ScrollBar> &bar );

			bool Apply();
		};
	
		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

	
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

		boost::shared_ptr<MenuItem> AddRow( const boost::shared_ptr<MenuItem> &Item, const boost::shared_ptr<LambdaFunc_1<int, int> > &f );
		boost::shared_ptr<MenuItem> AddRow( const boost::shared_ptr<MenuItem> &Item, const boost::shared_ptr<LambdaFunc_1<int, std::wstring> > &f );

	
		virtual void Init();

#if defined(PC_VERSION)
	
		boost::shared_ptr<ScrollBar> bar;
#endif

		int n;
		float HeaderPos;
		std::vector<boost::shared_ptr<PlayerStats> > Stats;
	
		StatsMenu( StatGroup group );
		boost::shared_ptr<StatsMenu> StatsMenu_Construct( StatGroup group );


	
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
