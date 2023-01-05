#include <string>
#include <vector>
#include<openmpi/mpi.h>

class Author
{
private:
    std::string name;
    std::string nation;
public:
    Author(std::string n, std::string nat):name(n), nation(nat){};
    std::string get_name(void){return name;}
    std::string get_nation(void)const{return nation;}
};
using authors = std::vector<Author>;
size_t author_nation_count(const std::string & nation, const authors & auts){
    int rank, size;
    unsigned count = 0, total_count = 0;
    unsigned letters = nation.length();
    std::string message;
    MPI_Bcast(&letters, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
    message.resize(letters);
    MPI_Bcast(&message[0], letters, MPI_CHAR, 0, MPI_COMM_WORLD);
    for (size_t i = 0; i < auts.size()/size; i++)
    {
        if (auts.at(i+rank*(auts.size()/size)).get_nation() == message)
        {
            count++;
        }
    }
    MPI_Reduce(&count, &total_count, size, MPI_UNSIGNED, MPI_SUM, 0, MPI_COMM_WORLD);
    return total_count;
}