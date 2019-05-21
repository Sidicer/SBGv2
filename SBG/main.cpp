#include <sstream>

#include "Computer.h"

int main()
{
	Computer computer;
	Player player;
	
    // Init Window
    sf::RenderWindow window(sf::VideoMode(1000,800), "Sidicers Battleship Game");
	window.setFramerateLimit(60);

    // Init Game
    float gridSizeF = 50.f;
    unsigned gridSizeU = static_cast<unsigned>(gridSizeF);
    float dt = 0.f;
    sf::Clock dtClock;
    
    sf::Vector2i mousePosScreen = sf::Mouse::getPosition();
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;

    // Init background
    sf::RectangleShape background(sf::Vector2f(gridSizeF, gridSizeF));
    background.setFillColor(sf::Color(255,255,255,50));
    background.setOutlineColor(sf::Color(255,255,255,15));
    background.setOutlineThickness(0.75f);
    sf::RectangleShape separator(sf::Vector2f(1.f, gridSizeF));
    separator.setFillColor(sf::Color(255,255,255,255));

    sf::Text text;
    sf::Font font;
    font.loadFromFile("Fonts/Dosis-Light.otf");
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::White);
    text.setFont(font);
    text.setPosition(20.f, window.getSize().y - 120.f);
    text.setString("Technical Info"); // Will be over-written

    // Init camera (view)
    sf::View view;
    view.setSize(1000.f,800.f);
    view.setCenter(window.getSize().x/2.f,window.getSize().y/2.f);
    float viewSpeed = 200.f;

    // Init game elements
    sf::RectangleShape ship_part(sf::Vector2f(gridSizeF, gridSizeF));
    ship_part.setFillColor(sf::Color(255,255,255,255));
    Ship ships[10];

	sf::RectangleShape test_collision(sf::Vector2f(gridSizeF, gridSizeF));
	test_collision.setFillColor(sf::Color::Red);
	test_collision.setPosition(200.f, window.getSize().y - 120.f);

    while(window.isOpen())
    {
        // Update dt
        dt = dtClock.restart().asSeconds();

        // Update mouse positions
        mousePosScreen = sf::Mouse::getPosition();
        mousePosWindow = sf::Mouse::getPosition(window);
        window.setView(view);
        mousePosView = window.mapPixelToCoords(mousePosWindow);
        if(mousePosView.x >= 0.f)
            mousePosGrid.x = mousePosView.x / gridSizeU;
        if(mousePosView.y >= 0.f)
            mousePosGrid.y = mousePosView.y / gridSizeU;
		/*if (mousePosGrid.x >= 10)
			mousePosGrid.x -= 10;*/

        window.setView(window.getDefaultView());
        
        std::stringstream ss;
        /*ss << "Screen: " << mousePosScreen.x << " " << mousePosScreen.y << "\n"
            << "Window: " << mousePosWindow.x << " " << mousePosWindow.y << "\n"
            << "View: " << mousePosView.x << " " << mousePosView.y << "\n"*/
        ss << "Mouse in Grid: " << mousePosGrid.x << " " << mousePosGrid.y << "\n"
            //<< "Player: " << player.getShip(0).getShipPosition().x << " " << player.getShip(0).getShipPosition().y << "\n"
			<< "Current rotation: " << player.getShip(player.getPlacingShipId()).getShipRotation() << "\n";
        text.setString(ss.str());

        // Events
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();

			if (player.isCurrentlyPlacing()) {
				if (event.type == sf::Event::KeyPressed) {
					if (event.key.code == sf::Keyboard::R) {
						player.setShipRotation();
					}
				}
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Right) {
						player.changePlacingShipId();
					}
					if (event.mouseButton.button == sf::Mouse::Left) {
						player.getShip(player.getPlacingShipId()).set(true, player.getShip(player.getPlacingShipId()).getShipSize(), player.getShip(player.getPlacingShipId()).getShipRotation(), sf::Vector2i(mousePosGrid));
						player.changePlacingShipId(true);
					}
				}
			}
				
        }

        // Update
		if (computer.canPlace(sf::Vector2i(mousePosGrid), 0, 0))
			test_collision.setFillColor(sf::Color::Red);
		else
			test_collision.setFillColor(sf::Color::Green);

        // Update Input
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) // Left
            view.move(-viewSpeed * dt, 0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) // Right
            view.move(viewSpeed * dt, 0.f);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) // Up
            view.move(0.f, -viewSpeed * dt);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) // Down
            view.move(0.f, viewSpeed * dt);

        // Render
        window.clear();
        window.setView(view);

        for (int x = 0; x < 20; x++)
        {
            for (int y = 0; y < 10; y++)
            {
                background.setPosition(x * gridSizeF, y * gridSizeF);
                window.draw(background);
                if (x == 10) {
                    separator.setPosition(x * gridSizeF, y * gridSizeF);
                    window.draw(separator);
                }
            }
        }

        // Render game elements
		for (int i = 0; i < 5; i++) {

			if (computer.getShip(i).getShipPlaced()) {

				for (int s = 0; s <= computer.getShip(i).getShipSize(); s++) {

					switch (computer.getShip(i).getShipRotation()) {
					case 0:
						ship_part.setPosition(sf::Vector2f((
							computer.getShip(i).getShipPosition().x + s)*gridSizeF,
							computer.getShip(i).getShipPosition().y*gridSizeF
						));
						break;
					case 1:
						ship_part.setPosition(sf::Vector2f((
							computer.getShip(i).getShipPosition().x) * gridSizeF,
							(computer.getShip(i).getShipPosition().y + s) * gridSizeF
						));
						break;

					}
					ship_part.setFillColor(sf::Color(255, 0, 0, 125));
					window.draw(ship_part);
				}

			}

			if (player.getShip(i).getShipPlaced()) {

				for (int s = 0; s <= player.getShip(i).getShipSize(); s++) {
					
					switch (player.getShip(i).getShipRotation()) {
					case 0:
						ship_part.setPosition(sf::Vector2f((
							player.getShip(i).getShipPosition().x + s)*gridSizeF,
							player.getShip(i).getShipPosition().y*gridSizeF
						));
						break;
					case 1:
						ship_part.setPosition(sf::Vector2f((
							player.getShip(i).getShipPosition().x) * gridSizeF,
							(player.getShip(i).getShipPosition().y + s) * gridSizeF
						));
						break;

					}
					ship_part.setFillColor(sf::Color(0, 255, 0, 125));
					window.draw(ship_part);
				}

			}

		}
		
		if (player.isCurrentlyPlacing())
		{
			if (mousePosGrid.x > 9 && mousePosGrid.y < 10)
			{
				for (int i = 0; i <= player.getShip(player.getPlacingShipId()).getShipSize(); i++) {
					switch (player.getShip(player.getPlacingShipId()).getShipRotation()) {
					case 0:
						ship_part.setPosition(sf::Vector2f((mousePosGrid.x + i) * gridSizeF, mousePosGrid.y * gridSizeF));
						
					break;
					case 1:
						ship_part.setPosition(sf::Vector2f(mousePosGrid.x * gridSizeF, (mousePosGrid.y + i) * gridSizeF));
					break;

					}
					window.draw(ship_part);
				}
			}
		}

		window.draw(test_collision);

        window.setView(window.getDefaultView());
        // Render UI
        window.draw(text);

        window.display();
    }
    return 0;
}