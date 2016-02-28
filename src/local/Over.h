#ifndef OVER_H
#define OVER_H

#include <game/Entity.h>
#include <SFML/Graphics.hpp>

namespace local{
	class Over
	{
	public:
		explicit Over();
		virtual ~Over();
		void update(sf::Vector2f charPos);
		bool load(std::string tileset);
		sf::Sprite sprite;
		sf::Texture m_texture;

	private:
	};
}

#endif //OVER_H
