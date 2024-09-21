#include <stack>
#include <unordered_map>
#include <unordered_set>

namespace CherryMath
{

// acyclic graphs -> no cycles, also they are directed graphs


inline void dfs_stack(std::unordered_map<char, std::vector<char>>& graph, char starting_node)
{
    std::stack<char> nodes;
    std::unordered_set<char> visited;
    visited.insert(starting_node);
    nodes.push(starting_node);

    while(!nodes.empty())
    {
        char current = nodes.top();
        nodes.pop();
        // work with it
        std::cout << current << std::endl;

        for(const auto& child : graph[current])
        {
            nodes.push(child);
        }
    }
}

inline void dfs_recursive(std::unordered_map<char, std::vector<char>>& graph, char starting_node)
{
    std::cout << starting_node << std::endl;

    for(const auto& node : graph[starting_node])
    {
        dfs_recursive(graph, node);
    }
}

inline void bfs(std::unordered_map<char, std::vector<char>>& graph, char starting_node)
{
    std::queue<char> nodes_queue;
    nodes_queue.push(starting_node);
    std::cout << starting_node << std::endl;

    while(!nodes_queue.empty())
    {
        char current = nodes_queue.front();
        nodes_queue.pop();

        for(const auto& node : graph[current])
        {
            nodes_queue.push(node);
        }
    }

}

inline bool has_path(std::unordered_map<char, std::vector<char>>& graph, char source, char destination)
{
    static std::vector<bool> visited(graph.size(), false);
    if(visited[source]) return false;
    else if (source == destination) return true;
    visited[source] = true;
    for(const auto& node : graph[source])
    {
        if(has_path(graph, node, destination))
        {
            return true;
        }
    }
    return false;
}

} // namespace CherryMath

