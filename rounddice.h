#ifndef ROUNDDICE_H
#define ROUNDDICE_H
#include <random>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "playerhud.h"



class RoundDice
{
public:
    explicit RoundDice(Player (&players)[4]);
    Player *playersHud;


    std::string drawRound();
    int diceResult;
    int diceResultSix;
    int throwDiceSix();
    sf::Texture textureDice;
    sf::Sprite spriteDice;
    void setDiceTexture();
    void setDiceTexture(int diceResult);

    void setColor(int playerNumber);

private:
    int throwDice();


    int diceSize;

//    void eventExtraCash();

    sf::SoundBuffer sfxDiceBuffer;
    sf::Sound sfxDice;

};

#endif // ROUNDDICE_H
