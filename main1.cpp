#include "class2.h"

int main() {
    PerformanceManager manager;
    manager.addPerformance(Performance("Hamlet", "Shakespeare", "Drama", "2024-05-10", {{50, 100}, {75, 50}}));
    manager.addPerformance(Performance("Macbeth", "Shakespeare", "Tragedy", "2024-05-15", {{40, 150}, {65, 100}}));

    while (true) {
        showMainMenu();
        int mainChoice;
        std::cin >> mainChoice;
        std::cin.ignore();

        switch (mainChoice) {
            case 1:
                while (true) {
                    showSearchMenu();
                    int searchChoice;
                    std::cin >> searchChoice;
                    std::cin.ignore();

                    if (searchChoice == 1) {
                        manager.searchByAuthor();
                    } else if (searchChoice == 2) {
                        manager.searchByTitle();
                    } else if (searchChoice == 3) {
                        break;
                    } else {
                        std::cout << "Invalid option, please try again.\n";
                    }
                }
                break;
            case 2:
                manager.viewPerformanceDetails();
                break;
            case 3:
                manager.viewAndManageTickets();
                break;
            case 4:
                handleSystemManagement(manager);
                break;
            case 5:
                std::cout << "Exiting program.\n";
                return 0;
            default:
                std::cout << "Invalid option, please try again.\n";
        }
    }

    return 0;
}
