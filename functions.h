#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

///////////////////////////////////////////////////////////////////
// INCLUDES GO HERE
///////////////////////////////////////////////////////////////////
#include "bigint/bigint.h"


///////////////////////////////////////////////////////////////////
// FUNCTION HEADERS GO HERE
///////////////////////////////////////////////////////////////////

/*
Takes a char ch. If ch is a Roman letter (a-z, A-Z) converts it to its
numeric representation for the base-26 encoding, e.g. a becomes 0.
This result is placed in the unsigned int i.
Returns a boolean indicating whether this conversion was successful:
true if the char was in the range a-z or A-Z; false otherwise.
*/
bool convert_char(char &ch, unsigned int &i);


/*
Takes a string which must be a valid path to a file.
Returns a vector of unsigned ints representing the trigram frequencies
of that file, in canonical base-26 order (aaa to zzz)
*/
std::vector<unsigned int> get_frequency_vector(const std::string file_name);


// uses the above functions to find which language is most similar to the test_language.
/*
Take a string indicating a query (test) filename,
and a vector of strings each of which is a filename.
Return that filename from the vector whose contents are most similar to the query,
in terms of trigram frequency cosine similarity.
*/
std::string detect_language(const std::string &test_language, const std::vector<std::string> &language_names);

/*
Takes 2 constant frequency vectors passed by reference, a and b.
Assumes the frequency vectors are built from trigrams
and have 26^3 elements.
Return the cosine similarity between the frequency vectors as a double
where 0 means the vectors are completely different and 1 means the vectors
are exactly the same.
*/

double similarity(const std::vector<unsigned int> &a, const std::vector<unsigned int> &b);

#endif
