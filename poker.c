#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define H 5 // liczba kart w ręce

int greater(int a, int b) { // funckja przyjmująca wartość jeden, gdy a > b, wartość 2, gdy a < b i 0, gdy a = b
    if (a > b) return 1;
    else if (a < b) return 2;
    else return 0;
}
int char_to_value(int c) { // funckja zamieniająca wartość char na liczbę, odpowiadającą danej wartości karty
    if (c == 'A') return 14;
    if (c == 'K') return 13;
    if (c == 'Q') return 12;
    if (c == 'J') return 11;
    if (c == 'T') return 10;
    if (c >= '2' && c <= '9') return c - '0';
    return 0;
}
typedef struct{ // struktura karty - wartość i kolor
    int value;
    int suit;
} Card;
typedef struct{ // struktura ręki pokerowej - 5 kart
   Card Cards[5];
} Hand;
void sort_hand(Hand *h) { // procedura sortująca rękę pokerową ze względu na wartości kart
    Card temp;
    for (int i = 5; i > 0; i--) {
        for (int j = 0; j < i - 1; j++) {
            if ((*h).Cards[j].value < (*h).Cards[j + 1].value) {
                temp = (*h).Cards[j];
                (*h).Cards[j] = (*h).Cards[j + 1];
                (*h).Cards[j + 1] = temp;
            }
        }
    }
}
bool is_same_suit(Hand h) { // sprawdzamy czy wszystkie karty w ręce są tego samego koloru
    int color = h.Cards[0].suit;
    bool result = true;
    int i = 1;
    while (i < H && result == true) {
        result = (h.Cards[i].suit == color);
        i++;
    }
    return result;
}
void fix_ace_straight(Hand *h) {
    if ((*h).Cards[0].value == 14 && (*h).Cards[1].value == 5 &&
        (*h).Cards[2].value == 4 && (*h).Cards[3].value == 3 &&
        (*h).Cards[4].value == 2) {
        (*h).Cards[0].value = 1;
        sort_hand(h);
        }
}
bool is_sequence(Hand h) { // sprawdzamy czy wartości kart w ręce są kolejnymi liczbami (poker lub strit)
    bool result = true;
    int i = 0;
    while (i < H - 1 && result == true) {
        result = (h.Cards[i].value == h.Cards[i + 1].value + 1);
        i++;
    }
    i = 1;
    bool five_to_A = (h.Cards[0].value == 14);
    while (i < H && five_to_A == 1) {
        five_to_A = (h.Cards[i].value == 6 - i);
        i++;
    }
    if (five_to_A == true) result = true;
    return result;
}
int count_value(Hand h, int value) { // funkcja licząca, ile kart w ręce ma daną wartość
    int count = 0;
    for (int i = 0; i < H; i++) {
        if (h.Cards[i].value == value) count++;
    }
    return count;
}
int how_many(Hand h) { // funckja licząca liczbę różnych wartości w ręce pokerowej
    int count = 0;
    int i = 0;
    while(i < H) {
        count++;
        i += count_value(h, h.Cards[i].value);
    }
    return count;
}
int compare_one_by_one(Hand h1, Hand h2) { // funckja porównująca dwie ręce od najwyższej wartości
    int higher = 0;
    int i = 0;
    while (i < H && higher == 0) {
        higher = greater(h1.Cards[i].value, h2.Cards[i].value);
        i++;
    }
    return higher;
}
int get_rank(Hand h) { // funckja określająca najlepszy układ pokerowy z danej ręki, od 1 - wysoka karta do 9 - poker
    bool same = is_same_suit(h);
    bool sequential = is_sequence(h);
    if (how_many(h) == 5) {
    if (same == true && sequential == true) return 9;
    else if (same == true) return 6;
    else if (sequential == true) return 5;
    else return 1;
    }
    if (how_many(h) == 4) return 2;
    if (how_many(h)== 3) {
        if (count_value(h, h.Cards[2].value) == 3) return 4;
        else return 3;
    }
    if (how_many(h) == 2) {
        if (count_value(h, h.Cards[2].value) == 3) return 7;
        else if (count_value(h, h.Cards[2].value) == 4) return 8;
    }
    return 0;
}int double_value(Hand h) { // funckja zwracająca wartość, która występuje dokładnie dwa razy w ręce, jeśli istnieje dokładnie jedna taka wartość w ręce
    int result = 0;
    int i = 0;
    if (how_many(h) == 4) {
        while (i < H - 1) {
            if (h.Cards[i].value == h.Cards[i + 1].value) result = h.Cards[i].value;
            i++;
        }
    return result;
    }
    else return 0;
}
int compare_hands(Hand h1, Hand h2) { // rostrzyganie remisów
    int common_rank;
    int result = greater(get_rank(h1), get_rank(h2));
    if (result == 0) {
            common_rank = get_rank(h1);
            switch (common_rank){
                case 9: result = compare_one_by_one(h1, h2);
                        break;
                case 8: result = greater(h1.Cards[2].value, h2.Cards[2].value);
                        if (result == 0) {
                            if (h1.Cards[0].value == h2.Cards[0].value) result = greater(h1.Cards[4].value, h2.Cards[4].value);
                            else result = greater(h1.Cards[0].value, h2.Cards[0].value);
                        }
                        break;
                case 7: result = greater(h1.Cards[2].value, h2.Cards[2].value);
                        if (result == 0) {
                            if (h1.Cards[0].value == h2.Cards[0].value) result = greater(h1.Cards[4].value, h2.Cards[4].value);
                            else result = greater(h1.Cards[0].value, h2.Cards[0].value);
                        }
                        break;
                case 6: result = compare_one_by_one(h1, h2);
                        break;
                case 5: result = compare_one_by_one(h1, h2);
                        break;
                case 4: result = greater(h1.Cards[2].value, h2.Cards[2].value);
                        if (h1.Cards[4].value == h2.Cards[0].value) result = 1;
                        else if (h2.Cards[4].value == h1.Cards[0].value) result = 2;
                        else {
                                result = compare_one_by_one(h1, h2);
                        }
                        break;
                case 3: result = greater(h1.Cards[1].value, h2.Cards[1].value);
                        if (result == 0) {
                                result = greater(h1.Cards[3].value, h2.Cards[3].value);
                                if (result == 0) result = compare_one_by_one(h1, h2);
                        }
                        break;
                case 2: result = greater(double_value(h1), double_value(h2));
                        if (result == 0) result = compare_one_by_one(h1, h2);
                        break;
                case 1: result = compare_one_by_one(h1, h2);
                        break;
                default: result = -1;
            }
    }
    return result;
}
int read_hand(Hand *hand) { // wczytywanie rąk
    Hand h;
    char value;
    char suit;
    if (scanf(" %c%c", &value, &suit) != 2) {
        return 0;
    }
    h.Cards[0].value = char_to_value(value);
    h.Cards[0].suit = suit;
    for (int i = 1; i < 5; i++) {
        scanf(" %c%c", &value, &suit);
        h.Cards[i].value = char_to_value(value);
        h.Cards[i].suit = suit;
    }
    sort_hand(&h);
    *hand = h;
    fix_ace_straight(hand);
    return 1;
}

int main(){
   Hand current_hand;
   Hand best_hand;
   int current_row = 1;
   int best_row = 0;
   bool is_tie = false;
   while (read_hand(&current_hand) == 1) {
        if (current_row == 1) {
            best_hand = current_hand;
            best_row = current_row;
        }
        else {
            if (compare_hands(current_hand, best_hand) == 1) {
                best_hand = current_hand;
                best_row = current_row;
		is_tie = false;
            }
            else if (compare_hands(current_hand, best_hand) == 0) {
                is_tie = true;
                best_row = 0;
            }
        }
        current_row++;
   }

    if (is_tie == false) printf("%d\n", best_row);
    else printf("%d\n", 0);
    return 0;
}
