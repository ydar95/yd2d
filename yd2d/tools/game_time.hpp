#pragma once
#include<chrono>

namespace yd2d {
  class GameTime {
  public:
    enum class State{Start,Suspend,Stop};
    using time_namespace = std::chrono::system_clock;
    typedef int64_t nsec_type;
  public:
    inline static time_namespace::time_point now() noexcept { return time_namespace::now(); };
    inline static double toSec(nsec_type nsec){ return nsec*1e-9; }
  public:
    explicit GameTime(double scale = 1.0f)
      : m_accumulacted_time()
      , m_start_time(GameTime::now())
      , m_scale(scale)
    { /* pass */}

    inline void reset() {
      m_accumulacted_time = time_namespace::time_point();
      m_start_time = time_namespace::time_point();
    }

    inline void start(double scale = 1.0f) {
      m_state = State::Start;
      m_start_time = GameTime::now();
      m_scale = scale;
    }

    inline void stop() {
      m_state = State::Stop;
      m_accumulacted_time += (now() - m_start_time);
    }

    inline void suspend() {
      m_state = State::Start;
      m_accumulacted_time += (now() - m_start_time);
    }

    inline void resume() {
      m_start_time = GameTime::now();
      m_state = State::Start;
    }

    inline nsec_type time() {
      if (m_state == State::Start) {
        auto total_time = std::chrono::duration_cast<std::chrono::nanoseconds>(m_accumulacted_time.time_since_epoch() + (now() - m_start_time));
        return static_cast<nsec_type>(total_time.count()* m_scale);
      }
      else {
        auto total_time = std::chrono::duration_cast<std::chrono::nanoseconds>(m_accumulacted_time.time_since_epoch());
        return static_cast<nsec_type>(total_time.count()* m_scale);
      }
    }

  private:
    State m_state= State::Stop;
    double m_scale;
    time_namespace::time_point m_accumulacted_time;
    time_namespace::time_point m_start_time;
  };
}