// Copyright (C) 2016 InfoTM, XXX
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef IPU_BadEncoder_H
#define IPU_BadEncoder_H

#include <IPU.h>
#include <h264encapi.h>

class IPU_BadEncoder : public IPU{
    private:
        char *Header;
        int HeaderLength;

    public:
        IPU_BadEncoder(std::string, Json *);
        void Prepare();
        void Unprepare();
        void WorkLoop();
        int UnitControl(std::string, void *);
        void GenHeader();
        int Encode(char *in, char *out);

};
#endif
