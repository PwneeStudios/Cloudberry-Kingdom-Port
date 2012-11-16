#ifndef IPREPARETODRAW
#define IPREPARETODRAW

namespace CloudberryKingdom
{
	/// <summary>
	/// Interface for an object that requires preparation before drawing
	/// <\summary>
	class IPrepareToDraw
	{
		/// <summary>
		/// Prepares the object to be drawn
		/// </summary>
	public:
		virtual void PrepareToDraw() = 0;
	};
}


#endif	//#ifndef IPREPARETODRAW
