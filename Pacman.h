#pragma once
#define TILE_SIZE 32
#define MAX_ELEMENTS 560

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif
#endif

// Just need to include main header file
#include "S2D/S2D.h"
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <list>

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

enum Direction {
	Up = 0,
	Down,
	Left,
	Right,
	STILL
};

enum Walls {
	topLefttCornerWall = 0,
	btmLeftCornerWall,
	topRightCornerWall,
	btmRightCornerWall,
	verticalWall,
	horizontalWall,
	HorRightEdgeWall,
	HorLeftEdgeWall,
	vertBtmEdgeWall,
	vertTopEdgeWall,
	leftSingleEdge,
	topSingleEdge,
	bottomSingleEdge,
	rightSingleEdge
};

struct Player {
	// Data to represent a player
	float _cSpeed = .15;
	Vector2* startPos;
	Vector2* _Position;
	Rect* _SourceRect;
	Texture2D* _Texture;
	int _moveMouth;
	Direction currentDir, nextDir;
	bool canTurn;
};

struct Collectable {
	//data for collectables
	Vector2* _Position;
	Rect* _SrcRect;
	Texture2D* _Texture;
	int _rand;
	bool spawn;
};

struct Menu {
	Texture2D* _menuBackground;
	Rect* _menuRectangle;
	Vector2* _menuStringPosition;
	bool _menu;
	bool _keyDown;
};

struct StartScreenMenu {
	Texture2D* _background;
	Rect* _rect;
	Rect* selector;
	bool _upKeyDown;
	bool _downKeyDown;
	bool _active;
	bool _selectKeyDown;
};

struct Wall {
	//data to represent border
	Vector2* _Position;
	Rect* _SrcRect;
	Texture2D* _Texture;
};

// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
class Pacman : public Game
{
private:
	void LoadGhosts();

	void Input(int elapsedTime, Input::KeyboardState* state);

	void CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey);

	void CheckViewPortCollision();

	void UpdatePacman(int elapsedTime);

	void UpdateMunchie(int elapsedTime);

	void StartGame(Input::KeyboardState* state, Input::Keys enter);

	void UpdateCherry(int elapsedTime);
	
	void UpdatePowerUp(int elapsedTime);

	bool collisionCheck(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2);

	int ScoreBoard();

	void CheckIfCanTurn(Direction current, Direction _next);

	Vector2 GetPacmanGridPosition();

	bool CheckLevelComplete();

	void StartNewLevel();

	void UpdateMenu(Input::KeyboardState* state);

	void MovePointerDown(Input::KeyboardState* state, Input::Keys downArrow);

	void MovePointerUp(Input::KeyboardState* state, Input::Keys upArrow);

	void ShowContollsMenu(Input::KeyboardState* state, Input::Keys enter);

	void ExitGame(Input::KeyboardState* state, Input::Keys enter);

	void Move(Player* ghost, int elapsedTime);

	void UpdateGhosts(int elapsedTime);

	void ChooseRandomDirection(Player* ghost);

	void ChasePacman();

	void PredictPacmanPath();

	bool _dead = false;
	bool _complete = false;
	int munchiesCollected;
	int _frameCount;
	int _time;
	int _maxMunchie;
	int _maxPowerUp;
	int _maxWall;
	int score;

	Texture2D* _inkyTexture;
	Texture2D* _pinkyTexture;
	Texture2D* _blinkyTexture;
	Texture2D* _clideTexture;

	Texture2D* _munchieTexture;
	Texture2D* _powerUpTexture;
	Texture2D* _wallTexture;
	// Position for String
	Vector2* _stringPosition;
	Vector2* _scorePosition;

	Player* _pacman;
	Player* _ghosts[4];
	Collectable* _munchie[MAX_ELEMENTS];
	Collectable* _cherry;
	Collectable* _powerUp[MAX_ELEMENTS];
	Menu* _pause;
	StartScreenMenu* _startScreen;
	Wall* _wall[MAX_ELEMENTS];
	int** mMap;
public:
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	int GetTileAt(unsigned int h, unsigned int w);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);
};