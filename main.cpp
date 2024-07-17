// * 2d maze solver by Djikstra Algorighm for non weighted maze.
// * Author: Aditya

//adding necessary libraries
#include <stdio.h>
#include <bits/stdc++.h>
#include"CImg.h"
using namespace std;
using namespace cimg_library;

int main(){
    // taking the images as input.
    CImg<unsigned char> img("maze.jpg");
    CImg<unsigned int> *image=new CImg<unsigned int>("maze.jpg");

    // getting dimentions. 
    int w=(*image).width();
    int h=(*image).height();
    cout<<"Dimentions: "<<w<<" "<<h<<" "<<endl;

    // initializing variables and array.
    int x=w+2;
    int y=h+2;
    int sheet[x][y][4]={0};
    int size=x*y;

    // reading and saving maze data from image.
    for(int i=1;i<x;i++){
        for(int j=1;j<y;j++){
            if(img.atXY(j-1,i-1)>120){
                sheet[i][j][0]=1;
            }else{
                sheet[i][j][0]=0;
            }
        }
    }

    // setting starting and end points.
    sheet[w][0+1][0]=3;
    sheet[0+1][h][0]=5;

    // adding a 1 length wide block to reduce computation cost.
    for(int i=0;i<x;i++){
        sheet[0][i][0]=0;
        sheet[y-1][i][0]=0;
    }
    for(int i=0;i<y;i++){
        sheet[i][0][0]=0;
        sheet[i][x-1][0]=0;
    }

    // result display 
    int x5=10*x;
    int y5=10*y;
    CImg<unsigned char> vis(x5,y5,1,3);
    CImgDisplay draw_disp(vis,"shrotest path");
    vis.fill(0);

    // second display
    CImg<unsigned char> maze(x5,y5,1,3);
    CImgDisplay draw_disp2(maze,"shrotest path");
    maze.fill(0);

    // setting every block as not-visited.
    for(int i=0;i<y;i++){
        for(int j=0;j<x;j++){
            sheet[i][j][3]=0;
        }
    }

    // reading start and end point and setup.     
    int current_num=1;
    for(int i=0;i<y;i++){
        for(int j=0;j<x;j++){
            if(sheet[i][j][0]==3){
                sheet[i][j][1]=1;
                sheet[i][j][3]=1;
            }else{
                sheet[i][j][1]=0;
            }
            if(sheet[i][j][0]==5){
                sheet[i][j][3]=1;
            }
        }
    }
    
    // traversing the data to solve the algorithm.
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
                }
            }
        }
        current_num++;
        steps--;
    }

    // display number of steps.
    cout<<"Number of Steps: "<<size-steps<<endl;
    int run=size-steps;

    // starting a reverse traversal form end point to start point. 
    int finalx;
    int finaly;
    for(int i=0;i<y;i++){
        for(int j=0;j<x;j++){
            if(sheet[i][j][0]==5){
                finalx=j;
                finaly=i;
                break;
            }
        }
    }
    run++;
    currentx=finalx;
    currenty=finaly;
    int back[run][2];
    back[0][0]=currentx;
    back[0][1]=currenty;
    int count=1;

    // reverse traversal.
    for(int i=0;i<(size-steps-1);i++){
        if(sheet[currenty+1][currentx][1]==run-1){
            currenty=currenty+1;
            currentx=currentx;
            sheet[currenty][currentx][3]++;
            run--;
            back[count][0]=currentx;
            back[count][1]=currenty;
            count++;
            cout<<"down ";
        }else if(sheet[currenty-1][currentx][1]==run-1){
            currenty=currenty-1;
            currentx=currentx;
            sheet[currenty][currentx][3]++;
            run--;
            back[count][0]=currentx;
            back[count][1]=currenty;
            count++;
            cout<<"up ";
        }else if(sheet[currenty][currentx+1][1]==run-1){
            currenty=currenty;
            currentx=currentx+1;
            sheet[currenty][currentx][3]++;
            run--;
            back[count][0]=currentx;
            back[count][1]=currenty;
            count++;
            cout<<"right ";
        }else if(sheet[currenty][currentx-1][1]==run-1){
            currenty=currenty;
            currentx=currentx-1;
            sheet[currenty][currentx][3]++;
            run--;
            back[count][0]=currentx;
            back[count][1]=currenty;
            count++;
            cout<<"left ";
        }
    }
        cout<<endl;
    
    // constructing the result screens.
    int p=0;
    int q=0;
    for(int i=0;i<y;i++){
        for(int j=0;j<x;j++){
            if(sheet[i][j][3]!=0){
                for(int p=0;p<9;p++){
                    for(int q=0;q<9;q++){
                        vis(10*j+p,10*i+q,0,0)=255;
                        vis(10*j+p,10*i+q,0,1)=255;
                        vis(10*j+p,10*i+q,0,2)=255;
                    }
                }
                cout<<"  ";
            }else{
                for(int p=0;p<9;p++){
                    for(int q=0;q<9;q++){
                        vis(10*j+p,10*i+q,0,0)=100;
                        vis(10*j+p,10*i+q,0,1)=100;
                        vis(10*j+p,10*i+q,0,2)=100;
                    }
                }
                cout<<"█ ";
            }
        }
        cout<<endl;
    }

    p=0;
    q=0;
    for(int i=0;i<y;i++){
        for(int j=0;j<x;j++){
            if(sheet[i][j][0]==0){        
                for(int p=0;p<9;p++){
                    for(int q=0;q<9;q++){
                        maze(10*j+p,10*i+q,0,0)=0;
                        maze(10*j+p,10*i+q,0,1)=0;
                        maze(10*j+p,10*i+q,0,2)=0;
                    }
                }
            }else{
                for(int p=0;p<9;p++){
                    for(int q=0;q<9;q++){
                        maze(10*j+p,10*i+q,0,0)=255;
                        maze(10*j+p,10*i+q,0,1)=255;
                        maze(10*j+p,10*i+q,0,2)=255;
                    }
                }
            }
            if(sheet[i][j][3]!=0){
                for(int p=0;p<9;p++){
                    for(int q=0;q<9;q++){
                        maze(10*j+p,10*i+q,0,0)=250;
                        maze(10*j+p,10*i+q,0,1)=140;
                        maze(10*j+p,10*i+q,0,2)=0;
                    }
                }
            }
        }
    }

    // displaying the result screen.
    while (!draw_disp.is_closed()&&!draw_disp2.is_closed()) {
        vis.display(draw_disp);
        maze.display(draw_disp2);
    }
}