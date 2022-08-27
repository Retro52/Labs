#define GLEW_STATIC

#include "Core/Application.h"

#include "Logging/easylogging++.h"
INITIALIZE_EASYLOGGINGPP;

/**
 * Program entry point
 * @param argc command-line arguments count
 * @param argv command-line arguments
 * @return exit code
 */
int main(int argc, char ** argv)
{
    Application::Create();
    return Application::Run();
}
