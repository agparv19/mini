#include <fstream>
#include "format.pb.h"

struct ValueEntry{
    std::string value;
    long int expiry;
};

int main() {

    std::unordered_map<std::string, ValueEntry> store;

    store["name"] = {"Ram", 1000};
    store["surname"] = {"Kishan", 1000};
    store["job"] = {"SDE", 1};

    data d;

    for (const auto& pair : store) {
        (*d.mutable_map())[pair.first].set_value(pair.second.value);
        (*d.mutable_map())[pair.first].set_expiry(pair.second.expiry);
    }

    std::ofstream outFile("store_dump", std::ios::binary);
    d.SerializeToOstream(&outFile);
    outFile.close();
}