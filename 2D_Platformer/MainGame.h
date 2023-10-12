enum GameModes
{
	TEST_MODE_OBJ = 0,
	TEST_MODE_BOOL,
	TEST_MODE_TIME,
	PLAY_MODE,
	END,
};

enum GameObjectType
{
	TYPE_NULL = -1,
	TYPE_PLAYER,
	TYPE_SLIME,
	TYPE_PORTAL,
	TYPE_DESTROYED,
};

enum PlatformType
{
	_empt = 0,
	_btm_mid,
	_btm_l_out_cnr,
	_unused,
	_btm_r_in_cnr,
	_btm_r_out_cnr,
	_l_mid,
	_r_mid,
	_top_l_in_cnr,
	_top_l_out_cnr,
	_top_mid,
	_btm_l_in_cnr,
	_top_r_out_cnr,
	ice,
	ledge,
	fire,
	_bg_wall,
	_top_r_in_cnr,
	spike_down,
	spike_left,
	spike_right,
	spike_up,
};

enum Backgrounds
{
	BG_0 = 0,
	BG_1,
	BG_2,
	BG_3,
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
	STATE_DEATH,
};

enum SlimeState
{
	SLIME_IDLE = 0,
	SLIME_WALK,
	SLIME_TURN,
	SLIME_TALK,
};

enum PortalState
{
	PORTAL_OPENING = 0,
	PORTAL_IDLE,
	PORTAL_CLOSING,
};

struct Petal
{
	Point2D pos{ 0, 0 };
	float currentLifetime{ 0 };
	float opacity{ 1.f };
	int spriteId{ 0 };
	int spriteFrame{ 0 };
};

struct PetalEmitter
{
	std::vector<Petal> vPetal;
	const Vector2D windForce{ 1.5f, 0 };
	float splitTime{ 0 };
	float windTime{ 0 };
	const float baseOpacity{ 1.f };
	const float decayConstant{ 0.75f };
	const float emitPeriod{ 0.3f };
	const float windEndTime{ 2.f };
	const float breakTime{ 8.f };
	int windDir{ 1 };
	const int petalSpeed{ 5 };
	const int amplitude{ 1 };
	const int frequency{ 2 };
	const int emitParticles{ 5 };
	bool applyAccel{ false };
	bool onBreak{ true };
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

struct PortalAttributes
{
	std::vector<float> vSplitTime;
	std::vector<Point2D> vStartingPos{ { 1120, 155 }, {1120, 155}, {1120, 155}, {1120, 155} };
	Vector2D box{ 8, 26 };
	PortalState state{ PORTAL_OPENING };
	float sizeScale{ 1.5f };
	float splitTime{ 0.f };
	bool crossesPortal{ false };
};

struct PlayerAttributes
{
	std::vector<Point2D> vStartingPos{ { 416, 384 }, { 640, 640 }, { 160, 640 }, { 160, 160 } };
	Vector2D airDashDir{ 0, 0 };
	Vector2D GroundBox{ 4, 1 };				//scale with size in x
	Vector2D GroundBoxOffset{ 0, 15 };		//scale with size in y
	Vector2D WallBox{ 1, 7 };				//scale with size in y
	Vector2D WallBoxOffset{ 7, -3 };		//scale with size in x and y
	Vector2D HurtBox{ 5, 15 };				//scale with size in x and y
	Vector2D HurtBoxOffset{ 0, 0 };
	Vector2D PunchBox{ 7, 7 };				//scale with size in x and y
	Vector2D PunchBoxOffset{ 25, 0 };		//scale with size in x
	PlayerState state{ STATE_IDLE };
	float deathTime{ 0 };
	float jumpTime{ 0 };
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
	const float deathEndTime{ 3.f };
	const float jumpEndTime{ 0.1f };
	const float sizeScale{ 1.5f };
	const float maxJumpAccel{ 1.f };
	const float obstructedImpulse{ 5.f };
	const float coyoteTimeThreshold{ 0.8f };
	const float airDashEndTime{ 0.1f };
	int direction{ -1 };
	bool hasJumped{ false };
	bool isAirDashing{ false };
	bool hasAirDashed{ false };
	bool hasLandedOnWall{ false };
	bool isGrounded{ false };
	bool isOnWall{ false };
	bool hasDied{ false };
};

struct SlimeAttributes
{
	Vector2D HurtBox{ 16, 12 };				//scale with size in x and y
	Vector2D TalkBox{ 32, 12 };				//scale with size in x and y
	Vector2D HurtBoxOffset{ 4, 1 };
	Point2D startingPos{ 500, 384 };
	SlimeState state{ SLIME_IDLE };
	float maxWalkSpeed{ 2.f };				//scaled with size
	float sizeScale{ 1.f };
	float idleTime{ 0 };
	int direction{ -1 };
	const float idleLimit{ 3.f };
	bool isHurt{ false };
	bool isGrounded{ false };
	bool hasTalked{ false };
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
	std::vector<int> vBg;
	PetalEmitter petalEmitter;
	AfterImageEmitter afterImageEmitter;
	PortalAttributes portalAttr;
	PlayerAttributes playerAttr;
	SlimeAttributes slimeAttr;
	PlatformAttributes platformAttr;
	ScreenShakeInfo camera;
	Vector2D gravity{ 0, 1.f };
	int gameMode = TEST_MODE_OBJ;
	int level{ 0 };
	bool roomBGLoaded{ false };
	bool isLevelCreated{ false };
};

// player
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
void Death(float& elapsedTime);
void HandleSizeScale();
float ApplyFriction();
Vector2D CalculateAcceleration();

// slime
void UpdateSlime(float& elapsedTime);
void SlimeIdle(float& elapsedTime);
void SlimeWalk(float& elapsedTime);
void SlimeTurn(float& elapsedTime);
void SlimeGrounded();
void SlimeTalk();
void SlimeTalkIcon();
void DrawSlimeTalk();

// portal
void UpdatePortal();

// coin
void UpdateCoin();

// collisions
void HandleDeath();
void HandleObstructed();
void HandleGrounded();
void HandleOnWall();

// environment and effects
void ScreenShake(float& elapsedTime);
void HandleAfterImageLifetime(float& elapsedTime);
void AddAfterImageToEmitter(GameObject& playerObj);
void DrawAfterImage(float& elapsedTime);
void ApplyWind(float& elapsedTime);
void HandlePetalLifetime(float& elapsedTime);
void AddPetalToEmitter();
void DrawPetal(float& elapsedTime);
void HandleLevelChange();

// draw
void DrawPlayer();
void DrawPlatformSprites();
void DrawCollisionBoxes();
void DrawSlime();
void DrawCoin();
void DrawPortal();
void DrawUI();
void DrawButtons();

// background and level
void LoadBackground();
void LoadLevel();
void ChangeLevel();


// create
void CreatePlayer();
void CreatePlatform(const int room[][40]);
void CreateSlime();
void CreatePortal();
void CreateCoin();

// utility
void ResetPlayerPos();
float q_rsqrt(float number);
float exponentialDecay(const float& A0, const float& lambda, const float& time);
bool AABBCollisionTest(const Point2D& aPos, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset);
Vector2D GetNearestEdge(const Point2D& aPos, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset);
void ApplyReflection(GameObject& aObj, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset);
void MergeCollisionBox();
int GetPlatformId();
int GetPlatformType();
void ToggleGameModes();