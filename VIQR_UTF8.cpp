#include <iostream>
#include <fstream>
#include <map>
#include <cstring>
using namespace std;

struct cmp_str
{
   bool operator()(char const *a, char const *b) const
   {
      return strcmp(a, b) < 0;
   }
};

char* CHARSET_UTF8[] = {
			"À", "Á", "Â", "Ã", "È", "É", "Ê", "Ì", "Í", "Ò",
			"Ó", "Ô", "Õ", "Ù", "Ú", "Ý", "à", "á", "â", "ã",
			"è", "é", "ê", "ì", "í", "ò", "ó", "ô", "õ", "ù",
			"ú", "ý", "Ă", "ă", "Đ", "đ", "Ĩ", "ĩ", "Ũ", "ũ",
			"Ơ", "ơ", "Ư", "ư", "Ạ", "ạ", "Ả", "ả", "Ấ", "ấ",
			"Ầ", "ầ", "Ẩ", "ẩ", "Ẫ", "ẫ", "Ậ", "ậ", "Ắ", "ắ",
			"Ằ", "ằ", "Ẳ", "ẳ", "Ẵ", "ẵ", "Ặ", "ặ", "Ẹ", "ẹ",
			"Ẻ", "ẻ", "Ẽ", "ẽ", "Ế", "ế", "Ề", "ề", "Ể", "ể",
			"Ễ", "ễ", "Ệ", "ệ", "Ỉ", "ỉ", "Ị", "ị", "Ọ", "ọ",
			"Ỏ", "ỏ", "Ố", "ố", "Ồ", "ồ", "Ổ", "ổ", "Ỗ", "ỗ",
			"Ộ", "ộ", "Ớ", "ớ", "Ờ", "ờ", "Ở", "ở", "Ỡ", "ỡ",
			"Ợ", "ợ", "Ụ", "ụ", "Ủ", "ủ", "Ứ", "ứ", "Ừ", "ừ",
			"Ử", "ử", "Ữ", "ữ", "Ự", "ự", "Ỳ", "ỳ", "Ỵ", "ỵ",
			"Ỷ", "ỷ", "Ỹ", "ỹ", ".", "Đ", "đ"
};

char* CHARSET_VIQR[] = {
			"A`" , "A'" , "A^" , "A~" , "E`" , "E'" , "E^" , "I`" , "I'" , "O`" ,
			"O'" , "O^" , "O~" , "U`" , "U'" , "Y'" , "a`" , "a'" , "a^" , "a~" ,
			"e`" , "e'" , "e^" , "i`" , "i'" , "o`" , "o'" , "o^" , "o~" , "u`" ,
			"u'" , "y'" , "A(" , "a(" , "DD" , "dd" , "I~" , "i~" , "U~" , "u~" ,
			"O*" , "o*" , "U*" , "u*" , "A." , "a." , "A?" , "a?" , "A^'", "a^'",
			"A^`", "a^`", "A^?", "a^?", "A^~", "a^~", "A^.", "a^.", "A('", "a('",
			"A(`", "a(`", "A(?", "a(?", "A(~", "a(~", "A(.", "a(.", "E." , "e." ,
			"E?" , "e?" , "E~" , "e~" , "E^'", "e^'", "E^`", "e^`", "E^?", "e^?",
			"E^~", "e^~", "E^.", "e^.", "I?" , "i?" , "I." , "i." , "O." , "o." ,
			"O?" , "o?" , "O^'", "o^'", "O^`", "o^`", "O^?", "o^?", "O^~", "o^~",
			"O^.", "o^.", "O*'", "o*'", "O*`", "o*`", "O*?", "o*?", "O*~", "o*~",
			"O*.", "o*.", "U." , "u." , "U?" , "u?" , "U*'", "u*'", "U*`", "u*`",
			"U*?", "u*?", "U*~", "u*~", "U*.", "u*.", "Y`" , "y`" , "Y." , "y." ,
			"Y?" , "y?" , "Y~" , "y~" , "\\.", "DD", "dd"
};

void string_concat(char * dst_str, const char *src_str1, const char *src_str2) {
	//cout << "String before concat: " << str1 << endl;
	int length = strlen(src_str1) + strlen(src_str2) + 1;
	strncpy(dst_str, src_str1, strlen(src_str1));
	strncpy(dst_str, src_str2, strlen(src_str2));
	dst_str[length] = '\0';
	//cout << "String after concat: " << result << endl;
}

void get_sub_str(char *dst_str, const char *src_str, int size) {
	strncpy(dst_str, src_str, size);
	dst_str[size] = '\0';
}

void viqr_2_utf8(map<const char*, const char*, cmp_str> charset_map, char *in_file_name, char *out_file_name) {
	ifstream in_file;
	in_file.open(in_file_name);
	in_file.seekg(0, ios::end);
    
    size_t file_size_in_bytes = in_file.tellg();
	char viqr_str[file_size_in_bytes + 1];
    in_file.seekg(0, ios::beg);
    in_file.read(viqr_str, file_size_in_bytes);
	in_file.close();
	viqr_str[file_size_in_bytes] = '\0';
	int input_length = file_size_in_bytes;

	ofstream out_file;
	out_file.open(out_file_name);

	int i=0;
	while (i < input_length) {
		const char *curr_sub_str = viqr_str + i;
		bool found_result = false;
		if (i <= input_length - 3) {
			char tuple3[4];
			get_sub_str(tuple3, curr_sub_str, 3);
			if (charset_map.count(tuple3) > 0) {
				// Found 3-characters matched, replace by UTF8 char
				const char* utf8_replacement = charset_map[tuple3];
				// Write to file
				out_file << utf8_replacement;
				i += 3;
				continue;
			} else {
				char tuple2[3];
				get_sub_str(tuple2, curr_sub_str, 2);
				if (charset_map.count(tuple2) > 0) {
					// Found 2-characters matched, replace by UTF8 char
					const char* utf8_replacement = charset_map[tuple2];
					// Write to file
					out_file << utf8_replacement;
					i += 2;
					continue;
				}
			}
		} else if (i <= input_length - 2) {
			char tuple2[3];
			get_sub_str(tuple2, curr_sub_str, 2);
			if (charset_map.count(tuple2) > 0) {
				// Found 2-characters matched, replace by UTF8 char
				const char* utf8_replacement = charset_map[tuple2];
				// Write to file
				out_file << utf8_replacement;
				i += 2;
				continue;
			}
		}

		// Not matched, keep current character
		char tuple1[2];
		get_sub_str(tuple1, curr_sub_str, 1);
		// Write to file
		out_file << tuple1;
		i++;
	}
	out_file.close();
}

int main(int argc, char **argv) {
	if (argc != 4) {
		cout << "Invalid syntax" << endl;
	}

	int mode = atoi(argv[1]); // VIQR -> UTF-8 mode
	char *in_file_name = argv[2];
	char *out_file_name = argv[3];
	cout << "VIQR_UTF8, mode: " << mode << ", in_file: " << in_file_name << ", out_file: " << out_file_name << endl;

	int arr_length = sizeof(CHARSET_VIQR) / sizeof(CHARSET_VIQR[0]);

	if (mode == 1) {
		cout << "Converting VIQR to UTF8..." << endl;
		// Build VIQR -> UTF8 charset map
		map<const char*, const char*, cmp_str> viqr_utf8_map;
		for (int i=0; i<arr_length; i++) {
			viqr_utf8_map[CHARSET_VIQR[i]] = CHARSET_UTF8[i];
		}
		// Convert VIQR -> UTF8
		viqr_2_utf8(viqr_utf8_map, in_file_name, out_file_name);
		cout << "Convert VIQR to UTF8 done" << endl;
	}
	if (mode == 2) {
		cout << "Converting UTF8 to VIQR..." << endl;
		// Build UTF8 -> VIQR charset map
		map<const char*, const char*, cmp_str> utf8_viqr_map;
		for (int i=0; i<arr_length; i++) {
			utf8_viqr_map[CHARSET_UTF8[i]] = CHARSET_VIQR[i];
		}
		// Convert VIQR -> UTF8
		viqr_2_utf8(utf8_viqr_map, in_file_name, out_file_name);
		cout << "Convert VIQR to UTF8 done" << endl;
	}
	

    return 0;
}