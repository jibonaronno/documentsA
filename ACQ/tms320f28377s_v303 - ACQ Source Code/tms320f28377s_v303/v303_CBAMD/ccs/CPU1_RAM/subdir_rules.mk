################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
adc.obj: D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD/adc.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

emif.obj: D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD/emif.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

io.obj: D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD/io.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

loopback.obj: D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD/loopback.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD/main.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

modbus.obj: D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD/modbus.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

rtc.obj: D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD/rtc.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sci.obj: D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD/sci.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

socket.obj: D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD/socket.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

tigerwin.obj: D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD/tigerwin.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

timer.obj: D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD/timer.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

w5300.obj: D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD/w5300.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

wizchip_conf.obj: D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD/wizchip_conf.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1200/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/100_Project_Thomas/20210809_CBAMD/300_Program/ccs12/tms320f28377s_v303/v303_CBAMD" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


