#include "User.h"

User::User() : username(""), password(""), isAdmin(false), tickets(0), watchedMovieIds(0), balance(0){}

User::User(const MyString& username, const MyString& password, bool isAdmin, MyVector<Ticket> tickets, MyVector<unsigned> watchedMovieIds, unsigned balance)
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

unsigned User::getBalance() const
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
}

void User::setPassword(const MyString& password)
{
	if (password.getSize() < 6)
	{
		throw std::invalid_argument("Password must be at least 6 characters long.");
	}
}

void User::setBalance(unsigned balance)
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


void User::writeToFile(std::ofstream& out) const {
    if (!out.is_open()) {
        throw std::runtime_error("Output file stream is not open");
    }

    // Write username and password
    writeStringToFile(out, username);
    writeStringToFile(out, password);

    // Write admin status and balance
    out.write(reinterpret_cast<const char*>(&isAdmin), sizeof(isAdmin));
    out.write(reinterpret_cast<const char*>(&balance), sizeof(balance));

    // Write tickets
    size_t ticketCount = tickets.getSize();
    out.write(reinterpret_cast<const char*>(&ticketCount), sizeof(ticketCount));
    for (size_t i = 0; i < ticketCount; i++) {
        tickets[i].writeToFile(out);
    }

    // Write watched movies
    size_t movieCount = watchedMovieIds.getSize();
    out.write(reinterpret_cast<const char*>(&movieCount), sizeof(movieCount));
    for (size_t i = 0; i < movieCount; i++) {
        out.write(reinterpret_cast<const char*>(&watchedMovieIds[i]), sizeof(unsigned));
    }
}

void User::readFromFile(std::ifstream& in) {
    if (!in.is_open()) {
        throw std::runtime_error("Input file stream is not open");
    }

    // Read username and password
    username = readStringFromFile(in);
    password = readStringFromFile(in);

    // Read admin status and balance
    in.read(reinterpret_cast<char*>(&isAdmin), sizeof(isAdmin));
    in.read(reinterpret_cast<char*>(&balance), sizeof(balance));

    // Read tickets
    size_t ticketCount;
    in.read(reinterpret_cast<char*>(&ticketCount), sizeof(ticketCount));
    tickets.clear();
    for (size_t i = 0; i < ticketCount; i++) {
        Ticket ticket;
        ticket.readFromFile(in);
        tickets.push_back(ticket);
    }

    // Read watched movies
    size_t movieCount;
    in.read(reinterpret_cast<char*>(&movieCount), sizeof(movieCount));
    watchedMovieIds.clear();

    for (size_t i = 0; i < movieCount; i++) {
        unsigned movieId;
        in.read(reinterpret_cast<char*>(&movieId), sizeof(movieId));
        watchedMovieIds.push_back(movieId);
    }
}