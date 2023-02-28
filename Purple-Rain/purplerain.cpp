#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

const int WIDTH = 800;
const int HEIGHT = 800;

class Drop 
{
    public:
        float x = rand() % WIDTH;
        float y = -(rand() % HEIGHT);
        float z = rand() % 20 + 1;
        float len = map(z, 1, 20, 10, 20);
        float thickness = map(z, 1, 20, 10, 20);
        float speed = map(z, 1, 20, 1, 20);

        void fall ()
        {
            y = y + speed;
            if (y > HEIGHT) 
                y = -(rand() % HEIGHT);
        }

        void show (sf::RenderWindow & window)
        {
            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(x, y)),
                sf::Vertex(sf::Vector2f(x, y + len))
            };

            line[0].color = sf::Color(138, 43, 226);
            line[1].color = sf::Color(75, 0, 130);
            //line[0].color.a = map(y, 0, HEIGHT, 0, 255);
            //line[1].color.a = map(y, 0, HEIGHT, 0, 255);

            window.draw(line, 2, sf::Lines);
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
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Purple Rain");

    // Create array of rain drops
    int num_drops = 1000;
    Drop drops[num_drops];
    float speed = 1;

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
        window.clear(sf::Color(230, 230, 250));

        for (int i = 0; i < num_drops; i++)
        {
            drops[i].fall();
            drops[i].show(window);
        }

        // End the current frame
        window.display();

    }

    return 0;
}