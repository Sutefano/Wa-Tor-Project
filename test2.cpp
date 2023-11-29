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
void update_grid(int start, int end){
	while(isRunning){
        // Update the grid
        for (int i = start; i < end; ++i) {
            grid[i] = rand()%3;
        }
	}   
}


// Entry point into our program
int main(int argc, char* argv[]){
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

    // Check if the number of threads is provided as a command-line argument
    int num_threads = 4; // Default to 2 threads
    if (argc > 1) {
        num_threads = std::max(1, std::stoi(argv[1])); // Ensure at least 1 thread
    }

    
    // Launch the update grid threads
    std::vector<std::thread> threads;
    int chunk_size = gridSize / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunk_size;
        int end = (i == num_threads - 1) ? gridSize : start + chunk_size;
        threads.push_back(std::thread(update_grid, start, end));
    }
    

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
    /*
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    */
    
    for(auto& th: threads){
        th.join(); 
    }
    

    // Program finish
    std::cout << "Program Terminating" << std::endl;

    return 0;
}