// Acknowledgements:
// Zeggy Games - player character sprite https://zegley.itch.io/2d-platformermetroidvania-asset-pack
// Nate Kling - platform sprites https://drive.google.com/file/d/1hNrC1vZqzQ7fjO3Q1qFxWe0PERl8dXDs/view
// CraftPix - Background sprites https://www.youtube.com/channel/UCW6u-uvdYt5ub0zsZDAHXKw

#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"


/* TODO:
 * Jump and Fall
 *	- Variable jump height		DONE
 *  - Apex modifier
 *  - Jump buffering
 *  - Coyote time
 *  - Clamped fall speed		DONE
 *  - Edge detection
 *
 * Wall Slide, Climb and Jump
 * 
 * Platforms, TileMaps and Level Design  
 * 
 */

constexpr int DISPLAY_WIDTH{ 1280 };
constexpr int DISPLAY_HEIGHT{ 720 };
constexpr int DISPLAY_SCALE{ 1 };
constexpr int PLATFORM_WIDTH{ 32 };

enum GameObjectType
{
	TYPE_NULL = -1,
	TYPE_PLAYER,
	TYPE_DESTROYED,
	TYPE_PLATFORM,
};

enum PlayerState
{
	STATE_IDLE = 0,
	STATE_RUN,
	STATE_JUMP,
	STATE_FALL,
	STATE_AIRDASH,
	STATE_ATTACK,
	STATE_ROLL,
	STATE_WALLCLIMB,
	STATE_WALLJUMP,
	STATE_HURT,
	STATE_DEATH,
};

struct Particle
{
	float currentLifetime{ 0 };
	float lifetime{ 0.2f };
	float baseOpacity{ 0.5f };
	float opacityThreshold{ 0.01f };
	float decayConstant{ 5.0f };
	Point2D pos;
	int spriteId;
};

struct CameraInfo
{
	Point2f cameraPos;
	float shakeTime;
	float shakeEndTime{ 0.08f };
};

struct ParticleEmitter
{
	std::vector<Particle> vParticle;
	float splitTime{ 0.0f };
	float emitPeriod{ 0.05f };
	const int emitParticles{ 1 };
};

struct PlayerInfo
{
	int health{ 100 };
	int direction{ 1 };
	const float runSpeed{ 5 };
	const float runAccel{ 5 };

	bool hasJumped;
	float jumpTime{ 0 };
	float jumpImpulse{ 20 };
	float jumpEndTime{ 0.5f };
	float coyoteTimeThreshold{ 0.1f };
	const float terminalVelocity{ 50.f };

	bool hasAirDashed;
	bool isAirDashing;
	float airDashTime{ 0 };
	float airDashImpulse{ 50 };
	float airDashEndTime{ 0.1f };
	Vector2D airDashDirection;

	const int rollSpeed{ 10 };

	bool hasLandedOnWall;
	const float wallJumpImpulse{ 30 };

	const float climbUp{ 1.2f };
	const float climbDown{ 5 };
	const float climbAccel{ 5 };

	bool isGrounded;
	bool isOnWall;
	bool isHurt;

	Vector2D gravity{ 0, 1.f };

	PlayerState state = STATE_IDLE;

	const Vector2D GroundBox{ 12, 1 };
	const Vector2D GroundBoxOffset{ 0, 46 };
	const Vector2D WallBox{ 1, 20 };
	const Vector2D WallBoxOffset{ 20, -10 };
	const Vector2D HurtBox{ 14, 40 };
	const Vector2D HurtBoxOffset{ 0, 0 };
	const Vector2D PunchBox{ 20, 20 };
	const Vector2D PunchBoxOffset{ 75, 0 };
};

struct Platform
{
	int type = TYPE_PLATFORM;
	Point2D pos;
	const Vector2D PlatformBox{ 16, 16 };
};


struct GameState
{
	PlayerInfo player;
	std::vector<Platform> vPlatform;
	ParticleEmitter particleEmitter;
	CameraInfo camera;
};

GameState gameState;

// Update Player prototypes
void UpdatePlayer(float& elapsedTime);
void Idle(float& elapsedTime);
void Run(float& elapsedTime);
void Jump(float& elapsedTime);
void Fall(float& elapsedTime);
void AirDash(float& elapsedTime);
void Punch(float& elapsedTime);
void Roll(float& elapsedTime);
void WallClimb(float& elapsedTime);
void WallJump(float& elapsedTime);
void Hurt(float& elapsedTime);
void Death(float& elapsedTime);

void HandleObstructions();
void HandleGrounded();
void HandleOnWall();
void HandleHurt();

void UpdatePlayerCamera(float& elapsedTime);

// Air Dashing prototypes 
void ScreenShake(float& elapsedTime);
void DrawParticle(float& elapsedTime);
void AddParticleToEmitter(GameObject& playerObj);
void UpdateParticleLifeTime(float& elapsedTime);

// Draw prototypes
void DrawPlayer();
void DrawPlatform();
void DrawAllCollisionBoxes();

void SetForegrounds();

// Create and Destroy prototypes
void CreatePlayer();
void CreatePlatform();

// Utility prototypes
bool AABBCollisionTest(const Point2D& aPos, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset);
float q_rsqrt(float number);
float exponentialDecay(float A0, float lambda, float time);

void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	Play::LoadBackground("Data\\Backgrounds\\bg.png");
	//Play::StartAudioLoop("theme");
	Play::CentreAllSpriteOrigins();
	SetForegrounds();
	CreatePlatform();
	CreatePlayer();
}

bool MainGameUpdate(float elapsedTime)
{
	Play::ClearDrawingBuffer(Play::cWhite);
	Play::DrawBackground();
	Play::DrawSprite(Play::GetSpriteId("fg1st"), Point2D(0, 0), 0);
	Play::DrawSprite(Play::GetSpriteId("fg2nd"), Point2D(0, 0), 0);
	Play::DrawSprite(Play::GetSpriteId("fg3rd"), Point2D(0, 0), 0);
	Play::DrawSprite(Play::GetSpriteId("fg4th"), Point2D(0, 0), 0);
	Play::DrawSprite(Play::GetSpriteId("fg5th"), Point2D(0, 0), 0);

	UpdatePlayer(elapsedTime);

	//UpdatePlayerCamera(elapsedTime);   //ScreenShake instead
	DrawPlatform();
	DrawPlayer();
	DrawAllCollisionBoxes();
	DrawParticle(elapsedTime);


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
	playerObj.scale = { 3.f };

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
	HandleObstructions();
	HandleOnWall();
	HandleHurt();
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
		(abs(playerObj.velocity.x) > 0.01) ? playerObj.velocity.x *= 0.4 : 0;
	}

	if (gameState.player.isGrounded == false && playerObj.velocity.y > 5)
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
		playerObj.acceleration.x = -gameState.player.runAccel;
		Play::SetSprite(playerObj, "player_run_left", 0.25f);
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		gameState.player.direction = 1;
		Play::SetSprite(playerObj, "player_run", 0.25f);
		playerObj.acceleration.x = gameState.player.runAccel;
	}

	playerObj.velocity.x = std::clamp(playerObj.velocity.x, -gameState.player.runSpeed, gameState.player.runSpeed);

	if (Play::KeyDown('Z'))
	{
		playerObj.acceleration.x = 0;
		gameState.player.state = STATE_JUMP;
		return;
	}
	else if (Play::KeyPressed('X'))
	{
		playerObj.acceleration.x = 0;
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

	if (gameState.player.isGrounded == false && playerObj.velocity.y > 5)
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
		playerObj.velocity.y = -gameState.player.jumpImpulse;

		if (gameState.player.jumpTime < gameState.player.jumpEndTime)
		{
			gameState.player.jumpTime += elapsedTime;
			playerObj.velocity += (gameState.player.gravity * elapsedTime * 1.5f);

		}
	}

	if (!gameState.player.isGrounded)
	{
		gameState.player.hasJumped = true;
	}
	else
	{
		gameState.player.hasJumped = false;
		gameState.player.jumpTime = 0;
	}

	if (Play::KeyDown(VK_LEFT))
		playerObj.velocity.x = -gameState.player.runSpeed;
	else if (Play::KeyDown(VK_RIGHT))
		playerObj.velocity.x = gameState.player.runSpeed;

	playerObj.velocity.x = std::clamp(playerObj.velocity.x, -gameState.player.runSpeed, gameState.player.runSpeed);

	if (Play::KeyPressed('C'))
	{
		gameState.player.state = STATE_AIRDASH;
		return;
	}

	if (gameState.player.isGrounded == true)
	{
		gameState.player.state = STATE_IDLE;
		return;
	}
}

void Fall(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	playerObj.acceleration.x = 0;

	if (gameState.player.isGrounded == false)
	{
		Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_jump_left" : "player_jump", 0);
		playerObj.frame = 2;
	}

	if (Play::KeyDown(VK_LEFT))
		playerObj.pos.x -= gameState.player.runSpeed;
	else if (Play::KeyDown(VK_RIGHT))
		playerObj.pos.x += gameState.player.runSpeed;

	playerObj.velocity.x = std::clamp(playerObj.velocity.x, -gameState.player.runSpeed, gameState.player.runSpeed);


	if (Play::KeyPressed('C'))
	{
		gameState.player.state = STATE_AIRDASH;
		return;
	}

	if (gameState.player.isGrounded == true)
	{
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

	Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_punch_left" : "player_punch", 0.2f);

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

	Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_roll_left" : "player_roll", 0.2f);

	if (Play::IsAnimationComplete(playerObj))
	{
		playerObj.velocity = { 0 , 0 };
		gameState.player.state = STATE_IDLE;
		return;
	}
	else
		playerObj.velocity.x = gameState.player.direction * gameState.player.rollSpeed;
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
			playerObj.velocity.y = -gameState.player.climbUp;

		}
		else if (Play::KeyDown(VK_DOWN))
		{
			Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_wall_slid_left" : "player_wall_slid", 0.2f);
			playerObj.velocity.y += (gameState.player.climbDown * elapsedTime * 2.5f);
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

void HandleObstructions()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	for (Platform& p : gameState.vPlatform)
	{
		if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
		{
			playerObj.pos = playerObj.oldPos;
			playerObj.velocity.x = 0;
			playerObj.acceleration.x = 0;
			return;
		}
	}
}

void HandleGrounded()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	for (Platform& p : gameState.vPlatform)
	{
		if (AABBCollisionTest(playerObj.pos, gameState.player.GroundBox, gameState.player.GroundBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
		{

			int diff = playerObj.pos.y - playerObj.oldPos.y;
			playerObj.pos.y = playerObj.oldPos.y;
			for (int i = 0; i < diff; i++)
			{
				if (AABBCollisionTest(playerObj.oldPos + Vector2D(0, i), gameState.player.GroundBox, gameState.player.GroundBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
				{
					playerObj.pos.y += i;
					break;
				}
			}

			gameState.player.isGrounded = true;
			gameState.player.hasJumped == false;
			gameState.player.hasAirDashed = false;
			playerObj.velocity.y = 0;

			break;
		}
		else
			gameState.player.isGrounded = false;
	}

	if (gameState.player.isGrounded == false || gameState.player.isOnWall == false)
	{
		playerObj.acceleration.y = gameState.player.gravity.y;
		playerObj.velocity.y = std::clamp(playerObj.velocity.y, -gameState.player.terminalVelocity, gameState.player.terminalVelocity);
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
		else if (AABBCollisionTest(playerObj.pos, gameState.player.WallBox, Vector2f(gameState.player.direction, 1) * gameState.player.WallBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
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
		{
			UpdateParticleLifeTime(elapsedTime);
		}
		break;
	}
	default:
	{
		if (!gameState.particleEmitter.vParticle.empty())
		{
			UpdateParticleLifeTime(elapsedTime);
		}
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
	}


}

void UpdateParticleLifeTime(float& elapsedTime)
{
	Particle particle;


	for (int i = 0; i < gameState.particleEmitter.vParticle.size(); ++i)
	{
		gameState.particleEmitter.vParticle[i].currentLifetime += elapsedTime;
		float opacity = exponentialDecay(gameState.particleEmitter.vParticle[i].baseOpacity, gameState.particleEmitter.vParticle[i].decayConstant, gameState.particleEmitter.vParticle[i].currentLifetime);
		Play::DrawSpriteRotated(gameState.particleEmitter.vParticle[i].spriteId, gameState.particleEmitter.vParticle[i].pos, 0, 0, 3.0f, opacity);

		if (opacity < particle.opacityThreshold)
			gameState.particleEmitter.vParticle.erase(gameState.particleEmitter.vParticle.begin() + i);
	}
}

void DrawPlayer()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	Play::DrawObjectRotated(playerObj);
}

void DrawAllCollisionBoxes()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	for (Platform& p : gameState.vPlatform)
	{
		Play::DrawRect(p.pos - p.PlatformBox, p.pos + p.PlatformBox, Play::cMagenta);

		if (gameState.player.direction == -1)
		{
			if (AABBCollisionTest(playerObj.pos, gameState.player.GroundBox, Vector2D(-1, 1) * gameState.player.GroundBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
				Play::DrawRect(playerObj.pos - gameState.player.GroundBox + Vector2D(-1, 1) * gameState.player.GroundBoxOffset, playerObj.pos + gameState.player.GroundBox + Vector2D(-1, 1) * gameState.player.GroundBoxOffset, Play::cRed, true);
			else
				Play::DrawRect(playerObj.pos - gameState.player.GroundBox + Vector2D(-1, 1) * gameState.player.GroundBoxOffset, playerObj.pos + gameState.player.GroundBox + Vector2D(-1, 1) * gameState.player.GroundBoxOffset, Play::cGreen);

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
			if (AABBCollisionTest(playerObj.pos, gameState.player.GroundBox, gameState.player.GroundBoxOffset, p.pos, p.PlatformBox, Vector2D(0, 0)))
				Play::DrawRect(playerObj.pos - gameState.player.GroundBox + gameState.player.GroundBoxOffset, playerObj.pos + gameState.player.GroundBox + gameState.player.GroundBoxOffset, Play::cRed, true);
			else
				Play::DrawRect(playerObj.pos - gameState.player.GroundBox + gameState.player.GroundBoxOffset, playerObj.pos + gameState.player.GroundBox + gameState.player.GroundBoxOffset, Play::cGreen);

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
}

void SetForegrounds()
{
	Play::SetSpriteOrigin("fg1", 0, 0);
	Play::SetSpriteOrigin("fg2", 0, 0);
	Play::SetSpriteOrigin("fg3", 0, 0);
	Play::SetSpriteOrigin("fg4", 0, 0);
	Play::SetSpriteOrigin("fg5", 0, 0);
}

void DrawPlatform()
{
	for (Platform& p : gameState.vPlatform)
	{
		Play::DrawSprite(Play::GetSpriteId("brick"), p.pos, 0);
	}
}

void CreatePlayer()
{
	int id{ Play::CreateGameObject(TYPE_PLAYER, { 1100, 500 }, 0, "player_idle") };
	GameObject& playerObj{ Play::GetGameObject(id) };
}

void CreatePlatform()
{
	Platform platform;

	// Floor
	for (int display_x = 0; display_x < DISPLAY_WIDTH; display_x += PLATFORM_WIDTH)
	{
		gameState.vPlatform.push_back(platform);
		gameState.vPlatform.back().pos = Point2D{ float(display_x), DISPLAY_HEIGHT - 32 };
	}

	// Ceiling
	for (int display_x = 0; display_x < DISPLAY_WIDTH; display_x += PLATFORM_WIDTH)
	{
		gameState.vPlatform.push_back(platform);
		gameState.vPlatform.back().pos = Point2D{ float(display_x), 32 };
	}

	// Left Wall
	for (int display_y = 0; display_y < DISPLAY_HEIGHT; display_y += PLATFORM_WIDTH)
	{
		gameState.vPlatform.push_back(platform);
		gameState.vPlatform.back().pos = Point2D{ 32, float(display_y) };
	}

	// Right Wall
	for (int display_y = 0; display_y < DISPLAY_HEIGHT; display_y += PLATFORM_WIDTH)
	{
		gameState.vPlatform.push_back(platform);
		gameState.vPlatform.back().pos = Point2D{ DISPLAY_WIDTH - 32, float(display_y) };
	}

	// Chimmney
	for (int display_y = 0; display_y < 550; display_y += PLATFORM_WIDTH)
	{
		gameState.vPlatform.push_back(platform);
		gameState.vPlatform.back().pos = Point2D{ 200 - 32, float(display_y) };
	}

}

bool AABBCollisionTest(const Point2D& aPos, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset)
{
	return (aPos.x - aAABB.x + aOffset.x < bPos.x + bAABB.x + bOffset.x
		&& aPos.x + aAABB.x + aOffset.x > bPos.x - bAABB.x + bOffset.x
		&& aPos.y - aAABB.y + aOffset.y < bPos.y + bAABB.y + bOffset.y
		&& aPos.y + aAABB.y + aOffset.y > bPos.y - bAABB.y + bOffset.y);
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

float exponentialDecay(float A0, float lambda, float time)
{
	return A0 * exp(-lambda * time);
}