#ifndef TEXTUREORANIM
#define TEXTUREORANIM

#include "../Core/Tools/Set.h"
#include <string>

namespace CloudberryKingdom
{
	class EzTexture;
}

namespace CloudberryKingdom
{
	class AnimationData_Texture;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
using namespace Microsoft::Xna::Framework::Content;
using namespace Microsoft::Xna::Framework::Graphics;

namespace CloudberryKingdom
{
	/// <summary>
	/// Wraps either an EzTexture or an AnimationData_Texture.
	/// The purpose of this class is to let a quad's texture be easily replaced by an animation, without additional fuss.
	/// Would be better to implement this functionality with inheritance, with EzTexture and AnimationData_Texture inheriting from a base class.
	/// </summary>
	class TextureOrAnim
	{
	public:
		std::shared_ptr<EzTexture> MyTexture;
		std::shared_ptr<AnimationData_Texture> MyAnim;
		bool IsAnim;

		TextureOrAnim();

		TextureOrAnim( const std::wstring &name );

		void Set( const std::wstring &name );

//C# TO C++ CONVERTER TODO TASK: C++ cast operators must convert from the enclosing type to another type:
		operator TextureOrAnim*( const std::shared_ptr<EzTexture> &texture );

//C# TO C++ CONVERTER TODO TASK: C++ cast operators must convert from the enclosing type to another type:
		operator TextureOrAnim*( const std::wstring &name );

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef TEXTUREORANIM
