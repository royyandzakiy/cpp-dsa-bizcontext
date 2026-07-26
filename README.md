# DSA with Business Context

A personal collection of classic data structures & algorithms problems, each reframed
around a realistic business scenario (fraud detection, HR org charts, log analysis, etc.)
rather than an abstract prompt. The intent is to make each pattern stick by tying it to
where it actually shows up in production systems.

Written in **modern C++23**, one self-contained solution per folder.

## Problems

| # | Folder | Pattern | Business Framing |
|---|--------|---------|------------------|
| 1 | [1_twoSum](src/1_twoSum/main.cpp) | Two Sum (hash-map pair lookup) | Fraud detection — find two transactions summing to a flagged value |
| 2 | [2_containsDuplicate](src/2_containsDuplicate/main.cpp) | Contains Duplicate (hash-set membership) | Reject duplicate customer IDs before a DB import |
| 3 | [3_anagram](src/3_anagram/main.cpp) | Valid Anagram (frequency count) | Detect emails belonging to the same thread |
| 4 | [4_twoPointer](src/4_twoPointer/main.cpp) | Valid Palindrome (two pointers) | Security log symmetry / anomaly detection |
| 5 | [5_binaryTreeDepth](src/5_binaryTreeDepth/main.cpp) | Max Depth of Binary Tree (DFS) | Longest chain of command in an org chart |

## Layout

Each problem lives in its own folder under [src](src/) with a single `main.cpp`.
