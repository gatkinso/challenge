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

#include "apm.h"
#include "transport.pb.h"
#include "google/protobuf/util/json_util.h"

namespace exagent
{

APM::APM()
{

}

bool APM::process_request(const std::string req_json_str)
{
    challenge::transport::Transport txp_proto;

    if (req_json_str.length() == 0)
    {
        return false;
    }

    auto ret = google::protobuf::util::JsonStringToMessage(req_json_str, &txp_proto);

    if (ret != google::protobuf::util::Status::OK)
    {
        return false;
    }

    for (auto val : txp_proto.string_values())
    {
        if (val.first == "uuid")
        {
            std::lock_guard<std::mutex> lock(mtx_);
            exmap_[val.second] = req_json_str;
            break;
        }
    }

    return true;
}

bool APM::process_response(const std::string res_json_str)
{
    std::lock_guard<std::mutex> lock(mtx_);

    return true;
}

}