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

    for (int episode{}; episode<LEARNING_EPISODES; ++episode){
        int state{};
        while (state!=NUM_STATES-1){
            int action{};
            if (distr(gen)<EXPLORATION_RATE){
                action = (distr(gen)>0.5)? 1 : 0;
            }
            else{
                action=(q_table(state,0)>q_table(state,1))? 0 : 1;
            }
            int next_state = state;
            double reward=0.0;

            if (action==0){
                next_state = std::max(0,state-1);
            }
            else{
                next_state=std::min(NUM_STATES -1, state+1);
            }
            if (next_state == NUM_STATES - 1 && state != NUM_STATES -1){
                reward = 10.0;
            }
            else{
                reward = -1.0;
            }

            double max_next_q = std::max(q_table(next_state,0),q_table(next_state,1));
            q_table(state,action) += LR*(reward+DISCOUNT_FACTOR*max_next_q - q_table(state,action));
            state=next_state;

        }
    }

    std::cout<<"Training loop finished, resulting Q-Table: \n" <<q_table<<std::endl;

    sqlite3* db;
    char* errMsg =0;
    int rc = sqlite3_open("q_model.db",&db);

    if (rc){
        std::cerr<<"Unable to open the database, sqlite error: "<<sqlite3_errmsg(db)<<std::endl;
    }
    const char* sql_create = "CREATE TABLE IF NOT EXISTS q_table (state INT, action INT, q_value REAL);";
    rc=sqlite3_exec(db,sql_create,0,0,&errMsg);
    if (rc!= SQLITE_OK){
        std::cerr << "SQL error while trying to create table, sqlite error: "<<errMsg<<std::endl;
    }
    else {
        sqlite3_exec(db, "DELETE FROM q_table;", 0, 0, 0);
        for(int s{}; s<NUM_STATES;++s){
            for(int a{};a<NUM_ACTIONS;++a){
                std::string sql_insert = "INSERT INTO q_table (state, action, q_value) VALUES (" + std::to_string(s) + ", "+std::to_string(a)+", "+std::to_string(q_table(s,a))+ ");";
                sqlite3_exec(db,sql_insert.c_str(),0,0,&errMsg);
           }
           
        }
        std::cout<<"Saved the Q-Table to q_model.db"<<std::endl;
    }
    sqlite3_close(db);
    return 0;

   
}
