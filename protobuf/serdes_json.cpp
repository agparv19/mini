#include <nlohmann/json.hpp>
#include <fstream>

struct ValueEntry{
    std::string value;
    long int expiry;
};

void to_json(nlohmann::json& j, const ValueEntry& v) {
    j = nlohmann::json{{"val", v.value}, {"expiry", v.expiry}};
}

void from_json(const nlohmann::json& j, ValueEntry& v) {
    j.at("val").get_to(v.value);
    j.at("expiry").get_to(v.expiry);
}

int main() {

    std::unordered_map<std::string, ValueEntry> store;
    store["name"] = {"Ram", 1000};
    store["surname"] = {"Kishan", 1000};
    store["job"] = {"SDE", 1};

    nlohmann::json json;
    for (const auto& pair : store) {
        json[pair.first] = pair.second;
    }
    std::ofstream outputFile("store_json_dump");
    outputFile << json.dump() << std::endl;
}