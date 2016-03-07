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
#include <local/Rewardmap.h>
#include <local/Character.h>
#include <local/Ennemy.h>
#include <local/Over.h>
#include <local/HUD.h>
#include<local/Wave.h>
#include <chrono>
#include <stdio.h>
#include <cmath>

int main (void)
{
  game::Log::setLevel(game::Log::DEBUG);

  // initialize
  static const int HMAP_WIDTH = 200;
  static const int HMAP_HEIGHT = 200;
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
  local::Rewardmap rmap(hmap,seed,HMAP_WIDTH, HMAP_HEIGHT);
  if (!tmap.load(sf::Vector2u(32,32), "tile.png"))
  {
  	return -1;
  } 

  if (!omap.load(sf::Vector2u(32,32), "map.png"))
  {
  	return -1;
  } 

  if (!rmap.load(sf::Vector2u(32,32), "key.png"))
  {
  	return -1;
  } 

  //Character
  local::Character perso(posCamX, posCamY);
  if (!perso.load(sf::Vector2u(32,32), "perso.png"))
  {
  	return -1;
  }

  //Ennemy
  local::Wave e1(perso.getPosition().x, perso.getPosition().y, 25, seed,HMAP_WIDTH, HMAP_HEIGHT);


  //TitleScreen
  local::HUD hud;
  		if (!hud.load("HUD.png"))
		{
			return -1;
		}
  local::Over gameover;
  		if (!gameover.load("gameOver.png"))
		{
			return -1;
		}
  //GameOver
  bool gameOver=false;
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
if(!gameOver){
	if (moveUP.isActive()) {
		perso.move(0,MARGEX,MARGEY,omap.isReachable(perso.getHitBox(), perso.getDir()));
//		printf("%f : %f\n",perso.getPosition().x,perso.getPosition().y);
	}else if (moveDown.isActive()) {
		perso.move(1,MARGEX,MARGEY,omap.isReachable(perso.getHitBox(), perso.getDir()));
//		printf("%f : %f\n",perso.getPosition().x,perso.getPosition().y);
	}else if (moveLeft.isActive()) {
		perso.move(2,MARGEX,MARGEY,omap.isReachable(perso.getHitBox(), perso.getDir()));
//		printf("%f : %f\n",perso.getPosition().x,perso.getPosition().y);
	}else if (moveRight.isActive()) {
		perso.move(3,MARGEX,MARGEY, omap.isReachable(perso.getHitBox(), perso.getDir()));
//		printf("%f : %f\n",perso.getPosition().x,perso.getPosition().y);
	}else{

	}
}

		//Objectif
	int key = rmap.isColecable(perso.getHitBox(),HMAP_WIDTH,HMAP_HEIGHT);
	switch(key)
	{
		case 1 :
			hud.update(perso.getPosition(), 1, 0, 0, 0);
			break;
		case 2 :
			hud.update(perso.getPosition(), 0, 1, 0, 0);
			break;
		case 3 :
			hud.update(perso.getPosition(), 0, 0, 1, 0);
			break;
		case 4 :
			hud.update(perso.getPosition(), 0, 0, 0, 1);
			break;
		default :
			break;
	}

	if (getPosition.isActive()) {
		//printf("Position : \n - X : %f\n -Y : %f\n\n", perso.getPosition().x, perso.getPosition().y);
	}

	gameView.setCenter(perso.getPosition());



    // update
    auto elapsed = clock.restart();
    auto dt = elapsed.asSeconds();

    mainEntities.update(dt);

		tmap.update(sf::Vector2u(32,32), perso.getPosition().x, perso.getPosition().y);
		omap.update(sf::Vector2u(32,32), perso.getPosition().x, perso.getPosition().y);
		rmap.update(sf::Vector2u(32,32), perso.getPosition().x, perso.getPosition().y);
		e1.update(perso.getPosition().x,perso.getPosition().y,MARGEX,MARGEY);
		gameOver=e1.getStatus();
		gameover.update(perso.getPosition());
		hud.update(perso.getPosition(),0,0,0,0);
		perso.update(sf::Vector2u(32,32), perso.getPosition().x, perso.getPosition().y);



		window.clear();

		window.draw(tmap);
		window.draw(omap);
		window.draw(rmap);
		window.draw(perso.spritePerso);
		for(int e = 0; e < 25; ++e){
			window.draw(e1.getSprite(e));
		}
		window.draw(hud.sprite);
		//window.draw(hud.text);
		window.draw(hud.textS);
		window.draw(hud.textP);
		window.draw(hud.textT);
		window.draw(hud.textC);
		if(gameOver == true){
			window.draw(gameover.sprite);
		}
		mainEntities.render(window);

		window.setView(gameView);
		//window.setView(minimapView);

		window.display();

		actions.reset();
//	}
  }

  return 0;
}
