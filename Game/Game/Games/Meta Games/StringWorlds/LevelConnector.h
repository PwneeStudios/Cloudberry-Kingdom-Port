#ifndef LEVELCONNECTOR
#define LEVELCONNECTOR

#include <global_header.h>

namespace CloudberryKingdom
{
	/// <summary>
	/// A singleton struct to store data about LevelConnectors.
	/// </summary>
	struct LevelConnector
	{

	
		static void InitializeStatics();

		/// <summary> The object core string code for an end of level object level connector. </summary>
	
		static std::wstring EndOfLevelCode;

		/// <summary> The object core string code for a start of level object level connector. </summary>
		static std::wstring StartOfLevelCode;
	};

	/// <summary>
	/// Implemented by IObjects that connect levels together.
	/// </summary>
	struct ILevelConnector : public ObjectBase
	{
	
		virtual ~ILevelConnector()
		{
#ifdef BOOST_BIN
			OnDestructor( "ILevelConnector" );
#endif
		}


		virtual const boost::shared_ptr<LevelSeedData> &getNextLevelSeedData() const = 0;
		virtual void setNextLevelSeedData( const boost::shared_ptr<LevelSeedData> &value ) = 0;
		virtual boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > getOnOpen() const = 0;
		virtual void setOnOpen( const boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > &value ) = 0;
		virtual const boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > &getOnEnter() const = 0;
		virtual void setOnEnter( const boost::shared_ptr<Lambda_1<boost::shared_ptr<Door> > > &value ) = 0;

	};
}


#endif	//#ifndef LEVELCONNECTOR
