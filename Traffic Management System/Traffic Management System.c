#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep function

// Enum for Traffic Lights
enum TrafficLight { RED, YELLOW, GREEN };

// Function to simulate a traffic light
void displayTrafficLight(int direction, enum TrafficLight light) {
    // Display traffic lights based on the direction and light
    if (direction == 1) {  // North-South
        if (light == RED) {
            printf("North-South Light: RED\n");
        } else if (light == YELLOW) {
            printf("North-South Light: YELLOW\n");
        } else {
            printf("North-South Light: GREEN\n");
        }
    } else if (direction == 2) {  // East-West
        if (light == RED) {
            printf("East-West Light: RED\n");
        } else if (light == YELLOW) {
            printf("East-West Light: YELLOW\n");
        } else {
            printf("East-West Light: GREEN\n");
        }
    }
}

// Function to simulate the traffic light cycle for North-South and East-West directions
void trafficLightCycle() {
    enum TrafficLight northSouthLight = GREEN;
    enum TrafficLight eastWestLight = RED;

    while (1) {
        // Green for North-South, Red for East-West
        displayTrafficLight(1, northSouthLight); // North-South GREEN
        displayTrafficLight(2, eastWestLight);   // East-West RED
        sleep(5); // Wait for 5 seconds

        // Change to Yellow for North-South, Green for East-West
        northSouthLight = YELLOW;
        eastWestLight = GREEN;
        displayTrafficLight(1, northSouthLight); // North-South YELLOW
        displayTrafficLight(2, eastWestLight);   // East-West GREEN
        sleep(2); // Wait for 2 seconds

        // Red for North-South, Yellow for East-West
        northSouthLight = RED;
        eastWestLight = YELLOW;
        displayTrafficLight(1, northSouthLight); // North-South RED
        displayTrafficLight(2, eastWestLight);   // East-West YELLOW
        sleep(2); // Wait for 2 seconds

        // Green for North-South, Red for East-West
        northSouthLight = GREEN;
        eastWestLight = RED;
        displayTrafficLight(1, northSouthLight); // North-South GREEN
        displayTrafficLight(2, eastWestLight);   // East-West RED
        sleep(5); // Wait for 5 seconds
    }
}

int main() {
    printf("------ Traffic Management System ------\n");
    printf("Simulating Traffic Lights at an Intersection...\n\n");

    trafficLightCycle();

    return 0;
}
