/*
 * Copyright (C) 2004-2013 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __STRING_UTIL_H__
#define __STRING_UTIL_H__

#include <vector>
#include <string>

class StringUtil {

private:
	StringUtil();

public:
	static bool stringStartsWith(const std::string &str, const std::string &start);
	static bool stringEndsWith(const std::string &str, const std::string &end);

	static void appendNumber(std::string &str, unsigned int n);
	static void append(std::string &str, const std::vector<std::string> &buffer);
	static void stripWhiteSpaces(std::string &str);
	static std::string stripAllWhiteSpaces(const std::string str);

	static std::vector<std::string> split(const std::string &str, const std::string &delimiter);

	static std::string printf(const std::string &format, const std::string &arg0);

	static std::string doubleToString(double value);
	static std::string intToString(int value);
	static std::string longToString(long value);
	static double stringToDouble(const std::string &value, double defaultValue);
	static int stringToInteger(const std::string &str, int defaultValue);

	/*把原来字符串中所有old_value（包括替换后产生的）替换成新的字符串（替换后的字符串不会再有old_value）*/
	/* pamera: 12212 12 21   结果：22211   */
	/* src_str 原字符串会被替换 */
	static std::string replaceAll(std::string& src_str,const std::string &old_value,const std::string& new_value);
	/*把原来字符串中所有原old_value替换成新的字符串（替换后的字符串可能还会有新的old_value）*/
	/* pamera: 12212 12 21   结果：21221   */
	/* src_str 原字符串会被替换 */
	static std::string replaceAllDistinct(std::string& src_str, const std::string& old_value, const std::string& new_value);
};

#endif /* __STRING_UTIL_H__ */
