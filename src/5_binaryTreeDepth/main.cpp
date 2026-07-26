/**
 * Business Context: Organization Chart Analysis
 * In HR systems, you need to calculate the maximum depth of an organization's
 * reporting structure. This helps determine the longest chain of command and
 * identify potential bottlenecks in communication. Also used in corporate
 * hierarchy optimization.
 *
 * Based on: Maximum Depth of Binary Tree (DFS/BFS traversal)
 */

#include <algorithm>
#include <fmt/base.h>
#include <memory>

struct Employee {
	int id;
	std::unique_ptr<Employee> leftDirectReport{nullptr};
	std::unique_ptr<Employee> rightDirectReport{nullptr};
	Employee(int _id) : id(_id) {
	}
};

auto getMaxDepth(const std::unique_ptr<Employee> &root) -> int {
	if (root == nullptr)
		return 0;

	auto leftDirectReportDepth = getMaxDepth(root->leftDirectReport);
	auto rightDirectReportDepth = getMaxDepth(root->rightDirectReport);

	return 1 + std::max(leftDirectReportDepth, rightDirectReportDepth);
}

auto main() -> int {
	// Example 1: Simple tree (CEO with 2 direct reports)
	auto orgTopLeader1 = std::make_unique<Employee>(1);
	orgTopLeader1->leftDirectReport = std::make_unique<Employee>(2);
	orgTopLeader1->rightDirectReport = std::make_unique<Employee>(3);
	// Returns: 2 (CEO → employee)
	fmt::println("{}", getMaxDepth(orgTopLeader1));

	// Example 2: Deep hierarchy
	auto orgTopLeader2 = std::make_unique<Employee>(1);
	orgTopLeader2->leftDirectReport = std::make_unique<Employee>(2);
	orgTopLeader2->leftDirectReport->leftDirectReport = std::make_unique<Employee>(3);
	orgTopLeader2->leftDirectReport->leftDirectReport->leftDirectReport = std::make_unique<Employee>(4);
	// Returns: 4 (CEO → V → Manager → Individual Contributor)
	fmt::println("{}", getMaxDepth(orgTopLeader2));

	// Example 3: Balanced hierarchy
	auto orgTopLeader3 = std::make_unique<Employee>(1);
	orgTopLeader3->leftDirectReport = std::make_unique<Employee>(2);
	orgTopLeader3->rightDirectReport = std::make_unique<Employee>(3);
	orgTopLeader3->leftDirectReport->leftDirectReport = std::make_unique<Employee>(4);
	orgTopLeader3->leftDirectReport->rightDirectReport = std::make_unique<Employee>(5);
	orgTopLeader3->rightDirectReport->leftDirectReport = std::make_unique<Employee>(6);
	// Returns: 3 (CEO → Manager → Employee)
	fmt::println("{}", getMaxDepth(orgTopLeader3));

	// Example 4: Empty org (no employees)
	std::unique_ptr<Employee> orgTopLeader4 = nullptr;
	// Returns: 0
	fmt::println("{}", getMaxDepth(orgTopLeader4));

	// Example 5: Single employee (just CEO)
	auto orgTopLeader5 = std::make_unique<Employee>(1);
	// Returns: 1
	fmt::println("{}", getMaxDepth(orgTopLeader5));

	return 0;
}
