#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#pragma once
#include "CinemaSystem.h"
#include "MyVector.hpp"
#include "MyString.h"
#include <iostream>
#include <sstream>


class CinemaCommandHandler
{
private:
    CinemaSystem& system;

    // Helper function to parse command line into tokens
    MyVector<MyString> parseCommand(const MyString& commandLine);

    // Helper function to validate if user is logged in
    bool requireLogin() const;

    // Helper function to validate if user is admin
    bool requireAdmin() const;

    

public:
    explicit CinemaCommandHandler(CinemaSystem& cinemaSystem);

    // Main dispatch function
    void dispatch(const MyString& commandLine);

    // User management commands
    void login(const MyVector<MyString>& inputs);
    void logout(const MyVector<MyString>& inputs);
    void register_user(const MyVector<MyString>& inputs);
    void show_profile(const MyVector<MyString>& inputs);
    void add_balance(const MyVector<MyString>& inputs);

    // Movie management commands (admin only)
    void add_movie(const MyVector<MyString>& inputs);
    void remove_movie(const MyVector<MyString>& inputs);
    void list_movies(const MyVector<MyString>& inputs);
    void show_movie(const MyVector<MyString>& inputs);

    // Room management commands (admin only)
    void open_haul(const MyVector<MyString>& inputs);
    void close_haul(const MyVector<MyString>& inputs);
    void list_rooms(const MyVector<MyString>& inputs);
    void show_room(const MyVector<MyString>& inputs);

    // Booking commands
    void buy_ticket(const MyVector<MyString>& inputs);
    void list_tickets(const MyVector<MyString>& inputs);

    // Rating commands
    void rate_movie(const MyVector<MyString>& inputs);

    // Utility commands
    void help(const MyVector<MyString>& inputs);
    void quit(const MyVector<MyString>& inputs);

    void update_movie_title(const MyVector<MyString>& inputs);
    void update_movie_haul(const MyVector<MyString>& inputs);
    void list_user_history(const MyVector<MyString>& inputs);
    void list_user_tickets_admin(const MyVector<MyString>& inputs);
    void list_users(const MyVector<MyString>& inputs);
    void remove_user(const MyVector<MyString>& inputs);
    void checkIfTicketExpired(const MyVector<MyString>& inputs);
    void removeMovieWithRefunds(unsigned movieId);


    ~CinemaCommandHandler() = default;


    Date getCurrentDate() const {
        time_t now = time(0);
        tm* localTime = localtime(&now);

        return Date(localTime->tm_mday,
            localTime->tm_mon + 1,  // tm_mon is 0-based
            localTime->tm_year + 1900); // tm_year is years since 1900
    }

    bool isTicketExpired(const Date& ticketDate) const {
        Date currentDate = getCurrentDate();
        return ticketDate < currentDate;
    }

    
};




