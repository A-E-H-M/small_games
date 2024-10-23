#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "bat.hpp"
#include "ball.hpp"

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);

	// Create and open a window for the game
	RenderWindow window(vm, "Pong", Style::Fullscreen);
	
	// Values to maintain and render to the screen
	int score {0};
	int lives {3};

	// Create a bat at the bottom center of the screen
	bat m_Bat(1920 / 2, 1080 - 20);

	// Create a ball
	Ball ball(1920 / 2, 0);
	
	// Create a text object called HUD
	Text hud;

	// A retro-style font
	Font font;
	font.loadFromFile("fonts/DS-DIGIT.ttf");

	// Set the font to the retro-style
	hud.setFont(font);

	// Make the size of the font large
	hud.setCharacterSize(75);

	// Choose a color
	hud.setFillColor(Color::White);
	hud.setPosition(20, 20);

	// Here is the clock for timing everything
	Clock clock;

	// Create the main game loop
	while (window.isOpen())
	{
		// Handle player input
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				//Quit the game when the window is closed
				window.close();
		}

		// Handle the player quitting
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		// Handle the pressing and releasing of the arrow keys
		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			m_Bat.moveLeft();
		}
		else
		{
			m_Bat.stopLeft();
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			m_Bat.moveRight();
		}
		else
		{
			m_Bat.stopRight();
		}


		// Update the bat, the ball and HUD
		// Update the delta time
		Time dt = clock.restart();
		m_Bat.update(dt);
		ball.update(dt);

		// Update the HUD text
		std::stringstream ss;
		ss << "Score: " << score << " Lives: " << lives;
		hud.setString(ss.str());

		// Handle ball hitting the bottom on the window
		if (ball.getPosition().top > window.getSize().y)
		{
			// Reverse the ball direction
			ball.reboundBottom();

			//Remove a life
			lives--;

			// Check for zero lives
			if (lives <  1)
			{
				// Reset the score
				score = 0;

				// Reset the lives
				lives = 3;
			}
		}
		
		// Handle ball hitting the top of the window
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatOrTop();

			// Add a point to the players score
			score++;
		}

		// Handle ball hitting sides of the window
		if (ball.getPosition().left < 0 || ball.getPosition().left + ball.getPosition().width > window.getSize().x)
		{
			ball.reboundSides();
		}

		// Has the ball hit the bat?
		if (ball.getPosition().intersects(m_Bat.getPosition()))
		{
			// Hit detected so reverse the ball and score a point
			ball.reboundBatOrTop();
		}

		// Draw the bat, the ball and HUD
		window.clear();
		window.draw(hud);
		window.draw(m_Bat.getShape());
		window.draw(ball.getShape());
		window.display();

	} // End main game loop
	return 0;
}
