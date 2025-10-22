std::string cmd;
        std::cout << "Enter a command (h for help) > ";
        std::cin >> cmd;
        std::cout << std::endl;

        if (cmd == "q") {
            this->Quit = true;
        } else if (cmd == "h") {
            std::cout << "Available preround commands:" << std::endl
                      << "h -> get a list of available commands" << std::endl
                      << "q -> quit the game" << std::endl
                      << "r -> start a new round" << std::endl
                      << "s -> print game scoreboard" << std::endl;
        } else if (cmd == "r") {
            this->Active = true;
            this->runRound();
        } else if (cmd == "s") {
            this->printScoreboard();
        } else if (cmd == "p") {
            std::cout << this->NumPlayers << std::endl;
        } else {
            std::cout << "Unknown command" << std::endl;
        }