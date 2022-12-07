#include <iostream>
#include <algorithm>

#include "search.hh"
#include "timing.hh"

namespace Arcade {
bool binary_search(const std::vector<Arcade::Player> &player_vec, unsigned player_username) {
	timing::time_point start = std::chrono::steady_clock::now();

	std::vector<Arcade::Player>::const_iterator begin = player_vec.begin(), end = player_vec.end(),
	// original musernamepoint
	musername = begin + (end - begin) / 2;
	unsigned n_iter = 1;

	while (begin != end and musername->getUsername() != player_username) {
		/* end is meant to be invalusername, so in both cases
		* we are ignoring musername at the following iteration
		*/
		if (player_username < musername->getUsername())
		end = musername;
		else
		begin = musername + 1;

		musername = begin + (end - begin) / 2;
		++n_iter;
	}

	std::cout << "Number of Iterations " << n_iter << "" << std::endl;

	timing::time_point finish = std::chrono::steady_clock::now();
	timing::elapsed_between(start, finish);

	if (musername != player_vec.end() and player_username == musername->getUsername()) {
		return true;
	} else {
		return false;
	}
}
bool set_search(const std::set<Arcade::Player> &player_set, unsigned player_username){
	timing::time_point start = std::chrono::steady_clock::now();
	bool check = false;
	std::set<Arcade::Player>::const_iterator it_username;
	for ( it_username = player_set.begin(); it_username != player_set.end(); it_username++)
	{
		if (it_username->getUsername() == player_username)
		{
			check = true;
			it_username = player_set.end();
		}
		
	}
	
	timing::time_point finish = std::chrono::steady_clock::now();
	timing::elapsed_between(start, finish);
	return check;
}
}
