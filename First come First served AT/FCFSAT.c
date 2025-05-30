#include<stdio.h>
#include<conio.h>
#define max 30

void main(){
    int i, j,n;
    int burst[max], arrival_time[max],total_arrival_time[max], waiting_time[max],temp[max];
    float average_waiting_time=0, average_total_arriavl_time=0;


    printf("Enter the no of process ");
    scanf("%d", &n);

    printf("Enter the burst time of the process ");
    for(i=0;i<n;i++)
            scanf("%d", &burst[i]);


    printf("Enter the arrival time of the process");
    for(i =0;i<n;i++)
            scanf("%d", &arrival_time[i]);

    temp[0]= 0;
    printf("process\t burst time\t arrival time\t waiting time\t turnaround time\n");
    for(i=0 ; i<n ;i++){
            waiting_time[i]=0;
            total_arrival_time[i]= 0;
            temp[i+1]=temp[i]+burst[i];
            waiting_time[i] = temp[i]- arrival_time[i];
            total_arrival_time[i] = waiting_time[i]+burst[i];
            average_waiting_time = average_waiting_time+waiting_time[i];
            average_total_arriavl_time=average_total_arriavl_time+total_arrival_time[i];
            printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i+1,burst[i],arrival_time[i],waiting_time[i],total_arrival_time[i]);
    }

    average_waiting_time = average_waiting_time/n;
    average_total_arriavl_time/n;
    printf("\naverage waiting time = %f\n", average_waiting_time);
    printf("\naverage turnaround time =%f",average_total_arriavl_time);
    getch();
}
