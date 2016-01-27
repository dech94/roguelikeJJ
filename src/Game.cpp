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
#include <local/Background.h>
#include <local/Obstaclemap.h>
#include <local/Character.h>
#include <chrono>
#include <stdio.h>
#include <cmath>

int main (void)
{
  game::Log::setLevel(game::Log::DEBUG);

  // initialize
  static const int HMAP_WIDTH = 1000;
  static const int HMAP_HEIGHT = 1000;
  static const int MARGEX = HMAP_WIDTH*32 - 1000;
  static const int MARGEY = HMAP_HEIGHT*32 -1000;

  game::WindowSettings settings( 1024, 1024, "Game");
  game::WindowGeometry geometry( 1024, 1024);

  sf::RenderWindow window;
  settings.applyTo(window);
  window.setKeyRepeatEnabled(false);
  
  //add view
  int posCamX = HMAP_WIDTH*32/2;
  int posCamY = HMAP_HEIGHT*32/2;
  sf::View gameView(sf::Vector2f(HMAP_WIDTH*32/2, HMAP_HEIGHT*32/2), sf::Vector2f(1024, 1024));
  sf::View minimapView(sf::Vector2f(HMAP_WIDTH*32/2, HMAP_HEIGHT*32/2), sf::Vector2f(100*32, 100*32));
  //view.zoom(0.1f);
  // la vue de jeu (toute la fenêtre)
	gameView.setViewport(sf::FloatRect(0, 0, 1, 1));

	// la mini-carte (dans un coin en haut à droite)
	minimapView.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));

  // add actions
  game::ActionManager actions;

  game::Action closeWindowAction("Close window");
  closeWindowAction.addCloseControl();
  closeWindowAction.addKeyControl(sf::Keyboard::Escape);
  actions.addAction(closeWindowAction);

  game::Action fullscreenAction("Fullscreen");
  fullscreenAction.addKeyControl(sf::Keyboard::F);
  actions.addAction(fullscreenAction);
  
    game::Action moveUP("Move UP");
  moveUP.addKeyControl(sf::Keyboard::Z);
  moveUP.setContinuous();
  actions.addAction(moveUP);

  game::Action moveDown("Move Down");
  moveDown.addKeyControl(sf::Keyboard::S);
  moveDown.setContinuous();
  actions.addAction(moveDown);

  game::Action moveLeft("Move Left");
  moveLeft.addKeyControl(sf::Keyboard::Q);
  moveLeft.setContinuous();
  actions.addAction(moveLeft);

  game::Action moveRight("Move Right");
  moveRight.addKeyControl(sf::Keyboard::D);
  moveRight.setContinuous();
  actions.addAction(moveRight);

  game::Action getPosition("Get Position");
  getPosition.addKeyControl(sf::Keyboard::R);
  getPosition.setContinuous();
  actions.addAction(getPosition);




  // Events manager 
  game::EventManager events;

  game::EntityManager mainEntities;

  //Random
	typedef std::chrono::high_resolution_clock myclock;
	myclock::time_point beginning = myclock::now();
	myclock::duration d = myclock::now() - beginning;
	unsigned seed = d.count();
  // map

  local::Heightmap hmap(HMAP_WIDTH, HMAP_HEIGHT, seed);
  hmap.Compute();
  local::Background tmap(hmap);
  local::Obstaclemap omap(hmap);
  if (!tmap.load(sf::Vector2u(32,32), "tile.png"))
  {
  	return -1;
  } 

  if (!omap.load(sf::Vector2u(32,32), "map.png"))
  {
  	return -1;
  } 

  //Character
  local::Character perso(posCamX, posCamY);
  if (!perso.load(sf::Vector2u(32,32), "perso.png"))
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
        // Check move of view
	if (moveUP.isActive()) {
		perso.move(0,MARGEX,MARGEY);
		printf("%f : %f\n",perso.getPosition().x,perso.getPosition().y);
	}
	if (moveDown.isActive()) {
		perso.move(1,MARGEX,MARGEY);
		printf("%f : %f\n",perso.getPosition().x,perso.getPosition().y);
	}
	if (moveLeft.isActive()) {
		perso.move(2,MARGEX,MARGEY);
		printf("%f : %f\n",perso.getPosition().x,perso.getPosition().y);
	}
	if (moveRight.isActive()) {
		perso.move(3,MARGEX,MARGEY);
		printf("%f : %f\n",perso.getPosition().x,perso.getPosition().y);
	}

	if (getPosition.isActive()) {
		printf("Position : \n - X : %f\n -Y : %f\n\n", perso.getPosition().x, perso.getPosition().y);
	}

	gameView.setCenter(perso.getPosition());



    // update
    auto elapsed = clock.restart();
    auto dt = elapsed.asSeconds();

    mainEntities.update(dt);

		tmap.update(sf::Vector2u(32,32), perso.getPosition().x, perso.getPosition().y);
		omap.update(sf::Vector2u(32,32), perso.getPosition().x, perso.getPosition().y);
		perso.update(sf::Vector2u(32,32), perso.getPosition().x, perso.getPosition().y);


    	window.clear();
	
		
	    window.draw(tmap);
	    window.draw(omap);

	    window.draw(perso.spritePerso);
	    
	    mainEntities.render(window);

	    window.setView(gameView);
	    //window.setView(minimapView);

	    window.display();

	    actions.reset();
//	}
  }

  return 0;
}
