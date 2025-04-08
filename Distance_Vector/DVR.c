#include<stdio.h>
#define max 1024
int cost[max][max],dist[max][max],nexthop[max][max];
int nodes;
void initialize(){
    for(int i = 0 ; i<nodes ; i++){
        for(int j = 0 ; j<nodes ; j++){
            dist[i][j] = cost[i][j];
            nexthop[i][j] = j;
        }
    }
}
void update(){
    int updated = 0;
    do{
        for(int i = 0 ; i< nodes ; i++){
            for(int j = 0 ; j< nodes ; j++){
                for(int k = 0 ; k<nodes ; k++){
                    if(dist[i][j]>dist[i][j]+dist[i][k]){
                        dist[i][j]=dist[i][j]+dist[i][k];
                        nexthop[i][j]=nexthop[i][k];
                        updated = 1;
                    }
                }
            }
        }
    }while(updated);
}
void display(){
    for(int i = 0 ; i< nodes ; i++){
        printf("Router %d Routing table \n",i+1);
        printf("Destination\tCost\tNext Hop\n");
        for(int j = 0 ; j<nodes ; j++){
            printf("%d\t\t%d\t\t%d\n",j+1,dist[i][j],nexthop[i][j]+1);
        }
    }
}
void main(){
    printf("Enter the number of nodes");
    scanf("%d",&nodes);
    printf("Enter the cost matrix\n");
    for(int i = 0 ; i< nodes ; i++){
        for(int j = 0 ; j<nodes ; j++){
           scanf("%d",&cost[i][j]);
           if(i==j){
            cost[i][j] = 0;
           }
        }
    }
    initialize();
    update();
    display();
    
}