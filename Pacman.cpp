#include "Pacman.h"
#include <fstream>
#include <cstdlib>

#define MAP_HEIGHT 28
#define MAP_WIDTH 20 

//2d array for map
int _level[28][20] = {
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{6, 7, 7, 7, 7, 7, 7, 7, 7,14, 7, 7, 7, 7, 7, 7, 7, 7, 4, 0},
{8, 2, 1, 1, 1, 1, 1, 1, 1, 8, 1, 1, 1, 1, 1, 1, 1, 2, 8, 0},
{8, 1, 6, 4, 1, 6,14 ,4, 1, 8, 1, 6,14, 4, 1, 6, 4, 1, 8, 0},
{8, 1, 5, 3, 1, 5,15, 3, 1, 8, 1, 5,15, 3, 1, 5, 3, 1, 8, 0},
{8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8 ,0},
{8, 1, 9,10, 1,11, 1, 9, 7,14 ,7,10, 1,11 ,1, 9,10 ,1 ,8 ,0},
{8 ,1 ,1 ,1 ,1 ,8 ,1 ,1 ,1 ,8 ,1 ,1 ,1 ,8 ,1 ,1 ,1 ,1 ,8 ,0},
{13,7 ,7 ,4 ,1 ,13,7,10 ,1,12, 1, 9, 7,16 ,1 ,6 ,7, 7,16 ,0},
{8 ,0 ,0 ,8 ,1 ,8 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,8 ,1 ,8 ,0 ,0 ,8 ,0},
{5 ,7 ,7 ,3 ,1,12 ,1 ,6 ,14,20,14,4 ,1,12 ,1 ,5 ,7 ,7,15 ,7},
{1, 1 ,1 ,1 ,1 ,1 ,1 ,5 ,15,15,15,3 ,1, 1 ,1 ,1 ,1 ,1 ,1 ,1},
{6,14,14 ,4 ,1,11 ,1 ,1 ,1 ,1 ,1 ,1 ,1,11 ,1 ,6,14,14,14 ,7},
{13,15,15,3 ,1,12 ,1 ,9 ,7 ,14,7,10, 1,12 ,1 ,5,15,15,16, 0},
{8, 1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,8 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,8 ,0},
{8, 1 ,9 ,4 ,1 ,9 ,7,10 ,1,12 ,1,9 ,7 ,10 ,1 ,6,10 ,1 ,8 ,0},
{8, 1 ,1 ,8 ,1 ,1 ,1 ,1 ,1 ,17,1 ,1 ,1 ,1 ,1 ,8 ,1 ,1 ,8 ,0},
{13,10,1,12 ,1,11 ,1 ,9 ,7 ,14 ,7,10,1,11 ,1,12 ,1 ,9,16 ,0},
{8, 2 ,1 ,1 ,1 ,8 ,1 ,1 ,1 ,8 ,1 ,1 ,1 ,8 ,1 ,1 ,1 ,2 ,8 ,0},
{8, 1 ,9 ,7 ,7,15 ,7,10 ,1,12 ,1 ,9 ,7 ,15,7 ,7,10 ,1 ,8 ,0},
{8, 1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,1 ,8 ,0},
{5, 7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,7 ,3 ,0},
{0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0},
{0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0},
{0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0},
{0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0},
{0, 0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0}
};

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv)
{
	mMap = new int* [MAP_HEIGHT];

	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		mMap[i] = new int[MAP_WIDTH];
	}

	//populate the map array
	for (unsigned int i = 0; i < MAP_HEIGHT; i++)
	{
		for (unsigned int j = 0; j < MAP_WIDTH; j++)
		{
			mMap[i][j] = _level[i][j];
		}
	}

	_frameCount = 0;
	_time = 0;
	_maxMunchie = 0;
	_maxPowerUp = 0;
	_maxWall = 0;
	score = 0;

	_pause = new Menu();
	_pause->_menu = false;
	_pause->_keyDown = false;

	_startScreen = new StartScreenMenu();
	_startScreen->selector = new Rect(550, 265, 50, 30);
	_startScreen->_active = true;
	_startScreen->_downKeyDown = false;
	_startScreen->_upKeyDown = false;
	_startScreen->_selectKeyDown = false;

	_munchieTexture = new Texture2D();
	_powerUpTexture = new Texture2D();
	_wallTexture = new Texture2D();

	for(int i = 0; i < MAX_ELEMENTS; i++){
		//setup munchies
		_munchie[i] = new Collectable();
		_munchie[i]->_Texture = new Texture2D();
		_munchie[i]->_Texture = _munchieTexture;
		_munchie[i]->_SrcRect = new Rect(0.0f, 0.0f, 12, 12);
		_munchie[i]->_Position = new Vector2();
		_munchie[i]->spawn = true;
		//setup walls
		_wall[i] = new Wall();
		_wall[i]->_Texture = new Texture2D();
		_wall[i]->_Texture = _wallTexture;
		_wall[i]->_SrcRect = new Rect(0.0f, 0.0f, 32, 32);
		_wall[i]->_Position = new Vector2();

		//setup powerups
		_powerUp[i] = new Collectable();
		_powerUp[i]->_Texture = new Texture2D();
		_powerUp[i]->_Texture = _powerUpTexture;
		_powerUp[i]->_SrcRect = new Rect(0.0f, 0.0f, 32, 32);
		_powerUp[i]->_Position = new Vector2();
		_powerUp[i]->spawn = true;
	}

	for (int i = 0; i < 4; i++)
	{
		_ghosts[i] = new Player();
		_ghosts[i]->_Texture = new Texture2D();
		_ghosts[i]->_Texture = _ghosts[i]->_Texture;
		_ghosts[i]->_Position = new Vector2();
		_ghosts[i]->_SourceRect = new Rect(0.0f, 0.0f, 32, 32);
		_ghosts[i]->currentDir = Direction::STILL;
		_ghosts[i]->nextDir = Direction::STILL;
	}
	_ghosts[0]->startPos = new Vector2(32, 96);
	_ghosts[1]->startPos = new Vector2(544, 96);
	_ghosts[2]->startPos = new Vector2(32, 672);
	_ghosts[3]->startPos = new Vector2(544, 672);

	_pacman = new Player;
	_pacman->_Texture = new Texture2D();
	_pacman->_Texture = _pacman->_Texture;
	_pacman->_Position = new Vector2();
	_pacman->_SourceRect = new Rect(0.0f, 0.0f, 32, 32);
	_pacman->_moveMouth = 0;
	_pacman->currentDir = Direction::STILL;
	_pacman->nextDir = Direction::STILL;
	_pacman->startPos = new Vector2(288, 544);

	_cherry = new Collectable();
	_cherry->_Texture = new Texture2D();
	_cherry->_Texture = _cherry->_Texture;
	_cherry->_SrcRect = new Rect(0.0f, 0.0f, 32, 32);
	_cherry->_Position = new Vector2();
	_cherry->spawn = false;

	// Set string position
	_stringPosition = new Vector2(10.0f, 25.0f);
	_scorePosition = new Vector2(700.0f, 25.0f);
	//Initialise important Game aspects
  	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25);
	Input::Initialise();
	// Start the Game Loop - This calls Update and Draw in game 	
	Graphics::StartGameLoop();
}

Pacman::~Pacman()
{
	delete _pacman->_Texture;
	delete _pacman->_SourceRect;
	delete _pacman->_Position;
	delete _pacman;

	for (int i = 0; i < _maxMunchie; i++) {
		delete _munchie[i]->_Texture;
		delete _munchie[i]->_SrcRect;
		delete _munchie[i]->_Position;
		delete _munchie[i];
	}

	for (int i = 0; i < _maxWall; i++) {
		delete _wall[i]->_Texture;
		delete _wall[i]->_SrcRect;
		delete _wall[i]->_Position;
		delete _wall[i];
	}

	delete _cherry->_Position;
	delete _cherry->_SrcRect;
	delete _cherry->_Texture;
	delete _cherry;

	for (int i = 0; i < _maxPowerUp; i++)
	{
		delete _powerUp[i]->_Position;
		delete _powerUp[i]->_SrcRect;
		delete _powerUp[i]->_Texture;
		delete _powerUp[i];
	}

	delete _startScreen;
	delete _pause;
}

void Pacman::LoadContent()
{
	LoadGhosts();
	// load border
	_wallTexture->Load("Textures/Borders.png", false);

	// Load Pacman
	_pacman->_Texture->Load("Textures/Pacman.tga", false);

	// Load Munchie
	_munchieTexture->Load("Textures/Munchie.png", true);

	//load cherry
	_cherry->_Texture->Load("Textures/Cherry.png", false);

	//load powerup
	_powerUpTexture->Load("Textures/Power_up.png", false);

	// Set pause Menu Paramters
	_pause->_menuBackground = new Texture2D();
	_pause->_menuBackground->Load("Textures/Transparency.png", false);
	_pause->_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_pause->_menuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);

	//set start menu parameters
	_startScreen->_background = new Texture2D();
	_startScreen->_background->Load("Textures/pacmanBackground.png", false);;
	_startScreen->_rect = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());

	// Draws out th pacman map, based on a 2d array
    //can set up a function which can be passed a map (if multiple levels wanted)
	int munchieCounter = 0;
	int powerUpCounter = 0;
	int wallCounter = 0;
	int _tileType = 0;
	int offset = 10;

	for (int row = 0; row < 28; row++)
	{
		for (int col = 0; col < 20; col++)
		{
			if (munchieCounter < MAX_ELEMENTS &&
				powerUpCounter < MAX_ELEMENTS &&
				wallCounter < MAX_ELEMENTS) {

				if (_level[row][col] == 1) {
					_munchie[munchieCounter]->_Position->Y = row * 32;
					_munchie[munchieCounter]->_Position->Y += offset;
					_munchie[munchieCounter]->_Position->X = col * 32;
					_munchie[munchieCounter]->_Position->X += offset;

					munchieCounter++;
				}
				if (_level[row][col] == 2)
				{
					_powerUp[powerUpCounter]->_Position->Y = row * 32;
					_powerUp[powerUpCounter]->_Position->X = col * 32;

					powerUpCounter++;
				}
				if (_level[row][col] == 3)
				{
					_wall[wallCounter]->_SrcRect->X = Walls::btmRightCornerWall * TILE_SIZE;

					_wall[wallCounter]->_Position->X = col * 32;
					_wall[wallCounter]->_Position->Y = row * 32;

					wallCounter++;
				}
				if (_level[row][col] == 4)
				{
					_wall[wallCounter]->_SrcRect->X = Walls::topRightCornerWall * TILE_SIZE;

					_wall[wallCounter]->_Position->X = col * 32;
					_wall[wallCounter]->_Position->Y = row * 32;

					wallCounter++;
				}
				if (_level[row][col] == 5)
				{
					//draw btmLeftCornerWall
					_wall[wallCounter]->_SrcRect->X = Walls::btmLeftCornerWall * TILE_SIZE;

					_wall[wallCounter]->_Position->X = col * 32;
					_wall[wallCounter]->_Position->Y = row * 32;

					wallCounter++;
				}
				if (_level[row][col] == 6)
				{
					//draw topLefttCornerWall
					_wall[wallCounter]->_SrcRect->X = Walls::topLefttCornerWall * TILE_SIZE;

					_wall[wallCounter]->_Position->X = col * 32;
					_wall[wallCounter]->_Position->Y = row * 32;

					wallCounter++;
				}
				if (_level[row][col] == 7)
				{
					//draw horizontalWall
					_wall[wallCounter]->_SrcRect->X = Walls::horizontalWall * TILE_SIZE;

					_wall[wallCounter]->_Position->X = col * 32;
					_wall[wallCounter]->_Position->Y = row * 32;

					wallCounter++;
				}
				if (_level[row][col] == 8)
				{
					//draw verticalWall
					_wall[wallCounter]->_SrcRect->X = Walls::verticalWall * TILE_SIZE;

					_wall[wallCounter]->_Position->X = col * 32;
					_wall[wallCounter]->_Position->Y = row * 32;

					wallCounter++;
				}
				if (_level[row][col] == 9)
				{
					//draw HorLeftEdgeWall
					_wall[wallCounter]->_SrcRect->X = Walls::HorRightEdgeWall * TILE_SIZE;

					_wall[wallCounter]->_Position->X = col * 32;
					_wall[wallCounter]->_Position->Y = row * 32;

					wallCounter++;
				}
				if (_level[row][col] == 10)
				{
					//draw vertTopEdgeWall 
					_wall[wallCounter]->_SrcRect->X = Walls::HorLeftEdgeWall * TILE_SIZE;

					_wall[wallCounter]->_Position->X = col * 32;
					_wall[wallCounter]->_Position->Y = row * 32;

					wallCounter++;
				}
				if (_level[row][col] == 11)
				{
					//draw topLefttCornerWall
					_wall[wallCounter]->_SrcRect->X = Walls::vertTopEdgeWall * TILE_SIZE;

					_wall[wallCounter]->_Position->X = col * 32;
					_wall[wallCounter]->_Position->Y = row * 32;

					wallCounter++;
				}
				if (_level[row][col] == 12)
				{
					//draw vertBtmEdgeWall
					_wall[wallCounter]->_SrcRect->X = Walls::vertBtmEdgeWall * TILE_SIZE;

					_wall[wallCounter]->_Position->X = col * 32;
					_wall[wallCounter]->_Position->Y = row * 32;

					wallCounter++;
				}
				if (_level[row][col] == 13)
				{
					//leftSingleEdge
					_wall[wallCounter]->_SrcRect->X = Walls::leftSingleEdge * TILE_SIZE;

					_wall[wallCounter]->_Position->X = col * 32;
					_wall[wallCounter]->_Position->Y = row * 32;

					wallCounter++;
				}
				if (_level[row][col] == 14)
				{
					//topSingleEdge
					_wall[wallCounter]->_SrcRect->X = Walls::topSingleEdge * TILE_SIZE;

					_wall[wallCounter]->_Position->X = col * 32;
					_wall[wallCounter]->_Position->Y = row * 32;

					wallCounter++;
				}
				if (_level[row][col] == 15)
				{
					//bottomSingleEdge				
					_wall[wallCounter]->_SrcRect->X = Walls::bottomSingleEdge * TILE_SIZE;

					_wall[wallCounter]->_Position->X = col * 32;
					_wall[wallCounter]->_Position->Y = row * 32;

					wallCounter++;
				}
				if (_level[row][col] == 16)
				{
					//rightSingleEdge
					_wall[wallCounter]->_SrcRect->X = Walls::rightSingleEdge * TILE_SIZE;

					_wall[wallCounter]->_Position->X = col * 32;
					_wall[wallCounter]->_Position->Y = row * 32;

					wallCounter++;
				}
				if (_level[row][col] == 17)
				{
					_pacman->_Position->Y = row * 32;
					_pacman->_Position->X = col * 32;

					_cherry->_Position->Y = row * 32;
					_cherry->_Position->X = col * 32;
				}
			}
			else {
				cout << "Too many elements!" << endl;
			}
		}
	}

	_maxMunchie = munchieCounter;
	_maxPowerUp = powerUpCounter;
	_maxWall = wallCounter;

	cout << "munchieCounter : " << munchieCounter << endl;
	cout << "powerUpCounter: " << powerUpCounter << endl;
	cout << "wallCount: " << wallCounter << endl;
	//cout << GetTileAt(_pacman->_Position->Y / 32, _pacman->_Position->X / 32) << endl;
}

void Pacman::Update(int elapsedTime) {
	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	CheckPaused(keyboardState, Input::Keys::P);

	UpdateMenu(keyboardState);

	if (!_pause->_menu && !_startScreen->_active && !_dead && !_complete)
	{
		_frameCount++;
		Input(elapsedTime, keyboardState);	// get input from user
		UpdateGhosts(elapsedTime);
		UpdatePacman(elapsedTime);			// update pacman's position, animation, etc
		CheckViewPortCollision();
		UpdateMunchie(elapsedTime);
		UpdateCherry(elapsedTime);
		UpdatePowerUp(elapsedTime);
		ScoreBoard();
		if (CheckLevelComplete())
		{
			_complete = true;
			StartNewLevel();
		}
	}
}

int Pacman::ScoreBoard()
{
	//variable for user to input name
	char name[30];
	//variable for the score
	score == score;

	ofstream scoreBoardIn("Scoreboard.txt", ios::out);

	if (!scoreBoardIn.is_open())
	{
		cerr << "File could not be opened!";
		std::exit(1);
	}
	//outputs the score to the text file
	scoreBoardIn << score;

	// Close the file.
	scoreBoardIn.close();
}

bool Pacman::collisionCheck(int x1, int y1, int width1, int height1, int x2, int y2, int width2, int height2)
{
	int left1 = x1;
	int right1 = x1 + width1;
	int top1 = y1;
	int btm1 = y1 + height1;

	int left2 = x2;
	int right2 = x2 + width2;
	int top2 = y2;
	int btm2 = y2 + height2;

	if ((btm1 >= top2) && (top1 <= btm2) && (left1 <= right2) && (right1 >= left2))
		return true;
	return false;
}

void Pacman::StartGame(Input::KeyboardState* state, Input::Keys selectKey)
{
	//initializes the start screen
	if (state->IsKeyDown(selectKey))
	{
		_startScreen->_selectKeyDown = true;
		_startScreen->_active = false;
	}
	if (state->IsKeyUp(selectKey))
		_startScreen->_selectKeyDown = false;
}

void Pacman::CheckPaused(Input::KeyboardState* state, Input::Keys pauseKey)
{
	//initializes the pause menu
	if (state->IsKeyDown(pauseKey) && !_pause->_keyDown)
	{
		_pause->_keyDown = true;
		_pause->_menu = !_pause->_menu;
	}
	if (state->IsKeyUp(pauseKey))
		_pause->_keyDown = false;
}

void Pacman::CheckViewPortCollision()
{
	if (_pacman->_Position->X + _pacman->_SourceRect->Width > 650)
		_pacman->_Position->X = 0 - _pacman->_SourceRect->Width;

	if (_pacman->_Position->X + _pacman->_SourceRect->Width < 0)
		_pacman->_Position->X = 650 - _pacman->_SourceRect->Width;

	if (_pacman->_Position->Y + _pacman->_SourceRect->Width > Graphics::GetViewportHeight())
		_pacman->_Position->Y = 0 - _pacman->_SourceRect->Width;

	if (_pacman->_Position->Y + _pacman->_SourceRect->Width < 0)
		_pacman->_Position->Y = Graphics::GetViewportHeight() - _pacman->_SourceRect->Width;
}

void Pacman::LoadGhosts()
{
	_inkyTexture = new Texture2D();
	_inkyTexture->Load("Textures/Inky.png", false);
	_ghosts[0]->_Texture = _inkyTexture;
	_ghosts[0]->_Position = _ghosts[0]->startPos;

	_pinkyTexture = new Texture2D();
	_pinkyTexture->Load("Textures/Pinky.png", false);
	_ghosts[1]->_Texture = _pinkyTexture;
	_ghosts[1]->_Position = _ghosts[1]->startPos;

	_blinkyTexture = new Texture2D();
	_blinkyTexture->Load("Textures/Blinky.png", false);
	_ghosts[2]->_Texture = _blinkyTexture;
	_ghosts[2]->_Position = _ghosts[2]->startPos;

	_clideTexture = new Texture2D();
	_clideTexture->Load("Textures/Clide.png", false);
	_ghosts[3]->_Texture = _clideTexture;
	_ghosts[3]->_Position = _ghosts[3]->startPos;
}

void Pacman::Input(int elapsedTime, Input::KeyboardState* state)
{
	if (state->IsKeyDown(Input::Keys::D)) {
		_pacman->nextDir = Direction::Right;
	}
	else if (state->IsKeyDown(Input::Keys::W)) {
		_pacman->nextDir = Direction::Up;
	}
	else if (state->IsKeyDown(Input::Keys::A)) {
		_pacman->nextDir = Direction::Left;
	}
	else if (state->IsKeyDown(Input::Keys::S)) {
		_pacman->nextDir = Direction::Down;
	}
}

void Pacman::UpdatePacman(int elapsedTime)
{
	//move pacmans mouth
	if (_pacman->_moveMouth < 30)
	{
		_pacman->_SourceRect->X = 0.0f;
		_pacman->_moveMouth++;
	}
	else
	{
		_pacman->_SourceRect->X = 32.0f;
		_pacman->_moveMouth++;
		if (_pacman->_moveMouth >= 60)
			_pacman->_moveMouth = 0;
	}

	if (_pacman->currentDir == STILL && _pacman->nextDir != STILL)
	{
		_pacman->currentDir = _pacman->nextDir;
	}

	if (_pacman->canTurn)
	{
		_pacman->currentDir = _pacman->nextDir;
		_pacman->canTurn = false;
	}
	//cout << _pacman->currentDir << "  " << _pacman->nextDir << endl;

	Move(_pacman, elapsedTime);
	CheckIfCanTurn(_pacman->currentDir, _pacman->nextDir);
}

void Pacman::CheckIfCanTurn(Direction direction, Direction next) {
	//cout << "checking ...";
	if (next == Direction::Up && direction != Direction::Up)
	{
		if (GetTileAt((_pacman->_Position->Y / 32) - 1, (_pacman->_Position->X / 32)) == 1)
		{
			_pacman->_Position->X = ((int)_pacman->_Position->X / 32) * 32;
			_pacman->_Position->Y = ((int)_pacman->_Position->Y / 32) * 32;

			_pacman->canTurn = true;
			//cout << "can turn" << endl;
		}
	}
	if (next == Direction::Down && direction != Direction::Down)
	{
		if (GetTileAt((_pacman->_Position->Y / 32) + 1, (_pacman->_Position->X / 32)) == 1)
		{
			_pacman->_Position->X = ((int)_pacman->_Position->X / 32) * 32;
	    	_pacman->_Position->Y = ((int)_pacman->_Position->Y / 32) * 32;
		
			_pacman->canTurn = true;
			//cout << "can turn" << endl;
		}
	}
	if (next == Direction::Left && direction != Direction::Left)
	{
		if (GetTileAt((_pacman->_Position->Y / 32), (_pacman->_Position->X / 32) - 1) == 1)
		{
			_pacman->_Position->X = ((int)_pacman->_Position->X / 32) * 32;
			_pacman->_Position->Y = ((int)(_pacman->_Position->Y) / 32) * 32;

			_pacman->canTurn = true;
			//cout << "can turn" << endl;
		}
	}
	if (next == Direction::Right && direction != Direction::Right)
	{
		if (GetTileAt((_pacman->_Position->Y / 32), (_pacman->_Position->X / 32) + 1) == 1)
		{
			_pacman->_Position->X = ((int)_pacman->_Position->X / 32) * 32;
			_pacman->_Position->Y = ((int)_pacman->_Position->Y / 32) * 32;

			_pacman->canTurn = true;
			//cout << "can turn" << endl;
		}
	}
}

Vector2 Pacman::GetPacmanGridPosition()
{
	return Vector2((int)_pacman->_Position->X / 32, (int)_pacman->_Position->Y / 32);
}

bool Pacman::CheckLevelComplete()
{
	if (munchiesCollected == _maxMunchie + _maxPowerUp)
	{
		return true;
	}
	else
		return false;
}

void Pacman::StartNewLevel()
{
	for (int i = 0; i < _maxMunchie; i++)
	{
		_munchie[i]->spawn = true;
		if (i < _maxPowerUp)
		{
			_powerUp[i]->spawn = true;
		}
	}
	_pacman->_Position = _pacman->startPos;
	_pacman->currentDir = Direction::STILL;
	_pacman->nextDir = Direction::STILL;

	_complete = false;
}

void Pacman::UpdateMenu(Input::KeyboardState* state)
{
	MovePointerDown(state, Input::Keys::DOWN);
	MovePointerUp(state, Input::Keys::UP);

	if (_startScreen->selector->Y == 265)
	{
	    StartGame(state, Input::Keys::RETURN);
	}
	if (_startScreen->selector->Y == 315)
	{
		ShowContollsMenu(state, Input::Keys::RETURN);
	}
	if (_startScreen->selector->Y == 365)
	{
		ExitGame(state, Input::Keys::RETURN);
	}
}

void Pacman::MovePointerDown(Input::KeyboardState* state, Input::Keys downArrow)
{
	if (state->IsKeyDown(downArrow) && !_startScreen->_downKeyDown)
	{
		_startScreen->_downKeyDown = true;
		_startScreen->selector->Y += 50;
		if (_startScreen->selector->Y > 365)
		{
			_startScreen->selector->Y = 265;
		}
	}
	if (state->IsKeyUp(downArrow))
		_startScreen->_downKeyDown = false;
}

void Pacman::MovePointerUp(Input::KeyboardState* state, Input::Keys upArrow)
{
	if (state->IsKeyDown(upArrow) && !_startScreen->_upKeyDown)
	{
		_startScreen->_upKeyDown = true;
		_startScreen->selector->Y -= 50;
		if (_startScreen->selector->Y < 265)
		{
			_startScreen->selector->Y = 365;
		}
	}
	if (state->IsKeyUp(upArrow))
		_startScreen->_upKeyDown = false;
}

void Pacman::ShowContollsMenu(Input::KeyboardState* state, Input::Keys enter)
{
	
}

void Pacman::ExitGame(Input::KeyboardState* state, Input::Keys enter)
{
	if (state->IsKeyDown(enter))
	{
		_startScreen->_selectKeyDown = true;
		exit(0);
	}
	if (state->IsKeyUp(enter))
		_startScreen->_selectKeyDown = false;
}

void Pacman::Move(Player* player, int elapsedTime)
{
	int tmpDistance = player->_cSpeed * elapsedTime;
	if (player->currentDir == 1)
	{
		player->_SourceRect->Y = 32.0f;
		player->_Position->Y += tmpDistance; //moves pacman down

		for (int i = 0; i < _maxWall; i++)
		{
			if (collisionCheck(player->_Position->X + 1, player->_Position->Y + 1, player->_SourceRect->Width - 2, player->_SourceRect->Height - 2,
				_wall[i]->_Position->X, _wall[i]->_Position->Y, _wall[i]->_SrcRect->Width, _wall[i]->_SrcRect->Height))
			{
				player->_Position->Y -= tmpDistance;
				player->currentDir = Direction::STILL;
				//cout << "colided with wall" << endl;
			}
		}
	}

	if (player->currentDir == 2)
	{
		player->_SourceRect->Y = 64.0f;
		player->_Position->X -= tmpDistance; //Moves Pacman left
		for (int i = 0; i < _maxWall; i++)
		{
			if (collisionCheck(player->_Position->X + 1, player->_Position->Y + 1, player->_SourceRect->Width - 2, player->_SourceRect->Height - 2,
				_wall[i]->_Position->X, _wall[i]->_Position->Y, _wall[i]->_SrcRect->Width, _wall[i]->_SrcRect->Height))
			{
				player->_Position->X += tmpDistance;
				player->currentDir = Direction::STILL;
				//cout << "colided with wall" << endl;
			}
		}
	}

	if (player->currentDir == 3)
	{
		player->_SourceRect->Y = 0.0f;
		player->_Position->X += tmpDistance; //Moves Pacman right
		for (int i = 0; i < _maxWall; i++)
		{
			if (collisionCheck(player->_Position->X + 1, player->_Position->Y + 1, player->_SourceRect->Width - 2, player->_SourceRect->Height - 2,
				_wall[i]->_Position->X, _wall[i]->_Position->Y, _wall[i]->_SrcRect->Width, _wall[i]->_SrcRect->Height))
			{
				player->_Position->X -= tmpDistance;
				player->currentDir = Direction::STILL;
				//cout << "colided with wall" << endl;
			}
		}
	}

	if (player->currentDir == 0)
	{
		player->_SourceRect->Y = 96.0f;
		player->_Position->Y -= tmpDistance; //Moves Pacman up
		for (int i = 0; i < _maxWall; i++)
		{
			if (collisionCheck(player->_Position->X + 1, player->_Position->Y + 1, player->_SourceRect->Width - 2, player->_SourceRect->Height - 2,
				_wall[i]->_Position->X, _wall[i]->_Position->Y, _wall[i]->_SrcRect->Width, _wall[i]->_SrcRect->Height))
			{
				player->_Position->Y += tmpDistance;
				player->currentDir = Direction::STILL;
				//cout << "colided with wall" << endl;
			}
		}
	}
}

void Pacman::UpdateGhosts(int elapsedTime)
{
	for (int i = 0; i < 4; i++)
	{
		Move(_ghosts[i], elapsedTime);
		ChooseRandomDirection(_ghosts[i]);
	}
}

void Pacman::ChooseRandomDirection(Player* ghost)
{
	if (ghost->currentDir == Direction::STILL)
	{
		int randNum = (rand() % 4);
		switch (randNum)
		{
		case 0: ghost->currentDir = Direction::Up;
			break;
		case 1: ghost->currentDir = Direction::Down;
			break;
		case 2: ghost->currentDir = Direction::Left;
			break;
		case 3: ghost->currentDir = Direction::Right;
			break;
		default:
			break;
		}
	}
}

void Pacman::UpdateMunchie(int elapsedTime)
{
	for (int i = 0; i < _maxMunchie; i++)
	{
		if (_munchie[i]->spawn == true)
		{
			if (collisionCheck(_pacman->_Position->X, _pacman->_Position->Y, _pacman->_SourceRect->Width, _pacman->_SourceRect->Height,
				_munchie[i]->_Position->X, _munchie[i]->_Position->Y, _munchie[i]->_SrcRect->Width / 2, _munchie[i]->_SrcRect->Height / 2))
			{
				score += 10;
				_munchie[i]->spawn = false;
				munchiesCollected++;
				cout << "colided with munchie " << munchiesCollected << endl;
			}

			if (_frameCount < 30)
			{
				_munchie[i]->_SrcRect->X = 0;
			}
			else
			{
				// Draw Blue Munchie
				_munchie[i]->_SrcRect->X = 12;
				if (_frameCount >= 60)
					_frameCount = 0;
			}
		}
	}
}

void Pacman::UpdateCherry(int elapsedTime)
{
	_cherry->_rand++;
	//creates a pseudorandom number and checks to see if it is greter than _randcherry
	//if it is it will set spawnCherry to true 
	if (_cherry->_rand >= rand() % 500 + 2000)
	{
		_time++;
		_cherry->spawn = true;
		if (_time >= 100 * elapsedTime)
		{
			_cherry->spawn = false;
			_cherry->_rand = 0;
			_time = 0;
		}
	}
	//if spawnCherry is false then this code executes
	//false indicatwes we have no cherry on screen
	//and want another to spawn randomly 

	if (_cherry->spawn == true)
	{
		if (collisionCheck(_pacman->_Position->X, _pacman->_Position->Y, _pacman->_SourceRect->Width /2, _pacman->_SourceRect->Height /2,
			_cherry->_Position->X, _cherry->_Position->Y, _cherry->_SrcRect->Width / 2, _cherry->_SrcRect->Height / 2))
		{
			score += 100;
			_cherry->_rand = 0;
			_cherry->spawn = false;
			cout << "colided with cherry" << endl;
		}
		if (_frameCount < 30)
		{
			_cherry->_SrcRect->X = 0;
		}
		else
		{
			_cherry->_SrcRect->X = 32;
			if (_frameCount >= 60)
				_frameCount = 0;
		}
	}
}

void Pacman::UpdatePowerUp(int elapsedTime)
{
	for (int i = 0; i < _maxPowerUp; i++)
	{
		if (collisionCheck(_pacman->_Position->X, _pacman->_Position->Y, _pacman->_SourceRect->Width, _pacman->_SourceRect->Height,
			_powerUp[i]->_Position->X, _powerUp[i]->_Position->Y, _powerUp[i]->_SrcRect->Width / 2, _powerUp[i]->_SrcRect->Height / 2))
		{
			if (_powerUp[i]->spawn == true)
			{
				score += 10;

				_powerUp[i]->spawn = false;
				cout << "colided with powerup " << munchiesCollected << endl;
				munchiesCollected++;
			}
		}
		if (_frameCount < 30)
		{
			_powerUp[i]->_SrcRect->X = 0;
		}
		else
		{
			_powerUp[i]->_SrcRect->X = 32;
			if (_frameCount >= 60)
				_frameCount = 0;
		}
	}
}

int Pacman::GetTileAt(unsigned int h, unsigned int w)
{
	//return each tile in the array
	if (h < MAP_HEIGHT && w < MAP_WIDTH)
	{
		return mMap[h][w];
	}

	return 0;
}

void Pacman::Draw(int elapsedTime)
{
	// Allows us to easily create a string
	std::stringstream stream;
	stream << "Pacman X: " << _pacman->_Position->X << " Y: " << _pacman->_Position->Y;

	SpriteBatch::BeginDraw(); // Starts Drawing

	for (int i = 0; i < _maxMunchie; i++)
	{
		if (_munchie[i]->spawn == true)
		{
			SpriteBatch::Draw(_munchieTexture, _munchie[i]->_Position, _munchie[i]->_SrcRect);
		}
	}

	for (int i = 0; i < _maxPowerUp; i++)
	{
		if (_powerUp[i]->spawn == true)
		{
			SpriteBatch::Draw(_powerUpTexture, _powerUp[i]->_Position, _powerUp[i]->_SrcRect);
		};
	}

	if (_cherry->spawn == true)
	{
		SpriteBatch::Draw(_cherry->_Texture, _cherry->_Position, _cherry->_SrcRect);
	}

	for (int i = 0; i < _maxWall; i++)
	{
		SpriteBatch::Draw(_wallTexture, _wall[i]->_Position, _wall[i]->_SrcRect);
	}

	SpriteBatch::Draw(_pacman->_Texture, _pacman->_Position, _pacman->_SourceRect); // Draws Pacman

	for (int i = 0; i < 4; i++)
	{
		SpriteBatch::Draw(_ghosts[i]->_Texture, _ghosts[i]->_Position, _ghosts[i]->_SourceRect); // Draws Ghosts
	}

	//draws the start menu
	if (_startScreen->_active)
	{
		std::stringstream play;
		play << "PLAY";
		SpriteBatch::Draw(_startScreen->_background, _startScreen->_rect, nullptr);
		Vector2* _playStringPosition = new Vector2((Graphics::GetViewportWidth() / 2.0f) - 50, (Graphics::GetViewportHeight() / 2.0f) - 100);
		SpriteBatch::DrawString(play.str().c_str(), _playStringPosition, Color::Cyan);

		std::stringstream options;
		options << "CONTROLS";
		Vector2* _optionsStringPosition = new Vector2((Graphics::GetViewportWidth() / 2.0f) -80, (Graphics::GetViewportHeight() / 2.0f) - 50);
		SpriteBatch::DrawString(options.str().c_str(), _optionsStringPosition, Color::Cyan);

		std::stringstream quit;
		quit << "QUIT";
		Vector2* _quitStringPosition = new Vector2((Graphics::GetViewportWidth() / 2.0f) - 50, (Graphics::GetViewportHeight() / 2.0f));
		SpriteBatch::DrawString(quit.str().c_str(), _quitStringPosition, Color::Cyan);

		Texture2D* _pointerTex = new Texture2D();
		_pointerTex->Load("Textures/pointer.png", false);

		SpriteBatch::Draw(_pointerTex, _startScreen->selector, nullptr);

		//std::stringstream startStream;
		//startStream << "START - press space!";

		//SpriteBatch::Draw(_start->_menuBackground, _start->_menuRectangle, nullptr);
		//SpriteBatch::DrawString(startStream.str().c_str(), _start->_menuStringPosition, Color::Yellow);
	}

	if (!_startScreen->_active)
	{
		// Draws String
		SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);

		std::stringstream scoreStream;
		scoreStream << "Score: " << score << endl;
		SpriteBatch::DrawString(scoreStream.str().c_str(), _scorePosition, Color::Green);
	}

	//pause screen
	if (_pause->_menu)
	{
		std::stringstream menuStream;
		menuStream << "PAUSED!";

		SpriteBatch::Draw(_pause->_menuBackground, _pause->_menuRectangle, nullptr);
		SpriteBatch::DrawString(menuStream.str().c_str(), _pause->_menuStringPosition, Color::Red);
	}

	SpriteBatch::EndDraw(); // Ends Drawing
}