#ifndef FANCYVECTOR2
#define FANCYVECTOR2

#include <global_header.h>

#include "Core/Animation/AnimationData_Vector.h"
#include "Core/Animation/AnimationData_Integer.h"

namespace CloudberryKingdom
{
	struct IPos
	{
		virtual ~IPos() { }
		virtual Vector2 getPos() = 0;
	};

	struct FancyVector2 : public IPos
	{

		AnimationData AnimData;

		std::vector<Vector2> HoldVecs;

		Vector2 RelVal, AbsVal;

		const float &getRelValX() const;
		void setRelValX( const float &value );
		const float &getRelValY() const;
		void setRelValY( const float &value );

		// Debug
		int code;

		// Debug AbsVal and RelVal
		//public Vector2 AbsVal;
		//public Vector2 _RelVal;
		//public Vector2 RelVal
		//{
		//    get { return _RelVal; }
		//    set
		//    {
		//        if (code == 23)
		//            Tools::Write("");
		//        _RelVal = value;
		//    }
		//}

		boost::shared_ptr<IPos> Center;
		boost::shared_ptr<ObjectBase> ObjCenter;
		// Debug Center
		//IPos _Center;
		//public IPos Center
		//{
		//    get { return _Center; }
		//    set
		//    {
		//        _Center = value;
		//    }
		//}

		float Speed;
		int TimeStamp, LastUpdate;
		float t;
		bool Playing;
		bool Loop;
		Vector2 getPos();

		float getVal();
		void setVal( const float &value );


		void Release();

		FancyVector2();

		FancyVector2( const boost::shared_ptr<IPos> &Center );

		/// <summary>
		/// Sets the FancyPos's center FancyPos. Updates relative coordinates so that absolute coordinates are unaffected.
		/// </summary>
		void SetCenter( const boost::shared_ptr<IPos> &Center );
		/// <summary>
		/// Sets the FancyPos's center FancyPos
		/// </summary>
		/// <param name="UsePosAsRelPos">Whether to use the current position as relative coordinates in the new system</param>
		void SetCenter( const boost::shared_ptr<IPos> &Center, bool UsePosAsRelPos );

		/// <summary>
		/// Sets the FancyPos's ObjCenter FancyPos. Updates relative coordinates so that absolute coordinates are unaffected.
		/// </summary>
		void SetCenter( const boost::shared_ptr<ObjectBase> &ObjCenter );
		/// <summary>
		/// Sets the FancyPos's ObjCenter FancyPos
		/// </summary>
		/// <param name="UsePosAsRelPos">Whether to use the current position as relative coordinates in the new system</param>
		void SetCenter( const boost::shared_ptr<ObjectBase> &ObjCenter, bool UsePosAsRelPos );

		Vector2 GetDest();

		void ToAndBack( Vector2 End, int Frames );
		void ToAndBack( Vector2 Start, Vector2 End, int Frames );

//ORIGINAL LINE: public void MultiLerp(int Frames, params Vector2[] Positions)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		void MultiLerp( int Frames, const std::vector<Vector2> Positions );

	
//ORIGINAL LINE: void MultiLerp(int Frames, bool Reverse, params Vector2[] Positions)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		void MultiLerp( int Frames, bool Reverse, const std::vector<Vector2> Positions );

	
		static const LerpStyle DefaultLerpStyle;
		//public const LerpStyle DefaultLerpStyle = LerpStyle.DecayNoOvershoot;

		void LerpTo( int EndIndex, int Frames );
		void LerpTo( int EndIndex, int Frames, LerpStyle Style );
		void LerpTo( int StartIndex, int EndIndex, int Frames );
		void LerpTo( int StartIndex, int EndIndex, int Frames, LerpStyle Style );
		void LerpTo( float End, int Frames );
		void LerpTo( Vector2 End, int Frames );
		void LerpTo( float End, int Frames, LerpStyle Style );
		void LerpTo( Vector2 End, int Frames, LerpStyle Style );
		void LerpTo( float Start, float End, int Frames );
		void LerpTo( float Start, float End, int Frames, LerpStyle Style );
		void LerpTo( Vector2 Start, Vector2 End, int Frames );
		void LerpTo( Vector2 Start, Vector2 End, int Frames, LerpStyle Style );

		bool UpdateOnPause;
		bool UpdateWithGame;
	
		int GetCurStep();

	
		Vector2 Update();
		Vector2 Update( Vector2 Scale );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef FANCYVECTOR2
