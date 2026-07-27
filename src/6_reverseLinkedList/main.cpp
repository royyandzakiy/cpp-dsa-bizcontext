/**
 * Business Context: Undo/Redo History Management
 * In text editors or design tools, you need to reverse a user's action history for
 * undo/redo functionality. This allows users to step backward through their actions
 * efficiently without storing massive history arrays. Also used in browser back
 * button navigation.
 *
 * Based on: Reverse Linked List (pointer manipulation)
 */

#include <fmt/base.h>
#include <memory>
#include <string>
#include <string_view>
#include <utility>

struct HistoryItem {
	std::string action;
	std::unique_ptr<HistoryItem> previousItem{nullptr};
	std::unique_ptr<HistoryItem> nextItem{nullptr};

	HistoryItem(std::string_view _action) : action(_action) {
	}
};

auto reverseHistoryList(std::unique_ptr<HistoryItem> historyListHead) -> std::unique_ptr<HistoryItem> {
	std::unique_ptr<HistoryItem> tempCurr = std::move(historyListHead);
	std::unique_ptr<HistoryItem> tempPrev{nullptr}, tempNext{nullptr};

	while (tempCurr != nullptr) {
		// temporarily store nextItem
		tempNext = std::move(tempCurr->nextItem);

		// SWAP: change historyListHead->nextItem to the previously stored tempPrev
		tempCurr->nextItem = std::move(tempPrev);

		// --- for next iteration use ---
		// temporarily store current in tempPrev
		tempPrev = std::move(tempCurr);

		// continue, prepare to modify the nextItem (that was stored inside tempNext)
		tempCurr = std::move(tempNext);
	}

	return std::move(tempPrev);
}

auto printHistoryList(const std::unique_ptr<HistoryItem> &head) {
	const HistoryItem *myNode = head.get();
	while (myNode) {
		fmt::print("{} -> ", myNode->action);
		myNode = myNode->nextItem.get();
	}
	fmt::println("nullptr");
}

auto main() -> int {
	// Example 1: Simple action history
	fmt::println("-------- Example 1 --------");
	auto head = std::make_unique<HistoryItem>("type A");
	head->nextItem = std::make_unique<HistoryItem>("type B");
	head->nextItem->nextItem = std::make_unique<HistoryItem>("type C");
	// Original: A → B → C
	// After reverse: C → B → A
	printHistoryList(head);
	printHistoryList(reverseHistoryList(std::move(head)));

	// Example 2: Single action
	fmt::println("-------- Example 2 --------");
	auto head2 = std::make_unique<HistoryItem>("delete");
	// After reverse: delete (unchanged)
	printHistoryList(head2);
	printHistoryList(reverseHistoryList(std::move(head2)));

	// Example 3: Empty history
	fmt::println("-------- Example 3 --------");
	auto head3 = nullptr;
	// Returns: nullptr (empty history)
	printHistoryList(head3);
	printHistoryList(reverseHistoryList(std::move(head3)));

	// Example 4: Two actions
	fmt::println("-------- Example 4 --------");
	auto head4 = std::make_unique<HistoryItem>("copy");
	head4->nextItem = std::make_unique<HistoryItem>("paste");
	// Original: copy → paste
	// After reverse: paste → copy
	printHistoryList(head4);
	printHistoryList(reverseHistoryList(std::move(head4)));

	return 0;
}
