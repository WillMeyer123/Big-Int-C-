#include "functions.h"
#include "bigint/bigint.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cmath>

const char B = 26;

bool convert_char(char &ch, unsigned int &i) {

    if (ch >= 'a' && ch <= 'z') i = (unsigned int)(ch - 'a' + 0);
    else if (ch >= 'A' && ch <= 'Z') i = (unsigned int)(ch - 'A' + 0);
    else return false;

    return true;
}



std::vector<unsigned int> get_frequency_vector(const std::string file_name) {
    std::vector <unsigned int> frequency(B*B*B, 0);
    char c;
    unsigned int i1, i2, i3, count, temp;
    count = 0;

    std::ifstream infile(file_name);

    while (infile.get(c)) {
    	if (convert_char(c, temp)) {
    		count++;
    		switch (count) {
    			case 1: i1 = temp; break;
    			case 2: i2 = temp; break;
    			case 3: i3 = temp; frequency[B*B*i1 + B*i2 + i3]++; break;
    			default:
    			i1 = i2;
    			i2 = i3;
    			i3 = temp;
    			frequency[B*B*i1 + B*i2 + i3]++;
    		}


    	}

    }
    if (count < 3) {
    	std::cerr << "Not enough characters in " << file_name << std::endl;
        exit(EXIT_FAILURE);
    }

    return frequency;
}

double similarity(const std::vector<unsigned int> &a, const std::vector<unsigned int> &b) {
    //Initialize bigints for the numerator and denominator
    bigint top, bottom1, bottom2;
    //Loop through each element of the frequency vectors
    for(int i = 0; i < 17575; i++) {
        //Numerator accumulates dot product
        top += bigint(a[i] * b[i]);
        //Denominators accumlate absolute value of each element, bigints must be > 0
        bottom1 += bigint(a[i]);
        bottom2 += bigint(b[i]);
    }
    //Multiply denominator accumulators
    bigint bottom = bottom1 * bottom2;
    //Perform scaled division using bigints
    top *= bigint(1000000);
    bigint raised = top/bottom;
    //Save result of scaled divison as a double so errors are not lost converting to float
    double scaled = std::stod(raised.to_string())/1000000.0;
    //Should return a value between 0 and 1
    return scaled;
}

std::string detect_language(const std::string &test_language, const std::vector<std::string> &training_languages) {
    //Generate frequency vector for the test case
    std::vector<unsigned int> test = get_frequency_vector(test_language);
    //Initialize current highest similarity, any vector with values should give a result
    //higher than 0.0 when compared
    double maxSim = 0.0;
    //Initialize string to return as result
    std::string lang;
    //Loop through the training languages
    for(size_t i = 0; i < training_languages.size(); i++) {
        //Generate a frequency vector for the current training language
        std::vector<unsigned int> training = get_frequency_vector(training_languages[i]);
        //Calculate similarity between test case and training language
        double sim = similarity(test, training);
        //Compare current similarity with the highest found similarity
        if (sim > maxSim) {
            //If higher, training lang is most similar to test case, so set result to
            //that language and set the similarity as the new highest similarity
            lang = training_languages[i];
            maxSim = sim;
        }

    }
    return lang;

}