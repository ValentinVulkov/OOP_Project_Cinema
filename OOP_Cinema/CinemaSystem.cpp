#include "CinemaSystem.h"

bool CinemaSystem::userExists(const User* user) const
{
	for (size_t i = 0; i < users.getSize(); i++)
	{
		if (user->getUsername() == users[i].getUsername())
		{
			return true;
		}
	}
	return false;
}

User* CinemaSystem::findUserByUsername(const MyString& username) {
    for (size_t i = 0; i < users.getSize(); i++) {
        if (users[i].getUsername() == username) {
            return &users[i];
        }
    }
    return nullptr;
}

const User* CinemaSystem::findUserByUsername(const MyString& username) const {
    for (size_t i = 0; i < users.getSize(); i++) {
        if (users[i].getUsername() == username) {
            return &users[i];
        }
    }
    return nullptr;
}

void CinemaSystem::saveUsers() const
{
    std::ofstream out("Users.txt");
    if (!out.is_open()) {
        throw std::runtime_error("Could not open users file for writing");
    }

    // Write number of users
    size_t userCount = users.getSize();
    out.write(reinterpret_cast<const char*>(&userCount), sizeof(userCount));

    // Write each user
    for (size_t i = 0; i < userCount; i++) {
        users[i].writeToFile(out);
    }

    out.close();
}

void CinemaSystem::saveRooms() const {
    std::ofstream out("Rooms.txt");
    if (!out.is_open()) {
        throw std::runtime_error("Could not open rooms file for writing");
    }

    // Write total number of rooms
    out << rooms.getSize() << '\n';

	unsigned roomCount = rooms.getSize();
    // Write each room's data
    for (unsigned i = 0; i < roomCount;i++) {
        rooms[i].writeToTextFile(out);
    }

    out.close();
}

void CinemaSystem::saveMovies() const
{
    std::ofstream out("Movies.txt");
    if (!out.is_open()) {
        throw std::runtime_error("Could not open movies file for writing");
    }

    // Write number of movies
    out << movies.getSize() << '\n';

    for (size_t i = 0; i < movies.getSize(); i++) {
        // Write movie type first
        out << static_cast<int>(movies[i]->getGenre()) << '\n';
        // Then write movie data
        movies[i]->writeToTextFile(out);
    }

    out.close();
}

void CinemaSystem::loadUsers()
{
    std::ifstream in("Users.dat", std::ios::binary);
    if (!in.is_open()) {
        users.clear(); // Initialize empty user list
        return; // No file exists yet (not an error)
    }

    // Check if file is empty
    in.seekg(0, std::ios::end);
    if (in.tellg() == 0) {
        users.clear();
        in.close();
        return;
    }
    in.seekg(0, std::ios::beg);
    users.clear();

    // Read number of users
    size_t userCount;
    in.read(reinterpret_cast<char*>(&userCount), sizeof(userCount));

    for (size_t i = 0; i < userCount; i++) {
        User user;
        user.readFromFile(in);
        users.push_back(user);
    }

    in.close();
}

void CinemaSystem::loadRooms()
{
    std::ifstream in("Rooms.txt");
    if (!in.is_open()) {
        throw std::runtime_error("Could not open rooms file for reading");
    }

    rooms.clear();
    size_t roomCount;
    in >> roomCount;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (size_t i = 0; i < roomCount; i++) {
        Room room;
        room.readFromTextFile(in);
        rooms.push_back(room);
    }
    in.close();
}

void CinemaSystem::loadMovies()
{
    std::ifstream in("Movies.txt");
    if (!in.is_open()) {
        // File doesn't exist yet - not an error
        movies.clear();
        return;
    }

    // Clear existing movies
    for (size_t i = 0; i < movies.getSize(); i++) {
        delete movies[i];
    }
    movies.clear();

    // Read number of movies
    size_t movieCount;
    in >> movieCount;
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (size_t i = 0; i < movieCount; i++) {
        // Read genre first
        int genreInt;
        in >> genreInt;
        in.ignore(); // Skip newline
        Genre genre = static_cast<Genre>(genreInt);

        Movie* movie = nullptr;
        switch (genre) {
        case Genre::ActionMovie:
            movie = new ActionMovie();
            break;
        case Genre::DramaMovie:
            movie = new DramaMovie();
            break;
        case Genre::DocumentaryMovie:
            movie = new DocumentaryMovie();
            break;
        default:
            throw std::runtime_error("Unknown movie genre in file");
        }
        std::cout << genreInt;
        try {
            movie->readFromTextFile(in);
            movies.push_back(movie);
        }
        catch (...) {
            delete movie;
            throw; // Re-throw the exception after cleanup
        }
    }

    in.close();
}


void CinemaSystem::Login()
{
    std::cout << "Enter username: ";
    MyString username;
    std::cin >> username;
    std::cout << "Enter password: ";
    MyString password;
    std::cin >> password;

    CinemaSystem& system = CinemaSystem::getInstance();
    User* user = system.findUserByUsername(username);

    if (user == nullptr)
    {
        throw std::invalid_argument("User not found.");
    }

    if (user->getPassword() != password)
    {
        throw std::invalid_argument("Incorrect password.");
    }

    system.setCurrentUser(user);
    std::cout << "Login successful. Welcome, " << user->getUsername() << "!" << std::endl;
}


void CinemaSystem::setCurrentUser(User* user)
{
	if (user == nullptr) {
		currentUser = nullptr;
		return;
	}

	if (!userExists(user)) {
		throw std::runtime_error("User does not exist in the system");
	}

	currentUser = user;
}

User* CinemaSystem::getCurrentUser() const
{
	if (currentUser == nullptr) {
		return nullptr;
	}
	return currentUser;
}




CinemaSystem::CinemaSystem()
{
	//loadUsers();
	//loadRooms();
	//loadMovies();
	//currentUser = nullptr; // Initialize current user to nullptr
}

CinemaSystem::~CinemaSystem()
{
    saveUsers();
	saveRooms();
	saveMovies();

	// Clean up dynamically allocated movies
	for (size_t i = 0; i < movies.getSize(); i++) {
		delete movies[i];
	}
	movies.clear();
}

CinemaSystem& CinemaSystem::getInstance()
{
    static CinemaSystem instance;
    return instance;
}

size_t CinemaSystem::getMoviesCount() const {
    return movies.getSize();
}

Movie* CinemaSystem::getMovieByIndex(size_t index) {
    if (index >= movies.getSize()) return nullptr;
    return movies[index];
}

size_t CinemaSystem::getRoomsCount() const {
    return rooms.getSize();
}

const Room& CinemaSystem::getRoomByIndex(size_t index) const {
    if (index >= rooms.getSize()) {
        throw std::out_of_range("Room index out of range");
    }
    return rooms[index];
}

size_t CinemaSystem::getUsersCount() const {
    return users.getSize();
}

