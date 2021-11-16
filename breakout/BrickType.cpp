#include "BrickType.hpp"

BrickType::BrickType() {}

void BrickType::setBrickType(char c)
{
	if (c == '_')
		{
			id = '_';
			hitPoints = 0;
			breakScore = 0;
		}

	if (c=='S')
		{
			id = 'S';
			hitPoints = 1;
			breakScore = 5;
			texture = "Textures/Bricks/Soft.dds";
			hitSound = "Sounds/Hit_01.wav";
			breakSound = "Sounds/Break_01.wav";
		}

	if (c == 'M')
	{
		id = 'M';
		hitPoints = 2;
		breakScore = 10;
		texture = "Textures/Bricks/Medium.dds";
		hitSound = "Sounds/Hit_02.wav";
		breakSound = "Sounds/Break_02.wav";
	}

	if (c == 'H')
	{
		id = 'H';
		hitPoints = 3;
		breakScore = 15;
		texture = "Textures/Bricks/Hard.dds";
		hitSound = "Sounds/Hit_03.wav";
		breakSound = "Sounds/Break_03.wav";
	}

	if (c == 'I')
	{
		id = 'I';
		hitPoints = -1;
		breakScore = 0;
		texture = "Textures/Bricks/Infinite.dds";
		hitSound = "Sounds/Hit_04.wav";
	}
}

BrickType::~BrickType() {}