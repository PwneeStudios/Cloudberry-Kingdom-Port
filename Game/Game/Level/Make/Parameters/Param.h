#ifndef PARAM
#define PARAM

namespace CloudberryKingdom
{
	struct PieceSeedData;
}

namespace CloudberryKingdom
{
	struct Rand;
}




namespace CloudberryKingdom
{
	struct Param
	{
	
		boost::shared_ptr<PieceSeedData> PieceSeed;
		float val1, val2;
		bool val1_IsSet, val2_IsSet;

	
		const float &getVal() const;
		void setVal( const float &value );

		Param();

		Param( float val );

		Param( const boost::shared_ptr<PieceSeedData> &PieceSeed );

		//public Param(PieceSeedData PieceSeed, ParamFunc f)
		//{
		//    val1 = val2 = 0;
		//    val1_IsSet = val2_IsSet = false;

		//    this.PieceSeed = PieceSeed;

		//    if (f != null)
		//        SetVal(f);
		//}

		//public void SetVal(ParamFunc f)
		//{
		//    if (PieceSeed.MyUpgrades1 != null)
		//    {
		//        val1 = f(PieceSeed.MyUpgrades1);
		//        val1_IsSet = true;
		//    }
		//    if (PieceSeed.MyUpgrades2 != null && PieceSeed.Start != PieceSeed.End)
		//    {
		//        val2 = f(PieceSeed.MyUpgrades2);
		//        val2_IsSet = true;
		//    }
		//}

		Param( const boost::shared_ptr<PieceSeedData> &PieceSeed, float v );

		void SetVal( float v );

		float GetVal();

		float GetVal( Vector2 Pos );

		//public static implicit operator Param(float val)
		//{
		//    return new Param(val);
		//}
	};

	struct VectorParam
	{
	
		Param X, Y;

		VectorParam() { }

		VectorParam( const boost::shared_ptr<PieceSeedData> &PieceSeed );

		VectorParam( const boost::shared_ptr<PieceSeedData> &PieceSeed, Vector2 v );

		void SetVal( Vector2 v );

		Vector2 GetVal();

		Vector2 GetVal( Vector2 Pos );

		/// <summary>
		/// Assuming the top and bottom values of the vector are ranges of a value,
		/// this method returns a randomly chosen value in that range.
		/// </summary>
		/// <returns></returns>
		float RndFloat( Vector2 Pos, const boost::shared_ptr<Rand> &Rnd );
	};
}


#endif	//#ifndef PARAM
