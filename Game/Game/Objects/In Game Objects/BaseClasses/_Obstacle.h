#ifndef _OBSTACLE
#define _OBSTACLE

#include <global_header.h>

namespace CloudberryKingdom
{
	class AutoGen;
}







namespace CloudberryKingdom
{
	class _Obstacle : public ObjectBase
	{
	public:
		std::shared_ptr<AutoGen> AutoGenSingleton;

		/// <summary>
		/// This is the distance from the edge of the screen the obstacle must be before Physics updates are no longer active in-game.
		/// </summary>
	protected:
		Vector2 PhsxCutoff_Playing;

		/// <summary>
		/// This is the distance from the edge of the screen the obstacle must be before Physics updates are no longer active during level creation.
		/// </summary>
		Vector2 PhsxCutoff_BoxesOnly;

		/// <summary>
		/// This is the distance from the edge of the screen the obstacle must be before Physics updates are no longer active.
		/// </summary>
		const Vector2 &getPhsxCutoff() const;

	public:
		virtual void Construct( bool BoxesOnly ) = 0;

		virtual void MakeNew();

		virtual void Die();

		virtual void Reset( bool BoxesOnly );

		virtual void PhsxStep();

		virtual void Draw();

	protected:
		virtual void DrawGraphics() = 0;

		virtual void DrawBoxes() = 0;

		virtual void ActivePhsxStep() = 0;

	private:
		void InitializeInstanceFields();

public:
		_Obstacle()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef _OBSTACLE
