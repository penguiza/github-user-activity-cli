#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <map>
#include <vector>
#include <algorithm>

using json = nlohmann::json;

//std::string token = "YOUR TOKEN HERE";

void displayPushEvents(json j)
{
    std::map<std::string, int> pushCount;
    for (const auto& events : j) {
        if (events["type"] == "PushEvent") {
            std::string repoName = events["repo"]["name"];
            pushCount[repoName]++;
            
        }
    }
    if (pushCount.empty()) {
        std::cout << "No Push Events Found" << std::endl;
    }
    else
    {
        for (const auto& entry : pushCount) {
            std::cout << "Pushed to: " << "github.com/" << entry.first << " (" << entry.second << " times)" << std::endl;

        }
    }

}

void displayCommits(json j)
{
    std::map<std::string, int> pushEvents;
    for (const auto& events : j) {
        if (events["type"] == "PushEvent") {
            int commitCount = events["payload"]["commits"].size();
            std::string repoName = events["repo"]["name"];
            pushEvents[repoName] += commitCount;
        }
    }
    if (pushEvents.empty())
    {
        std::cout << "No Commits Found" << std::endl;
    }
    for (const auto& event : pushEvents) {
        std::cout << "Pushed " << event.second << " commits to " << "github.com/" << event.first << std::endl;
    }
}

void displayStarred(json j)
{
    bool found = false;

    for (const auto& starred : j) {
        std::cout << "Starred: " << "github.com/" << starred["full_name"] << std::endl;
        found = true;
    }
    if (!found) {
        std::cout << "No Starred Repos Found!" << std::endl;
    }
}
void displayMenu(json j, json h);

void changeUser()
{
    std::string user;
    std::cout << "Which user's activity would you like to view?: ";
    std::cin.ignore();
    std::getline(std::cin, user);
    user.erase(std::remove(user.begin(), user.end(), ' '), user.end());

    cpr::Response newEvents = cpr::Get(cpr::Url{ "https://api.github.com/users/" + user + "/events" });//, cpr::Header{ {"Authorization", "token " + token} });
    cpr::Response newStarred = cpr::Get(cpr::Url{ "https://api.github.com/users/" + user + "/starred"});//, cpr::Header{ {"Authorization", "token " + token} });

    json newJ = json::parse(newEvents.text);
    json newH = json::parse(newStarred.text);

    if (newEvents.status_code != 200 || newStarred.status_code != 200) {
        std::cout << "Invalid user try again!" << std::endl;
    }
    else {
        displayMenu(newJ, newH);

    }
   
}

void displayMenu(json j, json h) {
    int choices = 0;
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Display Commits\n";
        std::cout << "2. Display Push Events\n";
        std::cout << "3. Display Starred Repos\n";
        std::cout << "4. Change User To View\n";
        std::cout << "0. Exit\n";
        std::cout << "Please enter your choice: ";
        std::cin >> choices;

        switch (choices)
        {
        case 1:
            displayCommits(j);
            break;
        case 2:
            displayPushEvents(j);
            break;
        case 3:
            displayStarred(h);
            break;
        case 4:
            
            changeUser();
            return;
        
        default:
            break;
        }
      
    } while (choices != 0);
}



int main()
{
    while (true)
    {
        std::string user;
        std::cout << "Which user's activity would you like to view?: ";
        std::getline(std::cin, user);
        user.erase(std::remove(user.begin(), user.end(), ' '), user.end());
        cpr::Response r = cpr::Get(cpr::Url{ "https://api.github.com/users/" + user + "/events" });//, cpr::Header{{"Authorization", "token " + token}});
        cpr::Response g = cpr::Get(cpr::Url{ "https://api.github.com/users/" + user + "/starred" });//, cpr::Header{ {"Authorization", "token " + token} });
        json j = json::parse(r.text);
        json h = json::parse(g.text);
        if (r.status_code != 200 || g.status_code != 200) {
            std::cout << "Invalid user try again!" << std::endl;
        }
        else {
            displayMenu(j, h);

        }
    }
}