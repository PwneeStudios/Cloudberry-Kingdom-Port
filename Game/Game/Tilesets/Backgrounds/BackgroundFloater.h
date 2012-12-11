#ifndef BACKGROUNDFLOATER
#define BACKGROUNDFLOATER

#include <global_header.h>

namespace CloudberryKingdom
{
	struct BackgroundFloater
	{
	
		float _SpinVelocity;
	
		const float &getSpinVelocity() const;
		void setSpinVelocity( const float &value );

	
		std::shared_ptr<Level> MyLevel;
	
		std::wstring Name;

		std::shared_ptr<QuadClass> MyQuad;
		Vector2 uv_speed, uv_offset;

		PhsxData Data, StartData;

		const Vector2 &getPos() const;

		/// <summary>
		/// Sets the current and start position of the floater.
		/// </summary>
		void SetPos( Vector2 pos );

		std::wstring Root;

		virtual void Release();

		void SetLevel( const std::shared_ptr<Level> &level );

		virtual void SetBackground( const std::shared_ptr<Background> &b );

		/// <summary>
		/// Reset the floater to its start position.
		/// </summary>
		void Reset();

		void ChangeParallax( float Prev, float New );

		void Move( Vector2 shift );

		BackgroundFloater( const std::shared_ptr<BackgroundFloater> &source );

		BackgroundFloater();

		BackgroundFloater( const std::shared_ptr<Level> &level );

		virtual void InitialUpdate();

		virtual void PhsxStep( const std::shared_ptr<BackgroundFloaterList> &list );

		virtual void Draw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef BACKGROUNDFLOATER
