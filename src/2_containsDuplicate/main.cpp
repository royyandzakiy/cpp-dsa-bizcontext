/**
 * Business Context: Unique Customer ID Check
 * You're importing a CSV of 1M customer records. Duplicate IDs would corrupt your
 * primary key. Using a hash set lets you reject the whole batch in O(n) time before
 * hitting the database—saving expensive rollback operations.
 *
 * Based on: Contains Duplicate (hash-set membership checking)
 */

#include <algorithm>
#include <fmt/base.h>
#include <unordered_set>
#include <vector>
using namespace std;

auto hasDuplicateCustomerId(vector<int> &customerIds) {
	auto seenIds = unordered_set<int>{};

	// any of returns true if if at least one return from lambda yields true
	return std::ranges::any_of(customerIds, [&](int id) {
		// if fail to insert, then already exists
		auto alreadyExists = !seenIds.insert(id).second;
		return alreadyExists;
	});
}

auto main() -> int {
	std::vector<int> uniqueCustomers = {101, 102, 103, 104};
	std::vector<int> duplicateCustomers = {201, 202, 203, 202, 204};

	// fmt automatically prints booleans as "true" or "false" by default
	fmt::print("Testing unique list: {}\n", hasDuplicateCustomerId(uniqueCustomers));
	fmt::print("Testing duplicate list: {}\n", hasDuplicateCustomerId(duplicateCustomers));

	return 0;
}
