#include <iostream>

#include "Player.hh"

namespace Arcade {
Player::Player(unsigned username, const std::vector<unsigned> &scores)
	: username(username), scores(scores) {}

Player::Player(unsigned username) : username(username), scores() {}

const std::vector<unsigned> &Player::getScores() const {
return scores;
}

unsigned Player::getUsername() const {
return username;
}

void Player::setScores(const std::vector<unsigned> &new_scores) {
scores = new_scores;
}

void Player::setUsername(unsigned new_username) {
username = new_username;
}

void Player::print() const {
std::cout << username << ":" << std::endl;

for (unsigned score: scores)
	std::cout << score << " ";

std::cout << std::endl;
}
bool Player::operator<(Player rhs) const{
	if (username < rhs.getUsername())
		return true;
	else
		return false;

}
}
