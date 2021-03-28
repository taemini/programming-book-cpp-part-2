#include <gtest/gtest.h>

#include <cstdio>
#include <functional>
#include <stdexcept>

struct SpeedUpdate {
  double velocity_mps;
};

struct CarDetected {
  double distance_m;
  double velocity_mps;
};

struct BrakeCommand {
  double time_to_collision_s;
};

using SpeedUpdateCallback = std::function<void(const SpeedUpdate&)>;
using CarDetectedCallback = std::function<void(const CarDetected&)>;

struct IServiceBus {
  virtual ~IServiceBus() = default;
  virtual void publish(const BrakeCommand&) = 0;
  virtual void subscribe(SpeedUpdateCallback) = 0;
  virtual void subscribe(CarDetectedCallback) = 0;
};

struct MockServiceBus : IServiceBus {
  void publish(const BrakeCommand& cmd) override {
    commands_published++;
    last_command = cmd;
  }
  void subscribe(SpeedUpdateCallback callback) override {
    speed_update_callback = callback;
  }
  void subscribe(CarDetectedCallback callback) override {
    car_detected_callback = callback;
  }

  BrakeCommand last_command{};
  int commands_published{};
  SpeedUpdateCallback speed_update_callback{};
  CarDetectedCallback car_detected_callback{};
};

struct AutoBrake {
  AutoBrake(IServiceBus& bus) : collision_threshold_s{5}, speed_mps{} {
    bus.subscribe(
        [this](const SpeedUpdate& update) { speed_mps = update.velocity_mps; });
    bus.subscribe([this, &bus](const CarDetected& cd) {
      const auto relative_velocity_mps = speed_mps - cd.velocity_mps;
      const auto time_to_collision_s = cd.distance_m / relative_velocity_mps;
      if (time_to_collision_s > 0 &&
          time_to_collision_s <= collision_threshold_s) {
        bus.publish(BrakeCommand{time_to_collision_s});
      }
    });
  }
  void set_collision_threshold_s(double x) {
    if (x < 1) throw std::invalid_argument{"Collision less than 1."};
    collision_threshold_s = x;
  }
  double get_collision_threshold_s() const { return collision_threshold_s; }
  double get_speed_mps() const { return speed_mps; }

 private:
  double collision_threshold_s;
  double speed_mps;
};

// TEST(AutoBrakeTest, InitialCarSpeedIsZero) {
//   MockServiceBus bus{};
//   AutoBrake auto_brake{bus};
//   ASSERT_FLOAT_EQ(0, auto_brake.get_speed_mps());
// }

struct AutoBrakeTest : ::testing::Test {
  MockServiceBus bus{};
  AutoBrake auto_brake{bus};
};

TEST_F(AutoBrakeTest, InitialCarSpeedIsZero) {
  ASSERT_DOUBLE_EQ(0, auto_brake.get_speed_mps());
}

TEST_F(AutoBrakeTest, InitialSensitivityIsFive) {
  ASSERT_DOUBLE_EQ(5, auto_brake.get_collision_threshold_s());
}

TEST_F(AutoBrakeTest, SensitivityGreaterThanOne) {
  ASSERT_ANY_THROW(auto_brake.set_collision_threshold_s(0.5L));
}

TEST_F(AutoBrakeTest, SpeedIsSaved) {
  bus.speed_update_callback(SpeedUpdate{100L});
  ASSERT_EQ(100, auto_brake.get_speed_mps());
  bus.speed_update_callback(SpeedUpdate{50L});
  ASSERT_EQ(50, auto_brake.get_speed_mps());
  bus.speed_update_callback(SpeedUpdate{0L});
  ASSERT_EQ(0, auto_brake.get_speed_mps());
}

TEST_F(AutoBrakeTest, NoAlertWhenNotImminent) {
  auto_brake.set_collision_threshold_s(2L);
  bus.speed_update_callback(SpeedUpdate{100L});
  bus.car_detected_callback(CarDetected{1000L, 50L});
  ASSERT_EQ(0, bus.commands_published);
}

TEST_F(AutoBrakeTest, AlerWhenImminent) {
  auto_brake.set_collision_threshold_s(10L);
  bus.speed_update_callback(SpeedUpdate{100L});
  bus.car_detected_callback(CarDetected{100L, 0L});
  ASSERT_EQ(1, bus.commands_published);
  ASSERT_DOUBLE_EQ(1L, bus.last_command.time_to_collision_s);
}