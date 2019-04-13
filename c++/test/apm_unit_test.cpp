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

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "apm.h"
#include "transport.pb.h"
#include "google/protobuf/util/json_util.h"

using namespace exagent;

/*  Reference req_str
{  
   "stringValues":{  
      "uuid":"cfdca0e5-b14a-43f5-aa7e-d9a9561064dc",
      "method":"GET",
      "endpoint":"get_tasks",
      "pid":"20513",
      "tid":"140266636424960",
      "timestamp":"2019-04-08 22:27:54.522591",
      "base_url":"http://127.0.0.1:5000/todo/api/v1.0/tasks"
   }
}
*/

class APMUnitTest : public ::testing::Test
{
protected:
    APMUnitTest() {}

    std::string req_str = "{ \"stringValues\": {    \"uuid\": \"cfdca0e5-b14a-43f5-aa7e-d9a9561064dc\"," \
    "\"method\": \"GET\",    \"endpoint\": \"get_tasks\",    \"pid\": \"20513\"," \
    "\"tid\": \"140266636424960\",    \"timestamp\": \"2019-04-08 22:27:54.522591\"," \
    "\"base_url\": \"http://127.0.0.1:5000/todo/api/v1.0/tasks\"  }}";
};

TEST_F(APMUnitTest, process_exchange)
{
    APM apm;

    challenge::transport::Transport txp_proto;
    ASSERT_TRUE(apm.process_request(req_str, "testid"));

    std::string response_json("{ \"response\": { \"timestamp\":\"1554584055\"} }");

    ASSERT_TRUE(apm.process_response(response_json, "testid"));
}

TEST_F(APMUnitTest, process_request_fail_empty_req)
{
    APM apm;
    challenge::transport::Transport txp_proto;
    std::string empty_request_str;
    ASSERT_FALSE(apm.process_request(empty_request_str, "testid"));
}

TEST_F(APMUnitTest, process_request_fail_empty_id)
{
    APM apm;
    challenge::transport::Transport txp_proto;
    std::string empty_id_str;
    ASSERT_FALSE(apm.process_request(req_str, empty_id_str));
}

TEST_F(APMUnitTest, process_exchange_fail_wrongid)
{
    APM apm;
    challenge::transport::Transport txp_proto;
    ASSERT_TRUE(apm.process_request(req_str, "testid"));

    std::string response_json("{ \"response\": { \"timestamp\":\"1554584055\"} }");

    ASSERT_FALSE(apm.process_response(response_json, "testid1"));
}

TEST_F(APMUnitTest, process_exchange_fail_hash_fails)
{
    APM apm;
    challenge::transport::Transport txp_proto;
    ASSERT_TRUE(apm.process_request(req_str, "testid"));

    std::string response_json;

    ASSERT_FALSE(apm.process_response(response_json, "testid"));
}

TEST_F(APMUnitTest, process_exchange_fail_malformed_protojson)
{
    APM apm;
    challenge::transport::Transport txp_proto;
    std::string _req_str = "This is not a valid string";
    ASSERT_TRUE(apm.process_request(_req_str, "testid"));

    std::string response_json;

    ASSERT_FALSE(apm.process_response(response_json, "testid"));
}