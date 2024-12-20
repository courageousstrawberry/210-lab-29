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
    int date;
    double temperature;
    double sun_distance;
    int time;
public:
    Planet(int d, double t, double s, int ti) {
        date = d;
        temperature = t;
        sun_distance = s;
        time = ti;
    }
    double get_temp(){
        return temperature;
    }
    double get_date(){
        return date;
    }
    double get_sunD() {
        return sun_distance;
    }
    int get_time() {
        return time;
    }
    void set_date(int d) {
        date = d;
    }
    void display_info() {
        cout << "Date: " << date << ", Sun Distance: " << sun_distance << "Time: " << time << endl;
    }
    void increment_time() {
        if (time + 1 < 24) {
            time += 1;
        }
        else {
            time = 0;
        }
    }
    double dust_storm(int d) {
        return temperature - d;
    }
    double volcano(int v) {
        return temperature + v;
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
        
        cout << "Time: ";
        for (const auto& abundance : data[year][2]) {
            cout << abundance << " ";
        }
        cout << endl;
    } else {
        cout << "No data found for year " << year << endl;
    }
    

    // Begin a time-based simulation for environmental changes
    // Randomly pick an index for a year on the map, these will be the starting conditions
    srand(time(0));
    auto it = data.begin();
    advance(it, rand() % data.size());

    Planet current(2024, it->second[0].front(), it->second[1].front(), it->second[2].front());
    current.display_info();

    // For 30 time intervals (each time interval represents 3 earth-years)
    int count = 0;
    int index = 0;
    while (count < 30) {
        // Randomly pick an index from 1-3,
        index = 1 + rand() % 3;
        switch(index){
            // 1 represents a dust storm
            // 2 represents a volccanic erruption
            // 3 represents measuring data
            // Depending on the index, simulate current changes on the planet
            // If it's a dust storm, reduce the temperature
            // If it's a volcanic erruption, increase the temperature
            // If it's measuring data, display and add new data to the map
            // Once changes have been simulated, display the potential effect of these changes on the spacecraft
            // Spacecraft might break down due to inability of withstanding heat
            case 1: {
                // Randomly decide how much the temperature (kelvin) of the current planet will decrease
                int decrease = 2 + rand() % 10;
                current.dust_storm(decrease);
                cout << "Mars Dust Storm! Temperature decreased." << endl;
                break;
            }
            case 2: {
                // Randomly decide if it's a small or large erruption
                int erruption = 1 + rand() % 2;
                if (erruption == 1) {
                    // Small erruption
                    current.volcano(5);
                    cout << "Small volcanic erruption! Temperature increased." << endl;
                }
                else if (erruption == 2) {
                    // Large erruption
                    current.volcano(20);
                    cout << "Large volcanic erruption! Temperature increased." << endl;
                }
                break;
            }
            case 3: {
                cout << "Measure current planet data..." << endl;
                cout << "Current year: " << current.get_date() << endl;
                cout << "Temperature (in Kelvin): " << current.get_temp() << endl;
                cout << "Solar Distance: " << current.get_sunD() << endl; // This value will stay the same to simplify simulation
                cout << "Local Time: " << current.get_time() << endl;

                data[current.get_date()][0].push_back(current.get_temp());
                data[current.get_date()][1].push_back(current.get_sunD());
                data[current.get_date()][2].push_back(current.get_time());
                break;
            }
        }

        // Check for spacecraft stats
        // If planet temp >= 373K, the spacecraft fails and program exits
        if (current.get_temp() >= 373) {
            cout << "Error, spacecraft systems failing. Major damage sustained..." << endl;
            exit(EXIT_FAILURE);
        }

        // Wait or pause briefly to simulate the passage of 3 years between intervals
        count++;
        current.increment_time();
        current.set_date(current.get_date() + 3);
        cout << "Press Enter to continue...";
        cin.get();
    }

    cout << "Simulation ended, taking final measurements!" << endl;
    cout << "Measure current planet data..." << endl;
    cout << "Current year: " << current.get_date() << endl;
    cout << "Temperature (in Kelvin): " << current.get_temp() << endl;
    cout << "Solar Distance: " << current.get_sunD() << endl; // This value will stay the same to simplify simulation
    cout << "Local Time: " << current.get_time() << endl;

    data[current.get_date()][0].push_back(current.get_temp());
    data[current.get_date()][1].push_back(current.get_sunD());
    data[current.get_date()][2].push_back(current.get_time());
    
    // End of main function
    return 0;
}
