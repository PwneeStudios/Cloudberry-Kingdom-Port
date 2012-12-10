#ifndef GUI_BLOBS
#define GUI_BLOBS

#include <global_header.h>

namespace CloudberryKingdom
{
	struct GUI_Blobs : public GUI_Panel
	{
	
		struct TempStatsLambda : public PlayerIntLambda
		{
		
			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};

	
		std::shared_ptr<StringBuilder> MyString;

	
		int Blobs, TotalBlobs;

		/// <summary>
		/// Return a string representation of the number of Blobs
		/// </summary>
		/// <returns></returns>
		std::shared_ptr<StringBuilder> BuildString();

	
		virtual int OutOf();

	
		bool AddedOnce;
	
		virtual void OnAdd();

		virtual void Hide();

		virtual void Show();

		const Vector2 getApparentPos() const;

	
		std::shared_ptr<QuadClass> Blob;
		std::shared_ptr<EzText> Text;
	
		void UpdateCoinText();

	
		GUI_Blobs();

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
		
			std::shared_ptr<GUI_BlobQuota> blobQuota;

		
			MyPhsxStepHelper( const std::shared_ptr<GUI_BlobQuota> &blobQuota );

			void Apply();
		};

	
		int Quota;

		GUI_BlobQuota( int Quota );

	
		virtual int OutOf();

	
		std::shared_ptr<Lambda_1<std::shared_ptr<GUI_Blobs> > > OnQuotaMet;
		bool QuotaMet;

	
		std::shared_ptr<Door> FinalDoor;
	
		virtual void OnAdd();

		virtual void Reset( bool BoxesOnly );

	
		virtual void MyPhsxStep();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_BLOBS
