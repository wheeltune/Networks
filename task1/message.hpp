#pragma once

#include <cstdint>
#include <string>

#include "logger.hpp"
#include "constants.hpp"


////////////////////////////////////////////////////////////////////////////////

namespace NCsmaCd
{

////////////////////////////////////////////////////////////////////////////////

class Message
{
public:
    enum class State
    {
        Waiting, Sending, Sended, Dropped
    };

public:
    Message() {}

    State GetState() const { return state_; }
    uint64_t GetNumRetries() const { return num_retries_; }
    uint64_t GetStartTime() const { return start_time_; }

    bool OnTick();
    void OnCollision();

private:
    const uint64_t bits_size_ = MESSAGE_SIZE;

    State state_ = State::Waiting;
    uint64_t start_time_ = 0;
    uint64_t sended_bits_ = 0;
    uint64_t num_retries_ = 0;
    uint64_t last_time_ = 0;
    uint64_t backoff_time_ = 0;
};

////////////////////////////////////////////////////////////////////////////////

}  // namespace NCsmaCd

////////////////////////////////////////////////////////////////////////////////