#include <iostream>
using namespace std;
#include <math.h>
struct stack
{
   int curent_x=0;
   int curent_y=0;
   int previous_x=0,previous_y=0;
};
// w,x,y,z function use to change the rotaion of the robot 
char  w(int a,int& x,int& y)
{
    if(a==2)
    {
    y++;
    return 'w';
    }
    else if(a==0)
    {
       x--;
       // turn left
       return 'x';
    }
    else if(a==1)
     {
       x++;
       // turn right 
       return 'y';
    }
    return 'y';
}
char x(int a,int& x,int& y)
{
    if(a==2)
    {
    x--;
    return 'x';
    }
    else if(a==0)
    {
       y--;
        // turn left
       return 'z';
    }
    else if(a==1)
     {
       y++;
         // turn right 
       return 'w';
    }
    return 'y';
}
char y(int a,int& x,int& y)
{
    if(a==2)
    {
    x++;
    return 'y';
    }
    else if(a==0)
    {
       y++;
        // turn left
       return 'w';
    }
    else if(a==1)
     {
       y--;
         // turn right 
       return 'z';
    }
    return 'y';
}
char z(int a,int& x,int& y)
{
     if(a==2)
    {
    y--;
    return 'z';
    }
    else if(a==0)
    {
       x++;
        // turn left
       return 'y';
    }
    else if(a==1)
     {
       x--;
         // turn right 
       return 'x';
    }
    return 'y';
}
void Rotation(char& fnx,int i,int& x1,int& y1) // change rotation of the robo
{
    switch(fnx)
    {
        case 'w':
        fnx= w(i,x1,y1);
        break;
    
        case 'x':
        fnx= x(i,x1,y1);
        break;
                
        case 'y':
        fnx= y(i,x1,y1);
        break;
                
        case 'z':
        fnx= z(i,x1,y1);
        break;
    }
}
char Multi_option(int x, int y, int x1,int y1,int **visited,struct stack arr[],int j,char* &st,int &string_index,int &count,char& key)//check the index where multion options are available 
{
    cout<<"j= "<<j<<endl;
    for(int i=0;i<j;i++)
    {
        if(arr[i].curent_x==x && arr[i].curent_y==y)
        {
            visited[arr[i].previous_x][arr[i].previous_y]=0;//set '0' when there is wrong way
            cout<<"visited "<<"[ "<<arr[i].previous_x<<" ]"<<" [ "<<arr[i].previous_y<<" ] "<<visited[arr[i].previous_x][arr[i].previous_y]<<endl;
             // delete string 
            
            int k=j-i;
            if(k>1)
            k=k-count;
             cout<<"k = "<<k<<" j = "<<j<<" i = "<<i<<endl;
             cout<<"string_index "<<string_index<<endl;
            int l=0;
            int c=0;
            while(l<k)
            {
                if(st[string_index-1]=='o')
                {
                    l++;
                    if(l<k)
                    {
                     string_index--;
                     count++;
                    }
                }
                else 
                {
                    c++;
                    string_index--;
                }
            }
            if(c>0)
            {
                key=st[string_index];
                st[string_index++]='1';
            }
            cout<<"string_index "<<string_index<<endl;
        }
    }
    if(visited[x1][y1]==0)
     {
        return 'f';
     }
    else return 't';
}
float distance(int x,int y,int X,int Y)// calculate distance
{
    float a=X-x;
    float b=Y-y;
    float c=pow(a,2)+pow(b,2);
    float ans=pow(c,0.5);
   return ans; 
}
void Add_string(int v,char* &st,int &string_index,char key)
{
    if(v==0)
    st[string_index++]='L';
    else if(v==1)
    st[string_index++]='R';
    else st[string_index++]='M';
    
    if(st[string_index-2]=='1')
    {
        if(key=='R')
        {
            if(st[string_index-1]=='M')
            {
                st[string_index-1]='L';
            }
            else if(st[string_index-1]=='R')
            {
                st[string_index-1]='M';
            }
            
        }
        else if(key=='L')
        {
            if(st[string_index-1]=='M')
            {
                st[string_index-1]='R';
            }
            else if(st[string_index-1]=='L')
            {
                st[string_index-1]='M';
            }
        }
        else 
        {
            if(st[string_index-1]=='L')
            {
                st[string_index-1]='R';
            }
            else if(st[string_index-1]=='R')
            {
                st[string_index-1]='L';
            }
        }
    }
}
bool find(struct stack arr[],int j,int x,int y)
{
  for(int i=0;i<j;i++)
  {
    if(arr[i].curent_x==x && arr[i].curent_y==y)
    return false;
  }
 return true;
}
void map(struct stack arr[],int &x,int &y,int &string_index,int **visited,char* &st,int X,int Y)
{
    char p,key;
    int v=0,j=0,count=0;  // j for as index of array arr (multiple option are avialabe),{v use for left ('0'),right('1'),forward('2')}
    char fnx='w';
    while(x!=X || y!=Y)
    {
        cout<<"( "<<x<<" , "<<y<<" )"<<endl;
        int xx=3;
        for(int i=0;i<string_index;i++)
        {
            cout<<st[i];
        }
        cout<<endl;
        
        // cout<<"string_index = "<<string_index<<endl;
        // int ld=3, rd=4,fd=3;
        int ld,rd,fd;
        cout<<"ld"<<"  rd"<<"  fd"<<endl;
        cin>>ld>>rd>>fd;
        visited[x][y]=1; // define '1' where the robo visite
        if (ld==xx && rd==xx && fd>xx ) 
            {
               Rotation(fnx,2,x,y);// 2 is for moving forword
                Add_string(2,st,string_index,key);
            }
        else if (ld>xx && rd==xx && fd==xx )
            {
              Rotation(fnx,0,x,y); // 0 is for moving left
               Add_string(0,st,string_index,key);
            }
        else if (ld==xx && rd>xx && fd==xx )
            {
              Rotation(fnx,1,x,y);// 1 is for moving right 
               Add_string(1,st,string_index,key);
            }
        else if (ld>xx && rd>xx && fd==xx )
            {
                if(find(arr,j,x,y)) // push (x,y) in arr (array) not more than one time   
                {
                    arr[j].curent_x=x;
                    arr[j].curent_y=y;
                    st[string_index++]='o';
                     j++;
                }
                  char fnx1=fnx;
                  int x1=x,y1=y;
                  int x2=x,y2=y;
                Rotation(fnx1,0,x1,y1);
                fnx1=fnx;
                Rotation(fnx1,1,x2,y2);
                float Left_distance=distance(x1,y1,X,Y);// checking distance for left option
                float Right_distance=distance(x2,y2,X,Y); // checking distance for right option
                
                if(visited[x1][y1]==1 && visited[x2][x2]==1) // if left and right visited then go away from the destination
                {    
                     int temp=Left_distance;
                     Left_distance=Right_distance;
                     Right_distance=temp;
                }
                
                if(Left_distance>Right_distance)// if right distance is is smallar than left then go to right side
                {
                     p=Multi_option(x,y,x2,y2,visited,arr,j,st,string_index,count,key);// check the way it is right or wrong like if there is '0' so dont go there ,go to other option
                     if(p=='t')
                      v=1;
                     else v=0;
                }
                else 
                {
                   p=Multi_option(x,y,x1,y1,visited,arr,j,st,string_index,count,key);// check the way it is right or wrong like if there is '0' so dont go there ,go to other option
                   if(p=='t')
                   v=0;
                   else v=1;
                }
               
                    Rotation(fnx,v,x,y);
                    arr[j-1].previous_x=x;
                    arr[j-1].previous_y=y;
                    Add_string( v,st,string_index,key);
              
            }
        else if (ld>xx && rd==xx && fd>xx )
            {
                if(find(arr,j,x,y))  // push (x,y) in arr (array) not more than one time  
                {
                    arr[j].curent_x=x;
                    arr[j].curent_y=y;
                    st[string_index++]='o';
                    j++;
                }
                 char fnx1=fnx;
                 int x1=x,y1=y;
                 int x2=x,y2=y;    
               Rotation(fnx1,0,x1,y1);
               fnx1=fnx;
              Rotation(fnx1,2,x2,y2);
                float Left_distance=distance(x1,y1,X,Y);
                float Forward_distance=distance(x2,y2,X,Y);
                if(visited[x1][y1]==1 && visited[x2][x2]==1) // if left and forward index visited then go away from the destination(8,8)
                {
                      int temp=Left_distance;
                     Left_distance=Forward_distance;
                     Forward_distance=temp;
                }
                if(Left_distance>Forward_distance)// if forward distance is is smallar than left then go to forward side
                {
                     p=Multi_option(x,y,x2,y2,visited,arr,j,st,string_index,count,key);// check the way it is right or wrong like if there is '0' so dont go there ,go to other option
                     if(p=='t')
                     v=2;
                     else v=0;
                }
                else 
                {
                   p=Multi_option(x,y,x1,y1,visited,arr,j,st,string_index,count,key);// check the way it is right or wrong like if there is '0' so dont go there ,go to other option
                   if(p=='t')
                   v=0;
                   else v=2;
                }
              
               Rotation(fnx,v,x,y);
               arr[j-1].previous_x=x;
               arr[j-1].previous_y=y;
                Add_string( v,st,string_index,key);
            }
        else if (ld==xx && rd>xx && fd>xx )
            {
                if(find(arr,j,x,y)) // push (x,y) in arr (array) not more than one time   
                {
                    arr[j].curent_x=x;
                    arr[j].curent_y=y;
                     st[string_index++]='o';
                    j++;
                }
                 char fnx1=fnx;
                 int x1=x,y1=y;
                 int x2=x,y2=y;
               Rotation(fnx1,1,x1,y1);
               fnx1=fnx;
               Rotation(fnx1,2,x2,y2);
                float Right_distance=distance(x1,y1,X,Y);
                float Forward_distance=distance(x2,y2,X,Y);
               if( visited[x1][y1]==1 && visited[x2][x2]==1) // if Right and forward index visited then go away from the destination(8,8)
                {
                     int temp=Right_distance;
                     Right_distance=Forward_distance;
                     Forward_distance=temp;
                    
                }
                if(Right_distance>Forward_distance)// if Forward distance is is smallar than Right then go to Forward side
                {
                     p=Multi_option(x,y,x2,y2,visited,arr,j,st,string_index,count,key);// check the way it is right or wrong like if there is '0' so dont go there ,go to other option
                     if(p=='t')
                     v=2;
                     else v=1;
                }
                else 
                {
                   p=Multi_option(x,y,x1,y1,visited,arr,j,st,string_index,count,key);// check the way it is right or wrong like if there is '0' so dont go there ,go to other option
                   if(p=='t')
                   v=1;
                   else v=2;
                }
               Rotation(fnx,v,x,y);
              arr[j-1].previous_x=x;
              arr[j-1].previous_y=y;
               Add_string( v,st,string_index,key);
            }
        else if (ld>xx && rd>xx && fd>xx )
            {
               if(find(arr,j,x,y)) // push (x,y) in arr (array) not more than one time   
                {
                    arr[j].curent_x=x;
                    arr[j].curent_y=y;
                     st[string_index++]='o';
                    j++;
                }
                
                int x1=x,y1=y;
                int x2=x,y2=y;
                int x3=x,y3=y;
              char fnx1=fnx;
              Rotation(fnx1,0,x1,y1);
              fnx1=fnx;
              Rotation(fnx1,1,x2,y2);
              fnx1=fnx;
              Rotation(fnx1,2,x3,y3);
              float Left_distance=distance(x1,y1,X,Y);
              float Right_distance=distance(x2,y2,X,Y);
              float Forward_distance=distance(x3,y3,X,Y);
                if(Left_distance<Right_distance && Left_distance<Forward_distance)//if left distance is smaller then other then go left
                {
                     p=Multi_option(x,y,x1,y1,visited,arr,j,st,string_index,count,key);// check the way it is right or wrong like if there is '0' so dont go there ,go to other option
                    if(p=='t')
                     v=0;
                     else 
                     {
                         if(Right_distance<Forward_distance)
                         {
                             p=Multi_option(x,y,x1,y1,visited,arr,j,st,string_index,count,key);
                             if(p=='t')
                              v=1;
                              else v=2;
                         }
                        
                         
                     }
                }
                else if(Right_distance<Left_distance && Right_distance<Forward_distance)//if right distance is smaller then other then go right
                {
                     p=Multi_option(x,y,x2,y2,visited,arr,j,st,string_index,count,key);// check the way it is right or wrong like if there is '0' so dont go there ,go to other option
                     if(p=='t')
                     v=1;
                     else 
                     {
                         if(Left_distance<Forward_distance)
                         {
                             p=Multi_option(x,y,x1,y1,visited,arr,j,st,string_index,count,key);
                             if(p=='t')
                              v=0;
                              else v=2;
                         }
                     }
                }     
                else    //if forward distance is smaller then other then go forward
                {
                    p=Multi_option(x,y,x3,y3,visited,arr,j,st,string_index,count,key);// check the way it is right or wrong like if there is '0' so dont go there ,go to other option
                    if(p=='t')
                    v=2;
                    else 
                     {
                         if(Left_distance<Right_distance)
                         {
                             p=Multi_option(x,y,x1,y1,visited,arr,j,st,string_index,count,key);
                             if(p=='t')
                              v=0;
                              else v=1;
                         }
                     }
                }
             Rotation(fnx,v,x,y);
             arr[j-1].previous_x=x;
             arr[j-1].previous_y=y;
             Add_string( v,st,string_index,key);
            }
        else if (ld==xx && rd==xx && fd==xx )
            {
                int x1,y1;
               Rotation(fnx,0,x1,y1);
               Rotation(fnx,0,x1,y1);
               // turn left
               //turn left 
            }
            
    //   move 
    }
}
int main()
{
    struct stack arr[30]; // this aaray is creating for where the multiple option are available
    int x=13,y=13; // starting index of the robo
    char* st= new char[150];
    int string_index=0;
    
    int **visited = new int*[16]; // store visited index
    for(int i=0;i<16;i++){
        visited[i]=new int[16];
    } 
    for(int i=0;i<16;i++)
    {
      for(int j=0;j<16;j++)
        {
            visited[i][j]=2;
        } 
    }
    map(arr,x,y,string_index,visited,st,8,8);
    
    
    char* st1= new char[150];
    int string_index1=0;
    map(arr,x,y,string_index1,visited,st1,0,0);
    
    int k=string_index1;
    string st2[k]; //revers string for come back to starting point 
     for(int i=0;i<string_index1;i++)
        {
            if(st1[k-2]=='L')
            {
                st2[i]='R'; 
            }
            else if(st1[k-2]=='R')
            {
                st2[i]='L';
            }
            else 
            {
                st2[i]=st1[k-2];
            }
            k--;
        }
    //     cout<<"revers  ....."<<string_index<<endl;
    //     for(int i=0;i<string_index;i++)
    //     {
    //         cout<<st1[i];
    //     }
    //     cout<<endl;
    if(x==8 && y==8){
        // cout<<st<<endl;
        cout<<"Pohach Gaya Saale "<<endl;
    }
 return 0;
}














