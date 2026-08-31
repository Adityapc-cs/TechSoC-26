#include <iostream>
#include <string.h>
using namespace std;


void Generate_Normal(int R, int C , int G);

int main()
{
    int Rows,Columns,Gens;
    cout<<"Enter the grid dimensions Rows and Columns respectively: \n";
    cin>>Rows>>Columns;
    cout<<"\nEnter the number of generations to simulate: \n";
    cin>>Gens;
    
    Generate_Normal(Rows , Columns , Gens);
}

void Generate_Normal(int R, int C , int G)
{
    cout<<"\n* = Dead , # = Alive \nEnter the characters * and # for each row one by one\n";
    char Grid[R][C];
    int InitialPopulation = 0;
    
    char Temp[R][C];
    char Temp1[R][C];

    
    for(int i=0; i<R ; i++)
    {
        cout<<"Row "<<i+1<<endl;
        for(int j=0; j<C ; j++)
        {
            cin>>Grid[i][j];
            if(Grid[i][j] == '#')
            {
                InitialPopulation++;
            }
        }
    }
    
    memcpy(Temp , Grid , sizeof(Grid));
    
    int MaxPopulation = InitialPopulation;
    
    for(int i=0 ; i<G ;i++)
    {
        for(int i =0; i<R ; i++)
        {
            for(int j=0; j<C ; j++)
            {
                int Alive = 0;
                int Dead = 0;
                
                if(i-1<0 || Temp[i-1][j]=='*')                                  //1
                {
                    Dead++;
                }
                else
                {
                    Alive++;
                }  
                
                if(i+1>=R || Temp[i+1][j]=='*')                                 //2
                {
                    Dead++;
                }
                else
                {
                    Alive++;
                }
                
                if(j-1<0 || Temp[i][j-1]=='*')                                  //3
                {
                    Dead++;
                }
                else
                {
                    Alive++;
                }
                
                if(j+1>=C || Temp[i][j+1]=='*')                                 //4
                {
                    Dead++;
                }
                else
                {
                    Alive++;
                }
                 
                if(i-1<0 || j-1<0 || Temp[i-1][j-1]=='*')                       //5
                {
                    Dead++;
                }
                else
                {
                    Alive++;
                }
                
                if(i-1<0 || j+1>=C || Temp[i-1][j+1]=='*')                      //6
                {
                    Dead++;
                }
                else
                {
                    Alive++;
                }
                
                if(i+1>=R || j-1<0 || Temp[i+1][j-1]=='*')                      //7
                {
                    Dead++;
                }
                else
                {
                    Alive++;
                }
                
                if(i+1>=R || j+1>=C || Temp[i+1][j+1]=='*')                      //8
                {
                    Dead++;
                }
                else
                {
                    Alive++;
                }
                
                
                if(Temp[i][j] == '#')
                    {
                        if(Alive<2)
                        {
                            Temp1[i][j] = '*';
                        }
                        else if(Alive>3)
                        {
                            Temp1[i][j] = '*';
                        }
                        else
                        {
                            Temp1[i][j] = '#';
                        }
                    }
                else
                {
                    if(Alive == 3)
                    {
                        Temp1[i][j] = '#';
                    }
                    else
                    {
                        Temp1[i][j] = '*';
                    }
                }
                
            }
        }
        int TempPopulation = 0;
        for(int i=0; i<R ; i++)
        {
            for(int j=0; j<C ; j++)
            {
                if(Temp1[i][j] == '#')
                {
                    TempPopulation++;
                }
            }
        }    
        if(TempPopulation>MaxPopulation)
        {
            MaxPopulation = TempPopulation;
        }
        
        memcpy(Temp , Temp1 , sizeof(Temp1));
    }        

    int FinalPopulation = 0;

    for(int i=0; i<R ; i++)
    {
        for(int j=0; j<C ; j++)
        {
            if(Temp[i][j] == '#')
            {
                FinalPopulation++;
            }
        }
    }
    
    cout<<"Initial Population = "<<InitialPopulation<<endl;
    cout<<"Final Population = "<<FinalPopulation<<endl;
    cout<<"Maximum Population = "<<MaxPopulation<<endl;
    cout<<endl;
    
    for(int i=0; i<R ; i++)
    {
        for(int j=0; j<C ; j++)
        {    
            cout<<Temp[i][j]<<" ";
        }
        cout<<endl;
    }    

}