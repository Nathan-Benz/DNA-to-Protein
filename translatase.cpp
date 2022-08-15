/*
Nathan Benitez
CSCI-135
Professor Minh Nguyen
Assignment: Project 2

This program takes a dna text file and converts it into mRNA then amino acids
*/
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

char DNAbase_to_mRNAbase(char base);
string DNA_to_mRNA(string strand);
string dictionary_read(string codon, ifstream &dict);

int main () {
    ifstream fin("dna2b.txt");
    ifstream dict("codons.tsv");

    if (fin.fail()) {
        cerr << "File cannot be read, opened, or does not exist.\n";
        exit(1);
    }
    string strand;
    while(getline(fin, strand)) {
        bool start = false;

        for (int i = 0; i < strand.length(); i+=3) {
            string codon = DNA_to_mRNA(strand.substr(i, 3));

            if (codon == "AUG") {
                start = true;
            }
            
            //Checks for any stop codons to end the loop
            if (codon == "UAA" || codon == "UAG" || codon == "UGA") {
                break;
            }

            if (start) {
                cout << dictionary_read(codon, dict);
            }

            if(i < i+3) {
                string nCodon = DNA_to_mRNA(strand.substr(i+3, 3));

                if (start && nCodon != "UAA" && nCodon != "UAG" && nCodon != "UGA") {
                    cout << '-';
                }
            }
        }

        cout << endl;
    }
    fin.close();
    dict.close();
}

//Changes the bases of the DNA into mRNA
char DNAbase_to_mRNAbase(char base) {
    if (toupper(base) == 'A') {
            base = 'U';
        }
        else if (toupper(base) == 'T') {
            base = 'A';
        }
        else if (toupper(base) == 'C' ) {
            base = 'G';
        }
        else if (toupper(base) == 'G') {
            base = 'C';
        }
        return base;
}

//Sores the new mRND base into the string
string DNA_to_mRNA(string strand) {
    for (int i = 0; i < strand.size(); i++) {
        strand[i] = DNAbase_to_mRNAbase(strand[i]);
    } 
    return strand;
}

//Reads the table and prints protien
string dictionary_read(string codon, ifstream &dict) {
    string key, value;

    dict.clear(); // reset error state
    dict.seekg(0); // return file pointer to the beginning

    while (dict >> key >> value) {
        if (codon == key) {
            return value;
        }
    }

    return " ";
}