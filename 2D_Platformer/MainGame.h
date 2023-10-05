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
	_empt = 0,
	_btm_l_in_cnr = 12,
	_btm_l_out_cnr = 2,
	_btm_mid = 1,
	_btm_r_in_cnr = 4,
	_btm_r_out_cnr = 5,
	_l_mid = 6,
	_r_mid = 7,
	_top_l_in_cnr = 8,
	_top_l_out_cnr = 9,
	_top_mid = 10,
	_top_r_in_cnr = 11,
	_top_r_out_cnr = 13,
	fire = 16,
	ice = 14,
	ledge = 15,
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

struct Petal
{
	Point2D pos{ 0, 0 };
	float opacity{ 0 };
	float currentLifetime{ 0 };
	int spriteId{ 0 };
	int spriteFrame{ 0 };
};

struct PetalEmitter
{
	std::vector<Petal> vPetal;
	float splitTime{ 0 };
	const float lifetime{ 0.2f };
	const float baseOpacity{ 1.f };
	const float opacityThreshold{ 0.02f };
	const float decayConstant{ 4.0f };
	const float emitPeriod{ 0.02f };
	const int emitParticles{ 1 };
};

struct AfterImage
{
	Point2D pos{ 0, 0 };
	float opacity{ 0 };
	float currentLifetime{ 0 };
	int spriteId{ 0 };
	int spriteFrame{ 0 };
};

struct AfterImageEmitter
{
	std::vector<AfterImage> vAfterImage;
	float splitTime{ 0 };
	const float lifetime{ 0.2f };
	const float baseOpacity{ 1.f };
	const float opacityThreshold{ 0.02f };
	const float decayConstant{ 4.0f };
	const float emitPeriod{ 0.02f };
	const int emitParticles{ 1 };
};

struct ScreenShakeInfo
{
	Point2D cameraPos{ 0, 0 };
	float shakeTime{ 0 };
	float shakeEndTime{ 0.05f };
};

struct Audio
{
	float audioTimer{ 0 };
	bool audioPlayed{ false };
};

struct FinishLine
{
	std::vector<float> vSplitTime;
	Point2D pos{ 720, 120 };
	Vector2D box{ 16, 48 };
	float splitTime{ 0.f };
	int completedLap{ 0 };
	bool crossesPortal{ false };
	bool hasCompletedLap{ false };
};

struct PlayerAttributes
{
	Vector2D gravity{ 0, 1.f };
	Vector2D airDashDir{ 0, 0 };
	Vector2D GroundBox{ 4, 1 };				//scale with size in x
	Vector2D GroundBoxOffset{ 0, 15 };		//scale with size in y
	Vector2D WallBox{ 1, 7 };				//scale with size in y
	Vector2D WallBoxOffset{ 7, -3 };		//scale with size in x and y
	Vector2D HurtBox{ 5, 15 };				//scale with size in x and y
	Vector2D HurtBoxOffset{ 0, 0 };			
	Vector2D PunchBox{ 7, 7 };				//scale with size in x and y
	Vector2D PunchBoxOffset{ 25, 0 };		//scale with size in x
	Vector2D collisionDir{ 0, 0 };
	Point2D startingPos{ 600, 300 };
	PlayerState state{ STATE_IDLE };
	float jumpTime{ 0 };
	float jumpEndTime{ 0.1f };
	float coyoteTime{ 0 };
	float airDashTime{ 0 };
	float rollImpulse{ 12.f };				//scaled with size
	float jumpImpulse{ 12.f };				//scaled with size
	float wallJumpImpulse{ 15.f };			//scaled with size
	float maxClimbUpSpeed{ 1.f };			//scaled with size
	float maxClimbDownSpeed{ 3.f };			//scaled with size
	float maxRunSpeed{ 2.f };				//scaled with size
	float maxFallSpeed{ 8.f };				//scaled with size
	float airDashImpulse{ 15 };				//scaled with size
	const float sizeScale{ 1.5f };
	const float maxJumpAccel{ 1.f };
	const float obstructedImpulse{ 5.f };
	const float coyoteTimeThreshold{ 0.8f };
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
	Vector2D pBox{ 16, 16 };
	Point2D pos{ 0, 0 };
	Point2D Left() { return Point2D(pos.x - pBox.x, pos.y); };
	Point2D Right() { return Point2D(pos.x + pBox.x, pos.y); };
	Point2D Top() { return Point2D(pos.x, pos.y - pBox.y); };
	Point2D Bottom() { return Point2D(pos.x, pos.y + pBox.y); };
	Point2D TopLeft() { return pos - pBox; };
	Point2D BottomRight() { return pos + pBox; };
	Point2D TopRight() { return Point2D(pos.x + pBox.x, pos.y - pBox.y); };
	Point2D BottomLeft() { return Point2D(pos.x - pBox.x, pos.y + pBox.y); };
	int type{ 0 };
	bool playerOnTop{ false };
};

struct PlatformAttributes
{
	float frictionThreshold{ 0.1f };
	float defaultAccel{ 1.f };
	float iceAccel{ 0.05f };
};

struct GameState
{
	std::vector<Platform> vPlatform;
	PetalEmitter petalEmitter;
	AfterImageEmitter afterImageEmitter;
	FinishLine portal;
	PlayerAttributes player;
	PlatformAttributes platformAttr;
	ScreenShakeInfo camera;
	Audio audio;
	Backgrounds bg;
	int gameMode = TEST_MODE;
};

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

void HandlePortal(float& elapsedTime);
void HandleObstructed();
void HandleGrounded();
void HandleOnWall();
void HandleHurt();

void HandleAudio(float& elapsedTime);

void ScreenShake(float& elapsedTime);

void DrawAfterImage(float& elapsedTime);
void AddAfterImageToEmitter(GameObject& playerObj);
void UpdateAfterImageLifeTime(float& elapsedTime);

void DrawPlayer();
void DrawPlatformSprites();
void DrawCollisionBoxes();
void DrawPortal();
void DrawUI();

void HandleBackgrounds();

void CreatePlayer();
void CreatePlatform();

void ResetGame();

float q_rsqrt(float number);
float exponentialDecay(const float& A0, const float& lambda, const float& time);
bool AABBCollisionTest(const Point2D& aPos, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset);
void ApplyReflection(GameObject& aObj, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset);
void MergeCollisionBox();
int GetPlatformId();
int GetPlatformType();