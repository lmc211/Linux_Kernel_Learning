RK3588 有 10 组 GPIO bank：GPIO0~GPIO9，每组以 A0~A7, B0~B7, C0~C7, D0~D7 作为编号区分，用以下公式计算编号：
GPIO 引脚计算公式：pin = bank * 32 + number
GPIO 小组编号计算公式：number = group * 8 + X

找到led灯是哪个控制的 底板原理图GPIO1_A3 = 1*32 + number
                                                = 0 * 8 + 3 =35