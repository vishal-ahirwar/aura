#include "extractor.h"
#include <format>
#include <list>
#include <log/log.h>
#include <regex>
#include <sstream>
#include <string.h>
#include <unordered_set>

std::string normalize(const std::string& s) {
	std::string out;
	for (char c : s) {
		if (c == '-' || c == '_') out += ' ';
		else out += std::tolower(c);
	}
	return out;
}

std::vector<std::string> tokenize(const std::string& s) {
	std::istringstream iss(s);
	std::vector<std::string> tokens;
	std::string token;
	while (iss >> token) tokens.push_back(token);
	return tokens;
}

int fuzzy_score(const std::string& query, const std::string& target) {
	auto qTokens = tokenize(normalize(query));
	auto tTokens = tokenize(normalize(target));

	int score = 0;
	for (const auto& qt : qTokens) {
		for (const auto& tt : tTokens) {
			if (qt == tt) score += 10;
			else if (tt.find(qt) == 0) score += 6;
			else if (tt.find(qt) != std::string::npos) score += 3;
		}
	}

	return score;
}

std::vector<std::pair<std::string, std::regex>> patterns = {
  {"find_package", std::regex(R"(find_package\([^\)]+\))", std::regex_constants::icase)},
  {"target_link_libraries", std::regex(R"(target_link_libraries\([^)]*\))", std::regex_constants::icase)},
  {"find_path", std::regex(R"(find_path\([^\)]+\))", std::regex_constants::icase)},
  {"target_include_directories", std::regex(R"(target_include_directories\([^)]*\))", std::regex_constants::icase)}};

const Packages& Extractor::getPackages() const { return mPackages; };
#include <regex>

std::string formatToOneLine(const std::string& multiline)
{
	std::regex newlineAndIndentRegex(R"(\s*\n\s*)"); // Matches newlines and surrounding spaces
	return std::regex_replace(multiline, newlineAndIndentRegex, " ");
}
int compareWeight(const std::string& a, const std::string& b)
{
	std::string s1 = a;
	std::string s2 = b;

	// Convert both to lowercase
	std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

	int weight = 0;
	size_t minLen = std::min(s1.length(), s2.length());

	for (size_t i = 0; i < minLen; ++i) {
		if (s1[i] == s2[i])
			++weight;
		else
			--weight;
	}

	return ((a.length() + b.length())) / weight;
}
std::string getName(const std::string& findPackgeString)
{
	auto start = findPackgeString.find("(");
	auto end = findPackgeString.find(" ");
	if (start == std::string::npos || end == std::string::npos)
		return "";
	return findPackgeString.substr(start + 1, end - start);
}
// TODO FIX THIS:/
Packages Extractor::extract(const std::string& vcpkgLog, std::string package)
{
	// Regex for find_package or find_path blocks
	std::regex blockRegex(R"((find_(package|path)\([^\)]+\))\s+([^\n]*target_(link_libraries|include_directories)[^\)]+\)))");

	std::smatch match;
	std::string::const_iterator searchStart(vcpkgLog.cbegin());

	while (std::regex_search(searchStart, vcpkgLog.cend(), match, blockRegex)) {
		std::string declaration = match[1].str();
		std::string targetLine = match[3].str();

		// Extract name from find_(package|path)(NAME ...)
		std::regex nameRegex(R"(\(([^)\s]+))");
		std::smatch nameMatch;
		if (std::regex_search(declaration, nameMatch, nameRegex)) {
			std::string name = nameMatch[1].str();
			if (!mPackages.contains(name)) {
				mPackages[name] = {formatToOneLine(declaration), formatToOneLine(targetLine)};
			}
		}
		searchStart = match.suffix().first;
	}
	std::vector<std::pair<std::string, int>> scored;

	for (const auto& [name, data] : mPackages) {
		int score = fuzzy_score(package, name);
		if (score >= 6)
			scored.emplace_back(name, score);
	}

	std::sort(scored.begin(), scored.end(), [](auto& a, auto& b) {
	    return b.second > a.second;
	});

	Packages result;
	for (auto& [name, _] : scored)
		result[name] = mPackages.at(name);
	return result;
};
