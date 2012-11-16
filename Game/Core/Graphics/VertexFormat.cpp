#include <global_header.h>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Text;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;





//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{

	MyOwnVertexFormat::MyOwnVertexFormat( Vector2 XY, Vector2 UV, Color color )
	{
		this->xy = XY;
		this->uv = UV;
		this->Color = color;
	}

	MyOwnVertexFormat::MyOwnVertexFormat( Vector2 XY, Vector2 UV, Color color, Vector3 depth )
	{
		this->xy = XY;
		this->uv = UV;
		this->Color = color;
	}

const std::shared_ptr<Microsoft::Xna::Framework::Graphics::VertexDeclaration> MyOwnVertexFormat::VertexDeclaration = std::make_shared<VertexDeclaration>( VertexElement( 0, VertexElementFormat::Vector2, VertexElementUsage::Position, 0 ), VertexElement( sizeof( float ) * 2, VertexElementFormat::Vector2, VertexElementUsage::TextureCoordinate, 0 ), VertexElement( sizeof( float ) * 4, VertexElementFormat::Color, VertexElementUsage::Color, 0 ) );

	const std::shared_ptr<Microsoft::Xna::Framework::Graphics::VertexDeclaration> &MyOwnVertexFormat::getVertexDeclaration() const
	{
		return VertexDeclaration;
	}
}
