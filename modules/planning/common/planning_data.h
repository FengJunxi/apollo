/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

/**
 * @file
 **/

#ifndef MODULES_PLANNING_COMMON_PLANNING_DATA_H_
#define MODULES_PLANNING_COMMON_PLANNING_DATA_H_

#include <memory>
#include <string>
#include <vector>

#include "modules/common/proto/pnc_point.pb.h"

#include "modules/planning/common/decision_data.h"
#include "modules/planning/common/path/path_data.h"
#include "modules/planning/common/planning_data.h"
#include "modules/planning/common/planning_object.h"
#include "modules/planning/common/speed/speed_data.h"
#include "modules/planning/common/trajectory/publishable_trajectory.h"
#include "modules/planning/reference_line/reference_line.h"

namespace apollo {
namespace planning {

class PlanningData {
 public:
  PlanningData() = default;

  // copy reference line to planning data
  void set_reference_line(const apollo::hdmap::HDMap& hdmap,
                          const std::vector<ReferencePoint>& ref_points);
  void set_decision_data(std::shared_ptr<DecisionData>& decision_data);
  void set_init_planning_point(const TrajectoryPoint& init_planning_point);

  const ReferenceLine& reference_line() const;
  const DecisionData& decision_data() const;
  const TrajectoryPoint& init_planning_point() const;

  DecisionData* mutable_decision_data() const;

  const PathData& path_data() const;
  const SpeedData& speed_data() const;

  PathData* mutable_path_data();
  SpeedData* mutable_speed_data();

  double timestamp() const;

  // aggregate final result together by some configuration
  bool aggregate(const double time_resolution,
                 PublishableTrajectory* PublishableTrajectory);

  std::string DebugString() const;

 protected:
  std::unique_ptr<ReferenceLine> reference_line_ = nullptr;
  std::shared_ptr<DecisionData> decision_data_ = nullptr;
  TrajectoryPoint init_planning_point_;
  PathData path_data_;
  SpeedData speed_data_;
  double timestamp_ = 0.0;
};

}  // namespace planning
}  // namespace apollo

#endif  // MODULES_PLANNING_COMMON_PLANNING_DATA_H_
