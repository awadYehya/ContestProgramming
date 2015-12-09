The idea is to use Pascal's triangle. The solutions follow the same pattern

                1
			   1 1    Every number is the addition of the 2 above it ex  3 3 on the last row
			  1 2 1                                                       6
	         1 3 3 1
			1 4 6 4 1

Using this concept, our program should do this 
This is using input m = 4 and n = 3

    Pascal's triangle will be at a diagonal here
    Our board here is 4x3, we'll use an array[row][col] so array[3][4]

    0,	0,	0,	0,	Here the array is initialized
    0,	0,	0,	0,	
    0,	0,	0,	0,	
    
    1,	1,	1,	1,	We initialize all of the top row as 1's
    0,	0,	0,	0,	
    0,	0,	0,	0,	
    
    1,	1,	1,	1,	We initialize all of the left column as 1's
    1,	x,	0,	0,	I have placed an 'x' where we will calculate the value, it was previously a 0
    1,	0,	0,	0,	we calculate 'x' by adding the number on top of it (1), and to it's left (1)
    
    1,	1,	1,	1,	As you can see we got 2 in x's old position
    1,	2,	x,	0,	we do this agian for the next position, I have placed an 'x' there again
    1,	0,	0,	0,	again we add number at the top (1) and number to it's left (2)
    
    1,	1,	1,	1,	here we get a 3 since we did 2+1
    1,	2,	3,	x,	we repeat this process again
    1,	0,	0,	0,	
    
    1,	1,	1,	1,	we get a 4 from left(3)+top(1)
    1,	2,	3,	4,	we're done with this row, so we go to the next one
    1,	x,	0,	0,	
    
    1,	1,	1,	1,	we are at the next row and calculated it agian using top and left
    1,	2,	3,	4,	2 + 1 = 3
    1,	3,	x,	0,	
    
    1,	1,	1,	1,	
    1,	2,	3,	4,	3+3=6
    1,	3,	6,	x,	
    
    1,	1,	1,	1,	
    1,	2,	3,	4,	and lastly 6+4 = 10
    1,	3,	6,	10,	

    The solution is the number to the bottom right which here is 10



The code for this is:

    class Solution {
    public:
        int uniquePaths(int m, int n) {
            int board[n][m];
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
              for (int j = 1; j < m; j+=1) { // column loop
                board[i][j] = board[i-1][j] + board[i][j-1];
              }
            }
            return board[n-1][m-1];
        }
    };