#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "../Game/Objects/ObjectBase.h"
#include "../Core/Lambdas/Lambda.h"

namespace CloudberryKingdom
{
	class Set;
}

namespace CloudberryKingdom
{
	class Multicaster;
}

namespace CloudberryKingdom
{
	class GameData;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class GameObject : public ObjectBase
	{
	public:
		enum Tag
		{
			Tag_REMOVE_ON_LEVEL_FINISH,
			Tag_CHAR_SELECT
		};
	private:
		class OnCameraChangeProxy : public Lambda
		{
		private:
			std::shared_ptr<GameObject> go;

		public:
			OnCameraChangeProxy( const std::shared_ptr<GameObject> &go );

			void Apply();
		};

	public:
		class AddGameObjectToCoreHelper : public Lambda
		{
		private:
			std::shared_ptr<GameObject> obj;

		public:
			AddGameObjectToCoreHelper( const std::shared_ptr<GameObject> &obj );

			void Apply();
		};

		/// <summary>
		/// Tries to add the game object to the game object's level's game.
		/// Returns true if failed.
		/// </summary>
	public:
		bool AttemptToReAdd();

		std::shared_ptr<Set<Tag> > Tags;

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
	private:
		bool _SoftPause;

		/// <summary>
		/// Whether to pause the game
		/// </summary>
	public:
		void setPauseGame( const bool &value );

		const bool &getPauseGame() const;
	private:
		bool _PauseGame;

		/// <summary>
		/// Whether to pause the level.
		/// </summary>
	public:
		void setPauseLevel( const bool &value );

		const bool &getPauseLevel() const;
	private:
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

	public:
		void ForceRelease();

		virtual void Release();

		std::shared_ptr<Multicaster> OnRelease;
	protected:
		virtual void ReleaseBody();

		/// <summary>
		/// The GameData this GameObject belongs to.
		/// </summary>
	public:
		std::shared_ptr<GameData> MyGame;

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

	protected:
		virtual void MyDraw();

	public:
		int SkipPhsx;
		void PhsxStep();

	protected:
		virtual void MyPhsxStep();

		/// <summary>
		/// Called immediately after this GameObject is added to a GameData.
		/// </summary>
	public:
		virtual void OnAdd();


		/// <summary>
		/// Called if the main camera of the level is changed
		/// </summary>
		virtual void OnCameraChange();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef GAMEOBJECT
