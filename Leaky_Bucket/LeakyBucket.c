#include<stdio.h>
#include<stdlib.h>

void leaky_bucket(int bucket_capacity, int leak_rate, int num_packets, int packets[]) {
    int bucket = 0; 

    printf("Time\tIncoming\tBucket\tLeaked\tRemaining\n");
    for (int i = 0; i < num_packets; i++) {
        printf("%d%10d     ", i + 1, packets[i]);

       
        bucket += packets[i];
        if (bucket > bucket_capacity) {
            printf("%10d(Overflowed, Dropped %d)", bucket_capacity, bucket - bucket_capacity);
            bucket = bucket_capacity; // Discard excess packets
        } else {
            printf("%10d", bucket);
        }

        // Leak out packets at the constant rate
        int leaked = (bucket >= leak_rate) ? leak_rate : bucket;
        bucket -= leaked;

        printf("%10d%10d\n", leaked, bucket);
    }

    // Empty the bucket after all packets are processed
    int time = num_packets + 1;
    while (bucket > 0) {
        int leaked = (bucket >= leak_rate) ? leak_rate : bucket;
        printf("%d%10d     %10d%10d%10d\n", time,0,bucket, leaked, bucket - leaked);
        bucket -= leaked;
        time++;
    }
}
void main(){
    int bucket_capacity, leak_rate,num_packs;
    printf("Enter bucket capacity: ");
    scanf("%d",&bucket_capacity);
    printf("Enter leak rate: ");
    scanf("%d",&leak_rate);
    printf("Enter num_packs: ");
    scanf("%d",&num_packs);
    int packets[num_packs];
    printf("Enter the size of each incoming packet:\n");
    for(int i = 0 ; i<num_packs ; i++){
        scanf("%d",&packets[i]);
    }
    printf("Leaky bucket simulation:\n");
    leaky_bucket(bucket_capacity,leak_rate,num_packs,packets);
}