/**
 * Business Context: Security Log Anomaly Detection
 * Security logs often contain IP addresses or error codes that should be the same
 * when read forward or backward (palindromes). Detecting these helps identify
 * corrupted logs or potential network replay attacks. Also used in DNA sequence
 * analysis where palindromic sequences indicate certain genetic markers.
 *
 * Based on: Valid Palindrome (two-pointer approach, ignoring non-alphanumeric)
 */

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <fmt/base.h>
#include <ranges>
#include <string>
#include <string_view>

auto isLogEntrySymmetricOld(std::string_view secureLogEntry) -> bool {
	size_t leftIdx = 0;
	size_t rightIdx = secureLogEntry.size() - 1;

	while (leftIdx < rightIdx) {
		// skip non characters (space, punctuation)
		while (leftIdx < rightIdx && !std::isalnum(secureLogEntry.at(leftIdx)))
			leftIdx++;
		while (leftIdx < rightIdx && !std::isalnum(secureLogEntry.at(rightIdx)))
			rightIdx--;

		if (std::tolower(secureLogEntry.at(leftIdx)) != std::tolower(secureLogEntry.at(rightIdx)))
			return false;

		leftIdx++;
		rightIdx--;
	}

	return true; // everything matches
}

auto isLogEntrySymmetric(std::string_view secureLogEntry) -> bool {
	auto filtered = secureLogEntry | std::ranges::views::filter(::isalnum) | std::ranges::views::filter(::tolower);

	auto reversed = filtered | std::ranges::views::reverse;

	return std::ranges::equal(filtered, reversed);
}

auto main() -> int {
	// Example 1: Clean palindrome
	std::string logEntry1 = "A man a plan a canal Panama";
	// Returns: true (ignores spaces, case-insensitive)
	fmt::println("{} = {}", logEntry1, isLogEntrySymmetric(logEntry1) ? "true" : "false");

	// Example 2: Corrupted log
	std::string logEntry2 = "race a car";
	// Returns: false (raceacar is not a palindrome)
	fmt::println("{} = {}", logEntry2, isLogEntrySymmetric(logEntry2) ? "true" : "false");

	// Example 3: IP address pattern
	std::string logEntry3 = "192.291";
	// Returns: false (192291 is not a palindrome)
	fmt::println("{} = {}", logEntry3, isLogEntrySymmetric(logEntry3) ? "true" : "false");

	// Example 4: Simple palindrome
	std::string logEntry4 = "level";
	// Returns: true
	fmt::println("{} = {}", logEntry4, isLogEntrySymmetric(logEntry4) ? "true" : "false");

	// Example 5: Empty log
	std::string logEntry5 = "";
	// Returns: true (edge case - empty considered valid)
	fmt::println("{} = {}", logEntry5, isLogEntrySymmetric(logEntry5) ? "true" : "false");

	// Example 6: Empty log
	std::string logEntry6 = "myhome";
	// Returns: false
	fmt::println("{} = {}", logEntry6, isLogEntrySymmetric(logEntry6) ? "true" : "false");

	return 0;
}
