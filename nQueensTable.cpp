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
    for (unsigned long i = this->N - 1; i >= 0; i--) {
        for (unsigned long j = 0; j < this->N; j++) {
            if(this->board[j] == i)
                cout << "Q  ";
            else
                cout << "*  ";
        }
        cout << endl;
    }
    
}

void NQueensTable::update_from_serial(string s) {
    vector<string> split_result = Utils::explode(s, '|');

    if (split_result.size() == this->N) {
        for (unsigned long i = 0; i < this->N; i++) {
            unsigned long position = stoi(split_result.at(i));
            if (position >= this->N || position < -1){
                throw out_of_range("Position invalid!");
            }
            this->board[i] = position;
        }
    } else {
        throw length_error("Serial has a size different from expected!");
    }
}

void NQueensTable::update_from_vector(vector<unsigned long> const &vec) {
    if (vec.size() == this->N) {
        for (unsigned long i = 0; i < this->N; i++) {
            unsigned long position = vec.at(i);
            if (position >= this->N || position < -1){
                throw out_of_range("Position invalid!");
            }
            this->board[i] = position;
        }
    } else {
        throw length_error("Serial has a size different from expected!");
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

NQueensTable::~NQueensTable() {
    this->N = N;
    free(this->board);
}
