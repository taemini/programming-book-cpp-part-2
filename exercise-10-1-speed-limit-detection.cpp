#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cstdio>
#include <functional>
#include <stdexcept>

using ::testing::_;
using ::testing::A;
using ::testing::DoubleEq;
using ::testing::Field;
using ::testing::Invoke;
using ::testing::NiceMock;
using ::testing::StrictMock;

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

struct SpeedLimitDetected {
  double limit_mps;
};

using SpeedUpdateCallback = std::function<void(const SpeedUpdate&)>;
using CarDetectedCallback = std::function<void(const CarDetected&)>;
using SpeedLimitDetectedCallback =
    std::function<void(const SpeedLimitDetected&)>;

struct IServiceBus {
  virtual ~IServiceBus() = default;
  virtual void publish(const BrakeCommand&) = 0;
  virtual void subscribe(SpeedUpdateCallback) = 0;
  virtual void subscribe(CarDetectedCallback) = 0;
  virtual void subscribe(SpeedLimitDetectedCallback) = 0;
};

struct MockServiceBus : IServiceBus {
  MOCK_METHOD1(publish, void(const BrakeCommand& cmd));
  MOCK_METHOD1(subscribe, void(SpeedUpdateCallback callback));
  MOCK_METHOD1(subscribe, void(CarDetectedCallback callback));
  MOCK_METHOD1(subscribe, void(SpeedLimitDetectedCallback callback));
};

// ############## SpeedDetector #################
struct Detector {
  Detector(IServiceBus& bus) : limit_mps{39} {
    bus.subscribe([this](const SpeedLimitDetected& detected) {
      limit_mps = detected.limit_mps;
    });
  }
  double get_limit_mps() const { return limit_mps; }
  void set_limit_mps(double x) { limit_mps = x; }

 private:
  double limit_mps;
};

// ############## AutoBrake #################
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
// #######################################

struct NiceDetectorTest : ::testing::Test {
  NiceMock<MockServiceBus> bus;
  Detector detector{bus};
};

TEST_F(NiceDetectorTest, InitialLimitIs39) {
  ASSERT_DOUBLE_EQ(39, detector.get_limit_mps());
}

struct StrictDetectorTest : ::testing::Test {
  StrictDetectorTest() {
    EXPECT_CALL(bus, subscribe(A<SpeedLimitDetectedCallback>()))
        .Times(1)
        .WillOnce(
            Invoke([this](const auto& x) { limit_detected_callback = x; }));
  }
  StrictMock<MockServiceBus> bus;
  SpeedLimitDetectedCallback limit_detected_callback;
  CarDetectedCallback car_detected_callback;
  SpeedUpdateCallback speed_update_callback;
};

// struct StrictAutoBrakeTest : ::testing::Test {
//   StrictAutoBrakeTest() {
//     EXPECT_CALL(bus, subscribe(A<CarDetectedCallback>()))
//         .Times(1)
//         .WillOnce(Invoke([this](const auto& x) { car_detected_callback = x;
//         }));
//     EXPECT_CALL(bus, subscribe(A<SpeedUpdateCallback>()))
//         .Times(1)
//         .WillOnce(Invoke([this](const auto& x) { speed_update_callback = x;
//         }));
//   }
//   CarDetectedCallback car_detected_callback;
//   SpeedUpdateCallback speed_update_callback;
//   StrictMock<MockServiceBus> bus;
// };

TEST_F(StrictDetectorTest, LimitsAreSaved) {
  Detector detector{bus};
  limit_detected_callback(SpeedLimitDetected{50});
  ASSERT_DOUBLE_EQ(50, detector.get_limit_mps());
  limit_detected_callback(SpeedLimitDetected{100});
  ASSERT_DOUBLE_EQ(100, detector.get_limit_mps());
  limit_detected_callback(SpeedLimitDetected{150});
  ASSERT_DOUBLE_EQ(150, detector.get_limit_mps());
}

// TEST_F(StrictDetectorTest, NoAlertWhenNotImminent) {
//   EXPECT_CALL(bus, subscribe(A<CarDetectedCallback>()))
//       .Times(1)
//       .WillOnce(Invoke([this](const auto& x) { car_detected_callback = x;
//       }));
//   speed_update_callback(SpeedUpdate{40L});
//   speed
// }

struct NiceAutoBrakeTest : ::testing::Test {
  NiceMock<MockServiceBus> bus;
  AutoBrake auto_brake{bus};
};

struct StrictAutoBrakeTest : ::testing::Test {
  StrictAutoBrakeTest() {
    EXPECT_CALL(bus, subscribe(A<CarDetectedCallback>()))
        .Times(1)
        .WillOnce(Invoke([this](const auto& x) { car_detected_callback = x; }));
    EXPECT_CALL(bus, subscribe(A<SpeedUpdateCallback>()))
        .Times(1)
        .WillOnce(Invoke([this](const auto& x) { speed_update_callback = x; }));
  }
  CarDetectedCallback car_detected_callback;
  SpeedUpdateCallback speed_update_callback;
  StrictMock<MockServiceBus> bus;
};

TEST_F(NiceAutoBrakeTest, InitialCarSpeedIsZero) {
  ASSERT_DOUBLE_EQ(0, auto_brake.get_speed_mps());
}

TEST_F(NiceAutoBrakeTest, InitialSensitivityIsFive) {
  ASSERT_DOUBLE_EQ(5, auto_brake.get_collision_threshold_s());
}

TEST_F(NiceAutoBrakeTest, SensitivityGreaterThanOne) {
  ASSERT_ANY_THROW(auto_brake.set_collision_threshold_s(0.5L));
}

TEST_F(StrictAutoBrakeTest, NoAlertWhenNotImminent) {
  // strict mock은 EXEPCT하지 않은 call이 일어나면 fail되는 것을 이용
  AutoBrake auto_brake{bus};

  auto_brake.set_collision_threshold_s(2L);
  speed_update_callback(SpeedUpdate{100L});
  car_detected_callback(CarDetected{1000L, 50L});
}

TEST_F(StrictAutoBrakeTest, AlertWhenImminent) {
  EXPECT_CALL(bus,
              publish(Field(&BrakeCommand::time_to_collision_s, DoubleEq(1L))))
      .Times(1);
  AutoBrake auto_brake{bus};
  auto_brake.set_collision_threshold_s(10L);
  speed_update_callback(SpeedUpdate{100L});
  car_detected_callback(CarDetected{100L, 0L});
}
