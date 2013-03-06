#ifndef CEILING__AUTO
#define CEILING__AUTO

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Ceiling_Parameters : public AutoGen_Parameters
	{
	
		virtual ~Ceiling_Parameters()
		{
#ifdef BOOST_BIN
			OnDestructor( "Ceiling_Parameters" );
#endif
		}


		enum Style
		{
			Style_NORMAL,
			Style_SKIP_ONE,
			Style_SPARSE,
			Style_RANDOM,
			Style_LENGTH
		};
	
		struct _Special
		{
			/// <summary>
			/// One straight cement block for the ceiling.
			/// </summary>
		
			bool CementCeiling;

			/// <summary>
			/// One straight block for the ceiling.
			/// </summary>
			bool LongCeiling;

			_Special() : CementCeiling( false ), LongCeiling( false ) { }
		};
		/// <summary>
		/// Whether to make the ceiling or not.
		/// </summary>
	
		bool Make;

		Param BufferSize;
		VectorParam HeightRange, WidthRange;

		Style MyStyle;

		_Special Special;

		void SetLongCeiling();
		void SetCementCeiling();

		virtual void SetParameters( const boost::shared_ptr<PieceSeedData> &PieceSeed, const boost::shared_ptr<Level> &level );

	
		void InitializeInstanceFields();


		Ceiling_Parameters() :
			Make( false ),
			MyStyle( Style_NORMAL )
		{
			InitializeInstanceFields();
		}
	};

	struct Ceiling_AutoGen : public AutoGen
	{
	
		static boost::shared_ptr<Ceiling_AutoGen> instance;
	
		const static boost::shared_ptr<Ceiling_AutoGen> &getInstance();

	
		Ceiling_AutoGen();

	
		boost::shared_ptr<AutoGen_Parameters> SetParameters( const boost::shared_ptr<PieceSeedData> &data, const boost::shared_ptr<Level> &level );

		void MakeLongCeiling( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void PreFill_1( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR );

		void MakeCeiling( const boost::shared_ptr<Level> &level, Vector2 BL, Vector2 TR, float MaxStartY );
	};
}


#endif	//#ifndef CEILING__AUTO
