#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Bank account structure
typedef struct {
    int balance;
    pthread_mutex_t lock;
} Account;

// Function to perform a transaction
void* performTransaction(void* data) {
    Account* account = (Account*)data;
    int amount = 100; // Amount to withdraw or deposit

    // Acquire the lock
    pthread_mutex_lock(&account->lock);

    // Simulate a delay
    for (int i = 0; i < 10000; i++) {
        // Perform the transaction
        account->balance += amount;
    }


    // Release the lock
    pthread_mutex_unlock(&account->lock);

    return NULL;
}

int main() {
    // Create a bank account
    Account account;
    account.balance = 0;
    pthread_mutex_init(&account.lock, NULL);

    // Create two threads
    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, performTransaction, &account);
    pthread_create(&thread2, NULL, performTransaction, &account);

    // Wait for the threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print the final balance
    printf("Final balance: %d\n", account.balance);

    // Clean up
    pthread_mutex_destroy(&account.lock);

    return 0;
}