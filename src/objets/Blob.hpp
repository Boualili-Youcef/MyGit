#pragma once

#include <string>

namespace objects
{
    class Blob
    {
        public:
            Blob(const std::string &content);

            // Les getters
            std::string getHash() const;
            std::string getContent() const;

            // Stocker le blob dans .myGit/objects
            bool store() const;
        private:
            std::string content;
            std::string hash;
    };
}