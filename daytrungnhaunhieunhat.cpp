#include <iostream>
#include <vector>

using namespace std;

int longestCommonSubsequence(vector<int>& a, vector<int>& b) {
    int m = a.size();
    int n = b.size();

    // Tạo một bảng 2D để lưu độ dài LCS tại mỗi vị trí (i, j).
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Tính độ dài LCS bằng cách duyệt qua từng phần tử của cả hai dãy.
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[m][n]; // Độ dài LCS tại vị trí cuối cùng của mảng dp chính là kết quả.
}

int main() {
    vector<int> a = {1, 2, 3, 4, 5};
    vector<int> b = {2, 3, 4, 6, 8, 10};

    int result = longestCommonSubsequence(a, b);
    cout << result << endl;

    return 0;
}
