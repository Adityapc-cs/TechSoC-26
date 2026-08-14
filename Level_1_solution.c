#include <stdio.h>
#include <string.h>
int main()
{
 int C;
 int N;
 
 printf("Enter Max capacity: \n");
 scanf("%d",&C);
 printf("Enter number of containers: \n");
 scanf("%d",&N);
 printf("Enter weights of the containers one by one\n");
 
 float Weights[N];
 for(int i=0;i<N;i++)
 {
     scanf("%f",&Weights[i]);
 }
 
 float NetWeight=0;
 float HeaviestC=0;
 float LightestC=Weights[0];
 for(int i=0;i<N;i++)
 {
     NetWeight+=Weights[i];
     
     if(Weights[i]>=HeaviestC)
     {
        HeaviestC=Weights[i];
     }
     
     if(Weights[i]<=LightestC)
     {
        LightestC=Weights[i];
     }
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
 
}
