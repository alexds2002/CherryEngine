#pragma once

#include <project_definitions.h>
#include <Singleton.h>

#include <map>

class LogManager : Singleton<LogManager>
{
public:

    LogManager() noexcept
    {
        for (int i = 0; i < static_cast<int>(ELogCategory::AutoCount); ++i)
        {
            logCategoryStates[static_cast<ELogCategory>(i)] = ELogCategoryState::Enabled;
        }
    }

    void EnableCategory(ELogCategory category) noexcept
    {
        logCategoryStates[category] = ELogCategoryState::Enabled;
    }

    void DisableCategory(ELogCategory category) noexcept
    {
        logCategoryStates[category] = ELogCategoryState::Disabled;
    }

    bool IsCategoryEnabled(ELogCategory category) const noexcept
    {
        return logCategoryStates.at(category) == ELogCategoryState::Enabled;
    }
private:

    std::map<ELogCategory, ELogCategoryState> logCategoryStates;
};

