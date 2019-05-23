#include <sstream>

#include "Player.h"
#include "Computer.h"
#include "Game_engine.h"

int main()
{
	Game_engine game;
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

	// Init all texts
    sf::Text technical_data,
			game_title,
			player_text,
			information_text;

    sf::Font font;
    font.loadFromFile("Fonts/Dosis-Light.otf");
	technical_data.setFont(font);
	game_title.setFont(font);
	player_text.setFont(font);
	information_text.setFont(font);

    technical_data.setCharacterSize(20);
    technical_data.setFillColor(sf::Color::White);
    technical_data.setPosition(6.f, gridSizeF*10.f + 35.f);
    technical_data.setString("Technical Info"); // Will be over-written

	game_title.setCharacterSize(30);
	game_title.setFillColor(sf::Color::White);
	game_title.setString("Sidicers Battleship Game");
	game_title.setPosition(6.f, gridSizeF*10.f);

	player_text.setCharacterSize(30);
	player_text.setFillColor(sf::Color::White);
	player_text.setPosition(gridSizeF*10.f + 10.f, gridSizeF*10.f);
	player_text.setString("Player area");

	information_text.setCharacterSize(20);
	information_text.setFillColor(sf::Color::White);
	information_text.setPosition(gridSizeF*10.f + 10.f, gridSizeF*10.f + 35.f);
	information_text.setString("Player is placing the ships");

    // Init camera (view)
    sf::View view;
    view.setSize(1000.f,800.f);
    view.setCenter(window.getSize().x/2.f,window.getSize().y/2.f);
    float viewSpeed = 200.f;

    // Init game elements
    sf::RectangleShape ship_part(sf::Vector2f(gridSizeF, gridSizeF));
    ship_part.setFillColor(sf::Color(255,255,255,255));
	Ship ships[10];
	
	sf::RectangleShape hit_part(sf::Vector2f(gridSizeF, gridSizeF));
	hit_part.setFillColor(sf::Color::Red);
	hit_part.setPosition(sf::Vector2f(-1.f * gridSizeF, -1.f * gridSizeF));

	sf::RectangleShape miss_part(sf::Vector2f(gridSizeF, gridSizeF));
	miss_part.setFillColor(sf::Color(0,0,255,125));
	miss_part.setPosition(sf::Vector2f(-1.f * gridSizeF, -1.f * gridSizeF));

	sf::RectangleShape test_collision(sf::Vector2f(gridSizeF, gridSizeF));
	test_collision.setFillColor(sf::Color::Red);
	test_collision.setPosition(6.f, gridSizeF*10.f + 90.f);

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
			<< "Current rotation: " << player.getShip(player.getPlacingShipId()).getShipRotation() << "\n"
			<< "Hit ships: " << game.getHit().size() << "\n"
			<< "Missed ships: " << game.getMiss().size() << "\n"
			<< "Player hits: " << player.hitCount() << "\n"
			<< "Computer hits: " << computer.hitCount() << "\n";
		technical_data.setString(ss.str());

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
						if (player.canPlace(
							sf::Vector2i(mousePosGrid),
							player.getShip(player.getPlacingShipId()).getShipSize(),
							player.getShip(player.getPlacingShipId()).getShipRotation()) &&
						!player.outOfBounds(
							sf::Vector2i(mousePosGrid),
							player.getShip(player.getPlacingShipId()).getShipSize(),
							player.getShip(player.getPlacingShipId()).getShipRotation())
						) {
							player.getShip(player.getPlacingShipId()).set(true, player.getShip(player.getPlacingShipId()).getShipSize(), player.getShip(player.getPlacingShipId()).getShipRotation(), sf::Vector2i(mousePosGrid));
							player.changePlacingShipId(true);
						}
					}
				}
			}
			else {
				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						if (game.whoIsShooting()) {
							player.shoot(computer, sf::Vector2i(mousePosGrid), game);
							game.whoIsShooting(true);
						}
					}
				}
			}
				
        }


        // Update
		if (!computer.canPlace(sf::Vector2i(mousePosGrid), 0, 0))
			test_collision.setFillColor(sf::Color::Red);
		else if (!player.canPlace(sf::Vector2i(mousePosGrid), 0, 0))
			test_collision.setFillColor(sf::Color::Blue);
		else
			test_collision.setFillColor(sf::Color::Green);

		if (!player.isCurrentlyPlacing()) {
			
			if (game.whoIsShooting() == 0) {
				information_text.setString("Computer is shooting");
				if(computer.shoot(player, game))
					game.whoIsShooting(true);
			}
			else {
				information_text.setString("Player is shooting");
			}
			
		}

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
		if (player.hitCount() < 17) {

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
						ship_part.setFillColor(sf::Color(255, 0, 0, 10));
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
						ship_part.setFillColor(sf::Color::Red);
						window.draw(ship_part);
					}
				}
			}

			for (size_t i = 0; i < game.getHit().size(); i++)
			{
				hit_part.setPosition(sf::Vector2f(game.getHit()[i].x*gridSizeF, game.getHit()[i].y*gridSizeF));
				window.draw(hit_part);
			}

			for (size_t i = 0; i < game.getMiss().size(); i++)
			{
				miss_part.setPosition(sf::Vector2f(game.getMiss()[i].x*gridSizeF, game.getMiss()[i].y*gridSizeF));
				window.draw(miss_part);
			}

			window.setView(window.getDefaultView());
			// Render UI
			window.draw(technical_data);
			window.draw(game_title);
			window.draw(player_text);
			window.draw(information_text);

			window.display();
		} else {
			window.clear();
			game_title.setCharacterSize(50);
			game_title.setPosition(sf::Vector2f(window.getSize().x / 2 - 175.f, window.getSize().y / 2 - 50.f));
			game_title.setString("YOU WON, PLAYER!");
			window.draw(game_title);
			window.display();
		}
    }
    return 0;
}