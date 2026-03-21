1.找到led灯是哪个控制的 底板原理图GPIO1_A3

2.配置GPIO的复用关系，方向，数据

3.复用寄存器地址位0xFD5F8020   我们要将 GPIO1_A3 设置为 GPIO，所以 BUS_IOC_GPIO1A_IOMUX_SEL_L 的 bit15:12
这四位设置 0000。另外 bit31:28 要设置为 1111，允许写 bit15:12。