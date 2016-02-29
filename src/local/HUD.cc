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
		m_sable = sable;
		m_pomme = pomme;
		m_trefle = trefle;
		m_champi = champi;

		// choix de la police à utiliser
		text.setFont(m_font); // font est un sf::Font

		// choix de la chaîne de caractères à afficher
		text.setString("Rand :");

		// choix de la taille des caractères
		text.setCharacterSize(32); // exprimée en pixels, pas en points !

		// choix de la couleur du texte
		text.setColor(sf::Color::Black);

		text.setPosition(charPos.x-1024/2+32,charPos.y-1024/2+32);

		// choix du style du texte
		text.setStyle(sf::Text::Bold | sf::Text::Underlined);
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
