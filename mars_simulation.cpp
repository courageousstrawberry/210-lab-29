// Include necessary headers for file handling, data structures, etc.
// All data is from same position: latitude 4.5, longitude 137.4
// This is near the Gale Crater on Mars, which is where the Curiosity Rover is located
#include <iostream>
#include <map>
#include <list>
#include <array>
#include <fstream>
#include <sstream>
#include <random>
#include <ctime>

using namespace std;
// Define a class to represent Mars as a planet
// Private variables: current temperature, distance from sun, season
class Planet
{
private:
    string date;
    double temperature;
    double sun_distance;
    int time;
public:
    Planet(string d, double t, double s, int ti) {
        date = d;
        temperature = t;
        sun_distance = s;
        time = ti;
    }
};

// Define main function
// Initialize a map to store Mars climate data for each year
// Each key contains an array of lists for surface temperature, sun distance and rock abundance
int main()
{
    map<int, array<list<double>, 3>> data;
    
    fstream file;
    // Open an external file to read initial data about previous climate conditions on Mars
    // If file does not open, print an error and exit
    file.open("mars_data.txt", ios::in);
    // Read data from file and populate map
    // For each line, extract surface temperature, sun distance, and local time data
    if (!file.is_open())
    {
        cerr << "Error opening file." << endl;
        return 1;
    }

    string line;
    while (getline(file, line))
    {
        string date;
        double surfaceTemp, sunDistance;
        int time;
        // Assuming the file has data in the format: date, surfaceTemp, sunDistance, time
        istringstream iss(line);
        char comma; // to consume the commas
        if (getline(iss, date, ',') && 
            iss >> surfaceTemp >> comma >> ws >> sunDistance >> comma >> ws >> time) {

            // Extract the year from the date string (e.g., "2002-03-05" -> 2002)
            int year = stoi(date.substr(0, 4));
            
            // Push data into the corresponding lists for that year
            data[year][0].push_back(surfaceTemp); // Surface temperatures
            data[year][1].push_back(sunDistance);   // Solar distances
            data[year][2].push_back(time); 
        }
        else {
            cerr << "Error reading line: " << line << endl;
        }

    }
    // Close the file
    file.close();

    int year = 2002;
    if (data.find(year) != data.end()) {
        cout << "Data for year " << year << ":\n";
        cout << "Surface Temperatures: ";
        for (const auto& temp : data[year][0]) {
            cout << temp << " ";
        }
        cout << endl;
        
        cout << "Solar Distances: ";
        for (const auto& dist : data[year][1]) {
            cout << dist << " ";
        }
        cout << endl;
        
        cout << "Rock Abundances (Time): ";
        for (const auto& abundance : data[year][2]) {
            cout << abundance << " ";
        }
        cout << endl;
    } else {
        cout << "No data found for year " << year << endl;
    }
    

    // Begin a time-based simulation for environmental changes
    // Randomly pick an index for a year on the map, these will be the starting conditions
    /*
    srand(time(0));
    auto it = data.begin();
    advance(it, rand() % data.size());

    string selected_date = it->first;
    double initial_temperature = it->second[0].front();
    double initial_sun_distance = it->second[1].front();
    int initial_time = it->second[2].front();

    Planet current_conditions(it->first, it->second[0].front(), data[year][1], data[year][2]);
    */
    // For 30 time intervals (each time interval represents 3 earth-years)
    // Randomly pick an index from 1-3,
    // 1 represents a dust storm
    // 2 represents a volccanic erruption
    // 3 represents measuring data
    // Depending on the index, simulate current changes on the planet
    // If it's a dust storm, reduce the temperature and rock abundance value (erosion of rocks)
    // If it's a volcanic erruption, increase the temperature and rock abundance value
    // If it's measuring data, display and add new data to the map
    // Once changes have been simulated, display the potential effect of these changes on the spacecraft
    // Spacecraft breaks down (can't withstand heat), etc.

    // Wait or pause briefly to simulate the passage of 3 years between intervals
    // End of main function
}
