#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

const int WIDTH = 800;
const int HEIGHT = 800;

class Star 
{
    public:
        float x, y, z;

        // Constructor
        Star () 
        {
            x = std::rand() % (WIDTH * 2 + 1) - WIDTH;
            y = std::rand() % (HEIGHT * 2 + 1) - HEIGHT;
            z = std::rand() % (WIDTH * 2 + 1) - WIDTH;
        }

        // Function that renders star on the window
        void show (sf::RenderWindow & window)
        {
            // Define positions of the star
            float sx = map(x / z, 0, 1, 0, WIDTH);
            float sy = map(y / z, 0, 1, 0, HEIGHT);
            float r = map(z, 0, WIDTH, 16, 0);

            // Create star
            sf::CircleShape star(r);
            star.setFillColor(sf::Color(255, 255, 255));
            star.setPosition(sx, sy);
            window.draw(star);
        }

        // Function that updates the star's position according to its speed 
        void update (float speed)
        {
            z -= speed;
            if (z < 1) 
            {
                z = WIDTH;
                x = std::rand() % (WIDTH * 2 + 1) - WIDTH;
                y = std::rand() % (HEIGHT * 2 + 1) - HEIGHT;
            }
        }
    
    private:
        float map (float value, float start1, float stop1, float start2, float stop2)
        {
            return start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
        }

};


int main ()
{
    // Create window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Starfield");

    // Create array of stars
    int num_stars = 600;
    Star stars[num_stars];
    float speed = 2;

    // Draw loop
    while (window.isOpen())
    {
        // Check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "Close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window for each frame of the loop
        window.clear(sf::Color(0, 0, 0));

        // Update and show stars
        for (int i = 0; i < num_stars; i++)
        {
            stars[i].update(speed);
            stars[i].show(window);
        }

        // End the current frame
        window.display();

    }

    return 0;
}