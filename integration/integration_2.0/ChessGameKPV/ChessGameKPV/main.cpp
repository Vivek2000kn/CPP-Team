#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>

#include"BL.h"

using namespace std;

const int SQUARE_SIZE = 100; // Size of squares on the board

class Button {
private:
    sf::RectangleShape m_shape;
    sf::Text m_text;
public:
    static int userSelectedChessBoard;
    //Calling Button Constructor
    Button(float x, float y, float width, float height, std::string text, sf::Font& font)
        : m_shape(sf::Vector2f(width, height)), m_text(text, font, 20) {
        m_shape.setPosition(x, y);      //Position of the button on window
        m_shape.setFillColor(sf::Color(184, 134, 11));  // Color of the button
        m_shape.setOutlineThickness(2);         //Border of the Button
        m_shape.setOutlineColor(sf::Color::Black);      //Color of the Border

        m_text.setPosition(x + (width - m_text.getLocalBounds().width) / 2, y + (height - m_text.getLocalBounds().height) / 2);  //Setting the Text to display on the center of the button
        m_text.setFillColor(sf::Color::Black);      //Color of the Button Text

    }

    const void draw(sf::RenderWindow& window) {
        window.draw(m_shape);
        window.draw(m_text);
    }

    bool isMouseOver(sf::RenderWindow& window) {
        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
        sf::FloatRect buttonBounds = m_shape.getGlobalBounds();

        return buttonBounds.contains(mousePosition);
    }
};
int Button::userSelectedChessBoard = 0;

//Chess Board
static int drawChessBoard() {

    prediction obj1;        //ghostChecker();
    prediction obj2;       

    recoderClass obj3;

    checkerClass obj4;
    checkerClass obj5;

    int* gh;

    static GAMESTATUS winStatus = PLAY;


    int BOARD_SIZE;
    BOARD_SIZE = Button::userSelectedChessBoard;        //Initializing Board size

    sf::RenderWindow window(sf::VideoMode(BOARD_SIZE * SQUARE_SIZE, BOARD_SIZE * SQUARE_SIZE), "Chess Board");

    vector<sf::Vector2f> visited;       //Creating Vector to track visited square
    // Loading Image to mark visted square
    sf::Texture visit;
    if (!visit.loadFromFile("vis.png"))
    {
        return 1;
    }

    //Display visit Image
    sf::Sprite check(visit);
    check.setScale((SQUARE_SIZE) / check.getLocalBounds().width, (SQUARE_SIZE) / check.getLocalBounds().height);


    // Loading Kinght image
    sf::Texture pawn;
    if (!pawn.loadFromFile("Knight.png"))
    {
        return 1;
    }

    //Display Knight Image
    sf::Sprite sprite(pawn);
    sprite.setScale(SQUARE_SIZE / sprite.getLocalBounds().width, SQUARE_SIZE / sprite.getLocalBounds().height);
    sprite.setPosition(0, 0);       //Initial Position of Knight
    visited.push_back(sf::Vector2f(0,0));       //Mark as visited
    
    //Loading Image for Loss
    sf::Texture lost;
    if (!lost.loadFromFile("gameOver.jpg"))
    {
        cout << "Failed";
        return 1;
    }

    //Display Image when you Loss
    sf::Sprite over;
    over.setTexture(lost);
    over.setScale(BOARD_SIZE*SQUARE_SIZE / over.getLocalBounds().width, BOARD_SIZE*SQUARE_SIZE / over.getLocalBounds().height);

    //Loading Image for Win
    sf::Texture win;
    if (!win.loadFromFile("won.jpg"))
    {
        cout << "Failed";
        return 1;
    }

    //Display Image when you Win
    sf::Sprite cong;
    cong.setTexture(lost);
    cong.setScale(BOARD_SIZE * SQUARE_SIZE / cong.getLocalBounds().width, BOARD_SIZE * SQUARE_SIZE / cong.getLocalBounds().height);
    
    //Sound when u click valid position
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("click.wav")) {
        return 1;
    }

    sf::Sound sound;
    sound.setBuffer(buffer);

    //Sound when u click valid position
    sf::SoundBuffer buffer1;
    if (!buffer1.loadFromFile("fail.wav")) {
        return 1;
    }
    sf::Sound sound1;
    sound1.setBuffer(buffer1);

    /*-----------------BL START --------------------*/
    moveDefaulter();
    obj1.ghostMoves(0, 0, BOARD_SIZE, obj2, obj3);
    obj3.recoder(0);
    /*-----------------BL END --------------------*/

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            //click event
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sound.play();

                    //user ip----------------//
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int gridX = mousePos.x / SQUARE_SIZE;       //current position of the pawn
                    int gridY = mousePos.y / SQUARE_SIZE;       //current position of the pawn
                    //user ip end------------//

                    //check the validity of the clicked positions;

                    /*-----------------BL START --------------------*/

                    if (obj1.ghostChecker(gridY, gridX) == STATUS_OK && obj4.repeaterChecker((gridY * 10) + gridX, BOARD_SIZE, obj5) == STATUS_OK)
                    {
                        visited.push_back(sf::Vector2f(gridX*SQUARE_SIZE, gridY*SQUARE_SIZE));      //Storing current position when mouse in clicked
                        obj1.ghostMoves(gridY, gridX, BOARD_SIZE, obj2, obj3);
                        sprite.setPosition(gridX * SQUARE_SIZE, gridY * SQUARE_SIZE);       //Current position of the pawn
                    }
                    else
                    {
                        sound1.play();
                        cout << "Invalid Move\n";
                    }
                    /*-----------------BL END --------------------*/

                }
            }
        }
        window.clear();

        sf::RectangleShape square(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));

        bool isWhite = true;
        for (int i = 0; i < BOARD_SIZE; ++i) {
            isWhite = (i % 2 == 0);
            for (int j = 0; j < BOARD_SIZE; ++j) {
                square.setFillColor(isWhite ? sf::Color::White : sf::Color(139, 69, 19));
                square.setPosition(i * SQUARE_SIZE, j * SQUARE_SIZE);
                window.draw(square);
                isWhite = !isWhite;
            }
            for (const auto& position : visited) {
                check.setPosition(position);
                window.draw(check);
            }
            window.draw(sprite);
            isWhite = !isWhite; // Start each row with the opposite color 

        }
        winStatus = obj5.stopper(BOARD_SIZE);        //win OR loss;
        if (winStatus == PLAY)
        {
            cout << "PLAY\n";
        }
        else if (winStatus == LOSS)
        {
            window.draw(over);
            cout << "YOU LOST!!!\n";

        }
        else {
            window.draw(cong);
            cout << "You won\n";

        }
            

        window.display();
    }
    return 0;
}
int main() {
    //Declare and Create the Render window
    sf::RenderWindow window(sf::VideoMode(800, 500), "SFML Home");

    //Image 
    sf::Texture bgImage;
    if (!bgImage.loadFromFile("bg.png"))
    {
        cout << "Failed";
        return 1;
    }

    //Sprite for the image
    sf::Sprite bgSprite;
    bgSprite.setTexture(bgImage);

    //Font to load text
    sf::Font font;
    if (!font.loadFromFile("SHOWG.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    //Label
    sf::Text label;
    label.setFont(font);
    label.setString("START  THE  GAME ..!");
    label.setCharacterSize(40);
    label.setFillColor(sf::Color::Black);
    label.setPosition(200, 50);

    //Button instance and properties
    Button button1(180, 150, 150, 50, "4 * 4", font);
    Button button2(450, 150, 150, 50, "5 * 5", font);
    Button button3(180, 250, 150, 50, "6 * 6", font);
    Button button4(450, 250, 150, 50, "7 * 7", font);
    Button button5(250, 350, 300, 50, "8 * 8", font);

    //Background Music for Home screen
    sf::Music music;
    if (!music.openFromFile("music1.mpeg")) {
        return 1;
    }
    music.play();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonReleased:
                if (button1.isMouseOver(window)) {
                    Button::userSelectedChessBoard = 4;
                    music.stop();
                    window.close();
                }
                else if (button2.isMouseOver(window)) {
                    Button::userSelectedChessBoard = 5;
                    music.stop();
                    window.close();
                }
                else if (button3.isMouseOver(window)) {
                    Button::userSelectedChessBoard = 6;
                    music.stop();
                    window.close();
                }
                else if (button4.isMouseOver(window)) {
                    Button::userSelectedChessBoard = 7;
                    music.stop();
                    window.close();
                }
                else if (button5.isMouseOver(window)) {
                    Button::userSelectedChessBoard = 8;
                    music.stop();
                    window.close();
                }
                break;
            }
        }

        window.clear();
        window.draw(bgSprite);
        window.draw(label);
        button1.draw(window);
        button2.draw(window);
        button3.draw(window);
        button4.draw(window);
        button5.draw(window);
        window.display();


    }
    drawChessBoard();

    return 0;
}