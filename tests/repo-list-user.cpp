#include <iostream>
#include <vector>
#include "libgithub/c++/services/repository_service.hpp"
#include "libgithub/c++/exceptions/api_error.hpp"
#include "libgithub/c++/exceptions/curl_exception.hpp"

int main(int argc, char **argv)
{
  try
  {
    github::repository_service svc;
    std::vector<github::repository> repos = svc.list("emcrisostomo");
  }
  catch (const github::curl_exception& curl_error)
  {
    std::cerr << curl_error.what() << "\n";
  }
  catch (const github::api_error& api_error)
  {
    std::cerr << "Unexpected status code: " << api_error.get_status_code() << "\n";

    std::string err(api_error.what());
    if (err.length()) std::cerr << "Error message: " << err << "\n";
  }
  catch (const std::runtime_error& runtime_error)
  {
    std::cerr << runtime_error.what() << "\n";
  }
  catch (...)
  {
    std::cerr << "An unknown error has occurred.\n";
  }

  return 0;
}