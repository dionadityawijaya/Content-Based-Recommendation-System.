#ifndef RECOMMENDER_H
#define RECOMMENDER_H

#include <string>
#include <vector>
#include <unordered_map>


struct Item {
    std::string name;
    std::unordered_map<std::string, double> features;

};

class Recommender {
    public:
        Recommender();
        void addUserPreference(const std::string& user, const std::unordered_map<std::string, double>& preferences);
        void addItem(const Item& item);
        std::vector<std::string> recommendItems(const std::string& user, int topN) const;

    private:
        std::unordered_map<std::string, std::unordered_map<std::string, double>> userPreferences;
        std::vector<Item> items;

        double computeSimilarity(const std::unordered_map<std::string, double>& userPref, const std::unordered_map<std::string, double>& itemFeatures) const;
};


#endif