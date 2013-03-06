#ifndef _OBSTACLE
#define _OBSTACLE

#include <global_header.h>

namespace CloudberryKingdom
{

	struct _Obstacle : public ObjectBase
	{

		virtual ~_Obstacle()
		{
#ifdef BOOST_BIN
			OnDestructor( "_Obstacle" );
#endif
		}


		boost::shared_ptr<AutoGen> AutoGenSingleton;

		/// <summary>
		/// This is the distance from the edge of the screen the obstacle must be before Physics updates are no longer active in-game.
		/// </summary>
	
		Vector2 PhsxCutoff_Playing;

		/// <summary>
		/// This is the distance from the edge of the screen the obstacle must be before Physics updates are no longer active during level creation.
		/// </summary>
		Vector2 PhsxCutoff_BoxesOnly;

		/// <summary>
		/// This is the distance from the edge of the screen the obstacle must be before Physics updates are no longer active.
		/// </summary>
		const Vector2 &getPhsxCutoff() const;

	
		virtual void Construct( bool BoxesOnly );

		virtual void MakeNew();

		virtual void Die();

		virtual void Reset( bool BoxesOnly );

		virtual void PhsxStep();

		virtual void Draw();

	
		virtual void DrawGraphics();

		virtual void DrawBoxes();

		virtual void ActivePhsxStep();

	
		void InitializeInstanceFields();


		_Obstacle()
		{
			InitializeInstanceFields();
		}
	};

}


#endif	//#ifndef _OBSTACLE
