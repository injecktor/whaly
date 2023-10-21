#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <vector>

#include "generation.hpp"

int main() {
	std::string contents;
	{
		std::stringstream contents_stream;
		std::fstream input("C:\\Users\\p2282\\OneDrive\\Desktop\\new language.txt", std::ios_base::in);
		contents_stream << input.rdbuf();
		contents = contents_stream.str();
	}
	Tokenizer tokenizer(std::move(contents));
	std::vector<Token> tokens = tokenizer.tokenize();

	Parser parser(std::move(tokens));
	std::optional<NodeExit> tree = parser.parse();

	if (!tree.has_value()) {
		std::cerr << "No exit statement found" << std::endl;
		exit(EXIT_FAILURE);
	}

	Generator generator(tree.value());
	{
		std::fstream file("C:\\Users\\p2282\\OneDrive\\Desktop\\Assembled code.txt", std::ios::out);
		file << generator.generate();
	}
	return 0;
}