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

		// temporarily store current in tempPrev
		tempPrev = std::move(tempCurr);

		// continue, prepare to modify the nextItem (that was stored inside tempNext)
		tempCurr = std::move(tempNext);
	}

	return std::move(tempPrev);
}

auto main() -> int {

	return 0;
}
