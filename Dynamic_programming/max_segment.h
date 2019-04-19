#pragma once

#include <Util/std.h>
#include <Util/ranges.h>
#include <Util/Util.h>

namespace dp_ns
{
    using range_ns::xrange;
    constexpr ll INF = std::numeric_limits<ll>::max();

    ll find_max_segment(const std::vector<ll> vec)
    {
	ll min_sum = 0;
	ll sum = 0;
	ll ans = -INF;
	for (ll i : xrange(size(vec)))
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
	for (ll i : xrange(row_count))
	    rows_sums[i] = range_ns::partial_sum(matrix[i]);

	ll ans = -INF;
	for (ll i : xrange(column_count))
	{
	    for (ll j : xrange(i, column_count))
	    {
		std::vector<ll> rows_partial_sums(row_count);
		for (ll k : xrange(row_count))
		    rows_partial_sums[k] = rows_sums[k][j] - (i == 0 ? 0 : rows_sums[k][i - 1]);
		ans = std::max(ans, find_max_segment(rows_partial_sums));
	    }
	}
	return ans;
    }

    ll max_submatrix_naive(const std::vector<std::vector<ll>>& matrix)
    {
	const ll row_count = size(matrix);
	const ll column_count = size(matrix[0]);

	std::vector<std::vector<ll>> sums(row_count + 1,  std::vector<ll>(column_count + 1));
	for (ll i : xrange(1, row_count + 1))
	    for (ll j : xrange(1, column_count + 1))
		sums[i][j] = sums[i - 1][j] + sums[i][j - 1] - sums[i - 1][j - 1] + matrix[i - 1][j - 1];

	ll ans = -INF;
	for (ll x1 : xrange(1, row_count + 1))
	    for (ll y1 : xrange(1, column_count + 1))
		for (ll x2 : xrange(x1, row_count + 1))
		    for (ll y2 : xrange(y1, column_count + 1))
			ans = std::max(ans, sums[x2][y2] - sums[x1 - 1][y2] - sums[x2][y1 - 1] + sums[x1 - 1][y1 - 1]);
	return ans;
    }
}
