#include "InstantMessage.hpp"
int main(){
    InstantMessage pippo("Ciao", 1);
    pippo.send_message(2, "Ciao Carlo");
    pippo.send_message(4, "Come stai?");
    pippo.send_message(5, "Ciao Giulio");
    pippo.send_message(7, "Tutto bene, tu?");
    pippo.send_message(12, "Bene, grazie");
    pippo.send_message(16, "Ho ucciso un uomo");
    pippo.send_message(20, "Con questo dito");
    pippo.send_message(23, "Wow");
    std::multimap<int, std::string> pluto = pippo.search_by_time(5);
    for (auto k:pluto){
        std::cout << "Timestamp: "<< k.first << " Message: " << k.second << std::endl;
    }
    pluto = pippo.search_by_word("Ciao");
    for (auto k:pluto){
        std::cout << "Timestamp: "<< k.first << " Message: " << k.second << std::endl;
    }
    return 0;
    }