#ifndef CAPE
#define CAPE

#include <global_header.h>

namespace CloudberryKingdom
{
	class CapeNode
	{
	public:
		PhsxData Data, StartData;
		int AnchorIndex;
		Vector2 AnchorOffset;

		float Weight;

		bool Show;
	};

	class CapeLink
	{
	public:
		int j, k;
		float L, a_in, a_out;
		bool Show;

		void Init();
	};

	class Cape
	{
	public:
		static Vector2 SineWind( Vector2 Dir, float NormalIntensity, float Period, float t );

		std::shared_ptr<Bob> MyBob;
		int LastPhsxUpdate;

		std::vector<MyOwnVertexFormat> Vertices;
		int NumVertices, NumTriangles;


		bool DoScaling;
		Vector2 ScaleCenter;
		Vector2 Scale;

		std::vector<Vector2> AnchorPoint;

		std::vector<CapeNode> Nodes;
		std::vector<CapeLink> Links;

		void Copy( const std::shared_ptr<Cape> &cape );


		Color _MyColor;
		Color _MyOutlineColor;
		void setMyColor( const Color &value );
		const Color &getMyColor() const;
		void setMyOutlineColor( const Color &value );
		const Color &getMyOutlineColor() const;

		std::shared_ptr<QuadClass> MyQuad;

	private:
		int Sections, HorizontalSections;
		float MaxForce;
	public:
		int PhsxSteps;
		float strength_in;
	private:
		float strength_out;
	public:
		float Retard;
		Vector2 Gravity;
		bool GroundCollision;
		float GroundHeight;
		float GravityScale;

		Vector2 Wind;

	private:
		bool DrawLines, DrawNodes;

	public:
		Vector2 p1_Left, p2_Left;
		Vector2 p1_Right, p2_Right;

		void Release();

		void SetOutlineColor( Color clr );

		void SetColor( Color clr );

		void Move( Vector2 Shift );

		void ModVel_Add( Vector2 Mod );

		void ModVel_Mult( Vector2 Mod );

		void Reset();

	private:
		float CapeThickness;
	public:
		CapeType MyType;

//C# TO C++ CONVERTER NOTE: The parameter Phsx was renamed since it is named the same as a user-defined type:
		Cape( const std::shared_ptr<Bob> &bob, CapeType Type, const std::shared_ptr<BobPhsx> &Phsx_Renamed );

		void PhsxStep();

	private:
		void UpdateTriangles();

		void ApplyScaling( Vector2 &v );

	public:
		void Draw();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CAPE
