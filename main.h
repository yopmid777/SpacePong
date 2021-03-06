/* This code is released under the GNU GPL v2 license. */

//SDLpong main_h.h header file
#ifndef SDL_HEADERS
#define SDL_HEADERS
#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#endif

//definitions
#define MAX_SPRITES 512 //enough to handle current sprite effects.

//variable decs

//Engine stuff
typedef struct {
	int frames,update,maxframetime,framestart,framems;
	float frametime;
	float fps;
	} s_frames;
	
enum GAME_STATES {
	STATE_QUITTING,
	STATE_INITIALIZING,
	STATE_MENU,
	STATE_PLAYING
	};

typedef struct {
	enum GAME_STATES state;
	int debug;
	int paused;
	int twoplayer;
	int winner;
	int fullscreen;
	int resx, resy;
	} s_state;
	
enum SPRITE_TYPES {
	SPRITE_IMAGE,
	SPRITE_PIXEL,
	SPRITE_SPARK,
	SPRITE_RECT,
	SPRITE_FILLEDRECT,
	SPRITE_CIRCLE,
	SPRITE_FILLEDCIRCLE
	};
	
typedef struct {
	enum SPRITE_TYPES type;
	SDL_Surface *image;
	float x,y,rad;
	int w,h;
	float xspeed,yspeed;
	unsigned char r,g,b,a;
	int alphafade,faderate;
	int tick,lifespan;
	int enabled;
	} s_sprite;
		
struct {
	float x,y;
	int w,h;
	float xspeed,yspeed;
	SDL_Surface *image;
	SDL_Surface *Backgrounds[99];
	int numimg;
	} Background;
		
struct menu_item {
	char text[128];
	int enabled;
	};
	
typedef struct {
	struct menu_item item[32];
	int enabled;
	int x,y;
	} s_menu;
	
//Game specific stuff
typedef struct {
	int x,y;
	int height, width; //obvi needed for scaling
	int xspeed,yspeed;
	int speed; //default speed value, for scaling
	unsigned char r,g,b,a;
	unsigned char defr,defg,defb,defa;
	int ticks;
	int score;
	} s_paddle;
	
struct {
	int reactdist;
	int tolerance;
	} AI;
	
typedef struct {
	float x,y;
	float xspeed,yspeed;
	float maxspeed; //max speed, this is scaled per resolution
	int size;
	int enabled;
	unsigned char r,g,b,a;
	int movedelay;
	int trails,trailspawnrate;
	} s_ball;
	
struct {
	int paddlehit;
	int wallhit;
	} Samples;
//global vars

//sdl vars
SDL_Surface *screen;
SDL_Surface *textSurface;
SDL_Event SDLevent;
TTF_Font *font; 
Uint8 *SDL_KeyStates;

//engine/game vars
s_frames Frames;
s_state GameState;
s_sprite Sprite[MAX_SPRITES];
s_menu Menu;
s_paddle Paddle[2]; 
s_ball Ball;
int progressbar = 0;

//prototypes
//General Purpose/Engine Functions
int InitSDL(s_state GameState); //set up SDL. Returns 1 on success, 0 on failure.
int InitArgs(int argc, char *argv[]);
void InitMisc(void); //various things that need to be initialized
void InitScales(void); //scale objects in game per resolution
void InitSamples(void);
void DrawText(char text[128], int x, int y); //draws white text with black bkg
void ClearScreen(int r, int g, int b); //clear screen with any color
SDL_Surface *LoadImage(char filename[128]); //load 24bit bmp optimized to 32bit
void SpawnSprite(s_sprite TmpSprite); //spawn a new sprite
void ManageSprites(void); //manage sprite properties and physics
void RenderSprites(void); //renders sprites
void SetGameState(enum GAME_STATES state); //change game state safely
void RegulateFPS(void); //cap framerate
void CalcFPS(void); //calculates framerate and average frametime
int RandInt(int min, int max);
float RandFloat(float min, float max);
int DetectJPGs(char indir[256]);
int UpdateProgressBar(int mode, int param); 
void GameQuit(void); //quit and unload everything

//Menu Functions
void InitMenu(void); //set up menu text and such
void MenuLogic(void); //menu keypresses/etc.
void MenuKeyCheck(void); //check for menu specific keys
void MenuPhysics(void); //bounce the ball around
void MenuRender(void); //render menu

//Game Functions
void GameLoop(void); //main game loop, contains all game logic functions
void GameLogic(void); //game physics/rendering/ai/etc.
void GameKeyCheck(void); //game specific key checking
void GamePhysics(void); //ball physics/paddle bouncing, scoring, etc.
void GameRender(void); //render (game) shit to the screen
void AIThink(void); //AI code
void InitGame(void); //set up game variables and start playing
void ResetBall(void); //reset ball to middle with new velocities
void GoalCheck(void); //check if ball hits either side of screen for score
int EndGameCheck(void); //check if score for either player has reached max; show winning screen
//silly mods?
void GrowPaddles(void); //scale paddles per score

//Game Effect (FX) Functions
void LoadBackgrounds(void); //load all background images into Backgrounds[]
void InitBackground(void); //set up background
void BallSpark(int numsparks); //spawns sparks directionally at balls location
void BallTrail(int lifespan); //draws a fading square at the balls location
void ManageBackground(void); //move bkg
void PaddleEffects(void); //manage effects that aren't sprite related
void Firework(float x, float y, int r, int g, int b, int a, int size); //fireworks, yo

