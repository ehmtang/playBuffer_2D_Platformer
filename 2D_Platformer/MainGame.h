enum GameModes
{
	TEST_MODE = 0,
	PLAY_MODE = 1,
};

enum GameObjectType
{
	TYPE_NULL = -1,
	TYPE_PLAYER,
	TYPE_DESTROYED,
	TYPE_BALLOON,
};

enum PlatformType
{
	EMPT = 0,
	GBRK,
	DBRK,
	BUSH,
	FIRE,
	ICE_,
};

enum Backgrounds
{
	BG_1ST = 0,
	BG_2ND,
	BG_3RD,
	BG_4TH,
	BG_5TH,
	BG_6TH,
	BG_7TH,
	BG_8TH,
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
	Point2D pos{ 0, 0 };
	float opacity{ 0 };
	float currentLifetime{ 0 };
	int spriteId{ 0 };
	int spriteFrame{ 0 };
};

struct ParticleEmitter
{
	std::vector<Particle> vParticle;
	float splitTime{ 0 };
	const float lifetime{ 0.2f };
	const float baseOpacity{ 1.f };
	const float opacityThreshold{ 0.02f };
	const float decayConstant{ 4.0f };
	const float emitPeriod{ 0.05f };
	const int emitParticles{ 1 };
};

struct CameraInfo
{
	Point2D cameraPos{ 0, 0 };
	float shakeTime{ 0 };
	float shakeEndTime{ 0.08f };
};

struct FinishLine
{
	std::vector<float> vSplitTime;
	Point2D pos{ 704, 96 };
	Vector2D box{ 16, 48 };
	float splitTime{ 0.f };
	int completedLap{ 0 };
	bool crossesFinishLine{ false };
	bool hasCompletedLap{ false };
};

struct PlayerAttributes
{
	Vector2D gravity{ 0, 1.f };
	Vector2D airDashDirection{ 0, 0 };
	Vector2D GroundBox{ 4, 1 };				//scale in x
	Vector2D GroundBoxOffset{ 0, 15 };		//scale in y
	Vector2D WallBox{ 1, 7 };				//scale in y
	Vector2D WallBoxOffset{ 7, -3 };		//scale in x and y
	Vector2D HurtBox{ 5, 15 };				//scale in x and y
	Vector2D HurtBoxOffset{ 0, 0 };			//none
	Vector2D PunchBox{ 7, 7 };				//scale in x and y
	Vector2D PunchBoxOffset{ 25, 0 };		//scale in x
	Vector2D collisionDir{ 0, 0 };
	Point2D startingPos{ 768, 96 };
	PlayerState state{ STATE_IDLE };
	float jumpTime{ 0 };
	float jumpEndTime{ 0.1f };
	float coyoteTime{ 0 };
	float airDashTime{ 0 };
	const float sizeScale{ 2.f };
	const float rollImpulse{ 30.f };
	const float jumpImpulse{ 20.f };
	const float wallJumpImpulse{ 30.f };
	const float maxJumpAccel{ 1.f };
	const float obstructedImpulse{ 5.f };
	const float maxClimbUpSpeed{ 1.2f };
	const float maxClimbDownSpeed{ 5.f };
	const float maxRunSpeed{ 5.f };
	const float maxRunAccel{ 5.f };
	const float coyoteTimeThreshold{ 0.8f };
	const float maxFallSpeed{ 25.f };
	const float airDashImpulse{ 30 };
	const float airDashEndTime{ 0.1f };
	int health{ 100 };
	int direction{ -1 };
	bool hasJumped{ false };
	bool isAirDashing{ false };
	bool hasAirDashed{ false };
	bool hasLandedOnWall{ false };
	bool isGrounded{ false };
	bool isOnWall{ false };
	bool isHurt{ false };
};

struct Platform
{
	const Vector2D PlatformBox{ 16, 16 };
	Point2D pos{ 0, 0 };
	int type{ DBRK };
	bool playerOnTop{ false };

	Point2D Left() { return Point2D(pos.x - PlatformBox.x, pos.y); }
	Point2D Right() { return Point2D(pos.x + PlatformBox.x, pos.y); }
	Point2D Top() { return Point2D(pos.x, pos.y - PlatformBox.y); }
	Point2D Bottom() { return Point2D(pos.x, pos.y + PlatformBox.y); }

	Point2D TopLeft() { return pos - PlatformBox; }
	Point2D BottomRight() { return pos + PlatformBox; }
	Point2D TopRight() { return Point2D(pos.x + PlatformBox.x, pos.y - PlatformBox.y); }
	Point2D BottomLeft() { return Point2D(pos.x - PlatformBox.x, pos.y + PlatformBox.y); }
};

struct GameState
{
	std::vector<Platform> vPlatform;
	ParticleEmitter particleEmitter;
	FinishLine finishLine;
	PlayerAttributes player;
	CameraInfo camera;
	Backgrounds bg;
	int gameMode = TEST_MODE;
};

// player controls and states
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
void HandleSizeScale();
float ResolveFriction();

// collisions
void HandleFinishLine(float& elapsedTime);
void HandleObstructed();
void HandleGrounded();
void HandleOnWall();
void HandleHurt();
void BalloonCollision();

// camera 
void UpdatePlayerCamera(float& elapsedTime);
void ScreenShake(float& elapsedTime);

// particle effects
void DrawParticle(float& elapsedTime);
void AddParticleToEmitter(GameObject& playerObj);
void UpdateParticleLifeTime(float& elapsedTime);

// draw
void DrawPlayer();
void DrawPlatform();
void DrawBalloon();
void DrawCollisionBoxes();
void DrawFinishLine();
void DrawUI();


// background 
void HandleBackgrounds();

// create and destroy
void CreatePlayer();
void CreatePlatform();

// utility
float q_rsqrt(float number);
float exponentialDecay(const float& A0, const float& lambda, const float& time);
bool AABBCollisionTest(const Point2D& aPos, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset);
void ApplyReflection(GameObject& aObj, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset);
Vector2D GetNearestEdge(const Point2D& aPos, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset);
void MergeCollisionBox();
int GetPlatformId();
int GetPlatformType();