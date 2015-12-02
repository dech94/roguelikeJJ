#include <game/Action.h>
#include <game/Animation.h>
#include <game/AssetManager.h>
#include <game/Camera.h>
#include <game/Clock.h>
#include <game/Control.h>
#include <game/Entity.h>
#include <game/EntityManager.h>
#include <game/EventManager.h>
#include <game/Id.h>
#include <game/Log.h>
#include <game/Model.h>
#include <game/ModelManager.h>
#include <game/Queue.h>
#include <game/Random.h>
#include <game/ResourceManager.h>
#include <game/Singleton.h>
#include <game/Vector.h>
#include <game/WindowGeometry.h>
#include <game/WindowSettings.h>
#include <local/Noise.h>
#include <local/Heightmap.h>
#include <local/Tilemap.h>
#include <chrono>

int main (void)
{
  game::Log::setLevel(game::Log::DEBUG);

  // initialize
  static constexpr unsigned INITIAL_WIDTH = 50;
  static constexpr unsigned INITIAL_HEIGHT = 50;

  game::WindowSettings settings(INITIAL_WIDTH, INITIAL_HEIGHT, "Game");
  game::WindowGeometry geometry(INITIAL_WIDTH, INITIAL_HEIGHT);

  sf::RenderWindow window;
  settings.applyTo(window);
  window.setKeyRepeatEnabled(false);

  // add actions
  game::ActionManager actions;

  game::Action closeWindowAction("Close window");
  closeWindowAction.addCloseControl();
  closeWindowAction.addKeyControl(sf::Keyboard::Escape);
  actions.addAction(closeWindowAction);

  game::Action fullscreenAction("Fullscreen");
  fullscreenAction.addKeyControl(sf::Keyboard::F);
  actions.addAction(fullscreenAction);

  // Events manager 
  game::EventManager events;

  game::EntityManager mainEntities;

  //Random
	typedef std::chrono::high_resolution_clock myclock;
	myclock::time_point beginning = myclock::now();
	myclock::duration d = myclock::now() - beginning;
	unsigned seed = d.count();
  // map

  local::Heightmap hmap(INITIAL_WIDTH, INITIAL_HEIGHT, seed);
  hmap.Compute();
  local::Tilemap tmap(hmap);
  if (!tmap.load(sf::Vector2u(16,16)))
  {
  	return -1;
  } 
  

  // main loop
  game::Clock clock;
  
//  float lastRender = 0;

  while (window.isOpen()) {
    // input
    sf::Event event;

    while (window.pollEvent(event)) {
      actions.update(event);
      geometry.update(event);
    }

    if (closeWindowAction.isActive()) {
      window.close();
    }

    if (fullscreenAction.isActive()) {
      settings.toggleFullscreen();
      settings.applyTo(window);
      auto sz = window.getSize();

      sf::Event event;
      event.type = sf::Event::Resized;
      event.size.width = sz.x;
      event.size.height = sz.y;
      geometry.update(event);
    }

    // update
    auto elapsed = clock.restart();
    auto dt = elapsed.asSeconds();
    mainEntities.update(dt);
//	if (lastRender - clock.getElapsedTime.asSeconds() > 1/60)
//	{
//		lastRender=clock.getElapsedTime.asSeconds();
		
		// render
    	window.clear();
	
	    mainEntities.render(window);

	    window.draw(tmap);

	    window.display();

	    actions.reset();
//	}
  }

  return 0;
}
