#include <iostream>
#include <vector>
#include "libgithub/c++/resources/repository.h"

int main(int argc, char **argv)
{
    std::vector<github::repository> repos = github::repository::list();
    return 0;
}