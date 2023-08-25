import numpy as np
import scipy
from scipy.fft import fft, ifft, fftfreq
from scipy.signal import butter, lfilter
from scipy import signal
import argparse
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser()

parser.add_argument("-func", type=str, help="input function name")
parser.add_argument("-file", type=str, help="file path")
parser.add_argument("-smprate", type=str, help="sample rate")
parser.add_argument("-psdsmprate", type=str, help=" psd sample rate")
parser.add_argument("-lcutoff", type=int, help="cut off frequence")
parser.add_argument("-lorder", type=int, help="order of low pass filter")

args = parser.parse_args()


def chuyen_doi_nhi_phan_sang_so_am(nhi_phan):
    # Kiểm tra nếu số nhị phân rỗng

    if len(nhi_phan) == 0:
        return 0
    if len(nhi_phan) != 8:
        return 0

    # Kiểm tra bit dấu
    dau = int(nhi_phan[0])

    # Áp dụng phương pháp bù hai nếu số nhị phân là số âm
    if dau == 1:
        # Đảo bit
        dao_bit = "".join("1" if bit == "0" else "0" for bit in nhi_phan[1:])

        # Chuyển đổi sang số nguyên dương ban đầu

        so_nguyen_duong = int(dao_bit, 2)

        # Lấy bù 1 của số nguyên dương
        bu_1 = ~so_nguyen_duong

        # Chuyển đổi thành số âm
        so_am = bu_1 - 1
        return so_am
    else:
        # Số nhị phân là số dương

        so_nguyen_duong = int(nhi_phan, 2)
        return so_nguyen_duong


def chuyen_doi_hai_byte_sang_so_nguyen(byte1: bin, byte2: bin) -> int:
    integer_value = (byte1 << 8) | byte2
    return integer_value


def extraProcessingFile(x):
    _data = bin(x)[2:]
    return chuyen_doi_nhi_phan_sang_so_am(_data)


def toPositiveNum(x):
    return 65 + x


def lowPassFilterButter(
    signal: list[int], fs: int, cutoff: int, order: int
) -> list[int]:
    b, a = butter(order, cutoff / (0.5 * fs), btype="low")

    # Lọc tín hiệu sử dụng bộ lọc FIR thông thấp
    filtered_signal = lfilter(b, a, signal)
    return filtered_signal


def generate_sine_wave(freq, sample_rate, duration):
    x = np.linspace(0, duration, sample_rate * duration, endpoint=False)
    frequencies = x * freq
    # 2pi because np.sin takes radians
    y = np.sin((2 * np.pi) * frequencies)
    return x, y


def fft_func(filePath: str, sample_rate: int, lcutoff: int, lorder: int) -> None:
    with open(filePath, "rb") as binaryData:
        binData = binaryData.read()
        print(
            bin(binData[0])[2:] + bin(binData[1])[2:],
            chuyen_doi_hai_byte_sang_so_nguyen(binData[0], binData[1]),
        )
        # dataArr = list(map(extraProcessingFile, binData))
        dataArr = []
        for i in range(0, len(binData), 2):
            int_val = chuyen_doi_hai_byte_sang_so_nguyen(binData[i], binData[i + 1])
            dataArr.append(int_val)

        SAMPLE_RATE = sample_rate  # Hertz

        y_t = dataArr
        x_t = [i for i in range(len(y_t))]

        # x_t, y_t = generate_sine_wave(34, 42, 12)

        N = len(y_t)

        y_f = fft(y_t)
        x_f = fftfreq(N, 1 / SAMPLE_RATE)

        y_lpf = lowPassFilterButter(y_t, SAMPLE_RATE, lcutoff, lorder)

        f_sp, t_sp, Sxx_sp = signal.spectrogram(np.array(y_t), SAMPLE_RATE)

        fig, axs = plt.subplots(3)
        axs[0].plot(x_t, y_t)
        axs[0].tick_params(labelsize=8)
        axs[0].grid()

        axs[1].plot(x_f, abs(y_f))
        axs[1].tick_params(labelsize=8)
        axs[1].grid()

        axs[2].plot(x_t, y_lpf)
        axs[2].tick_params(labelsize=8)
        axs[2].grid()

        fig2 = plt.figure("Figure 2")
        plt.pcolormesh(t_sp, f_sp, Sxx_sp, shading="gouraud")
        plt.ylabel("Frequency [Hz]")
        plt.xlabel("Sample")
        # plt.xticks([0, 2, 4, 6, 8, 10], [0, 0.2, 0.4, 0.6, 0.8, 1])

        plt.show()


def main():
    if (
        args.func == "fft_func"
        and args.file
        and args.smprate
        and args.lcutoff
        and args.lorder
    ):
        filePath = args.file
        sample_rate = int(args.smprate)
        lcutoff = args.lcutoff
        lorder = args.lorder
        fft_func(
            filePath=filePath, sample_rate=sample_rate, lcutoff=lcutoff, lorder=lorder
        )
    else:
        print("print input right parameter")


if __name__ == "__main__":
    main()
