#include "NQueensTable.hpp"
#include <cstdlib>
#include <iostream>
#include "Utils.h"

NQueensTable::NQueensTable(unsigned long N) {
    this->N = N;
    this->board = (unsigned long *) calloc(this->N, sizeof(unsigned long));

    for (unsigned long i = 0; i < this->N; i++) {
        this->board[i] = -1;
    }
}

void NQueensTable::show() {
    int cont = 0;
    for (unsigned long i = this->N - 1; i >= 0; --i) {
        for (unsigned long j = 0; j < this->N; j++) {
            if(this->board[j] == i)
                cout << "Q  ";
            else
                cout << "*  ";
        }
        cout << endl;
        if(i == 0) break;
    }
    
}

void NQueensTable::update_from_mpz_class(mpz_class const &value) {
    vector<unsigned long> result = Utils::to_base_trunc(value, this->N);

    if (result.size() == this->N) {
        for (unsigned long i = 0; i < this->N; i++) {
            unsigned long q_position = result.at(i);
            if (q_position >= this->N) {
                throw out_of_range("Queen position invalid!");
            }
            this->board[i] = q_position;
        }
    } else {
        throw length_error("Vector has a size different from expected!");
    }
}

void NQueensTable::update_from_serial(string s) {
    vector<string> split_result = Utils::explode(s, '|');

    if (split_result.size() == this->N) {
        for (unsigned long i = 0; i < this->N; i++) {
            unsigned long q_position = stoi(split_result.at(i));
            if (q_position >= this->N){
                throw out_of_range("Queen position invalid!");
            }
            this->board[i] = q_position;
        }
    } else {
        throw length_error("Serial has a size different from expected!");
    }
}

void NQueensTable::update_from_vector(vector<unsigned long> const &vec) {
    if (vec.size() == this->N) {
        for (unsigned long i = 0; i < this->N; i++) {
            unsigned long q_position = vec.at(i);
            if (q_position >= this->N){
                throw out_of_range("Queen position invalid!");
            }
            this->board[i] = q_position;
        }
    } else {
        throw length_error("Vector has a size different from expected!");
    }
}

string NQueensTable::serialize() {
    string result = "";

    for(unsigned long i = 0; i < this->N; i++) {
        if (i != 0)
            result += "|" + to_string(this->board[i]);
        else
            result += to_string(this->board[i]);
    }

    return result;
}

bool NQueensTable::is_a_valid_table() {
    for(unsigned long i = 0; i < this->N - 1; i++) {
        for (unsigned long j = i+1; j < this->N; j++) {

            unsigned long diff = 0;
            if (this->board[i] > this->board[j])
                diff = this->board[i] - this->board[j];
            else
                diff = this->board[j] - this->board[i];

            if(diff == 0 || diff == j - i)
                return false;
        }
    }
    return true;
}

NQueensTable::~NQueensTable() {
    this->N = N;
    free(this->board);
}
