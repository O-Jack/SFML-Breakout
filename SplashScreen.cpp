#include "stdafx.h"
#include "SplashScreen.h"

void SplashScreen::show(sf::RenderWindow &window) {
	/* Attempt to load splash screen image from file, return immediately if failed */
	sf::Texture splash_texture;
	if (!splash_texture.loadFromFile("Images/splash-screen.jpg"))
		return;

	/* Note that image is not the one being rendered to screen, that's the job of a sprite */

	/* Create sprite (drawable representation of a texture) from loaded image
	 * and draw to window
	 */
	sf::Sprite splash_sprite(splash_texture);
	window.draw(splash_sprite);
	window.display();

	/* Show splash screen until a key press or mouse click, or until window is closed */
	sf::Event event;
	while (true) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed ||
				event.type == sf::Event::MouseButtonPressed ||
				event.type == sf::Event::Closed)
				return;
		}
	}
}
