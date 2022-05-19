#ifndef _STRING_SWITCH_HPP
#define _STRING_SWITCH_HPP
typedef std::uint64_t hash_t;

constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;

constexpr inline static hash_t hash_(char const* str)
{
	hash_t ret{basis};

	while(*str){
		ret ^= *str;
		ret *= prime;
		str++;
	}

	return ret;
}

constexpr hash_t hash_compile_time(char const* str, hash_t last_value = basis)
{
	return *str ? hash_compile_time(str+1, (*str ^ last_value) * prime) : last_value;
}

constexpr unsigned long long operator "" _hash(char const* p, size_t)
{
	return hash_compile_time(p);
}

void simple_switch(char const* str)
{
	using namespace std;
	switch(hash_(str)){
	case "first"_hash:
		cout << "1st one" << endl;
		break;
	case "thirfthirfthirfthir"_hash:
		cout << "2nd one" << endl;
		break;
	case "thirfthirfthirfthirfthirfthirfthirg"_hash:
		cout << "3rd one" << endl;
		break;
	case "thirfthirfthirfthirfthirfthirfthirf"_hash:
		cout << "4rd one" << endl;
		break;
	default:
		cout << "Default..." << endl;
	}
}
#endif //_STRING_SWITCH_HPP
