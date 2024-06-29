#include <iostream>
#include <queue>
#include <vector>

class Elevator {
public:
    Elevator(int floors) : currentFloor(0), totalFloors(floors), direction(0) {}

    void request(int floor) {
        if (floor < 0 || floor >= totalFloors) {
            std::cout << "Invalid floor request: " << floor << std::endl;
            return;
        }
        requests.push(floor);
        processRequests();
    }

    void processRequests() {
        while (!requests.empty()) {
            int targetFloor = requests.front();
            requests.pop();

            if (targetFloor > currentFloor) {
                direction = 1;
            } else if (targetFloor < currentFloor) {
                direction = -1;
            } else {
                direction = 0;
            }

            while (currentFloor != targetFloor) {
                currentFloor += direction;
                std::cout << "Elevator moving to floor: " << currentFloor << std::endl;
            }

            std::cout << "Elevator arrived at floor: " << currentFloor << std::endl;
        }
        direction = 0;
    }

private:
    int currentFloor;
    int totalFloors;
    int direction; // -1 for down, 1 for up, 0 for idle
    std::queue<int> requests;
};

int main() {
    Elevator elevator(10); // Assume 10 floors

    elevator.request(3);
    elevator.request(7);
    elevator.request(1);

    return 0;
}
