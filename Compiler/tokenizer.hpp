#pragma once

enum class TokenType {
	exit,
	int_lit,
	semi,
	open_paren,
	close_paren,
	let,
	ident,
	eq
};

struct Token {
	TokenType type;
	std::optional<std::string> value{};
};

class Tokenizer {
public:
	inline Tokenizer(std::string src)
		: m_src(std::move(src)), m_index(0) {};

	inline std::vector<Token> tokenize() 
	{
		m_index = 0;
		std::vector<Token> tokens;
		std::string buf;

		while (peek().has_value())
		{
			if (std::isalpha(peek().value())) {
				buf.push_back(consume());
				while (peek().has_value() && std::isalnum(peek().value())) {
					buf.push_back(consume());
				}
				if (buf == "exit") {
					tokens.push_back({ .type = TokenType::exit });
					buf.clear();
					continue;
				}
				else if (buf == "let") {
					tokens.push_back({ .type = TokenType::let });
					buf.clear();
					continue;
				}
				else {
					tokens.push_back({ .type = TokenType::ident, .value = buf });
					buf.clear();
					continue;
				}
			}
			else if (std::isdigit(peek().value())) {
				buf.push_back(consume());
				while (peek().has_value() && std::isdigit(peek().value())) {
					buf.push_back(consume());
				}
				tokens.push_back({ .type = TokenType::int_lit, .value = buf });
				buf.clear();
			}
			else if (peek().value() == ';') {
				consume();
				tokens.push_back({ .type = TokenType::semi });
				continue;
			}
			else if (peek().value() == '(') {
				consume();
				tokens.push_back({ .type = TokenType::open_paren });
				continue;
			}
			else if (peek().value() == ')') {
				consume();
				tokens.push_back({ .type = TokenType::close_paren });
				continue;
			}
			else if (peek().value() == '=') {
				consume();
				tokens.push_back({ .type = TokenType::eq });
				continue;
			}
			else if (std::isspace(peek().value())) {
				consume();
				continue;
			}
			else {
				std::cerr << "Mistake!" << std::endl;
				exit(EXIT_FAILURE);
			}
		}
		m_index = 0;
		return tokens;
	}

private:

	std::optional<char> peek(int offset = 0) const
	{
		if (m_index + offset >= m_src.length()) {
			return {};
		}
		else {
			return m_src.at(m_index + offset);
		}
	}

	char consume() 
	{
		return m_src.at(m_index++);
	}

	size_t m_index;
	const std::string m_src;
};