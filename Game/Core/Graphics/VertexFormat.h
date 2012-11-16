#ifndef VERTEXFORMAT
#define VERTEXFORMAT

namespace Microsoft
{
	namespace Xna
	{
		namespace Framework
		{
			namespace Graphics
			{
				class VertexDeclaration;
			}
		}
	}
}


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
	class MyOwnVertexFormat : public IVertexType //, IReadWrite
	{
	public:
		Vector2 xy;
		Vector2 uv;
		Color Color;

		MyOwnVertexFormat( Vector2 XY, Vector2 UV, Color color );

		MyOwnVertexFormat( Vector2 XY, Vector2 UV, Color color, Vector3 depth );

		const static std::shared_ptr<Microsoft::Xna::Framework::Graphics::VertexDeclaration> VertexDeclaration;

		const std::shared_ptr<Microsoft::Xna::Framework::Graphics::VertexDeclaration> &getVertexDeclaration() = IVertexType::VertexDeclaration::get const;

		/*
		static string[] _bits_to_save = new string[] { "xy", "uv", "Color" };
		public void WriteCode(string prefix, StreamWriter writer)
		{
		    Tools.WriteFieldsToCode(this, prefix, writer, _bits_to_save);
		}
		public void Write(StreamWriter writer)
		{
		    Tools.WriteFields(this, writer, _bits_to_save);
		}
		public void Read(StreamReader reader)
		{
		    Tools.ReadFields(this, reader);
		}*/
	};
}


#endif	//#ifndef VERTEXFORMAT
