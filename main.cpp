#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <numeric>
#include <algorithm>

class solution {
public:
  std::vector<std::vector<std::string>> palindromeCut(const std::string & s) {
    auto partitions = getPaths(s, std::vector<std::string>());
    for (auto partition : partitions) {
      std::copy(partition.begin(), partition.end(), std::ostream_iterator<std::string>(std::cout, " "));
      std::cout << std::endl;
    }
    return partitions;
  }

private:
  std::vector<std::vector<std::string>> getPaths(const std::string & s, const std::vector<std::string> & curr) {
    std::vector<std::vector<std::string>> result;
    if (getLength(curr) == s.size())
      result.push_back(curr);
    else {
      std::vector<std::string> next = getNext(s, curr);
      for (auto nx : next) {
	auto cpy = curr;
	cpy.push_back(nx);
	auto temp = getPaths(s, cpy);
	std::copy(temp.begin(), temp.end(), std::inserter(result, result.end()));
      }
    }
    return result;
  }

  std::vector<std::string> getNext(const std::string & s, const std::vector<std::string> & curr) {
    std::vector<std::string> next;
    size_t start = getLength(curr);
    if (start < s.size()) {
      size_t end = s.size();
      while (end > start) {
	if (isPalin(s.substr(start, end-start)))
	  next.push_back(s.substr(start, end-start));
	end--;
      }
    }
    return next;
  }

  bool isPalin(const std::string & s) {
    return std::equal(s.begin(), s.end(), s.rbegin());
  }

  size_t getLength(const std::vector<std::string> & vec) {
    return std::accumulate(vec.begin(), vec.end(), 0,
			   [](size_t i, const std::string & s){
			     return i+s.size();
			   });
  }
};

int main() {
  std::string s{"aab"};

  solution soln;
  auto paths = soln.palindromeCut(s);
  
}
