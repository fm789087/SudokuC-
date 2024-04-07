#include <iostream>
#include <typeinfo> 
#include <stdexcept>
#include <sstream>  
using namespace std; 

//Colour Strings 
string MAGENTA = "\u001B[35m"; 
string WHITE = "\u001B[0m"; 
string CYAN = "\u001B[36m";

//Function to display the board 
void displayBoard(int ogBoard[9][9], int p1[9][9]) 
{
  //Iterate through each row 
  for (int y=0; y<9; y++)
  {
    string rowString=""; 
    //Seperate every 3 rows with a section of dots 
    if(y%3==0)
      cout<<"\n"<<".............";
    //Iterate through each element in the row 
    for(int z=0; z<9; z++)
    {
      //Seperate every 3 elements with " | "
      if(z%3==0)
        if(ogBoard[y][z]==0 && p1[y][z]!=0) 
          rowString = rowString + "|"+ CYAN + std::to_string(p1[y][z]) + WHITE;   
        else if(ogBoard[y][z]==0)
          rowString = rowString + "|" + MAGENTA + std::to_string(p1[y][z]) + WHITE; 
        else 
          rowString = rowString + "|" + std::to_string(p1[y][z]); 
      else 
        if(ogBoard[y][z]==0 && p1[y][z]!=0)
           rowString = rowString  + CYAN + std::to_string(p1[y][z]) + WHITE;   
        else if(ogBoard[y][z]==0)
          rowString = rowString  + MAGENTA + std::to_string(p1[y][z]) + WHITE;   
        else 
          rowString = rowString + std::to_string(p1[y][z]);        
      if(z==8)
      {
        rowString+="|";
        cout<<"\n"<<rowString; 
      }
    }
  }
  cout<<"\n"<<"............."<<endl;     
}

int main() {
  //Create a while loop that creates a 9 x 9 grid from 1-9 
  //VARIABLES 
  int xCoord=0; //X coordinate of the guess
  int yCoord=0; //Y coordinate of the guess
  bool win=false; //if the user wins 
  bool lose=false; //if the user loses
  bool boardFilled=false; //Check if the board is filled 
  int num=0; //number that the user will enter 
  int ogBoard[9][9]= {{0,0,4,0,5,0,0,0,0}, {9,0,0,7,3,4,6,0,0}, {0,0,3,0,2,1,0,4,9}, {0,3,5,0,9,0,4,8,0}, {0,9,0,0,0,0,0,3,0}, {0,7,6,0,1,0,9,2}, {3,1,0,9,7,0,2,0,0}, {0,0,9,1,8,2,0,0,3}, {0,0,0,0,6,0,1,0,0} }; //the original unchanged board 
  int p1[9][9]  = {{0,0,4,0,5,0,0,0,0}, {9,0,0,7,3,4,6,0,0}, {0,0,3,0,2,1,0,4,9}, {0,3,5,0,9,0,4,8,0}, {0,9,0,0,0,0,0,3,0}, {0,7,6,0,1,0,9,2}, {3,1,0,9,7,0,2,0,0}, {0,0,9,1,8,2,0,0,3}, {0,0,0,0,6,0,1,0,0} }; //the user's board 
  cout<<"Welcome to Sudoku! Place a number in where the 0's are! "<<endl; 
  displayBoard(ogBoard,p1); 

  //if the player hasn't won yet 
  while(win!=true) 
  {
    do{
      displayBoard(ogBoard,p1);  
      //prompt for the x coord, y coord, and number:
      cout<<"Enter the x Coordinate you'd like to put/replace a #:"<<endl;
      cin>>xCoord; 
      cout<<"Enter the y Coordinate you'd like to put/replace a #:"<<endl; 
      cin>>yCoord;
      cout<<"Enter the number you would like to put from 1-9:"<<endl; 
      cin>>num; 
      xCoord-=1; 
      yCoord-=1; 

      //validation checks 
      if((p1[yCoord][xCoord]>0 && ogBoard[yCoord][xCoord]!=0))
      {
        cout<<"Oopsies! You can't put a number where the default number is! Try again!"<<endl; 
      } 
      else if(num<=0||num>9)
      {
        cout<<"Oopsies! You have to enter a number from 1-9!"<<endl;
      }
    } while ((p1[yCoord][xCoord]>0 && ogBoard[yCoord][xCoord]!=0)||num<=0||num>9); //loop if not valid input 

    p1[yCoord][xCoord]=num; 
    
    /* get the positions of the columns in the same cell as the xCoord */
    int colStart; 
    int colEnd; 
    int rowStart; 
    int rowEnd;  
    if(xCoord%3==0)
    {
      colStart=xCoord; 
      colEnd=xCoord+2; 
    }
    if(xCoord%3==1)
    {
      colStart= xCoord-1; 
      colEnd = xCoord+1;       
    }
    if(xCoord%3==2)
    {
      colStart = xCoord-2; 
      colEnd = xCoord; 
    }
    
    /* get the positions of the rows in the same cell as the yCoord */
    if(yCoord%3==0)
    {
      rowStart = yCoord; 
      rowEnd = yCoord+2; 
    }
    if(yCoord%3==1)
    {
      rowStart = yCoord-1; 
      rowEnd = yCoord+1; 
    }
    if(yCoord%3==2)
    {
      rowStart = yCoord-2;  
      rowEnd = yCoord; 
    }   
    // check if there is the same number in the same cell
    for(int n=rowStart; n<=rowEnd; n++)
    {
      for(int j=colStart; j<=colEnd; j++)
      {
        if(p1[n][j]==num && yCoord!=n && xCoord!=j)
        {
          cout<<"Uh Oh! You have a number in the exact same cell!"<<endl;
          lose=true; 
        }
      }
    }
    //check if there is the same number in the same row/column 
    for(int i=0; i<9; i++) //go through the array 
    {
      //same row 
      if(i!=xCoord)
      {
        if(p1[yCoord][i]==num)    
        {
          cout<<"Uh Oh! You have a number in the exact same row! "<<endl; 
          lose=true; 
        }
      }
      //same column 
      if(i!=yCoord)
      {
        if(p1[i][xCoord]==num)
        {
          lose=true; 
          cout<<"Uh Oh! You have a number in the exact same column! "<<endl;   
        }        
      }
    }
    //if the lose value is true, exit the loop! 
    if(lose==true)
    {
      displayBoard(ogBoard,p1); 
      cout<<"You've lost!"<<endl; 
      break; 
    }
    
    //Check if the board is filled yet 
    for(int y=0; y<9; y++)
    {
      for(int z=0; z<9; z++) 
      {
        if(p1[y][z]==0)
        {
          win=false;
          boardFilled=false; 
          break; 
        }
        else 
          boardFilled=true; 
      }
      //exit this loop if board is not filled 
      if(boardFilled==false)
      {
        break;
      }
    }

    //if the board is filled and the player has not lost, set win to true
    if(boardFilled==true && lose==false)
    {
      win=true; 
      cout<<"Congrats! You have won!"<<endl; 
    }
      
  }

   
}
