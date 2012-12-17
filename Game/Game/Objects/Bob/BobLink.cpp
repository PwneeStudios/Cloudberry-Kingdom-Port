#include <global_header.h>

namespace CloudberryKingdom
{

	void BobLink::Release()
	{
		j.reset();
		k.reset();
	}

	BobLink::BobLink() :
		_j( 0 ), _k( 0 ),
		L( 0 ), a_in( 0 ), a_out( 0 ), MaxForce( 0 )
	{
		j = k = 0;

		L = 0;
		a_out = 0;

		////a_in = .005f;
		////MaxForce = 5;

		a_in = .00525f;
		MaxForce = 5.15f;
	}

	const bool BobLink::getInactive() const
	{
		// Don't draw the bungee if we are a dead spaceship or if we explode on death and are dead
		if ( ( Bob::AllExplode && !Bob::ShowCorpseAfterExplode ) || boost::dynamic_pointer_cast<BobPhsxSpaceship>( j->getCore()->MyLevel->DefaultHeroType ) != 0 && (j->Dead || j->Dying || k->Dead || k->Dying) )
			return true;

		// Don't draw the bungee if one of the players isn't being drawn.
		if ( !j->getCore()->Show || !k->getCore()->Show )
			return true;

		return false;
	}

	void BobLink::Draw()
	{
		if ( getInactive() )
			return;

		Draw( j->getCore()->Data.Position, k->getCore()->Data.Position );
	}

	void BobLink::Draw( Vector2 p1, Vector2 p2 )
	{
		Tools::QDrawer->DrawLine( p1, p2, Color::WhiteSmoke, 15 );
	}

	void BobLink::PhsxStep( const boost::shared_ptr<Bob> &bob )
	{
		if ( getInactive() )
			return;

		float Length = ( j->getCore()->Data.Position - k->getCore()->Data.Position ).Length();

		Vector2 Tangent = ( j->getCore()->Data.Position - k->getCore()->Data.Position );

		if ( Length < 1 )
			Tangent = Vector2();
		else
			Tangent /= Length;

		float Force;
		if ( Length < L )
			Force = a_out * ( Length - L );
		else
			Force = a_in * ( Length - L );
		if ( abs( Force ) > MaxForce )
			Force = ::Sign( Force ) * MaxForce;

		Vector2 Bottom = Vector2::Min( j->getCore()->Data.Position, k->getCore()->Data.Position );
		if ( bob->getCore()->Data.Position.Y > Bottom.Y )
			Force /= 5;

		Vector2 VectorForce = Force * Tangent;
		if ( bob == j )
			VectorForce *= -1;

		Tangent = VectorForce;
		Tangent.Normalize();
		float v = Vector2::Dot( bob->getCore()->Data.Velocity, Tangent );
		if ( v < 25 )
			bob->getCore()->Data.Velocity += VectorForce;
	}

	void BobLink::Connect( const boost::shared_ptr<Bob> &bob1, const boost::shared_ptr<Bob> &bob2 )
	{
		j = bob1;
		k = bob2;
		if ( bob1->MyBobLinks.empty() )
			bob1->MyBobLinks = std::vector<boost::shared_ptr<BobLink> >();
		if ( bob2->MyBobLinks.empty() )
			bob2->MyBobLinks = std::vector<boost::shared_ptr<BobLink> >();
		bob1->MyBobLinks.push_back( shared_from_this() );
		bob2->MyBobLinks.push_back( shared_from_this() );
	}
}
