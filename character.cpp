#include "character.h"


void Character::setDir(int direction)
{
    if (direction==efc::DIR_LEFT)
        currentAnimation = &walkingAnimationLeft;
}



void Character::setDir()
{
    setDir(currentAnimationIndex);
}

void Character::setDirIndex(int direction)
{
    currentAnimationIndex = direction;
}


void Character::play()
{
    //    animatedSprite.play(*currentAnimation);
    animatedSprite.play(animations[currentAnimationIndex]);
    sf::Vector2f a(getPosition());
    sf::Vector2i position(efc::getCords(a));

//    std::cout << a.x << "    " << a.y << "           "
//              << position.x << "       " << position.y << " pos > "
//              << getBoardPosition() << std::endl;
}

Character::Character(TextureHolder *textures, int playerNumber):
    animatedSprite(sf::seconds(0.2), true, false),
    nextRedirect(0.f)

{

    this->textures = textures;
    int offset = playerNumber*16;

    walkingAnimationDown.setSpriteSheet(textures->textureCharacters);
    walkingAnimationDown.addFrame(sf::IntRect(offset, 0, 16, 24));
    walkingAnimationDown.addFrame(sf::IntRect(offset, 23, 16, 24));

    walkingAnimationRight.setSpriteSheet(textures->textureCharacters);
    walkingAnimationRight.addFrame(sf::IntRect(offset, 48, 16, 24));
    walkingAnimationRight.addFrame(sf::IntRect(offset, 72, 16, 24));

    walkingAnimationLeft.setSpriteSheet(textures->textureCharacters);
    walkingAnimationLeft.addFrame(sf::IntRect(offset, 96, 16, 24));
    walkingAnimationLeft.addFrame(sf::IntRect(offset, 120, 16, 24));

    walkingAnimationUp.setSpriteSheet(textures->textureCharacters);
    walkingAnimationUp.addFrame(sf::IntRect(offset, 144, 16, 24));
    walkingAnimationUp.addFrame(sf::IntRect(offset, 168, 16, 24));

    currentAnimation = &walkingAnimationRight;


    animations[efc::DIR_LEFT] = walkingAnimationLeft;
    animations[efc::DIR_RIGHT] = walkingAnimationRight;
    animations[efc::DIR_UP] = walkingAnimationUp;
    animations[efc::DIR_DOWN] = walkingAnimationDown;


    setDirIndex(efc::DIR_LEFT);
    setDir();

    sf::Vector2f positions[4] = {
        sf::Vector2f(0, 0),
        sf::Vector2f(20, 40),
        sf::Vector2f(20, 240),
        sf::Vector2f(40, 240)
    };

    std::array<int, 4> boardPositions{0,15,255-15,255};
//    std::cout << "define " << playerNumber << std::endl;
    setBoardPosition(boardPositions[playerNumber]);


}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    states.transform *= getTransform();
    target.draw(animatedSprite, states);

}

void Character::update(sf::Time deltaTime, std::set<int> &busyTiles)
{



    sf::Vector2f a(getPosition());
    sf::Vector2i position(efc::getCords(a));

    int charPos = efc::transCords(position);

//    std::cout << a.x << " " << a.y << " " << position.x << " " << position.y << " " << charPos << std::endl;

    nextRedirect -= deltaTime.asSeconds();

    if (nextRedirect<0)
    {
        int number = rand() % 2;
        if ((currentAnimationIndex==efc::DIR_LEFT) || (currentAnimationIndex==efc::DIR_RIGHT))
        {
            if (number==0){
                setDirIndex(efc::DIR_DOWN);
                setDir();
            } else if (number==1)
            {
                setDirIndex(efc::DIR_UP);
                setDir();
            }
        } else if ((currentAnimationIndex==efc::DIR_UP) || (currentAnimationIndex==efc::DIR_DOWN))
        {
            if (number==0){
                setDirIndex(efc::DIR_LEFT);
                setDir();
            } else if (number==1)
            {
                setDirIndex(efc::DIR_RIGHT);
                setDir();
            }
        }

        nextRedirect = rand() % 4;

    }

    if (currentAnimationIndex==efc::DIR_UP)
    {
        if (position.y<2)
        {
            setDirIndex(efc::DIR_DOWN);
            setDir();
        }
    }  else   if (currentAnimationIndex==efc::DIR_DOWN)
    {
        if (position.y>efc::BOARD_SIZE-1)
        {
            setDirIndex(efc::DIR_UP);
            setDir();
        }
    } else   if (currentAnimationIndex==efc::DIR_LEFT)
    {

        if (position.x<2)
        {
            setDirIndex(efc::DIR_RIGHT);
            setDir();
        }
    }  else   if (currentAnimationIndex==efc::DIR_RIGHT)
    {
        if (position.x>efc::BOARD_SIZE-1)
        {
            setDirIndex(efc::DIR_LEFT);
            setDir();
        }
    }
    animatedSprite.update(deltaTime);
}

sf::FloatRect Character::getLocalBounds() const
{

    return sf::FloatRect(0.f, 0.f, 0, 0);
}

sf::FloatRect Character::getGlobalBounds() const
{
    return getTransform().transformRect(getLocalBounds());
}

/*!
 * \brief Character::getBoardPosition
 * \return
 */
int Character::getBoardPosition()
{
    sf::Vector2f currentPos(getPosition());
    sf::Vector2i currentCords(efc::getCords(currentPos));
    int currentBoardPosition = efc::transCords(currentCords);
    return currentBoardPosition;
}

/*!
 * \brief Character::setBoardPosition
 * \param boardPosition
 */
void Character::setBoardPosition(int boardPosition)
{
    sf::Vector2i neededCords(efc::transPosition(boardPosition));

    sf::Vector2f newPos(efc::getScreenPos(neededCords));
    std::cout << "board pos >> " << boardPosition << " cords >>" << neededCords.x << " "   << neededCords.y
              << "newpos >> " << newPos.x << " " << newPos.y
              << std::endl;
    setPosition(newPos.x, newPos.y);

}


