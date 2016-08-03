#include "nlp.h"

using namespace std;

int main()
{
	string input, answer;
	map<string,string> answers = DatFileLoader("questions.dat");
    map<string,string> vocab = DatFileLoader("vocabulary.dat");
    map<string,string> words = DatFileLoader("words.dat");
	while(1)
	{
	getline(cin, input);
	answer = ReadAnswers(answers, input, vocab, words);
	cout << answer << endl;
	}
	return 0;
}
