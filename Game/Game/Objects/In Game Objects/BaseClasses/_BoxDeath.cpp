#include <global_header.h>







namespace CloudberryKingdom
{

	void _BoxDeath::MakeNew()
	{
		_Death::MakeNew();

		Box->Initialize( Vector2::Zero, Vector2::One );
	}

	_BoxDeath::_BoxDeath()
	{
	}

	_BoxDeath::_BoxDeath( bool BoxesOnly )
	{
		Construct( BoxesOnly );
	}

	void _BoxDeath::Construct( bool BoxesOnly )
	{
		getCore()->BoxesOnly = BoxesOnly;

		Box = std::make_shared<AABox>();

		MakeNew();
	}

	Microsoft::Xna::Framework::Vector2 _BoxDeath::GetBoxPos()
	{
		return getPos();
	}

	void _BoxDeath::Init( Vector2 pos, const std::shared_ptr<Level> &level )
	{
		_Death::Init( pos, level );

		Box->Initialize( GetBoxPos(), BoxSize );

		Box->SetTarget( GetBoxPos(), BoxSize );
		Box->SwapToCurrent();
	}

	void _BoxDeath::Scale( float scale )
	{
		Box->Scale( scale );
	}

	void _BoxDeath::TargetPos()
	{
	}

	void _BoxDeath::ActivePhsxStep()
	{
		Box->SetTarget( getPos(), BoxSize );

		if ( getCore()->WakeUpRequirements )
		{
			Box->SwapToCurrent();
			getCore()->WakeUpRequirements = false;
		}
	}

	void _BoxDeath::PhsxStep2()
	{
		if ( getCore()->SkippedPhsx )
			return;

		Box->SwapToCurrent();
	}

	void _BoxDeath::OnMarkedForDeletion()
	{
		_Death::OnMarkedForDeletion();
	}

	void _BoxDeath::DrawBoxes()
	{
		Box->Draw( Color( 50, 50, 255, 120 ), 5 );
	}

	void _BoxDeath::Move( Vector2 shift )
	{
		_Death::Move( shift );

		Box->Move( shift );
	}

	void _BoxDeath::Interact( const std::shared_ptr<Bob> &bob )
	{
		if ( !getCore()->SkippedPhsx )
		{
			bool Col = Phsx::BoxBoxOverlap( bob->Box2, Box );

			if ( Col )
			{
				if ( getCore()->MyLevel->PlayMode == 0 )
					bob->Die( DeathType, this );

				if ( getCore()->MyLevel->PlayMode != 0 )
				{
					bool col = Phsx::BoxBoxOverlap_Tiered( Box, getCore(), bob, AutoGenSingleton );

					if ( col )
					{
						//if ((Pos - bob.Pos).Length() > 2000) Tools.Write(0);
						getCore()->getRecycle()->CollectObject(this);
					}
				}
			}
		}
	}

	void _BoxDeath::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());

		getCore()->WakeUpRequirements = true;
	}
}
