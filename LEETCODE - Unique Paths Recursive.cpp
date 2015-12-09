/* 
    Yehya Awad
    LEETCODE
    December 8th, 2015
*/

class Solution {
public:
    int diffpaths = 0; // different paths counter
    int uniquePaths(int m, int n) {
        turn(m,n,0,0); // make first step
        return diffpaths;
    }
    // recursive algorithm
    void turn(int m, int n, int x, int y) {
		// Add 1 when you reach the end
        if (x == m-1 && y == n-1) {
            diffpaths += 1;
            return;
        }
		// Make right turn
        if (x < m-1){
            turn(m,n,x+1,y);
        }
		// Make left turn
        if (y < n-1) {
            turn(m,n,x,y+1);
        }
    }
};