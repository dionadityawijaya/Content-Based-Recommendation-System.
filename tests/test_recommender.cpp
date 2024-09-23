#include "recommender.h"
#include <iostream>
#include <cassert>

void testRecommender() {
    Recommender recommender;

    recommender.addUserPreference("user1", {{"action", 5.0}, {"drama", 1.0}, {"comedy", 3.0}});
    recommender.addItem({"Movie A", {{"action", 5.0}, {"drama", 2.0}}});
    recommender.addItem({"Movie B", {{"action", 5.0}, {"comedy", 4.0}}});
    recommender.addItem({"Movie C", {{"drama", 5.0}, {"comedy", 1.0}}});

    auto recommendations = recommender.recommendItems("user1", 2);

    assert(recommendations.size() == 2);
    assert(recommendations[0] == "Movie A");
    assert(recommendations[1] == "Movie B");

    std::cout << "All test passed!" << std::endl;

}

int main(int argc, char const *argv[])
{
    testRecommender();
    return 0;
}
