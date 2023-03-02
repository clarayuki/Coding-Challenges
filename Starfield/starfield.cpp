#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

const int WIDTH = 800;
const int HEIGHT = 800;

class Star 
{
    public:
        float x;
        float y;
        float z;
        float sx;
        float sy;

        // Constructor
        Star () 
        {
            x = std::rand() % (WIDTH) - WIDTH / 2;
            y = std::rand() % (HEIGHT) - HEIGHT / 2;
            z = WIDTH;
        }

        // Function that renders star on the window
        void show (sf::RenderWindow & window)
        {
            // Define positions of the star
            sx = map(x / z, 0, 1, 0, WIDTH);
            sy = map(y / z, 0, 1, 0, HEIGHT);
            float r = map(z, 0, WIDTH, 16, 0);

            // Create star
            sf::CircleShape star(r);
            star.setFillColor(sf::Color(255, 255, 255));
            star.setPosition(sx, sy);
            star.setOrigin(r, r);
            window.draw(star);
        }

        // Function that updates the star's position according to its speed 
        void update (float speed)
        {
            z -= speed;
            if (abs(sx) > WIDTH / 2 + 8 || abs(sy) > HEIGHT / 2 + 8) 
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
    sf::View view(sf::Vector2f(0, 0), sf::Vector2f(WIDTH, HEIGHT));
    window.setView(view);

    // Create array of stars
    int num_stars = 200;
    Star stars[num_stars];
    float speed = 20;

    sf::Clock deltaClock;
    // Draw loop
    while (window.isOpen())
    {
        sf::Time dt = deltaClock.restart();
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
            stars[i].update(speed * dt.asSeconds());
            stars[i].show(window);
        }

        // End the current frame
        window.display();

        // speed += 50 * dt.asSeconds();

    }

    return 0;
}