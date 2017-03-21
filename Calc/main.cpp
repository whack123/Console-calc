#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

vector<int> BracketStart;
vector<int> BracketEnd;

int FindNextBracket(vector<char> v) {
	int brackPos = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == ')') {
			brackPos = i;
		}
	}
	return brackPos;
}
bool ChackForSymb(char symb) {
	if (symb == '+' || symb == '-' || symb == '*' || symb == '/'||symb == '('||symb == ')'|| symb == '^')
	{
		return true;
	}
	return false;
}
double Sum(vector<string> numbers, vector<char> symbols);
int main() {
	string input;
	int pos = 0;
	vector<string> numbers;
	vector<char> symbols;
	getline(cin, input);
	for (int i = 0; i <= input.size(); i++)
	{
		//read numbers
		if (ChackForSymb(input[i])||i == input.size())
		{
			string num1;
			num1 = input.substr(pos, i-pos);
			numbers.push_back(num1);
			pos = i+1;
		}
		//read symbols
		if (ChackForSymb(input[i])) {//
			symbols.push_back(input[i]);
		}
	}
	for (int i = 0; i < numbers.size(); i++)//carieli adgilebi ro darcheba prcxilebtan isini movashorot
	{
		if (numbers[i] == "")
		{
			numbers.erase(numbers.begin() + i);
		}
	}
	cout << endl;
	double FullSum = Sum(numbers, symbols);
	cout << "++++++++++++++++++++++++" << endl<<" gamosaxulebis pasuxia:  " << FullSum << endl << "++++++++++++++++++++++++" << endl;
	system("pause");
	return 0;
}
//
double SumInBrackets(vector<string> &_numbers, vector<char> &_symbols,int firstBrackPos) {//am metodit calke gadagvaqvs prchxilebshi arsebuli gamosaxuleba
	double sumInBrackets = 0;
	vector<string> numbers;
	vector<char> symbols;
	for (int i = firstBrackPos+1; i < FindNextBracket(_symbols); i++)
	{
		symbols.push_back(_symbols[i]);
	}
	for (int i = firstBrackPos; i < FindNextBracket(_symbols); i++)
	{
		numbers.push_back(_numbers[i]);
	}
	//vshlit frchxilebs shignit ricxxvebsa da simboloebs
	_numbers.erase(_numbers.begin() + firstBrackPos, _numbers.begin() + FindNextBracket(_symbols));
	_symbols.erase(_symbols.begin() + firstBrackPos, _symbols.begin() + FindNextBracket(_symbols)+1);
	//
	sumInBrackets = Sum(numbers,symbols);//
	return sumInBrackets;
}
//void BracketPos(vector<char> symbols) {
//	for (int i = 0; i < symbols.size(); i++) {
//		if (symbols[i] == '(')
//		{
//			int newnum = SumInBrackets(numbers, symbols, i);
//			numbers.insert(numbers.begin() + i, to_string(newnum));
//			break;
//		}
//	}
//}
double SumNumbers(vector<string> &numbers, vector<char> &symbols, int firstNumIndex,int secendNumberIndex,int symbolIndex) {//metodi krebavs or ricxvs mat shua arsebuli moqmedebis mixedvit shlis samive madgans da mat adgilas svams migebul shedegs
	double flSumm = 0;
	switch (symbols[symbolIndex]) {
	case '+':
		flSumm = stod(numbers[firstNumIndex].c_str()) + stod(numbers[secendNumberIndex].c_str());
		symbols.erase(symbols.begin() + symbolIndex);
		numbers.erase(numbers.begin() + firstNumIndex, numbers.begin() + 2);
		numbers.insert(numbers.begin()+ symbolIndex, to_string(flSumm));
		break;
	case '-':
		flSumm = stod(numbers[firstNumIndex].c_str()) - stod(numbers[secendNumberIndex].c_str());
		symbols.erase(symbols.begin() + symbolIndex);
		numbers.erase(numbers.begin() + firstNumIndex, numbers.begin() + 2);
		numbers.insert(numbers.begin() + symbolIndex, to_string(flSumm));
		break;
	case '*':
		flSumm = stod(numbers[firstNumIndex].c_str()) * stod(numbers[secendNumberIndex].c_str());
		symbols.erase(symbols.begin() + symbolIndex);
		numbers.erase(numbers.begin() + firstNumIndex, numbers.begin() + firstNumIndex + 2);
		numbers.insert(numbers.begin() + symbolIndex, to_string(flSumm));
		break;
	case '/':
		flSumm = stod(numbers[firstNumIndex].c_str()) / stod(numbers[secendNumberIndex].c_str());
		symbols.erase(symbols.begin() + symbolIndex);
		numbers.erase(numbers.begin() + firstNumIndex, numbers.begin() + firstNumIndex + 2);
		numbers.insert(numbers.begin() + symbolIndex, to_string(flSumm));
		break;
	case '^':
		flSumm = pow(stod(numbers[firstNumIndex].c_str()), stod(numbers[secendNumberIndex].c_str()));
		symbols.erase(symbols.begin() + symbolIndex);
		numbers.erase(numbers.begin() + firstNumIndex, numbers.begin() + firstNumIndex + 2);
		numbers.insert(numbers.begin() + symbolIndex, to_string(flSumm));
		break;
	}
	return flSumm;
}
double Sum(vector<string> numbers, vector<char> symbols)//metodi adgens prioritetebs da idzaxebs shesabamis metodebs
{
	double flSumm = 0;
	
	while (symbols.size() > 0)
	{
		int firstNumIndex = 0, secendNumberIndex = 1, symbolIndex = 0;
		for (int i = 0; i < symbols.size(); i++)
		{
			for (int i = 0; i < symbols.size(); i++) {
				if (symbols[i] == '(')
				{
					int newnum = SumInBrackets(numbers, symbols, i);
					numbers.insert(numbers.begin() + i, to_string(newnum));
					break;
				}
			}
			if (symbols[i] == '^')
			{
				symbolIndex = i;
				firstNumIndex = i;
				secendNumberIndex = i + 1;
				break;
			}
			if (symbols[i] == '*'|| symbols[i] == '/')
			{
				symbolIndex = i;
				firstNumIndex = i;
				secendNumberIndex = i + 1;
				break;
			}
		}
		flSumm = SumNumbers(numbers,symbols,firstNumIndex,secendNumberIndex,symbolIndex);
	}
	return flSumm;
}
