/*
    Boson v1.5 - Grammar analyzer generator

        Author: ict
        Email:  ictxiangxin@hotmail.com
        Site:   https://github.com/ictxiangxin/boson

    File: "lexer.hpp"
    These codes ware generated by the boson C++ code generator.
*/

#ifndef _BOSON_LEXER_HPP_
#define _BOSON_LEXER_HPP_

#include <functional>
#include <vector>
#include <set>
#include <unordered_map>
#include "token.hpp"

namespace boson {
    class Tokenizer {
    public:
        using lexical_function = std::function<std::string &(std::string &)>;

        Tokenizer() = default;

        std::vector<Token> &token_list() {
            return this->_token_list;
        }

        void skip() {
            this->_skip = true;
        }

        void newline() {
            this->_line++;
        }

        int error_index() const {
            return _error_index;
        }

        int no_error_index() const {
            return _no_error_index;
        }

        int tokenize(std::string text) {
            this->_token_list.clear();
            this->_line = 1;
            int state = this->_start_state;
            std::string token_string{};
            int index = 0;
            while (index < text.length()) {
                char character = text[index];
                index++;
                bool get_token = false;
                if (this->_non_greedy_state_set.count(state)) {
                    get_token = true;
                }
                if (this->_compact_move_table.count(state)) {
                    std::vector<std::tuple<int, std::set<char>, std::vector<std::tuple<char, char>>, int>> state_move_table = this->_compact_move_table[state];
                    unsigned long i;
                    for (i = 0; i < state_move_table.size(); i++) {
                        std::tuple<int, std::set<char>, std::vector<std::tuple<char, char>>, int> compact_table = state_move_table[i];
                        int attribute = std::get<0>(compact_table);
                        std::set<char> &character_set = std::get<1>(compact_table);
                        std::vector<std::tuple<char, char>> &range_list = std::get<2>(compact_table);
                        int next_state = std::get<3>(compact_table);
                        bool condition;
                        if (attribute == 2) {
                            condition = !character_set.count(character);
                            for (auto & range : range_list) {
                                condition &= character < std::get<0>(range) || character > std::get<1>(range);
                            }
                        } else {
                            condition = character_set.count(character);
                            if (attribute == 1 && this->_character_set.count(character) == 0) {
                                condition = true;
                            }
                            for (auto & range : range_list) {
                                if (condition || (std::get<0>(range) <= character && character <= std::get<1>(range))) {
                                    condition = true;
                                    break;
                                }
                            }
                        }
                        if (condition) {
                            token_string += character;
                            state = next_state;
                            break;
                        }
                    }
                    if (i == state_move_table.size()) {
                        if (this->_end_state_set.count(state)) {
                            get_token = true;
                        } else {
                            this->_error_index = index - 1;
                            return this->_error_index;
                        }
                    }
                } else {
                    if (this->_end_state_set.count(state)) {
                        get_token = true;
                    } else {
                        this->_error_index = index - 1;
                        return this->_error_index;
                    }
                }
                if (get_token) {
                    this->_generate_token(state, token_string);
                    token_string = "";
                    state = this->_start_state;
                    index--;
                }
            }
            if (this->_end_state_set.count(state)) {
                this->_generate_token(state, token_string);
            } else {
                this->_error_index = index - 1;
                return this->_error_index;
            }
            this->_token_list.emplace_back("", this->_line, "$");
            return this->_error_index;
        }

        void register_function(std::string &function_name, lexical_function &function) {
            this->_lexical_function[function_name] = function;
        }

    private:
        std::vector<Token> _token_list{};
        int _line = 1;
        int _error_index = -1;
        int _no_error_index = -1;
        bool _skip = false;
        std::unordered_map<int, std::vector<std::tuple<int, std::set<char>, std::vector<std::tuple<char, char>>, int>>> _compact_move_table = {
            {0, {
                {0, {'\x5f'}, {{'\x41', '\x5a'}, {'\x61', '\x7a'}}, 1},
                {0, {}, {{'\x30', '\x39'}}, 2},
                {0, {'\x20', '\x09'}, {}, 3},
                {0, {'\x0d'}, {}, 4},
                {0, {'\x0a'}, {}, 5},
                {0, {'\x3d'}, {}, 6},
                {0, {'\x28'}, {}, 7},
                {0, {'\x29'}, {}, 8},
                {0, {'\x2c'}, {}, 9},
                {0, {'\x2b'}, {}, 10},
                {0, {'\x2d'}, {}, 11},
                {0, {'\x2a'}, {}, 12},
                {0, {'\x2f'}, {}, 13},
                {0, {'\x5e'}, {}, 14}
            }},
            {15, {
                {0, {}, {{'\x30', '\x39'}}, 15}
            }},
            {4, {
                {0, {'\x0a'}, {}, 5}
            }},
            {3, {
                {0, {'\x20', '\x09'}, {}, 3}
            }},
            {2, {
                {0, {}, {{'\x30', '\x39'}}, 2},
                {0, {'\x2e'}, {}, 15}
            }},
            {1, {
                {0, {'\x5f'}, {{'\x30', '\x39'}, {'\x41', '\x5a'}, {'\x61', '\x7a'}}, 1}
            }}
        };
        std::set<char> _character_set = {'\x4a', '\x69', '\x5e', '\x48', '\x5f', '\x76', '\x34', '\x49', '\x41', '\x43', '\x72', '\x0a', '\x33', '\x54', '\x68', '\x6a', '\x2a', '\x7a', '\x2f', '\x32', '\x2c', '\x09', '\x46', '\x2b', '\x73', '\x0d', '\x6e', '\x39', '\x4e', '\x28', '\x20', '\x38', '\x6b', '\x74', '\x47', '\x70', '\x50', '\x44', '\x77', '\x53', '\x45', '\x67', '\x78', '\x58', '\x63', '\x42', '\x56', '\x31', '\x71', '\x52', '\x79', '\x35', '\x3d', '\x59', '\x6d', '\x4f', '\x6c', '\x65', '\x4d', '\x61', '\x37', '\x62', '\x6f', '\x4b', '\x75', '\x5a', '\x51', '\x36', '\x29', '\x64', '\x4c', '\x57', '\x2d', '\x55', '\x66', '\x2e', '\x30'};
        int _start_state = 0;
        std::set<int> _end_state_set = {1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
        std::unordered_map<int, std::string> _lexical_symbol_mapping = {
            {1, "t_symbol"},
            {2, "t_number"},
            {3, "skip"},
            {5, "newline"},
            {6, "!symbol_1"},
            {7, "!symbol_2"},
            {8, "!symbol_3"},
            {9, "!symbol_4"},
            {10, "!symbol_5"},
            {11, "!symbol_6"},
            {12, "!symbol_7"},
            {13, "!symbol_8"},
            {14, "!symbol_9"},
            {15, "t_number"}
        };
        std::set<int> _non_greedy_state_set = {};
        std::unordered_map<std::string, std::vector<std::string>> _symbol_function_mapping = {
            {"t_symbol", {}},
            {"t_number", {}},
            {"skip", {"skip"}},
            {"newline", {"skip","newline"}}
        };
        std::unordered_map<std::string, lexical_function> _lexical_function{};

        std::string &_invoke_lexical_function(std::string &symbol, std::string &token_string) {
            this->_skip = false;
            if (this->_symbol_function_mapping.count(symbol)) {
                for (const auto& function : this->_symbol_function_mapping[symbol]) {
                    if (this->_lexical_function.count(function)) {
                        token_string = this->_lexical_function[function](token_string);
                    } else if (function == "skip") {
                        this->skip();
                    } else if (function == "newline") {
                        this->newline();
                    }
                }
            }
            return token_string;
        }

        void _generate_token(int state, std::string &token_string) {
            std::string symbol;
            if (this->_lexical_symbol_mapping.count(state)) {
                symbol = this->_lexical_symbol_mapping[state];
            } else {
                symbol = "!symbol";
            }
            token_string = this->_invoke_lexical_function(symbol, token_string);
            if (!this->_skip) {
                this->_token_list.emplace_back(token_string, this->_line, symbol);
            }
        }
    };
}

#endif
