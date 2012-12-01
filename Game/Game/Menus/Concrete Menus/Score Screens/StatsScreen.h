#ifndef STATSSCREEN
#define STATSSCREEN

#include <global_header.h>

namespace CloudberryKingdom
{
	class StatsMenu : public CkBaseMenu
	{
	private:
		class StringificationWrapper : public LambdaFunc_1<int, std::wstring>
		{
		private:
			std::shared_ptr<LambdaFunc_1<int, int> > f;

		public:
			StringificationWrapper( const std::shared_ptr<LambdaFunc_1<int, int> > &f );

			std::wstring Apply( const int &i );
		};

	private:
		class StatsLevels : public LambdaFunc_1<int, int>
		{
		private:
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		public:
			StatsLevels( std::vector<std::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	private:
		class StatsJumps : public LambdaFunc_1<int, int>
		{
		private:
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		public:
			StatsJumps( std::vector<std::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	private:
		class StatsScore : public LambdaFunc_1<int, int>
		{
		private:
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		public:
			StatsScore( std::vector<std::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	private:
		class StatsCoins : public LambdaFunc_1<int, int>
		{
		private:
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		public:
			StatsCoins( std::vector<std::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	private:
		class StatsTotalCoins : public LambdaFunc_1<int, int>
		{
		private:
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		public:
			StatsTotalCoins( std::vector<std::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	private:
		class StatsCoinPercentGotten : public LambdaFunc_1<int, std::wstring>
		{
		private:
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		public:
			StatsCoinPercentGotten( std::vector<std::shared_ptr<PlayerStats> > Stats );

			std::wstring Apply( const int &j );
		};

	private:
		class StatsBlobs : public LambdaFunc_1<int, int>
		{
		private:
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		public:
			StatsBlobs( std::vector<std::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	private:
		class StatsCheckpoints : public LambdaFunc_1<int, int>
		{
		private:
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		public:
			StatsCheckpoints( std::vector<std::shared_ptr<PlayerStats> > Stats );

			int Apply( const int &j );
		};

	private:
		class StatsLifeExpectancy : public LambdaFunc_1<int, std::wstring>
		{
		private:
			std::vector<std::shared_ptr<PlayerStats> > Stats;

		public:
			StatsLifeExpectancy( std::vector<std::shared_ptr<PlayerStats> > Stats );

			std::wstring Apply( const int &j );
		};

	private:
		class StatsDeathsBy : public LambdaFunc_1<int, int>
		{
		private:
			std::vector<std::shared_ptr<PlayerStats> > Stats;
			int i;

		public:
			StatsDeathsBy( std::vector<std::shared_ptr<PlayerStats> > Stats, int i );

			int Apply( const int &j );
		};

	private:
		class OnAddHelper : public LambdaFunc<bool>
		{
		private:
			std::shared_ptr<ScrollBar> bar;

		public:
			OnAddHelper( const std::shared_ptr<ScrollBar> &bar );

			bool Apply();
		};
	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

		virtual void SetHeaderProperties( const std::shared_ptr<EzText> &text );

	private:
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

	public:
		virtual void Init();

#if defined(PC_VERSION)
	private:
		std::shared_ptr<ScrollBar> bar;
#endif

		int n;
		float HeaderPos;
		std::vector<std::shared_ptr<PlayerStats> > Stats;
	public:
		StatsMenu( StatGroup group );


	private:
		void SetPos();

#if defined(PC_VERSION)
#endif

		Vector2 BarPos;
	public:
		virtual void OnAdd();

	private:
		void MakeBack();

	protected:
		virtual void MyPhsxStep();

		virtual void MyDraw();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef STATSSCREEN
