#include <project_definitions.h>
#include <map>

/*
 * Automatically linked from CMake.
 * creates the global instance of the avalable Log categories
 * and their states(Enabled, Disabled...)
 */

/* global list of all the categories and their states */
std::map<ELogCategory, ELogCategoryState> gLogCategoryStates;
