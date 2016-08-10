#ifndef IPREPARETODRAW
#define IPREPARETODRAW

namespace CloudberryKingdom
{

	/// <summary>
	/// Interface for an object that requires preparation before drawing
	/// <\summary>
	struct IPrepareToDraw
	{

		virtual ~IPrepareToDraw()
		{
#ifdef BOOST_BIN
			OnDestructor( "IPrepareToDraw" );
#endif
		}


		/// <summary>
		/// Prepares the object to be drawn
		/// </summary>
		virtual void PrepareToDraw() = 0;

	};

}


#endif	//#ifndef IPREPARETODRAW
