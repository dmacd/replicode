//	cpp_programs.cpp
//
//	Author: Eric Nivel
//
//	BSD license:
//	Copyright (c) 2010, Eric Nivel
//	All rights reserved.
//	Redistribution and use in source and binary forms, with or without
//	modification, are permitted provided that the following conditions are met:
//
//   - Redistributions of source code must retain the above copyright
//     notice, this list of conditions and the following disclaimer.
//   - Redistributions in binary form must reproduce the above copyright
//     notice, this list of conditions and the following disclaimer in the
//     documentation and/or other materials provided with the distribution.
//   - Neither the name of Eric Nivel nor the
//     names of their contributors may be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
//	THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
//	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//	DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
//	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "cpp_programs.h"

#include <r_exec/cpp_programs.h>  // for CPPPrograms, CPPPrograms::Program
#include <iostream>               // for operator<<, basic_ostream, cerr, etc
#include <utility>                // for pair

namespace r_code {
class View;
}  // namespace r_code
namespace r_exec {
class Controller;
}  // namespace r_exec


namespace r_exec
{

std::unordered_map<std::string, CPPPrograms::Program> CPPPrograms::Programs;

void CPPPrograms::Register(std::string &pgm_name, Program pgm)
{
    Programs[pgm_name] = pgm;
}

CPPPrograms::Program CPPPrograms::Get(std::string &pgm_name)
{
    std::unordered_map<std::string, Program>::const_iterator it = Programs.find(pgm_name);

    if (it != Programs.end()) {
        return it->second;
    }

    return nullptr;
}

Controller *CPPPrograms::New(std::string &pgm_name, r_code::View *view)
{
    CPPPrograms::Program pgm = Get(pgm_name);

    if (pgm != nullptr) {
        return pgm(view);
    } else {
        std::cerr << "c++ program '" << pgm_name << "' could not be found\n";
        return nullptr;
    }
}
}
