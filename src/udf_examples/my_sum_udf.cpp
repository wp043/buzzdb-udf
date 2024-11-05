#include "common/value.h"
#include <vector>

extern "C" buzzdb::common::Value ExecuteUDF(const std::vector<buzzdb::common::Value> &args) {
    int sum = 0;
    for (const auto &arg : args) {
        sum += arg.GetAs<int>();
    }
    return buzzdb::common::Value(sum);
}
