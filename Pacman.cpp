#include "Pacman.h"
#include <fstream>
#include <cstdlib>

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
{5 ,7 ,7 ,3 ,1,12 ,1 ,6 ,14,14,14,4 ,1,12 ,1 ,5 ,7 ,7,15 ,7},
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
	_frameCount = 0;
	_time = 0;
	_maxMunchie = 0;
	_maxPowerUp = 0;
	_maxWall = 0;
	score = 0;

	_pause = new Menu();
	_pause->_menu = false;
	_pause->_keyDown = false;

	_start = new Menu();
	_start->_menu = true;

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

	_pacman = new Player;
	_pacman->_Texture = new Texture2D();
	_pacman->_Texture = _pacman->_Texture;
	_pacman->_Position = new Vector2();
	_pacman->_SourceRect = new Rect(0.0f, 0.0f, 32, 32);
	_pacman->_moveMouth = 0;

	_cherry = new Collectable();
	_cherry->_Texture = &Texture2D();
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

	delete _start;
	delete _pause;
}

void Pacman::LoadContent()
{
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
	_start->_menuBackground = new Texture2D();
	_start->_menuBackground->Load("Textures/Transparency.png", false);
	_start->_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());
	_start->_menuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);

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
}

void Pacman::Update(int elapsedTime) {
	// Gets the current state of the keyboard
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	CheckPaused(keyboardState, Input::Keys::P);
	CheckStart(keyboardState, Input::Keys::SPACE);

	if (!_pause->_menu && !_start->_menu && !_dead)
	{
		_frameCount++;

		Input(elapsedTime, keyboardState);	// get input from user
		UpdatePacman(elapsedTime);			// update pacman's position, animation, etc
		CheckViewPortCollision();
		UpdateMunchie(elapsedTime);
		UpdateCherry(elapsedTime);
		UpdatePowerUp(elapsedTime);
		ScoreBoard();
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

void Pacman::CheckStart(Input::KeyboardState* state, Input::Keys startKey)
{
	//initializes the start screen
	if (state->IsKeyDown(startKey))
	{
		_start->_keyDown = true;
		_start->_menu = false;
	}
	if (state->IsKeyUp(startKey))
		_start->_keyDown = false;
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

void Pacman::Input(int elapsedTime, Input::KeyboardState* state)
{
	if (state->IsKeyDown(Input::Keys::D)) {
		_pacman->moveUp = false;
		_pacman->moveDown = false;
		_pacman->moveLeft = false;
		_pacman->moveRight = true;
		_pacman->_SourceRect->Y = 0.0f;
	}
	else if (state->IsKeyDown(Input::Keys::W)) {
		_pacman->moveUp = true;
		_pacman->moveDown = false;
		_pacman->moveLeft = false;
		_pacman->moveRight = false;
		_pacman->_SourceRect->Y = 96.0f;
	}
	else if (state->IsKeyDown(Input::Keys::A)) {
		_pacman->moveUp = false;
		_pacman->moveDown = false;
		_pacman->moveLeft = true;
		_pacman->moveRight = false;
		_pacman->_SourceRect->Y = 64.0f;
	}
	else if (state->IsKeyDown(Input::Keys::S)) {
		_pacman->moveUp = false;
		_pacman->moveDown = true;
		_pacman->moveLeft = false;
		_pacman->moveRight = false;
		_pacman->_SourceRect->Y = 32.0f;
	}
}

void Pacman::UpdatePacman(int elapsedTime)
{
	//how about
	float tmpDistance = _pacman->_cSpeed * elapsedTime;

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

	if (_pacman->moveDown)
	{
		_pacman->_Position->Y += tmpDistance; //moves pacman down

		for (int i = 0; i < _maxWall; i++)
		{
			if (collisionCheck(_pacman->_Position->X + 1, _pacman->_Position->Y + 1, _pacman->_SourceRect->Width - 2, _pacman->_SourceRect->Height - 2,
				_wall[i]->_Position->X, _wall[i]->_Position->Y, _wall[i]->_SrcRect->Width, _wall[i]->_SrcRect->Height))
			{
				_pacman->_Position->Y -= tmpDistance;
				cout << "colided with wall" << endl;
			}
		}
	}

	if (_pacman->moveLeft)
	{
		_pacman->_Position->X -= tmpDistance; //Moves Pacman left
		for (int i = 0; i < _maxWall; i++)
		{
			if (collisionCheck(_pacman->_Position->X + 1, _pacman->_Position->Y + 1, _pacman->_SourceRect->Width - 2, _pacman->_SourceRect->Height - 2,
				_wall[i]->_Position->X, _wall[i]->_Position->Y, _wall[i]->_SrcRect->Width, _wall[i]->_SrcRect->Height))
			{
				_pacman->_Position->X += tmpDistance;
				cout << "colided with wall" << endl;
			}
		}
	}
	if (_pacman->moveRight)
	{
		_pacman->_Position->X += tmpDistance; //Moves Pacman right
		for (int i = 0; i < _maxWall; i++)
		{
			if (collisionCheck(_pacman->_Position->X + 1, _pacman->_Position->Y + 1, _pacman->_SourceRect->Width - 2, _pacman->_SourceRect->Height - 2,
				_wall[i]->_Position->X, _wall[i]->_Position->Y, _wall[i]->_SrcRect->Width, _wall[i]->_SrcRect->Height))
			{
				_pacman->_Position->X -= tmpDistance;
				cout << "colided with wall" << endl;
			}
		}
	}
	if (_pacman->moveUp)
	{
		_pacman->_Position->Y -= tmpDistance; //Moves Pacman up
		for (int i = 0; i < _maxWall; i++)
			{
			if (collisionCheck(_pacman->_Position->X + 1, _pacman->_Position->Y + 1, _pacman->_SourceRect->Width - 2, _pacman->_SourceRect->Height - 2,
				_wall[i]->_Position->X, _wall[i]->_Position->Y, _wall[i]->_SrcRect->Width, _wall[i]->_SrcRect->Height))
			{
				_pacman->_Position->Y += tmpDistance;
				cout << "colided with wall" << endl;
			}
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
				cout << "colided with munchie" << endl;
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
		if (_time >= 500 * elapsedTime)
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
		if (collisionCheck(_pacman->_Position->X, _pacman->_Position->Y, _pacman->_SourceRect->Width, _pacman->_SourceRect->Height,
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
				score += 10;

			_powerUp[i]->spawn = false;
			cout << "colided with powerup" << endl;
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
		}
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

	//draws the start menu
	if (_start->_menu)
	{
		std::stringstream startStream;
		startStream << "START - press space!";

		SpriteBatch::Draw(_start->_menuBackground, _start->_menuRectangle, nullptr);
		SpriteBatch::DrawString(startStream.str().c_str(), _start->_menuStringPosition, Color::Yellow);
	}

	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);

	std::stringstream scoreStream;
	scoreStream << "Score: " << score << endl;
	SpriteBatch::DrawString(scoreStream.str().c_str(), _scorePosition, Color::Green);

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