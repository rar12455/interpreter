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

#include <cctype>
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

// readline libary for the core of interpreter;
#include <readline/history.h>
#include <readline/readline.h>

// ANSI Color code definitions;
#define RED_m "\033[31m"
#define GREEN_m "\033[32m"
#define YELLOW_m "\033[33m"
#define RESET_m "\033[0m"

enum class token_type // t_var means it's a token type
{
        t_number,
        t_plus,
        t_minus,
        t_multiply,
        t_divide,
        t_end
};

struct token
{
        token_type type;
        char     **value;
};

void
do_math(auto numbers_vector, auto math_operator_vector)
{
        // std::cout << "test" << std::endl;
        char math_operator_m;
        for (const auto &v : math_operator_vector)
        {
                if (v == '+')
                {
                        char math_operator_m = '+';
                }
        }
        std::cout << math_operator_m;
}

void
parse_input(int iterator)
{
        // declare the vectors
        std::vector<int>  numbers       = {};
        std::vector<char> math_operator = {};
        if (std::isdigit(iterator))
        {
                iterator = iterator - '0'; // convert it to an actual int
                numbers.push_back(iterator);
                do_math(math_operator, numbers);
                for (const auto &v : numbers)
                {
                        std::cout << "number vector lookup: " << v << '\n';
                }
        }
        else
        {
                math_operator.push_back(iterator);
                do_math(math_operator, numbers);
                for (const auto &v : math_operator)
                {
                        std::cout << "math_operator vector lookup: " << v
                                  << std::endl;
                }
        }
}

void
scan_input(auto argv)
{
        // Wrap the raw pointer in a string_view so the loop knows the
        // boundaries
        // Note: Ensure argv[2] actually exists before accessing it!
        std::string_view arg_view(argv[1]);
        for (const auto &i : arg_view)
        {
                if (i == ' ') // ignore whitespace
                {
                        continue;
                }
                if (i != '+' && i != '*' && i != '/' && i != '-' &&
                    !std::isdigit(i)) // ignore non-math spesific chars
                {
                        continue;
                }
                //     std::cout << "argv: " << i << std::endl; // test to see
                //     output
                parse_input(i);
        }
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

void
exec_system_function(std::string system_command)
{
        std::unique_ptr<FILE, decltype(&pclose)> pipe(
            popen(system_command.c_str(), "r"), pclose);

        if (!pipe)
        {
                std::cout << "Failed to run command.\n";
                return;
        }

        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr)
        {
                std::cout << buffer;
        }
}

bool
eval(std::string &__user_input)
{
        if (__user_input == "exit")
                return false;
        ;

        if (!__user_input.empty())
                add_history(__user_input.c_str());

        if (__user_input == "clear")
        {
                std::cout << "\033[2J\033[H";
        }
        std::string prefix_system = "sys:";
        if (__user_input == "help")
                print_repl_help();
        if (__user_input.starts_with(prefix_system))
        {
                __user_input.erase(0, prefix_system.length());
                exec_system_function(__user_input);
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

                char *line = readline("\001\033[1;32m\002>> \001\033[0m\002");

                if (!line)
                        break; // Ctrl+D

                std::string input(line);
                free(line);
                if (!eval(input))
                        break;
        }
}

int
main(int argc, char **argv)
{
        if (argc < 2)
        {
                std::cout << RED_m
                          << "No argument found, switching to REPL mode"
                          << RESET_m << std::endl;

                repl();
        }
        else
        {

                scan_input(argv);
        }

        return 0;
}
