#if defined(__GNUG__) && !defined(__clang__)
#warning The `using BotTurn` line will crash GCC (as of 7.0.1). Use Clang instead.
#endif

#if !defined(TAKE)
#define TAKE 3
#endif

#if !defined(PILE)
#define PILE 3
#endif

#include <algorithm>
#include <iostream>

template <int pile, bool _side>
struct OnceCheck {
	constexpr static int amount = pile;
	constexpr static bool lost = false;
	constexpr static bool side = _side;
};

template <bool _side>
struct OnceCheck <0, _side> {
	constexpr static int amount = 0;
	constexpr static bool lost = true;
	constexpr static bool side = _side;
};

template <int pile, bool side>
using BotTurn = OnceCheck<std::max(std::min(pile - (pile - 1) % 4, pile - 1), 0), side>;

template <int pile, int take, bool side>
using HumanTurn = OnceCheck<std::max(pile - take, 0), 1>;

template <int pile, int take, bool side>
struct OnceState;

template <int pile, int take>
struct OnceState <pile, take, 0> {
	using one = HumanTurn<pile, take, 1>;
	using two = BotTurn<one::amount, 0>;
	constexpr static int amount = two::amount;
	constexpr static bool side = one::lost ? one::side : two::side;
	constexpr static bool end = one::lost || two::lost;
};

template <int pile, int take>
struct OnceState <pile, take, 1> {
	using one = BotTurn<pile, 0>;
	using two = HumanTurn<pile, take, 1>;
	constexpr static int amount = two::amount;
	constexpr static bool side = one::lost ? one::side : two::side;
	constexpr static bool end = one::lost || two::lost;
};

static_assert(TAKE >= 1 && TAKE <= 3, "TAKE must be between 1 and 3");
static_assert(PILE > 0, "PILE must be positive");

using FinalResult = OnceState<PILE, TAKE, 0>;

constexpr int side = FinalResult::side + 1;
constexpr int amount = FinalResult::amount;
constexpr bool end = FinalResult::end;

int main() {
	if (end) {
		std::cout << "Side " << side << " won!" << std::endl;
	} else {
		std::cout << "The pile has " << amount << " stick" << (amount == 1 ? "" : "s") << "." << std::endl;
	}
	return 0;
}
