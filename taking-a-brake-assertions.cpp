#include <cstdio>
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

template <typename T>
struct AutoBrake {
  AutoBrake(const T& publish)
      : collision_threshold_s{5}, speed_mps{}, publish{publish} {};
  void observe(const SpeedUpdate& x) { speed_mps = x.velocity_mps; };
  void observe(const CarDetected& cd) {
    const auto realtive_velocity_mps = speed_mps - cd.velocity_mps;
    const auto time_to_collision_s = cd.distance_m / realtive_velocity_mps;
    if (time_to_collision_s > 0 &&
        time_to_collision_s <= collision_threshold_s) {
      publish(BrakeCommand{time_to_collision_s});
    }
  };
  void set_collision_threshold_s(double x) {
    if (x < 1) throw std::invalid_argument{"Collision less than 1."};
    collision_threshold_s = x;
  }
  double get_collision_threshold_s() const { return collision_threshold_s; }
  double get_speed_mps() const { return speed_mps; }

 private:
  double collision_threshold_s;
  double speed_mps;
  const T& publish;
};

// assertions
constexpr void assert_that(bool statement, const char* message) {
  if (!statement) throw std::runtime_error{message};
}

void initial_speed_is_zero() {
  AutoBrake auto_brake{[](const BrakeCommand&) {}};
  assert_that(auto_brake.get_speed_mps() == 0L, "speed not equal 0");
}

void initial_sensitivity_is_five() {
  AutoBrake auto_brake{[](const BrakeCommand&) {}};
  assert_that(auto_brake.get_collision_threshold_s() == 5L,
              "sensitivity is not 5");
}

void sensitivity_greater_than_1() {
  AutoBrake auto_brake{[](const BrakeCommand&) {}};
  try {
    auto_brake.set_collision_threshold_s(0.5L);
  } catch (const std::exception&) {
    return;
  }
  assert_that(false, "no exception thrown");
}

void speed_is_saved() {
  AutoBrake auto_brake{[](const BrakeCommand&) {}};
  auto_brake.observe(SpeedUpdate{100L});
  assert_that(100L == auto_brake.get_speed_mps(), "speed not saved to 100");
  auto_brake.observe(SpeedUpdate{50L});
  assert_that(50L == auto_brake.get_speed_mps(), "speed not saved to 50");
  auto_brake.observe(SpeedUpdate{0L});
  assert_that(0L == auto_brake.get_speed_mps(), "speed not saved to 0");
}

void alert_when_imminent() {
  int brake_commands_published{};
  AutoBrake auto_brake{[&brake_commands_published](const BrakeCommand&) {
    brake_commands_published++;
  }};
  auto_brake.set_collision_threshold_s(10L);
  auto_brake.observe(SpeedUpdate{100L});
  auto_brake.observe(CarDetected{100L, 0L});
  assert_that(brake_commands_published == 1,
              "brake commands published not one");
}

void no_alert_when_not_imminent() {
  int brake_commands_published{};
  AutoBrake auto_brake{[&brake_commands_published](const BrakeCommand&) {
    brake_commands_published++;
  }};
  auto_brake.set_collision_threshold_s(2L);
  auto_brake.observe(SpeedUpdate{100L});
  auto_brake.observe(CarDetected{100L, 50L});
  assert_that(brake_commands_published == 0, "brake command published");
}

// test harnesses
void run_test(void (*unit_test)(), const char* name) {
  try {
    unit_test();
    printf("[+] Test %s successful.\n", name);
  } catch (const std::exception& e) {
    printf("[-] Test failure in %s. %s.\n", name, e.what());
  }
}

int main() {
  run_test(initial_speed_is_zero, "initial speed is zero");
  run_test(initial_sensitivity_is_five, "initial sensitivity is not five");
  run_test(sensitivity_greater_than_1, "sensitivity greater than 1");
  run_test(speed_is_saved, "speed is saved");
  run_test(alert_when_imminent, "alert when imminent");
  run_test(no_alert_when_not_imminent, "no alert when not imminent");
}