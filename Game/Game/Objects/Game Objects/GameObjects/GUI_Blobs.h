#ifndef GUI_BLOBS
#define GUI_BLOBS

#include <global_header.h>

namespace CloudberryKingdom
{
	class Lambda_1;
}

namespace CloudberryKingdom
{
	class GUI_Blobs;
}

namespace CloudberryKingdom
{
	class Door;
}

namespace CloudberryKingdom
{
	class PlayerData;
}

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class EzText;
}




namespace CloudberryKingdom
{
	class GUI_BlobQuota : public GUI_Blobs
	{
	private:
		class MyPhsxStepHelper : public Lambda
		{
		private:
			std::shared_ptr<GUI_BlobQuota> blobQuota;

		public:
			MyPhsxStepHelper( const std::shared_ptr<GUI_BlobQuota> &blobQuota );

			void Apply();
		};

	public:
		int Quota;

		GUI_BlobQuota( int Quota );

	protected:
		virtual int OutOf();

	public:
		std::shared_ptr<Lambda_1<GUI_Blobs*> > OnQuotaMet;
		bool QuotaMet;

	private:
		std::shared_ptr<Door> FinalDoor;
	public:
		virtual void OnAdd();

		virtual void Reset( bool BoxesOnly );

	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};

	class GUI_Blobs : public GUI_Panel
	{
	private:
		class TempStatsLambda : public PlayerIntLambda
		{
		public:
			virtual int Apply( const std::shared_ptr<PlayerData> &p );
		};

	private:
		std::shared_ptr<StringBuilder> MyString;

	public:
		int Blobs, TotalBlobs;

		/// <summary>
		/// Return a string representation of the number of Blobs
		/// </summary>
		/// <returns></returns>
		std::shared_ptr<StringBuilder> BuildString();

	protected:
		virtual int OutOf();

	private:
		bool AddedOnce;
	public:
		virtual void OnAdd();

		virtual void Hide();

		virtual void Show();

		const Vector2 &getApparentPos() const;

	private:
		std::shared_ptr<QuadClass> Blob;
		std::shared_ptr<EzText> Text;
	protected:
		void UpdateCoinText();

	public:
		GUI_Blobs();

		virtual void Init();

	protected:
		virtual void MyDraw();

		virtual void MyPhsxStep();

	public:
		virtual void Reset( bool BoxesOnly );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GUI_BLOBS
