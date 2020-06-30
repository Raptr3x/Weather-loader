#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using json = nlohmann::json;

cpr::Response call_api() {
    const string api_key = "1b163db11fa9b3b855ad058329c6466b";
    string api_url = "api.openweathermap.org/data/2.5/weather";

    string location = "Vienna";

    cpr::Response r = cpr::Get(
        cpr::Url{ api_url },
        cpr::Parameters{
            {"q",location},
            {"appid", api_key}
        });

    int sCode = r.status_code;
    if (sCode!=200) {
        cout << "API not available, status code: " << sCode << endl;
    }

    return r;
}

int main()
{
    cpr::Response r = call_api();

    auto json_response = json::parse(r.text);

    cout << json_response << endl;

    return 0;
}