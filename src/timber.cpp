#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

int main () 
{
// Create a video mode object
sf::VideoMode vm(1920, 1080);

// Create and open a window for the game
sf::RenderWindow window(vm, "Timber!!!", sf::Style::Fullscreen);

// Create a texture to hold a graphic on the GPU
sf::Texture textureBackground;

// Load a graphic into the texture
textureBackground.loadFromFile("../graphics/background.png");

// Create a sprite
sf::Sprite spriteBackground;

// Attach the texture to the sprite
spriteBackground.setTexture(textureBackground);

// Set the spriteBackground to cover the screen
spriteBackground.setPosition(0,0);

// Make a tree sprite
sf::Texture textureTree;
textureTree.loadFromFile("../graphics/tree.png");
sf::Sprite spriteTree;
const float TREE_HORIZONTAL_POSITION { 810 };
const float TREE_VERTICAL_POSITION { 0 };
spriteTree.setTexture(textureTree);
spriteTree.setPosition(TREE_HORIZONTAL_POSITION, TREE_VERTICAL_POSITION);

// Prepare the bee
sf::Texture textureBee;
textureBee.loadFromFile("../graphics/bee.png");
sf::Sprite spriteBee;
const float BEE_HORIZONTAL_POSITION { 0 };
const float BEE_VERTICAL_POSITION { 800 };
spriteBee.setTexture(textureBee);
spriteBee.setPosition(BEE_HORIZONTAL_POSITION, BEE_VERTICAL_POSITION);

// Is the bee currently moving?
bool beeActive { false };

// How fast can the bee fly?
float beeSpeed { 0.0f };

// Make 3 cloud sprite from 1 texture
sf::Texture textureCloud;

// Load 1 new texture
textureCloud.loadFromFile("../graphics/cloud.png");

// 3 new sprites with the same texture
sf::Sprite spriteCloud1;
sf::Sprite spriteCloud2;
sf::Sprite spriteCloud3;
spriteCloud1.setTexture(textureCloud);
spriteCloud2.setTexture(textureCloud);
spriteCloud3.setTexture(textureCloud);

// Position the clouds on the left of the screen at different heights
const float CLOUD1_HORIZONTAL_POSITION { 0 };
const float CLOUD1_VERTICAL_POSITION { 0 };
spriteCloud1.setPosition(CLOUD1_HORIZONTAL_POSITION, CLOUD1_VERTICAL_POSITION);
const float CLOUD2_HORIZONTAL_POSITION { 0 };
const float CLOUD2_VERTICAL_POSITION { 250 };
spriteCloud2.setPosition(CLOUD2_HORIZONTAL_POSITION, CLOUD2_VERTICAL_POSITION);
const float CLOUD3_HORIZONTAL_POSITION { 0 };
const float CLOUD3_VERTICAL_POSITION { 500 };
spriteCloud3.setPosition(CLOUD3_HORIZONTAL_POSITION, CLOUD3_VERTICAL_POSITION);

// Are the clouds currently on screen?
bool cloud1Active { false };
bool cloud2Active { false };
bool cloud3Active { false };

// How fast is each cloud?
float cloud1Speed { 0.0f };
float cloud2Speed { 0.0f };
float cloud3Speed { 0.0f };

// Variables to control time itself
sf::Clock clock;

while (window.isOpen())
{

// Handle player's inputs
//
//

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
{
window.close();
}

// Update the scene
//
//
//

// Measure Time
sf::Time dt = clock.restart();

// Draw the scene
//
//
//

// Clear everything from the last frame window.clear();
window.clear();
//

// Draw our game to the screen
window.draw(spriteBackground);

// Draw the clouds
window.draw(spriteCloud1);
window.draw(spriteCloud2);
window.draw(spriteCloud3);

// Draw the tree
window.draw(spriteTree);

// Draw the insect
window.draw(spriteBee);

// Show everything we just drew window.display();
window.display();

}

return 0;	
}
