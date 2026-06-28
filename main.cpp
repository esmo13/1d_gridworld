#include <string>
#include <iostream>
#include <vector>
#include <xtensor/containers/xarray.hpp>
#include <xtensor/generators/xbuilder.hpp>
#include <xtensor/io/xio.hpp>
#include <random>
#include <sqlite3.h>

constexpr int NUM_STATES=10;
constexpr int NUM_ACTIONS=2;
constexpr int LEARNING_EPISODES=500;
constexpr double LR=0.1;
constexpr double DISCOUNT_FACTOR=0.9;
constexpr double EXPLORATION_RATE=0.2;

int main() {
    xt::xarray<double> q_table = xt::zeros<double>({NUM_STATES,NUM_ACTIONS});
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> distr(0.0,1.0);

    //TODO: implement training loop

    std::cout<<"Training loop finished, resulting Q-Table: \n" <<q_table<<std::endl;

    sqlite3* db;
    char* errMsg =0;
    int rc = sqlite3_open("q_model.db",&db);

    if (rc){
        std::cerr<<"Unable to open the database, sqlite error: "<<sqlite3_errmsg(db)<<std::endl;
    }

    //TODO: implement saving to database logic
}
