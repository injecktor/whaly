#include "includes.hpp"

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
	std::optional<NodeProg> prog = parser.parse_prog();

	if (!prog.has_value()) {
		std::cerr << "Invalid program" << std::endl;
		exit(EXIT_FAILURE);
	}

	Generator generator(prog.value());
	{
		std::fstream file("C:\\Users\\p2282\\OneDrive\\Desktop\\Assembled code.txt", std::ios::out);
		file << generator.gen_prog();
	}
	return 0;
}