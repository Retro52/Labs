//
// Created by Anton on 20.03.2022.
//

#include <iostream>
#include "Parser.h"

/***
 * @deprecated
 */
void Parser::parse(const std::string &command, std::vector<std::string> &args)
{
    int indexOfSpace = command.find(' ');
    std::string com = command.substr(0, indexOfSpace);
    std::cout << com << std::endl;
}