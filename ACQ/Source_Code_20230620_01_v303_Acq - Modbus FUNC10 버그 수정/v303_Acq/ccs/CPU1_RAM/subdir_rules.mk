################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
adc.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq/adc.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

emif.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq/emif.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

io.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq/io.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

loopback.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq/loopback.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq/main.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

modbus.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq/modbus.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

rtc.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq/rtc.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

sci.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq/sci.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

socket.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq/socket.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

tigerwin.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq/tigerwin.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

timer.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq/timer.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

w5300.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq/w5300.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

wizchip_conf.obj: D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq/wizchip_conf.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla1 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu2 -Ooff --opt_for_speed=5 --fp_mode=relaxed --fp_reassoc=on --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/headers/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/common/include" --include_path="D:/SynologyDrive/100_Project/20210809_Acq/300_Program/ccs12/tms320f28377s_v303/v303_Acq" --advice:performance=all --define=CPU1 --define=_FLASH -g --diag_suppress=10063 --diag_warning=225 --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


