#include "parsing.h"

using namespace std;

string GetAnswer(map<string,string> answers, string question, map<string,string> vocab, map<string,string> words)
{
        string answer;
        question = FormatToReadable(words,vocab,question);
        answer = answers[question];
        if(answer != "")
        {
		if (answer.find("+command+") != string::npos)
		{
			answer = CheckForCommands(answer);
		}
		else
		{
                	answer = answer_parse(answer);
		}
        }
        else
	{
                answer = "I don't know what you mean.";
	}
        return answer;
}

string ReadAnswers(map<string,string> answers, string question, map<string,string> vocab, map<string,string> words)
{
        string answer;
        if (question.find(",") != string::npos)
        {
                debugcout("Multi sentense detected");
                vector<string> x = split(question, ',');
                for(int i = 0; i < x.size(); i++)
                {
                        answer += GetAnswer(answers,x[i],vocab,words);
                        if(x.size()-1 != i)
                        {
                                answer += ", ";
                        }
                }
                answer += ".";
        }
        else
        {
                answer = GetAnswer(answers, question, vocab, words) + ".";
        }
        return answer;
}

