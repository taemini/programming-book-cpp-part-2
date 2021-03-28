#include <cstdio>
#include <functional>
#include <iostream>
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

std::ostream& operator<<(std::ostream& s, AutoBrake ab) {
  s << "Collision Threshold: " << ab.get_collision_threshold_s() << " s\n";
  s << "Speed: " << ab.get_speed_mps() << " mps\n";

  return s;
}

int main() {
  MockServiceBus bus{};
  AutoBrake auto_brake{bus};
  bus.speed_update_callback(SpeedUpdate{100L});
  bus.car_detected_callback(CarDetected{1000L});
  std::cout << auto_brake;
}
