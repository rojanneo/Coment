#ifndef __INPUTMANAGER_H__
#define __INPUTMANAGER_H__

#include <string>
#include <map>

#include <SFML/Graphics.hpp>

#include <coment/managers/Manager.h>
#include <coment/systems/EntitySystem.h>

namespace coment
{
        namespace samples
        {
                namespace balls
                {
			class MovementSystem;
			class RenderingSystem;
			class GravitySystem;

			class InputManager
				: public coment::Manager
			{
			public:
				InputManager(sf::RenderWindow* window);

				void handleEvent(const sf::Event& e);

				void onRegistered();

			private:
				sf::RenderWindow* _window;
				coment::EntitySystem* _movementSystem;
				coment::EntitySystem* _renderingSystem;
				coment::EntitySystem* _gravitySystem;
			};

			InputManager::InputManager(sf::RenderWindow* window)
				: _window(window)
			{

			}

			// Called when this manager is registered with the world
			void InputManager::onRegistered()
			{
				_renderingSystem = (coment::EntitySystem*)_world->getSystem<RenderingSystem>();
				_movementSystem = (coment::EntitySystem*)_world->getSystem<MovementSystem>();
				_gravitySystem = (coment::EntitySystem*)_world->getSystem<GravitySystem>();
			}

			void InputManager::handleEvent(const sf::Event& event)
			{
				// End when the user closes the window or presses esc
				if (event.type == sf::Event::Closed ||
					(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
				{
					_window->close();
				}

				// Handle keyboard input
				if (event.type == sf::Event::KeyReleased)
				{
					// Toggle rendering when player presses R
					if (event.key.code == sf::Keyboard::R)
					{
						_renderingSystem->setEnabled(!_renderingSystem->getEnabled());
					}
					// Toggle movement when player presses M
					else if (event.key.code == sf::Keyboard::M)
					{
						_movementSystem->setEnabled(!_movementSystem->getEnabled());
						_gravitySystem->setEnabled(!_gravitySystem->getEnabled());
					}
					// Add 100 balls when user presses right arrow
					else if (event.key.code == sf::Keyboard::Right)
					{
						_world->getManager<BallManager>()->createBalls(10);
					}
					// Remove 100 balls when user presses left arrow
					else if (event.key.code == sf::Keyboard::Left)
					{
						_world->getManager<BallManager>()->destroyBalls(10);
					}
				}
			}
		}
	}
}

#endif /* __INPUTMANAGER_H__ */