#ifndef GAMEOBJECT
#define GAMEOBJECT

#include <global_header.h>

#include "Core/Lambdas/Lambda.h"
#include "Core/Lambdas/Multicaster.h"

namespace CloudberryKingdom
{
	struct GameObject : public ObjectBase
	{
	
		enum Tag
		{
			Tag_REMOVE_ON_LEVEL_FINISH,
			Tag_CHAR_SELECT
		};
	
		struct OnCameraChangeProxy : public Lambda
		{
		
			boost::shared_ptr<GameObject> go;

		
			OnCameraChangeProxy( const boost::shared_ptr<GameObject> &go );

			void Apply();
		};

	
		struct AddGameObjectToCoreHelper : public Lambda
		{
		
			boost::shared_ptr<GameObject> obj;

		
			AddGameObjectToCoreHelper( const boost::shared_ptr<GameObject> &obj );

			void Apply();
		};

		/// <summary>
		/// Tries to add the game object to the game object's level's game.
		/// Returns true if failed.
		/// </summary>
	
		bool AttemptToReAdd();

		boost::shared_ptr<Set<Tag> > Tags;

		/// <summary>
		/// If true the object is prevented from being released.
		/// </summary>
		bool PreventRelease;

		bool PauseOnPause;

		/// <summary>
		/// Whether to SoftPause the game
		/// </summary>
		void setSoftPause( const bool &value );

		const bool &getSoftPause() const;
	
		bool _SoftPause;

		/// <summary>
		/// Whether to pause the game
		/// </summary>
	
		void setPauseGame( const bool &value );

		const bool &getPauseGame() const;
	
		bool _PauseGame;

		/// <summary>
		/// Whether to pause the level.
		/// </summary>
	
		void setPauseLevel( const bool &value );

		const bool &getPauseLevel() const;
	
		bool _PauseLevel;

		/// <summary>
		/// Communicates the GameObject's desire to SoftPause to the parent game.
		/// </summary>
		void AffectGameSoftPause();

		/// <summary>
		/// Communicates the GameObject's desire to pause to the parent game.
		/// </summary>
		void AffectGamePause();

		/// <summary>
		/// Communicates the GameObject's desire to pause to the parent game.
		/// </summary>
		void AffectLevelPause();

	
		void ForceRelease();

		virtual void Release();

		boost::shared_ptr<Multicaster> OnRelease;
	
		virtual void ReleaseBody();

		/// <summary>
		/// The GameData this GameObject belongs to.
		/// </summary>
	
		boost::shared_ptr<GameData> MyGame;

		virtual void MakeNew();

		GameObject();

		virtual void Init();

		bool HideOnReplay;
		bool PauseOnReplay;

		/// <summary>
		/// When true the object is automatically drawn with the level.
		/// Set to false if you are manually calling the ManualDraw function somewhere
		/// </summary>
		bool AutoDraw;

		/// <summary>
		/// Explicitly calls the object's draw code.
		/// Should be used if manually drawing the object.
		/// </summary>
		void ManualDraw();

		virtual void Draw();

	
		virtual void MyDraw();

	
		int SkipPhsx;
		void PhsxStep();

	
		virtual void MyPhsxStep();

		/// <summary>
		/// Called immediately after this GameObject is added to a GameData.
		/// </summary>
	
		virtual void OnAdd();


		/// <summary>
		/// Called if the main camera of the level is changed
		/// </summary>
		virtual void OnCameraChange();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GAMEOBJECT
