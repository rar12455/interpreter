/*
 * Copyright (C) 2026 rar <rarSS@proton.me>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * version 2 any later version.
 *
 * This program is distributed in the hope that it will be WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cctype> /* for isdigit, isspace, isalpha */
#include <iostream>
#include <string>
#include <vector>

enum class token_type /* t_var means it's a token type */
{
        t_number,
        t_plus,
        t_minus,
        t_multiply,
        t_divide,
        t_left_parenthesis,
        t_right_parenthesis,
        t_identifier, /* for sin,cos etc. */
        t_end
};

struct token
{
        token_type  type;
        std::string value;
};

std::vector<token>
tokenize(const std::string &input)
{
        std::vector<token> tokens;
        for (size_t i = 0; i < input.length(); i++)
        {
                char c = input[i];

                if (std::isspace(c))
                        continue; /* skip spaces */

                if (std::isdigit(c))
                {
                        std::string num;
                        while (i < input.length() &&
                               (std::isdigit(input[i]) || input[i] == '.'))
                        {
                                num += input[i++];
                        }
                        i--; /* Correct the index after the while loop */
                        tokens.push_back({token_type::t_number, num});
                }
                else if (std::isalpha(c))
                {
                        std::string ident;
                        while (i < input.length() && std::isalnum(input[i]))
                        {
                                ident += input[i++];
                        }
                        i--; /* Correct the index after the while loop */
                        tokens.push_back({token_type::t_identifier, ident});
                }
                else if (c == '+')
                        tokens.push_back({token_type::t_plus, "+"});
                else if (c == '-')
                        tokens.push_back({token_type::t_minus, "-"});
                else if (c == '*')
                        tokens.push_back({token_type::t_multiply, "*"});
                else if (c == '/')
                        tokens.push_back({token_type::t_divide, "/"});
                else if (c == '(')
                        tokens.push_back({token_type::t_left_parenthesis, "("});
                else if (c == ')')
                        tokens.push_back(
                            {token_type::t_right_parenthesis, ")"});
        }
        return tokens;
}

void
print_repl_help()
{
        std::cout << "REPL - help:" << std::endl;
        std::cout << "1- you can do masic math like: 2 + 2 -> will return 4."
                  << std::endl;
        std::cout
            << "2- you can invoke math functions like sin with value: sin(30) "
               "-> will return 1/2"
            << std::endl;
}

bool
eval(const std::string &__user_input)
{
        if (__user_input == "exit")
                return false;
        if (__user_input == "help")
                print_repl_help();

        std::vector<token> tokens = tokenize(__user_input);

        /* For now, let's just print the tokens to verify it works */
        std::cout << "Tokens found: " << tokens.size() << std::endl;
        for (const auto &t : tokens)
        {
                std::cout << "  Type: " << (int)t.type
                          << " | Value: " << t.value << std::endl;
        }
        return true;
}

void
repl()
{
        std::string user_input;
        std::cout
            << "Welcome to the REPL interface. For help, you can type string "
               "literal 'help'."
            << std::endl;
        while (true)
        {
                std::cout << ">> ";
                std::getline(std::cin, user_input);
                if (!eval(user_input))
                        break;
                std::cout << "read: " << user_input << std::endl;
        }
}

int
main()
{
        repl();
        return 0;
}
