#include <unordered_map>
#include <vector>
#include <string>

namespace atl
{

static constexpr uint8_t ALPHABET_SIZE = 26;

template<typename T>
struct Trie
{
public:
    void add_word(std::string word)
    {
        for(int i = 0; i < word.size(); ++i)
        {
        }
    }
private:
    std::unordered_map<char, std::vector<Trie>> children;
    bool word{false};
    char value[ALPHABET_SIZE];
};

}

