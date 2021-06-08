/* Copyright (c) 2018 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#pragma once

#include "common/interface/gen-cpp2/meta_types.h"
// #include "common/thrift/ThriftTypes.h"
#include <glog/logging.h>
#include <string>
#include <common/utils/magic_enum.hpp>

namespace nebula {
namespace utils {
class myLogger {
public:
    static void doLog(const std::string &pref, int lglvl, const meta::cpp2::SpaceDesc &sd);
    static void doLogEncBuf(const std::string &pref, int lglvl, const std::string &buf);
    static void doLogBackTrace(const std::string &pref, int lglvl);

    template<typename S>
    static std::string fetchEnumName(S&& s);

    static constexpr int kBacktraceMaxDepth = 8;
};

template<typename S>
std::string myLogger::fetchEnumName(S&& s) {
    return std::string(magic_enum::enum_name(s));
}

}   // namespace utils
}   // namespace nebula
