#include <cstdlib>
#include <exception>

int main(int /*argc*/, char** /*argv[]*/)
{
  try
  {

  }
  catch(const std::exception& e)
  {
    return EXIT_FAILURE;
  }
  catch(...)
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
