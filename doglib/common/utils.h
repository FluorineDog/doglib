#pragma once
#include <algorithm>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <string>
#include <memory>
#include <queue>
#include <stack>
#include <cassert>
#include <functional>
#include <numeric>
template <class T>
using min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;