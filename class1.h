#include <iostream>
#include <map>
#include <string>

class Performance {
private:
    std::string title;
    std::string author;
    std::string genre;
    std::string date;
    std::map<int, int> availableTickets;
    std::map<int, int> reservedTickets;
    std::map<int, int> soldTickets;
    std::map<int, int> tickets;
public:
    
    Performance(const std::string& title, const std::string& author, const std::string& genre, const std::string& date, const std::map<int, int>& tickets)
        : title(title), author(author), genre(genre), date(date), availableTickets(tickets) {}

    
    const std::string& getTitle() const { return title; }
    const std::string& getAuthor() const { return author; }
    const std::string& getGenre() const { return genre; }
    const std::string& getDate() const { return date; }
    const std::map<int, int>& getTickets() const { return tickets; }


    void displayTicketDetails() const {
        std::cout << "Ticket Details (Available / Reserved / Sold):" << std::endl;
        for (const auto& pair : availableTickets) {
            int reserved = reservedTickets.count(pair.first) ? reservedTickets.at(pair.first) : 0;
            int sold = soldTickets.count(pair.first) ? soldTickets.at(pair.first) : 0;
            std::cout << "Price: $" << pair.first << " - Available: " << pair.second << " / Reserved: " << reserved << " / Sold: " << sold << std::endl;
        }
    }
    void updateTickets(const std::map<int, int>& newTickets) {
         availableTickets = newTickets;
     }

    bool reserveTicket(int price) {
        if (availableTickets[price] > 0) {
            availableTickets[price]--;
            reservedTickets[price]++;
            return true;
        }
        return false;
    }

    bool sellTicket(int price) {
        if (availableTickets[price] > 0) {
            availableTickets[price]--;
            soldTickets[price]++;
            return true;
        }
        return false;
    }

    bool cancelReservation(int price) {
        if (reservedTickets.find(price) != reservedTickets.end() && reservedTickets[price] > 0) {
            reservedTickets[price]--;
            availableTickets[price]++;
            return true;
        }
        return false;
    }

    bool confirmReservation(int price) {
        if (reservedTickets.find(price) != reservedTickets.end() && reservedTickets[price] > 0) {
            reservedTickets[price]--;
            soldTickets[price]++;
            return true;
        }
        return false;
    }
};
