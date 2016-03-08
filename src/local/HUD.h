#ifndef HUD_H
#define HUD_H

#include <game/Entity.h>
#include <SFML/Graphics.hpp>

namespace local{
	class HUD
	{
	public:
		explicit HUD();
		virtual ~HUD();
		void update(sf::Vector2f charPos,int sable, int pomme, int trefle, int champi);
		bool load(std::string tileset);
		sf::Sprite sprite;
		sf::Texture m_texture;
		sf::Text text;
		sf::Text textRang;
		sf::Text textS;
		sf::Text textP;
		sf::Text textT;
		sf::Text textC;

	private:
		int m_sable;
		int m_pomme;
		int m_trefle;
		int m_champi;
		int m_score;
		std::string m_rang;
		sf::Font m_font;
	};
}

#endif //HUD_H
