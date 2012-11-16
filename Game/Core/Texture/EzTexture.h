#ifndef EZTEXTURE
#define EZTEXTURE

#include <global_header.h>

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Graphics
			{
				class Texture2D;
			}
		}
	}
}

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			class Game;
		}
	}
}












namespace CloudberryKingdom
{
	class EzTexture
	{
	public:
		int Width, Height;

	private:
		std::shared_ptr<Texture2D> _Tex;
	public:
		const std::shared_ptr<Texture2D> &getTex() const;
		void setTex( const std::shared_ptr<Texture2D> &value );

		const float &getAspectRatio() const;

		std::wstring Path, Name;

		/// <summary>
		/// If true this texture is a sub-image from a packed collection.
		/// </summary>
		bool FromPacked;

		std::shared_ptr<EzTexture> Packed;

		/// <summary>
		/// If true this texture was loaded dynamically after the game loaded, not from a packed XNA file.
		/// </summary>
		bool Dynamic;

		/// <summary>
		/// If true this texture is created via code, not from an asset file.
		/// </summary>
		bool FromCode;

		/// <summary>
		/// Texture coordinates in the atlas.
		/// </summary>
		Vector2 BL, TR;

#if defined(EDITOR)
		static std::shared_ptr<Game> game;
		bool Load();
#else
		bool Load();
#endif

		virtual std::wstring ToString();

//C# TO C++ CONVERTER TODO TASK: C++ cast operators must convert from the enclosing type to another type:
		operator EzTexture*( const std::wstring &name );

	private:
		void InitializeInstanceFields();

public:
		EzTexture()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef EZTEXTURE
