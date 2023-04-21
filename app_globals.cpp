/*
    Copyright 2023 Cleverson S A

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "app_globals.hpp"

AppGlobals * AppGlobals::_me = 0;

void AppGlobals::setEnableObjDelLog(const bool opt)
{
    _enableObjDelLog = opt;
}

bool AppGlobals::getEnableObjDelLog() const
{
    return _enableObjDelLog;
}

AppGlobals& AppGlobals::getInstance()
{
    if (AppGlobals::_me == 0)
    {
        AppGlobals::_me = new AppGlobals();
    }
    return (*AppGlobals::_me);
}

AppGlobals::AppGlobals():
    _enableObjDelLog(false)
{

}
