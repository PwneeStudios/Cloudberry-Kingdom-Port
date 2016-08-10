#ifndef ANIMATIONDATA_INTEGER
#define ANIMATIONDATA_INTEGER

#include <small_header.h>

//#include "Core/WriteReadTools.h"
//#include "Core/Texture/EzTexture.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{

	struct OneAnim_Texture
	{

		std::vector<boost::shared_ptr<EzTexture> > Data;
		float Speed;

		OneAnim_Texture();

	};

	struct AnimationData_Texture
	{
	
		std::vector<OneAnim_Texture> Anims;

		AnimationData_Texture();

		AnimationData_Texture( const std::wstring &TextureName );
		AnimationData_Texture( const std::wstring &TextureRoot, int StartFrame, int EndFrame );

		AnimationData_Texture( const boost::shared_ptr<EzTexture> &texture );

		int Width, Height;

		void Release();

		void Write( const boost::shared_ptr<BinaryWriter> &writer );

		void Read( const boost::shared_ptr<BinaryReader> &reader );

		AnimationData_Texture( const boost::shared_ptr<AnimationData_Texture> &data );

		void CopyAnim( const boost::shared_ptr<AnimationData_Texture> &data, int Anim );

		void Init();

		void InsertFrame( int anim, int frame );

		/// <summary>
		/// Clears a given animation back to 0 frames.
		/// </summary>
		void ClearAnim( int anim );

		void DeleteFrame( int anim, int frame );

		void AddFrame( const boost::shared_ptr<EzTexture> &val, int anim );
		void Set( const boost::shared_ptr<EzTexture> &val, int anim, int frame );

		boost::shared_ptr<EzTexture> Get( int anim, int frame );

		int LastSetFrame, LastSetAnim;
		boost::shared_ptr<EzTexture> NextKeyFrame();

		boost::shared_ptr<EzTexture> Calc( int anim, float t, int Length, bool Loop );

		boost::shared_ptr<EzTexture> Calc( int anim, float t );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef ANIMATIONDATA_INTEGER
