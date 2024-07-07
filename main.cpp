#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

// letting the array size be a varible as feed by the input
int main(){
    //manually inputing the grid
    int x=15;
    int y=12;
    int size=x*y;
    // ! x -->
    // ! y  V
    int sheet[y][x][3]={0};
    int temprary[size]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
                        0,0,1,0,1,1,0,0,1,1,0,1,1,0,0,
                        0,0,1,1,1,0,0,0,0,1,0,1,1,5,0,
                        0,0,0,1,0,1,0,1,0,1,0,0,1,0,0,
                        0,1,1,1,0,1,1,1,0,1,1,0,1,0,0,
                        0,0,0,1,1,1,0,1,0,0,1,0,1,1,0,
                        0,1,0,1,0,0,0,1,1,1,1,1,0,1,0,
                        0,1,1,1,1,1,0,1,0,1,0,1,0,1,0,
                        0,0,0,1,0,1,0,0,0,1,0,1,1,1,0,
                        0,3,1,1,0,0,0,1,1,1,0,1,0,1,0,
                        0,1,0,1,1,1,0,1,0,1,0,1,1,1,0,
                        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    int num=0;
    for(int i=0;i<y;i++){
        for(int j=0;j<x;j++){
            num=x*i+j;
            int tem=temprary[num];
            sheet[i][j][0]=temprary[num];
            // cout<<sheet[i][j][0];
            // cout<<endl;
        }
    }

    // for(int i=0;i<y;i++){
    //     for(int j=0;j<x;j++){
    //         if(sheet[i][j][0]==5){
    //             cout<<"its here: "<<i<<" "<<j<<endl;
    //         }
    //     }
    // }

    // for(int i=0;i<y;i++){
    //     for(int j=0;j<x;j++){
    //         cout<<sheet[i][j][0]<<" ";
    //     }
    //     cout<<endl;
    // }

    // cout<<endl;
    // cout<<sheet[2][13][0]<<endl;
    // cout<<sheet[13][2][0]<<endl;
    // cout<<endl;  

    // cout<<"type of values of grids one by one as 0 or 1"<<endl;
    // // * taking input values
    // for(int i=1;i<=10;i++){
    //     for(int j=1;j<=10;j++){
    //         cin>>sheet[i][j][0];
    //     }
    // }
    /*
    * this code for manual input after running the program 
    // * inputing the block, path, start, end or void as a porperty.
    int inputs=x*y;
    int tempx=1;
    int tempy=1;
    while(inputs){
        int temp;
        cin>>temp;
        if(temp==0){
            sheet[tempx][tempy][0]=0;
            tempy++;
            inputs--;
        }else if(temp==1){
            sheet[tempx][tempy][0]=1;
            tempy++;
            inputs--;
        }else if(temp==2){
            sheet[tempx][tempy][0]=2;
            tempy++;
            inputs--;
        }else if(temp==3){
            sheet[tempx][tempy][0]=3;
            tempy++;
            inputs--;
        }else if(temp==5){
            sheet[tempx][tempy][0]=5;
            tempy++;
            inputs--;
        }else {
            cout<<"enter a valid input below \n";
        }
        if(tempy==y+1){
            tempx++;
            tempy=1;
        }
    }
    for(int i=0;i<x+1;i++){
        sheet[i][0][0]=0;
    }
    
    for(int i=0;i<y+1;i++){
        sheet[0][i][0]=0;
    }
    
    for(int i=0;i<x+2;i++){
        cout<<sheet[i][0][0]<<" "<<sheet[i][1][0]<<" "<<
        sheet[i][2][0]<<" "<<sheet[i][3][0]<<" "<<sheet[i][4][0]<<" ";
        cout<<endl;
    }
    */

   // ! setup      
   int current_num=1;
   for(int i=0;i<y;i++){
        for(int j=0;j<x;j++){
            if(sheet[i][j][0]==3){
                sheet[i][j][1]=1;
            }else{
                sheet[i][j][1]=0;
            }
        }
    }

    
    // * traversal
    int currenty=0;
    int currentx=0; 
    int steps =size; 
    int complete=1;
    while(complete&&steps){
        for(int i=0;i<y;i++){
            for(int j=0;j<x;j++){
                if(sheet[currenty][currentx][0]==5){
                    complete=0;
                    break;
                }else if(sheet[i][j][1]==current_num){
                    if((sheet[i+1][j][0]==1||sheet[i+1][j][0]==5)&&sheet[i+1][j][2]==0){
                        sheet[i+1][j][1]=current_num+1;
                        sheet[i][j][2]=1;
                        currenty=i+1;
                        currentx=j;
                        if(sheet[i+1][j][0]==5){
                            complete=0;
                            break;
                        }
                    } 
                    if((sheet[i][j+1][0]==1||sheet[i][j+1][0]==5)&&sheet[i][j+1][2]==0){
                        sheet[i][j+1][1]=current_num+1;
                        sheet[i][j][2]=1;
                        currenty=i;
                        currentx=j+1;
                        if(sheet[i][j+1][0]==5){
                            complete=0;
                            break;
                        }
                    }
                    if((sheet[i-1][j][0]==1||sheet[i-1][j][0]==5)&&sheet[i-1][j][2]==0){
                        sheet[i-1][j][1]=current_num+1;
                        sheet[i][j][2]=1;
                        currenty=i-1;
                        currentx=j;
                        if(sheet[i-1][j][0]==5){
                            complete=0;
                            break;
                        }
                    }
                    if((sheet[i][j-1][0]==1||sheet[i][j-1][0]==5)&&sheet[i][j-1][2]==0){
                        sheet[i][j-1][1]=current_num+1;
                        sheet[i][j][2]=1;
                        currenty=i;
                        currentx=j-1;
                        if(sheet[i][j-1][0]==5){
                            complete=0;
                            break;
                        }
                    }
                    // for(int i=0;i<y;i++){
                    //     for(int j=0;j<x;j++){
                    //         cout<<sheet[i][j][1]<<" ";
                    //     }
                    //     cout<<endl;
                    // }
                }
            }
        }
        current_num++;
        steps--;
        // cout<<size-steps<<endl;
    }
   
   // *displaying the array.
    for(int i=0;i<y;i++){
        for(int j=0;j<x;j++){
            cout<<sheet[i][j][0]<<" ";
        }
        cout<<endl;
    }
    cout<<"Number of Steps: "<<size-steps<<endl;
    // cout<<sheet[2][10][0]<<endl;
    // cout<<sheet[10][2][0]<<endl;
}
