#include <iostream>
#include <cstdlib>
#include <ctime>  

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));

    int number_to_guess = rand() % 100 + 1;
    int user_guess = 0;

    cout << "Welcome to the Number Guessing Game!" << endl;
    cout << "I'm thinking of a number between 1 and 100." << endl;

    while (user_guess != number_to_guess) {
        cout << "Enter your guess: ";
        cin >> user_guess;

        if (user_guess < number_to_guess) {
            cout << "Too low! Try again." << endl;
        } else if (user_guess > number_to_guess) {
            cout << "Too high! Try again." << endl;
        } else {
            cout << "Congratulations! You guessed the correct number: " << number_to_guess << endl;
        }
    }

    return 0;
}
