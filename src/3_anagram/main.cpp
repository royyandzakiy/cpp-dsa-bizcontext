/**
Business Context: Fraud Detection Alerts

You get a real-time stream of transaction amounts. You need to instantly find if two specific transactions from the last
minute add up to exactly a flagged fraud value. Hash map gives you O(1) lookups—critical for low-latency systems.
The fraudsters always use a signature fraud value that they use from their transactions. These low volume frauds are
hard to detect!

Based on: Two Sum (classic hash-map pair lookup)
 */

#include <algorithm>
#include <array>
#include <fmt/base.h>
#include <string>
#include <string_view>
using namespace std;

auto areEmailsSameThread(std::string_view emailSubject1, std::string_view emailSubject2) -> bool {
	if (emailSubject1.size() != emailSubject2.size())
		return false;

	// array is better than unordered_map bcs explicitly defines 104 bytes in stack
	// using unordered_map dynamically allocates in heap for its nodes
	auto letterCount = std::array<int, 26>{};

	// count letters from 1st email subject
	for (char letter : emailSubject1) {
		letterCount.at(letter - 'a')++;
	}

	// all of returns true if all return from lambda yields true
	return ranges::all_of(emailSubject2, [&](char letter) -> bool { return --letterCount.at(letter - 'a') >= 0; });
}

auto main() -> int {
	fmt::print("--- Testing Email Anagram Thread Grouping ---\n\n");

	// Case 1: Typo thread grouping (Anagram matches)
	std::string emailA = "meeting";
	std::string emailB = "teemgin"; // typo with exact same letters

	// Case 2: Unrelated thread (Same length, different character makeup)
	std::string emailC = "project";
	std::string emailD = "product";

	// Case 3: Completely structural mismatch (Different sizes)
	std::string emailE = "review";
	std::string emailF = "reviews";

	fmt::print("Comparing '{}' vs '{}' (Typo Match):\n-> Same thread? {}\n\n", emailA, emailB,
			   areEmailsSameThread(emailA, emailB));

	fmt::print("Comparing '{}' vs '{}' (Different contents):\n-> Same thread? {}\n\n", emailC, emailD,
			   areEmailsSameThread(emailC, emailD));

	fmt::print("Comparing '{}' vs '{}' (Size mismatch):\n-> Same thread? {}\n", emailE, emailF,
			   areEmailsSameThread(emailE, emailF));

	return 0;
}
