/*  Title: simplePokerGame.cpp
    Due Date: 01/29/2024
    Group 4:
        Jesus Ceron-Gonzalez
        Lukas Hammett
        Ismiel Higareda
        David Reyes
    Goal: 7. Handling Aces: 
        Modify the code to handle Aces properly, where they can be worth 1 or 11 points.
        The value should be chosen to benefit the player or dealer.
    Other Notable Changes:
        - Lukas: Used a constant DECK_SIZE and size(RANKS) instead of the numbers 52 and 13, respectively.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
const int DECK_SIZE = 52;
int DECK[DECK_SIZE];
int currentCardIndex = 0;

void initializeDeck() {                             // A function that initializes the deck, resetting it to a default ascending sort.
    for (int i = 0; i < DECK_SIZE; i++) {
        DECK[i] = i;                                // Puts the numbers 0-51 in the array DECK.
    }
}

void shuffleDeck() {                                // A function that shuffles the deck, randomizing the numbers.
    srand(time(0));                                 // Seed the random number generator based on the current time (essentially making it more random).
    for (int i = 0; i < DECK_SIZE; i++) {
        int index = rand() % DECK_SIZE;             // Retrieve some other card in the deck.
        int temp = DECK[i];                         // Get the card currently at the index i in DECK.
        DECK[i] = DECK[index];
        DECK[index] = temp;                         // Swap the number at the random index with the current index.
    }
}

int dealCard() {                                    // A function that generates a card in the game.
    return DECK[currentCardIndex++] % size(RANKS);     // Uses the mod operator to draw a card with a value between 0-12 based on the current place in the deck.
}

int cardValue(int card) {                           // Gets the value of a specified card.
                                                    // Note that card here is equal to its index in RANKS.
    return (card < 9) ? card + 2 : 10;              // Ternary operator (shorthand for an if statement).
                                                    // Could be written as:
                                                    // if (card < 9) {
                                                    //      return card + 2;
                                                    // } else {
                                                    //      return 10;
                                                    // }
                                                    // If the card is a number card, return the true value of the card (its index in RANKS + 2).
                                                    // Otherwise (if it is a face card), return 10.
                                                    // 0->2, 1->3, 2->4, 3->5, 4->6, 5->7, 6->8, 7->9, 8->10
                                                    // 9 -> Ace = 10 (currently)
                                                    // 10 -> Jack = 10
                                                    // 11 -> Queen = 10
                                                    // 12 -> King = 10
}

int dealInitialPlayerCards() {
    int card1 = dealCard();
    int card2 = dealCard();
    cout << "Your cards: " << RANKS[card1 % size(RANKS)] << " of " << SUITS[card1 / size(RANKS)] << " and " << RANKS[card2 % size(RANKS)] << " of " << SUITS[card2 / size(RANKS)] << endl;
    return cardValue(card1) + cardValue(card2);
}

int dealInitialDealerCards() {
    int card1 = dealCard();
    cout << "Dealer's card: " << RANKS[card1 % size(RANKS)] << " of " << SUITS[card1 / size(RANKS)] << endl;
    return cardValue(card1);
}

int playerTurn(int playerTotal) {
    while (true) {
        cout << "Your total is " << playerTotal << ". Do you want to hit or stand?" << endl;
        string action;
        getline(cin, action);
        if (action == "hit") {
            int newCard = dealCard();
            playerTotal += cardValue(newCard);
            cout << "You drew a " << RANKS[newCard % size(RANKS)] << " of " << SUITS[newCard / size(RANKS)] << endl;
            if (playerTotal > 21) {
                break;
            }
        } else if (action == "stand") {
            break;
        } else {
            cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
        }
    }
    return playerTotal;
}

int dealerTurn(int dealerTotal) {
    while (dealerTotal < 17) {
        int newCard = dealCard();
        dealerTotal += cardValue(newCard);
    }
    cout << "Dealer's total is " << dealerTotal << endl;
    return dealerTotal;
}

void determineWinner(int playerTotal, int dealerTotal) {
    if (dealerTotal > 21 || playerTotal > dealerTotal) {
        cout << "You win!" << endl;
    } else if (dealerTotal == playerTotal) {
        cout << "It's a tie!" << endl;
    } else {
        cout << "Dealer wins!" << endl;
    }
}

int main() {
    initializeDeck();
    shuffleDeck();
  
    int playerTotal = dealInitialPlayerCards();
    int dealerTotal = dealInitialDealerCards();
  
    playerTotal = playerTurn(playerTotal);
    if (playerTotal > 21) {
      cout << "You busted! Dealer wins." << endl;
      return 0;
    }
    dealerTotal = dealerTurn(dealerTotal);
    determineWinner(playerTotal, dealerTotal);
  
    return 0;
}
