#include <sfml/Graphics.hpp>
#include <iostream>
#include <vector>

int main() {
    // Load an image file
    sf::Image image;
    if (!image.loadFromFile("maze_ani.png")) {
        std::cerr << "Failed to load image" << std::endl;
        return -1;
    }

    // Get image size
    sf::Vector2u size = image.getSize();
    std::cout << "Image size: " << size.x << "x" << size.y << std::endl;

    // variables
    int padding = 2;
    int end_point_x = 0;
    int end_point_y = 0;
    int start_point_x = 0;
    int start_point_y = 0;

    // Create a 3D array for the image with added padding and properties
    std::vector<std::vector<std::vector<int>>> imageData(size.x + padding, std::vector<std::vector<int>>(size.y + padding, std::vector<int>(5)));

    //insert default values
    for (unsigned int y = 0; y < size.y + 2; ++y) {
        for (unsigned int x = 0; x < size.x + 2; ++x) {
            imageData[x][y][0] = 0; // block
            imageData[x][y][1] = 0; // not visited
            imageData[x][y][2] = -1; // step_count
            imageData[x][y][3] = 0; // not gold
        }
    }

    // Populate the array with the image data
    for (unsigned int y = 0; y < size.y + 0; ++y) {
        for (unsigned int x = 0; x < size.x + 0; ++x) {
            sf::Color pixel = image.getPixel(x, y); // get pixel color
            if (pixel.r == 255 && pixel.g == 255 && pixel.b == 255) {
                imageData[x + 1][y + 1][0] = 1; //path
            }
            else if (pixel.r == 0 && pixel.g == 0 && pixel.b == 0) {
                imageData[x + 1][y + 1][0] = 0; // block
            }
            else if (pixel.r == 255 && pixel.g == 0 && pixel.b == 0) {
                imageData[x + 1][y + 1][0] = 2; // start point
                imageData[x + 1][y + 1][1] = 1; // visited
                imageData[x + 1][y + 1][2] = 0; // step_count
                imageData[x + 1][y + 1][3] = 1; // gold
                start_point_x = x + 1;
                start_point_y = y + 1;
            }
            else if (pixel.r == 0 && pixel.g == 255 && pixel.b == 0) {
                imageData[x + 1][y + 1][0] = 3; // end point
                imageData[x + 1][y + 1][3] = 1; // gold
                end_point_x = x + 1;
                end_point_y = y + 1;

            }
        }
    }

    // print start and end point
    std::cout << "start point: " << end_point_x << ", " << end_point_y << std::endl;
    std::cout << "end point: " << end_point_x << ", " << end_point_y << std::endl;

    for (unsigned int y = 0; y < size.y + 2; y++) {
        for (unsigned int x = 0; x < size.x + 2; x++) {
            std::cout << imageData[x][y][0] << " ";
        }
        std::cout << std::endl;
    }

    // variables
    int step_count = 0; // total steps taken to reach final state
    int searching = 1; // is still searching
    int once = 1;
    int x = 0;
    int y = 0;
    int temp_max = 250;

    // backtracking attributes
    int back_x = end_point_x;
    int back_y = end_point_y;
    int back_count = imageData[end_point_x][end_point_y][2];

    // define size of window and cell
    int window_size = 800;
    int cell_size = window_size / size.x;
    int edgeOfRect = 1;

    // display window setup
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(window_size, window_size), "Main menu", sf::Style::Default, settings);
    window.setFramerateLimit(144); // set frame rate limit
    window.setVerticalSyncEnabled(true); // enable vertical sync

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        if (searching == 1) { // for path finding
            for (unsigned int num_y = 1;num_y < size.y + 1; num_y++) {
                for (unsigned int num_x = 1; num_x < size.x + 1; num_x++) {
                    if (imageData[end_point_x][end_point_y][2] == step_count) { // check if end point is reached
                        searching = 0;
                    }
                    else if (step_count == imageData[num_x][num_y][2]) { // check neighbourhood
                        if (imageData[num_x + 1][num_y][0] && imageData[num_x + 1][num_y][1] == 0) { // right
                            imageData[num_x + 1][num_y][2] = step_count + 1;
                            imageData[num_x + 1][num_y][1] = 1; // set visited
                        }
                        if (imageData[num_x - 1][num_y][0] && imageData[num_x - 1][num_y][1] == 0) { // left 
                            imageData[num_x - 1][num_y][2] = step_count + 1;
                            imageData[num_x - 1][num_y][1] = 1; // set visited
                        }
                        if (imageData[num_x][num_y + 1][0] && imageData[num_x][num_y + 1][1] == 0) { // down
                            imageData[num_x][num_y + 1][2] = step_count + 1;
                            imageData[num_x][num_y + 1][1] = 1; // set visited
                        }
                        if (imageData[num_x][num_y - 1][0] && imageData[num_x][num_y - 1][1] == 0) { // up
                            imageData[num_x][num_y - 1][2] = step_count + 1;
                            imageData[num_x][num_y - 1][1] = 1; // set visited
                        }
                    }
                }
            }
            step_count++;
        }

        sf::sleep(sf::milliseconds(100 * 20 / size.x)); // sleep for 100ms for 20x20 maze, 20ms for 100x100 maze, 10ms for 200x200 maze

        if (searching == 0 && once == 1) { // to be followed only once after searching finishes
            back_count = imageData[end_point_x][end_point_y][2];
            temp_max = back_count;
            once = 0;
        }

        if (back_count > 0 && searching == 0) { // main backtracking step
            if (imageData[back_x - 1][back_y][2] == back_count - 1) { // left
                back_x = back_x - 1;
            }
            else if (imageData[back_x + 1][back_y][2] == back_count - 1) { // right
                back_x = back_x + 1;
            }
            else if (imageData[back_x][back_y + 1][2] == back_count - 1) { // up
                back_y = back_y + 1;
            }
            else if (imageData[back_x][back_y - 1][2] == back_count - 1) { // down
                back_y = back_y - 1;
            }
            imageData[back_x][back_y][3] = 1; // set gold
            back_count--;
            std::cout << back_x - 1 << " " << back_y - 1 << std::endl; // write backtracking path from end to start
        }

        // Draw the maze
        for (unsigned int y = 0; y < size.y + 0; y++) {
            for (unsigned int x = 0; x < size.x + 0; x++) {
                float gradient = (float)imageData[x + 1][y + 1][2] / (float)temp_max;
                // drawing individual cells
                if (imageData[x + 1][y + 1][0] == 0) { // block
                    sf::RectangleShape rectangle(sf::Vector2f(cell_size - edgeOfRect, cell_size - edgeOfRect));
                    rectangle.setFillColor(sf::Color::Black);
                    rectangle.setPosition(x * cell_size + edgeOfRect, y * cell_size + edgeOfRect);
                    window.draw(rectangle);
                }
                else { // path
                    sf::RectangleShape rectangle(sf::Vector2f(cell_size - edgeOfRect, cell_size - edgeOfRect));
                    rectangle.setFillColor(sf::Color::White);
                    rectangle.setPosition(x * cell_size + edgeOfRect, y * cell_size + edgeOfRect);
                    window.draw(rectangle);
                }

                if (imageData[x + 1][y + 1][2] >= 0) { // area visited
                    sf::RectangleShape rectangle(sf::Vector2f(cell_size - edgeOfRect, cell_size - edgeOfRect));
                    rectangle.setFillColor(sf::Color((int)(200 * gradient / 2 + 200 * 1 / 2), (int)(190 * gradient / 2 + 190 * 1 / 2), (int)(200 * gradient / 2 + 200 * 1 / 2)));
                    rectangle.setPosition(x * cell_size + edgeOfRect, y * cell_size + edgeOfRect);
                    window.draw(rectangle);
                }
                if (imageData[x + 1][y + 1][3] == 1) { // gold
                    sf::RectangleShape rectangle(sf::Vector2f(cell_size - edgeOfRect, cell_size - edgeOfRect));
                    rectangle.setFillColor(sf::Color(250, 140, 0));
                    rectangle.setPosition(x * cell_size + edgeOfRect, y * cell_size + edgeOfRect);
                    window.draw(rectangle);
                }
            }
        }
        window.display();
    }
}