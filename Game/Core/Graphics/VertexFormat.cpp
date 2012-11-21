#include <global_header.h>





namespace CloudberryKingdom
{

	MyOwnVertexFormat::MyOwnVertexFormat( Vector2 XY, Vector2 UV, Color color )
	{
		this->xy = XY;
		this->uv = UV;
		this->TheColor = color;
	}

	MyOwnVertexFormat::MyOwnVertexFormat( Vector2 XY, Vector2 UV, Color color, Vector3 depth )
	{
		this->xy = XY;
		this->uv = UV;
		this->TheColor = color;
	}

	/*
const std::shared_ptr<Microsoft::Xna::Framework::Graphics::VertexDeclaration> MyOwnVertexFormat::VertexDeclaration = std::make_shared<VertexDeclaration>( VertexElement( 0, VertexElementFormat::Vector2, VertexElementUsage::Position, 0 ), VertexElement( sizeof( float ) * 2, VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 0 ), VertexElement( sizeof( float ) * 4, VertexElementFormat::Color, VertexElementUsage::Color, 0 ) );

	const std::shared_ptr<Microsoft::Xna::Framework::Graphics::VertexDeclaration> &MyOwnVertexFormat::getVertexDeclaration() const
	{
		return VertexDeclaration;
	}*/
}
