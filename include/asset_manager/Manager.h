#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>
#include "profiling/LoggerManager.h"

namespace AssetManager {

template<typename T, typename IDTYPE = uint32_t>
class Manager {
private:
    IDTYPE nextID = 1;
    std::unordered_map<IDTYPE, std::unique_ptr<T>> map;
    std::unordered_map<std::string, IDTYPE> name_to_id;
    std::unordered_map<IDTYPE, std::string> id_to_name;
    std::vector<IDTYPE> removeMemory;
    bool allDestroyed = false;

public:

    // ---------------- CREATE ----------------
    template<typename Factory>
    T* create(const std::string& name, Factory&& factory) {
        if (name_to_id.find(name) != name_to_id.end()) {
            LOG_WARNING("Asset already exists with name: " + name);
            return map[name_to_id[name]].get();
        }

        IDTYPE id = nextID++;
        map[id] = std::forward<Factory>(factory)(); // Factory liefert unique_ptr<T>
        name_to_id[name] = id;
        id_to_name[id] = name;

        LOG_SUCCESS("Asset created: " + name);
        return map[id].get();
    }

    // Optional: Mock-Funktion
    template<typename Factory>
    T* createMock(const std::string& name, Factory&& factory) {
        return create(name, std::forward<Factory>(factory));
    }

    // ---------------- GET ----------------
    T* get(IDTYPE id) {
        auto it = map.find(id);
        if(it != map.end()) return it->second.get();
        LOG_WARNING("Asset not found for ID");
        return nullptr;
    }

    const T* get(IDTYPE id) const {
        auto it = map.find(id);
        if(it != map.end()) return it->second.get();
        return nullptr;
    }

    T* get(const std::string& name) {
        auto it = name_to_id.find(name);
        if(it != name_to_id.end()) return get(it->second);
        LOG_WARNING("Asset not found for name: " + name);
        return nullptr;
    }

    const T* get(const std::string& name) const {
        auto it = name_to_id.find(name);
        if(it != name_to_id.end()) return get(it->second);
        return nullptr;
    }

    // ---------------- DESTROY ----------------
    void destroy(IDTYPE id) {
        removeMemory.push_back(id);
    }

    void destroy(const std::string& name) {
        auto it = name_to_id.find(name);
        if(it != name_to_id.end()) {
            removeMemory.push_back(it->second);
        }
    }

    void destroyAll() {
        allDestroyed = true;
    }

    // ---------------- CLEANUP ----------------
    void cleanUp() {
        if(allDestroyed) {
            map.clear();
            name_to_id.clear();
            id_to_name.clear();
            removeMemory.clear();
            allDestroyed = false;
            LOG_WARNING("All assets destroyed!");
            return;
        }

        for(auto id : removeMemory) {
            map.erase(id);
            auto it = id_to_name.find(id);
            if(it != id_to_name.end()) {
                name_to_id.erase(it->second);
                id_to_name.erase(it);
            }
        }

        LOG_INFO("Marked assets destroyed!");
        removeMemory.clear();
    }
};

} // namespace AssetManager