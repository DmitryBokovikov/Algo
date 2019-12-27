#pragma once

#include <Util/std.h>
#include <Util/ranges.h>
#include <Util/Util.h>

namespace dp_ns
{
    using range_ns::indices;
    constexpr ll INF = std::numeric_limits<ll>::max();

    ll find_max_segment(const std::vector<ll> vec)
    {
	ll min_sum = 0;
	ll sum = 0;
	ll ans = -INF;
	for (ll i : indices(size(vec)))
	{
	    sum += vec[i];
	    ans = std::max(sum - min_sum, ans);
	    min_sum = std::min(min_sum, sum);
	}
	return ans;
    }

    ll max_submatrix(const std::vector<std::vector<ll>>& matrix)
    {
	const ll row_count = size(matrix);
	const ll column_count = size(matrix[0]);

	std::vector<std::vector<ll>> rows_sums(row_count);
	for (ll i : indices(row_count))
	    rows_sums[i] = range_ns::partial_sum(matrix[i]);

	ll ans = -INF;
	for (ll i : indices(column_count))
	{
	    for (ll j : indices(i, column_count))
	    {
		std::vector<ll> rows_partial_sums(row_count);
		for (ll k : indices(row_count))
		    rows_partial_sums[k] = rows_sums[k][j] - (i == 0 ? 0 : rows_sums[k][i - 1]);
		ans = std::max(ans, find_max_segment(rows_partial_sums));
	    }
	}
	return ans;
    }

    ll max_submatrix_naive(const std::vector<std::vector<ll>>& matrix)
    {
	const int row_count = size(matrix);
	const int column_count = size(matrix[0]);

	std::vector<std::vector<ll>> sums(row_count + 1,  std::vector<ll>(column_count + 1));
	for (ll i : indices(1, row_count + 1))
	    for (ll j : indices(1, column_count + 1))
		sums[i][j] = sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1] + matrix[i - 1][j - 1];

	ll ans = -INF;
	for (int x1 : indices(1, row_count + 1))
	    for (int y1 : indices(1, column_count + 1))
		for (int x2 : indices(x1, row_count + 1))
		    for (int y2 : indices(y1, column_count + 1))
			ans = std::max(ans, sums[x2][y2] - sums[x1 - 1][y2] - sums[x2][y1 - 1] + sums[x1 - 1][y1 - 1]);
	return ans;
    }
}
