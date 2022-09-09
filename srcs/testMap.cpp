#include "tests.hpp"

#include <map>
#include "map.hpp"
#include <utility>

void ft_hitchcock(std::map<string, int> &real, ft::map<string, int> &mine){
	real["The Pleasure Garden"] = 1925;
	real["The Lodger"] = 1927;
	real["The Ring"] = 1927;
	real["Downhill"] = 1927;
	real["The Farmer's Wife"] = 1928;
	real["Easy Virtue"] = 1928;
	real["Champagne"] = 1928;
	real["The Manxman"] = 1929;
	real["Blackmail"] = 1929;
	real["Juno and the Paycock"] = 1930;
	real["Murder!"] = 1930;
	real["The Skin Game"] = 1931;
	real["Mary" ]= 1931;
	real["Rich and Strange"] = 1931;
	real["Number Seventeen"] = 1932;
	real["Waltzes from Vienna"] = 1934;
	real["The Man Who Knew Too Much"] = 1934;
	real["The 39 Steps"] = 1935;
	real["Secret Agent"] = 1936;
	real["Sabotage" ]= 1936;
	real["Young and Innocent"] = 1937;
	real["The Lady Vanishes"] = 1938;
	real["Jamaica Inn"] = 1939;
	real["Rebecca"] = 1940;
	real["Foreign Correspondent"] = 1940;
	real["Mr. & Mrs. Smith"] = 1941;
	real["Suspicion"] = 1941;
	real["Saboteur"] = 1942;
	real["Shadow of a Doubt"] = 1943;
	real["Lifeboat"] = 1944;
	real["Spellbound"] = 1945;
	real["Notorious"] = 1946;
	real["The Paradine Case"] = 1947;
	real["Rope"] = 1948;
	real["Under Capricorn"] = 1949;
	real["Stage Fright"] = 1950;
	real["Strangers on a Train"] = 1951;
	real["I Confess"] = 1953;
	real["Dial M for Murder"] = 1954;
	real["Rear Window"] = 1954;
	real["To Catch a Thief"] = 1955;
	real["The Trouble with Harry"] = 1955;
	real["The Man Who Knew Too Much"] = 1956;
	real["The Wrong Man"] = 1956;
	real["Vertigo"] = 1958;
	real["North by Northwest"] = 1959;
	real["Psycho"] = 1960;
	real["The Birds" ]= 1963;
	real["Marnie"] = 1964;
	real["Torn Curtain"] = 1966;
	real["Topaz"] = 1969;
	real["Frenzy"] = 1972;
	real["Family Plot"] = 1976;

	mine["The Pleasure Garden"] = 1925;
	mine["The Lodger"] = 1927;
	mine["The Ring"] = 1927;
	mine["Downhill"] = 1927;
	mine["The Farmer's Wife"] = 1928;
	mine["Easy Virtue"] = 1928;
	mine["Champagne"] = 1928;
	mine["The Manxman"] = 1929;
	mine["Blackmail"] = 1929;
	mine["Juno and the Paycock"] = 1930;
	mine["Murder!"] = 1930;
	mine["The Skin Game"] = 1931;
	mine["Mary" ]= 1931;
	mine["Rich and Strange"] = 1931;
	mine["Number Seventeen"] = 1932;
	mine["Waltzes from Vienna"] = 1934;
	mine["The Man Who Knew Too Much"] = 1934;
	mine["The 39 Steps"] = 1935;
	mine["Secret Agent"] = 1936;
	mine["Sabotage" ]= 1936;
	mine["Young and Innocent"] = 1937;
	mine["The Lady Vanishes"] = 1938;
	mine["Jamaica Inn"] = 1939;
	mine["Rebecca"] = 1940;
	mine["Foreign Correspondent"] = 1940;
	mine["Mr. & Mrs. Smith"] = 1941;
	mine["Suspicion"] = 1941;
	mine["Saboteur"] = 1942;
	mine["Shadow of a Doubt"] = 1943;
	mine["Lifeboat"] = 1944;
	mine["Spellbound"] = 1945;
	mine["Notorious"] = 1946;
	mine["The Paradine Case"] = 1947;
	mine["Rope"] = 1948;
	mine["Under Capricorn"] = 1949;
	mine["Stage Fright"] = 1950;
	mine["Strangers on a Train"] = 1951;
	mine["I Confess"] = 1953;
	mine["Dial M for Murder"] = 1954;
	mine["Rear Window"] = 1954;
	mine["To Catch a Thief"] = 1955;
	mine["The Trouble with Harry"] = 1955;
	mine["The Man Who Knew Too Much"] = 1956;
	mine["The Wrong Man"] = 1956;
	mine["Vertigo"] = 1958;
	mine["North by Northwest"] = 1959;
	mine["Psycho"] = 1960;
	mine["The Birds" ]= 1963;
	mine["Marnie"] = 1964;
	mine["Torn Curtain"] = 1966;
	mine["Topaz"] = 1969;
	mine["Frenzy"] = 1972;
	mine["Family Plot"] = 1976;
}

template<class Key, class Value>
bool compare(ft::map<Key, Value> mine, std::map<Key, Value> real) {
	if (mine.size() != real.size()) {
		PRINT_KO;
		std::cout << "SIZE IS DIFFERENT: " << mine.size() << " / " << real.size() << std::endl;
		return (false);
	}

	typename ft::map<Key, Value>::iterator	myIt;
	typename std::map<Key, Value>::iterator	realIt = real.begin();
	for (myIt = mine.begin(); myIt != mine.end(); myIt++) {
		// if (*myIt != *realIt++) {
		// 	PRINT_KO;
		// 	// printMine(mine);
		// 	// printReal(real);
		// 	return (false);
		// }
	}
	PRINT_OK;
	return (true);
}

int testMap() {
	clock_t begin, end;
	float	realRes, myRes;
	int		resClock = 0, count = 0;

	ANNOUNCE1("CONSTRUCTOR TEST");
	
	ANNOUNCE2("Map Constructor Type 1: Default Constructor");

	START_CLOCK;
	std::map<string, int> real;
	END_CLOCK_REAL;
	START_CLOCK;
	ft::map<string, int> mine;
	END_CLOCK_MY;
	CHECK(MAP, ONLY_CLOCK);

	// ft::map<string, int>::iterator myIt = mine.begin();
	// std::map<string, int>::iterator realIt = real.begin();
	// std::cout << "pardon?" << std::endl;
	// std::cout << "my type: " << typeid(myIt).name() << std::endl;
	// std::cout << "real type: " << typeid(realIt).name() << std::endl;

	ANNOUNCE2("Map Constructor Type 2: Default Constructor with compare and allocator");

	START_CLOCK;
	real = std::map<string, int>(std::less<string>(), std::allocator<std::pair<const string, int> >());
	END_CLOCK_REAL;
	START_CLOCK;
	mine = ft::map<string, int>(std::less<string>(), std::allocator<ft::pair<const string, int> >());
	END_CLOCK_MY;
	CHECK(MAP, ONLY_CLOCK);

	ANNOUNCE2("Map Constructor Type 3: Constructor with iterator");
	std::map<string, int>	realHitchcock;
	ft::map<string, int>	myHitchcock;

	ft_hitchcock(realHitchcock, myHitchcock);

	std::cout << "test value at begin: " << (*realHitchcock.begin()).second << std::endl;
	START_CLOCK;
	real = std::map<string, int>(realHitchcock.begin(), realHitchcock.end());
	END_CLOCK_REAL;
	START_CLOCK;
	mine = ft::map<string, int>(myHitchcock.begin(), myHitchcock.end());
	END_CLOCK_MY;
	CHECK(MAP, ONLY_CLOCK);

	END_TEST(MAP);
}

