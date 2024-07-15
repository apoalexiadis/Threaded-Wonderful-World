#include <stdio.h>
#include <pthread.h>

// Χρησιμοποιούμε condition variables για τον συγχρονισμό των threads για τα εξής πλεονεκτήματα:
////Ευκολότερη Διαχείριση Σειριακής Εκτέλεσης: Οι condition variables επιτρέπουν στα threads να περιμένουν συγκεκριμένες συνθήκες πριν συνεχίσουν, κάτι που διευκολύνει την δημιουργία μιας αλληλουχίας εκτέλεσης μεταξύ των threads.
//Αναμενόμενη Συμπεριφορά: Όταν χρησιμοποιούμε condition variables, η συμπεριφορά του προγράμματος είναι πιο προβλέψιμη και ελεγχόμενη, καθώς τα threads ενεργοποιούνται μόνο όταν πληρούνται οι κατάλληλες συνθήκες.
//Καλύτερη Κατανοησιμότητα: Η χρήση condition variables κάνει τον κώδικα πιο κατανοητό όσον αφορά τη σειρά εκτέλεσης και τις αλληλεξαρτήσεις μεταξύ των threads.


// Mutexes για τις condition variables
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

// Condition variables για κάθε συνθήκη
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;

// Κοινό flag για την κατάσταση των threads
int flag = 0;

// Αρχικοποίηση των συναρτήσεων
void* printWhatA(void* );
void* printWonderful(void* );
void* printWorld(void* );

int main() {
    pthread_t thread1, thread2, thread3;

    // Δημιουργία των threads
    pthread_create(&thread1, NULL, printWhatA, NULL);
    pthread_create(&thread2, NULL, printWonderful, NULL);
    pthread_create(&thread3, NULL, printWorld, NULL);

    // Αναμονή τερματισμού των threads
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    return 0;
}

// Λειτουργία ενός thread για εκτύπωση "What A "
void* printWhatA(void* arg) {
    
	while (1) {
    	
        // Κλείδωμα του mutex1 για προστασία του κοινού flag και της condition variable cond1
        pthread_mutex_lock(&mutex1);
        
        // Το thread περιμένει μέχρι να είναι έτοιμο να εκτελέσει το τμήμα κώδικα του
        while (flag != 0) {
            pthread_cond_wait(&cond1, &mutex1); // Απελευθέρωση του mutex1 κατά την αναμονή
        }
        
        // Εκτύπωση του τμήματος "What A "
        printf("What A ");
        
        // Αλλαγή του flag για την επόμενη κατάσταση του προγράμματος
        flag = 1;
        
        // Ειδοποίηση του επόμενου thread (printWonderful) να εκτελέσει
        pthread_cond_signal(&cond2);
        
        // Απελευθέρωση του mutex1 μετά την ολοκλήρωση του τμήματος κώδικα
        pthread_mutex_unlock(&mutex1);
    }
       
    return NULL;
}

// Λειτουργία ενός thread για εκτύπωση "Wonderful "
void* printWonderful(void* arg) {
    while (1) {
        // Κλείδωμα του mutex2 για προστασία του κοινού flag και της condition variable cond2
        pthread_mutex_lock(&mutex2);
        
        // Το thread περιμένει μέχρι να είναι έτοιμο να εκτελέσει το τμήμα κώδικα του
        while (flag != 1) {
            pthread_cond_wait(&cond2, &mutex2); // Απελευθέρωση του mutex2 κατά την αναμονή
        }
        
        // Εκτύπωση του τμήματος "Wonderful "
        printf("Wonderful ");
        
        // Αλλαγή του flag για την επόμενη κατάσταση του προγράμματος
        flag = 2;
        
        // Ειδοποίηση του επόμενου thread (printWorld) να εκτελέσει
        pthread_cond_signal(&cond3);
        
        // Απελευθέρωση του mutex2 μετά την ολοκλήρωση του τμήματος κώδικα
        pthread_mutex_unlock(&mutex2);
    }
    return NULL;
}

// Λειτουργία ενός thread για εκτύπωση "World! "
void* printWorld(void* arg) {
    while (1) {
        // Κλείδωμα του mutex3 για προστασία του κοινού flag και της condition variable cond3
        pthread_mutex_lock(&mutex3);
        
        // Το thread περιμένει μέχρι να είναι έτοιμο να εκτελέσει το τμήμα κώδικα του
        while (flag != 2) {
            pthread_cond_wait(&cond3, &mutex3); // Απελευθέρωση του mutex3 κατά την αναμονή
        }
        
        // Εκτύπωση του τμήματος "World! "
        printf("World! ");
        
        // Αλλαγή του flag για την επόμενη κατάσταση του προγράμματος
        flag = 0;
        
        // Ειδοποίηση του επόμενου thread (printWhatA) να εκτελέσει
        pthread_cond_signal(&cond1);
        
        // Απελευθέρωση του mutex3 μετά την ολοκλήρωση του τμήματος κώδικα
        pthread_mutex_unlock(&mutex3);
        
    }
    return NULL;
}

