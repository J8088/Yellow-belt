
#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string operation_code;
    is >> operation_code;
    if (operation_code == "NEW_BUS") {
        q.type = QueryType::NewBus;
        is >> q.bus;
        int stop_count;
        is >> stop_count;
        q.stops = {};
        for (int i = 0; i < stop_count; ++i)
        {
            string stop;
            is >> stop;
            q.stops.push_back(stop);
        }
    }
    else if (operation_code == "BUSES_FOR_STOP") {
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (operation_code == "STOPS_FOR_BUS") {
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (operation_code == "ALL_BUSES")
        q.type = QueryType::AllBuses;
    return is;
}

struct BusesForStopResponse {
    bool no_stop;
    string answer;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    if (r.no_stop)
        os << "No stop";
    else
        os << r.answer << endl;
    return os;
}

struct StopsForBusResponse {
    bool no_bus;
    string answer;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.no_bus)
        os << "No bus";
    else
        os << r.answer;
    return os;
}

struct AllBusesResponse {
    bool no_buses;
    string answer;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.no_buses)
        os << "No buses";
    else
        os << r.answer;
    return os;
}

class BusManager {
private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for (const string& stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }

    }

    BusesForStopResponse GetBusesForStop(const string& stop) {
        BusesForStopResponse res;
        res.no_stop = (stops_to_buses.count(stop) == 0);
        if (!res.no_stop) {
            for (const string &bus : stops_to_buses[stop])
                res.answer += bus + " ";
        }
        return res;
    }

    StopsForBusResponse GetStopsForBus(const string& bus) {
        StopsForBusResponse res;
        res.no_bus = (buses_to_stops.count(bus) == 0);
        if (!res.no_bus) {
            for (const string &stop : buses_to_stops[bus]) {
                res.answer += "Stop " + stop + ": ";
                if (stops_to_buses[stop].size() == 1) {
                    res.answer += "no interchange";
                } else {
                    for (const string &other_bus : stops_to_buses[stop]) {
                        if (bus != other_bus) {
                            res.answer += other_bus + " ";
                        }
                    }
                }
                res.answer += '\n';
            }
        }
        return res;
    }

    AllBusesResponse GetAllBuses() const {
        AllBusesResponse res;
        res.no_buses = (buses_to_stops.empty());
        if (!res.no_buses) {
            for (const auto& bus_item : buses_to_stops) {
                res.answer += "Bus " + bus_item.first + ": ";
                for (const string& stop : bus_item.second)
                    res.answer += stop + " ";
                res.answer += '\n';
            }
        }
        return  res;
    }

    void TestAddBus()
    {
        vector<string> b32 = {"Tolstopaltsevo", "Marushkino", "Vnukovo"};
        vector<string> b32K = {"Tolstopaltsevo", "Marushkino", "Vnukovo", "Peredelkino"};
        vector<string> b950 = {"Kokoshkino", "Marushkino", "Vnukovo", "Peredelkino", "Solntsevo"};
        vector<string> b272 = {"Vnukovo", "Moskovsky", "Rumyantsevo", "Troparyovo"};
        vector<string> stTol = {"32", "32K"};
        vector<string> stMar = {"32", "32K", "950"};
        vector<string> stMos = {"272"};
        vector<string> stVn = {"32", "32K", "950", "272"};
        AddBus("32", b32);
        AddBus("32K", b32K);
        AddBus("950", b950);
        AddBus("272", b272);
        assert((buses_to_stops["32"] == b32));
        assert((buses_to_stops["32K"] == b32K));
        assert((buses_to_stops["950"] == b950));
        assert((buses_to_stops["272"] == b272));
        assert((stops_to_buses["Tolstopaltsevo"] == stTol));
        assert((stops_to_buses["Marushkino"] == stMar));
        assert((stops_to_buses["Moskovsky"] == stMos));
        assert((stops_to_buses["Vnukovo"] == stVn));
        cout << "AddBus OK" << endl;
    }

    void TestGetBusesForStop()
    {
        vector<string> b32 = {"Tolstopaltsevo", "Marushkino", "Vnukovo"};
        vector<string> b32K = {"Tolstopaltsevo", "Marushkino", "Vnukovo", "Peredelkino"};
        AddBus("32", b32);
        AddBus("32K", b32K);
        BusesForStopResponse res_test;
        {
            res_test = GetBusesForStop("London");
            assert(res_test.no_stop);
        }
        {
            res_test = GetBusesForStop("Tolstopaltsevo");
            assert((res_test.answer == "32 32K \n"));
        }
        {
            res_test = GetBusesForStop("Vnukovo");
            assert((res_test.answer == "32 32K \n"));
        }
        cout << "GetBusesForStop OK" << endl;
    }


};

void TestAll()
{
    {
        BusManager TestBM;
        TestBM.TestAddBus();
    }
    {
        BusManager TestBM;
        TestBM.TestGetBusesForStop();
    }
}

void TestProgram()
{   int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }
}


int main() {

    TestProgram();
    //TestAll();
    return 0;
}


/*
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main() {
    int q;
    cin >> q;

    map<string, vector<string>> buses_to_stops, stops_to_buses;

    for (int i = 0; i < q; ++i) {
        string operation_code;
        cin >> operation_code;

        if (operation_code == "NEW_BUS") {

            string bus;
            cin >> bus;
            int stop_count;
            cin >> stop_count;
            vector<string>& stops = buses_to_stops[bus];
            stops.resize(stop_count);
            for (string& stop : stops) {
                cin >> stop;
                stops_to_buses[stop].push_back(bus);
            }

        } else if (operation_code == "BUSES_FOR_STOP") {

            string stop;
            cin >> stop;
            if (stops_to_buses.count(stop) == 0) {
                cout << "No stop" << endl;
            } else {
                for (const string& bus : stops_to_buses[stop]) {
                    cout << bus << " ";
                }
                cout << endl;
            }

        } else if (operation_code == "STOPS_FOR_BUS") {

            string bus;
            cin >> bus;
            if (buses_to_stops.count(bus) == 0) {
                cout << "No bus" << endl;
            } else {
                for (const string& stop : buses_to_stops[bus]) {
                    cout << "Stop " << stop << ": ";
                    if (stops_to_buses[stop].size() == 1) {
                        cout << "no interchange";
                    } else {
                        for (const string& other_bus : stops_to_buses[stop]) {
                            if (bus != other_bus) {
                                cout << other_bus << " ";
                            }
                        }
                    }
                    cout << endl;
                }
            }

        } else if (operation_code == "ALL_BUSES") {

            if (buses_to_stops.empty()) {
                cout << "No buses" << endl;
            } else {
                for (const auto& bus_item : buses_to_stops) {
                    cout << "Bus " << bus_item.first << ": ";
                    for (const string& stop : bus_item.second) {
                        cout << stop << " ";
                    }
                    cout << endl;
                }
            }

        }
    }
    return 0;
}*/
