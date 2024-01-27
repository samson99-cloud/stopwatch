#include <iostream>
#include <chrono>
#include <vector>

class Stopwatch {
private:
    std::chrono::steady_clock::time_point start_time;
    std::chrono::steady_clock::time_point pause_time;
    std::vector<std::chrono::duration<double>> lap_times;
    bool is_running;
    bool is_paused;

public:
    Stopwatch() : is_running(false), is_paused(false) {}

    void start() {
        if (!is_running && !is_paused) {
            start_time = std::chrono::steady_clock::now();
            is_running = true;
            std::cout << "Stopwatch started." << std::endl;
        } else if (is_paused) {
            auto elapsed_paused_time = std::chrono::steady_clock::now() - pause_time;
            start_time += elapsed_paused_time;
            is_paused = false;
            std::cout << "Stopwatch resumed." << std::endl;
        } else {
            std::cout << "Stopwatch is already running." << std::endl;
        }
    }

    void pause() {
        if (is_running && !is_paused) {
            pause_time = std::chrono::steady_clock::now();
            is_paused = true;
            std::cout << "Stopwatch paused." << std::endl;
        } else {
            std::cout << "Stopwatch is not running or already paused." << std::endl;
        }
    }

    void stop() {
        if (is_running) {
            auto stop_time = std::chrono::steady_clock::now();
            is_running = false;
            auto elapsed_time = stop_time - (is_paused ? pause_time : start_time);
            lap_times.push_back(elapsed_time);
            std::cout << "Stopwatch stopped. Elapsed time: " << elapsed_time.count() << " seconds." << std::endl;
        } else {
            std::cout << "Stopwatch is not running." << std::endl;
        }
    }

    void reset() {
        is_running = false;
        is_paused = false;
        lap_times.clear();
        std::cout << "Stopwatch reset." << std::endl;
    }

    void lap() {
        if (is_running && !is_paused) {
            auto lap_time = std::chrono::steady_clock::now() - start_time;
            lap_times.push_back(lap_time);
            std::cout << "Lap time: " << lap_time.count() << " seconds." << std::endl;
        } else {
            std::cout << "Cannot record lap time when the stopwatch is not running or paused." << std::endl;
        }
    }

    void display() {
        if (is_running || is_paused) {
            auto current_time = std::chrono::steady_clock::now();
            auto elapsed_time = current_time - (is_paused ? pause_time : start_time);
            std::cout << "Elapsed time: " << elapsed_time.count() << " seconds." << std::endl;
        } else {
            std::cout << "Stopwatch not running." << std::endl;
        }
    }

    void displayLapTimes() {
        if (!lap_times.empty()) {
            std::cout << "Lap times:" << std::endl;
            for (std::size_t i = 0; i < lap_times.size(); ++i) {
                std::cout << "Lap " << i + 1 << ": " << lap_times[i].count() << " seconds." << std::endl;
            }
        } else {
            std::cout << "No lap times recorded." << std::endl;
        }
    }
};

int main() {
    Stopwatch stopwatch;

    char choice;
    do {
        std::cout << "\n1. Start\n2. Pause\n3. Stop\n4. Reset\n5. Lap\n6. Display\n7. Display Lap Times\n8. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                stopwatch.start();
                break;
            case '2':
                stopwatch.pause();
                break;
            case '3':
                stopwatch.stop();
                break;
            case '4':
                stopwatch.reset();
                break;
            case '5':
                stopwatch.lap();
                break;
            case '6':
                stopwatch.display();
                break;
            case '7':
                stopwatch.displayLapTimes();
                break;
            case '8':
                std::cout << "Quitting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

    } while (choice != '8');

    return 0;
}

