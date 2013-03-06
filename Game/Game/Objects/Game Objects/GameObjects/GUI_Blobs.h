#ifndef GUI_BLOBS
#define GUI_BLOBS

#include <global_header.h>

namespace CloudberryKingdom
{

	struct GUI_Blobs : public GUI_Panel
	{

		virtual ~GUI_Blobs()
		{
#ifdef BOOST_BIN
			OnDestructor( "GUI_Blobs" );
#endif
		}


		using GUI_Panel::SlideOut;
		using GUI_Panel::SlideIn;
		using GUI_Panel::Call;
	
		struct TempStatsLambda : public PlayerIntLambda
		{
		
			virtual ~TempStatsLambda()
			{
#ifdef BOOST_BIN
				OnDestructor( "TempStatsLambda" );
#endif
			}

			
			virtual int Apply( const boost::shared_ptr<PlayerData> &p );

		};

	
		boost::shared_ptr<StringBuilder> MyString;

	
		int Blobs, TotalBlobs;

		/// <summary>
		/// Return a string representation of the number of Blobs
		/// </summary>
		/// <returns></returns>
		boost::shared_ptr<StringBuilder> BuildString();

	
		virtual int OutOf();

	
		bool AddedOnce;
	
		virtual void OnAdd();

		virtual void Hide();

		virtual void Show();

		const Vector2 getApparentPos() const;

	
		boost::shared_ptr<QuadClass> Blob;
		boost::shared_ptr<EzText> Text;
	
		void UpdateCoinText();

	
		GUI_Blobs();
		boost::shared_ptr<GUI_Blobs> GUI_Blobs_Construct();

		virtual void Init();

	
		virtual void MyDraw();

		virtual void MyPhsxStep();

	
		virtual void Reset( bool BoxesOnly );

	
		void InitializeInstanceFields();
	};

	struct GUI_BlobQuota : public GUI_Blobs
	{
	
		struct MyPhsxStepHelper : public Lambda
		{
		
			boost::shared_ptr<GUI_BlobQuota> blobQuota;

		
			MyPhsxStepHelper( const boost::shared_ptr<GUI_BlobQuota> &blobQuota );

			void Apply();
		};

	
		int Quota;

		GUI_BlobQuota( int Quota );

	
		virtual int OutOf();

	
		boost::shared_ptr<Lambda_1<boost::shared_ptr<GUI_Blobs> > > OnQuotaMet;
		bool QuotaMet;

	
		boost::shared_ptr<Door> FinalDoor;
	
		virtual void OnAdd();

		virtual void Reset( bool BoxesOnly );

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_BLOBS
