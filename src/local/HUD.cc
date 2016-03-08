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

		m_score = m_sable*50+m_pomme*100+m_trefle*200+m_champi*500;

		if (m_score < 1000){
			m_rang = "Novice";
		}
		else if (m_score >= 1000 && m_score < 2000)
		{
			m_rang = "Apprenti";
		}
		else if (m_score >= 2000 && m_score < 3000)
		{
			m_rang = "Adepte";
		}
		else if (m_score >= 3000 && m_score < 5000)
		{
			m_rang = "Adepte Confirmé";
		}
		else if (m_score >= 5000 && m_score < 7000)
		{
			m_rang = "Membre de l'ordre";
		}
		else if (m_score >= 7000 && m_score < 10000)
		{
			m_rang = "Maitre";
		}
		else if (m_score >= 10000 && m_score < 25000)
		{
			m_rang = "Grand Maitre";
		}
		else if (m_score >= 25000 && m_score < 50000)
		{
			m_rang = "Maitre de l'ordre'";
		}
		else if (m_score >= 50000 && m_score < 100000)
		{
			m_rang = "Prophète";
		}else{
			m_rang = "Dieu féral";
		}
		// choix de la police à utiliser
		text.setFont(m_font); // font est un sf::Font

		// choix de la chaîne de caractères à afficher
		text.setString("Score : "+std::to_string(m_score));

		// choix de la taille des caractères
		text.setCharacterSize(32); // exprimée en pixels, pas en points !

		// choix de la couleur du texte
		text.setColor(sf::Color::Black);

		text.setPosition(charPos.x-1024/2+32,charPos.y-1024/2+32);

		text.setStyle(sf::Text::Bold);

		textRang.setFont(m_font);
		textRang.setString(m_rang);
		textRang.setCharacterSize(32);
		textRang.setPosition(charPos.x-1024/2+32,charPos.y-1024/2+64);
		textRang.setColor(sf::Color::Black);
		textRang.setStyle(sf::Text::Bold);

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
