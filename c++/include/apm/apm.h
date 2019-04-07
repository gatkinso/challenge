// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#pragma once

#include <vector>
#include <string>
#include <map>
#include <mutex>

namespace exagent
{

class APM
{
public:
    APM();

    bool process_request(const std::string req_json_str);
    bool process_response(const std::string res_json_str);

private:
    std::mutex mtx_;
    std::map<std::string, std::string> exmap_;
};

}


