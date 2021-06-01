/* Copyright (c) 2018 vesoft inc. All rights reserved.
 *
 * This source code is licensed under Apache 2.0 License,
 * attached with Common Clause Condition 1.0, found in the LICENSES directory.
 */

#pragma once

#include "common/interface/gen-cpp2/meta_types.h"
#include <glog/logging.h>
#include <string>

namespace nebula {
namespace utils {
class myLogger {
public:
    static void doLog(const std::string &pref, int lglvl, const meta::cpp2::SpaceDesc &sd);
};
}   // namespace utils
}   // namespace nebula
