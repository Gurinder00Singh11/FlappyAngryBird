# include "Flappy_Bird_Interface.h"
# include <iostream>

using namespace sf;

FlappyBird::FlappyBird()
{
	/* Function to take care of the 
	   designing aspects of the game
	*/
	DesignWindow(); 

	// Main function that will
	// bring everything together
	// (Game logic)
	GameDriver();
}

void FlappyBird::DesignWindow()
{
	// Create game screen
	WindowObj.create
	(VideoMode(ScreenWidth, ScreenHeight), "Flappy Bird");

	// Load pictures that will be used later
	Texture1FromFile.loadFromFile("Background.png");
	Texture2FromFile.loadFromFile("AngryBird2.png");
	Texture3FromFile.loadFromFile("Pipe.png");

	// Create sprites
	Background.setTexture(Texture1FromFile);
	AngryBird.setTexture(Texture2FromFile);
	Pipe.setTexture(Texture3FromFile);
	Pipe2.setTexture(Texture3FromFile);

	// Load fonts
	FontFile.loadFromFile("TryFont.ttf");

	TextFromFontFile.setFont(FontFile);
	TextFromFontFile.setString("Game Over");
	TextFromFontFile.setCharacterSize(96);
	TextFromFontFile.setFillColor(Color::Red);
	TextFromFontFile.setPosition(8 * ColScalar, 7 * RowScalar);
	TextFromFontFile.setStyle(Text::Bold);

	DisplayMessage.setFont(FontFile);
	DisplayMessage.setString("Do you want to Quit (y or n)");
	DisplayMessage.setCharacterSize(32);
	DisplayMessage.setFillColor(Color::Green);
	DisplayMessage.setPosition(11 * ColScalar, 14 * RowScalar);
	DisplayMessage.setStyle(Text::Regular);

	DisplayScore.setFont(FontFile);
	DisplayScore.setCharacterSize(32);
	DisplayScore.setFillColor(Color::Magenta);
	DisplayScore.setPosition(11 * ColScalar, 12 * RowScalar);
	DisplayScore.setStyle(Text::Regular);
}

void FlappyBird::GameDriver()
{
	static int Count = 1;

	// Clear the screen
	WindowObj.clear();

	// Loop that will basically run the
	// entire game
	while (WindowObj.isOpen())
	{
		Event E;
		while (WindowObj.pollEvent(E))
		{
			if (E.type == Event::Closed)
				WindowObj.close();
		}

		////Draw////
		WindowObj.clear();

		WindowObj.draw(Background);

		GetUserInput();

		CheckCollison();

		HandlePipe(TotalScore);

		HandleBird();

		WindowObj.display();

		ClockObj.restart();

		// Wait
		while (ClockObj.getElapsedTime().asMilliseconds() 
			< (time)) { }
		
		// Time is originally set to 700 miliseconds
		// to give the user sometime to interact with
		// the game. After the time passes the game will
		// start and the response time available will be reduced
		// to 100 milliseconds (to make it more challenging :)
		time = 100;

	}
}

void FlappyBird::GetUserInput()
{
	// Check if the user entered the game key (space)
	// if yes then move our angry bird up 2 units
	// else move it down
	if (Keyboard::isKeyPressed(Keyboard::Space))
		BirdYCoord -= 2;
	else
		BirdYCoord += 2;

}

void FlappyBird::HandlePipe(int i)
{
	// This function will control
	// the movement of our obstactle (pipes)
	if (DrawPipe == 1)
	{
		////Pipe 1 Calculations////
		Pipe.setRotation(180);
		PipeCoords[1].x = ColScalar;
		PipeCoords[1].y = rand() % (8 - 5 + 1) + 5;
		ScaleY = float(PipeCoords[1].y) / 5;
		////Pipe 2 Calculations////
		Pipe2.setRotation(0);
		PipeCoords[2].x = ColScalar - 3;
		PipeCoords[2].y = 18 - (rand() % (5 - 2 + 1) + 2);
		Scale2Y = float(18 - (PipeCoords[2].y)) / 5;
	}

	Pipe.setPosition(PipeCoords[1].x-- * ColScalar, 
		PipeCoords[1].y * RowScalar);
	Pipe.setScale(1, ScaleY);

	Pipe2.setPosition(PipeCoords[2].x-- * ColScalar,
		PipeCoords[2].y * RowScalar);
	Pipe2.setScale(1, Scale2Y);

	WindowObj.draw(Pipe);
	WindowObj.draw(Pipe2);

	if (PipeCoords[1].x < 0) DrawPipe = 1;
	else DrawPipe++;
}

void FlappyBird::HandleBird()
{
	// This function will use the input 
	// we recieved from the user and set
	// our bird's location accordingly
	AngryBird.setPosition(BirdXCoord * ColScalar,
		BirdYCoord * RowScalar);
	WindowObj.draw(AngryBird);
}

void FlappyBird::CheckCollison()
{
	// This function will determine whether our bird
	// collided with a pipe or not. If yes then game over.
	if (BirdYCoord >= 0 && BirdYCoord <= (PipeCoords[1].y - 2.5)
		&& (BirdXCoord >= (PipeCoords[1].x - 3.5)
			&& BirdXCoord <= PipeCoords[1].x))
		GameOver();

	else if (BirdYCoord >= (PipeCoords[2].y)
		&& BirdYCoord <= 18 && (BirdXCoord >= PipeCoords[2].x
			&& BirdXCoord <= (PipeCoords[2].x + 3)))
		GameOver();

	else if (BirdYCoord < -2 || BirdYCoord > 20)
		GameOver();

	else if (PipeCoords[1].x == 9)
	{
		if (Count)
			TotalScore++;
		else
			Count = true;
	}

}

void FlappyBird::GameOver()
{
	// This function will handle the situation 
	// when our bird collides with a pipe.
	// This function will also ask the user to 
	// decide whether they want to continue with the game
	// or quit.
	ClockObj.restart();

	while (ClockObj.getElapsedTime().asSeconds() < 2) {  }

	ClockObj.restart();

	DisplayScore.setString(
		"Total Scores: " + std::to_string(TotalScore));

	while (ClockObj.getElapsedTime().asSeconds() < 10)
	{
		WindowObj.clear();
		WindowObj.draw(TextFromFontFile);
		WindowObj.draw(DisplayMessage);
		WindowObj.draw(DisplayScore);
		WindowObj.display();

		if (Keyboard::isKeyPressed(Keyboard::N))
		{
			TotalScore = 0; BirdXCoord = 9; BirdYCoord = 7;
			Count = false; time = 700;  GameDriver();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Y))
			_Exit(100);
	}

	_Exit(100);
}