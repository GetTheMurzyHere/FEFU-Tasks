#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector>
#include <time.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/integer.hpp>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/random/mersenne_twister.hpp>

using namespace std;
using namespace boost::multiprecision;
using namespace boost::random;

pair<cpp_int, cpp_int> publicKey(cpp_int e, cpp_int n) {
	cout << "Открытый ключ для шифрования: " << e << " " << n << endl;
	return make_pair(e, n);
}

pair<cpp_int, cpp_int> privateKey(cpp_int d, cpp_int n) {
	return make_pair(d, n);
}

cpp_int gcd(cpp_int a, cpp_int b)
{
	cpp_int c;
	while (b)
	{
		c = a % b;
		a = b;
		b = c;
	}
	return abs(a);
}

cpp_int my_pow(unsigned char a, int n) {
	if (n == 0)
		return 1;
	if (n % 2 == 1)
		return my_pow(a, n - 1) * a;
	else {
		cpp_int b = my_pow(a, n / 2);
		return b * b;
	}
}

cpp_int my_pow(cpp_int a, cpp_int n) {
	if (n == 0)
		return 1;
	if (n % 2 == 1)
		return my_pow(a, n - 1) * a;
	else {
		cpp_int b = my_pow(a, n / 2);
		return b * b;
	}
}

int getDigitsCount(cpp_int number) {
	int count = 0;
	while (number > 0) {
		count++;
		number /= 10;
	}
	return count;
}

cpp_int getNumber(string x) {
	cpp_int number = 0;
	for (int i = 0; i < x.length(); i++) {
		number += (int)(x[i] - '0') * my_pow((cpp_int)10, (cpp_int)(x.length() - 1 - i));
	}
	return number;
}

void encrypt(string text, pair<cpp_int, cpp_int> key, vector<pair<int, string>> &vec) {
	clock_t time;
	time = clock();
	for (long long i = 0; i < text.length(); i++) {
		cpp_int symbol = (unsigned char)text[i];
		cpp_int cryptedSymbol = powm(symbol, key.first, key.second);
		int codeLength = getDigitsCount(cryptedSymbol);
		cout << "Символ " << text[i] << "(ASCII" << symbol << ") закодирован " <<  " " << cryptedSymbol << ", колличество символов в коде - " << codeLength << endl;
		string code = "";
		while (cryptedSymbol > 0) {
			code += to_string((int)(cryptedSymbol % 10));
			cryptedSymbol /= 10;
		}
		reverse(code.begin(), code.end());
		vec.push_back(make_pair(codeLength, code));
	}
	time = clock() - time;
	cout << "Шифрование прошло успешно! Зашифрованный текст записан в файл output.txt.\nВремя работы алгоритма шифрования: " << (double)time / CLOCKS_PER_SEC << " секунд.\n";
}



void decrypt(pair<cpp_int, cpp_int> key, vector<pair<int, string>>vec, vector<unsigned char> &text) {
	clock_t time;
	time = clock();

	for (long long i = 0; i < vec.size(); i++) {
		cpp_int code = getNumber(vec[i].second);
		cpp_int char_code = powm(code, key.first, key.second);
		text.push_back((unsigned char)char_code);
	}
	time = clock() - time;
	cout << "Дешифрование прошло успешно! Исходный текст записан в файл output.txt.\nВремя работы алгоритма расшифрования: " << (double)time / CLOCKS_PER_SEC << " секунд.\n";
}

cpp_int GetPrime()
{
	mt11213b base_gen(clock());
	independent_bits_engine<mt11213b, 512, cpp_int> gen(base_gen);
	cpp_int n;
	do
	{
		n = gen();
	} while (!miller_rabin_test(n, 25));
	return n;
}

int calculateE(cpp_int f)
{

	int e;

	for (e = 2; e < f; e++)
	{
		if (gcd(e, f) == 1)
		{
			return e;
		}
	}

	return -1;
}

cpp_int calculateD(cpp_int e, cpp_int t)
{

	cpp_int d;
	cpp_int k = 1;

	while (1)
	{
		k = k + t;

		if (k % e == 0)
		{
			d = (k / e);
			return d;
		}
	}

}


int main() {
	setlocale(LC_ALL, "Russian");
	cout << "Выполняется генерация простых чисел...\n";

	cpp_int p = GetPrime();
	cpp_int q = GetPrime();
	cpp_int f = (p - 1)*(q - 1);
	cpp_int n = p * q;

	int e = calculateE(f);
	cpp_int d = calculateD(e, f);

	cout << "Доброго времени суток, пользователь! Данное приложение выполняет шифрование/расшифрование с помощью алгоритма RSA.\n";
	cout << "\n1 - зашифровать текст\n2 - расшифровать текст\n\n";
	vector<pair<int, string>> encryptedCodes;

	while (true) {
	int mode;
	string inputText;
	cin >> mode;
		switch (mode)
		{
		case 1: {
			encryptedCodes.clear();
			ifstream input("input.txt");
			if (!input) {
				cout << "Файл не существует, чтение невозможно!\n";
				break;
			}
			else {
				if (input.peek() == EOF) {
					cout << "Файл пуст! Занесите текст в файл и повторите попытку!\n";
					break;
				}
				else {
					while (!input.eof())
					{
						string temp;
						getline(input, temp);
						inputText += temp;
					}
					input.close();
					encrypt(inputText, publicKey(e, n), encryptedCodes);
					ofstream output("output.txt");
					for (long long i = 0; i < encryptedCodes.size(); i++) {
						output << encryptedCodes[i].first << encryptedCodes[i].second;
					}
					output.close();
				}
			}
			break;
		}
		case 2: {
			ifstream output("output.txt");
			if (!output) {
				cout << "Файл не существует, чтение невозможно!\n";
				break;
			}
			else {
				if (output.peek() == EOF) {
					cout << "Файл пуст! Занесите текст в файл и повторите попытку!\n";
					break;
				}
				else {
					string temp;
					getline(output, temp);
					vector<pair<int, string>> symbols = encryptedCodes;
					vector<unsigned char> text;
					/*for (int i = 0; i < temp.length();) {
						string symbol = "";
						int count = symbols[i].first;
						temp.erase(0, getDigitsCount(count));
						for (int i = 0; i < count; i++) {
							symbol = symbol + temp[i];
						}
						symbols.push_back(make_pair(count, symbol));
						i += count;
					}*/
					output.close();
					decrypt(privateKey(d, n), symbols, text);
					ofstream input("input.txt");
					for (long long i = 0; i < symbols.size(); i++) {
						input << text[i];
					}
					symbols.clear();
					text.clear();
					input.close();
				}
			}
			break;
		}
		}
	}
	system("pause");
	return 0;
}