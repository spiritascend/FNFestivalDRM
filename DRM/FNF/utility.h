#pragma once

#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "..\lib\json.hpp"
#include "..\lib\base64.h"

TArray<char> Conv_StringToCharArray(std::string InString) {
	TArray<char> Temp;
	for (int i = 0; i < InString.size(); i++)
		Temp.Add(InString[i]);
	return Temp;
}


std::string ExtractObjectFromBuff(std::string InBuff) {
	size_t startPos = InBuff.find("{");
	if (startPos != std::string::npos) {
		size_t endPos = InBuff.rfind("}");
		if (endPos != std::string::npos) {
			return InBuff.substr(startPos, endPos - startPos + 1);
		}
		else {
			return "";
		}
	}
	else {
		return "";
	}
}


std::vector<unsigned char> decodeBase64(const std::string& encoded) {
    const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    auto is_base64 = [](unsigned char c) {
        return (isalnum(c) || (c == '+') || (c == '/'));
        };

    auto find_base64_char = [&](unsigned char c) {
        return std::find(base64_chars.begin(), base64_chars.end(), c) - base64_chars.begin();
        };

    std::vector<unsigned char> decoded;
    int in_len = static_cast<int>(encoded.size());

    int i = 0;
    while (in_len && (encoded[i] != '=') && is_base64(encoded[i])) {
        unsigned char a = find_base64_char(encoded[i++]);
        unsigned char b = find_base64_char(encoded[i++]);
        unsigned char c = find_base64_char(encoded[i++]);
        unsigned char d = find_base64_char(encoded[i++]);

        unsigned char triple = (a << 2) | (b >> 4);
        decoded.push_back(triple);

        if (c != 64) {  // 64 is the ASCII code for '='
            triple = ((b & 0x0F) << 4) | (c >> 2);
            decoded.push_back(triple);
        }

        if (d != 64) {
            triple = ((c & 0x03) << 6) | d;
            decoded.push_back(triple);
        }
    }

    return decoded;
}



std::string arrayToHexString(const uint8_t* array, size_t size) {
	std::stringstream ss;
	ss << std::hex << std::setfill('0');

	for (size_t i = 0; i < size; ++i) {
		ss << std::setw(2) << static_cast<unsigned int>(array[i]);
	}

	return ss.str();
}




