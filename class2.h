#include "class1.h"


class PerformanceManager {
private:
    std::vector<Performance> performances;

public:
    void addPerformance(const Performance& performance) {
        performances.push_back(performance);
    }
    
    void viewPerformanceDetails() {
        std::string title;
        std::cout << "Enter the title of the performance to view details: ";
        std::getline(std::cin, title);

        bool found = false;
        for (const auto& perf : performances) {
            if (perf.getTitle() == title) {
                std::cout << "Performance: " << perf.getTitle() << " by " << perf.getAuthor() << " on " << perf.getDate() << std::endl;
                perf.displayTicketDetails();
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "No performance found with the title: " << title << std::endl;
        }
    }

    void removePerformance(const std::string& title) {
           auto it = std::remove_if(performances.begin(), performances.end(), [&title](const Performance& perf) {
               return perf.getTitle() == title;
           });
           performances.erase(it, performances.end());
           std::cout << "Performance removed.\n";
       }

       void editPerformance(const std::string& title) {
           for (auto& perf : performances) {
               if (perf.getTitle() == title) {
                   std::string newTitle, newAuthor, newGenre, newDate;
                   std::cout << "Enter new title (current: " << perf.getTitle() << "): ";
                   getline(std::cin, newTitle);
                   std::cout << "Enter new author (current: " << perf.getAuthor() << "): ";
                   getline(std::cin, newAuthor);
                   std::cout << "Enter new genre (current: " << perf.getGenre() << "): ";
                   getline(std::cin, newGenre);
                   std::cout << "Enter new date (current: " << perf.getDate() << "): ";
                   getline(std::cin, newDate);
                   // Updating the details of the performance
                   perf = Performance(newTitle.empty() ? perf.getTitle() : newTitle,
                                      newAuthor.empty() ? perf.getAuthor() : newAuthor,
                                      newGenre.empty() ? perf.getGenre() : newGenre,
                                      newDate.empty() ? perf.getDate() : newDate,
                                      perf.getTickets()); // Keeps current tickets as is
                   std::cout << "Performance updated.\n";
                   return;
               }
           }
           std::cout << "No performance found with the title: " << title << std::endl;
       }

       void updateTicketPrices(const std::string& title) {
           for (auto& perf : performances) {
               if (perf.getTitle() == title) {
                   std::map<int, int> newPrices;
                   int price, quantity;
                   char more = 'y';
                   while (more == 'y') {
                       std::cout << "Enter new price: ";
                       std::cin >> price;
                       std::cout << "Enter quantity for price $" << price << ": ";
                       std::cin >> quantity;
                       newPrices[price] = quantity;
                       std::cout << "Add more prices? (y/n): ";
                       std::cin >> more;
                   }
                   perf.updateTickets(newPrices);
                   std::cout << "Ticket prices updated.\n";
                   return;
               }
           }
           std::cout << "No performance found with the title: " << title << std::endl;
       }
    
    void searchByAuthor() {
           std::string author;
           std::cout << "Enter author's name: ";
           std::getline(std::cin, author);
           
           bool found = false;
           for (const auto& perf : performances) {
               if (perf.getAuthor() == author) {
                   std::cout << "Found: " << perf.getTitle() << " by " << perf.getAuthor() << " (" << perf.getDate() << ")" << std::endl;
                   found = true;
               }
           }
           if (!found) {
               std::cout << "No performances found for author: " << author << std::endl;
           }
       }

       void searchByTitle() {
           std::string title;
           std::cout << "Enter title: ";
           std::getline(std::cin, title);
           
           bool found = false;
           for (const auto& perf : performances) {
               if (perf.getTitle() == title) {
                   std::cout << "Found: " << perf.getTitle() << " by " << perf.getAuthor() << " (" << perf.getDate() << ")" << std::endl;
                   found = true;
               }
           }
           if (!found) {
               std::cout << "No performances found for title: " << title << std::endl;
           }
       }

    void viewAndManageTickets() {
        std::string title;
        std::cout << "Enter the title of the performance to view and manage tickets: ";
        std::getline(std::cin, title);

        for (auto& perf : performances) {
            if (perf.getTitle() == title) {
                std::cout << "Details for: " << perf.getTitle() << " by " << perf.getAuthor() << std::endl;
                perf.displayTicketDetails();
                manageIndividualTickets(perf);
                return;
            }
        }
        std::cout << "No performance found with the title: " << title << std::endl;
    }

    void manageIndividualTickets(Performance& perf) {
        int action;
        do {
            std::cout << "Choose action: 1) Sell Ticket, 2) Reserve Ticket, 3) Cancel Reservation, 4) Confirm Reservation, 5) Return\n";
            std::cin >> action;
            std::cin.ignore();

            int price;
            if (action >= 1 && action <= 4) {
                std::cout << "Enter ticket price: ";
                std::cin >> price;
                std::cin.ignore();
            }

            switch (action) {
                case 1:
                    if (perf.sellTicket(price)) std::cout << "Ticket sold successfully.\n";
                    else std::cout << "Failed to sell ticket.\n";
                    break;
                case 2:
                    if (perf.reserveTicket(price)) std::cout << "Ticket reserved successfully.\n";
                    else std::cout << "Failed to reserve ticket.\n";
                    break;
                case 3:
                    if (perf.cancelReservation(price)) std::cout << "Reservation cancelled successfully.\n";
                    else std::cout << "Failed to cancel reservation.\n";
                    break;
                case 4:
                    if (perf.confirmReservation(price)) std::cout << "Reservation confirmed successfully.\n";
                    else std::cout << "Failed to confirm reservation.\n";
                    break;
                case 5:
                    std::cout << "Returning to previous menu...\n";
                    break;
                default:
                    std::cout << "Invalid option, please try again.\n";
            }
        } while (action != 5);
    }
    
};

void showMainMenu() {
    std::cout << "\n*** Main Menu ***\n";
    std::cout << "1. Search Performances\n";
    std::cout << "2. View Performance Details\n";
    std::cout << "3. Manage Tickets\n";
    std::cout << "4. System Management\n";
    std::cout << "5. Exit\n";
    std::cout << "Select an option: ";
}



void showSearchMenu() {
    std::cout << "\n*** Search Menu ***\n";
    std::cout << "1. Search by Author\n";
    std::cout << "2. Search by Title\n";
    std::cout << "3. Exit to Main Menu\n";
    std::cout << "Select an option: ";
}


void showSystemManagementMenu() {
    std::cout << "\n*** System Management Menu ***\n";
    std::cout << "1. Add New Performance\n";
    std::cout << "2. Edit Existing Performance\n";
    std::cout << "3. Remove Performance\n";
    std::cout << "4. Update Ticket Prices\n";
    std::cout << "5. Return to Main Menu\n";
    std::cout << "Select an option: ";
}

void handleSystemManagement(PerformanceManager& manager) {
    while (true) {
        showSystemManagementMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::string title, author, genre, date;
                std::map<int, int> tickets;
                std::cout << "Enter title: ";
                getline(std::cin, title);
                std::cout << "Enter author: ";
                getline(std::cin, author);
                std::cout << "Enter genre: ";
                getline(std::cin, genre);
                std::cout << "Enter date: ";
                getline(std::cin, date);

                int price, quantity;
                char cont = 'y';
                while (cont == 'y') {
                    std::cout << "Enter ticket price: ";
                    std::cin >> price;
                    std::cout << "Enter quantity: ";
                    std::cin >> quantity;
                    tickets[price] = quantity;
                    std::cout << "Add more tickets? (y/n): ";
                    std::cin >> cont;
                    std::cin.ignore();
                }

                manager.addPerformance(Performance(title, author, genre, date, tickets));
                std::cout << "New performance added.\n";
                break;
            }
            case 2: {
                std::string title;
                std::cout << "Enter the title of the performance to edit: ";
                getline(std::cin, title);
                manager.editPerformance(title);
                break;
            }
            case 3: {
                std::string title;
                std::cout << "Enter the title of the performance to remove: ";
                getline(std::cin, title);
                manager.removePerformance(title);
                break;
            }
            case 4: {
                std::string title;
                std::cout << "Enter the title of the performance to update ticket prices: ";
                getline(std::cin, title);
                manager.updateTicketPrices(title);
                break;
            }
            case 5:
                return;
            default:
                std::cout << "Invalid option, please try again.\n";
        }
    }
}