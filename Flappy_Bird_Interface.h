# ifndef FLAPPY_BIRD_INTERFACE_H
# define FLAPPY_BIRD_INTERFACE_H
# include <SFML/Graphics.hpp>
# include <string>

class FlappyBird
{
	public:
		FlappyBird();
		void DesignWindow();
		void GameDriver();
		void GetUserInput();
		void HandlePipe(int i = 1);
		void HandleBird();
		void CheckCollison();
		void GameOver();
	private:
		struct PipeCoord
		{
			int x = 0;
			int y = 0;
		} PipeCoords[2];
		sf::RenderWindow WindowObj;
		sf::Texture Texture1FromFile;
		sf::Texture Texture2FromFile;
		sf::Texture Texture3FromFile;
		sf::Sprite Background;
		sf::Sprite AngryBird;
		sf::Sprite Pipe, Pipe2;
		sf::Font FontFile;
		sf::Text TextFromFontFile;
		sf::Text DisplayMessage;
		sf::Text DisplayScore;
		sf::Clock ClockObj;
		const int ScreenWidth = 1024;
		const int ScreenHeight = 576;
		const int ColScalar = 32;
		const int RowScalar = 32;
		int BirdYCoord = 7;
		int TotalScore = 0;
		int DrawPipe = 1;
		float ScaleY = 1.0;
		float Scale2Y = 0.0;
		int BirdXCoord = 9;
		bool Count = true;
		bool slow = true;
		int time = 700;
};
# endif