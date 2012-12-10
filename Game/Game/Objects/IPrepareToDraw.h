#ifndef IPREPARETODRAW
#define IPREPARETODRAW

namespace CloudberryKingdom
{
	/// <summary>
	/// Interface for an object that requires preparation before drawing
	/// <\summary>
	struct IPrepareToDraw
	{
		/// <summary>
		/// Prepares the object to be drawn
		/// </summary>
	
		virtual void PrepareToDraw() = 0;
	};
}


#endif	//#ifndef IPREPARETODRAW
