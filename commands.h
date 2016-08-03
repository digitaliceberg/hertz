#include <string>
#include <ctime>

using namespace std;

string ai_version()
{
	string version = "Hertz Version: Alpha 0.10";
	return version;
}

string formatted_time()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	stringstream ss;
	string hours, minutes, seconds, formatted_time;
	if(ltm->tm_hour < 10)
		hours = "0";
	if(ltm->tm_min < 10)
		minutes = "0";
	if(ltm->tm_sec < 10)
		seconds = "0";
	ss << hours << ltm->tm_hour << ":" << minutes << ltm->tm_min << ":" << seconds << ltm->tm_sec;
	formatted_time = "The current time is: " + ss.str();
	return formatted_time;
}
