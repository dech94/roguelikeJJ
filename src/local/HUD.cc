#include "HUD.h"

namespace local {

/*explicit*/HUD::HUD()
	{
		if (!m_font.loadFromFile("bilbo.ttf"))
		{
			
		}
	}

/*virtuel*/HUD::~HUD()
	{
	}

	void HUD::update(sf::Vector2f charPos, int sable, int pomme, int trefle, int champi)
	{
		m_sable += sable;
		m_pomme += pomme;
		m_trefle += trefle;
		m_champi += champi;

		// choix de la police à utiliser
		text.setFont(m_font); // font est un sf::Font

		// choix de la chaîne de caractères à afficher
		text.setString("Rang :");

		// choix de la taille des caractères
		text.setCharacterSize(32); // exprimée en pixels, pas en points !

		// choix de la couleur du texte
		text.setColor(sf::Color::Black);

		text.setPosition(charPos.x-1024/2+32,charPos.y-1024/2+32);

		textS.setFont(m_font);
		textS.setString(std::to_string(m_sable));
		textS.setCharacterSize(32);
		textS.setPosition(charPos.x-1024/2+32*21,charPos.y-1024/2+20);
		textS.setColor(sf::Color::Black);

		textP.setFont(m_font);
		textP.setString(std::to_string(m_pomme));
		textP.setCharacterSize(32);
		textP.setPosition(charPos.x-1024/2+32*24,charPos.y-1024/2+20);
		textP.setColor(sf::Color::Black);

		textT.setFont(m_font);
		textT.setString(std::to_string(m_trefle));
		textT.setCharacterSize(32);
		textT.setPosition(charPos.x-1024/2+32*27,charPos.y-1024/2+20);
		textT.setColor(sf::Color::Black);

		textC.setFont(m_font);
		textC.setString(std::to_string(m_champi));
		textC.setCharacterSize(32);
		textC.setPosition(charPos.x-1024/2+32*30,charPos.y-1024/2+20);
		textC.setColor(sf::Color::Black);

		sprite.setTexture(m_texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 1024, 1024));
		sprite.setPosition(charPos.x-1024/2,charPos.y-1024/2);
	}

	bool HUD::load(std::string tileset)
	{
		//chargement des tiles
		if (!m_texture.loadFromFile(tileset))
		{
			return false;
		}
		return true;
	}
}
