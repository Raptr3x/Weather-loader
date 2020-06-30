#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using json = nlohmann::json;

cpr::Response call_api(string city, string unitSys) {
    const string api_key = "1b163db11fa9b3b855ad058329c6466b";
    string api_url = "api.openweathermap.org/data/2.5/weather";

    cpr::Response r = cpr::Get(
        cpr::Url{ api_url },
        cpr::Parameters{
            {"q",city},
            {"units",unitSys},
            {"appid", api_key}
        });

    return r;
}

void write_json(string filename, json data) {
    ofstream file;
    file.open(filename);

    if (file.is_open()) {
        file << data;
        file.close();
    }
    cout << "Data is saved under " << filename << endl;
}

int main()
{
    string city;
    string unitSys;

    cout << "Open Weather Map API\n" << "---------------------\n" << endl;

    cout << "City name: ";
    cin >> city;

    cout << "\n[M]etric system or [I]mperial system: ";
    cin >> unitSys;

    cpr::Response r = call_api(city, unitSys);

    if (r.status_code != 200) {
        cout << "API call failed, status code: " << r.status_code << endl;
        return 1;
    }

    json json_response = json::parse(r.text);
    cout << json_response << endl;
    write_json("data.json", json_response);

    return 0;
}