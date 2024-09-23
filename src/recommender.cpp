#include "recommender.h"
#include <algorithm>
#include <cmath>

Recommender::Recommender() {

}

void Recommender::addUserPreference(const std::string& user, const std::unordered_map<std::string, double>& preferences) {
    userPreferences[user] = preferences;
}

void Recommender::addItem(const Item& item) {
    items.push_back(item);
}

std::vector<std::string> Recommender::recommendItems(const std::string& user, int topN) const {
    std::vector<std::pair<std::string, double>>
    scoredItems;

   if (userPreferences.find(user) == userPreferences.end()) {
    return {};
   }

   auto userPref = userPreferences.at(user);

   for (const auto& item : items) {
    double similarity = computeSimilarity(userPref, item.features);
    scoredItems.emplace_back(item.name, similarity);

   }

   std::sort(scoredItems.begin(), scoredItems.end(), [](const auto& a, const auto& b) {
    return a.second > b.second;
   });

   std::vector<std::string> recommendations;
   for (int i = 0; i < std::min(topN, static_cast<int>
   (scoredItems.size())); ++i) {
    recommendations.push_back(scoredItems[i].first);
   }

   return recommendations;
}


double Recommender::computeSimilarity(const std::unordered_map<std::string, double>& userPref, const std::unordered_map<std::string, double>& itemFeatures) const {
    double dotProduct = 0.0;
    double userMagnitude = 0.0;
    double itemMagnitude = 0.0;

    for (const auto& [feature, userValue] : userPref) {
        if (itemFeatures.find(feature) != itemFeatures.end()) {
            double itemValue = itemFeatures.at(feature);
            dotProduct += userValue * itemValue;
        }
        userMagnitude += userValue * userValue;
    }

    for (const auto& [_, itemValue] : itemFeatures) {
        itemMagnitude += itemValue * itemValue;
    }

    userMagnitude = std::sqrt(userMagnitude);
    itemMagnitude = std::sqrt(itemMagnitude);

    return (userMagnitude == 0 || itemMagnitude == 0) ? 0.0 : dotProduct / (userMagnitude * itemMagnitude);
}

