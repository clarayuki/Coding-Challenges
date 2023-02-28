#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

const int WIDTH = 800;
const int HEIGHT = 800;

class Star 
{
    private:
        float map (float value, float start1, float stop1, float start2, float stop2)
        {
            return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
        }

    public:
        float x, y, z;

        // Constructor
        Star () 
        {
            x = std::rand()%(WIDTH * 2 + 1) - WIDTH;
            y = std::rand()%(HEIGHT * 2 + 1) - HEIGHT;
            z = std::rand()%(WIDTH * 2 + 1) - WIDTH;
        }

        void show (sf::RenderWindow& window)
        {
            float sx = map(x / z, 0, 1, 0, WIDTH);
            float sy = map(y / z, 0, 1, 0, HEIGHT);
            float r = map(z, 0, WIDTH, 16, 0);
            sf::CircleShape star(r);
            star.setFillColor(sf::Color(255, 255, 255));
            star.setPosition(sx, sy);
            window.draw(star);
        }

        void update (float speed)
        {
            z -= speed;
            if (z < 1) 
            {
                z = WIDTH;
                x = std::rand()%(WIDTH * 2 + 1) - WIDTH;
                y = std::rand()%(HEIGHT * 2 + 1) - HEIGHT;
            }
        }
};


int main ()
{
    // Create window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Starfield");

    // Create array of stars
    int num_stars = 600;
    Star stars[num_stars];
    float speed = 1;

    // Draw loop
    while (window.isOpen())
    {
        // Event of closing window
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear background for each frame of the loop
        window.clear(sf::Color(0, 0, 0));

        // Update and show stars
        for (int i = 0; i < num_stars; i++)
        {
            stars[i].update(speed);
            stars[i].show(window);
        }

        // Display frame
        window.display();

    }
}