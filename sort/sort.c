#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Function to generate random array and write to a file
void generate_test_case(const char *filename, int size) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d\n", rand() % 100); // Random numbers between 0 and 99
    }
    fclose(file);
}

int main() {
    generate_test_case("input1.txt", 10);  // Small test case
    generate_test_case("input2.txt", 100); // Larger test case
    generate_test_case("input3.txt", 1000); // Stress test
    printf("Test cases generated.\n");
    return 0;
}
