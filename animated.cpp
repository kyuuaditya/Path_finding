#include <sfml/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Main menu", sf::Style::Default, settings);
    window.setFramerateLimit(144); // set frame rate limit
    window.setVerticalSyncEnabled(true); // enable vertical sync

    sf::Image image;
    if (!image.loadFromFile("maze_ani.png")) {
        std::cerr << "Failed to load image" << std::endl;
        return -1;
    }

    // Get image size
    sf::Vector2u size = image.getSize();
    std::cout << "Image size: " << size.x << "x" << size.y << std::endl;

    // Padding for the image
    int padding = 2;
    // Create a 3D array to store the image data
    std::vector<std::vector<std::vector<int>>> imageData(size.x + padding, std::vector<std::vector<int>>(size.y + padding, std::vector<int>(5)));

    int location_x = 0;
    int location_y = 0;
    //insert dummy values
    for (unsigned int y = 0; y < size.y + 2; ++y) {
        for (unsigned int x = 0; x < size.x + 2; ++x) {
            imageData[x][y][0] = 0;
            imageData[x][y][1] = 0;
            imageData[x][y][2] = -1;
            imageData[x][y][3] = 0;
        }
    }
    // Populate the array with the image data
    for (unsigned int y = 1; y < size.y + 1; ++y) {
        for (unsigned int x = 1; x < size.x + 1; ++x) {
            imageData[x + 1][y + 1][1] = 0; // visited
            imageData[x + 1][y + 1][2] = -1; // step_count
            imageData[x + 1][y + 1][3] = 0; // gold
            sf::Color pixel = image.getPixel(x, y);
            if (pixel.r == 255 && pixel.g == 255 && pixel.b == 255) {
                imageData[x + 1][y + 1][0] = 1; //path
            }
            else if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0) {
                imageData[x + 1][y + 1][0] = 0; // block
            }
            else if (pixel.r == 255 && pixel.g == 0 && pixel.b == 0) {
                imageData[x + 1][y + 1][0] = 2; // start point
                imageData[x + 1][y + 1][1] = 1;
                imageData[x + 1][y + 1][2] = 0;
                imageData[x + 1][y + 1][3] = 1;
            }
            else if (pixel.r == 0 && pixel.g == 255 && pixel.b == 0) {
                imageData[x + 1][y + 1][0] = 3; // end point
                location_x = x + 1;
                location_y = y + 1;
                imageData[x + 1][y + 1][3] = 1;

            }
        }
    }
    std::cout << "end point: " << location_x << ", " << location_y << std::endl;

    int step_count = 0;
    int searching = 1;
    int count = 0;
    int x = 0;
    int y = 0;
    // searching the path
    while (searching == 1) {
        // main loop for path finding
        for (unsigned int temp_y = 1;temp_y < size.y + 1; temp_y++) {
            y = temp_y;
            for (unsigned int temp_x = 1; temp_x < size.x + 1; temp_x++) {
                x = temp_x;
                // check for current step
                if (imageData[location_x][location_y][2] == step_count) {
                    // std::cout << imageData[location_x][location_y][2] << " " << step_count << std::endl;
                    searching = 0;
                    // return 0;
                }
                else if (step_count == imageData[x][y][2]) {
                    // check neighbourhood
                    if (imageData[x + 1][y][0] && imageData[x + 1][y][1] == 0) {
                        imageData[x + 1][y][2] = step_count + 1;
                        imageData[x + 1][y][1] = 1;
                    }
                    if (imageData[x - 1][y][0] && imageData[x - 1][y][1] == 0) {
                        imageData[x - 1][y][2] = step_count + 1;
                        imageData[x - 1][y][1] = 1;
                    }
                    if (imageData[x][y + 1][0] && imageData[x][y + 1][1] == 0) {
                        imageData[x][y + 1][2] = step_count + 1;
                        imageData[x][y + 1][1] = 1;
                    }
                    if (imageData[x][y - 1][0] && imageData[x][y - 1][1] == 0) {
                        imageData[x][y - 1][2] = step_count + 1;
                        imageData[x][y - 1][1] = 1;
                    }
                }
            }
        }
        step_count++;
        count++;
    }

    // print the result
    for (unsigned int y = 0; y < size.y + 2; y++) {
        for (unsigned int x = 0; x < size.x + 2; x++) {
            std::cout << imageData[x][y][2] << " ";
        }
        std::cout << std::endl;
    }

    // backtracking
    int back_x = location_x;
    int back_y = location_y;
    int back_count = imageData[location_x][location_y][2];
    while (back_count > 0) {
        if (imageData[back_x + 1][back_y][2] == back_count - 1) {
            back_x = back_x + 1;
            imageData[back_x + 1][back_y][3] = 1;
        }
        else if (imageData[back_x - 1][back_y][2] == back_count - 1) {
            back_x = back_x - 1;
            imageData[back_x - 1][back_y][3] = 1;
        }
        else if (imageData[back_x][back_y + 1][2] == back_count - 1) {
            back_y = back_y + 1;
            imageData[back_x][back_y + 1][3] = 1;
        }
        else if (imageData[back_x][back_y - 1][2] == back_count - 1) {
            back_y = back_y - 1;
            imageData[back_x][back_y - 1][3] = 1;
        }
        back_count--;
        std::cout << back_x - 1 << " " << back_y - 1 << std::endl;
    }

    int window_size = 1000;

    int cell_size = window_size / size.x;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(window_size, window_size), "Main menu", sf::Style::Default, settings);
    window.setFramerateLimit(144); // set frame rate limit
    window.setVerticalSyncEnabled(true); // enable vertical sync


    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.clear();
        // Draw your stuff here
        window.display();
    }
}