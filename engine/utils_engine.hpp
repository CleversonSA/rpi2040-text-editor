
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
#ifndef UTILSENGINE
#define UTILSENGINE

#include "../app_globals.hpp"
#include "../csa_object.hpp"

/*
    Abstract class for extra utils that does not fit in any agnostic engine.
*/
class UtilsEngine: public CSAObject
{
public:

    UtilsEngine();
    ~UtilsEngine();

    virtual void sleepMs(long) = 0;
    virtual void softReset() = 0;
    virtual void activateActStatus() = 0;
    virtual void deactivateActStatus () = 0;

private:


};

#endif // DOCUMENT


