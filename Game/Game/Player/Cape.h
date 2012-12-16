#ifndef CAPE
#define CAPE

#include <global_header.h>

namespace CloudberryKingdom
{
	struct CapeNode
	{
	
		PhsxData Data, StartData;
		int AnchorIndex;
		Vector2 AnchorOffset;

		float Weight;

		bool Show;
	};

	struct CapeLink
	{
	
		int j, k;
		float L, a_in, a_out;
		bool Show;

		void Init();
	};

	struct Cape
	{
	
		static Vector2 SineWind( Vector2 Dir, float NormalIntensity, float Period, float t );

		boost::shared_ptr<Bob> MyBob;
		int LastPhsxUpdate;

		std::vector<MyOwnVertexFormat> Vertices;
		int NumVertices, NumTriangles;


		bool DoScaling;
		Vector2 ScaleCenter;
		Vector2 Scale;

		std::vector<Vector2> AnchorPoint;

		std::vector<CapeNode> Nodes;
		std::vector<CapeLink> Links;

		void Copy( const boost::shared_ptr<Cape> &cape );


		Color _MyColor;
		Color _MyOutlineColor;
		void setMyColor( const Color &value );
		const Color &getMyColor() const;
		void setMyOutlineColor( const Color &value );
		const Color &getMyOutlineColor() const;

		boost::shared_ptr<QuadClass> MyQuad;

	
		int Sections, HorizontalSections;
		float MaxForce;
	
		int PhsxSteps;
		float strength_in;
	
		float strength_out;
	
		float Retard;
		Vector2 Gravity;
		bool GroundCollision;
		float GroundHeight;
		float GravityScale;

		Vector2 Wind;

	
		bool DrawLines, DrawNodes;

	
		Vector2 p1_Left, p2_Left;
		Vector2 p1_Right, p2_Right;

		void Release();

		void SetOutlineColor( Color clr );

		void SetColor( Color clr );

		void Move( Vector2 Shift );

		void ModVel_Add( Vector2 Mod );

		void ModVel_Mult( Vector2 Mod );

		void Reset();

	
		float CapeThickness;
	
		CapeType MyType;

//C# TO C++ CONVERTER NOTE: The parameter Phsx was renamed since it is named the same as a user-defined type:
		Cape( const boost::shared_ptr<Bob> &bob, CapeType Type, const boost::shared_ptr<BobPhsx> &Phsx_Renamed );

		void PhsxStep();

	
		void UpdateTriangles();

		void ApplyScaling( Vector2 &v );

	
		void Draw();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CAPE
