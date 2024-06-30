#include <iostream>
#include <queue>
#include <vector>
#include <cmath>

class Elevator {
public:
    Elevator(int id, int floors) : id(id), currentFloor(0), totalFloors(floors), direction(0) {}

    int getId() const { return id; }
    int getCurrentFloor() const { return currentFloor; }
    bool isIdle() const { return direction == 0; }

    void request(int floor) {
        if (floor < 0 || floor >= totalFloors) {
            std::cout << "Invalid floor request: " << floor << std::endl;
            return;
        }
        requests.push(floor);
        if (direction == 0) {
            processRequests();
        }
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
                std::cout << "Elevator " << id << " moving to floor: " << currentFloor << std::endl;
            }

            std::cout << "Elevator " << id << " arrived at floor: " << currentFloor << std::endl;
        }
        direction = 0;
    }

private:
    int id;
    int currentFloor;
    int totalFloors;
    int direction; // -1 for down, 1 for up, 0 for idle
    std::queue<int> requests;
};

class ElevatorSystem {
public:
    ElevatorSystem(int numElevators, int floors) {
        for (int i = 0; i < numElevators; ++i) {
            elevators.emplace_back(i, floors);
        }
    }

    void request(int floor) {
        Elevator& bestElevator = findBestElevator(floor);
        bestElevator.request(floor);
    }

private:
    std::vector<Elevator> elevators;

    Elevator& findBestElevator(int floor) {
        Elevator* bestElevator = nullptr;
        int minDistance = std::numeric_limits<int>::max();

        for (auto& elevator : elevators) {
            if (elevator.isIdle()) {
                int distance = std::abs(elevator.getCurrentFloor() - floor);
                if (distance < minDistance) {
                    minDistance = distance;
                    bestElevator = &elevator;
                }
            }
        }

        if (!bestElevator) {
            // If all elevators are busy, choose the one with the shortest queue
            int minQueueSize = std::numeric_limits<int>::max();
            for (auto& elevator : elevators) {
                int queueSize = elevator.isIdle() ? 0 : 1; // Assuming each elevator processes one request at a time
                if (queueSize < minQueueSize) {
                    minQueueSize = queueSize;
                    bestElevator = &elevator;
                }
            }
        }

        return *bestElevator;
    }
};

int main() {
    ElevatorSystem system(3, 10); // 3 elevators, 10 floors

    system.request(3);
    system.request(7);
    system.request(1);
    system.request(9);
    system.request(4);

    return 0;
}
