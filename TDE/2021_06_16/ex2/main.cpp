#include<openmpi/mpi.h>
#include<iostream>

bool is_blank(char d){
    return d == ' ';
}

std::string caesar (const std::string& str, unsigned key, bool is_encrypted){
 std::string res = str;
 if(is_encrypted){
    /*A = 38
    Z = 64*/
    for (size_t i = 0; i < str.size(); i++)
    {
        if(!is_blank(str[i]))
            {
                if(str[i]-key < 'A')
                    res[i] = 'Z' - ('A'-str[i]-key);
                else
                    res[i] = str[i] - key;
            }
        else
            res[i] = ' ';
    }
 }
  else{
    /*A = 38
    Z = 64*/
    for (size_t i = 0; i < str.size(); i++)
    {
        if(!is_blank(str[i]))
            {
                if(str[i]+key > 'Z')
                    res[i] = 'A' + (str[i]+key - 'Z');
                else
                    res[i] = str[i] + key;
            }
        else
            res[i] = ' ';
    }
 }
 return res;
}


int main (int argc, char *argv[])
{
MPI_Init(&argc, &argv);
int rank, size;
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
unsigned key = 0;
int A = 'A', Z = 'Z';
if(rank==0){
std::cout << "A = " << A <<std::endl;
std::cout << "Z = " << Z <<std::endl;
std::cout << "insert key: ";
std::cin >> key;}
std::string sentence = "";
bool is_encrypted = true;
if (rank == 0)
{
sentence = "Q EQTT OQDM I KPWKWTIBM JIZ BW IVGWVM EPW LMKZGXBA BPQA";
std::cout << "Your sentence is:" << std::endl;
std::cout << " " << sentence << std::endl;
std::cout << "It should be " << (is_encrypted ? "decrypted." : "encrypted.") << std::endl;
}
std::string sentence_loc= "";
size_t portion =  sentence.length()/size;
MPI_Bcast(&portion, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
MPI_Bcast(&key, 1, MPI_UNSIGNED, 0, MPI_COMM_WORLD);
sentence.resize(portion);
MPI_Scatter(&sentence[0], portion, MPI_CHAR, &sentence_loc[0], portion, MPI_CHAR, 0, MPI_COMM_WORLD);
std::string res_loc = caesar(sentence_loc, key, is_encrypted);
std::string new_sentence;
new_sentence.resize(portion*size);
MPI_Gather(&res_loc[0], portion, MPI_CHAR, &new_sentence[0], portion, MPI_CHAR, 0, MPI_COMM_WORLD);
if (rank == 0)
{
std::cout << std::endl;
std::cout << "The new sentence is:" << std::endl;
std::cout << " " << new_sentence << std::endl;
}
MPI_Finalize();
return 0;
}