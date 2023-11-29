// @file sfml_grid.cpp
// g++ -std=c++17 sfml_grid.cpp -o prog -lpthread -lsfml-graphics -lsfml-window -lsfml-system
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm> // for fill
#include <memory>
#include <chrono>  // For sleep

// Third party libraries
#include <SFML/Graphics.hpp>

// Globally available grid
static std::vector<int> grid;
// Global array of all of our objects
std::vector<std::unique_ptr<sf::Shape>> shapes;
// Keeps track of the program running
bool isRunning = true;
static int sizeX = 512;
static int sizeY = 512;
static int gridSize = sizeX * sizeY;

// Function to update grid
// This will be handled in each thread, independently working
// on the task.
void update_grid(){
	while(isRunning){
		//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		//grid[y*2+x] = rand()%5;

        // Update the grid
        for (int i = 0; i < gridSize; ++i) {
            grid[i] = rand()%3;
        }

	}   
}


// Entry point into our program
int main(){
    // Initialize our grid with 4 entries
    grid.reserve(gridSize);
    std::fill(begin(grid),end(grid),0);
	// Pick out the shape being drawn
	// in our grid and update it accordingly.
    for(int x=0; x < sizeX; x++){
        for(int y=0; y< sizeY; y++){
			shapes.push_back(std::make_unique<sf::RectangleShape>(sf::Vector2f(5.0f, 5.0f)));	
		}
	}


    std::thread thread1(update_grid);
    

    // Main program loop
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML with C++ threads");

	// Main Game loop
	while (window.isOpen() && isRunning)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed){
				window.close();
				isRunning = false;
			}
		}
		
		// Clear the window
		window.clear();
        int counter = 0;
		for(int x=0; x < sizeX; x++){   
			for(int y=0; y< sizeY; y++){
				// Set the position
				shapes[counter]->setPosition(x*1.5625,y*1.5625);
				// Update the color
				if(0==grid[counter]){
					shapes[counter]->setFillColor(sf::Color::Black);
				}else if(1==grid[counter]){
					shapes[counter]->setFillColor(sf::Color::Green);	
				}else if(2==grid[counter]){
					shapes[counter]->setFillColor(sf::Color::Blue);
				}
                counter++;
			}
		}
	
		// Draw all of our shapes
		for(auto& shape: shapes){
			window.draw(*shape);
		}
		window.display();
	}

    // Join threads before program execution termintes
    
    thread1.join();
    

    // Program finish
    std::cout << "Program Terminating" << std::endl;

    return 0;
}