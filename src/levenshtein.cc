#include "levenshtein.hpp"

#include <algorithm>
#include <string_view>
#include <vector>

int compute_levenshtein_distance(std::string_view s1, std::string_view s2) {
	std::vector<std::vector<int>> matrix;

	int row_count = s2.length() + 1;
	int column_count = s1.length() + 1;

	// initialization of the matrix
	for (int i = 0; i < row_count; i++) {
		matrix.emplace_back(std::vector<int>{i});
	}
	for (int i = 1; i < column_count; i++) {
		matrix.at(0).emplace_back(i);
	}

	for (int row = 1; row < row_count; row++) {
		for (int column = 1; column < column_count; column++) {
			if (s2.at(row - 1) == s1.at(column - 1)) {
				matrix.at(row).emplace_back(matrix.at(row - 1).at(column - 1));
				continue;
			}

			int ed1 = matrix.at(row - 1).at(column);
			int ed2 = matrix.at(row - 1).at(column - 1);
			int ed3 = matrix.at(row).at(column - 1);

			matrix.at(row).emplace_back(std::min(std::min(ed1, ed2), ed3) + 1);
		}
	}

	return matrix.at(row_count - 1).at(column_count - 1);
}
