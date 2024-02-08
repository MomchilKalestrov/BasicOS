size_t string_length(const char* data) {
	size_t len = 0;
	while (data[len])
		len++;
	return len;
}

void string_reverse(char *string, size_t length)
{
    size_t start = 0;
    size_t end = length - 1;
    while (start < end) {
        char temp = string[start];
        string[start] = string[end];
        string[end] = temp;
        end--;
        start++;
    }
}

void string_convert(char *string, int32_t number) {
    size_t length = 0;
    int32_t temp = number;
    bool isNegative = false;

    if (temp == 0) {
        string[length++] = '0';
        string[length] = '\0';
		return;
    }
	
    if (temp < 0) {
        isNegative = true;
        temp = -temp;
    }

    while (temp != 0) {
        uint8_t rem = temp % 10;
        string[length++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        temp = temp / 10;
    }

    if (isNegative)
        string[length++] = '-';
 
    string[length] = '\0';

    string_reverse(string, length);
 
    return;
}