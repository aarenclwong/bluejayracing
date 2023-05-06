#ifndef ADS1115_HPP
#define ADS1115_HPP

#define ADS1115_ADDRESS0 0x48
#define ADS1115_ADDRESS1 0x49
#define ADS1115_ADDRESS2 0x4A
#define ADS1115_ADDRESS3 0x4B


class ADCConstantContainer {
public:
    int address;
    int diff_mux;
    int single_mux;
    
    // Disgusting code, but best way I could think
    // of to allow quick modification later & without
    // reqiring changes to makefile.
    ADCConstantContainer(int location) {
        if (location == 0) {
            address = ADS1115_ADDRESS0;
            diff_mux = ADS1X15_REG_CONFIG_MUX_DIFF_0_1;
            single_mux = ADS1X15_REG_CONFIG_MUX_SINGLE_0;
        } else if (location == 1) {
            address = ADS1115_ADDRESS1;
            diff_mux = ADS1X15_REG_CONFIG_MUX_DIFF_0_1;
            single_mux = ADS1X15_REG_CONFIG_MUX_SINGLE_1;
        } else if (location == 2) {
            address = ADS1115_ADDRESS2;
            diff_mux = ADS1X15_REG_CONFIG_MUX_DIFF_0_1;
            single_mux = ADS1X15_REG_CONFIG_MUX_SINGLE_0;
        } else if (location == 3) {
            address = ADS1115_ADDRESS3;
            diff_mux = ADS1X15_REG_CONFIG_MUX_DIFF_0_1;
            single_mux = ADS1X15_REG_CONFIG_MUX_SINGLE_0;
        }
    }
};

#endif