#pragma once

/*
 * TODO(Alex): Add API for runtine disabling/enabling of the categories. Maybe with IMGUI
 */

#include <project_definitions.h>
#include <Singleton.h>

// std::map can outperform std::unordered_map when the number of elements is small
// Range queries (lower/upper bound)
#include <map>

class LogManager : public Singleton<LogManager>
{
public:

    LogManager() noexcept
    {
        for (int i = 0; i < static_cast<int>(ELogCategory::AutoCount); ++i)
        {
            logCategoryStates[static_cast<ELogCategory>(i)] = ELogCategoryState::Enabled;
        }
    }

    void EnableCategory(ELogCategory category)
    {
        logCategoryStates[category] = ELogCategoryState::Enabled;
    }

    void DisableCategory(ELogCategory category)
    {
        logCategoryStates[category] = ELogCategoryState::Disabled;
    }

    bool IsCategoryEnabled(ELogCategory category) const
    {
        return logCategoryStates.at(category) == ELogCategoryState::Enabled;
    }

    bool IsCategoryDisabled(ELogCategory category) const
    {
        return logCategoryStates.at(category) == ELogCategoryState::Disabled;
    }
private:

    std::map<ELogCategory, ELogCategoryState> logCategoryStates;
};

