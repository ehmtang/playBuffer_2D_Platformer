// Acknowledgements:
// Zeggy Games - player character sprite https://zegley.itch.io/2d-platformermetroidvania-asset-pack
// Ninjikin - tile sprites https://ninjikin.itch.io/starter-tiles
// Mix&Jam and Nate Kling - tile sprites https://drive.google.com/file/d/1hNrC1vZqzQ7fjO3Q1qFxWe0PERl8dXDs/view
// CraftPix - background sprites https://free-game-assets.itch.io/free-sky-with-clouds-background-pixel-art-set
// Leopaz - player SFX https://leohpaz.itch.io/90-retro-player-movement-sfx
// JasonTomLee - slime character sprite https://jasontomlee.itch.io/slime-platformer-asset-pack
// Elthen - portal sprite https://elthen.itch.io/2d-pixel-art-portal-sprites
// CazWolf - keyboard sprites https://cazwolf.itch.io/caz-pixel-keyboard
// Purrple Cat - Crescent Moon background theme https://purrplecat.com/
// Grafxkid - speech indicator https://grafxkid.itch.io/mini-fx-items-ui

#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER

#include "Play.h"
#include "MainGame.h"

constexpr int DISPLAY_WIDTH{ 1280 };
constexpr int DISPLAY_HEIGHT{ 720 };
constexpr int DISPLAY_SCALE{ 1 };
constexpr int PLATFORM_WIDTH{ 32 };

const int MAX_ROWS = 23;
const int MAX_COLS = 40;


const int ROOM_0[23][40] =
{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,13,13,13,13,13,13,13,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,17,0,0},
	{ 0,0,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0 },
	{ 0,0,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0 },
	{ 0,0,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0 },
	{ 0,0,13,0,0,0,9,1,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0 },
	{ 0,0,13,0,0,0,7,0,6,0,0,0,21,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,9,1,1,1,1,1,4,0,0 },
	{ 0,0,13,0,0,0,7,0,6,0,0,19,9,1,12,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,10,10,10,10,10,17,0,0 },
	{ 0,0,13,0,0,0,7,0,6,0,0,0,7,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,7,0,0 },
	{ 0,0,13,0,0,0,7,0,6,0,0,0,2,10,5,14,14,14,14,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,7,0,0 },
	{ 0,0,13,0,0,0,7,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,7,0,0 },
	{ 0,0,13,0,0,0,7,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,7,0,0 },
	{ 0,0,13,0,0,0,7,0,6,0,0,0,9,1,1,1,1,1,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,15,7,0,0 },
	{ 0,0,13,0,0,0,7,0,6,0,0,0,7,0,0,0,0,0,6,0,0,14,14,14,14,9,1,1,1,1,1,12,15,0,0,0,15,7,0,0 },
	{ 0,0,13,0,0,0,7,0,6,0,0,0,2,10,10,10,10,10,5,0,0,0,0,0,0,7,0,0,0,0,0,6,15,0,0,0,15,7,0,0 },
	{ 0,0,13,0,0,0,2,10,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,6,15,15,15,15,15,7,0,0 },
	{ 0,0,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,14,14,14,14,7,0,0,0,0,0,11,1,1,1,1,1,4,0,0 },
	{ 0,0,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,13,13,13,13,13,13,13,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

const int ROOM_1[23][40] =
{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,8,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,17,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0 },
	{ 0,0,6,0,0,9,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,0,0 },
	{ 0,0,6,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,2,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,11,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0  },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

const int ROOM_2[23][40] =
{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,8,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,17,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,13,1,1,1,4,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,13,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,13,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,13,13,13,13,13,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,13,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,13,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,13,13,13,13,13,13,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,13,13,13,13,13,13,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,19,13,13,13,13,13,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,19,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,19,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,11,1,1,12,21,21,21,21,21,21,13,13,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,11,1,1,1,1,1,1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

const int ROOM_3[23][40] =
{
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,8,10,10,10,10,10,10,10,10,10,10,10,17,0,0,0,0,0,0,0,0,0,0,8,10,10,10,10,10,10,10,10,10,10,10,17,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,19,7,0,0,0,0,0,0,0,0,0,0,6,20,0,0,0,0,0,0,0,0,0,0,7,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,19,7,0,0,0,0,0,0,0,0,0,0,6,20,0,0,0,0,0,0,0,0,0,0,7,0,0 },
	{ 0,0,6,0,0,0,0,0,0,0,0,0,0,19,7,0,0,0,0,0,0,0,0,0,0,6,20,0,0,0,0,0,0,0,0,0,0,7,0,0 },
	{ 0,0,11,1,1,1,1,12,20,0,0,0,0,19,7,0,0,0,0,0,0,0,0,0,0,6,20,0,0,0,0,19,9,1,1,1,1,4,0,0 },
	{ 0,0,0,0,0,0,0,6,20,0,0,0,0,19,7,0,0,0,0,0,0,0,0,0,0,6,20,0,0,0,0,19,7,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,6,20,0,0,0,0,19,7,0,0,0,0,0,0,0,0,0,0,6,20,0,0,0,0,19,7,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,6,20,0,0,0,0,19,7,0,0,0,0,0,0,0,0,0,0,6,20,0,0,0,0,19,7,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,6,20,0,0,0,0,19,7,0,0,0,0,0,0,0,0,0,0,6,20,0,0,0,0,19,7,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,6,20,0,0,0,0,19,7,0,0,0,0,0,0,0,0,0,0,6,20,0,0,0,0,19,7,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,6,20,0,0,0,0,19,7,0,0,0,0,0,0,0,0,0,0,6,20,0,0,0,0,19,7,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,6,20,0,0,0,0,19,7,0,0,0,0,0,0,0,0,0,0,6,20,0,0,0,0,19,7,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,6,20,0,0,0,0,19,2,10,10,10,10,10,10,10,10,10,10,5,20,0,0,0,0,19,7,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,6,20,0,0,0,0,0,18,18,18,18,18,18,18,18,18,18,18,18,0,0,0,0,0,19,7,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,6,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,7,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,6,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,7,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,6,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,7,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,6,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,19,7,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,6,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,21,7,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,11,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,4,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};

const char* spriteNames[] =
{
	"_empt",
	"_btm_mid",
	"_btm_l_out_cnr",
	"",
	"_btm_r_in_cnr",
	"_btm_r_out_cnr",
	"_l_mid",
	"_r_mid",
	"_top_l_in_cnr",
	"_top_l_out_cnr",
	"_top_mid",
	"_btm_l_in_cnr",
	"_top_r_out_cnr",
	"ice",
	"ledge",
	"fire",
	"_bg_wall",
	"_top_r_in_cnr",
	"spike_down",
	"spike_left",
	"spike_right",
	"spike_up",
};

GameState gameState;

void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	LoadBackground();

	//Play::LoadBackground("Data\\Backgrounds\\platformer_tut_map-export.png");
	Play::StartAudioLoop("Crescent-Moon_snip");
	Play::CentreAllSpriteOrigins();
	HandleSizeScale();
	//CreatePlatform(ROOM_0);
	//MergeCollisionBox();
	CreatePlayer();
	CreateSlime();
	CreatePortal();
}

bool MainGameUpdate(float elapsedTime)
{
	Play::ClearDrawingBuffer(Play::cWhite);
	Play::DrawBackground(gameState.vBg[gameState.level]);
	
	ToggleGameModes();
	LoadLevel();

	UpdatePlayer(elapsedTime);
	UpdateSlime(elapsedTime);
	UpdatePortal();

	HandleAfterImageLifetime(elapsedTime);

	DrawPlatformSprites();
	DrawCollisionBoxes();
	DrawPortal();
	DrawPlayer();
	DrawSlime();
	DrawUI();
	DrawSlimeTalk();

	ApplyWind(elapsedTime);

	Play::PresentDrawingBuffer();

	if (Play::KeyPressed(VK_TAB))
		ResetPlayerPos();

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
	case STATE_DEATH:
	{
		Death(elapsedTime);
		break;
	}
	}

	if (Play::IsLeavingDisplayArea(playerObj))
		playerObj.pos = playerObj.oldPos;

	Play::UpdateGameObject(playerObj);
	HandleDeath();
	HandleGrounded();
	if (gameState.player.state != STATE_DEATH)
	{
		HandleObstructed();
		HandleOnWall();
	}
}

void Idle(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_idle_left" : "player_idle", 0.25f);

	playerObj.velocity.x = std::clamp(playerObj.velocity.x, -gameState.player.maxRunSpeed - playerObj.acceleration.x, gameState.player.maxRunSpeed - playerObj.acceleration.x);

	if (!Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_RIGHT) && gameState.player.isGrounded == true)
	{
		playerObj.acceleration.x = ApplyFriction();
	}
	else if (Play::KeyDown(VK_LEFT) || Play::KeyDown(VK_RIGHT))
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
		Play::SetSprite(playerObj, "player_run_left", 0.25f);
		playerObj.acceleration.x = ApplyFriction();
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		gameState.player.direction = 1;
		Play::SetSprite(playerObj, "player_run", 0.25f);
		playerObj.acceleration.x = ApplyFriction();
	}

	playerObj.velocity.x = std::clamp(playerObj.velocity.x, -gameState.player.maxRunSpeed - playerObj.acceleration.x, gameState.player.maxRunSpeed - playerObj.acceleration.x);

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

	if (Play::KeyDown(VK_LEFT))
		playerObj.velocity.x = -gameState.player.maxRunSpeed;
	else if (Play::KeyDown(VK_RIGHT))
		playerObj.velocity.x = gameState.player.maxRunSpeed;

	playerObj.velocity.x = std::clamp(playerObj.velocity.x, -gameState.player.maxRunSpeed, gameState.player.maxRunSpeed);

	if (Play::KeyDown('Z') && gameState.player.hasJumped == false)
	{
		gameState.player.jumpTime += elapsedTime;
		playerObj.velocity.y = -gameState.player.jumpImpulse;
		if (gameState.player.jumpTime > gameState.player.jumpEndTime)
			gameState.player.hasJumped = true;
	}
	else if (!Play::KeyDown('Z') && gameState.player.hasJumped == false)
		gameState.player.hasJumped = true;


	if (Play::KeyPressed('C'))
	{
		gameState.player.state = STATE_AIRDASH;
		return;
	}

	if (gameState.player.isGrounded == false && playerObj.velocity.y > 0)
	{
		gameState.player.state = STATE_FALL;
		return;
	}
}

void Fall(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	playerObj.acceleration.x = 0;

	if (Play::KeyDown(VK_LEFT))
		playerObj.velocity.x = -gameState.player.maxRunSpeed;
	else if (Play::KeyDown(VK_RIGHT))
		playerObj.velocity.x = gameState.player.maxRunSpeed;

	playerObj.velocity.x = std::clamp(playerObj.velocity.x, -gameState.player.maxRunSpeed, gameState.player.maxRunSpeed);

	gameState.player.coyoteTime += elapsedTime;

	if (Play::KeyDown('Z') && gameState.player.hasJumped == false && gameState.player.coyoteTime < gameState.player.coyoteTimeThreshold)
	{
		gameState.player.coyoteTime = 0;
		gameState.player.state = STATE_JUMP;
		return;
	}

	if (gameState.player.isGrounded == false)
	{
		Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_jump_left" : "player_jump", 0);
		playerObj.frame = 2;
	}

	if (Play::KeyPressed('C'))
	{
		gameState.player.coyoteTime = 0;
		gameState.player.state = STATE_AIRDASH;
		return;
	}

	if (gameState.player.isGrounded == true)
	{
		gameState.player.hasJumped = false;
		gameState.player.jumpTime = 0;
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

	if (gameState.player.hasAirDashed == false)
	{
		gameState.player.hasAirDashed = true;

		playerObj.velocity = Vector2D(0, 0);
		playerObj.acceleration = Vector2D(0, 0);

		if (Play::KeyDown(VK_UP) && !Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_RIGHT))
			gameState.player.airDashDir = Vector2D(0, -1);
		else if (Play::KeyDown(VK_UP) && Play::KeyDown(VK_RIGHT))
			gameState.player.airDashDir = Vector2D(q_rsqrt_2, -q_rsqrt_2);
		else if (Play::KeyDown(VK_RIGHT) && !Play::KeyDown(VK_UP) && !Play::KeyDown(VK_DOWN))
			gameState.player.airDashDir = Vector2D(1, 0);
		else if (Play::KeyDown(VK_DOWN) && Play::KeyDown(VK_RIGHT))
			gameState.player.airDashDir = Vector2D(q_rsqrt_2, q_rsqrt_2);
		else if (Play::KeyDown(VK_DOWN) && !Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_RIGHT))
			gameState.player.airDashDir = Vector2D(0, 1);
		else if (Play::KeyDown(VK_DOWN) && Play::KeyDown(VK_LEFT))
			gameState.player.airDashDir = Vector2D(-q_rsqrt_2, q_rsqrt_2);
		else if (Play::KeyDown(VK_LEFT) && !Play::KeyDown(VK_UP) && !Play::KeyDown(VK_DOWN))
			gameState.player.airDashDir = Vector2D(-1, 0);
		else if (Play::KeyDown(VK_UP) && Play::KeyDown(VK_LEFT))
			gameState.player.airDashDir = Vector2D(-q_rsqrt_2, -q_rsqrt_2);
	}

	if (gameState.player.airDashTime <= gameState.player.airDashEndTime)
	{
		gameState.player.airDashTime += elapsedTime;
		ScreenShake(elapsedTime);
		playerObj.velocity = gameState.player.airDashDir * gameState.player.airDashImpulse;
	}
	else if (gameState.player.isGrounded == true)
	{
		playerObj.velocity = Vector2D(0, 0);
		gameState.player.airDashTime = 0;
		gameState.player.airDashDir = Vector2D(0, 0);
		gameState.player.state = STATE_IDLE;
		return;
	}
	else if (gameState.player.airDashTime > gameState.player.airDashEndTime)
	{
		playerObj.velocity = Vector2D(0, 0);
		gameState.player.airDashTime = 0;
		gameState.player.airDashDir = Vector2D(0, 0);
		gameState.player.state = STATE_JUMP;
		return;
	}
}

void Punch(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_punch_left" : "player_punch", 0.7f);

	playerObj.velocity.x = std::clamp(playerObj.velocity.x, -gameState.player.maxRunSpeed, gameState.player.maxRunSpeed);

	if (Play::IsAnimationComplete(playerObj))
	{
		gameState.player.state = STATE_IDLE;
		return;
	}
}

void Roll(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_roll_left" : "player_roll", 1.f);

	if (Play::IsAnimationComplete(playerObj))
	{
		gameState.player.state = STATE_IDLE;
		return;
	}
	else
	{
		ScreenShake(elapsedTime);
		playerObj.velocity.x = gameState.player.direction * gameState.player.rollImpulse;
	}
}

void WallClimb(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	if (gameState.player.hasLandedOnWall == false && gameState.player.isOnWall == true)
	{
		Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_wall_land_left" : "player_wall_land", 0.f);
		gameState.player.hasLandedOnWall = true;
	}

	if (gameState.player.hasLandedOnWall == true && gameState.player.isOnWall == true)
	{
		playerObj.velocity.x = 0;
		playerObj.acceleration.y = 0;		// apply friction here

		if (Play::KeyDown(VK_UP))
		{
			Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_wall_land_left" : "player_wall_land", 0.2f);
			playerObj.velocity.y = -gameState.player.maxClimbUpSpeed;

		}
		else if (Play::KeyDown(VK_DOWN))
		{
			Play::SetSprite(playerObj, (gameState.player.direction == -1) ? "player_wall_slid_left" : "player_wall_slid", 0.2f);
			playerObj.velocity.y += (gameState.player.maxClimbDownSpeed * elapsedTime * 2.5f);
		}

		playerObj.velocity.y = std::clamp(playerObj.velocity.y, -gameState.player.maxFallSpeed, gameState.player.maxFallSpeed);

		if (Play::KeyPressed('Z'))
		{
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
	gameState.player.hasLandedOnWall = false;
	gameState.player.state = STATE_JUMP;
	return;
}

void Death(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	playerObj.velocity.x = 0;
	playerObj.acceleration.x = 0;
	gameState.player.deathTime += elapsedTime;

	if (gameState.player.hasDied == false)
		Play::SetSprite(playerObj, (gameState.slime.direction == -1) ? "player_death_left" : "player_death", 0.1f);

	if (Play::IsAnimationComplete(playerObj))
	{
		gameState.player.hasDied = true;
		Play::SetSprite(playerObj, "player_death", 0);
		playerObj.frame = 9;
	}

	if (gameState.player.deathTime > gameState.player.deathEndTime)
	{
		gameState.player.deathTime = 0;
		gameState.player.hasDied = false;
		playerObj.pos = gameState.player.startingPos;
		gameState.player.state = STATE_IDLE;
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
	gameState.player.PunchBox *= Vector2D(gameState.player.sizeScale, gameState.player.sizeScale);
	gameState.player.PunchBoxOffset *= Vector2D(gameState.player.sizeScale, 1);
	gameState.player.rollImpulse *= gameState.player.sizeScale;
	gameState.player.jumpImpulse *= gameState.player.sizeScale;
	gameState.player.wallJumpImpulse *= gameState.player.sizeScale;
	gameState.player.maxClimbUpSpeed *= gameState.player.sizeScale;
	gameState.player.maxClimbDownSpeed *= gameState.player.sizeScale;
	gameState.player.maxRunSpeed *= gameState.player.sizeScale;
	gameState.player.maxFallSpeed *= gameState.player.sizeScale;
	gameState.player.airDashImpulse *= gameState.player.sizeScale;

	GameObject& slimeObj{ Play::GetGameObjectByType(TYPE_SLIME) };
	gameState.slime.HurtBox *= Vector2D(gameState.slime.sizeScale, gameState.slime.sizeScale);
	gameState.slime.HurtBoxOffset *= Vector2D(1, gameState.slime.sizeScale);

	GameObject& portalObj{ Play::GetGameObjectByType(TYPE_PORTAL) };
	gameState.portal.box *= Vector2D(gameState.portal.sizeScale, gameState.portal.sizeScale);
}

float ApplyFriction()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	int dir = gameState.player.direction;
	float accel_x;

	switch (GetPlatformType())
	{
	default:
	{
		accel_x = dir * gameState.platformAttr.defaultAccel;

		if (gameState.player.state == STATE_IDLE)
		{
			if (playerObj.velocity.x > gameState.platformAttr.frictionThreshold)
				accel_x = -gameState.platformAttr.defaultAccel;
			else if (playerObj.velocity.x < gameState.platformAttr.frictionThreshold)
				accel_x = gameState.platformAttr.defaultAccel;

			if (playerObj.velocity.x >= -gameState.platformAttr.frictionThreshold && playerObj.velocity.x <= gameState.platformAttr.frictionThreshold)
			{
				accel_x = 0;
				playerObj.velocity.x = 0;
			}
		}
		break;
	}
	case fire:
	{
		accel_x = dir * gameState.platformAttr.defaultAccel;
		playerObj.velocity.y = -gameState.player.jumpImpulse;
		gameState.player.hasJumped = true;
		gameState.player.state = STATE_JUMP;
		break;
	}
	case ice:
	{
		accel_x = dir * gameState.platformAttr.iceAccel;

		if (gameState.player.state == STATE_IDLE)
		{
			if (playerObj.velocity.x > gameState.platformAttr.frictionThreshold)
				accel_x = -gameState.platformAttr.iceAccel;
			else if (playerObj.velocity.x < -gameState.platformAttr.frictionThreshold)
				accel_x = gameState.platformAttr.iceAccel;

			if (playerObj.velocity.x >= -gameState.platformAttr.frictionThreshold && playerObj.velocity.x <= gameState.platformAttr.frictionThreshold)
			{
				accel_x = 0;
				playerObj.velocity.x = 0;
			}
		}
		break;
	}
	}
	return accel_x;
}

Vector2D CalculateAcceleration()
{
	// NOTE: not implemented in game yet.
	// requires resolving the frictional algorithm to work with this function
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	Vector2D totalAccel = playerObj.acceleration + gameState.petalEmitter.windForce + gameState.gravity;
	return totalAccel;
}

void HandleDeath()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	for (Platform& p : gameState.vPlatform)
	{
		if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
			&& (p.type == spike_up || p.type == spike_down || p.type == spike_left || p.type == spike_right))
			gameState.player.state = STATE_DEATH;
	}
}

void UpdateSlime(float& elapsedTime)
{
	GameObject& slimeObj{ Play::GetGameObjectByType(TYPE_SLIME) };
	slimeObj.scale = gameState.slime.sizeScale;

	switch (gameState.slime.state)
	{
	case SLIME_IDLE:
	{
		SlimeIdle(elapsedTime);
		break;
	}
	case SLIME_WALK:
	{
		SlimeWalk(elapsedTime);
		break;
	}
	case SLIME_TURN:
	{
		SlimeTurn(elapsedTime);
		break;
	}
	}

	Play::UpdateGameObject(slimeObj);
	SlimeGrounded();
	SlimeTalk();
}

void SlimeIdle(float& elapsedTime)
{
	GameObject& slimeObj{ Play::GetGameObjectByType(TYPE_SLIME) };
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	Play::SetSprite(slimeObj, (gameState.slime.direction == -1) ? "slime_idle_left" : "slime_idle", 0.25f);

	gameState.slime.idleTime += elapsedTime;

	if (AABBCollisionTest({ slimeObj.pos.x + gameState.slime.direction * PLATFORM_WIDTH / 2, slimeObj.pos.y }, gameState.slime.HurtBox, gameState.slime.HurtBoxOffset, playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset))
	{
		gameState.slime.idleTime = 0;
		return;
	}

	if (gameState.slime.idleTime > gameState.slime.idleLimit)
	{
		gameState.slime.idleTime = 0;
		gameState.slime.state = SLIME_WALK;
		return;
	}

}

void SlimeWalk(float& elapsedTime)
{
	GameObject& slimeObj{ Play::GetGameObjectByType(TYPE_SLIME) };

	Play::SetSprite(slimeObj, (gameState.slime.direction == -1) ? "slime_walk_left" : "slime_walk", 0.25f);

	float newPosX = slimeObj.pos.x + gameState.slime.direction * gameState.slime.maxWalkSpeed;

	bool willWalkOffEdge = true;

	for (Platform& p : gameState.vPlatform)
	{
		if (AABBCollisionTest({ slimeObj.pos.x + gameState.slime.direction * PLATFORM_WIDTH, slimeObj.pos.y }, gameState.slime.HurtBox, gameState.slime.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0)))
		{
			willWalkOffEdge = false;
			break;
		}
	}

	if (willWalkOffEdge)
	{
		gameState.slime.state = SLIME_TURN;
		return;
	}

	for (Platform& p : gameState.vPlatform)
	{
		if (AABBCollisionTest(slimeObj.pos + Vector2D(gameState.slime.direction * gameState.slime.maxWalkSpeed, 0), gameState.slime.HurtBox, gameState.slime.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
			&& GetNearestEdge(slimeObj.pos + Vector2D(gameState.slime.direction * gameState.slime.maxWalkSpeed, 0), gameState.slime.HurtBox, gameState.slime.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0)) == Vector2D(-gameState.slime.direction, 0))
		{
			gameState.slime.state = SLIME_TURN;
			return;
		}
	}
	slimeObj.pos.x = newPosX;
}

void SlimeTurn(float& elapsedTime)
{
	GameObject& slimeObj{ Play::GetGameObjectByType(TYPE_SLIME) };

	Play::SetSprite(slimeObj, (gameState.slime.direction == -1) ? "slime_walk_turn_left" : "slime_walk_turn", 0.1f);
	if (Play::IsAnimationComplete)
	{
		gameState.slime.direction *= -1;
		gameState.slime.state = SLIME_IDLE;
		return;
	}
}

void SlimeGrounded()
{
	GameObject& slimeObj{ Play::GetGameObjectByType(TYPE_SLIME) };

	for (Platform& p : gameState.vPlatform)
	{
		if (AABBCollisionTest(slimeObj.pos, gameState.slime.HurtBox, gameState.slime.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0)))
		{
			int diff = abs(slimeObj.pos.y - slimeObj.oldPos.y);
			slimeObj.pos.y = slimeObj.oldPos.y;
			for (int i = 0; i < diff; i++)
			{
				if (AABBCollisionTest(slimeObj.oldPos + Vector2D(0, i), gameState.slime.HurtBox, gameState.slime.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
					&& GetNearestEdge(slimeObj.oldPos + Vector2D(0, i), gameState.slime.HurtBox, gameState.slime.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0)) == Vector2D(0, -1))
				{
					slimeObj.pos.y += i;
					break;
				}
			}
			gameState.slime.isGrounded = true;
			slimeObj.velocity.y = 0;
			slimeObj.acceleration.y = 0;
			break;
		}
		else
			gameState.slime.isGrounded = false;
	}

	if (gameState.slime.isGrounded == false)
		slimeObj.acceleration.y = gameState.gravity.y;
}

void SlimeTalk()
{
	GameObject& slimeObj{ Play::GetGameObjectByType(TYPE_SLIME) };
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	if (AABBCollisionTest(slimeObj.pos, gameState.slime.TalkBox, Vector2D(gameState.slime.direction, 1) * gameState.slime.HurtBoxOffset, playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset))
		SlimeTalkIcon();
}

void SlimeTalkIcon()
{
	GameObject& slimeObj{ Play::GetGameObjectByType(TYPE_SLIME) };

	Play::DrawSpriteRotated("key_x", slimeObj.pos + Point2D(0, -20), 0, 0, 0.5f, 1);

	if (Play::KeyPressed('X'))
		(gameState.slime.hasTalked == true) ? gameState.slime.hasTalked = false : gameState.slime.hasTalked = true;
}

void DrawSlimeTalk()
{
	if (gameState.slime.hasTalked == true)
	{
		Play::DrawFontText("64px", "Use the arrow keys to move. 'Z' to jump. 'X' to punch. 'C' to roll.", Point2D(37, DISPLAY_HEIGHT - 111), Play::LEFT);
		Play::DrawFontText("64px", "To Air Dash, jump and press 'C' with arrow keys.", Point2D(37, DISPLAY_HEIGHT - 74), Play::LEFT);
		Play::DrawFontText("64px", "When you're ready. Enter the portal!", Point2D(37, DISPLAY_HEIGHT - 37), Play::LEFT);
	}
}

void UpdatePortal()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	GameObject& portalObj{ Play::GetGameObjectByType(TYPE_PORTAL) };

	portalObj.scale = gameState.portal.sizeScale;

	switch (gameState.portal.state)
	{
	case(PORTAL_OPENING):
	{
		Play::SetSprite(portalObj, "portal_open", 0.2f);

		if (Play::IsAnimationComplete(portalObj) && portalObj.spriteId == Play::GetSpriteId("portal_open"))
			gameState.portal.state = PORTAL_IDLE;

		break;
	}
	case(PORTAL_IDLE):
	{
		Play::SetSprite(portalObj, "portal", 0.2f);
		break;
	}
	case(PORTAL_CLOSING):
	{
		if (Play::IsAnimationComplete(portalObj) && portalObj.spriteId == Play::GetSpriteId("portal_close"))
		{
			Play::SetSprite(portalObj, "portal_close", 0);
			portalObj.frame = 7;
			ChangeLevel();
		}
		else
			Play::SetSprite(portalObj, "portal_close", 0.2f);
		break;
	}
	}

	if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, portalObj.pos, gameState.portal.box, Vector2D(0, 0)))
	{
		gameState.portal.crossesPortal = true;
		gameState.portal.state = PORTAL_CLOSING;
	}

	Play::UpdateGameObject(portalObj);
}

void HandleObstructed()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	for (Platform& p : gameState.vPlatform)
	{
		if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
			&& GetNearestEdge(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0)) == Vector2D(0, 1))
		{
			if (p.type == ledge)
				break;

			int diff = abs(playerObj.pos.y - playerObj.oldPos.y);
			playerObj.pos.y = playerObj.oldPos.y;
			for (int i = 0; i < diff; ++i)
			{
				if (AABBCollisionTest(playerObj.oldPos + Vector2D(0, -i), gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0)))
				{
					playerObj.pos.y -= i;
					break;
				}
			}
			ApplyReflection(playerObj, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0));
		}

		else if (AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
			&& GetNearestEdge(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0)) == Vector2D(-1, 0)
			|| AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
			&& GetNearestEdge(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0)) == Vector2D(1, 0))
		{
			int diff = playerObj.pos.x - playerObj.oldPos.x;
			playerObj.pos.x = playerObj.oldPos.x;
			for (int i = 0; i < diff; ++i)
			{
				if (AABBCollisionTest(playerObj.oldPos + Vector2D(0, i), gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0)))
				{
					playerObj.pos.x += i;
					break;
				}
			}
			playerObj.pos.x = playerObj.oldPos.x;
			playerObj.velocity.x = 0;
		}
	}
}

void HandleGrounded()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	for (Platform& p : gameState.vPlatform)
	{
		if (AABBCollisionTest(playerObj.pos, gameState.player.GroundBox, gameState.player.GroundBoxOffset, p.pos, p.pBox, Vector2D(0, 0)))
		{
			if (p.type == ledge && playerObj.velocity.y < 0)
				break;

			int diff = abs(playerObj.pos.y - playerObj.oldPos.y);
			playerObj.pos.y = playerObj.oldPos.y;
			for (int i = 0; i < diff; i++)
			{
				if (AABBCollisionTest(playerObj.oldPos + Vector2D(0, i), gameState.player.GroundBox, gameState.player.GroundBoxOffset, p.pos, p.pBox, Vector2D(0, 0)))
				{
					playerObj.pos.y += i;
					break;
				}
			}
			p.playerOnTop = true;
			gameState.player.isGrounded = true;
			gameState.player.hasJumped = false;
			gameState.player.hasAirDashed = false;
			playerObj.velocity.y = 0;
			playerObj.acceleration.y = 0;
			break;
		}
		else
		{
			p.playerOnTop = false;
			gameState.player.isGrounded = false;
		}
	}

	if (gameState.player.isGrounded == false || gameState.player.isOnWall == false)
	{
		playerObj.acceleration.y = gameState.gravity.y;
		playerObj.velocity.y = std::clamp(playerObj.velocity.y, -gameState.player.maxFallSpeed, gameState.player.maxFallSpeed);
	}
}

void HandleOnWall()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	for (Platform& p : gameState.vPlatform)
	{
		bool unclimbable =
			(
				p.type != _btm_mid &&
				p.type != _top_mid &&
				p.type != ledge &&
				p.type != fire &&
				p.type != spike_up &&
				p.type != spike_down &&
				p.type != spike_left &&
				p.type != spike_right
				);

		if (gameState.player.state == STATE_WALLJUMP)
		{
			gameState.player.isOnWall = false;
			return;
		}

		if (AABBCollisionTest(playerObj.pos, gameState.player.WallBox, Vector2f(gameState.player.direction, 1) * gameState.player.WallBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
			&& unclimbable)
		{
			gameState.player.isOnWall = true;
			gameState.player.hasJumped = false;
			gameState.player.state = STATE_WALLCLIMB;
			return;
		}
		else
			gameState.player.isOnWall = false;

	}
}

void ScreenShake(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	gameState.camera.shakeTime += elapsedTime;

	if (gameState.camera.shakeTime <= gameState.camera.shakeEndTime)
	{
		Point2f randomPos = { Play::RandomRollRange(-3, 3), Play::RandomRollRange(-3, 3) };
		Play::SetCameraPosition(randomPos);
	}
	else if (gameState.camera.shakeTime > gameState.camera.shakeEndTime)
	{
		Play::SetCameraPosition(Point2f(0, 0));
		gameState.camera.shakeTime = 0;
	}
}

void HandleAfterImageLifetime(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	switch (gameState.player.state)
	{
	case STATE_AIRDASH:
	{
		gameState.afterImageEmitter.splitTime += elapsedTime;

		if (gameState.afterImageEmitter.splitTime > gameState.afterImageEmitter.emitPeriod)
		{
			AddAfterImageToEmitter(playerObj);
			gameState.afterImageEmitter.splitTime = 0;
		}

		if (!gameState.afterImageEmitter.vAfterImage.empty())
			DrawAfterImage(elapsedTime);

		break;
	}
	case STATE_ROLL:
	{
		gameState.afterImageEmitter.splitTime += elapsedTime;

		if (gameState.afterImageEmitter.splitTime > gameState.afterImageEmitter.emitPeriod)
		{
			AddAfterImageToEmitter(playerObj);
			gameState.afterImageEmitter.splitTime = 0;
		}

		if (!gameState.afterImageEmitter.vAfterImage.empty())
		{
			DrawAfterImage(elapsedTime);
		}
		break;
	}
	default:
	{
		gameState.afterImageEmitter.splitTime = 0;
		if (!gameState.afterImageEmitter.vAfterImage.empty())
			DrawAfterImage(elapsedTime);

		break;
	}
	}
}

void AddAfterImageToEmitter(GameObject& playerObj)
{
	AfterImage afterImage;

	for (int i = 0; i < gameState.afterImageEmitter.emitParticles; ++i)
	{
		afterImage.pos = playerObj.pos;
		afterImage.spriteId = playerObj.spriteId;
		afterImage.spriteFrame = playerObj.frame;
		gameState.afterImageEmitter.vAfterImage.push_back(afterImage);
	}
}

void DrawAfterImage(float& elapsedTime)
{
	for (int i = 0; i < gameState.afterImageEmitter.vAfterImage.size(); ++i)
	{
		gameState.afterImageEmitter.vAfterImage[i].currentLifetime += elapsedTime;
		gameState.afterImageEmitter.vAfterImage[i].opacity = exponentialDecay(gameState.afterImageEmitter.baseOpacity, gameState.afterImageEmitter.decayConstant, gameState.afterImageEmitter.vAfterImage[i].currentLifetime);
		Play::DrawSpriteRotated(gameState.afterImageEmitter.vAfterImage[i].spriteId, gameState.afterImageEmitter.vAfterImage[i].pos, gameState.afterImageEmitter.vAfterImage[i].spriteFrame, 0, gameState.player.sizeScale, gameState.afterImageEmitter.vAfterImage[i].opacity);

		if (gameState.afterImageEmitter.vAfterImage[i].opacity < gameState.afterImageEmitter.opacityThreshold)
			gameState.afterImageEmitter.vAfterImage.erase(gameState.afterImageEmitter.vAfterImage.begin() + i);
	}
}

void ApplyWind(float& elapsedTime)
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };

	gameState.petalEmitter.windTime += elapsedTime;

	if (gameState.petalEmitter.windTime <= gameState.petalEmitter.windEndTime
		&& gameState.petalEmitter.onBreak == false)
	{

		if (gameState.player.state != STATE_DEATH)
			playerObj.velocity += gameState.petalEmitter.windDir * gameState.petalEmitter.windForce;

		HandlePetalLifetime(elapsedTime);
	}
	else if (gameState.petalEmitter.windTime > gameState.petalEmitter.windEndTime
		&& gameState.petalEmitter.onBreak == false)
	{
		gameState.petalEmitter.applyAccel = false;
		gameState.petalEmitter.windDir *= -1;
		gameState.petalEmitter.windTime = 0;
		gameState.petalEmitter.onBreak = true;
	}

	if (gameState.petalEmitter.windTime > gameState.petalEmitter.breakTime
		&& gameState.petalEmitter.onBreak == true)
	{
		gameState.petalEmitter.windTime = 0;
		gameState.petalEmitter.onBreak = false;
	}
}

void HandleLevelChange()
{

}

void HandlePetalLifetime(float& elapsedTime)
{
	gameState.petalEmitter.splitTime += elapsedTime;

	if (gameState.petalEmitter.splitTime > gameState.petalEmitter.emitPeriod)
	{
		AddPetalToEmitter();
		gameState.petalEmitter.splitTime = 0;
	}

	if (!gameState.petalEmitter.vPetal.empty())
	{
		DrawPetal(elapsedTime);
	}
}

void AddPetalToEmitter()
{
	Petal petal;

	int petalSpriteId = (gameState.petalEmitter.windDir == -1) ? Play::GetSpriteId("petal_left") : Play::GetSpriteId("petal");

	for (int i = 0; i < gameState.petalEmitter.emitParticles; ++i)
	{
		petal.pos = Point2D(Play::RandomRollRange(-128, DISPLAY_WIDTH + 128), Play::RandomRollRange(-128, DISPLAY_HEIGHT + 128));
		petal.spriteId = petalSpriteId;
		gameState.petalEmitter.vPetal.push_back(petal);
	}
}

void DrawPetal(float& elapsedTime)
{
	float phase = 0;

	for (int i = 0; i < gameState.petalEmitter.vPetal.size(); ++i)
	{
		gameState.petalEmitter.vPetal[i].pos.x += gameState.petalEmitter.windDir * gameState.petalEmitter.petalSpeed;
		gameState.petalEmitter.vPetal[i].pos.y += gameState.petalEmitter.amplitude * sin((PLAY_PI * gameState.petalEmitter.frequency) + phase);
		gameState.petalEmitter.vPetal[i].currentLifetime += elapsedTime;
		phase += 0.1f;

		gameState.petalEmitter.vPetal[i].opacity = exponentialDecay(gameState.petalEmitter.baseOpacity, gameState.petalEmitter.decayConstant, gameState.petalEmitter.vPetal[i].currentLifetime);
		Play::DrawSpriteRotated(gameState.petalEmitter.vPetal[i].spriteId, gameState.petalEmitter.vPetal[i].pos, 0, 0, 1, gameState.petalEmitter.vPetal[i].opacity);

		if (gameState.petalEmitter.vPetal[i].currentLifetime > gameState.petalEmitter.windEndTime)
			gameState.petalEmitter.vPetal.erase(gameState.petalEmitter.vPetal.begin() + i);
	}
}

void DrawPlayer()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	Play::DrawObjectRotated(playerObj);
}

void DrawCollisionBoxes()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	GameObject& slimeObj{ Play::GetGameObjectByType(TYPE_SLIME) };
	GameObject& portalObj{ Play::GetGameObjectByType(TYPE_PORTAL) };

	switch (gameState.gameMode)
	{
	case(PLAY_MODE):
	{
		break;
	}
	default:
	{
		Play::DrawRect(portalObj.pos - gameState.portal.box, portalObj.pos + gameState.portal.box, Play::cGreen);

		if (gameState.slime.direction == -1)
			Play::DrawRect(slimeObj.pos - gameState.slime.HurtBox + Vector2D(-1, 1) * gameState.slime.HurtBoxOffset, slimeObj.pos + gameState.slime.HurtBox + Vector2D(-1, 1) * gameState.slime.HurtBoxOffset, Play::cOrange);
		else if (gameState.slime.direction == 1)
			Play::DrawRect(slimeObj.pos - gameState.slime.HurtBox + gameState.slime.HurtBoxOffset, slimeObj.pos + gameState.slime.HurtBox + gameState.slime.HurtBoxOffset, Play::cOrange);

		for (Platform& p : gameState.vPlatform)
		{
			(AABBCollisionTest(playerObj.pos, gameState.player.GroundBox, gameState.player.GroundBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
				? Play::DrawRect(p.pos - p.pBox, p.pos + p.pBox, Play::cRed, true)
				: Play::DrawRect(p.pos - p.pBox, p.pos + p.pBox, Play::cGreen));

			if (gameState.player.direction == -1)
			{
				(AABBCollisionTest(playerObj.pos, gameState.player.GroundBox, Vector2D(-1, 1) * gameState.player.GroundBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
					? Play::DrawRect(playerObj.pos - gameState.player.GroundBox + Vector2D(-1, 1) * gameState.player.GroundBoxOffset, playerObj.pos + gameState.player.GroundBox + Vector2D(-1, 1) * gameState.player.GroundBoxOffset, Play::cRed, true)
					: Play::DrawRect(playerObj.pos - gameState.player.GroundBox + Vector2D(-1, 1) * gameState.player.GroundBoxOffset, playerObj.pos + gameState.player.GroundBox + Vector2D(-1, 1) * gameState.player.GroundBoxOffset, Play::cGreen));

				(AABBCollisionTest(playerObj.pos, gameState.player.WallBox, Vector2D(-1, 1) * gameState.player.WallBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
					? Play::DrawRect(playerObj.pos - gameState.player.WallBox + Vector2D(-1, 1) * gameState.player.WallBoxOffset, playerObj.pos + gameState.player.WallBox + Vector2D(-1, 1) * gameState.player.WallBoxOffset, Play::cRed, true)
					: Play::DrawRect(playerObj.pos - gameState.player.WallBox + Vector2D(-1, 1) * gameState.player.WallBoxOffset, playerObj.pos + gameState.player.WallBox + Vector2D(-1, 1) * gameState.player.WallBoxOffset, Play::cYellow));

				(AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, Vector2D(-1, 1) * gameState.player.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
					? Play::DrawRect(playerObj.pos - gameState.player.HurtBox + Vector2D(-1, 1) * gameState.player.HurtBoxOffset, playerObj.pos + gameState.player.HurtBox + Vector2D(-1, 1) * gameState.player.HurtBoxOffset, Play::cRed, true)
					: Play::DrawRect(playerObj.pos - gameState.player.HurtBox + Vector2D(-1, 1) * gameState.player.HurtBoxOffset, playerObj.pos + gameState.player.HurtBox + Vector2D(-1, 1) * gameState.player.HurtBoxOffset, Play::cCyan));

				(AABBCollisionTest(playerObj.pos, gameState.player.PunchBox, Vector2D(-1, 1) * gameState.player.PunchBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
					? Play::DrawRect(playerObj.pos - gameState.player.PunchBox + Vector2D(-1, 1) * gameState.player.PunchBoxOffset, playerObj.pos + gameState.player.PunchBox + Vector2D(-1, 1) * gameState.player.PunchBoxOffset, Play::cRed, true)
					: Play::DrawRect(playerObj.pos - gameState.player.PunchBox + Vector2D(-1, 1) * gameState.player.PunchBoxOffset, playerObj.pos + gameState.player.PunchBox + Vector2D(-1, 1) * gameState.player.PunchBoxOffset, Play::cMagenta));
			}
			else if (gameState.player.direction == 1)
			{
				(AABBCollisionTest(playerObj.pos, gameState.player.GroundBox, gameState.player.GroundBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
					? Play::DrawRect(playerObj.pos - gameState.player.GroundBox + gameState.player.GroundBoxOffset, playerObj.pos + gameState.player.GroundBox + gameState.player.GroundBoxOffset, Play::cRed, true)
					: Play::DrawRect(playerObj.pos - gameState.player.GroundBox + gameState.player.GroundBoxOffset, playerObj.pos + gameState.player.GroundBox + gameState.player.GroundBoxOffset, Play::cGreen));

				(AABBCollisionTest(playerObj.pos, gameState.player.WallBox, gameState.player.WallBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
					? Play::DrawRect(playerObj.pos - gameState.player.WallBox + gameState.player.WallBoxOffset, playerObj.pos + gameState.player.WallBox + gameState.player.WallBoxOffset, Play::cRed, true)
					: Play::DrawRect(playerObj.pos - gameState.player.WallBox + gameState.player.WallBoxOffset, playerObj.pos + gameState.player.WallBox + gameState.player.WallBoxOffset, Play::cYellow));

				(AABBCollisionTest(playerObj.pos, gameState.player.HurtBox, gameState.player.HurtBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
					? Play::DrawRect(playerObj.pos - gameState.player.HurtBox + gameState.player.HurtBoxOffset, playerObj.pos + gameState.player.HurtBox + gameState.player.HurtBoxOffset, Play::cRed, true)
					: Play::DrawRect(playerObj.pos - gameState.player.HurtBox + gameState.player.HurtBoxOffset, playerObj.pos + gameState.player.HurtBox + gameState.player.HurtBoxOffset, Play::cCyan));

				(AABBCollisionTest(playerObj.pos, gameState.player.PunchBox, gameState.player.PunchBoxOffset, p.pos, p.pBox, Vector2D(0, 0))
					? Play::DrawRect(playerObj.pos - gameState.player.PunchBox + gameState.player.PunchBoxOffset, playerObj.pos + gameState.player.PunchBox + gameState.player.PunchBoxOffset, Play::cRed, true)
					: Play::DrawRect(playerObj.pos - gameState.player.PunchBox + gameState.player.PunchBoxOffset, playerObj.pos + gameState.player.PunchBox + gameState.player.PunchBoxOffset, Play::cMagenta));
			}
		}
		break;
	}
	}
}

void DrawSlime()
{
	GameObject& slimeObj{ Play::GetGameObjectByType(TYPE_SLIME) };
	Play::DrawObjectRotated(slimeObj);
}

void DrawPlatformSprites()
{
	for (Platform& p : gameState.vPlatform)
	{
		int nPlatform = (p.Right().x - p.Left().x) / PLATFORM_WIDTH;
		for (int i = 0; i < nPlatform; ++i)
		{
			int spritePosX = (i * PLATFORM_WIDTH) + p.Left().x + PLATFORM_WIDTH / 2;
			Point2D spritePos = { spritePosX, p.pos.y };
			Play::DrawSprite(Play::GetSpriteId(spriteNames[p.type]), spritePos, 0);
		}
	}
}


void DrawPortal()
{
	GameObject& portalObj{ Play::GetGameObjectByType(TYPE_PORTAL) };
	Play::DrawObjectRotated(portalObj);
}

void DrawUI()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	GameObject& slimeObj{ Play::GetGameObjectByType(TYPE_SLIME) };

	switch (gameState.gameMode)
	{
	case(TEST_MODE_OBJ):
	{
		Play::DrawFontText("64px", "TEST MODE obj - TAB to switch MODE & reset player pos", Point2D(37, 32), Play::LEFT);
		Play::DrawFontText("64px", "PLAYER POS: (" + std::to_string(playerObj.pos.x) + ',' + ' ' + std::to_string(playerObj.pos.y) + ')', Point2D(37, 69), Play::LEFT);
		Play::DrawFontText("64px", "PLAYER VEL: (" + std::to_string(playerObj.velocity.x) + ',' + ' ' + std::to_string(playerObj.velocity.y) + ')', Point2D(37, 106), Play::LEFT);
		Play::DrawFontText("64px", "PLAYER ACC: (" + std::to_string(playerObj.acceleration.x) + ',' + ' ' + std::to_string(playerObj.acceleration.y) + ')', Point2D(37, 143), Play::LEFT);
		Play::DrawFontText("64px", "SLIME POS: (" + std::to_string(slimeObj.pos.x) + ',' + ' ' + std::to_string(slimeObj.pos.y) + ')', Point2D(37, 180), Play::LEFT);
		Play::DrawFontText("64px", "SLIME VEL: (" + std::to_string(slimeObj.velocity.x) + ',' + ' ' + std::to_string(slimeObj.velocity.y) + ')', Point2D(37, 217), Play::LEFT);
		Play::DrawFontText("64px", "SLIME ACC: (" + std::to_string(slimeObj.acceleration.x) + ',' + ' ' + std::to_string(slimeObj.acceleration.y) + ')', Point2D(37, 254), Play::LEFT);
		DrawButtons();
		break;
	}
	case(TEST_MODE_BOOL):
	{
		Play::DrawFontText("64px", "TEST MODE bool - TAB to switch MODE & reset player pos", Point2D(37, 32), Play::LEFT);
		Play::DrawFontText("64px", "STATE: " + std::to_string(gameState.player.state), Point2D(37, 69), Play::LEFT);
		Play::DrawFontText("64px", "HAS JUMPED: " + std::to_string(gameState.player.hasJumped), Point2D(37, 106), Play::LEFT);
		Play::DrawFontText("64px", "HAS AIR DASHED: " + std::to_string(gameState.player.hasAirDashed), Point2D(37, 143), Play::LEFT);
		Play::DrawFontText("64px", "HAS LANDED ON WALL: " + std::to_string(gameState.player.hasLandedOnWall), Point2D(37, 180), Play::LEFT);
		Play::DrawFontText("64px", "IS GROUNDED: " + std::to_string(gameState.player.isGrounded), Point2D(37, 217), Play::LEFT);
		Play::DrawFontText("64px", "PLATFORM ON: " + std::to_string(GetPlatformId()), Point2D(37, 254), Play::LEFT);
		Play::DrawFontText("64px", "PLATFORM TYPE: " + std::to_string(GetPlatformType()), Point2D(37, 291), Play::LEFT);
		DrawButtons();
		break;
	}
	case(TEST_MODE_TIME):
	{
		Play::DrawFontText("64px", "TEST MODE time - TAB to switch MODE & reset player pos", Point2D(37, 32), Play::LEFT);
		Play::DrawFontText("64px", "JUMP TIMER: " + std::to_string(gameState.player.jumpTime), Point2D(37, 69), Play::LEFT);
		Play::DrawFontText("64px", "AIR DASH TIMER: " + std::to_string(gameState.player.airDashTime), Point2D(37, 106), Play::LEFT);
		Play::DrawFontText("64px", "COYOTE TIMER: " + std::to_string(gameState.player.coyoteTime), Point2D(37, 143), Play::LEFT);
		Play::DrawFontText("64px", "PARTICLE SPLIT TIMER: " + std::to_string(gameState.afterImageEmitter.splitTime), Point2D(37, 180), Play::LEFT);
		Play::DrawFontText("64px", "SCREEN SHAKE TIMER: " + std::to_string(gameState.camera.shakeTime), Point2D(37, 217), Play::LEFT);
		DrawButtons();
		break;
	}
	case(PLAY_MODE):
	{
		Play::DrawFontText("64px", "LEVEL: " + std::to_string(gameState.level), Point2D(37, 37), Play::LEFT);
		break;
	}
	}
}

void DrawButtons()
{
	(Play::KeyDown('Z') ? Play::DrawSpriteRotated("key_z_pressed", Point2D(64, DISPLAY_HEIGHT - 27), 0, 0, 1, 1) : Play::DrawSpriteRotated("key_z", Point2D(64, DISPLAY_HEIGHT - 27), 0, 0, 1, 1));
	(Play::KeyDown('X') ? Play::DrawSpriteRotated("key_x_pressed", Point2D(96, DISPLAY_HEIGHT - 27), 0, 0, 1, 1) : Play::DrawSpriteRotated("key_x", Point2D(96, DISPLAY_HEIGHT - 27), 0, 0, 1, 1));
	(Play::KeyDown('C') ? Play::DrawSpriteRotated("key_c_pressed", Point2D(128, DISPLAY_HEIGHT - 27), 0, 0, 1, 1) : Play::DrawSpriteRotated("key_c", Point2D(128, DISPLAY_HEIGHT - 27), 0, 0, 1, 1));
	(Play::KeyDown(VK_LEFT) ? Play::DrawSpriteRotated("key_left_pressed", Point2D(192, DISPLAY_HEIGHT - 27), 0, 0, 1, 1) : Play::DrawSpriteRotated("key_left", Point2D(192, DISPLAY_HEIGHT - 27), 0, 0, 1, 1));
	(Play::KeyDown(VK_UP) ? Play::DrawSpriteRotated("key_up_pressed", Point2D(224, DISPLAY_HEIGHT - 27), 0, 0, 1, 1) : Play::DrawSpriteRotated("key_up", Point2D(224, DISPLAY_HEIGHT - 27), 0, 0, 1, 1));
	(Play::KeyDown(VK_RIGHT) ? Play::DrawSpriteRotated("key_right_pressed", Point2D(256, DISPLAY_HEIGHT - 27), 0, 0, 1, 1) : Play::DrawSpriteRotated("key_right", Point2D(256, DISPLAY_HEIGHT - 27), 0, 0, 1, 1));
	(Play::KeyDown(VK_DOWN) ? Play::DrawSpriteRotated("key_down_pressed", Point2D(288, DISPLAY_HEIGHT - 27), 0, 0, 1, 1) : Play::DrawSpriteRotated("key_down", Point2D(288, DISPLAY_HEIGHT - 27), 0, 0, 1, 1));
}

void LoadBackground()
{
	gameState.vBg.push_back(Play::LoadBackground("Data\\Backgrounds\\platformer_tut_map-export.png"));
	gameState.vBg.push_back(Play::LoadBackground("Data\\Backgrounds\\platformer_first_map-export.png"));
	gameState.vBg.push_back(Play::LoadBackground("Data\\Backgrounds\\platformer_second_map-export.png"));
	gameState.vBg.push_back(Play::LoadBackground("Data\\Backgrounds\\platformer_third_map-export.png"));
}

void LoadLevel()
{
	if (gameState.isLevelCreated == false)
	{
		if (gameState.level == 0)
			CreatePlatform(ROOM_0);
		else if (gameState.level == 1)
			CreatePlatform(ROOM_1);
		else if (gameState.level == 2)
			CreatePlatform(ROOM_2);
		else if (gameState.level == 3)
			CreatePlatform(ROOM_3);

		MergeCollisionBox();
		gameState.isLevelCreated = true;
	}
}

void ChangeLevel()
{
	gameState.vPlatform.clear();
	gameState.roomBGLoaded = false;
	gameState.isLevelCreated = false;
	gameState.portal.state = PORTAL_OPENING;
	gameState.level += 1;

	// change starting positions
}

void CreatePlayer()
{
	Play::CreateGameObject(TYPE_PLAYER, gameState.player.startingPos, 0, "player_idle");
}

void CreatePlatform(const int room[][MAX_COLS])
{
	Platform platform;

	int total = MAX_ROWS * MAX_COLS;
	int nColumn = MAX_COLS;
	int nRow = total / nColumn;

	int gap = PLATFORM_WIDTH / 2;

	for (int row = 0; row < nRow; ++row)
	{
		for (int col = 0; col < nColumn; ++col)
		{
			int value = room[row][col];

			if (room[row][col] == _empt)
				continue;
			else
				platform.type = room[row][col];

			platform.pos = Point2D(gap + (col * PLATFORM_WIDTH), gap + (row * PLATFORM_WIDTH));
			gameState.vPlatform.push_back(platform);
		}
	}
}

void CreateSlime()
{
	Play::CreateGameObject(TYPE_SLIME, gameState.slime.startingPos, 0, "slime_idle");
}

void CreatePortal()
{
	Play::CreateGameObject(TYPE_PORTAL, gameState.portal.startingPos, 0, "portal");
}

void ResetPlayerPos()
{
	GameObject& playerObj{ Play::GetGameObjectByType(TYPE_PLAYER) };
	playerObj.pos = gameState.player.startingPos;
	playerObj.velocity = Vector2D(0, 0);
	playerObj.acceleration = Vector2D(0, 0);
}

float q_rsqrt(float number)
{
	// Quake3 inverse root algorithm
	long i;
	float x2, y;
	const float threehalfs = 1.5F;
	x2 = number * 0.5F;
	y = number;
	i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;
	y = y * (threehalfs - (x2 * y * y));
	return y;
}

float exponentialDecay(const float& A0, const float& lambda, const float& time)
{
	return A0 * exp(-lambda * time);
}

bool AABBCollisionTest(const Point2D& aPos, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset)
{
	return (aPos.x - aAABB.x + aOffset.x < bPos.x + bAABB.x + bOffset.x
		&& aPos.x + aAABB.x + aOffset.x > bPos.x - bAABB.x + bOffset.x
		&& aPos.y - aAABB.y + aOffset.y < bPos.y + bAABB.y + bOffset.y
		&& aPos.y + aAABB.y + aOffset.y > bPos.y - bAABB.y + bOffset.y);
}

Vector2D GetNearestEdge(const Point2D& aPos, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset)
{
	float left = abs((aPos.x + aAABB.x + aOffset.x) - (bPos.x - bAABB.x + bOffset.x));
	float right = abs((aPos.x - aAABB.x + aOffset.x) - (bPos.x + bAABB.x + bOffset.x));
	float top = abs((aPos.y + aAABB.y + aOffset.y) - (bPos.y - bAABB.y + bOffset.y));
	float bottom = abs((aPos.y - aAABB.y + aOffset.y) - (bPos.y + bAABB.y + bOffset.y));

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

void ApplyReflection(GameObject& aObj, const Vector2D& aAABB, const Vector2D& aOffset, const Point2D& bPos, const Vector2D& bAABB, const Vector2D& bOffset)
{
	Vector2D collisionEdge = GetNearestEdge(aObj.pos, aAABB, aOffset, bPos, bAABB, bOffset);
	Vector2D surfaceNormal = collisionEdge.Perpendicular();
	float dotProduct = aObj.velocity.Dot(surfaceNormal);
	Vector2D reflectionVector = aObj.velocity - (2.0 * dotProduct * surfaceNormal);
	reflectionVector.Normalize();
	aObj.velocity = -reflectionVector * gameState.player.obstructedImpulse;
}

void MergeCollisionBox()
{
	for (int i = 0; i < gameState.vPlatform.size() - 1; ++i)
	{
		Platform& currentPlatform = gameState.vPlatform[i];
		Platform& nextPlatform = gameState.vPlatform[i + 1];

		while (currentPlatform.Right().x == nextPlatform.Left().x && currentPlatform.type == nextPlatform.type && currentPlatform.pos.y == nextPlatform.pos.y)
		{
			currentPlatform.pos.x += nextPlatform.pBox.x;;
			currentPlatform.pBox.x += nextPlatform.pBox.x;
			gameState.vPlatform.erase(gameState.vPlatform.begin() + i + 1);
		}
	}
}

int GetPlatformId()
{
	for (int i = 0; i < gameState.vPlatform.size(); ++i)
	{
		if (gameState.vPlatform[i].playerOnTop == true)
			return i;
	}
}

int GetPlatformType()
{
	for (int i = 0; i < gameState.vPlatform.size(); ++i)
	{
		if (gameState.vPlatform[i].playerOnTop == true)
			return gameState.vPlatform[i].type;
	}
}

void ToggleGameModes()
{
	if (Play::KeyPressed(VK_TAB))
	{
		gameState.gameMode += 1;
		if (gameState.gameMode == END)
			gameState.gameMode = TEST_MODE_OBJ;
	}
}