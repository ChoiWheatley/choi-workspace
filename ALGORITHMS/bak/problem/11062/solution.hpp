#include <deque>
#include <utility>
using std::deque;
using std::pair;

using Card = int;
using Score = int;
using Result = pair<Score, Score>;
using Turn = bool;

enum class TakeCard { Left, Right };

/**
@brief: from list of card is placed like {l1, l2, ... , r2, r1}, player can only
select one side of the list: Left and Right
*/
inline TakeCard strategy(Card l1, Card l2, Card r2, Card r1) {
  if (l2 < r2) {
    Card best_inner = r2;
    if (best_inner <= r1) {
      return TakeCard::Right;
    }
    return TakeCard::Left;
  }
  Card best_inner = l2;
  if (best_inner <= l1) {
    return TakeCard::Left;
  }
  return TakeCard::Right;
}

/**
@brief: Player "G" always take the card first, and then player "M"
interchangely. Given that two players play to get best score, find out the score
of player "G" and "M"
*/
inline Result solution(deque<Card> &&cards) {
  Score g = 0;
  Score m = 0;
  Turn turn = true; // true: G, false: M
  while (cards.size() >= 4) {
    Card popped = 0;
    if (strategy(cards.front(), *(cards.begin() + 1), *(cards.rbegin() + 1),
                 cards.back()) == TakeCard::Left) {
      popped = cards.front();
      cards.pop_front();
    } else {
      popped = cards.back();
      cards.pop_back();
    }
    if (turn) {
      g += popped;
    } else {
      m += popped;
    }
    turn = !turn;
  }
  // greedly take left of cards
  while (!cards.empty()) {
    Card popped = 0;
    if (cards.front() < cards.back()) {
      popped = cards.back();
      cards.pop_back();
    } else {
      popped = cards.front();
      cards.pop_front();
    }
    if (turn) {
      g += popped;
    } else {
      m += popped;
    }
    turn = !turn;
  }

  return std::make_pair(g, m);
}