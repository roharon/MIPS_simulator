extern int* REGISTER;

unsigned int HashCode(const wchar_t *str)
{
	return str[0] ? static_cast<unsigned int>(str[0]) + 0xEDB8832Full * HashCode(str + 1) : 8603;
}
}

// switch statement에서 문자열쓰기위함