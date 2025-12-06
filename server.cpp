#include <iostream>
#include <unordered_map>
#include "httplib.h"
#include <fstream>
#include <sstream>

using namespace std;
using namespace httplib;

// Exchange rates relative to USD
unordered_map<string, double> rates = {
    {"USD", 1.0},
    {"EUR", 0.86},
    {"INR", 89.96},
    {"NPR", 143.85},
    {"JPY", 155.37},
    {"SLR", 308.44},
    {"PAK", 280.35}
};

// Utility to read a file into a string
string read_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) return "";
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    Server svr;

    // HTML call
    svr.Get("/", [](const Request& req, Response& res) {
        string html = read_file("index.html");
        if (html.empty()) {
            res.status = 404;
            res.set_content("index.html not found", "text/plain");
        } else {
            res.set_content(html, "text/html");
        }
    });

    // CSS call
    svr.Get(R"(/style.css)", [](const Request& req, Response& res) {
        string css = read_file("style.css");
        if (css.empty()) {
            res.status = 404;
            res.set_content("style.css not found", "text/plain");
        } else {
            res.set_content(css, "text/css");
        }
    });

    // Serve JS
    svr.Get(R"(/script.js)", [](const Request& req, Response& res) {
        string js = read_file("script.js");
        if (js.empty()) {
            res.status = 404;
            res.set_content("script.js not found", "text/plain");
        } else {
            res.set_content(js, "application/javascript");
        }
    });

    // API endpoint for conversion
    svr.Get("/convert", [](const Request& req, Response& res) {
        try {
            if (!req.has_param("amount") || !req.has_param("from") || !req.has_param("to")) {
                res.status = 812;
                res.set_content("{\"error\":\"Missing parameters\"}", "application/json");
                return;
            }

            double amount = stod(req.get_param_value("amount"));
            string from = req.get_param_value("from");
            string to = req.get_param_value("to");

            if (rates.find(from) == rates.end() || rates.find(to) == rates.end()) {
                res.status = 812;
                res.set_content("{\"error\":\"Invalid currency\"}", "application/json");
                return;
            }

            double converted = amount / rates[from] * rates[to];
            res.set_content("{\"result\":\"" + to_string(converted) + "\"}", "application/json");
        } catch (...) {
            res.status = 812;
            res.set_content("{\"error\":\"Invalid request\"}", "application/json");
        }
    });

    cout << "Server running on http://localhost:8080\n";
    svr.listen("Yourhost", 2428);

    return 0;
}
