#include "mood_detector.hh"


MoodDetector::MoodDetector(
    const uint8_t num_baseline_samples, const uint8_t num_comparison_samples, const float significant_difference
) :
    num_baseline_samples(num_baseline_samples),
    num_comparison_samples(num_comparison_samples),
    significant_difference(significant_difference)
{
}

void MoodDetector::update(const float sample)
{
    // First, updating the comparison members.
    comparison_mean += sample / static_cast<float>(num_comparison_samples);
    comparison_samples.push(sample);

    // If there are too many samples now in the comparison queue, take out the last one, subtract it from
    // the rolling comparison mean and push it into the baseline_samples queue.
    if (comparison_samples.size() > num_comparison_samples)
    {
        const auto old_sample = comparison_samples.front();
        comparison_samples.pop();

        comparison_mean -= old_sample / static_cast<float>(num_comparison_samples);

        baseline_samples.push(old_sample);
        baseline_mean += old_sample / static_cast<float>(num_baseline_samples);

        // Once the baseline queue also contains enough samples, the detector is initialized.
        if (baseline_samples.size() >= num_baseline_samples)
        {
            status = Status::initialized;
        }
    }

    // If there are too many samples now in the baseline_samples queue, remove the oldest element and also
    // subtract it from the rolling baseline mean.
    if (baseline_samples.size() > num_baseline_samples)
    {
        const auto old_sample = baseline_samples.front();
        baseline_samples.pop();

        baseline_mean -= old_sample / static_cast<float>(num_baseline_samples);
    }

    // If the queues are all initialized, we can check whether there is a significant difference.
    if ((status != Status::uninitialized) && (baseline_mean > (comparison_mean + significant_difference)))
    {
        status = Status::drop_sensed;
    }

    return;
}

const MoodDetector::Status& MoodDetector::get_status() const
{
    return status;
}
