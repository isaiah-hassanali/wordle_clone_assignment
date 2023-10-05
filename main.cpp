/**
 * Author: Isaiah Hassanali
 * Student Number: 251192094
 * Description: This class implements the main function, which creates an instance of the Wordle class to run the application.
 * Date: October 4, 2023
 */


#include <Wt/WApplication.h>
#include "wordle.h"

/**
 * @brief Main function that creates application instances.
 * @param argc number of arguments
 * @param argv arguments
 * @return status code
 */
int main(int argc, char **argv) {
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment &env) {
        return std::make_unique<Wordle>(env);
    });
}
