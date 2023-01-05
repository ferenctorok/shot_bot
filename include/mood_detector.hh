#pragma once

#include "Arduino.h"
#include <queue>


/// @brief An object for determining whether the mood has dropped significantly by comparing a baseline mean noise value
/// to a comparison mean noise value.
class MoodDetector
{
public:
    /// @brief Enum class for showing the state of the MoodDetector class.
    enum class Status
    {
        uninitialized = 0,
        initialized = 1,
        drop_sensed = 2
    };

    /// @brief Constructs a MoodDetector object.
    /// @param num_baseline_samples The number of samples used to determine the baseline mean value.
    /// @param num_comparison_samples The number of samples used to determine the comparison mean value.
    /// @param significant_difference The difference between the baseline and the comparison mean value in order to consider a change significant.
    MoodDetector(const uint8_t num_baseline_samples, const uint8_t num_comparison_samples, const float significant_difference);

    /// @brief Updates the object with a new noise sample. A new noise sample first gets into the comparison_samples queue, since this contains the
    /// most recent noise samples. Once a noise sample is too old (i.e it gets removed from the comparison_samples queue), it gets pushed into the
    /// baseline_samples queue. Eventually it also gets removed from the baseline_samples queue too.
    /// @param sample The new noise sample.
    void update(const float sample);

    /// @brief Accessor for the status of the MoodDetector object.
    /// @return The current status.
    [[nodiscard]] const Status& get_status() const;

private:
    /// @brief The number of samples used to determine the baseline mean value.
    uint8_t num_baseline_samples;

    /// @brief The number of samples used to determine the comparison mean value.
    uint8_t num_comparison_samples;

    /// @brief The difference for which if the following is true:
    /// baseline_mean_noise > comparison_mean_noise + significant_difference
    /// then the drop in the noise is assumed to be the indicator of a drop in the mood.
    /// Must be between 0 and 1.
    float significant_difference;

    /// @brief FIFO queue that contains the baseline samples.
    std::queue<float> baseline_samples;

    /// @brief FIFO queue that contains the comparison samples.
    std::queue<float> comparison_samples;

    /// @brief The baseline mean noise value.
    float baseline_mean{0.0f};

    /// @brief The comparison mean noise value.
    float comparison_mean{0.0f};

    /// @brief The status of the MoodDetector.
    Status status{Status::uninitialized};
};