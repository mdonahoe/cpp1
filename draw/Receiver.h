#pragma once

#include <lcm/lcm-cpp.hpp>
#include <Eigen/Core>
#include "imu_t.hpp"

class Receiver {
public:
    Receiver();
    void run();
    void MessageHandler(const lcm::ReceiveBuffer*,
                        const std::string&,
                        const droidsensor::imu_t*);
    const Eigen::Vector3f GetControl();
    lcm::LCM * lcm_;
    Eigen::Vector3f stick;
};
