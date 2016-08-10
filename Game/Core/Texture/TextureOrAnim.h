#ifndef TEXTUREORANIM
#define TEXTUREORANIM

#include <small_header.h>

//#include "Core/Animation/AnimationData_Integer.h"
//#include "Core/Texture/EzTexture.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	/// <summary>
	/// Wraps either an EzTexture or an AnimationData_Texture.
	/// The purpose of this struct is to let a quad's texture be easily replaced by an animation, without additional fuss.
	/// Would be better to implement this functionality with inheritance, with EzTexture and AnimationData_Texture inheriting from a base struct.
	/// </summary>
	struct TextureOrAnim
	{
	
		boost::shared_ptr<EzTexture> MyTexture;
		boost::shared_ptr<AnimationData_Texture> MyAnim;
		bool IsAnim;

		TextureOrAnim();

		TextureOrAnim( const std::wstring &name );

		void Set( const std::wstring &name );

		static boost::shared_ptr<TextureOrAnim> Get( const boost::shared_ptr<EzTexture> &texture );
		static boost::shared_ptr<TextureOrAnim> Get( const std::wstring &name );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TEXTUREORANIM
