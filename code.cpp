#include <bits/stdc++.h>
using namespace std;

map<string, vector<pair<string, int>>> adj; // Location, it's neighbours and the distance between them

// Function to add a location
void addNode(string name) {
    adj[name];
}

// Function to add a path between two locations
void addEdge(string u, string v, int w) {
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
}

// Dijkstra's Algorithm
void dijkstra(string src, string dest) {

    map<string, int> dist; //Stores the shortest known distance from the source to every location.
    map<string, string> parent; //Stores the previous location in the shortest path.

    // Initially, we assume that every location is infinitely far away.
    for (auto x : adj) {
        dist[x.first] = INT_MAX;
    }

    // min - priority queue <data type, container, comparator>
    priority_queue<
        pair<int, string>,
        vector<pair<int, string>>,
        greater<pair<int, string>>
    > pq; // stores distance from source and location {dist, location}

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {

        int d = pq.top().first;
        string u = pq.top().second;
        pq.pop();

        if (d > dist[u])
            continue;

        for (auto edge : adj[u]) {

            string v = edge.first;
            int w = edge.second;

            if (dist[u] + w < dist[v]) {

                dist[v] = dist[u] + w;
                parent[v] = u;

                pq.push({dist[v], v});
            }
        }
    }

    if (dist[dest] == INT_MAX) {
        cout << "\nNo path exists between these locations.";
        return;
    }

    vector<string> path;

    string current = dest;

    while (current != src) {
        path.push_back(current);
        current = parent[current];
    }

    path.push_back(src);

    reverse(path.begin(), path.end());

    cout << "\nShortest Path:\n";

    for (int i = 0; i < path.size(); i++) {

        cout << path[i];

        if (i != path.size() - 1)
            cout << " -> ";
    }

    cout << "\nTotal Distance: " << dist[dest] << " units\n";
}

string selectLocation(map<int, pair<string, vector<string>>> floors) {

    int floorChoice, locationChoice;

    cout << "\nSelect your floor:\n";

    for (auto x : floors) {
        cout << x.first << ". " << x.second.first << endl;
    }

    cout << "\nEnter floor number: ";
    cin >> floorChoice;

    if (floors.find(floorChoice) == floors.end()) {
        cout << "Invalid floor!";
        return "";
    }

    vector<string> locations = floors[floorChoice].second;

    cout << "\nAvailable locations on "
         << floors[floorChoice].first << ":\n";

    for (int i = 0; i < locations.size(); i++) {
        cout << i + 1 << ". " << locations[i] << endl;
    }

    cout << "\nSelect your location: ";
    cin >> locationChoice;

    if (locationChoice < 1 || locationChoice > locations.size()) {
        cout << "Invalid location!";
        return "";
    }

    return locations[locationChoice - 1];
}

int main(int argc, char* argv[]) 
{
    // 1. INSERT COLLEGE LOCATIONS (NODES)
        // Ground Floor:
    addNode("Entrance");
    addNode("Staircase 0a");
    addNode("Staircase 0b");
    addNode("Staircase 0c");
    addNode("Staircase 0d");
    addNode("Staircase 0e");
    addNode("Saraswati Murti");
    addNode("Annapurna 1");
    addNode("Annapurna 2");
    addNode("LRC");
    addNode("Admin Block");
    addNode("BE Lab 1");
    addNode("Phy Lab 1");
    addNode("CL 1");
    addNode("CL 2");
    addNode("VM 1");
    addNode("Ride Block");
    addNode("Washroom 0a");
    addNode("Washroom 0b");
    addNode("MPH");
    addNode("Main Ground");
    addNode("Football Ground");

        // First Floor:
    addNode("Washroom 1a");
    addNode("Washroom 1b");
    addNode("Staircase 1a");
    addNode("Staircase 1b");
    addNode("Staircase 1c");
    addNode("Staircase 1d");
    addNode("Staircase 1e");
    addNode("Staircase 1f");
    addNode("Staircase 1g");
    addNode("Printout Shop");
    addNode("Gym Room");
    addNode("EDD Lab");
    addNode("Block 1A Entrance 1");
    addNode("Block 1A Entrance 2");
    addNode("Block 1B Entrance 1");
    addNode("Faculty Block 1B");
    addNode("Block 1C");
    //addNode("Anti-Sexual Harassment Cell");
    addNode("Cafe");
    addNode("BE Lab 2");
    addNode("111");
    addNode("113");
    addNode("116");
    addNode("117");
    addNode("Faculty Block 1A");
    addNode("127");
    addNode("118A");
    addNode("118B");
    addNode("121");
    addNode("123");
    addNode("153");
    addNode("148");
    addNode("CR 60");
    addNode("CL 4");
    addNode("VLSI Lab");
    addNode("138");
    addNode("CIC Lab");

        //Second Floor:
    addNode("Washroom 2a");
    addNode("Washroom 2b");
    addNode("Staircase 2a");
    addNode("Staircase 2b");
    addNode("Staircase 2c");
    addNode("Staircase 2d");
    addNode("Staircase 2e");
    addNode("Block 2A Entrance 1");
    addNode("Block 2A Entrance 2");
    addNode("VM 2");
    addNode("Faculty Block 2A");
    addNode("Faculty Block 2B");
    addNode("Faculty Block 2C");
    addNode("Block 2B Entrance 1");
    addNode("Block 2B Entrance 2");
    addNode("Block 2C");
    addNode("Phy Lab 2");
    addNode("217");
    addNode("Mobile Technology Lab");
    addNode("Analogue and Digital Electronics Lab");
    addNode("226");
    addNode("225");
    addNode("Faculty Block 2A1");
    addNode("228");
    addNode("229");
    addNode("230");
    addNode("234");
    addNode("Electromagnetic Lab");
    addNode("Embedded System and IoT Lab");
    addNode("Language Lab 1");
    addNode("241A");
    addNode("241B");
    addNode("Faculty Block 2B1");
    addNode("244A");
    addNode("244B");
    addNode("263");
    addNode("Language Lab 2");
    addNode("259");
    addNode("254");
    addNode("DSP Lab");
    addNode("Communication System Lab");

        //Others
    addNode("Basement Workshop");
    addNode("Third Floor Entrance 1");
    addNode("Third Floor Entrance 2");
    addNode("Third Floor Entrance 3");

    // 2. INSERT CONNECTIONS (EDGES)
    // Format: addEdge(location1, location2, distance);
        // Ground floor:
    addEdge("Entrance", "Saraswati Murti", 3);
    addEdge("Entrance", "Admin Block", 4);
    addEdge("Admin Block", "Staircase 0c" , 1);
    addEdge("Admin Block", "Staircase 0b", 4);
    addEdge("Staircase 0b", "MPH", 3);
    addEdge("MPH", "Washroom 0a", 6);
    addEdge("MPH", "VM 1", 1);
    addEdge("VM 1", "Staircase 0a", 1);
    addEdge("VM 1", "BE Lab 1", 3);
    addEdge("BE Lab 1", "CL 1", 6);
    addEdge("CL 1", "CL 2", 8);
    addEdge("CL 2", "Phy Lab 1", 6);
    addEdge("Phy Lab 1", "Saraswati Murti", 6);
    addEdge("Saraswati Murti", "Annapurna 1", 6);
    addEdge("Annapurna 1", "Annapurna 2", 6);
    addEdge("Entrance", "LRC", 6);
    addEdge("LRC", "Staircase 0d", 2);
    addEdge("Staircase 0d", "Ride Block", 8);
    addEdge("Ride Block", "Staircase 0e", 2);
    addEdge("Annapurna 2", "Washroom 0b", 2);
    addEdge("Washroom 0b", "Staircase 0e", 2);
    addEdge("Saraswati Murti", "Main Ground", 10);
    addEdge("Main Ground", "Football Ground", 2);
    addEdge("BE Lab 1", "Phy Lab 1", 8);

        // Ground floor to other floors:
    addEdge("Staircase 0b", "Basement Workshop", 12);
    addEdge("Staircase 0a", "Staircase 1a", 10);
    addEdge("Staircase 0b", "Staircase 1b", 10);
    addEdge("Staircase 0c", "Staircase 1d", 10);
    addEdge("Staircase 0d", "Staircase 1f", 10);
    addEdge("Staircase 0e", "Staircase 1g", 10);

        // First floor:
    addEdge("Washroom 1a", "Printout Shop", 1);
    addEdge("Printout Shop", "Gym Room", 2);
    addEdge("Printout Shop", "Staircase 1a", 1);
    addEdge("Gym Room", "Staircase 1a", 1);
    addEdge("Staircase 1a", "Block 1A Entrance 1", 1);
    addEdge("Block 1A Entrance 1", "Staircase 1c", 8);
    addEdge("Staircase 1c", "Staircase 1b", 2);
    addEdge("Staircase 1d", "Staircase 1b", 2);
    addEdge("Staircase 1c", "Staircase 1d", 3);
    addEdge("Staircase 1d", "EDD Lab", 1);
    addEdge("Block 1A Entrance 2", "Staircase 1d", 3);
    addEdge("Block 1A Entrance 2", "Cafe", 8);
    addEdge("Cafe", "Faculty Block 1B", 2);
    addEdge("Faculty Block 1B", "Staircase 1f", 2);
    addEdge("Staircase 1e", "Staircase 1f", 2);
    addEdge("Faculty Block 1B", "Staircase 1e", 2);
    addEdge("Staircase 1e", "Block 1B Entrance 1", 7);
    addEdge("Block 1B Entrance 1", "VLSI Lab", 1);
    addEdge("VLSI Lab", "CIC Lab", 1);
    addEdge("CIC Lab", "138", 1);
    addEdge("138", "BE Lab 2", 1);
    addEdge("Block 1B Entrance 1", "Block 1C", 3);
    addEdge("Block 1C", "153", 1);
    addEdge("Block 1C", "148", 1);
    addEdge("148", "CL 4", 1);
    addEdge("CL 4", "CR 60", 1);
    addEdge("CR 60", "153", 1);
    addEdge("Block 1C", "Washroom 1b", 3);
    addEdge("Washroom 1b", "Staircase 1g", 1);
    addEdge("Block 1A Entrance 1", "111", 1);
    addEdge("111", "113", 1);
    addEdge("113", "116", 1);
    addEdge("116", "127", 1);
    addEdge("116", "117", 1);
    addEdge("117", "Faculty Block 1A", 1);
    addEdge("Faculty Block 1A", "118A", 1);
    addEdge("118A", "118B", 1);
    addEdge("118B", "121", 1);
    addEdge("121", "123", 1);
    addEdge("123", "Block 1A Entrance 2", 1);

        // First floor to other floors:
    addEdge("Staircase 1a", "Staircase 2a", 10);
    addEdge("Staircase 1c", "Staircase 2b", 10);
    addEdge("Staircase 1e", "Staircase 2d", 10);
    addEdge("Staircase 1g", "Staircase 2e", 10);
    
        // Second floor:
    addEdge("Washroom 2a", "Staircase 2a", 3);
    addEdge("Staircase 2a", "Block 2A Entrance 1", 1);
    addEdge("Block 2A Entrance 1", "Block 2A Entrance 2", 10);
    addEdge("Block 2A Entrance 2", "Staircase 2c", 1);
    addEdge("Staircase 2c", "Staircase 2b", 1);
    addEdge("Staircase 2b", "Faculty Block 2A", 2);
    addEdge("Faculty Block 2A", "VM 2", 1);
    addEdge("Staircase 2b", "Staircase 2d", 8);
    addEdge("Staircase 2d", "Faculty Block 2B", 2);
    addEdge("Staircase 2d", "Block 2B Entrance 1", 1);
    addEdge("Block 2B Entrance 2", "Faculty Block 2C", 1);
    addEdge("Faculty Block 2C", "Block 2C", 3);
    addEdge("Block 2C", "259", 1);
    addEdge("Block 2C", "254", 1);
    addEdge("259", "Phy Lab 2", 1);
    addEdge("Phy Lab 2", "Communication System Lab", 1);
    addEdge("Communication System Lab", "DSP Lab", 1);
    addEdge("DSP Lab", "254", 1);
    addEdge("Block 2C", "Washroom 2b", 3);
    addEdge("Washroom 2b", "Staircase 2e", 1);
    addEdge("Block 2A Entrance 1", "217", 1);
    addEdge("217", "Mobile Technology Lab", 1);
    addEdge("Mobile technology Lab", "Analogue and Digital Electronics Lab", 1);
    addEdge("Analogue and Digital Electronics Lab", "226", 1);
    addEdge("Analogue and Digital Electronics Lab", "225", 1);
    addEdge("225", "226", 1);
    addEdge("226", "Faculty Block 2A1", 1);
    addEdge("Faculty Block 2A1", "228", 1);
    addEdge("228", "229", 1);
    addEdge("225", "229", 1);
    addEdge("228", "230", 1);
    addEdge("230", "234", 1);
    addEdge("234", "Electromagnetic Lab", 1);
    addEdge("Electromagnetic Lab", "Block 2A Entrance 2", 1);
    addEdge("Block 2B Entrance 1", "Embedded System and IoT Lab", 1);
    addEdge("Embedded System and IoT Lab", "Language Lab 2", 1);
    addEdge("Language Lab 2", "241A", 1);
    addEdge("241A", "241B", 1);
    addEdge("241B", "Faculty Block 2B1", 1);
    addEdge("Faculty Block 2B1", "244A", 1);
    addEdge("244A", "244B", 1);
    addEdge("244B", "Language Lab 2", 1);
    addEdge("Language Lab 2", "Faculty Block 2C", 1);

        // Second floor to other floors:
    addEdge("Staircase 2a", "Third Floor Entrance 1", 10);
    addEdge("Staircase 2c", "Third Floor Entrance 2", 10);
    addEdge("Staircase 2e", "Third Floor Entrance 3", 10);

        // Others
    addEdge("Third Floor Entrance 1", "Third Floor Entrance 2", 10);
    addEdge("Third Floor Entrance 2", "Third Floor Entrance 3", 18);

    if (argc < 3) {
        return 1;
    }

    string src = argv[1];
    string dest = argv[2];

    // 4. Run Dijkstra
    dijkstra(src, dest);

    return 0;
}