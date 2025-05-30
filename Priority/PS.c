#include<stdio.h>
#include<conio.h>
#define max 30

void main(){
    int i,j, n,t,pos;
    int burst_time[max], waiting_time[max], priority[max], total_arrival_time[max];
    float average_waiting_time =0, atat=0;

    printf("Enter the number process");
    scanf("%d", &n);
    printf("Enter the burst time of the process");
    for(i=0;i<n;i++){
        scanf("%d",&burst_time[i]);
    }

    printf("Enter the priority of the process");
    for(i=0;i<n;i++){
        scanf("%d",&priority[i]);
    }

    for(i=0;i<n;i++){
        pos=i;
        for(j=i+1;j<n; j++){
            if(priority[j]<priority[pos]){
                pos=j;
            }
        }
        t=priority[i];
        priority[i]=priority[pos];
        priority[pos]= t;

        t=burst_time[i];
        burst_time[i]= burst_time[pos];
        burst_time[pos]=t;
    }

    waiting_time[0]=0;
    printf("process\tbursts time\tpriority\twaiting time\tturnaround time\n");
    for(i=0;i<n;i++){
        waiting_time[i]=0;
        total_arrival_time[i]=0;
        for (j=0;j<i; j++){
            waiting_time[i]=waiting_time[i]+burst_time[j];
        }
        total_arrival_time[i]=waiting_time[i]+burst_time[i];
        average_waiting_time=average_waiting_time+waiting_time[i];
        atat=atat+total_arrival_time[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n",i+1,burst_time[i],priority[i],waiting_time[i],total_arrival_time[i]);  
    }
    average_waiting_time =average_waiting_time/n;
    atat=atat/n;
    printf("Average waiting time=%f\n", average_waiting_time);
    printf("Average turn around time=%f",atat);
    getch();
}