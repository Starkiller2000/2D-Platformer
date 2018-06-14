// 2DPlatformer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Player.h"
#include "Map.h"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>


int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Platformer");
	window.setFramerateLimit(144);

	sf::Sprite playerSprite;

	std::vector <sf::Texture> idleAnimation(10);
	std::vector <sf::Texture> walkingAnimation(10);
	std::vector <sf::Texture> jumpingAnimation(10);
	
	//Debugging
	bool jumpVariable;

	Map map;

	std::vector<sf::RectangleShape> blockArray = map.DrawMap();
	std::vector<sf::FloatRect> blockBoundingBox = map.MapBoundingBox();

	sf::Vector2f playerStart = map.PlayerStart();

	sf::View view;
	view.setSize(1920, 1080);
	view.setCenter(playerStart.x, playerStart.y);
	window.setView(view);

	Player player(playerSprite, playerStart);
	player.textureInit(idleAnimation, walkingAnimation, jumpingAnimation);

	sf::Clock clock;
	sf::Clock frameTime;
	float lastTime = 0;

	sf::Font font;
	if (!font.loadFromFile("Fonts/HVR.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(16);
	text.setFillColor(sf::Color::White);

	sf::Text debugText;
	debugText.setFont(font);
	debugText.setCharacterSize(16);
	debugText.setFillColor(sf::Color::White);
	debugText.setPosition(200, 0);


	////draw level
	//const int levelWidth = 5;
	//const int levelHeight = 5;

	//int levelArray[levelHeight][levelWidth] = {
	//{ 1, 1, 1, 1, 1 },
	//{ 1, 1, 1, 1, 1 },
	//{ 1, 1, 1, 1, 1 },
	//{ 1, 1, 1, 1, 1 },
	//{ 1, 1, 1, 1, 1 } };
	//std::vector<sf::RectangleShape> blockArray;
	//std::vector<sf::FloatRect> blockBoundingBox;
	//int Xoffset = 200;
	//int Yoffset = 50;

	//for (int y = 0; y < levelHeight; y++)
	//{
	//	for (int x = 0; x < levelWidth; x++)
	//	{
	//		sf::RectangleShape block(sf::Vector2f(200.f, 50.f));
	//		block.setPosition(x * Xoffset, 600 + (y * Yoffset));
	//		sf::FloatRect boxCollision = block.getGlobalBounds();
	//		blockBoundingBox.push_back(boxCollision);
	//		blockArray.push_back(block);
	//	}
	//}

	//playerSprite.setOrigin(playerSprite.getTextureRect().width / 2, playerSprite.getTextureRect().height / 2);
	
	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(visibleArea));
			}

		}
		playerSprite = player.playerSpriteUpdate(playerSprite, idleAnimation, walkingAnimation, jumpingAnimation, deltaTime, playerSprite.getOrigin());


		//debug
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
		{
			playerSprite.setPosition(map.PlayerStart());
		}
		

		sf::Vertex topLine[3][2] =
		{
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + 50)),

			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width + 35) / 2, playerSprite.getPosition().y)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width + 35) / 2, playerSprite.getPosition().y + 50)),

			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width  - 25) / 2, playerSprite.getPosition().y)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width - 25) / 2, playerSprite.getPosition().y + 50))
		};
		sf::Vertex bottomLine[3][2] =
		{
			//Middle Bottom Line
			{sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + 95))},
			//Middle Right Line
			{ sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width + 35) / 2, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width + 35) / 2, playerSprite.getPosition().y + 95)) },
			//Middle Left Line
			{ sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width - 25) / 2, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + (playerSprite.getGlobalBounds().width - 25) / 2, playerSprite.getPosition().y + 95)) },

		};
		sf::Vertex rightLine[3][2] =
		{
			//Middle Right Line
			{sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2))},
			//Bottom Right Line
			{ sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height + 50) / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width, playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height + 50) / 2)) },
			//Top Right Lin
			{ sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height - 35) / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width, playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height - 35) / 2)) },
		};
		sf::Vertex leftLine[3][2] =
		{
			//Middle Left Line
			{sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x - (playerSprite.getGlobalBounds().width - 80), playerSprite.getPosition().y + playerSprite.getGlobalBounds().height / 2))},
			//Bottom Left Line
			{ sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height + 50) / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x - (playerSprite.getGlobalBounds().width - 80), playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height + 50) / 2)) },
			//Top Left Line
			{ sf::Vertex(sf::Vector2f(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height - 35) / 2)),
			sf::Vertex(sf::Vector2f(playerSprite.getPosition().x - (playerSprite.getGlobalBounds().width - 80), playerSprite.getPosition().y + (playerSprite.getGlobalBounds().height - 35) / 2)) },

		};

		player.Update(playerSprite, deltaTime, blockArray, playerSprite.getOrigin(), bottomLine, rightLine, leftLine, topLine, jumpVariable);

		float currentTime = frameTime.restart().asSeconds();
		int fps = 1.f / currentTime;
		lastTime = currentTime;
		
		
		//playerSprite.setOrigin(playerSprite.getTextureRect().width / 2, playerSprite.getTextureRect().height / 2);
		text.setString(std::to_string(fps));
		text.setPosition(view.getCenter().x - (window.getSize().x / 2), view.getCenter().y - (window.getSize().y / 2));
		debugText.setString(std::to_string(jumpVariable));
		/*sf::IntRect debugRect = playerSprite.getTextureRect();
		sf::RectangleShape debugRectangle(sf::Vector2f(debugRect.left, debugRect.top));
		debugRectangle.setFillColor(sf::Color::Green);*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		{
			view.zoom(1.1f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		{
			view.zoom(0.9f);
		}
		view.setCenter(playerSprite.getPosition().x, playerSprite.getPosition().y);

		window.clear();
		window.draw(playerSprite);
		window.draw(topLine[0], 2, sf::Lines);
		window.draw(topLine[1], 2, sf::Lines);
		window.draw(topLine[2], 2, sf::Lines);
		window.draw(bottomLine[0], 2, sf::Lines);
		window.draw(bottomLine[1], 2, sf::Lines);
		window.draw(bottomLine[2], 2, sf::Lines);
		window.draw(rightLine[0], 2, sf::Lines);
		window.draw(rightLine[1], 2, sf::Lines);
		window.draw(rightLine[2], 2, sf::Lines);
		window.draw(leftLine[0], 2, sf::Lines);
		window.draw(leftLine[1], 2, sf::Lines);
		window.draw(leftLine[2], 2, sf::Lines);
		window.draw(text);
		window.draw(debugText);
		for (int i = 0; i < blockArray.size(); i++)
		{
			window.draw(blockArray[i]);
		}
		window.setView(view);
		window.display();
	}

	return 0;
}