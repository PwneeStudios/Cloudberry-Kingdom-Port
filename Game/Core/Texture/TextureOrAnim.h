#ifndef TEXTUREORANIM
#define TEXTUREORANIM

#include <global_header.h>

namespace CloudberryKingdom
{
	/// <summary>
	/// Wraps either an EzTexture or an AnimationData_Texture.
	/// The purpose of this struct is to let a quad's texture be easily replaced by an animation, without additional fuss.
	/// Would be better to implement this functionality with inheritance, with EzTexture and AnimationData_Texture inheriting from a base struct.
	/// </summary>
	struct TextureOrAnim
	{
	
		std::shared_ptr<EzTexture> MyTexture;
		std::shared_ptr<AnimationData_Texture> MyAnim;
		bool IsAnim;

		TextureOrAnim();

		TextureOrAnim( const std::wstring &name );

		void Set( const std::wstring &name );

		static std::shared_ptr<TextureOrAnim> Get( const std::shared_ptr<EzTexture> &texture );
		static std::shared_ptr<TextureOrAnim> Get( const std::wstring &name );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TEXTUREORANIM
