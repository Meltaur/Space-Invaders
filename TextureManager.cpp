#include "External.h""
#include "TextureManager.h"

void TextureManager::ZaladujTeksture(const std::string& nazwa, const std::string& fileName)
{
	sf::Texture tex;
	if (tex.loadFromFile(fileName))
		this->tekstury[nazwa] = tex; //Wkładanie do mapy
}
sf::Texture& TextureManager::GetTexture(const std::string& texture)
{
	return this->tekstury.at(texture); //Wyciąganie tekstury z mapy
}