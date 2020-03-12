// dijsktras.cpp

// Main Execution

#include <iostream>
#include <map>
#include <vector>
#include <limits.h>
#include <deque>

using namespace std;

struct Node{
	int row;
	int col;
	int position;
	int distance;
	int cost;
	char name;
	bool visit;
	map<int,int>edge;
	int backRow;
	int backCol;

	Node(){
		distance = INT_MAX;//From the wiki page
		visit = false;
	}

	
};

int main(int argc, char *argv[]) {
    
	int numTile;

	cin >> numTile;
	char tilel;
	int tileCost;
	char tileChar;
	map<char,int>cost;
	map<char,int>::iterator it;
	for(int i = 0; i < numTile; i++){
		
		cin >> tilel>> tileCost;
		cost[tilel] = tileCost;
	}

	int row;
	int col;

	cin >> row >> col;

	vector< vector<Node> >grid;

	grid.resize(row);

	
	for(int i = 0; i < row; i++){
		grid[i].resize(col);
	}
	

	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			cin >> tileChar;

			grid[i][j].row = i;
			grid[i][j].col = j;
			
			it = cost.find(tileChar);
			grid[i][j].cost = it -> second;
      grid[i][j].name = tileChar;
		}

	}
	

	int rowStart;
	int colStart;
	int rowEnd;
	int colEnd;

	int tempDistance;

	cin >> rowStart >> colStart >> rowEnd >> colEnd;

	grid[rowStart][colStart].distance = 0;

	Node startN = grid[rowStart][colStart];
	Node endN = grid[rowEnd][colEnd];

	int tempRow;
  int tempCol;
	
	multimap<int, Node> nDistance;
	multimap<int, Node>::iterator mmIT;

	nDistance.insert(make_pair(startN.distance, startN));

	//Dijkstra's algorithm
	while(nDistance.size() != 0){
		mmIT = nDistance.begin();

		
		tempRow = mmIT->second.row;
		tempCol = mmIT->second.col;

		nDistance.erase(mmIT);

		grid[tempRow][tempCol].visit = true;
		//check the right side
		if(grid[tempRow][tempCol].col + 1 < col && grid[tempRow][tempCol+1].visit != true){
			tempDistance = grid[tempRow][tempCol].distance + grid[tempRow][tempCol+1].cost;
			if(grid[tempRow][tempCol+1].distance == INT_MAX ||tempDistance<grid[tempRow][tempCol+1].distance){
				for(mmIT = nDistance.begin(); mmIT != nDistance.end(); mmIT++){
					if(tempRow == mmIT->second.row && tempCol+1 == mmIT ->second.col){
             //delete mmIT before iterating it
						nDistance.erase(mmIT++);
           }
           }
						grid[tempRow][tempCol+1].distance = tempDistance;
						grid[tempRow][tempCol+1].backRow = tempRow;
						grid[tempRow][tempCol+1].backCol = tempCol;
						nDistance.insert(make_pair(grid[tempRow][tempCol+1].distance, grid[tempRow][tempCol+1]));				
			}
		}

		//check the left side
   if(grid[tempRow][tempCol].col -1 >= 0 && grid[tempRow][tempCol-1].visit != true){
			tempDistance = grid[tempRow][tempCol].distance + grid[tempRow][tempCol-1].cost;
			if(grid[tempRow][tempCol-1].distance == INT_MAX ||tempDistance<grid[tempRow][tempCol-1].distance){
				for(mmIT = nDistance.begin(); mmIT != nDistance.end();  mmIT++){
					if(tempRow == mmIT->second.row && tempCol-1 == mmIT ->second.col){
             //delete mmIT before iterating it
						nDistance.erase(mmIT++);
                }             
        }      
						grid[tempRow][tempCol-1].distance = tempDistance;
						grid[tempRow][tempCol-1].backRow = tempRow;
						grid[tempRow][tempCol-1].backCol = tempCol;
						nDistance.insert(make_pair(grid[tempRow][tempCol-1].distance, grid[tempRow][tempCol-1]));
    	}
		}

   //check the top side
   if(grid[tempRow][tempCol].row - 1 >= 0 && grid[tempRow-1][tempCol].visit != true){
			tempDistance = grid[tempRow][tempCol].distance + grid[tempRow-1][tempCol].cost;
			if(grid[tempRow-1][tempCol].distance == INT_MAX ||tempDistance<grid[tempRow-1][tempCol].distance){
				for(mmIT = nDistance.begin(); mmIT != nDistance.end(); mmIT++){
					if(tempRow-1 == mmIT->second.row && tempCol == mmIT ->second.col){
             //delete mmIT before iterating it
						nDistance.erase(mmIT++);
            }
        }
				grid[tempRow-1][tempCol].distance = tempDistance;
        grid[tempRow-1][tempCol].backRow = tempRow;
        grid[tempRow-1][tempCol].backCol = tempCol;
        nDistance.insert(make_pair(grid[tempRow-1][tempCol].distance, grid[tempRow-1][tempCol]));
			}
		}
   //check the bottom side
   if(grid[tempRow][tempCol].row + 1 < row && grid[tempRow+1][tempCol].visit != true){
			tempDistance = grid[tempRow][tempCol].distance + grid[tempRow+1][tempCol].cost;
			if(grid[tempRow+1][tempCol].distance == INT_MAX ||tempDistance<grid[tempRow+1][tempCol].distance){
				for(mmIT = nDistance.begin(); mmIT != nDistance.end(); mmIT++){
					if(tempRow+1 == mmIT->second.row && tempCol == mmIT ->second.col){
            //delete mmIT before iterating it
						nDistance.erase(mmIT++);
            }
        }
						grid[tempRow+1][tempCol].distance = tempDistance;
						grid[tempRow+1][tempCol].backRow = tempRow;
						grid[tempRow+1][tempCol].backCol = tempCol;
						nDistance.insert(make_pair(grid[tempRow+1][tempCol].distance, grid[tempRow+1][tempCol]));		
			}
		}
   
   }
   
   deque<int>path;
   int total_distance;
   total_distance = grid[rowEnd][colEnd].distance - grid[rowEnd][colEnd].cost + grid[rowStart][colStart].cost;
   cout << total_distance << endl;
   tempRow = rowEnd;
   tempCol = colEnd;
   //loop backwards from the end of the path and push the path to the front of the deque
   while((grid[tempRow][tempCol].col != grid[rowStart][colStart].col) && (grid[tempRow][tempCol].row != grid[rowStart][colStart].row)){
       path.push_front(grid[tempRow][tempCol].backCol);
       path.push_front(grid[tempRow][tempCol].backRow);
       tempRow = grid[tempRow][tempCol].backRow;
       tempCol = grid[tempRow][tempCol].backCol;
   }
   cout << rowStart << " " << colStart << endl;
   for(int i = 0; i < path.size(); i++){
       cout << path[i] << " ";
       i++;
       cout << path[i] << endl;
   } 
  
	cout << rowEnd << " " << colEnd <<endl;
	
	return 0;
}

