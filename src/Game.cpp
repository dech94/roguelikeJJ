#include <game/Action.h>
#include <game/Animation.h>
#include <game/AssetManager.h>
#include <game/Camera.h>
#include <game/Clock.h>
#include <game/Control.h>
#include <game/Entity.h>
#include <game/EntityManager.h>
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

int main (void)
{
  game::Log::setLevel(game::Log::DEBUG);

  // initialize
  static constexpr unsigned INITIAL_WIDTH = 800;
  static constexpr unsigned INITIAL_HEIGHT = 600;

  game::WindowSettings settings(INITIAL_WIDTH, INITIAL_HEIGHT, "Game");
  game::WindowGeometry geometry(INITIAL_WIDTH, INITIAL_HEIGHT);

  sf::RenderWindow window;
  settings.applyTo(window);
  window.setKeyRepeatEnabled(false);

  // add cameras
  game::CameraManager cameras;

  game::FixedRatioCamera mainCamera(INITIAL_WIDTH, INITIAL_HEIGHT, {INITIAL_WIDTH * 0.5f, INITIAL_HEIGHT * 0.5f});
  cameras.addCamera(mainCamera);

  // add actions
  game::ActionManager actions;

  game::Action closeWindowAction("Close window");
  closeWindowAction.addCloseControl();
  closeWindowAction.addKeyControl(sf::Keyboard::Escape);
  actions.addAction(closeWindowAction);

  game::Action fullscreenAction("Fullscreen");
  fullscreenAction.addKeyControl(sf::Keyboard::F);
  actions.addAction(fullscreenAction);

  // Setup Box2d engine
  b2World b2_world(b2Vec2(0.0f, 0.0f));

  // Events manager 
  game::EventManager events;

  game::EntityManager mainEntities;

  // main loop
  game::Clock clock;

  while (window.isOpen()) {
    // input
    sf::Event event;

    while (window.pollEvent(event)) {
      actions.update(event);
      cameras.update(event);
      geometry.update(event);
    }

    if (closeWindowAction.isActive()) {
      window.close();
    }

    if (fullscreenAction.isActive()) {
      settings.toggleFullscreen();
      settings.applyTo(window);
      auto sz = window.getSize();

      // fake resize event (not sent when going fullscreen before SFML 2.3.1)
      sf::Event event;
      event.type = sf::Event::Resized;
      event.size.width = sz.x;
      event.size.height = sz.y;
      cameras.update(event);
      geometry.update(event);
    }

    // update
    auto elapsed = clock.restart();
    auto dt = elapsed.asSeconds();
    mainEntities.update(dt);
    b2_world.Step(dt, 8, 3);

    // render
    window.clear(sf::Color::White);

    mainCamera.configure(window);
    mainEntities.render(window);
    b2_world.DrawDebugData();

    window.display();

    actions.reset();
  }

  return 0;
}
