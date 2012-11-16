#ifndef ANIMATIONDATA_INTEGER
#define ANIMATIONDATA_INTEGER

#include <global_header.h>

namespace CloudberryKingdom
{
	class EzTexture;
}


namespace CloudberryKingdom
{
	class OneAnim_Texture
	{
	public:
		std::vector<EzTexture*> Data;
		float Speed;
	};

	class AnimationData_Texture
	{
	public:
		std::vector<OneAnim_Texture> Anims;

		AnimationData_Texture();

		AnimationData_Texture( const std::wstring &TextureName );
		AnimationData_Texture( const std::wstring &TextureRoot, int StartFrame, int EndFrame );

		AnimationData_Texture( const std::shared_ptr<EzTexture> &texture );

		int Width, Height;

		void Release();

		void Write( const std::shared_ptr<BinaryWriter> &writer );

		void Read( const std::shared_ptr<BinaryReader> &reader );

		AnimationData_Texture( const std::shared_ptr<AnimationData_Texture> &data );

		void CopyAnim( const std::shared_ptr<AnimationData_Texture> &data, int Anim );

		void Init();

		void InsertFrame( int anim, int frame );

		/// <summary>
		/// Clears a given animation back to 0 frames.
		/// </summary>
		void ClearAnim( int anim );

		void DeleteFrame( int anim, int frame );

		void AddFrame( const std::shared_ptr<EzTexture> &val, int anim );
		void Set( const std::shared_ptr<EzTexture> &val, int anim, int frame );

		std::shared_ptr<EzTexture> Get( int anim, int frame );

		int LastSetFrame, LastSetAnim;
		std::shared_ptr<EzTexture> NextKeyFrame();

		std::shared_ptr<EzTexture> Calc( int anim, float t, int Length, bool Loop );

		std::shared_ptr<EzTexture> Calc( int anim, float t );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef ANIMATIONDATA_INTEGER
