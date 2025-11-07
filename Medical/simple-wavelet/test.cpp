#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

// Function for convolution
std::vector<double> convolve(const std::vector<double>& signal, const std::vector<double>& filter) {
    int signalLen = signal.size();
    int filterLen = filter.size();
    int outputLen = signalLen + filterLen - 1;
    std::vector<double> output(outputLen, 0.0);

    for (int i = 0; i < signalLen; ++i) {
        for (int j = 0; j < filterLen; ++j) {
            output[i + j] += signal[i] * filter[j];
        }
    }
    return output;
}

// Function for upsampling by inserting zeros (for IDWT)
std::vector<double> upsample(const std::vector<double>& signal) {
    std::vector<double> upsampledSignal(signal.size() * 2, 0.0);
    for (int i = 0; i < signal.size(); ++i) {
        upsampledSignal[2 * i] = signal[i];
    }
    return upsampledSignal;
}

// Single level reconstruction (IDWT)
std::vector<double> idwt_sym5(const std::vector<double>& approx_coeffs, 
                              const std::vector<double>& detail_coeffs,
                              const std::vector<double>& LoR, // Low-pass reconstruction filter
                              const std::vector<double>& HiR  // High-pass reconstruction filter
                              ) {
    // Upsample and convolve with reconstruction filters
    std::vector<double> upsampled_approx = upsample(approx_coeffs);
    std::vector<double> upsampled_detail = upsample(detail_coeffs);

    std::vector<double> reconstructed_approx = convolve(upsampled_approx, LoR);
    std::vector<double> reconstructed_detail = convolve(upsampled_detail, HiR);

    // Sum the results
    std::vector<double> original_signal(reconstructed_approx.size());
    for (int i = 0; i < original_signal.size(); ++i) {
        original_signal[i] = reconstructed_approx[i] + reconstructed_detail[i];
    }
    
    // Note: Border handling (truncation/padding) is important for perfect reconstruction. 
    // The sizes might not match perfectly without proper border handling.
    return original_signal;
}
