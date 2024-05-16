#include "GlfwOcctView.h"

int main(int, char**)
{
    GlfwOcctView anApp;

    try
    {
        anApp.run();
    }
    catch (const std::runtime_error& theError)
    {
        std::cerr << theError.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
