#include "operation_strategy.h"

#include <vector>
#include <memory>

class ColumnOperationContext
{
private:
    std::unique_ptr<OperationStrategy> strategy;

public:
    void SetStrategy(std::unique_ptr<OperationStrategy>&& newStrategy)
    {
        // take ownership of the smartpointer
        strategy = std::move(newStrategy);
    }

    std::vector<int> executeStrategy(const std::vector<int>& col1, const std::vector<int>& col2)
    {
        if (strategy)
        {
            return strategy->ExecuteColumnAlgorithm(col1, col2);
        }
        return {};
    }
};
