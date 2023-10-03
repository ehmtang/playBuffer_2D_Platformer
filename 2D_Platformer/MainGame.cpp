// Acknowledgements:
// Zeggy Games - player character sprite https://zegley.itch.io/2d-platformermetroidvania-asset-pack
// Ninjikin - tile sprites https://ninjikin.itch.io/starter-tiles
// CraftPix - Background sprites https://free-game-assets.itch.io/free-sky-with-clouds-background-pixel-art-set

#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "MainGame.h"

constexpr int DISPLAY_WIDTH{ 1280 };
constexpr int DISPLAY_HEIGHT{ 720 };
constexpr int DISPLAY_SCALE{ 1 };
constexpr int PLATFORM_WIDTH{ 32 };

const int ROOM[23][40] =
{
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},

	//	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	//	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	//	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	//	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};


GameState gameState;

void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);

	Play::LoadBackground("Data\\Backgrounds\\bg_5th.png");
	//Play::StartAudioLoop("theme");
	Play::CentreAllSpriteOrigins();
	HandleSizeScale();
	CreatePlatform();
	CreatePlayer();
}

bool MainGameUpdate(float elapsedTime)
{
	Play::ClearDrawingBuffer(Play::cWhite);
	HandleBackgrounds();
	UpdatePlayer(elapsedTime);
	HandleFinishLine(elapsedTime);
	DrawFinishLine();
	DrawParticle(elapsedTime);
	DrawPlatform();
	DrawCollisionBoxes();
	DrawBalloon();
	DrawPlayer();
	DrawUI();
	Play::PresentDrawingBuffer();
	return Play::KeyDown(VK_ESCAPE);
}

int MainGameExit(void)
{
	Play::DestroyManager();
	return PLAY_OK;
}

void UpdatePlayer(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	playerObj.scale = gameState.player.sizeScale;

	switch (gameState.player.state)
	{
	case STATE_IDLE:
	{
		Idle(elapsedTime);
		break;
	}
	case STATE_RUN:
	{
		Run(elapsedTime);
		break;
	}
	case STATE_JUMP:
	{
		Jump(elapsedTime);
		break;
	}
	case STATE_FALL:
	{
		Fall(elapsedTime);
		break;
	}
	case STATE_ATTACK:
	{
		Punch(elapsedTime);
		break;
	}
	case STATE_ROLL:
	{
		Roll(elapsedTime);
		break;
	}
	case STATE_AIRDASH:
	{
		AirDash(elapsedTime);
		break;
	}
	case STATE_WALLCLIMB:
	{
		WallClimb(elapsedTime);
		break;
	}
	case STATE_WALLJUMP:
	{
		WallJump(elapsedTime);
		break;
	}
	case STATE_HURT:
	{
		Hurt(elapsedTime);
		break;
	}
	case STATE_DEATH:
	{
		Death(elapsedTime);
		break;
	}
	}

	if (Play::IsLeavingDisplayArea(playerObj))
		playerObj.pos = playerObj.oldPos;

	Play::UpdateGameObject(playerObj);

	HandleGrounded();
	//HandleOnWall();
	HandleHurt();
	HandleObstructed();
}

void Idle(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_idle_left" : "player_idle", 0.25f);

	if (Play::KeyDown(VK_LEFT) || Play::KeyDown(VK_RIGHT))
	{
		gameState.player.state = STATE_RUN;
		return;
	}

	if (Play::KeyDown('Z'))
	{
		gameState.player.state = STATE_JUMP;
		return;
	}
	else if (Play::KeyPressed('X'))
	{
		gameState.player.state = STATE_ATTACK;
		return;
	}
	else if (Play::KeyPressed('C'))
	{
		gameState.player.state = STATE_ROLL;
		return;
	}

	if (!Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_RIGHT) && gameState.player.isGrounded == true)
	{
		playerObj.acceleration.x = 0;
		(abs(playerObj.velocity.x) < 0.01) ? 0 : playerObj.velocity.x *= 0.4;
	}

	if (gameState.player.isGrounded == false)
	{
		gameState.player.state = STATE_FALL;
		return;
	}
}

void Run(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	if (Play::KeyDown(VK_LEFT))
	{
		gameState.player.direction = -1;
		playerObj.acceleration.x = -gameState.player.maxRunAccel;
		Play::SetSprite(playerObj, "player_run_left", 0.25f);
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		gameState.player.direction = 1;
		Play::SetSprite(playerObj, "player_run", 0.25f);
		playerObj.acceleration.x = gameState.player.maxRunAccel;
	}

	playerObj.velocity.x = std::clamp(playerObj.velocity.x, -gameState.player.maxRunSpeed, gameState.player.maxRunSpeed);

	if (Play::KeyDown('Z'))
	{
		playerObj.acceleration.x = 0;
		gameState.player.state = STATE_JUMP;
		return;
	}
	else if (Play::KeyPressed('X'))
	{
		gameState.player.state = STATE_ATTACK;
		return;
	}
	else if (Play::KeyPressed('C'))
	{
		playerObj.acceleration.x = 0;
		gameState.player.state = STATE_ROLL;
		return;
	}

	if (!Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_RIGHT) && gameState.player.isGrounded == true)
	{
		playerObj.acceleration.x = 0;
		gameState.player.state = STATE_IDLE;
		return;
	}

	if (gameState.player.isGrounded == false)
	{
		playerObj.acceleration.x = 0;
		gameState.player.state = STATE_FALL;
		return;
	}
}

void Jump(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_jump_left" : "player_jump", 0);

	if (playerObj.velocity.y < -5)
		playerObj.frame = 0;
	else if (-5 <= playerObj.velocity.y && playerObj.velocity.y <= 5)
		playerObj.frame = 1;
	else if (playerObj.velocity.y > 5)
		playerObj.frame = 2;

	if (Play::KeyDown('Z') && gameState.player.hasJumped == false)
	{
		gameState.player.jumpTime += elapsedTime;
		playerObj.velocity.y = -gameState.player.jumpImpulse;
		if (gameState.player.jumpTime > gameState.player.jumpEndTime)
			gameState.player.hasJumped = true;
	}
	else if (!Play::KeyDown('Z') && gameState.player.hasJumped == false)
		gameState.player.hasJumped = true;

	if (Play::KeyDown(VK_LEFT))
		playerObj.velocity.x = -gameState.player.maxRunSpeed;
	else if (Play::KeyDown(VK_RIGHT))
		playerObj.velocity.x = gameState.player.maxRunSpeed;

	playerObj.velocity.x = std::clamp(playerObj.velocity.x, -gameState.player.maxRunSpeed, gameState.player.maxRunSpeed);

	if (Play::KeyPressed('C'))
	{
		gameState.player.state = STATE_AIRDASH;
		return;
	}

	if (gameState.player.isGrounded == false && playerObj.velocity.y < 0)
	{
		gameState.player.state = STATE_FALL;
		return;
	}

	//if (gameState.player.isGrounded == true)
	//{
	//	gameState.player.hasJumped = false;
	//	gameState.player.jumpTime = 0;
	//	gameState.player.state = STATE_IDLE;
	//	return;
	//}
}

void Fall(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	playerObj.acceleration.x = 0;

	gameState.player.coyoteTime += elapsedTime;

	if (gameState.player.hasJumped == false && gameState.player.coyoteTime < gameState.player.coyoteTimeThreshold)
	{
		if (Play::KeyDown('Z'))
		{
			gameState.player.coyoteTime = 0;
			gameState.player.state = STATE_JUMP;
			return;
		}
	}

	if (gameState.player.isGrounded == false)
	{
		Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_jump_left" : "player_jump", 0);
		playerObj.frame = 2;
	}

	if (Play::KeyDown(VK_LEFT))
		playerObj.pos.x -= gameState.player.maxRunSpeed;
	else if (Play::KeyDown(VK_RIGHT))
		playerObj.pos.x += gameState.player.maxRunSpeed;

	playerObj.velocity.x = std::clamp(playerObj.velocity.x, -gameState.player.maxRunSpeed, gameState.player.maxRunSpeed);


	if (Play::KeyPressed('C'))
	{
		gameState.player.coyoteTime = 0;
		gameState.player.state = STATE_AIRDASH;
		return;
	}

	if (gameState.player.isGrounded == true)
	{
		gameState.player.coyoteTime = 0;
		gameState.player.state = STATE_IDLE;
		return;
	}
}

void AirDash(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_jump_left" : "player_jump", 0);

	float q_rsqrt_2 = q_rsqrt(2);

	if (gameState.player.isAirDashing == false && gameState.player.hasAirDashed == false)
	{
		gameState.player.airDashTime = 0;
		gameState.player.hasAirDashed = true;
		gameState.player.isAirDashing = true;

		playerObj.velocity = Vector2D(0, 0);
		playerObj.acceleration = Vector2D(0, 0);

		if (Play::KeyDown(VK_UP) && !Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_RIGHT))
			gameState.player.airDashDirection = Vector2D(0, -1);
		else if (Play::KeyDown(VK_UP) && Play::KeyDown(VK_RIGHT))
			gameState.player.airDashDirection = Vector2D(q_rsqrt_2, -q_rsqrt_2);
		else if (Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_UP) && !Play::KeyDown(VK_DOWN))
			gameState.player.airDashDirection = Vector2D(1, 0);
		else if (Play::KeyDown(VK_DOWN) && Play::KeyDown(VK_RIGHT))
			gameState.player.airDashDirection = Vector2D(q_rsqrt_2, q_rsqrt_2);
		else if (Play::KeyDown(VK_DOWN) && !Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_RIGHT))
			gameState.player.airDashDirection = Vector2D(0, 1);
		else if (Play::KeyDown(VK_DOWN) && Play::KeyDown(VK_LEFT))
			gameState.player.airDashDirection = Vector2D(-q_rsqrt_2, q_rsqrt_2);
		else if (Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_UP) && !Play::KeyDown(VK_DOWN))
			gameState.player.airDashDirection = Vector2D(-1, 0);
		else if (Play::KeyDown(VK_UP) && Play::KeyDown(VK_LEFT))
			gameState.player.airDashDirection = Vector2D(-q_rsqrt_2, -q_rsqrt_2);
	}

	if (gameState.player.airDashTime <= gameState.player.airDashEndTime)
	{
		gameState.player.airDashTime += elapsedTime;
		ScreenShake(elapsedTime);
		playerObj.velocity = gameState.player.airDashDirection * gameState.player.airDashImpulse;
	}
	else if (gameState.player.airDashTime > gameState.player.airDashEndTime)
	{
		playerObj.velocity = Vector2D(0, 0);
		gameState.player.airDashDirection = Vector2D(0, 0);
		gameState.player.isAirDashing = false;
		gameState.player.state = STATE_JUMP;
		return;
	}
}

void Punch(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_punch_left" : "player_punch", 0.7f);

	if (Play::IsAnimationComplete(playerObj))
	{
		gameState.player.state = STATE_IDLE;
		return;
	}
	else
		playerObj.velocity = { 0 , 0 };
}

void Roll(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_roll_left" : "player_roll", 1.f);

	if (Play::IsAnimationComplete(playerObj))
	{
		playerObj.velocity = { 0 , 0 };
		gameState.player.state = STATE_IDLE;
		return;
	}
	else
	{
		ScreenShake(elapsedTime);

		playerObj.velocity.x = gameState.player.direction * gameState.player.rollSpeed;
	}
}

void WallClimb(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	if (gameState.player.hasLandedOnWall == false && gameState.player.isOnWall == true)
	{
		Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_wall_land_left" : "player_wall_land", 0.5f);
		if (!Play::IsAnimationComplete(playerObj))
		{
			(abs(playerObj.velocity.y) > 0.01) ? playerObj.velocity.y *= 0.5 : 0;

			if (Play::KeyPressed('Z'))
			{
				gameState.player.hasLandedOnWall = false;
				gameState.player.state = STATE_WALLJUMP;
				return;
			}
		}
		else
		{
			gameState.player.hasLandedOnWall = true;
		}
	}
	else if (gameState.player.hasLandedOnWall == true && gameState.player.isOnWall == true)
	{
		playerObj.velocity.x = 0;
		playerObj.acceleration.y = 0;

		if (Play::KeyDown(VK_UP))
		{
			Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_wall_land_left" : "player_wall_land", 0.4f);
			playerObj.velocity.y = -gameState.player.maxClimbUpSpeed;

		}
		else if (Play::KeyDown(VK_DOWN))
		{
			Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_wall_slid_left" : "player_wall_slid", 0.2f);
			playerObj.velocity.y += (gameState.player.maxClimbDownSpeed * elapsedTime * 2.5f);
		}

		if (Play::KeyPressed('Z'))
		{
			gameState.player.hasLandedOnWall = false;
			gameState.player.state = STATE_WALLJUMP;
			return;
		}

		if (!Play::KeyDown(VK_UP) && !Play::KeyDown(VK_DOWN) && gameState.player.isOnWall == true)
		{
			Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_wall_slid_left" : "player_wall_slid", 0.f);
			playerObj.frame = 0;
			playerObj.velocity = Vector2D(0, 0);
			playerObj.acceleration.y = 0;
		}
	}
	else if (gameState.player.isOnWall == false)
	{
		gameState.player.state = STATE_FALL;
		return;
	}
}

void WallJump(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	float q_rsqrt_2 = q_rsqrt(2);

	if (gameState.player.hasJumped == false)
	{
		gameState.player.direction *= -1;
		gameState.player.hasJumped = true;
	}

	playerObj.velocity = Vector2D((gameState.player.direction * q_rsqrt_2), -q_rsqrt_2) * Vector2D(gameState.player.wallJumpImpulse, gameState.player.wallJumpImpulse);
	Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_jump_left" : "player_jump", 0);

	gameState.player.state = STATE_JUMP;

}

void Hurt(float& elapsedTime)
{
	// All states go to hurt

	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	Play::SetSprite(playerObj, "player_hurt", 0.2f);

	if (!Play::IsAnimationComplete(playerObj))
	{
		playerObj.pos += { 6, 0 };
	}
	else
	{
		playerObj.velocity = { 0 , 0 };
		gameState.player.state = STATE_IDLE;
		return;
	}
}

void Death(float& elapsedTime)
{
	// All states go to death

	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	Play::SetSprite(playerObj, "player_death", 0.2f);

	if (Play::IsAnimationComplete(playerObj))
	{
		playerObj.frame = 9;
	}
}

void HandleSizeScale()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	gameState.player.GroundBox *= Vector2D(gameState.player.sizeScale, 1);
	gameState.player.GroundBoxOffset *= Vector2D(1, gameState.player.sizeScale);
	gameState.player.WallBox *= Vector2D(1, gameState.player.sizeScale);
	gameState.player.WallBoxOffset *= Vector2D(gameState.player.sizeScale, gameState.player.sizeScale);
	gameState.player.HurtBox *= Vector2D(gameState.player.sizeScale, gameState.player.sizeScale);
	gameState.player.HurtBoxOffset;
	gameState.player.PunchBox *= Vector2D(gameState.player.sizeScale, gameState.player.sizeScale);
	gameState.player.PunchBoxOffset *= Vector2D(gameState.player.sizeScale, 1);
}

void Friction()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	if (gameState.player.isGrounded == true)
	{
		playerObj.velocity.x = 0;
		playerObj.acceleration.x = 0;
	}
}

void HandleFinishLine(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };


	if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, gameState.finishLine.pos, gameState.finishLine.box, Vector2D(0, 0))
		&& (playerObj.pos.x - gameState.player.HurtBox.x - gameState.player.HurtBoxOffset.x) > (gameState.finishLine.pos.x - gameState.finishLine.box.x))
	{
		gameState.finishLine.crossesFinishLine = false;
	}
	else if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, gameState.finishLine.pos, gameState.finishLine.box, Vector2D(0, 0))
		&& (playerObj.pos.x + gameState.player.HurtBox.x + gameState.player.HurtBoxOffset.x) <= gameState.finishLine.pos.x)
	{
		gameState.finishLine.crossesFinishLine = true;
	}

	if (gameState.finishLine.crossesFinishLine == true)
	{
		gameState.finishLine.splitTime += elapsedTime;
	}

	if (gameState.finishLine.crossesFinishLine == true
		&& gameState.finishLine.hasCompletedLap == false)
	{
		if (gameState.finishLine.completedLap > 0)
			gameState.finishLine.vSplitTime.push_back(gameState.finishLine.splitTime);
		gameState.finishLine.splitTime = 0;
		gameState.finishLine.hasCompletedLap = true;
		gameState.finishLine.completedLap += 1;
	}
	else if (gameState.finishLine.crossesFinishLine == false)
	{
		gameState.finishLine.hasCompletedLap = false;
	}
}

void HandleObstructed()
{
	//GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };


	//for (Platform& p : gameState.vPlatform)
	//{
	//	//if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
	//	//{
	//	//	playerObj.pos = playerObj.oldPos;
	//	//	playerObj.velocity.x = 0;
	//	//	playerObj.acceleration.x = 0;
	//	//	return;
	//	//}
	//	if (AABBCollisionTest(playerObj.pos, gameState.player.WallBox, Vector2f(gameState.player.direction, 1) * gameState.player.WallBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
	//	{
	//		return;
	//	}

	//	if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
	//	{
	//		ApplyReflection(playerObj, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0));
	//		return;
	//	}
	//}

	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	for (Platform& p : gameState.vPlatform)
	{
		if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0))
			&& GetNearestEdge(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)) == Vector2D(0, -1))
		{
			return;
		}
		else if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0))
			&& GetNearestEdge(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)) == Vector2D(0, 1))
		{
			int diff = playerObj.pos.y - playerObj.oldPos.y;
			playerObj.pos.y = playerObj.oldPos.y;
			for (int i = 0; i < diff; ++i)
			{
				if (AABBCollisionTest(playerObj.oldPos + Vector2D(0, i), gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
				{
					playerObj.pos.y += i;
					break;
				}
			}
			ApplyReflection(playerObj, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0));
		}
		else if ((AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0))
			&& GetNearestEdge(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)) == Vector2D(-1, 0))
			|| (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0))
				&& GetNearestEdge(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)) == Vector2D(1, 0)))
		{
			int diff = playerObj.pos.x - playerObj.oldPos.x;
			playerObj.pos.x = playerObj.oldPos.x;
			for (int i = 0; i < diff; ++i)
			{
				if (AABBCollisionTest(playerObj.oldPos + Vector2D(0, i), gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
				{
					playerObj.pos.x += i;
					break;
				}
			}
			playerObj.velocity.x = 0;
		}
	}
}

void HandleGrounded()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	for (Platform& p : gameState.vPlatform)
	{
		if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0))
			&& GetNearestEdge(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)) == Vector2D(0, -1))
		{
			int diff = playerObj.pos.y - playerObj.oldPos.y;
			playerObj.pos.y = playerObj.oldPos.y;
			for (int i = 0; i < diff; ++i)
			{
				if (AABBCollisionTest(playerObj.oldPos + Vector2D(0, diff), gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
				{
					playerObj.pos.y += i;
					gameState.player.isGrounded = true;
					break;
				}
			}
			gameState.player.hasJumped == false;
			gameState.player.hasAirDashed = false;
			playerObj.acceleration.y = 0;
			playerObj.velocity.y = 0;

			break;
		}
		else
			gameState.player.isGrounded = false;
	}

	if (gameState.player.isGrounded == false || gameState.player.isOnWall == false)
	{
		playerObj.acceleration.y = gameState.player.gravity.y;
		playerObj.velocity.y = std::clamp(playerObj.velocity.y, -gameState.player.maxFallSpeed, gameState.player.maxFallSpeed);
	}
}

void HandleOnWall()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	for (Platform& p : gameState.vPlatform)
	{
		if (gameState.player.state == STATE_WALLJUMP)
		{
			gameState.player.isOnWall = false;
		}
		else if (AABBCollisionTest(playerObj.pos, gameState.player.WallBox, Vector2f(gameState.player.direction, 1) * gameState.player.WallBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)) && gameState.player.isGrounded == false)
		{
			gameState.player.isOnWall = true;
			gameState.player.hasJumped = false;
			gameState.player.state = STATE_WALLCLIMB;
			return;
		}
		else
		{
			gameState.player.isOnWall = false;
		}
	}
}

void HandleHurt()
{

}

void BalloonCollision()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	std::vector<int> balloonIds = Play::CollectGameObjectIDsByType(TYPE_BALLOON);
	for (int balloonId : balloonIds)
	{
		GameObject& balloonObj{ Play::GetGameObject(balloonId) };

		if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, balloonObj.pos, Vector2D(32, 32), Vector2D(0, 0)))
		{
			Play::DestroyGameObject(balloonId);
			gameState.player.hasAirDashed = false;
		}
	}

}

void UpdatePlayerCamera(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	Play::SetCameraPosition(Point2f{ playerObj.pos.x - DISPLAY_WIDTH / 2, playerObj.pos.y - DISPLAY_HEIGHT / 2 });
}

void ScreenShake(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	if (gameState.camera.shakeTime < gameState.camera.shakeEndTime)
	{
		Point2f randomPos = { Play::RandomRollRange(-3, 3), Play::RandomRollRange(-3, 3) };
		Play::SetCameraPosition(randomPos);
		gameState.camera.shakeTime += elapsedTime;
	}
	else if (gameState.camera.shakeTime >= gameState.camera.shakeEndTime)
	{
		Play::SetCameraPosition(Point2f(0, 0));
		gameState.camera.shakeTime = 0;
	}
}

void DrawParticle(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	switch (gameState.player.state)
	{
	case STATE_AIRDASH:
	{
		gameState.particleEmitter.splitTime += elapsedTime;

		if (gameState.particleEmitter.splitTime > gameState.particleEmitter.emitPeriod)
		{
			AddParticleToEmitter(playerObj);
			gameState.particleEmitter.splitTime = 0;
		}

		if (!gameState.particleEmitter.vParticle.empty())
			UpdateParticleLifeTime(elapsedTime);

		break;
	}
	case STATE_ROLL:
	{
		gameState.particleEmitter.splitTime += elapsedTime;

		if (gameState.particleEmitter.splitTime > gameState.particleEmitter.emitPeriod)
		{
			AddParticleToEmitter(playerObj);
			gameState.particleEmitter.splitTime = 0;
		}

		if (!gameState.particleEmitter.vParticle.empty())
		{
			UpdateParticleLifeTime(elapsedTime);
		}
		break;
	}
	default:
	{
		gameState.particleEmitter.splitTime = 0;
		if (!gameState.particleEmitter.vParticle.empty())
			UpdateParticleLifeTime(elapsedTime);

		break;
	}
	}
}

void AddParticleToEmitter(GameObject& playerObj)
{
	Particle particle;

	for (int i = 0; i < gameState.particleEmitter.emitParticles; ++i)
	{
		gameState.particleEmitter.vParticle.push_back(particle);
		gameState.particleEmitter.vParticle.back().pos = playerObj.pos;
		gameState.particleEmitter.vParticle.back().spriteId = playerObj.spriteId;
		gameState.particleEmitter.vParticle.back().spriteFrame = playerObj.frame;
	}
}

void UpdateParticleLifeTime(float& elapsedTime)
{
	Particle particle;

	for (int i = 0; i < gameState.particleEmitter.vParticle.size(); ++i)
	{
		gameState.particleEmitter.vParticle[i].currentLifetime += elapsedTime;
		gameState.particleEmitter.vParticle[i].opacity = exponentialDecay(gameState.particleEmitter.baseOpacity, gameState.particleEmitter.decayConstant, gameState.particleEmitter.vParticle[i].currentLifetime);
		Play::DrawSpriteRotated(gameState.particleEmitter.vParticle[i].spriteId, gameState.particleEmitter.vParticle[i].pos, gameState.particleEmitter.vParticle[i].spriteFrame, 0, gameState.player.sizeScale, gameState.particleEmitter.vParticle[i].opacity);

		if (gameState.particleEmitter.vParticle[i].opacity < gameState.particleEmitter.opacityThreshold)
			gameState.particleEmitter.vParticle.erase(gameState.particleEmitter.vParticle.begin() + i);
	}
}

void DrawPlayer()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	Play::DrawObjectRotated(playerObj);
}

void DrawCollisionBoxes()
{
	switch (gameState.gameMode)
	{
	case(TEST_MODE):
	{
		GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

		for (Platform& p : gameState.vPlatform)
		{
			if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
				Play::DrawRect(p.pos - p.PlatformBox, p.pos + p.PlatformBox, Play::cRed, true);
			else
				Play::DrawRect(p.pos - p.PlatformBox, p.pos + p.PlatformBox, Play::cGreen);

			if (gameState.player.direction == -1)
			{
				if (AABBCollisionTest(playerObj.pos, gameState.player.WallBox, Vector2D(-1, 1) * gameState.player.WallBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
					Play::DrawRect(playerObj.pos - gameState.player.WallBox + Vector2D(-1, 1) * gameState.player.WallBoxOffset, playerObj.pos + gameState.player.WallBox + Vector2D(-1, 1) * gameState.player.WallBoxOffset, Play::cRed, true);
				else
					Play::DrawRect(playerObj.pos - gameState.player.WallBox + Vector2D(-1, 1) * gameState.player.WallBoxOffset, playerObj.pos + gameState.player.WallBox + Vector2D(-1, 1) * gameState.player.WallBoxOffset, Play::cYellow);
				if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, Vector2D(-1, 1) * gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
					Play::DrawRect(playerObj.pos - gameState.player.HurtBox + Vector2D(-1, 1) * gameState.player.HurtBoxOffset, playerObj.pos + gameState.player.HurtBox + Vector2D(-1, 1) * gameState.player.HurtBoxOffset, Play::cRed, true);
				else
					Play::DrawRect(playerObj.pos - gameState.player.HurtBox + Vector2D(-1, 1) * gameState.player.HurtBoxOffset, playerObj.pos + gameState.player.HurtBox + Vector2D(-1, 1) * gameState.player.HurtBoxOffset, Play::cCyan);

				if (AABBCollisionTest(playerObj.pos, gameState.player.PunchBox, Vector2D(-1, 1) * gameState.player.PunchBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
					Play::DrawRect(playerObj.pos - gameState.player.PunchBox + Vector2D(-1, 1) * gameState.player.PunchBoxOffset, playerObj.pos + gameState.player.PunchBox + Vector2D(-1, 1) * gameState.player.PunchBoxOffset, Play::cRed, true);
				else
					Play::DrawRect(playerObj.pos - gameState.player.PunchBox + Vector2D(-1, 1) * gameState.player.PunchBoxOffset, playerObj.pos + gameState.player.PunchBox + Vector2D(-1, 1) * gameState.player.PunchBoxOffset, Play::cMagenta);
			}
			else if (gameState.player.direction == 1)
			{
				if (AABBCollisionTest(playerObj.pos, gameState.player.WallBox, gameState.player.WallBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
					Play::DrawRect(playerObj.pos - gameState.player.WallBox + gameState.player.WallBoxOffset, playerObj.pos + gameState.player.WallBox + gameState.player.WallBoxOffset, Play::cRed, true);
				else
					Play::DrawRect(playerObj.pos - gameState.player.WallBox + gameState.player.WallBoxOffset, playerObj.pos + gameState.player.WallBox + gameState.player.WallBoxOffset, Play::cYellow);
				if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
					Play::DrawRect(playerObj.pos - gameState.player.HurtBox + gameState.player.HurtBoxOffset, playerObj.pos + gameState.player.HurtBox + gameState.player.HurtBoxOffset, Play::cRed, true);
				else
					Play::DrawRect(playerObj.pos - gameState.player.HurtBox + gameState.player.HurtBoxOffset, playerObj.pos + gameState.player.HurtBox + gameState.player.HurtBoxOffset, Play::cCyan);
				if (AABBCollisionTest(playerObj.pos, gameState.player.PunchBox, gameState.player.PunchBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
					Play::DrawRect(playerObj.pos - gameState.player.PunchBox + gameState.player.PunchBoxOffset, playerObj.pos + gameState.player.PunchBox + gameState.player.PunchBoxOffset, Play::cRed, true);
				else
					Play::DrawRect(playerObj.pos - gameState.player.PunchBox + gameState.player.PunchBoxOffset, playerObj.pos + gameState.player.PunchBox + gameState.player.PunchBoxOffset, Play::cMagenta);
			}
		}
		break;
	}
	case(PLAY_MODE):
	{
		break;
	}
	}
}

void DrawPlatform()
{
	for (Platform& p : gameState.vPlatform)
	{
		Play::DrawSprite(Play::GetSpriteId("dark_brick"), p.pos, 0);
	}
}

void DrawBalloon()
{
	std::vector<int> balloonIds = Play::CollectGameObjectIDsByType(TYPE_BALLOON);
	for (int balloonId : balloonIds)
	{
		GameObject& balloonObj{ Play::GetGameObject(balloonId) };
		Play::DrawObjectRotated(balloonObj);
	}
}

void DrawFinishLine()
{
	Play::DrawSprite(Play::GetSpriteId("finish_line"), gameState.finishLine.pos, 0);
}

void DrawUI()
{
	switch (gameState.gameMode)
	{
	case(TEST_MODE):
	{
		GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

		Play::DrawFontText("64px", "JUMP TIMER: " + std::to_string(gameState.player.jumpTime), Point2D(37, 32), Play::LEFT);
		Play::DrawFontText("64px", "AIR DASH TIMER: " + std::to_string(gameState.player.airDashTime), Point2D(37, 69), Play::LEFT);
		Play::DrawFontText("64px", "COYOTE TIMER: " + std::to_string(gameState.player.coyoteTime), Point2D(37, 106), Play::LEFT);
		Play::DrawFontText("64px", "PARTICLE SPLIT TIMER: " + std::to_string(gameState.particleEmitter.splitTime), Point2D(37, 143), Play::LEFT);

		Play::DrawFontText("64px", "STATE: " + std::to_string(gameState.player.state), Point2D(DISPLAY_WIDTH - 37, 32), Play::RIGHT);
		Play::DrawFontText("64px", "HAS JUMPED: " + std::to_string(gameState.player.hasJumped), Point2D(DISPLAY_WIDTH - 37, 69), Play::RIGHT);
		Play::DrawFontText("64px", "HAS AIR DASHED: " + std::to_string(gameState.player.hasAirDashed), Point2D(DISPLAY_WIDTH - 37, 106), Play::RIGHT);
		Play::DrawFontText("64px", "HAS LANDED ON WALL: " + std::to_string(gameState.player.hasLandedOnWall), Point2D(DISPLAY_WIDTH - 37, 143), Play::RIGHT);
		Play::DrawFontText("64px", "IS GROUNDED: " + std::to_string(gameState.player.isGrounded), Point2D(DISPLAY_WIDTH - 37, 180), Play::RIGHT);

		Play::DrawFontText("64px", "POSITION: (" + std::to_string(playerObj.pos.x) + ',' + ' ' + std::to_string(playerObj.pos.y) + ')', Point2D(DISPLAY_WIDTH - 37, 254), Play::RIGHT);
		Play::DrawFontText("64px", "VELOCITY: (" + std::to_string(playerObj.velocity.x) + ',' + ' ' + std::to_string(playerObj.velocity.y) + ')', Point2D(DISPLAY_WIDTH - 37, 291), Play::RIGHT);
		Play::DrawFontText("64px", "ACCELERATION: (" + std::to_string(playerObj.acceleration.x) + ',' + ' ' + std::to_string(playerObj.acceleration.y) + ')', Point2D(DISPLAY_WIDTH - 37, 328), Play::RIGHT);
		Play::DrawFontText("64px", "COLLISION DIR: (" + std::to_string(gameState.player.collisionDir.x) + ',' + ' ' + std::to_string(gameState.player.collisionDir.y) + ')', Point2D(DISPLAY_WIDTH - 37, 365), Play::RIGHT);
		break;
	}
	case(PLAY_MODE):
	{
		if (gameState.finishLine.vSplitTime.size() > 0)
		{
			float fastestSplit = *std::min_element(gameState.finishLine.vSplitTime.begin(), gameState.finishLine.vSplitTime.end());
			Play::DrawFontText("64px", "STATE: " + std::to_string(gameState.player.state), Point2D(DISPLAY_WIDTH - 64, 64), Play::RIGHT);
			Play::DrawFontText("64px", "FASTEST SPLIT: " + std::to_string(fastestSplit), Point2D(DISPLAY_WIDTH - 64, 101), Play::RIGHT);
			Play::DrawFontText("64px", "SPLIT TIME: " + std::to_string(gameState.finishLine.splitTime), Point2D(DISPLAY_WIDTH - 64, 138), Play::RIGHT);
		}
		else
		{
			Play::DrawFontText("64px", "STATE: " + std::to_string(gameState.player.state), Point2D(DISPLAY_WIDTH - 64, 64), Play::RIGHT);
			Play::DrawFontText("64px", "SPLIT TIME: " + std::to_string(gameState.finishLine.splitTime), Point2D(DISPLAY_WIDTH - 64, 101), Play::RIGHT);
		}
		Play::DrawFontText("64px", "CROSSES FINISH LINE: " + std::to_string(gameState.finishLine.crossesFinishLine), Point2D(64, 64), Play::LEFT);
		Play::DrawFontText("64px", "COMPLETED LAP: " + std::to_string(gameState.finishLine.completedLap), Point2D(64, 101), Play::LEFT);
		Play::DrawFontText("64px", "HAS COMPLETED LAP: " + std::to_string(gameState.finishLine.hasCompletedLap), Point2D(64, 138), Play::LEFT);
		break;
	}
	}
}

void HandleBackgrounds()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	// if player passes finishing line
	// change background
	Play::DrawBackground();
}

void CreatePlayer()
{
	int id{ Play::CreateGameObject(TYPE_PLAYER, gameState.player.startingPos, 0, "player_idle") };
	GameObject& playerObj{ Play::GetGameObject(id) };
}

void CreatePlatform()
{
	Platform platform;

	int gap = 16;

	for (int row = 0; row < 23; ++row)
	{
		for (int col = 0; col < 40; ++col)
		{
			if (ROOM[row][col] == 1)
			{
				gameState.vPlatform.push_back(platform);
				gameState.vPlatform.back().pos = Point2D(gap + (col * 32), gap + (row * 32));
			}
		}
	}
}

float q_rsqrt(float number)
{
	// Quake3 inverse root algorithm
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y;									   // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);			               // wtf?
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));			   // 1st iteration
	// y  = y * ( threehalfs - ( x2 * y * y ) );	   // 2nd iteration, this can be removed

	return y;
}

float exponentialDecay(const float& A0, const float& lambda, const float& time)
{
	return A0 * exp(-lambda * time);
}

bool AABBCollisionTest(const Point2D& aPos, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset)
{
	float left = abs((aPos.x + aAABB.x + aOffset.x) - (bPos.x - bAABB.x - bOffset.x));
	float right = abs((aPos.x - aAABB.x - aOffset.x) - (bPos.x + bAABB.x + bOffset.x));
	float top = abs((aPos.y + aAABB.y + aOffset.y) - (bPos.y - bAABB.y - bOffset.y));
	float bottom = abs((aPos.y - aAABB.y - aOffset.y) - (bPos.y + bAABB.y + bOffset.y));

	// aObj hit left side of bObj
	if (left < right && left < top && left < bottom)
		gameState.player.collisionDir = Vector2D(-1.0f, 0.0f);

	// aObj hit right side of bObj
	else if (right < left && right < top && right < bottom)
		gameState.player.collisionDir = Vector2D(1.0f, 0.0f);

	// aObj hit top side of bObj
	else if (top < bottom && top < left && top < right)
		gameState.player.collisionDir = Vector2D(0.0f, -1.0f);

	// aObj hit bottom side of bObj
	else if (bottom < top && bottom < left && bottom < right)
		gameState.player.collisionDir = Vector2D(0.0f, 1.0f);

	else
		gameState.player.collisionDir = Vector2D(0.0f, 0.0f);

	return (aPos.x - aAABB.x + aOffset.x < bPos.x + bAABB.x + bOffset.x
		&& aPos.x + aAABB.x + aOffset.x > bPos.x - bAABB.x + bOffset.x
		&& aPos.y - aAABB.y + aOffset.y < bPos.y + bAABB.y + bOffset.y
		&& aPos.y + aAABB.y + aOffset.y > bPos.y - bAABB.y + bOffset.y);
}

void ApplyReflection(GameObject& aObj, const Point2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Point2D& bAABB, const Vector2D& bOffset)
{
	Vector2D collisionEdge = GetNearestEdge(aObj.pos, aAABB, aOffset, bPos, bAABB, bOffset);
	Vector2D surfaceNormal = collisionEdge.Perpendicular();
	float dotProduct = aObj.velocity.Dot(surfaceNormal);
	Vector2D reflectionVector = aObj.velocity - (2.0 * dotProduct * surfaceNormal);
	reflectionVector.Normalize();
	aObj.velocity = -reflectionVector * gameState.player.obstructedImpulse;
}

Vector2D GetNearestEdge(const Point2D& aPos, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset)
{
	float left = abs((aPos.x + aAABB.x + aOffset.x) - (bPos.x - bAABB.x - bOffset.x));
	float right = abs((aPos.x - aAABB.x - aOffset.x) - (bPos.x + bAABB.x + bOffset.x));
	float top = abs((aPos.y + aAABB.y + aOffset.y) - (bPos.y - bAABB.y - bOffset.y));
	float bottom = abs((aPos.y - aAABB.y - aOffset.y) - (bPos.y + bAABB.y + bOffset.y));

	if (left < right && left < top && left < bottom)
		return Vector2D(-1.0f, 0.0f);
	else if (right < left && right < top && right < bottom)
		return Vector2D(1.0f, 0.0f);
	else if (top < bottom && top < left && top < right)
		return Vector2D(0.0f, -1.0f);
	else if (bottom < top && bottom < left && bottom < right)
		return Vector2D(0.0f, 1.0f);
	else
		return Vector2D(0.0f, 0.0f);
}

void MergeCollisionBox()
{

}