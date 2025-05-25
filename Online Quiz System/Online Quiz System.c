#include <stdio.h>
#include <stdlib.h>

// Structure to store question, options, and correct answer
struct Question {
    char question[256];
    char optionA[50];
    char optionB[50];
    char optionC[50];
    char optionD[50];
    char correctAnswer;
};

void displayQuestion(struct Question q) {
    printf("\n%s\n", q.question);
    printf("A. %s\n", q.optionA);
    printf("B. %s\n", q.optionB);
    printf("C. %s\n", q.optionC);
    printf("D. %s\n", q.optionD);
    printf("Your Answer: ");
}

int main() {
    struct Question questions[5] = {
        {"What is the capital of France?", "Berlin", "Madrid", "Paris", "Rome", 'C'},
        {"Who is the CEO of Tesla?", "Jeff Bezos", "Elon Musk", "Bill Gates", "Mark Zuckerberg", 'B'},
        {"Which language is used for web development?", "C", "Python", "HTML", "Java", 'C'},
        {"What is the largest planet in our solar system?", "Earth", "Mars", "Jupiter", "Saturn", 'C'},
        {"Who wrote 'Romeo and Juliet'?", "Shakespeare", "Dickens", "Austen", "Hemingway", 'A'}
    };

    int score = 0;
    char answer;
    
    printf("------ Welcome to the Online Quiz System ------\n");
    printf("Please answer the following questions:\n");

    for (int i = 0; i < 5; i++) {
        displayQuestion(questions[i]);
        scanf(" %c", &answer);  // Read the user's answer (with a space to skip any buffer)
        
        // Check if the answer is correct
        if (answer == questions[i].correctAnswer) {
            printf("Correct Answer!\n");
            score++;
        } else {
            printf("Wrong Answer. The correct answer is %c.\n", questions[i].correctAnswer);
        }
    }

    printf("\nYour total score: %d out of 5\n", score);

    // Display the result
    if (score == 5) {
        printf("Congratulations! You scored a perfect score!\n");
    } else if (score >= 3) {
        printf("Good job! You scored well.\n");
    } else {
        printf("Better luck next time!\n");
    }

    return 0;
}
