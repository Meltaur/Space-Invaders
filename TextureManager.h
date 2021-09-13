#pragma once
#include "External.h""
	
class TextureManager {
	private:
		std::map<std::string, sf::Texture> tekstury;
	public:
		TextureManager() {};
		~TextureManager() {};
		void ZaladujTeksture(const std::string& nazwa, const std::string& fileName);
		sf::Texture& GetTexture(const std::string& texture);
};