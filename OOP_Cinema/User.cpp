#include "User.h"

User::User() : username(""), password(""), isAdmin(false), tickets(0), watchedMovieIds(0), balance(0){}

User::User(const MyString& username, const MyString& password, bool isAdmin, MyVector<Ticket> tickets, MyVector<unsigned> watchedMovieIds, double balance)
{
	setUsername(username);
	setPassword(password);
	setTickets(tickets);
	setWatchedMovieIds(watchedMovieIds);
	setBalance(balance);
	setAdmin(isAdmin);
}

const MyString& User::getUsername() const
{
	return username;
}

const MyString& User::getPassword() const
{
	return password;
}

double User::getBalance() const
{
	return balance;
}

const MyVector<Ticket> User::getTickets() const
{
	return tickets;
}

const MyVector<unsigned> User::getWatchedMovieIds() const
{
	return watchedMovieIds;
}

const bool User::getIsAdmin() const
{
	return isAdmin;
}

void User::setUsername(const MyString& username)
{
	if (username.getSize() < 3)
	{
		throw std::invalid_argument("Username must be at least 3 characters long.");
	}
    this->username = username;
}

void User::setPassword(const MyString& password)
{
	if (password.getSize() < 6)
	{
		throw std::invalid_argument("Password must be at least 6 characters long.");
	}
    this->password = password;
}

void User::setBalance(double balance)
{
	this->balance = balance;
}

void User::setTickets(const MyVector<Ticket>& tickets)
{
	this->tickets = tickets;
}

void User::setWatchedMovieIds(const MyVector<unsigned>& watchedMovieIds)
{
	this->watchedMovieIds = watchedMovieIds;
}

void User::setAdmin(bool isAdmin)
{
	this->isAdmin = isAdmin;
}




void User::printInfo() const
{
    unsigned ticketCount = tickets.getSize();
    unsigned watchedMoviesCount = watchedMovieIds.getSize();

    std::cout << "User info:" << '\n';
    std::cout << "Username: " << username << '\n';
    std::cout << "Password: " << password << '\n';
    std::cout << "Is an admin: " << (isAdmin ? "yes" : "no") << '\n';
    std::cout << "Ticket count: " << tickets.getSize() << '\n';
    std::cout << "Tickets:" << '\n';
    for (unsigned i = 0; i < ticketCount; i++)
    {
        tickets[i].printTicketInfo();
    }
    std::cout << "Watched movie count: " << watchedMovieIds.getSize() << '\n';
    std::cout << "Watched movies:" << '\n';
    for (unsigned i = 0; i < watchedMoviesCount; i++)
    {
        std::cout << watchedMovieIds[i] << '\n';
    }
    std::cout << "Balance: " << balance;

}


void User::writeToTextFile(std::ofstream& out) const {
    writeStringToTextFile(out, username);
    writeStringToTextFile(out, password);
    out << (isAdmin ? 1 : 0) << "\n";
    out << balance << "\n";

    // Write tickets
    out << tickets.getSize() << "\n";
    for (size_t i = 0; i < tickets.getSize(); i++) {
        tickets[i].writeToTextFile(out);
    }

    // Write watched movie IDs
    out << watchedMovieIds.getSize() << "\n";
    for (size_t i = 0; i < watchedMovieIds.getSize(); i++) {
        out << watchedMovieIds[i];
        if (i < watchedMovieIds.getSize() - 1) {
            out << " ";
        }
    }
    out << "\n";
}

void User::readFromTextFile(std::ifstream& in) {
    username = readStringFromTextFile(in);
    password = readStringFromTextFile(in);

    int adminFlag;
    in >> adminFlag;
    isAdmin = (adminFlag == 1);

    in >> balance;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Read tickets
    size_t ticketCount;
    in >> ticketCount;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    tickets.clear();
    for (size_t i = 0; i < ticketCount; i++) {
        Ticket ticket;
        ticket.readFromTextFile(in);
        tickets.push_back(ticket);
    }

    // Read watched movie IDs
    size_t watchedCount;
    in >> watchedCount;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    watchedMovieIds.clear();
    for (size_t i = 0; i < watchedCount; i++) {
        unsigned movieId;
        in >> movieId;
        watchedMovieIds.push_back(movieId);
    }
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
