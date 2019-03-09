#include <iostream>
#include <vector>
#include "libgithub/c++/services/repository_service.hpp"

int main(int argc, char **argv)
{
    github::repository_service svc;
    std::vector<github::repository> repos = svc.list();
    return 0;
}