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
#ifndef CSAOBJECT
#define CSAOBJECT

/*
  Defines general methods and atributes for all objects of the app
  This is a Abstract Class
*/
class CSAObject
{
    public:
        CSAObject();
        ~CSAObject();

        int getSerialVersionUID();
        static void updateSerialUIDCounter();   // For explanation, this will not work on concurrency...
        virtual void toString() = 0;            // Pure virtual
        virtual int getMemSize() = 0;           // Pure virtual

    private:
        static int serialVersionUIDCounter;
        int serialVersionUID = 0;

};

#endif
