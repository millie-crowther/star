#include <iostream>
#include "engine.h"
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"

int main(){
  glm::mat4 myMatrix = glm::translate(glm::mat4(), glm::vec3(10.0f, 0.0f, 0.0f));
  glm::vec4 myVector(10.0f, 10.0f, 10.0f, 0.0f);
  glm::vec4 transformedVector = myMatrix * myVector; // guess the result

  engine_t engine;
  engine.run();

  sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}
