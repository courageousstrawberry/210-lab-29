// Include necessary headers for file handling, data structures, etc.
// All data is from same position: latitude 4.5, longitude 137.4
// This is near the Gale Crater on Mars, which is where the Curiosity Rover is located
#include <iostream>
#include <map>
#include <list>
#include <array>
#include <fstream>
#include <sstream>

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
    map<string, array<list<double>, 3>> data;
    
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
        // Assuming the file has data in the format: date, surfaceTemp, sunDistance, rockAbundance
        istringstream iss(line);
        char comma; // to consume the commas
        if (!(iss >> date >> comma >> surfaceTemp >> comma >> sunDistance >> comma >> time))
        {
            cerr << "Error reading line: " << line << endl;
            continue;
        }
        else {
            data[date][0].push_back(surfaceTemp);
            data[date][1].push_back(sunDistance);
            data[date][2].push_back(time);
        }
    }
    // Close the file

    file.close();

    // Begin a time-based simulation for environmental changes
    // Randomly pick an index for a year on the map, these will be the starting conditions
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
