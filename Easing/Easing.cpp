#define SFML_STATIC
#ifdef _DEBUG
#pragma comment(lib,"sfml-graphics-s-d.lib")
#pragma comment(lib,"sfml-audio-s-d.lib")
#pragma comment(lib,"sfml-system-s-d.lib")
#pragma comment(lib,"sfml-window-s-d.lib")
#pragma comment(lib,"sfml-network-s-d.lib")
#else
#pragma comment(lib,"sfml-graphics-s.lib")
#pragma comment(lib,"sfml-audio-s.lib")
#pragma comment(lib,"sfml-system-s.lib")
#pragma comment(lib,"sfml-window-s.lib")
#pragma comment(lib,"sfml-network-s.lib")
#endif
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"freetype.lib")


#include <SFML\Graphics.hpp>
#include <iostream>
#include <cassert>

#include"Graph.h"
#include"Viewport.h"

int width = 800;
int height = 800;

//sf::Vector2f toScreenSpace(sf::Vector2f p) {
//    float margin = 100;
//    sf::Vector2i origin(100, 100);
//
//    float boxWidth = width - (2 * margin);
//    float boxHeight = height - (2 * margin);
//
//    float x = margin + boxWidth * p.x;
//    float y = height - (margin + boxHeight * p.y);
//
//    return sf::Vector2f(x, y);
//
//}

//void drawGraph(int numPoints, float xValues[], float yValues[], sf::RenderWindow& window) {
//
//
//
//    sf::Vertex line[1001];
//    line[0].position = toScreenSpace(sf::Vector2f(0, 1));
//    line[0].color = sf::Color::White;
//    line[1].position = toScreenSpace(sf::Vector2f(0, 0));
//    line[1].color = sf::Color::White;
//    line[2].position = toScreenSpace(sf::Vector2f(1, 0));
//    line[2].color = sf::Color::White;
//    window.draw(line, 3, sf::LineStrip);
//
//
//    for (int i = 0; i < numPoints; i++) {
//        line[i].position = toScreenSpace(sf::Vector2f(xValues[i], yValues[i]));
//        line[i].color = sf::Color::White;
//    }
//    window.draw(line, numPoints, sf::LineStrip);
//
//}

void drawBall(sf::Vector2f pos, sf::RenderWindow& window, Viewport vp) {

    int radius = 25;
    sf::CircleShape circle(radius);
    circle.setFillColor(sf::Color(100, 250, 50));

    circle.setPointCount(100);

    circle.setPosition(vp.screenSpace(pos)-sf::Vector2f(radius,0));

    window.draw(circle);
}


void draw(float t) {

}

float easeIn(float t) {
    return t * t;
}

float easeOut(float t) {
    return 1 - (1-t) * (1-t);
}

float easeInOut(float t) {
    return easeIn(t) + t * (easeOut(t)-easeIn(t));
}


int main() {

    Graph graph;
    sf::VideoMode mode = sf::VideoMode::getDesktopMode();
    width = mode.width *0.8;
    height = mode.height*0.8;
    sf::RenderWindow sfmlWin(sf::VideoMode(width, height), "Hello World SFML Window");
    sf::Font font;
    //You need to pass the font file location
    if (!font.loadFromFile("GOTHIC.ttf")) {
        return -1;
    }
    sf::Text message("Press ESC to quit", font);

    const int numPoints = 1002;
    float x[numPoints];
    float y[numPoints];

    float t = 0;


    Viewport overallVP(width*0.9, height * 0.9, width * 0.05, height * 0.05, width, height);
    Viewport graphVP(width/2, height/2, width / 4, height / 4, width, height);


    sf::Clock deltaClock;
    sf::Time timeForAnimation = sf::milliseconds(2000);
    sf::Time delayTime = sf::milliseconds(1);
    sf::Time pauseTime = sf::milliseconds(500);

    bool firstFrame = true, lastFrame = false;
    while (sfmlWin.isOpen()) {
        sf::Time dt = deltaClock.restart();
        t += dt.asSeconds() / timeForAnimation.asSeconds();

        sf::Event e;
        while (sfmlWin.pollEvent(e)) {

            switch (e.type) {
            case sf::Event::EventType::Closed:
                sfmlWin.close();
                break;
             case sf::Event::KeyPressed:
                {
                    //if (event.key.code >= sf::Keyboard::A && event.key.code <= sf::Keyboard::Z) {
                        sfmlWin.close();
                        break;
                
                }
            }
        }

        sfmlWin.clear();
        sfmlWin.draw(message);

        ////float y = t * t;
        //float y = easeIn(t);
        //float y = easeOut(t);
        float y = easeInOut(t);

        graph.addPoint(sf::Vector2f(t, y));
        graph.drawGraph(sfmlWin, graphVP);
        drawBall(sf::Vector2f(y, 0.2), sfmlWin, overallVP);


        sf::sleep(delayTime);

        sfmlWin.display();

        if (firstFrame) {
            sf::sleep(pauseTime);
            sf::Time dt = deltaClock.restart(); 
            firstFrame = false;

        }
        //assert(i < 1000);
        if (t >= 1) {
            sf::sleep(pauseTime);
            t = 0;
            graph.reset();
            firstFrame = true;
            deltaClock.restart();
        }


 
    }
    return 0;
}