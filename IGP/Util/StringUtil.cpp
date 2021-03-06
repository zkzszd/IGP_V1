﻿#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <locale.h>

#include "StringUtil.h"

namespace zkzszd
{

	bool UtilString::stringEndsWith(const std::string &str, const std::string &end)
	{
		return
			(end.length() <= str.length()) &&
#if __GNUC__ == 2
			(str.compare(end, str.length() - end.length(), end.length()) == 0);
#else
			(str.compare(str.length() - end.length(), end.length(), end) == 0);
#endif
	}

	bool UtilString::stringStartsWith(const std::string &str, const std::string &start) {
		return
			(start.length() <= str.length()) &&
#if __GNUC__ == 2
			(str.compare(start, 0, start.length()) == 0);
#else
			(str.compare(0, start.length(), start) == 0);
#endif
	}

	void UtilString::appendNumber(std::string &str, unsigned int n) {
		int len;
		if (n > 0) {
			len = 0;
			for (unsigned int copy = n; copy > 0; copy /= 10) {
				len++;
			}
		}
		else {
			len = 1;
		}

		str.append(len, '\0');
		char *ptr = (char*)str.data() + str.length() - 1;
		for (int i = 0; i < len; ++i) {
			*ptr-- = '0' + n % 10;
			n /= 10;
		}
	}

	void UtilString::append(std::string &str, const std::vector<std::string> &text) {
		std::size_t len = str.length();
		for (std::vector<std::string>::const_iterator it = text.begin(); it != text.end(); ++it) {
			len += it->length();
		}
		str.reserve(len);
		for (std::vector<std::string>::const_iterator it = text.begin(); it != text.end(); ++it) {
			str += *it;
		}
	}

	void UtilString::stripWhiteSpaces(std::string &str) {
		std::size_t counter = 0;
		std::size_t length = str.length();
		while (counter < length && std::isspace((unsigned char)str[counter])) {
			counter++;
		}
		str.erase(0, counter);
		length -= counter;

		std::size_t r_counter = length;
		while (r_counter > 0 && std::isspace((unsigned char)str[r_counter - 1])) {
			r_counter--;
		}
		str.erase(r_counter, length - r_counter);
		while (str.length() > 3)
		{
			if ((str[0] == '\xE3') && (str[1] == '\x80') && (str[2] == '\x80'))
			{
				str.erase(0, 3); //去全角空格
			}
			else
			{
				break;
			}
		}
	}
	std::string UtilString::stripAllWhiteSpaces(const std::string str)
	{
		std::size_t counter = 0;
		std::size_t length = str.length();
		char *tem = new char[length + 1];
		memset(tem, 0, length + 1);
		int i = 0;
		for (i = 0; i < length; i++) {
			if (!std::isspace((unsigned char)str[i]))
			{
				tem[counter++] = str[i];
			}
		}
		std::string result = tem;
		delete[]tem;
		return result;
	}
	std::vector<std::string> UtilString::split(const std::string &str, const std::string &delimiter)
	{
		std::vector<std::string> result;
		std::size_t start = 0;
		std::size_t index = str.find(delimiter);
		while (index != std::string::npos)
		{
			result.push_back(str.substr(start, index - start));
			start = index + delimiter.length();
			index = str.find(delimiter, start);
		}
		result.push_back(str.substr(start, index - start));
		return result;
	}

	std::string UtilString::printf(const std::string &format, const std::string &arg0) {
		int index = (int)format.find("%s");
		if (index == -1) {
			return format;
		}
		return format.substr(0, index) + arg0 + format.substr(index + 2);
	}

	std::string UtilString::doubleToString(double value) {
		char buf[100];
		setlocale(LC_NUMERIC, "C");
		std::sprintf(buf, "%f", value);
		return buf;
	}

	std::string UtilString::intToString(int value) {
		char buf[100];
		setlocale(LC_NUMERIC, "C");
		std::sprintf(buf, "%d", value);
		return buf;
	}

	std::string UtilString::longToString(long value) {
		char buf[100];
		setlocale(LC_NUMERIC, "C");
		std::sprintf(buf, "%ld", value);
		return buf;
	}

	double UtilString::stringToDouble(const std::string &str, double defaultValue) {
		if (!str.empty()) {
			setlocale(LC_NUMERIC, "C");
			return std::atof(str.c_str());
		}
		else {
			return defaultValue;
		}
	}

	int UtilString::stringToInteger(const std::string &str, int defaultValue) {
		if (str.empty()) {
			return defaultValue;
		}
		if (!std::isdigit(str[0]) && (str.length() == 1 || str[0] != '-' || !std::isdigit(str[1]))) {
			return defaultValue;
		}

		for (std::size_t i = 1; i < str.length(); ++i) {
			if (!std::isdigit(str[i])) {
				return defaultValue;
			}
		}

		return std::atoi(str.c_str());
	}

	std::string UtilString::replaceAll(std::string& src_str, const std::string &old_value, const std::string& new_value)
	{
		while (true)
		{
			std::string::size_type   pos(0);
			if ((pos = src_str.find(old_value)) != std::string::npos)
				src_str.replace(pos, old_value.length(), new_value);
			else   break;
		}
		return   src_str;
	}

	std::string UtilString::replaceAllDistinct(std::string& src_str, const std::string& old_value, const std::string& new_value)
	{
		for (std::string::size_type pos(0); pos != std::string::npos; pos += new_value.length())
		{
			if ((pos = src_str.find(old_value, pos)) != std::string::npos)
				src_str.replace(pos, old_value.length(), new_value);
			else   break;
		}
		return  src_str;
	}
}
