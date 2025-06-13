#include "CommandHandler.h"
#include <iostream>
#include <stdexcept>

CinemaCommandHandler::CinemaCommandHandler(CinemaSystem& cinemaSystem)
    : system(cinemaSystem) {}

MyVector<MyString> CinemaCommandHandler::parseCommand(const MyString& commandLine) {
    MyVector<MyString> tokens;
    const char* str = commandLine.c_str();
    int len = 0;

    // Calculate length of the string
    while (str[len] != '\0') {
        len++;
    }

    int i = 0;
    while (i < len) {
        // Skip whitespace
        while (i < len && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')) {
            i++;
        }

        if (i >= len) break;

        // Find the start of the token
        int start = i;

        // Find the end of the token
        while (i < len && str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r') {
            i++;
        }

        // Extract the token
        if (i > start) {
            int tokenLen = i - start;
            char* token = new char[tokenLen + 1];

            for (int j = 0; j < tokenLen; j++) {
                token[j] = str[start + j];
            }
            token[tokenLen] = '\0';

            tokens.push_back(MyString(token));
            delete[] token;
        }
    }

    return tokens;
}

bool CinemaCommandHandler::requireLogin() const {
    if (system.getCurrentUser() == nullptr) {
        std::cout << "Error: You must be logged in to use this command." << std::endl;
        return false;
    }
    return true;
}

bool CinemaCommandHandler::requireAdmin() const {
    if (!requireLogin()) {
        return false;
    }

    if (!system.getCurrentUser()->getIsAdmin()) {
        std::cout << "Error: This command requires administrator privileges." << std::endl;
        return false;
    }
    return true;
}



void CinemaCommandHandler::dispatch(const MyString& commandLine) {
    try {
        MyVector<MyString> tokens = parseCommand(commandLine);

        if (tokens.getSize() == 0) {
            return; // Empty command
        }

        MyString command = tokens[0];

        // Convert to lowercase for case-insensitive comparison
        const char* cmdStr = command.c_str();
        int cmdLen = 0;
        while (cmdStr[cmdLen] != '\0') {
            cmdLen++;
        }

        char* lowerCmd = new char[cmdLen + 1];
        for (int i = 0; i < cmdLen; i++) {
            if (cmdStr[i] >= 'A' && cmdStr[i] <= 'Z') {
                lowerCmd[i] = cmdStr[i] + ('a' - 'A');
            }
            else {
                lowerCmd[i] = cmdStr[i];
            }
        }
        lowerCmd[cmdLen] = '\0';

        // Helper function to compare strings
        auto strEquals = [](const char* a, const char* b) {
            int i = 0;
            while (a[i] != '\0' && b[i] != '\0') {
                if (a[i] != b[i]) return false;
                i++;
            }
            return a[i] == '\0' && b[i] == '\0';
            };

        // User management commands
        if (strEquals(lowerCmd, "login")) {
            login(tokens);
        }
        else if (strEquals(lowerCmd, "logout")) {
            logout(tokens);
        }
        else if (strEquals(lowerCmd, "register")) {
            register_user(tokens);
        }
        else if (strEquals(lowerCmd, "profile")) {
            show_profile(tokens);
        }
        else if (strEquals(lowerCmd, "addbalance")) {
            add_balance(tokens);
        }
        // Movie management commands
        else if (strEquals(lowerCmd, "addmovie")) {
            add_movie(tokens);
        }
        else if (strEquals(lowerCmd, "removemovie")) {
            remove_movie(tokens);
        }
        else if (strEquals(lowerCmd, "listmovies")) {
            list_movies(tokens);
        }
        else if (strEquals(lowerCmd, "showmovie")) {
            show_movie(tokens);
        }
        // Room management commands
        else if (strEquals(lowerCmd, "open-haul")) {
            open_haul(tokens);
        }
        else if (strEquals(lowerCmd, "close-haul")) {
            close_haul(tokens);
        }
        else if (strEquals(lowerCmd, "listrooms")) {
            list_rooms(tokens);
        }
        else if (strEquals(lowerCmd, "showroom")) {
            show_room(tokens);
        }
        // Booking commands
        else if (strEquals(lowerCmd, "buy-ticket")) {
            buy_ticket(tokens);
        }
        else if (strEquals(lowerCmd, "tickets")) {
            list_tickets(tokens);
        }
        else if (strEquals(lowerCmd, "check-if-ticket-expired")) {
            checkIfTicketExpired(tokens);
        }
        // Rating commands
        else if (strEquals(lowerCmd, "rate")) {
            rate_movie(tokens);
        }
        else if (strEquals(lowerCmd, "update-movie-title")) {
            update_movie_title(tokens);
        }
        else if (strEquals(lowerCmd, "update-movie-haul")) {
            update_movie_haul(tokens);
        }
        else if (strEquals(lowerCmd, "list-user-history")) {
            list_user_history(tokens);
        }
        else if (strEquals(lowerCmd, "list-user-tickets")) {
            list_user_tickets_admin(tokens);
        }
        else if (strEquals(lowerCmd, "list-users")) {
            list_users(tokens);
        }
        else if (strEquals(lowerCmd, "remove-user")) {
            remove_user(tokens);
        }


        // Utility commands
        else if (strEquals(lowerCmd, "help")) {
            help(tokens);
        }

        
        else if (strEquals(lowerCmd, "quit") || strEquals(lowerCmd, "exit")) {
            quit(tokens);
        }
        else {
            std::cout << "Unknown command: " << command << std::endl;
            std::cout << "Type 'help' for available commands." << std::endl;
        }

        delete[] lowerCmd;
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void CinemaCommandHandler::login(const MyVector<MyString>& inputs) {
    if (inputs.getSize() != 3) {
        std::cout << "Usage: login <username> <password>" << std::endl;
        return;
    }

    if (system.getCurrentUser() != nullptr) {
        std::cout << "Already logged in as " << system.getCurrentUser()->getUsername() << std::endl;
        return;
    }

    try {
        MyString username = inputs[1];
        MyString password = inputs[2];

        User* user = system.findUserByUsername(username);
        if (user == nullptr) {
            std::cout << "Error: User not found." << std::endl;
            return;
        }

        if (user->getPassword() != password) {
            std::cout << "Error: Incorrect password." << std::endl;
            return;
        }

        system.setCurrentUser(user);
        std::cout << "Login successful. Welcome, " << user->getUsername() << "!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Login failed: " << e.what() << std::endl;
    }
}

void CinemaCommandHandler::logout(const MyVector<MyString>& inputs) {
    if (!requireLogin()) {
        return;
    }

    std::cout << "Goodbye, " << system.getCurrentUser()->getUsername() << "!" << std::endl;
    system.setCurrentUser(nullptr);
}

void CinemaCommandHandler::register_user(const MyVector<MyString>& inputs) {
    if (inputs.getSize() != 3) {
        std::cout << "Usage: register <username> <password>" << std::endl;
        return;
    }

    try {
        MyString username = inputs[1];
        MyString password = inputs[2];

        // Check if user already exists
        if (system.findUserByUsername(username) != nullptr) {
            std::cout << "Error: Username already exists." << std::endl;
            return;
        }

        User newUser(username, password, false, MyVector<Ticket>(), MyVector<unsigned>(), 0.0);
        system.users.push_back(newUser);

        std::cout << "Registration successful! You can now log in." << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Registration failed: " << e.what() << std::endl;
    }
}

void CinemaCommandHandler::show_profile(const MyVector<MyString>& inputs) {
    if (!requireLogin()) {
        return;
    }

    unsigned ticketCount = system.getCurrentUser()->getTickets().getSize();
    unsigned watchedMoviesCount = system.getCurrentUser()->getWatchedMovieIds().getSize();

    std::cout << "User info:" << '\n';
    std::cout << "Username: " << system.getCurrentUser()->getUsername() << '\n';
    std::cout << "Password: " << system.getCurrentUser()->getPassword() << '\n';
    std::cout << "Is an admin: " << (system.getCurrentUser()->getIsAdmin() ? "yes" : "no") << '\n';
    std::cout << "Ticket count: " << system.getCurrentUser()->getTickets().getSize() << '\n';
    std::cout << "Tickets:" << '\n';

    const MyVector<Ticket> tickets = system.getCurrentUser()->getTickets();
    const MyVector<unsigned int> watchedMovieIds = (*system.getCurrentUser()).getWatchedMovieIds();

    for (unsigned i = 0; i < ticketCount; i++)
    {
        tickets[i].printTicketInfo();
    }
    std::cout << "Watched movie count: " << watchedMovieIds.getSize() << '\n';
    std::cout << "Watched movies:" << '\n';
    for (unsigned i = 0; i < watchedMoviesCount; i++)
    {
        std::cout << watchedMovieIds[i] << ' ' << system.getMovieByIndex(i)->getTitle() << '\n';
    }
    std::cout << "Balance: " << system.getCurrentUser()->getBalance() << '\n';
    
    
}

void CinemaCommandHandler::add_balance(const MyVector<MyString>& inputs) {
    if (!requireLogin()) {
        return;
    }

    if (inputs.getSize() != 2) {
        std::cout << "Usage: addbalance <amount>" << std::endl;
        return;
    }

    try {
        // Manual string to double conversion
        const char* str = inputs[1].c_str();
        double amount = 0.0;
        double fraction = 0.0;
        bool isNegative = false;
        bool afterDecimal = false;
        double divisor = 10.0;

        int i = 0;
        if (str[0] == '-') {
            isNegative = true;
            i = 1;
        }

        while (str[i] != '\0') {
            if (str[i] == '.') {
                afterDecimal = true;
            }
            else if (str[i] >= '0' && str[i] <= '9') {
                if (afterDecimal) {
                    fraction += (str[i] - '0') / divisor;
                    divisor *= 10.0;
                }
                else {
                    amount = amount * 10.0 + (str[i] - '0');
                }
            }
            else {
                throw std::invalid_argument("Invalid number format");
            }
            i++;
        }

        amount += fraction;
        if (isNegative) amount = -amount;

        if (amount <= 0) {
            std::cout << "Error: Amount must be positive." << std::endl;
            return;
        }

        double newBalance = system.getCurrentUser()->getBalance() + amount;
        system.getCurrentUser()->setBalance(newBalance);

        std::cout << "Balance updated. New balance: " << newBalance << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Error adding balance: " << e.what() << std::endl;
    }
}

void CinemaCommandHandler::list_movies(const MyVector<MyString>& inputs) {
    std::cout << "=== Available Movies ===" << std::endl;

    if (system.getMoviesCount() == 0) {
        std::cout << "No movies available." << std::endl;
        return;
    }

    for (size_t i = 0; i < system.getMoviesCount(); i++) {
        Movie* movie = system.getMovieByIndex(i);
        if (movie != nullptr) {
            std::cout << "Movie ID: " << movie->getId() << std::endl;
            movie->printInfo();
            std::cout << "------------------------" << std::endl;
        }
    }
}

void CinemaCommandHandler::show_movie(const MyVector<MyString>& inputs) {
    if (inputs.getSize() != 2) {
        std::cout << "Usage: showmovie <movie_id>" << std::endl;
        return;
    }

    try {
        // Manual string to unsigned conversion
        const char* str = inputs[1].c_str();
        unsigned movieId = 0;
        int i = 0;

        while (str[i] != '\0') {
            if (str[i] >= '0' && str[i] <= '9') {
                movieId = movieId * 10 + (str[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid number format");
            }
            i++;
        }

        // Find movie by ID
        Movie* movie = nullptr;
        for (size_t i = 0; i < system.getMoviesCount(); i++) {
            if (system.getMovieByIndex(i)->getId() == movieId) {
                movie = system.getMovieByIndex(i);
                break;
            }
        }

        if (movie == nullptr) {
            std::cout << "Error: Movie with ID " << movieId << " not found." << std::endl;
            return;
        }

        movie->printInfo();
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void CinemaCommandHandler::list_rooms(const MyVector<MyString>& inputs) {
    std::cout << "=== Available Rooms ===" << std::endl;

    if (system.getRoomsCount() == 0) {
        std::cout << "No rooms available." << std::endl;
        return;
    }

    for (size_t i = 0; i < system.getRoomsCount(); i++) {
        const Room& room = system.getRoomByIndex(i);
        std::cout << "Room ID: " << room.getID() << std::endl;
        room.printInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void CinemaCommandHandler::show_room(const MyVector<MyString>& inputs) {
    if (inputs.getSize() != 2) {
        std::cout << "Usage: showroom <room_id>" << std::endl;
        return;
    }

    try {
        // Manual string to unsigned conversion
        const char* str = inputs[1].c_str();
        unsigned roomId = 0;
        int i = 0;

        while (str[i] != '\0') {
            if (str[i] >= '0' && str[i] <= '9') {
                roomId = roomId * 10 + (str[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid number format");
            }
            i++;
        }

        // Find room by ID
        const Room* room = nullptr;
        for (size_t i = 0; i < system.getRoomsCount(); i++) {
            if (system.getRoomByIndex(i).getID() == roomId) {
                room = &system.getRoomByIndex(i);
                break;
            }
        }

        if (room == nullptr) {
            std::cout << "Error: Room with ID " << roomId << " not found." << std::endl;
            return;
        }

        room->printInfo();
        std::cout << '\n';
        std::cout << "Current seat reservations: 1 for taken, 0 for free." << '\n';

        unsigned roomCols = room->getCols();
        unsigned roomRows = room->getRows();

        for (unsigned i = 0; i < roomRows; i++)
        {
            for (unsigned j = 0; j < roomCols; j++)
            {
                std::cout << room->getSeat(i, j).getReserved() << ' ';
            }
            std::cout << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void CinemaCommandHandler::list_tickets(const MyVector<MyString>& inputs) {
    if (!requireLogin()) {
        return;
    }

    const MyVector<Ticket> tickets = system.getCurrentUser()->getTickets();

    if (tickets.getSize() == 0) {
        std::cout << "You have no tickets." << std::endl;
        return;
    }

    std::cout << "=== Your Tickets ===" << std::endl;
    for (size_t i = 0; i < tickets.getSize(); i++) {
        std::cout << "Ticket " << (i + 1) << ":" << std::endl;
        tickets[i].printTicketInfo();
        std::cout << "------------------------" << std::endl;
    }
}

void CinemaCommandHandler::help(const MyVector<MyString>& inputs) {
    std::cout << "=== Cinema System Commands ===" << std::endl;
    std::cout << "User Commands:" << std::endl;
    std::cout << "  login <username> <password> - Log in to the system" << std::endl;
    std::cout << "  logout                      - Log out from the system" << std::endl;
    std::cout << "  register <username> <password> - Register a new account" << std::endl;
    std::cout << "  profile                     - Show your profile information" << std::endl;
    std::cout << "  addbalance <amount>         - Add money to your balance" << std::endl;
    std::cout << std::endl;
    std::cout << "Movie Commands:" << std::endl;
    std::cout << "  listmovies                  - List all available movies" << std::endl;
    std::cout << "  showmovie <movie_id>        - Show detailed movie information" << std::endl;
    std::cout << std::endl;
    std::cout << "Room Commands:" << std::endl;
    std::cout << "  listrooms                   - List all available rooms" << std::endl;
    std::cout << "  showroom <room_id>          - Show detailed room information" << std::endl;
    std::cout << std::endl;
    std::cout << "Booking Commands:" << std::endl;
    std::cout << "  buy-ticket <movie_id> <row> <col> - Book a ticket for a movie TODO" << std::endl;
    std::cout << "  cancel <ticket_id>          - Cancel a ticket TODO" << std::endl;
    std::cout << "  tickets                     - List your tickets" << std::endl;
    std::cout << std::endl;
    std::cout << "Rating Commands:" << std::endl;
    std::cout << "  rate <movie_id> <rating>    - Rate a movie (1-10) TODO" << std::endl;
    std::cout << "  ratings <movie_id>          - Show ratings for a movie" << std::endl;
    std::cout << std::endl;
    std::cout << "System Commands:" << std::endl;
    std::cout << "  help                        - Show this help message" << std::endl;
    std::cout << "  quit/exit                   - Exit the system" << std::endl;

    if (system.getCurrentUser() != nullptr && system.getCurrentUser()->getIsAdmin()) {
        std::cout << std::endl;
        std::cout << "Admin Commands:" << std::endl;
        std::cout << "  addmovie <title> <length> <year> <genre> <room_id> <date> <time> TODO" << std::endl;
        std::cout << "  removemovie <movie_id>      - Remove a movie TODO" << std::endl;
        std::cout << "  addroom <rows> <cols>       - Add a new room TODO" << std::endl;
        std::cout << "  removeroom <room_id>        - Remove a room TODO" << std::endl;
    }
}

void CinemaCommandHandler::quit(const MyVector<MyString>& inputs) {
    std::cout << "Thank you for using the Cinema System. Goodbye!" << std::endl;
    exit(0);
}

// Placeholder implementations for admin and booking functions
void CinemaCommandHandler::add_movie(const MyVector<MyString>& inputs) {
    if (!requireAdmin()) {
        return;
    }

    // Expected format: addmovie <title> <length> <year> <genre> <room_id> <date> <time> [genre_specific_params]
    // Action: addmovie "Title" 120 2024 action 1 15/06/2024 19:30 15
    // Drama: addmovie "Title" 120 2024 drama 1 15/06/2024 19:30 1 (1 for comedy elements, 0 for no)
    // Documentary: addmovie "Title" 120 2024 documentary 1 15/06/2024 19:30 "Science" 1 (theme, 1 for true events, 0 for no)

    if (inputs.getSize() < 8) {
        std::cout << "Usage: addmovie <title> <length> <year> <genre> <room_id> <date> <time> [genre_specific_params]" << std::endl;
        std::cout << "Genres: action, drama, documentary" << std::endl;
        std::cout << "Date format: dd/mm/yyyy" << std::endl;
        std::cout << "Time format: hh:mm" << std::endl;
        std::cout << "Action movies require intensity (0-20)" << std::endl;
        std::cout << "Drama movies require comedy elements flag (0 or 1)" << std::endl;
        std::cout << "Documentary movies require theme and true events flag (0 or 1)" << std::endl;
        return;
    }

    try {
        MyString title = inputs[1];

        // Parse length
        const char* lengthStr = inputs[2].c_str();
        unsigned length = 0;
        int i = 0;
        while (lengthStr[i] != '\0') {
            if (lengthStr[i] >= '0' && lengthStr[i] <= '9') {
                length = length * 10 + (lengthStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid length format");
            }
            i++;
        }

        // Parse year
        const char* yearStr = inputs[3].c_str();
        unsigned year = 0;
        i = 0;
        while (yearStr[i] != '\0') {
            if (yearStr[i] >= '0' && yearStr[i] <= '9') {
                year = year * 10 + (yearStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid year format");
            }
            i++;
        }

        // Parse genre
        MyString genreStr = inputs[4];
        const char* genreCStr = genreStr.c_str();
        int genreLen = 0;
        while (genreCStr[genreLen] != '\0') {
            genreLen++;
        }

        char* lowerGenre = new char[genreLen + 1];
        for (int j = 0; j < genreLen; j++) {
            if (genreCStr[j] >= 'A' && genreCStr[j] <= 'Z') {
                lowerGenre[j] = genreCStr[j] + ('a' - 'A');
            }
            else {
                lowerGenre[j] = genreCStr[j];
            }
        }
        lowerGenre[genreLen] = '\0';

        Genre genre;
        auto strEquals = [](const char* a, const char* b) {
            int i = 0;
            while (a[i] != '\0' && b[i] != '\0') {
                if (a[i] != b[i]) return false;
                i++;
            }
            return a[i] == '\0' && b[i] == '\0';
            };

        if (strEquals(lowerGenre, "action")) {
            genre = Genre::ActionMovie;
        }
        else if (strEquals(lowerGenre, "drama")) {
            genre = Genre::DramaMovie;
        }
        else if (strEquals(lowerGenre, "documentary")) {
            genre = Genre::DocumentaryMovie;
        }
        else {
            delete[] lowerGenre;
            std::cout << "Error: Invalid genre. Use: action, drama, or documentary" << std::endl;
            return;
        }
        delete[] lowerGenre;

        // Parse room ID
        const char* roomIdStr = inputs[5].c_str();
        unsigned roomId = 0;
        i = 0;
        while (roomIdStr[i] != '\0') {
            if (roomIdStr[i] >= '0' && roomIdStr[i] <= '9') {
                roomId = roomId * 10 + (roomIdStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid room ID format");
            }
            i++;
        }

        // Verify room exists
        bool roomExists = false;
        for (size_t i = 0; i < system.getRoomsCount(); i++) {
            if (system.getRoomByIndex(i).getID() == roomId) {
                roomExists = true;
                break;
            }
        }

        if (!roomExists) {
            std::cout << "Error: Room with ID " << roomId << " does not exist." << std::endl;
            return;
        }

        // Parse date (dd/mm/yyyy format)
        const char* dateStr = inputs[6].c_str();
        int day = 0, month = 0, yearFromDate = 0;
        i = 0;

        // Parse day
        while (dateStr[i] != '\0' && dateStr[i] != '/') {
            if (dateStr[i] >= '0' && dateStr[i] <= '9') {
                day = day * 10 + (dateStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid date format");
            }
            i++;
        }
        if (dateStr[i] != '/') throw std::invalid_argument("Invalid date format");
        i++; // skip '/'

        // Parse month
        while (dateStr[i] != '\0' && dateStr[i] != '/') {
            if (dateStr[i] >= '0' && dateStr[i] <= '9') {
                month = month * 10 + (dateStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid date format");
            }
            i++;
        }
        if (dateStr[i] != '/') throw std::invalid_argument("Invalid date format");
        i++; // skip '/'

        // Parse year
        while (dateStr[i] != '\0') {
            if (dateStr[i] >= '0' && dateStr[i] <= '9') {
                yearFromDate = yearFromDate * 10 + (dateStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid date format");
            }
            i++;
        }

        Date movieDate(day, month, yearFromDate);

        // Parse time (hh:mm format)
        const char* timeStr = inputs[7].c_str();
        int hour = 0, minute = 0;
        i = 0;

        // Parse hour
        while (timeStr[i] != '\0' && timeStr[i] != ':') {
            if (timeStr[i] >= '0' && timeStr[i] <= '9') {
                hour = hour * 10 + (timeStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid time format");
            }
            i++;
        }
        if (timeStr[i] != ':') throw std::invalid_argument("Invalid time format");
        i++; // skip ':'

        // Parse minute
        while (timeStr[i] != '\0') {
            if (timeStr[i] >= '0' && timeStr[i] <= '9') {
                minute = minute * 10 + (timeStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid time format");
            }
            i++;
        }

        Hour startTime(hour, minute);

        // Create empty ratings vector
        MyVector<Rating> ratings;

        // Create specific movie type based on genre
        Movie* newMovie = nullptr;

        if (genre == Genre::ActionMovie) {
            if (inputs.getSize() != 9) {
                std::cout << "Action movies require intensity parameter (0-20)" << std::endl;
                return;
            }

            // Parse intensity
            const char* intensityStr = inputs[8].c_str();
            unsigned intensity = 0;
            i = 0;
            while (intensityStr[i] != '\0') {
                if (intensityStr[i] >= '0' && intensityStr[i] <= '9') {
                    intensity = intensity * 10 + (intensityStr[i] - '0');
                }
                else {
                    throw std::invalid_argument("Invalid intensity format");
                }
                i++;
            }

            newMovie = new ActionMovie(title, 0.0, length, year, roomId, movieDate, startTime, ratings, intensity);

        }
        else if (genre == Genre::DramaMovie) {
            if (inputs.getSize() != 9) {
                std::cout << "Drama movies require comedy elements flag (0 or 1)" << std::endl;
                return;
            }

            // Parse comedy elements flag
            const char* comedyStr = inputs[8].c_str();
            bool hasComedy = false;
            if (comedyStr[0] == '1' && comedyStr[1] == '\0') {
                hasComedy = true;
            }
            else if (comedyStr[0] == '0' && comedyStr[1] == '\0') {
                hasComedy = false;
            }
            else {
                throw std::invalid_argument("Comedy elements flag must be 0 or 1");
            }

            newMovie = new DramaMovie(title, 0.0, length, year, roomId, movieDate, startTime, hasComedy, ratings);

        }
        else if (genre == Genre::DocumentaryMovie) {
            if (inputs.getSize() != 10) {
                std::cout << "Documentary movies require theme and true events flag (0 or 1)" << std::endl;
                return;
            }

            MyString theme = inputs[8];

            // Parse true events flag
            const char* trueEventsStr = inputs[9].c_str();
            bool isBasedOnTrueEvents = false;
            if (trueEventsStr[0] == '1' && trueEventsStr[1] == '\0') {
                isBasedOnTrueEvents = true;
            }
            else if (trueEventsStr[0] == '0' && trueEventsStr[1] == '\0') {
                isBasedOnTrueEvents = false;
            }
            else {
                throw std::invalid_argument("True events flag must be 0 or 1");
            }

            newMovie = new DocumentaryMovie(title, 0.0, length, year, roomId, movieDate, startTime, ratings, theme, isBasedOnTrueEvents);
        }

        if (newMovie != nullptr) {
            // Add movie to system (assuming there's a method to add movies)
            // Since I don't see the exact method in CinemaSystem, this is a placeholder
            // You'll need to implement this in your CinemaSystem class
            system.addMovie(newMovie);

            std::cout << "Movie added successfully!" << std::endl;
            std::cout << "Movie ID: " << newMovie->getId() << std::endl;
            std::cout << "Title: " << title << std::endl;
            std::cout << "Length: " << length << " minutes" << std::endl;
            std::cout << "Year: " << year << std::endl;
            std::cout << "Genre: " << genreStr << std::endl;
            std::cout << "Room ID: " << roomId << std::endl;
            std::cout << "Date: " << movieDate << std::endl;
            std::cout << "Start Time: " << startTime << std::endl;
            std::cout << "Ticket Price: " << newMovie->calculatePrice() << " BGN" << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cout << "Error adding movie: " << e.what() << std::endl;
    }
}


void CinemaCommandHandler::remove_movie(const MyVector<MyString>& inputs) {
    if (!requireAdmin()) {
        return;
    }
    std::cout << "Remove movie functionality not yet implemented." << std::endl;
}

void CinemaCommandHandler::open_haul(const MyVector<MyString>& inputs) {
    if (!requireAdmin()) {
        return;
    }

    if (inputs.getSize() != 3) {
        std::cout << "Usage: addroom <rows> <cols>" << std::endl;
        std::cout << "Example: addroom 10 12 (creates a room with 10 rows and 12 columns)" << std::endl;
        return;
    }

    try {
        // Parse rows
        const char* rowsStr = inputs[1].c_str();
        unsigned rows = 0;
        int i = 0;
        while (rowsStr[i] != '\0') {
            if (rowsStr[i] >= '0' && rowsStr[i] <= '9') {
                rows = rows * 10 + (rowsStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid rows format - must be a positive number");
            }
            i++;
        }

        // Parse columns
        const char* colsStr = inputs[2].c_str();
        unsigned cols = 0;
        i = 0;
        while (colsStr[i] != '\0') {
            if (colsStr[i] >= '0' && colsStr[i] <= '9') {
                cols = cols * 10 + (colsStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid columns format - must be a positive number");
            }
            i++;
        }

        // Validate input ranges
        if (rows == 0 || cols == 0) {
            std::cout << "Error: Rows and columns must be greater than 0." << std::endl;
            return;
        }

        if (rows > 50 || cols > 50) {
            std::cout << "Error: Maximum 50 rows and 50 columns allowed." << std::endl;
            return;
        }

        // Create new room with specified dimensions
        Room newRoom(rows, cols);

        // Add room to the system
        system.rooms.push_back(newRoom);

        // Save rooms to file to persist the changes
        try {
            system.saveRooms();
        }
        catch (const std::exception& e) {
            std::cout << "Warning: Room created but could not save to file: " << e.what() << std::endl;
        }

        std::cout << "Room created successfully!" << std::endl;
        std::cout << "Room ID: " << newRoom.getID() << std::endl;
        std::cout << "Dimensions: " << rows << " rows x " << cols << " columns" << std::endl;
        std::cout << "Total seats: " << (rows * cols) << std::endl;
        std::cout << "All seats are initially available for booking." << std::endl;

    }
    catch (const std::exception& e) {
        std::cout << "Error creating room: " << e.what() << std::endl;
    }
}

void CinemaCommandHandler::close_haul(const MyVector<MyString>& inputs) {
    if (!requireAdmin()) {
        return;
    }

    if (inputs.getSize() != 2) {
        std::cout << "Usage: close-haul <room_id>" << std::endl;
        std::cout << "Example: close-haul 5 (removes room with ID 5)" << std::endl;
        return;
    }

    try {
        // Parse room ID
        const char* roomIdStr = inputs[1].c_str();
        unsigned roomId = 0;
        int i = 0;

        while (roomIdStr[i] != '\0') {
            if (roomIdStr[i] >= '0' && roomIdStr[i] <= '9') {
                roomId = roomId * 10 + (roomIdStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid room ID format - must be a positive number");
            }
            i++;
        }

        // Find the room index
        int roomIndex = -1;
        for (size_t i = 0; i < system.getRoomsCount(); i++) {
            if (system.getRoomByIndex(i).getID() == roomId) {
                roomIndex = static_cast<int>(i);
                break;
            }
        }

        if (roomIndex == -1) {
            std::cout << "Error: Room with ID " << roomId << " not found." << std::endl;
            return;
        }

        // Check if there are any active movies scheduled in this room
        bool hasActiveMovies = false;
        for (size_t i = 0; i < system.getMoviesCount(); i++) {
            Movie* movie = system.getMovieByIndex(i);
            if (movie != nullptr && movie->getRoomId() == roomId) {
                hasActiveMovies = true;
                break;
            }
        }

        if (hasActiveMovies) {
            std::cout << "Warning: This room has movies scheduled. " << std::endl;
            std::cout << "Are you sure you want to close this haul? (This will affect scheduled movies)" << std::endl;
            std::cout << "Room will be closed anyway as per admin request." << std::endl;
        }

        // Store room info for confirmation message
        const Room& roomToRemove = system.getRoomByIndex(roomIndex);
        unsigned rows = roomToRemove.getRows();
        unsigned cols = roomToRemove.getCols();

        // Remove the room from the system
        // Note: You'll need to implement a removeRoom method in CinemaSystem
        // This is a placeholder assuming such method exists
        system.closeHaul(roomIndex);

        // Save rooms to file to persist the changes
        try {
            system.saveRooms();
        }
        catch (const std::exception& e) {
            std::cout << "Warning: Room removed but could not save to file: " << e.what() << std::endl;
        }

        std::cout << "Haul closed successfully!" << std::endl;
        std::cout << "Removed Room ID: " << roomId << std::endl;
        std::cout << "Room dimensions were: " << rows << " rows x " << cols << " columns" << std::endl;
        std::cout << "Total seats removed: " << (rows * cols) << std::endl;

        if (hasActiveMovies) {
            std::cout << "Note: Movies that were scheduled in this room may need to be rescheduled." << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cout << "Error closing haul: " << e.what() << std::endl;
    }
}

void CinemaCommandHandler::buy_ticket(const MyVector<MyString>& inputs) {
    if (!requireLogin()) {
        return;
    }

    if (inputs.getSize() != 4) {
        std::cout << "Usage: book <movie_id> <row> <col>" << std::endl;
        return;
    }

    try {
        // Manual string to unsigned conversion for movie_id
        const char* movieIdStr = inputs[1].c_str();
        unsigned movieId = 0;
        int i = 0;
        while (movieIdStr[i] != '\0') {
            if (movieIdStr[i] >= '0' && movieIdStr[i] <= '9') {
                movieId = movieId * 10 + (movieIdStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid movie ID format");
            }
            i++;
        }

        // Manual string to unsigned conversion for row
        const char* rowStr = inputs[2].c_str();
        unsigned row = 0;
        i = 0;
        while (rowStr[i] != '\0') {
            if (rowStr[i] >= '0' && rowStr[i] <= '9') {
                row = row * 10 + (rowStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid row format");
            }
            i++;
        }

        // Manual string to unsigned conversion for col
        const char* colStr = inputs[3].c_str();
        unsigned col = 0;
        i = 0;
        while (colStr[i] != '\0') {
            if (colStr[i] >= '0' && colStr[i] <= '9') {
                col = col * 10 + (colStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid column format");
            }
            i++;
        }

        // Find the movie
        Movie* movie = nullptr;
        for (size_t i = 0; i < system.getMoviesCount(); i++) {
            if (system.getMovieByIndex(i)->getId() == movieId) {
                movie = system.getMovieByIndex(i);
                break;
            }
        }

        if (movie == nullptr) {
            std::cout << "Error: Movie with ID " << movieId << " not found." << std::endl;
            return;
        }

        // Get the room for this movie
        unsigned roomId = movie->getRoomId();
        Room* room = nullptr;
        size_t roomIndex = 0;

        // Find the room and get its index for modification
        for (size_t i = 0; i < system.getRoomsCount(); i++) {
            if (system.getRoomByIndex(i).getID() == roomId) {
                roomIndex = i;
                room = &const_cast<Room&>(system.getRoomByIndex(i)); // Cast away const to modify
                break;
            }
        }

        if (room == nullptr) {
            std::cout << "Error: Room for this movie not found." << std::endl;
            return;
        }

        // Check if seat coordinates are valid
        if (row == 0 || col == 0 || row > room->getRows() || col > room->getCols()) {
            std::cout << "Error: Invalid seat coordinates. Room has "
                << room->getRows() << " rows and " << room->getCols() << " columns." << std::endl;
            std::cout << "Please use row and column numbers starting from 1." << std::endl;
            return;
        }

        // Check if seat is already taken (convert to 0-based indexing)
        if (room->getSeat(row - 1, col - 1).getReserved()) {
            std::cout << "Error: Seat at row " << row << ", column " << col << " is already taken." << std::endl;
            return;
        }

        // Check if user has enough balance
        double ticketPrice = movie->calculatePrice();
        if (system.getCurrentUser()->getBalance() < ticketPrice) {
            std::cout << "Error: Insufficient balance. Ticket price: " << ticketPrice
                << ", Your balance: " << system.getCurrentUser()->getBalance() << std::endl;
            return;
        }

        // Generate unique ticket ID (simple approach: use current time or counter)
        static unsigned ticketIdCounter = 1000; // Static counter for unique IDs
        unsigned ticketId = ++ticketIdCounter;

        // Create the seat for the ticket (using 1-based indexing as entered by user)
        Seat ticketSeat(row, col, true);

        // Create the ticket
        Ticket newTicket(movieId, ticketSeat, ticketPrice);

        // Add ticket to user's ticket list
        MyVector<Ticket> userTickets = system.getCurrentUser()->getTickets();
        userTickets.push_back(newTicket);
        system.getCurrentUser()->setTickets(userTickets);

        // Mark the seat as taken in the room (convert to 0-based indexing)
        room->getSeat(row - 1, col - 1).setReserved(true);

        // Deduct the price from user's balance
        /*double newBalance = system.getCurrentUser()->getBalance() - ticketPrice;
        system.getCurrentUser()->setBalance(newBalance);*/

        // Add movie to watched movies if not already there
        MyVector<unsigned> watchedMovies = system.getCurrentUser()->getWatchedMovieIds();
        bool alreadyWatched = false;
        for (unsigned i = 0; i < watchedMovies.getSize(); i++) {
            if (watchedMovies[i] == movieId) {
                alreadyWatched = true;
                break;
            }
        }
        if (!alreadyWatched) {
            watchedMovies.push_back(movieId);
            system.getCurrentUser()->setWatchedMovieIds(watchedMovies);
        }

        std::cout << "Ticket booked successfully!" << std::endl;
        std::cout << "Ticket ID: " << ticketId << std::endl;
        std::cout << "Movie: " << movie->getTitle() << std::endl;
        std::cout << "Seat: Row " << row << ", Column " << col << std::endl;
        std::cout << "Date: " << movie->getDate() << std::endl;
        std::cout << "Time: " << movie->getStartTime() << std::endl;
        std::cout << "Price: " << ticketPrice << std::endl;
        /*std::cout << "Remaining balance: " << newBalance << std::endl;*/

    }
    catch (const std::exception& e) {
        std::cout << "Error booking ticket: " << e.what() << std::endl;
    }
}


void CinemaCommandHandler::rate_movie(const MyVector<MyString>& inputs) {
    if (!requireLogin()) {
        return;
    }

    if (inputs.getSize() != 3) {
        std::cout << "Usage: rate <movie_id> <rating>" << std::endl;
        std::cout << "Rating should be between 1 and 10" << std::endl;
        return;
    }

    try {
        // Parse movie ID
        const char* movieIdStr = inputs[1].c_str();
        unsigned movieId = 0;
        int i = 0;

        // Manual string to unsigned conversion
        while (movieIdStr[i] != '\0') {
            if (movieIdStr[i] >= '0' && movieIdStr[i] <= '9') {
                movieId = movieId * 10 + (movieIdStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid movie ID format");
            }
            i++;
        }

        // Parse rating
        const char* ratingStr = inputs[2].c_str();
        double rating = 0.0;
        double fraction = 0.0;
        bool afterDecimal = false;
        double divisor = 10.0;
        i = 0;

        while (ratingStr[i] != '\0') {
            if (ratingStr[i] == '.') {
                afterDecimal = true;
            }
            else if (ratingStr[i] >= '0' && ratingStr[i] <= '9') {
                if (afterDecimal) {
                    fraction += (ratingStr[i] - '0') / divisor;
                    divisor *= 10.0;
                }
                else {
                    rating = rating * 10.0 + (ratingStr[i] - '0');
                }
            }
            else {
                throw std::invalid_argument("Invalid rating format");
            }
            i++;
        }

        rating += fraction;

        // Validate rating range
        if (rating < 1.0 || rating > 10.0) {
            std::cout << "Error: Rating must be between 1 and 10." << std::endl;
            return;
        }

        // Find the movie
        Movie* movie = nullptr;
        for (size_t j = 0; j < system.getMoviesCount(); j++) {
            Movie* currentMovie = system.getMovieByIndex(j);
            if (currentMovie != nullptr && currentMovie->getId() == movieId) {
                movie = currentMovie;
                break;
            }
        }

        if (movie == nullptr) {
            std::cout << "Error: Movie with ID " << movieId << " not found." << std::endl;
            return;
        }

        // Check if user has watched this movie (if this validation is required)
        const MyVector<unsigned>& watchedMovies = system.getCurrentUser()->getWatchedMovieIds();
        bool hasWatched = false;
        for (size_t k = 0; k < watchedMovies.getSize(); k++) {
            if (watchedMovies[k] == movieId) {
                hasWatched = true;
                break;
            }
        }

        if (!hasWatched) {
            std::cout << "Error: You can only rate movies you have watched." << std::endl;
            return;
        }

        // Check if user has already rated this movie
        const MyVector<Rating>& existingRatings = movie->getRatings();
        MyString currentUsername = system.getCurrentUser()->getUsername();

        for (size_t l = 0; l < existingRatings.getSize(); l++) {
            if (existingRatings[l].getUsername() == currentUsername) {
                std::cout << "Error: You have already rated this movie." << std::endl;
                return;
            }
        }

        // Create and add the rating
        Rating newRating(currentUsername, rating);
        movie->addRating(newRating);

        std::cout << "Rating added successfully!" << std::endl;
        std::cout << "Movie: " << movie->getTitle() << std::endl;
        std::cout << "Your rating: " << rating << "/10" << std::endl;
        std::cout << "New average rating: " << movie->getAverageRating() << "/10" << std::endl;

    }
    catch (const std::exception& e) {
        std::cout << "Error rating movie: " << e.what() << std::endl;
    }
}

void CinemaCommandHandler::update_movie_title(const MyVector<MyString>& inputs) {
    if (!requireAdmin()) {
        return;
    }

    if (inputs.getSize() != 3) {
        std::cout << "Usage: update-movie-title <movieId> <newTitle>" << std::endl;
        return;
    }

    try {
        // Parse movie ID
        const char* movieIdStr = inputs[1].c_str();
        unsigned movieId = 0;
        int i = 0;
        while (movieIdStr[i] != '\0') {
            if (movieIdStr[i] >= '0' && movieIdStr[i] <= '9') {
                movieId = movieId * 10 + (movieIdStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid movie ID format");
            }
            i++;
        }

        // Find the movie
        Movie* movie = nullptr;
        for (size_t i = 0; i < system.getMoviesCount(); i++) {
            if (system.getMovieByIndex(i)->getId() == movieId) {
                movie = system.getMovieByIndex(i);
                break;
            }
        }

        if (movie == nullptr) {
            std::cout << "Error: Movie with ID " << movieId << " not found." << std::endl;
            return;
        }

        MyString newTitle = inputs[2];
        MyString oldTitle = movie->getTitle();

        // Update the movie title
        movie->setTitle(newTitle);

        // Save movies to persist changes
        try {
            system.saveMovies();
        }
        catch (const std::exception& e) {
            std::cout << "Warning: Title updated but could not save to file: " << e.what() << std::endl;
        }

        std::cout << "Movie title updated successfully!" << std::endl;
        std::cout << "Movie ID: " << movieId << std::endl;
        std::cout << "Old title: " << oldTitle << std::endl;
        std::cout << "New title: " << newTitle << std::endl;
        std::cout << "The change will be reflected in user profiles." << std::endl;

    }
    catch (const std::exception& e) {
        std::cout << "Error updating movie title: " << e.what() << std::endl;
    }
}

void CinemaCommandHandler::update_movie_haul(const MyVector<MyString>& inputs) {
    if (!requireAdmin()) {
        return;
    }

    if (inputs.getSize() != 3) {
        std::cout << "Usage: update-movie-haul <movieId> <newHaulId>" << std::endl;
        return;
    }

    try {
        // Parse movie ID
        const char* movieIdStr = inputs[1].c_str();
        unsigned movieId = 0;
        int i = 0;
        while (movieIdStr[i] != '\0') {
            if (movieIdStr[i] >= '0' && movieIdStr[i] <= '9') {
                movieId = movieId * 10 + (movieIdStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid movie ID format");
            }
            i++;
        }

        // Parse new room/haul ID
        const char* roomIdStr = inputs[2].c_str();
        unsigned newRoomId = 0;
        i = 0;
        while (roomIdStr[i] != '\0') {
            if (roomIdStr[i] >= '0' && roomIdStr[i] <= '9') {
                newRoomId = newRoomId * 10 + (roomIdStr[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid room ID format");
            }
            i++;
        }

        // Find the movie
        Movie* movie = nullptr;
        for (size_t i = 0; i < system.getMoviesCount(); i++) {
            if (system.getMovieByIndex(i)->getId() == movieId) {
                movie = system.getMovieByIndex(i);
                break;
            }
        }

        if (movie == nullptr) {
            std::cout << "Error: Movie with ID " << movieId << " not found." << std::endl;
            return;
        }

        // Verify new room exists
        bool roomExists = false;
        for (size_t i = 0; i < system.getRoomsCount(); i++) {
            if (system.getRoomByIndex(i).getID() == newRoomId) {
                roomExists = true;
                break;
            }
        }

        if (!roomExists) {
            std::cout << "Error: Room with ID " << newRoomId << " does not exist." << std::endl;
            return;
        }

        unsigned oldRoomId = movie->getRoomId();

        // Check if it's actually a change
        if (oldRoomId == newRoomId) {
            std::cout << "Error: Movie is already in room " << newRoomId << std::endl;
            return;
        }

        // Update the movie's room
        movie->setRoomId(newRoomId);

        // Save movies to persist changes
        try {
            system.saveMovies();
        }
        catch (const std::exception& e) {
            std::cout << "Warning: Room updated but could not save to file: " << e.what() << std::endl;
        }

        std::cout << "Movie moved to new room successfully!" << std::endl;
        std::cout << "Movie: " << movie->getTitle() << " (ID: " << movieId << ")" << std::endl;
        std::cout << "Old room ID: " << oldRoomId << std::endl;
        std::cout << "New room ID: " << newRoomId << std::endl;
        std::cout << "Note: Existing tickets remain valid but seat reservations may need to be managed manually." << std::endl;

    }
    catch (const std::exception& e) {
        std::cout << "Error moving movie to new room: " << e.what() << std::endl;
    }
}

void CinemaCommandHandler::list_user_history(const MyVector<MyString>& inputs) {
    if (inputs.getSize() != 2) {
        std::cout << "Usage: list-user-history <username>" << std::endl;
        return;
    }

    try {
        MyString username = inputs[1];

        // Find the user
        User* user = system.findUserByUsername(username);
        if (user == nullptr) {
            std::cout << "Error: User '" << username << "' not found." << std::endl;
            return;
        }

        const MyVector<unsigned> watchedMovieIds = user->getWatchedMovieIds();

        if (watchedMovieIds.getSize() == 0) {
            std::cout << "User '" << username << "' has not watched any movies yet." << std::endl;
            return;
        }

        std::cout << "=== Movie History for User: " << username << " ===" << std::endl;
        std::cout << "Total movies watched: " << watchedMovieIds.getSize() << std::endl;
        std::cout << std::endl;

        for (unsigned i = 0; i < watchedMovieIds.getSize(); i++) {
            unsigned movieId = watchedMovieIds[i];

            // Find the movie details
            Movie* movie = nullptr;
            for (size_t j = 0; j < system.getMoviesCount(); j++) {
                if (system.getMovieByIndex(j)->getId() == movieId) {
                    movie = system.getMovieByIndex(j);
                    break;
                }
            }

            std::cout << (i + 1) << ". ";
            if (movie != nullptr) {
                std::cout << "Movie ID: " << movieId << std::endl;
                std::cout << "   Title: " << movie->getTitle() << std::endl;
                std::cout << "   Year: " << movie->getYear() << std::endl;
                std::cout << "   Length: " << movie->getLength() << " minutes" << std::endl;
                std::cout << "   Average Rating: " << movie->getAverageRating() << "/10" << std::endl;
            }
            else {
                std::cout << "Movie ID: " << movieId << " (Movie details not available - may have been removed)" << std::endl;
            }
            std::cout << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cout << "Error retrieving user history: " << e.what() << std::endl;
    }
}

void CinemaCommandHandler::list_user_tickets_admin(const MyVector<MyString>& inputs) {
    if (!requireAdmin()) {
        return;
    }

    if (inputs.getSize() != 2) {
        std::cout << "Usage: list-user-tickets <username>" << std::endl;
        return;
    }

    try {
        MyString username = inputs[1];

        // Find the user
        User* user = system.findUserByUsername(username);
        if (user == nullptr) {
            std::cout << "Error: User '" << username << "' not found." << std::endl;
            return;
        }

        const MyVector<Ticket> tickets = user->getTickets();

        if (tickets.getSize() == 0) {
            std::cout << "User '" << username << "' has no tickets." << std::endl;
            return;
        }

        std::cout << "=== Tickets for User: " << username << " ===" << std::endl;
        std::cout << "Total tickets: " << tickets.getSize() << std::endl;
        std::cout << std::endl;

        for (size_t i = 0; i < tickets.getSize(); i++) {
            const Ticket& ticket = tickets[i];

            std::cout << "Ticket " << (i + 1) << ":" << std::endl;
            std::cout << "  Movie ID: " << ticket.getMovieId() << std::endl;

            // Find movie details
            Movie* movie = nullptr;
            for (size_t j = 0; j < system.getMoviesCount(); j++) {
                if (system.getMovieByIndex(j)->getId() == ticket.getMovieId()) {
                    movie = system.getMovieByIndex(j);
                    break;
                }
            }

            if (movie != nullptr) {
                std::cout << "  Movie Title: " << movie->getTitle() << std::endl;
                std::cout << "  Date: " << movie->getDate() << std::endl;
                std::cout << "  Time: " << movie->getStartTime() << std::endl;
            }

            std::cout << "  Seat: Row " << ticket.getSeat().getRow()
                << ", Column " << ticket.getSeat().getCol() << std::endl;
            std::cout << "  Price: " << ticket.getPrice() << " BGN" << std::endl;
            std::cout << "------------------------" << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cout << "Error retrieving user tickets: " << e.what() << std::endl;
    }
}

void CinemaCommandHandler::list_users(const MyVector<MyString>& inputs) {
    if (!requireAdmin()) {
        return;
    }

    if (system.getUsersCount() == 0) {
        std::cout << "No users registered in the system." << std::endl;
        return;
    }

    std::cout << "=== All Registered Users ===" << std::endl;
    std::cout << "Total users: " << system.getUsersCount() << std::endl;
    std::cout << std::endl;

    for (size_t i = 0; i < system.getUsersCount(); i++) {
        const User& user = system.users[i]; // Direct access to users vector

        std::cout << (i + 1) << ". Username: " << user.getUsername() << std::endl;
        std::cout << "   Admin: " << (user.getIsAdmin() ? "Yes" : "No") << std::endl;
        std::cout << "   Balance: " << user.getBalance() << " BGN" << std::endl;
        std::cout << "   Tickets: " << user.getTickets().getSize() << std::endl;
        std::cout << "   Movies Watched: " << user.getWatchedMovieIds().getSize() << std::endl;
        std::cout << "------------------------" << std::endl;
    }
}

void CinemaCommandHandler::remove_user(const MyVector<MyString>& inputs) {
    if (!requireAdmin()) {
        return;
    }

    if (inputs.getSize() != 2) {
        std::cout << "Usage: remove-user <username>" << std::endl;
        return;
    }

    try {
        MyString username = inputs[1];

        // Check if trying to remove self
        if (system.getCurrentUser() != nullptr &&
            system.getCurrentUser()->getUsername() == username) {
            std::cout << "Error: You cannot remove your own account while logged in." << std::endl;
            return;
        }

        // Find the user
        User* user = system.findUserByUsername(username);
        if (user == nullptr) {
            std::cout << "Error: User '" << username << "' not found." << std::endl;
            return;
        }

        // Check if user has active tickets
        if (user->getTickets().getSize() > 0) {
            std::cout << "Warning: User '" << username << "' has "
                << user->getTickets().getSize() << " active tickets." << std::endl;
            std::cout << "Are you sure you want to remove this user? This action cannot be undone." << std::endl;
            std::cout << "Type 'yes' to confirm or any other key to cancel: ";

            // Simple confirmation - in a real system you might want more sophisticated input handling
            std::string confirmation;
            std::getline(std::cin, confirmation);

            if (confirmation != "yes") {
                std::cout << "User removal cancelled." << std::endl;
                return;
            }
        }

        // Find user index and remove
        bool userRemoved = false;
        for (size_t i = 0; i < system.users.getSize(); i++) {
            if (system.users[i].getUsername() == username) {
                // Create new vector without this user
                MyVector<User> newUsers;
                for (size_t j = 0; j < system.users.getSize(); j++) {
                    if (j != i) {
                        newUsers.push_back(system.users[j]);
                    }
                }
                system.users = newUsers;
                userRemoved = true;
                break;
            }
        }

        if (userRemoved) {
            // Save users to persist changes
            try {
                system.saveUsers();
            }
            catch (const std::exception& e) {
                std::cout << "Warning: User removed but could not save to file: " << e.what() << std::endl;
            }

            std::cout << "User '" << username << "' has been successfully removed from the database." << std::endl;

            if (user->getTickets().getSize() > 0) {
                std::cout << "Note: " << user->getTickets().getSize()
                    << " tickets were also removed. Seats in rooms may need manual cleanup." << std::endl;
            }
        }
        else {
            std::cout << "Error: Failed to remove user from system." << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cout << "Error removing user: " << e.what() << std::endl;
    }
}


void CinemaCommandHandler::checkIfTicketExpired(const MyVector<MyString>& inputs) {
    if (!requireLogin()) {
        return;
    }

    if (inputs.getSize() != 2) {
        std::cout << "Usage: check-if-ticket-expired <ticket_index>" << std::endl;
        std::cout << "Note: ticket_index starts from 1" << std::endl;
        return;
    }

    try {
        // Manual string to unsigned conversion for ticket index
        const char* str = inputs[1].c_str();
        unsigned ticketIndex = 0;
        int i = 0;

        while (str[i] != '\0') {
            if (str[i] >= '0' && str[i] <= '9') {
                ticketIndex = ticketIndex * 10 + (str[i] - '0');
            }
            else {
                throw std::invalid_argument("Invalid number format");
            }
            i++;
        }

        if (ticketIndex == 0) {
            std::cout << "Error: Ticket index must be greater than 0." << std::endl;
            return;
        }

        const MyVector<Ticket>& tickets = system.getCurrentUser()->getTickets();

        if (ticketIndex > tickets.getSize()) {
            std::cout << "Error: Ticket index " << ticketIndex << " is out of range. You have "
                << tickets.getSize() << " ticket(s)." << std::endl;
            return;
        }

        // Convert to 0-based index
        const Ticket& ticket = tickets[ticketIndex - 1];

        // Get the movie ID from the ticket
        unsigned movieId = ticket.getMovieId(); // Assuming ticket has getMovieId() method

        // Find the movie by ID
        Movie* movie = nullptr;
        for (size_t i = 0; i < system.getMoviesCount(); i++) {
            if (system.getMovieByIndex(i)->getId() == movieId) {
                movie = system.getMovieByIndex(i);
                break;
            }
        }

        if (movie == nullptr) {
            std::cout << "Error: Movie with ID " << movieId << " not found." << std::endl;
            return;
        }

        // Get the movie's date
        Date ticketDate = movie->getDate(); // Assuming movie has getDate() method
        Date currentDate = getCurrentDate();

        std::cout << "Ticket " << ticketIndex << " details:" << std::endl;
        ticket.printTicketInfo();

        std::cout << "Movie: " << movie->getTitle() << std::endl;
        std::cout << "Current date: " << currentDate.getDay() << "/"
            << currentDate.getMonth() << "/" << currentDate.getYear() << std::endl;

        std::cout << "Movie date: " << ticketDate.getDay() << "/"
            << ticketDate.getMonth() << "/" << ticketDate.getYear() << std::endl;

        if (isTicketExpired(ticketDate)) {
            std::cout << "Status: EXPIRED - This ticket's event has already passed." << std::endl;
        }
        else {
            std::cout << "Status: VALID - This ticket's event is still upcoming." << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << "Error checking ticket expiration: " << e.what() << std::endl;
    }
}