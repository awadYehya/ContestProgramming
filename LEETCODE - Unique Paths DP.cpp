/* 
    Yehya Awad
    LEETCODE
    December 8th, 2015
*/

// Pascal's triangle method
class Solution {
public:
    int uniquePaths(int m, int n) {
        int board[m][n];
        // set top row as 1's
        for (int i = 0; i < m; i+=1) {
          board[0][i] = 1;
        }
        // set left column as 1's
        for (int i = 0; i < n; i+=1) {
          board[i][0] = 1;
        }
        // Pascalafy
        for (int i = 1; i < n; i+=1) { // row loop
          for (int j = 1; j < m; i+=1) { // column loop
            board[i][j] = board[i-1][j] + board[i][j-1];
          }
        }
        return board[m-1][n-1];
    }
};