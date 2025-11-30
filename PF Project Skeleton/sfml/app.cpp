#include "app.h"
#include "../core/simulation_state.h"
#include "../core/simulation.h"
#include "../core/grid.h"
#include "../core/switches.h"
#include "../core/io.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdio>

// ============================================================================
// APP.CPP - Implementation of SFML application (NO CLASSES)
// ============================================================================

// ----------------------------------------------------------------------------
// GLOBAL VARIABLES FOR APP STATE
// ----------------------------------------------------------------------------
static sf::RenderWindow* g_window = nullptr;
static sf::Font g_font;

// View for camera (panning/zoom)
static sf::View g_camera;

// Simulation state
static bool g_isPaused = false;
static bool g_isStepMode = false;

// Mouse state
static bool g_isDragging = false;
static int g_lastMouseX = 0;
static int g_lastMouseY = 0;

// Grid rendering parameters
static float g_cellSize = 40.0f;
static float g_gridOffsetX = 50.0f;
static float g_gridOffsetY = 50.0f;

void drawGame(){
    for(int r=0; r<rows; r++){
        for(int c=0; c<cols; c++){
            char tile = grid[r][c];
            float px = c * g_cellSize;
            float py = r * g_cellSize;
            sf::RectangleShape cell(sf::Vector2f(g_cellSize-2, g_cellSize-2));
            cell.setPosition(px+1, py+1);
            cell.setFillColor(sf::Color(30,30,30));
            g_window->draw(cell);
            if(tile != ' '){
                sf::RectangleShape shape(sf::Vector2f(g_cellSize*0.8f, g_cellSize*0.8f));
                shape.setOrigin(shape.getSize().x/2, shape.getSize().y/2);
                shape.setPosition(px + g_cellSize/2, py + g_cellSize/2);

                if(tile == 'S') shape.setFillColor(sf::Color::Green);
                else if(tile == 'D') shape.setFillColor(sf::Color::Red);
                else if(tile >= 'A' && tile <= 'Z') shape.setFillColor(sf::Color::Yellow);
                else if(tile == '=') shape.setFillColor(sf::Color(255,165,0));
                else {
                    shape.setSize(sf::Vector2f(g_cellSize, g_cellSize*0.3f));
                    shape.setOrigin(shape.getSize().x/2, shape.getSize().y/2);
                    shape.setFillColor(sf::Color(150,150,150));
                }
                g_window->draw(shape);
            }
        }
    }
    for(int i=0; i<traincount; i++){
        if(Active[i] == true){
            float tx = x[i] * g_cellSize;
            float ty = y[i] * g_cellSize;
            sf::CircleShape trainShape(g_cellSize*0.4f);
            trainShape.setFillColor(sf::Color::Cyan);
            float offset = (g_cellSize - (g_cellSize*0.8f))/2.0f;
            trainShape.setPosition(tx + offset, ty + offset);
            g_window->draw(trainShape);
        }
    }
}

// ----------------------------------------------------------------------------
// INITIALIZATION
// ----------------------------------------------------------------------------
// This function will initialize the SFML application window and resources.
// It creates a render window with a specified size and title, sets the
// framerate limit, attempts to load a font file for text rendering, and
// initializes the camera view. Returns true on success, false on failure.
// This should be called once at the start of the application before entering
// the main loop.
// ----------------------------------------------------------------------------
bool initializeApp(){
    int w=1280;
    int h=720;
    g_window=new sf::RenderWindow(sf::VideoMode(w, h),"Switchback Rails");
    if(g_window==NULL){
        return false;
    }
    g_window->setFramerateLimit(60);
    float camW=(float)w;
    float camH=(float)h;
    g_camera.setSize(camW,camH);
    g_camera.setCenter(camW/2.0f,camH/2.0f);
    g_window->setView(g_camera);
    return true;
}

// ----------------------------------------------------------------------------
// MAIN RUN LOOP
// ----------------------------------------------------------------------------
// This function will run the main application loop. It handles event processing,
// simulation updates, and rendering. The loop continues while the window is open.
// It processes SFML events (window close, keyboard input, mouse input), updates
// the simulation at a fixed interval (2 ticks per second) when not paused,
// checks if the simulation is complete, and renders the current frame. Keyboard
// controls: SPACE to pause/resume, PERIOD to step one tick, ESC to exit. The
// loop exits when the window is closed or ESC is pressed.
// ----------------------------------------------------------------------------
void runApp(){
   if(g_window==NULL) return;
    sf::Clock clock;
    float timer=0.0f;
    while(g_window->isOpen()){
        sf::Event event;
        while(g_window->pollEvent(event)){
            if(event.type==sf::Event::Closed){
                g_window->close();
            }
            if(event.type==sf::Event::KeyPressed){
                if(event.key.code==sf::Keyboard::Escape){
                    g_window->close();
                }
                if(event.key.code==sf::Keyboard::Space){
                    if(g_isPaused==false) g_isPaused = true;
                    else g_isPaused=false;
                }
                if(event.key.code==sf::Keyboard::Period){
                    simulateOneTick();
                }
            }
        }
        float dt=clock.restart().asSeconds();
        if(g_isPaused==false){
            timer=timer+dt;
            if(timer>0.5f){
                simulateOneTick();
                timer=0.0f;
            }
        }else{
            timer = 0.0f;
        }
        g_window->clear(sf::Color(50, 50, 50));
        drawGame();
        g_window->display();
    }
}

// ----------------------------------------------------------------------------
// CLEANUP
// ----------------------------------------------------------------------------
// This function will clean up all resources and close the application window.
// It deletes the render window object and sets the pointer to nullptr. This
// should be called once at the end of the application before exiting to ensure
// proper resource cleanup.
// ----------------------------------------------------------------------------
void cleanupApp(){
    if(g_window!=NULL){
        delete g_window;
        g_window=NULL;
    }
}
