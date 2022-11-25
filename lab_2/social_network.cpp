///Header include
#include "social_network.hpp"
#include "user.hpp"

///STD include
#include <iostream>

namespace SocialNetworkNS {
size_t SocialNetwork::CUserIndex(const std::string &name,
                                 const std::string &surname) const {
  size_t i;

  User u(name, surname);

  bool found = false;

  for (i = 0; i < users.size() && !found; ++i)
    if (users[i] == u)
      found = true;

  if (found)
    return --i;
  else
    return users.size();
}

void SocialNetwork::AddUser(const std::string &name,
                            const std::string &surname) {
  bool flag = true;
  User u(name, surname);
  
  if (users.size() == 0)
           {
           users.push_back(u);
           friends.push_back(std::vector<size_t>());
           }
  else{
    for(size_t i = 0; i < users.size(); i++)
      {
        if(u == users[i])
        {
          std::cout << "utente già registrato" <<std::endl;
          flag = false;
            
        }
      }
      if(flag){
        users.push_back(u);
        friends.push_back(std::vector<size_t>());
      }
    }
  

}

const std::vector<User> SocialNetwork::CGetUsers() const {
  return users;
}

const std::vector<User> SocialNetwork::CGetFriends(const User &user) const {
  std::vector<User> ret{};
  size_t iter;
  for (size_t i = 0; i < users.size(); i++)
  {
    if (users[i] == user){
      iter = i;
    }
  }
  
      for (size_t j = 0; j < friends[iter].size(); j++)
      {
        ret.push_back(users[friends[iter][j]]);
      }
      
    
  
  return ret;
}


const std::vector<User> SocialNetwork::CGetFriends(const std::string &name,
                                                   const std::string &surname) const {
  std::vector<User> ret{};
  size_t u = CUserIndex(name, surname);
  
  for (size_t i = 0; i < friends.size(); i++)
  {
    if(i == u)
    {
      for (size_t j = 0; j < friends[i].size(); j++)
      {
        ret.push_back(users[friends[i][j]]);
      }
      
    }
  }
  return ret;

}

void SocialNetwork::AddFriendship(const std::string &first_name,
                                  const std::string &first_surname,
                                  const std::string &second_name,
                                  const std::string &second_surname) {
  
  bool flag = true;
  if (CUserIndex(first_name, first_surname) == users.size())
    std::cerr << "the first user is not in the social network" << std::endl;
  else if (CUserIndex(second_name, second_surname) == users.size())
    std::cerr << "the second user is not in the social network" << std::endl;
  else if (first_name == second_name && first_surname == second_surname)
    std::cerr << "a user cannot be friend of himself" << std::endl;
  else{
    size_t i = CUserIndex(first_name, first_surname);
    size_t j = CUserIndex(second_name, second_surname);
    for (size_t k = 0; k < friends[i].size(); k++)
    {
      if (friends[i][k] == j)
      {
        std::cout << "utenti già amici" << std::endl;
        flag = false;
      }
    }
    if(flag)
    { 
      std::cout << "aggiungo amico "  << users[i].ToString() << " all'amico " << users[j].ToString() << std::endl;
      friends[i].push_back(j);
      friends[j].push_back(i);
    }
    }
    
    
  }

}

