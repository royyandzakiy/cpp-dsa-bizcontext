/**
Business Context: Fraud Detection Alerts

You get a real-time stream of transaction amounts. You need to instantly find if two specific transactions from the last
minute add up to exactly a flagged fraud value. Hash map gives you O(1) lookups—critical for low-latency systems.
The fraudsters always use a signature fraud value that they use from their transactions. These low volume frauds are
hard to detect!

Based on: Two Sum (classic hash-map pair lookup)
 */

#include <fmt/base.h>
#include <fmt/ranges.h>
#include <unordered_map>
#include <vector>
using namespace std;

auto findFraudPair(vector<int> &transactions, int fraudSignatureValue) -> vector<int> {
	unordered_map<int, int> transactionIdxPairMap; // use this to store transactions

	for (int idx = 0; auto transaction : transactions) {
		// here we reverse search, by finding whether the sisa ever existed/stored to create the exact fraudValue
		auto sisaFraudValue = fraudSignatureValue - transaction;

		if (transactionIdxPairMap.contains(sisaFraudValue)) {
			// found a combination that creates the fraudValue! return :)
			return vector<int>{transactionIdxPairMap[sisaFraudValue], idx};
		}

		transactionIdxPairMap.emplace(transaction, idx); // just keep adding transactions with its idx
		idx++;
	}

	return {}; // the transactionIdxPairMap is full, we never found
}

auto main() -> int {
	fmt::println("--- Testing Fraud Pair Detection ---");
	std::vector<int> transactions = {10, 25, 40, 15, 60};
	int targetFraud = 55; // 15 (idx 3) + 40 (idx 2) = 55

	std::vector<int> fraudIndices = findFraudPair(transactions, targetFraud);
	std::vector<int> noFraudIndices = findFraudPair(transactions, 999);

	// Including <fmt/ranges.h> lets us print vectors directly like [2, 3]
	fmt::println("Transactions: {}", transactions);
	fmt::println("Target Fraud Value: {}", targetFraud);
	fmt::println("Found fraud pair at indices: {}", fraudIndices);
	fmt::println("Found fraud pair for 999: {}", noFraudIndices);

	return 0;
}
