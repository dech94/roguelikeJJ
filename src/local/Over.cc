#include "Over.h"

namespace local {

/*explicit*/Over::Over()
	{
	}

/*virtuel*/Over::~Over()
	{
	}

	void Over::update(sf::Vector2f charPos)
	{
		sprite.setTexture(m_texture);
		sprite.setTextureRect(sf::IntRect(0, 0, 1024, 1024));
		sprite.setPosition(charPos.x-1024/2,charPos.y-1024/2);
	}

	bool Over::load(std::string tileset)
	{
		//chargement des tiles
		if (!m_texture.loadFromFile(tileset))
		{
			return false;
		}
		return true;
	}
}
