// Include important libraries here
#include <sstream>

#include <SFML/Graphics.hpp>

// Make code easier to type with "using namespace" 
using namespace sf;

// Function declaration
void updateBranches(int seed);

const int NUM_BRANCHES {6};
Sprite branches[NUM_BRANCHES];

// Where is the player/branch? Left or right?
enum class side { LEFT, RIGHT, NONE };
side branchPositions[NUM_BRANCHES];

// This is where our game starts from int main()
int main()
{
	// Create a video mode object 
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

	// Create a texture to hold a graphic on the GPU 
	Texture textureBackground;

	// Load a graphic into the texture 
	textureBackground.loadFromFile("graphics/background.png");

	// Create a sprite 
	Sprite spriteBackground;

	// Attach the texture to the sprite 
	spriteBackground.setTexture(textureBackground);

	// Set the spriteBackground to cover the screen 
	spriteBackground.setPosition(0, 0);

	// Make a tree sprite
	Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	Sprite spriteTree;
	spriteTree.setTexture(textureTree);
	
	const float TREE_HORIZONTAL_POSITION {810};
	const float TREE_VERTICAL_POSITION {0};
	spriteTree.setPosition(TREE_HORIZONTAL_POSITION, TREE_VERTICAL_POSITION);

	// Prepare the bee
	Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	Sprite spriteBee;
	spriteBee.setTexture(textureBee);

	const float BEE_HORIZONTAL_POSITION {0};
	const float BEE_VERTICAL_POSITION {800};
	spriteBee.setPosition(BEE_HORIZONTAL_POSITION, BEE_VERTICAL_POSITION);

	// Is the bee currently moving?
	bool beeActive {false};

	// How fast can the bee fly?
	float beeSpeed {0.0f};

	// Make 3 cloud sprites with the same texture
	Texture textureCloud;

	// Load 1 new texture
	textureCloud.loadFromFile("graphics/cloud.png");
	
	// 3 new sprites with the same texture
	Sprite spriteCloud1;
	Sprite spriteCloud2;
	Sprite spriteCloud3;
	spriteCloud1.setTexture(textureCloud);
	spriteCloud2.setTexture(textureCloud);
	spriteCloud3.setTexture(textureCloud);
	
	// Position the clouds on the left of the screen at different heights
	const float CLOUD1_HORIZONTAL_POSITION {0};
	const float CLOUD1_VERTICAL_POSITION {0};
	spriteCloud1.setPosition(CLOUD1_HORIZONTAL_POSITION, CLOUD1_VERTICAL_POSITION);

	const float CLOUD2_HORIZONTAL_POSITION {0};
	const float CLOUD2_VERTICAL_POSITION {250};
	spriteCloud2.setPosition(CLOUD2_HORIZONTAL_POSITION, CLOUD2_VERTICAL_POSITION);


	const float CLOUD3_HORIZONTAL_POSITION {0};
	const float CLOUD3_VERTICAL_POSITION {500};
	spriteCloud3.setPosition(CLOUD3_HORIZONTAL_POSITION, CLOUD3_VERTICAL_POSITION);

	// Are the clouds currently on the screen?
	bool cloud1Active {false};
	bool cloud2Active {false};
	bool cloud3Active {false};

	// How fast is each cloud?
	float cloud1Speed {0.0f};
	float cloud2Speed {0.0f};
	float cloud3Speed {0.0f};

	// Variables to control time itself
	Clock clock;

	// Time bar
	RectangleShape timeBar;
	float timeBarStartWidth {400};
	float timeBarHeight {80};
	timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	Time gameTimeTotal;
	float timeRemaining {6.0f};
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	// Track whether the game is running
	bool paused {true};

	// Draw some text
	int score {0};

	Text messageText;
	Text scoreText;

	// We need to choose a font
	Font font;
	font.loadFromFile("fonts/KOMIKAP.ttf");

	// Set the font to our message
	messageText.setFont(font);
	scoreText.setFont(font);

	// Assign the actual message
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");

	// Make it really big
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(100);

	// Choose a color
	messageText.setFillColor(Color::White);
	scoreText.setFillColor(Color::White);

	// Position the text
	FloatRect textRect = messageText.getLocalBounds();
	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);

	scoreText.setPosition(20, 20);

	// Prepare 5 branches
	Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");

	// Set the texture for each branch sprite
	for (int i =0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-2000, -2000);

		// Set the sprite's origin to dead centre
		branches[i].setOrigin(220, 20);
	}
	
	while (window.isOpen())
	{

		/*
		**************************************** 
		Handle the players input
		****************************************
		*/

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			paused = false;

			// Reset the time and the score
			score = 0;
			timeRemaining = 6;
		}

		/*
		**************************************** 
		Update the scene
		****************************************
		*/

		// Start the game
		if (!paused)
		{

		// Measure time
		Time dt = clock.restart();

		// Subtract from the amount of the remaining
		timeRemaining -= dt.asSeconds();

		// Resize the time bar
		timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

		if (timeRemaining <= 0.0f)
		{
			// Pause the game
			paused = true;

			// Change the message shown to the player
			messageText.setString("Out of time!");

			// Reposition the text based on its new size
			FloatRect textRect = messageText.getLocalBounds();
			messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

			messageText.setPosition(1920 / 2.0f, 1080 /2.0f);
		}

		// Setup the bee
		if (!beeActive)
		{
			// How fast is the bee
			srand((int)time(0));
			beeSpeed = (rand() % 200) + 200;

			// How high is the bee
			srand((int)time(0) * 10);
			float height = (rand() % 500) + 500;
			spriteBee.setPosition(2000, height);
			beeActive = true;	
		}

		else
		// Move the bee
		{
			spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);

			// Has the bee reached the left-hand edge of the screen?
			if (spriteBee.getPosition().x < -100)
			{
				//Set it up ready to be a whole new bee next frame
				beeActive = false;
			}
		}

		// Manage the clouds
		// Cloud 1
		if (!cloud1Active)
		{
			// How fast is the cloud
			srand((int)time(0) * 10);
			cloud1Speed = (rand() % 200);

			// How high is the cloud
			srand((int)time(0) * 10);
			float height = (rand() % 150);
			spriteCloud1.setPosition(-200, height);
			cloud1Active = true;
		}

		else
		{
			spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);

			// Has the cloud reached the right hand edge of the screen?
			if (spriteCloud1.getPosition().x > 1920)
			{
				//Set it up ready to be a whole new cloud next frame
				cloud1Active = false;
			}

		}

		// Cloud 2
		if (!cloud2Active)
		{
			// How fast is the cloud
			srand((int)time(0) * 20);
			cloud2Speed = (rand() % 200);

			// How high is the cloud
			srand((int)time(0) * 20);
			float height = (rand() % 300) - 150;
			spriteCloud2.setPosition(-200, height);
			cloud2Active = true;
		}

		else
		{
			spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);

			// Has the cloud reached the right hand edge of the screen?
			if (spriteCloud2.getPosition().x > 1920)
			{
				//Set it up ready to be a whole new cloud next frame
				cloud2Active = false;
			}

		}

		// Cloud 3
		if (!cloud3Active)
		{
			// How fast is the cloud
			srand((int)time(0) * 30);
			cloud3Speed = (rand() % 200);

			// How high is the cloud
			srand((int)time(0) * 30);
			float height = (rand() % 450) - 150;
			spriteCloud3.setPosition(-200, height);
			cloud3Active = true;
		}

		else
		{
			spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);

			// Has the cloud reached the right hand edge of the screen?
			if (spriteCloud3.getPosition().x > 1920)
			{
				//Set it up ready to be a whole new cloud next frame
				cloud3Active = false;
			}

		}
		
		// Update the score text
		std::stringstream ss;
		ss << "Score = " << score;
		scoreText.setString(ss.str());

		// Update the branch sprites
		for (int i =0; i < NUM_BRANCHES; i ++)
		{
			float height = i * 50;

			if (branchPositions[i] == side::LEFT)
			{
				// Move the sprite to the left side
				branches[i].setPosition(610, height);

				// Flip the sprite round the other way
				branches[i].setRotation(180);
			}

			else if (branchPositions[i] == side::RIGHT)
			{
				// Move the sprite to the right side
				branches[i].setPosition(1330, height);

				// Set the sprite rotation to normal
				branches[i].setRotation(0);
			}

			else
			{
				// Hide the branch
				branches[i].setPosition(3000, height);
			}
		}

		} // End if(!paused)

		/*
		**************************************** 
		Draw the scene
		****************************************
		*/

		// Clear everything from the last frame 
		window.clear();

		// Draw our game scene here
		window.draw(spriteBackground);

		// Draw the clouds
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		// Draw the branches
		for (int i = 0; i <NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}
		
		// Draw the tree
		window.draw(spriteTree);

		// Draw the bee
		window.draw(spriteBee);

		// Draw the score
		window.draw(scoreText);

		// Draw the timebar
		window.draw(timeBar);

		if (paused)
		{
			// Draw our message
			window.draw(messageText);
		}

		// Show everything we just drew 
		window.display();
	}
	return 0;
}

// Function definition
void updateBranches(int seed)
{
	// Move all the branches down one place
	for (int j = NUM_BRANCHES - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j-1];

	// Spawn a new branch at position 0
	srand((int)time(0) + seed);
	int r = (rand() % 5);

	switch (r)
	{
		case 0:
			branchPositions[0] = side::LEFT;
			break;
		case 1:
			branchPositions[0] = side::RIGHT;
			break;
		default:
			branchPositions[0] = side::NONE;
			break;
	}
	}
}

