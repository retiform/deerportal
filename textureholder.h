#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
class TextureHolder
{
public:
    TextureHolder();
    sf::Texture textureTiles;
    sf::Texture textureFaces;
    sf::Texture textureGui;


};

#endif // TEXTUREHOLDER_H