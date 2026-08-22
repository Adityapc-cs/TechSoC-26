#include <stdio.h>
#include <string.h>

void ShipMent()                                          //I made the entire code of L1 a fn so that it can be reused in L2 multi-processing shipment feature
{
 int C;
 int N;
 
 printf("\nEnter Max capacity: \n");
 scanf("%d",&C);
 printf("Enter number of containers: \n");
 scanf("%d",&N);
 printf("Enter weights of the containers one by one\n");
 
 float Weights[N];
 for(int i=0;i<N;i++)
 {
     scanf("%f",&Weights[i]);
 }
 
 float Original_Order[N];                                //I later in this code , arranged the initial array , which had ordered inputs , so later on i made this array.
  
 float NetWeight=0;
 float HeaviestC=0;
 float LightestC=Weights[0];
 for(int i=0;i<N;i++)                                    //This loop does 3 things- 
 {                                                       //1.Calculates Net Weight 
     NetWeight+=Weights[i];                              //2.Finds the heaviest and the lightest weights 
                                                         //3.Copies the Weights array into another array(reason is mentioned in the above comment)) 
     if(Weights[i]>=HeaviestC)
     {
        HeaviestC=Weights[i];
     }
     
     if(Weights[i]<=LightestC)
     {
        LightestC=Weights[i];
     }
     
     Original_Order[i]=Weights[i];
 }
 
 char Classification[25];                                
 if(NetWeight>=200)
 {
    strcpy(Classification,"Heavy");
 }
 else
 {
    strcpy(Classification,"Light");
 }
 
 printf("\n\n");
 printf("Total Shipment Weight   : %.2f\n",NetWeight);
 printf("Average Container Weight: %.2f\n\n",NetWeight/N);
 printf("Weights of:\n");
 printf("Heaviest Container: %.2f\n",HeaviestC);
 printf("Lightest Container: %.2f\n\n",LightestC);
 printf("Classification: %s\n",Classification);
 printf("Port Capacity: %d\n",C);
 if(NetWeight<=C)
 {
    printf("Status: Shipment can be unloaded.");
 }
 else
 {
    printf("Status: Shipment exceeds port capacity.");
 }
 
 
 printf("\n\nWeights of Containers in sorted order:\n");        //SORTING

    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N-1;j++)
        {
            if(Weights[j+1]<=Weights[j])
            {
                float temp=Weights[j];
                Weights[j]=Weights[j+1];
                Weights[j+1]=temp;
            }
            else
            {
                continue;
            }
        }
    }
    
    for(int i = 0; i<N ; i++)                                   //Printing the sorted array.
    {
        printf("%d. %.2f\n",i+1,Weights[i]);
    }
    
    
printf("\nContainer Weight Bar Chart:\n");                      //BAR CHART
for(int i=0; i<N; i++)
{
    int Stars=Weights[i]/5;
    printf("Container %d (%.0f) : ",i+1,Weights[i]);
   
    for(int j=0; j<Stars; j++)
    {
        printf("*");
    }
    printf("\n");
}
printf("\n(Each * represents 5 units)\n\n");

float ToSearch;                                                 //Search Feature
printf("Search container by weight?\n");
        char Response[25];
        scanf(" %s",&Response);
            if(strcmp(Response,"Yes")==0 || strcmp(Response,"yes")==0)
            {
                
                printf("Enter Weight:\n");
                scanf("%f",&ToSearch);
                for(int i=0;i<N;i++)
                {
                    if(Original_Order[i]==ToSearch)
                    {
                        printf("\nContainer Found!\nContainer %d has weight %.1f\n",i+1,Original_Order[i]);
                    }
                }
                
            }
            
int K;                                                 //Search Feature(kth heavy container)
printf("\nFind kth heavy container by weight?\n");
        char Answer[25];
        scanf(" %s",&Answer);
            if(strcmp(Answer,"Yes")==0 || strcmp(Answer,"yes")==0)
            {
                
                printf("Enter k:\n");
                scanf("%d",&K);
                
                
                        int index=K-1;
                        switch(K%10)
                        {
                        case 1:
                        
                            printf("The %dst heaviest container has weight: %.f\n",K,Weights[index]);
                            break;
                            
                        case 2:
                        
                            printf("The %dnd heaviest container has weight: %.f\n",K,Weights[index]);
                            break;
                            
                        case 3:
                        
                            printf("The %drd heaviest container has weight: %.f\n",K,Weights[index]);
                            break;
                            
                        default:
                        
                            printf("The %dth heaviest container has weight: %.f\n",K,Weights[index]);
                            break;
                        }
            
            }    
    
    printf("\n");        
}

int main()
{
    
    ShipMent();
    int counter=1;                                                //To keep track on number of ships processed.
    while(1)
    {
        printf("\nContinue?\n");
        char Response[25];
        scanf(" %s",&Response);
   
            if(strcmp(Response,"Yes")==0 || strcmp(Response,"yes")==0)
            {
                
                ShipMent();
                counter++;
            }
            else if(strcmp(Response,"No")==0 || strcmp(Response,"no")==0)
            {
                printf("\nTotal ships processed: %d\n",counter);
                break;
            }
            else
            {
                printf("Invalid response. Enter Yes or No.\n");
            }
        
    }
}

