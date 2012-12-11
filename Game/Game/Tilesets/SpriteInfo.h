#ifndef SPRITEINFO
#define SPRITEINFO

namespace CloudberryKingdom
{
	struct TextureOrAnim;
}


namespace CloudberryKingdom
{
	struct LineSpriteInfo
	{
	
		bool Wrap;

		std::shared_ptr<TextureOrAnim> Sprite;
		float Width, RepeatWidth;
		int Dir;
		Vector4 Tint;
		float BlendAddRatio;

		bool DrawEndPoints;
		std::shared_ptr<TextureOrAnim> End1, End2;

		LineSpriteInfo( const std::shared_ptr<TextureOrAnim> &End1, const std::shared_ptr<TextureOrAnim> &Body, const std::shared_ptr<TextureOrAnim> &End2, float Width );

		LineSpriteInfo( const std::shared_ptr<TextureOrAnim> &Sprite, float Width, float RepeatWidth );

		LineSpriteInfo( const std::shared_ptr<TextureOrAnim> &Sprite, float Width, float RepeatWidth, int Dir, Vector4 Tint );

		LineSpriteInfo( const std::shared_ptr<TextureOrAnim> &Sprite, float Width, float RepeatWidth, int Dir, Vector4 Tint, float BlendAddRatio );

	
		void InitializeInstanceFields();
	};

	/// <summary>
	/// Struct for holding information about a sprite.
	/// </summary>
	struct SpriteInfo
	{
	
		std::shared_ptr<TextureOrAnim> Sprite;
		Vector2 Size, Offset;
		Color Tint;
		bool RelativeOffset;
		float Degrees;

		Matrix ColorMatrix;

		SpriteInfo( const std::shared_ptr<TextureOrAnim> &Sprite );

		SpriteInfo( const std::shared_ptr<TextureOrAnim> &Sprite, Vector2 Size );

		SpriteInfo( const std::shared_ptr<TextureOrAnim> &Sprite, Vector2 Size, Vector2 Offset, Color Tint );

		SpriteInfo( const std::shared_ptr<TextureOrAnim> &Sprite, Vector2 Size, Vector2 Offset, Color Tint, bool RelativeOffset );

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef SPRITEINFO
